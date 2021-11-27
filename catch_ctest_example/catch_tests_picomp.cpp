#include "catch.h"
#include "compute_pi.h"
#include <cmath>

TEST_CASE("test if pi_with_numerical_integration calculates pi", "correctness") {
  constexpr double pi = 3.14159265359;
  constexpr int n = 10000000;
  REQUIRE(std::abs(pi - pi_with_numerical_integration(n)) < 10e-7);
}

TEST_CASE("enter negative number in pi_with_numerical_integration", "stability") {
  constexpr int n = -100;
  REQUIRE(pi_with_numerical_integration(n) == 0.0);
}
