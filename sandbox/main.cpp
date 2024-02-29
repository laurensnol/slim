#include <slim/some.hpp>
#include <iostream>

auto main() -> int {
  const int result = slim::add(1, 2);
  std::cout << result << "\n";

  return 0;
}
