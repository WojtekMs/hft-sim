#pragma once

#include <vector>

#include "OrderBook/Order.hpp"
// Requirements

// Should be able to accept sell offers (ASK)
// SELL,ASSET-ID,PRICE,QUANTITY,TIMESTAMP

// Should be able to accept buy offers (BID)
// BUY,ASSET-ID,PRICE,QUANTITY,TIMESTAMP

// When trading ASK, then always choose the highest BID
// When trading BID, then always choose the lowest ASK
// Offers are sorted by price-time
// When more offers with the same price-time then use FIFO

// Not covered:
// offers without a price (an aggressive offer, want to buy/sell right away by
// the best price) floating-point prices
namespace HFT {
class OrderBook {
public:
  void add_order(Order order);
  [[nodiscard]] std::vector<Order> get_asks() const;
  [[nodiscard]] std::vector<Order> get_bids() const;

private:
  std::vector<Order> asks_{};
  std::vector<Order> bids_{};
};
} // namespace HFT