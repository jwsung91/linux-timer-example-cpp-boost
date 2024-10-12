#include <boost/asio.hpp>
#include <chrono>
#include <iomanip>
#include <iostream>

void print_timestamp() {
  auto now = std::chrono::system_clock::now();
  auto now_time = std::chrono::system_clock::to_time_t(now);
  std::cout << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
}

void timer_handler(const boost::system::error_code&) {
  std::cout << "Timer end (";
  print_timestamp();
  std::cout << ")";
}

int main() {
  boost::asio::io_context io;
  boost::asio::steady_timer timer(io, boost::asio::chrono::seconds(5));

  std::cout << "Timer start: 5 sec (";
  print_timestamp();
  std::cout << ")" << std::endl;

  timer.async_wait(&timer_handler);

  io.run();
  return 0;
}
