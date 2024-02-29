#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <slim/some.hpp>

TEST_CASE("Correct", "[add]") { REQUIRE(slim::add(1, 2) == 3); }
TEST_CASE("Incorrect", "[add]") { REQUIRE_FALSE(slim::add(1, 2) == 4); }
