/**
 * Driver for starting BST tests
 */

// some interactive and non-interactive testes to test BST

#include <iostream>

// forward declaration, implementation in bst_test.cpp
void testBSTAll();

int main() {
  testBSTAll();
  std::cout << "Done!" << std::endl;
  std::cin.get();
  return 0;
}

