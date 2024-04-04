#include "tracer.hpp"

namespace traceroute::net {

Tracer::Tracer(int max_ttl, int timeout, int attempts_num)
    : max_ttl_(max_ttl), timeout_(timeout), attempts_num_(attempts_num) {}

Tracer::Tracer() : Tracer(64, 3000, 3) {}

void Tracer::Trace(std::string const &host, std::ostream &out) {
  Randomizer randomizer;
  std::string unlikely_port =
      std::to_string(randomizer.NumRange(1024, USHRT_MAX));

  addrinfo *dns_lookup_res = nullptr;
  int err = getaddrinfo(host.c_str(), unlikely_port.c_str(), nullptr,
                        &dns_lookup_res);
  if (err == -1) {
    out << strerror(errno) << '\n';
    return;
  }

  char ip_destination[INET_ADDRSTRLEN];
  inet_ntop(AF_INET,
            &reinterpret_cast<sockaddr_in *>(dns_lookup_res->ai_addr)->sin_addr,
            ip_destination, dns_lookup_res->ai_addrlen);

  int on = 1;

  int send_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (send_sock == -1) {
    out << strerror(errno) << '\n';
    return;
  }
  setsockopt(send_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);

  int recv_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);
  if (recv_sock == -1) {
    out << strerror(errno) << '\n';
    return;
  }
  setsockopt(recv_sock, IPPROTO_IP, IP_HDRINCL, &on, sizeof on);
  timeval timeout;
  timeout.tv_sec = timeout_ / 1000;
  timeout.tv_usec = timeout_ % 1000 * 1000;
  setsockopt(recv_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);

  char const msg[] = "...";
  char buffer[kBufferCapacity];

  char ip_current[INET_ADDRSTRLEN];
  char host_current[NI_MAXHOST];

  out << "Maximum TTL: " << max_ttl_ << '\n';
  out << "Maximum respond time: " << timeout_ << "ms\n";
  out << "Connection attempts number: " << attempts_num_ << "\n\n";
  out << "Your destination is " << ip_destination << " (" << host << ").\n";

  sockaddr last_addr{};
  socklen_t len = sizeof last_addr;

  std::set<std::string> traversed;

  int curr_ttl = 1;
  while (curr_ttl <= max_ttl_ && strcmp(ip_current, ip_destination) != 0) {
    setsockopt(send_sock, IPPROTO_IP, IP_TTL, &curr_ttl, sizeof curr_ttl);

    out << curr_ttl << ' ';
    out.flush();

    int t;

    int attempts_used = 0;
    while (attempts_used < attempts_num_) {
      auto start = std::chrono::high_resolution_clock::now();

      sendto(send_sock, msg, sizeof msg, NULL, dns_lookup_res->ai_addr,
             dns_lookup_res->ai_addrlen);
      setsockopt(recv_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);
      recvfrom(recv_sock, buffer, kBufferCapacity, NULL, &last_addr, &len);

      auto stop = std::chrono::high_resolution_clock::now();

      auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
      t = duration.count();

      inet_ntop(AF_INET, &reinterpret_cast<sockaddr_in *>(&last_addr)->sin_addr,
                ip_current, len);

      std::string ip(ip_current);
      if (traversed.contains(ip)) {
        attempts_used++;
        out << "* ";
        out.flush();
      } else {
        traversed.insert(ip);
        getnameinfo(&last_addr, len, host_current, sizeof host_current, NULL,
                    NULL, NULL);
        break;
      }
    }

    if (attempts_used < attempts_num_) {
      out << host_current;
      out << " (" << ip_current << ") ";
      out << t << "ms";
    }
    out << '\n';
    curr_ttl++;
  }
}

} // namespace traceroute::net
