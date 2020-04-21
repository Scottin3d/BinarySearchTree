/**
 * Testing BST - Binary Search Tree functions
 *
 * This file has series of tests for BST
 * Each test is independent and uses assert statements
 * Test functions are of the form
 *
 *      test_netidXX()
 *
 * where netid is UW netid and XX is the test number starting from 01
 *
 * Test functions can only use the public functions from BST
 * testBSTAll() is called from main in main.cpp
 * testBSTAll calls all other functions
 * @author Multiple
 * @date ongoing
 */

#include "bst.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

/**
 * Trying to avoid global variables,
 * by creating a singleton class with our visitor functions
 * stringstream SS contains the output from visitor
 */
class TreeVisitor {
public:
  // never create an instance of TreeVisitor object
  // we'll just use the static functions
  TreeVisitor() = delete;

  // insert output to SS rather than cout, so we can test it
  static stringstream SS;

  static string getSS() { return SS.str(); }

  static void resetSS() { SS.str(string()); }

  // instead of cout, insert item into a string stream
  static void visitor(const string &Item) { SS << Item; }

  // instead of cout, insert item into a string stream
  static void visitor(const int &Item) { SS << Item; }
};

// initialize the static variable
//  warning: initialization of 'SS' with static storage duration
//  may throw an exception that cannot be caught [cert-err58-cpp]
//  Not sure how to do it without making code harder to read
//  NOLINTNEXTLINE
stringstream TreeVisitor::SS;

/**
 * Test functions by Yusuf Pisan
 */

// Testing ==
void testPisan01() {
  cout << "Starting testPisan01" << endl;
  cout << "* Testing == and !=" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  // == and != for empty trees
  assert(B1 == B2 && (!(B1 != B2)));
  B1.add("c");
  B2.add("c");
  B3.add("b");
  // == and !- for 1-Node trees B1, B2, B3
  assert(B1 == B2 && (!(B1 != B2)));
  assert(B1 != B3 && (!(B1 == B3)));
  cout << "Ending testPisan01" << endl;
}

// Testing == in detail
void testPisan02() {
  cout << "Starting testPisan02" << endl;
  cout << "* Testing == and != with more detail" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
    B1.add(S);

  for (auto &S : vector<string>{"c", "f", "a", "g", "x"})
    B2.add(S);

  B3.add("b");

  // == for 5-Node trees B1, B2
  assert(B1 == B2 && (!(B1 != B2)));

  BST<string> B4(B3);
  // copy constructor for 1-Node trees B3, B4
  assert(B3 == B4 && (!(B3 != B4)));

  BST<string> B5(B1);
  // copy constructor for 5-Node trees B1, B5
  assert(B1 == B5 && (!(B5 != B1)));

  BST<string> B7("b");
  // 1-param constructor for 1-Node trees B3, B7
  assert(B3 == B7 && (!(B3 != B7)));

  cout << "Ending testPisan02" << endl;
}

// Testing traversal
void testPisan03() {
  cout << "Starting testPisan03" << endl;
  cout << "* Testing traversal" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
    B1.add(S);

  for (auto &S : vector<string>{"c", "f", "a", "g", "x"})
    B2.add(S);

  B3.add("b");

  TreeVisitor::resetSS();
  B1.inOrderTraverse(TreeVisitor::visitor);
  string Result = "acfgx";
  assert(TreeVisitor::getSS() == Result);

  TreeVisitor::resetSS();
  B1.preOrderTraverse(TreeVisitor::visitor);
  Result = "cafgx";
  assert(TreeVisitor::getSS() == Result);

  TreeVisitor::resetSS();
  B1.postOrderTraverse(TreeVisitor::visitor);
  Result = "axgfc";
  assert(TreeVisitor::getSS() == Result);

  cout << "Visual check B1:" << endl;
  cout << B1 << endl;
  cout << "Ending testPisan03" << endl;
}

// tests number of nodes and height functions
void testSample01() {
  cout << "Starting testSample01" << endl;
  cout << "==============================" << endl;

  BST<string> B1;
  B1.add("A");
  B1.add("B");
  B1.add("C");
  std::cout << "Number of nodes in B1: " << B1.numberOfNodes() << std::endl;
  std::cout << "Height of B1: " << B1.getHeightNS() << std::endl;
  std::cout << B1 << std::endl;
  B1.rebalance();
  std::cout << B1 << std::endl;
  
  cout << "==============================" << endl;
  cout << "Ending testSample01" << endl;
}

// tests the remove functions
void removeTest() {
  cout << "         Remove Test" << endl;
  cout << "==============================" << endl;

  TreeVisitor::resetSS();
  int Array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  BST<int> B1(Array, 10);

  std::cout << B1 << std::endl;

  B1.remove(5);
  std::cout << B1 << std::endl;

  B1.remove(11);
  std::cout << B1 << std::endl;

  B1.remove(1);
  B1.remove(2);
  B1.remove(9);
  B1.remove(8);

  std::cout << B1 << std::endl;
  // inorder
  B1.inOrderTraverse(TreeVisitor::visitor);
  std::cout << "In order : " << TreeVisitor::getSS() << std::endl;
  TreeVisitor::resetSS();

  cout << "==============================" << endl;
  cout << "       Ending Remove Test" << endl;
}

// tests bst from array constructor
void testArrays() {
  cout << "           testArray" << endl;
  cout << "==============================" << endl;

  TreeVisitor::resetSS();
  int Array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  BST<int> B1(Array, 10);

  // inorder
  B1.inOrderTraverse(TreeVisitor::visitor);
  std::cout << "In order : " << TreeVisitor::getSS() << std::endl;
  TreeVisitor::resetSS();
  // preorder
  B1.preOrderTraverse(TreeVisitor::visitor);
  std::cout << "Pre order : " << TreeVisitor::getSS() << std::endl;
  TreeVisitor::resetSS();
  // post order
  B1.postOrderTraverse(TreeVisitor::visitor);
  std::cout << "Post order : " << TreeVisitor::getSS() << std::endl;
  TreeVisitor::resetSS();

  std::cout << B1 << std::endl;
  cout << "==============================" << endl;
  cout << "       Ending testArray" << endl;
}

// tests a mixed number array bst
void testMixedArrays() {
  cout << "           testMixedArray" << endl;
  cout << "==============================" << endl;

  TreeVisitor::resetSS();
  int Array[] = {11, 14, 43, 54, 123, 87, 65, 32, 12, 43};
  BST<int> B1(Array, 10);
  std::cout << "Creating and array of ints: " << std::endl;
  for (int N : Array) {
    std::cout << N << ", ";
  }
  std::cout << std::endl;

  std::cout << B1 << std::endl;
  // inorder
  B1.inOrderTraverse(TreeVisitor::visitor);
  std::cout << "In order : " << TreeVisitor::getSS() << std::endl;
  // preorder
  TreeVisitor::resetSS();
  B1.preOrderTraverse(TreeVisitor::visitor);
  std::cout << "Pre order : " << TreeVisitor::getSS() << std::endl;
  // post order
  TreeVisitor::resetSS();
  B1.postOrderTraverse(TreeVisitor::visitor);
  std::cout << "Post order : " << TreeVisitor::getSS() << std::endl;
  std::cout << B1 << std::endl;

  // rebalance array
  B1.rebalance();
  std::cout << "Rebalancing tree." << std::endl;
  TreeVisitor::resetSS();
  B1.inOrderTraverse(TreeVisitor::visitor);
  std::cout << "In order : " << TreeVisitor::getSS() << std::endl;
  
  std::cout << B1 << std::endl;

  cout << "==============================" << endl;
  cout << "       Ending testMixedArray" << endl;
}

// tests the clear function
void testClear() {
  cout << "        Clear BST Test" << endl;
  cout << "==============================" << endl;

  TreeVisitor::resetSS();
  int Array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  BST<int> B1(Array, 10);

  std::cout << B1 << std::endl;
  std::cout << "Clearing BST..." << std::endl;
  B1.clear();
  std::cout << B1 << std::endl;

  cout << "==============================" << endl;
  cout << "     Ending Clear BST Test" << endl;
}

// Calling all test functions
void testBSTAll() {
  testPisan01();
  testPisan02();
  testPisan03();
  testSample01();
  testArrays();
  removeTest();
  testMixedArrays();
  testClear();
}