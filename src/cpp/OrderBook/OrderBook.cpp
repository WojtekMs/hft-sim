#include "OrderBook/OrderBook.hpp"
#include <algorithm>

namespace HFT {
namespace {
void add_order_to_book(std::vector<Order> &orders, Order order) {
  const auto it =
      std::ranges::find_if(orders, [&order](const auto &booked_order) {
        if (order.type_ == OrderType::ASK) {
          return order.price_ <= booked_order.price_;
        }
        return order.price_ >= booked_order.price_;
      });
  if (it != orders.end()) {
    orders.insert(it, std::move(order));
  } else {
    orders.push_back(std::move(order));
  }
}
} // namespace

void OrderBook::add_order(Order order) {
  if (order.type_ == OrderType::ASK) {
    add_order_to_book(asks_, std::move(order));
  } else if (order.type_ == OrderType::BID) {
    add_order_to_book(bids_, std::move(order));
  }
}
std::vector<Order> OrderBook::get_asks() const { return asks_; }
std::vector<Order> OrderBook::get_bids() const { return bids_; }
} // namespace HFT