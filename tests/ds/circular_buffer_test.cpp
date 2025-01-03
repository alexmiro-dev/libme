// tests/ds/circular_buffer_test.cpp
#include <catch2/catch_test_macros.hpp>
import me.ds.circular_buffer;

TEST_CASE("circular_buffer basic operations", "[ds][circular_buffer]") {
  me::ds::circular_buffer<int, 5> buffer;

    /*
  SECTION("new buffer is empty") {
    REQUIRE(buffer.empty());
    REQUIRE_FALSE(buffer.full());
    REQUIRE(buffer.size() == 0);
  }

  SECTION("push and front operations") {
    buffer.push(42);
    REQUIRE_FALSE(buffer.empty());
    REQUIRE(buffer.front() == 42);
    REQUIRE(buffer.size() == 1);
  }

  SECTION("buffer fills correctly") {
    for(int i = 0; i < 5; ++i) {
      buffer.push(i);
    }
    REQUIRE(buffer.full());
    REQUIRE(buffer.size() == 5);
  }
  */
}