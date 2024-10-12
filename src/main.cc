#include <boost/asio.hpp>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

std::string get_timestamp() {
  std::ostringstream oss;
  auto now = std::chrono::system_clock::now();
  auto now_time = std::chrono::system_clock::to_time_t(now);
  oss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
  return oss.str();
}

void timer_handler(const boost::system::error_code&, int64_t& current_repeat,
                   int64_t repeat_count, boost::asio::steady_timer& timer,
                   int64_t delay_seconds, boost::asio::io_context& io) {
  std::cout << "Timer end (" << current_repeat + 1 << "/" << repeat_count
            << ") [" << get_timestamp() << "]" << std::endl;

  if (++current_repeat < repeat_count) {
    timer.expires_after(boost::asio::chrono::seconds(delay_seconds));
    timer.async_wait([&](const boost::system::error_code& ec) {
      timer_handler(ec, current_repeat, repeat_count, timer, delay_seconds, io);
    });
  } else {
    io.stop();
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <delay_seconds> <repeat_count>"
              << std::endl;
    return 1;
  }

  int64_t delay_seconds = std::stoll(argv[1]);
  int64_t repeat_count = std::stoll(argv[2]);
  int64_t current_repeat = 0;

  boost::asio::io_context io;
  boost::asio::steady_timer timer(io,
                                  boost::asio::chrono::seconds(delay_seconds));

  std::cout << "Timer start (" << delay_seconds << " sec): " << get_timestamp()
            << std::endl;

  timer.async_wait([&](const boost::system::error_code& ec) {
    timer_handler(ec, current_repeat, repeat_count, timer, delay_seconds, io);
  });

  io.run();
  return 0;
}
