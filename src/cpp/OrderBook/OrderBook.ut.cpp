#include "OrderBook/OrderBook.hpp"
#include "OrderBook/Order.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace HFT;
using namespace std::chrono_literals;

TEST_CASE("Orders can be added to the OrderBook", "[OrderBook]") {
  auto order_book = OrderBook();
  const auto bid1 = Order{
      .type_ = OrderType::BID,
      .price_ = 100,
      .quantity_ = 10,
      .timestamp_ = std::chrono::time_point<std::chrono::steady_clock,
                                            std::chrono::microseconds>{100us},
      .asset_id_ = "TEST-ASSET"};
  const auto ask1 = Order{
      .type_ = OrderType::ASK,
      .price_ = 110,
      .quantity_ = 10,
      .timestamp_ = std::chrono::time_point<std::chrono::steady_clock,
                                            std::chrono::microseconds>{100us},
      .asset_id_ = "TEST-ASSET"};
  SECTION("Bid can be added") {
    const auto expected_asks = std::vector<Order>{};
    const auto expected_bids = std::vector<Order>{bid1};

    order_book.add_order(bid1);

    REQUIRE(order_book.get_asks() == expected_asks);
    REQUIRE(order_book.get_bids() == expected_bids);
  }
  SECTION("Ask can be added") {
    const auto expected_asks = std::vector<Order>{ask1};
    const auto expected_bids = std::vector<Order>{};

    order_book.add_order(ask1);

    REQUIRE(order_book.get_asks() == expected_asks);
    REQUIRE(order_book.get_bids() == expected_bids);
  }
  GIVEN("Ask added") {
    order_book.add_order(ask1);

    WHEN("Ask with lower price added") {
      auto ask_with_lower_price = ask1;
      ask_with_lower_price.price_ = ask1.price_ - 10;

      order_book.add_order(ask_with_lower_price);

      THEN("Asks are sorted by lowest price") {
        const auto actual_asks = order_book.get_asks();

        REQUIRE(std::ssize(actual_asks) == 2);
        REQUIRE(actual_asks[0].price_ == ask_with_lower_price.price_);
        REQUIRE(actual_asks[1].price_ == ask1.price_);
      }
    }
    WHEN("Many asks with lower price added") {
      auto ask2 = ask1;
      ask2.price_ = ask1.price_ - 10;
      auto ask3 = ask1;
      ask3.price_ = ask1.price_ - 15;
      auto ask4 = ask1;
      ask4.price_ = ask1.price_ - 2;

      order_book.add_order(ask2);
      order_book.add_order(ask3);
      order_book.add_order(ask4);

      THEN("Asks are sorted by lowest price") {
        const auto actual_asks = order_book.get_asks();

        REQUIRE(std::ssize(actual_asks) == 4);
        REQUIRE(actual_asks[0].price_ == ask3.price_);
        REQUIRE(actual_asks[1].price_ == ask2.price_);
        REQUIRE(actual_asks[2].price_ == ask4.price_);
        REQUIRE(actual_asks[3].price_ == ask1.price_);
      }
    }
  }
  GIVEN("Bid added") {
    order_book.add_order(bid1);

    WHEN("Bid with higher price added") {
      auto bid2 = bid1;
      bid2.price_ = bid1.price_ + 10;

      order_book.add_order(bid2);

      THEN("Bids are sorted by highest price") {
        const auto actual_bids = order_book.get_bids();

        REQUIRE(std::ssize(actual_bids) == 2);
        REQUIRE(actual_bids[0].price_ == bid2.price_);
        REQUIRE(actual_bids[1].price_ == bid1.price_);
      }
    }
    WHEN("Many bids with higher price added") {
      auto bid2 = bid1;
      bid2.price_ = bid1.price_ + 10;
      auto bid3 = bid1;
      bid3.price_ = bid1.price_ + 15;
      auto bid4 = bid1;
      bid4.price_ = bid1.price_ + 2;

      order_book.add_order(bid2);
      order_book.add_order(bid3);
      order_book.add_order(bid4);

      THEN("Bids are sorted by highest price") {
        const auto actual_bids = order_book.get_bids();

        REQUIRE(std::ssize(actual_bids) == 4);
        REQUIRE(actual_bids[0].price_ == bid3.price_);
        REQUIRE(actual_bids[1].price_ == bid2.price_);
        REQUIRE(actual_bids[2].price_ == bid4.price_);
        REQUIRE(actual_bids[3].price_ == bid1.price_);
      }
    }
  }
}