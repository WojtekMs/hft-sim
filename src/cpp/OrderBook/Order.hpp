#pragma once

#include <chrono>
#include <string>

namespace HFT {
enum class OrderType {
  ASK = 0, // SELL
  BID = 1, // BUY
};

struct Order {
  OrderType type_{};
  int price_{};
  int quantity_{};
  std::chrono::time_point<std::chrono::steady_clock, std::chrono::microseconds>
      timestamp_{};
  std::string asset_id_{};

  friend bool operator==(const Order &, const Order &) = default;
};
} // namespace HFT
