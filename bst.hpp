// Yusuf Pisan pisan@uw.edu
// 15 Jan 2018
// edited by scott shirley 0760484

// BST class
// Creates a BST to store values
// Uses Node which holds the Data
// Uses templates to store any type of Data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BST_HPP
#define BST_HPP

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

template<class T>
class BST {
  // display BST tree in a human-readable format
  // given, should not need to be modified
  friend std::ostream &operator<<(std::ostream &Out, const BST &Bst) {
    Bst.printSideways(Out, Bst.Root);
    Out << std::endl;
    Bst.printVertical(Out, Bst.Root);
    return Out;
  }

private:
  // Node for BST
  struct Node {
    explicit Node(T Value) { Data = Value; Left = nullptr; Right = nullptr; }
    T Data;
    struct Node *Left;
    struct Node *Right;
  };

  // refer to data type "struct Node" as Node
  using Node = struct Node;

  // root of the tree
  Node *Root{ nullptr };

  // height of a Node, nullptr is 0, Root is 1, static, no access to 'this'
  static int getHeight(const Node* Node) {
    // base case
    if (Node == nullptr) {
      return 0;
    }
    // depth of BST
    int LeftDepth = 1 + getHeight(Node->Left);
    int RightDepth = 1 + getHeight(Node->Right);
    // check for bigger
    if (LeftDepth > RightDepth) {
      return LeftDepth;
    }
    return RightDepth;
  }

  /**
   * DO NOT MODIFY
   * print tree sideways with root on left
                6
            2
                5
        0
                4
            1
                3
   */
  static std::ostream &printSideways(std::ostream &Out, const Node *Curr, int Level = 0) {
    const static char SP = ' ';
    const static int ReadabilitySpaces = 4;
    if (!Curr)
      return Out;
    printSideways(Out, Curr->Right, ++Level);
    Out << std::setfill(SP) << std::setw(Level * ReadabilitySpaces) << SP;
    Out << Curr->Data << std::endl;
    printSideways(Out, Curr->Left, Level);
    return Out;
  }

  static std::ostream &centeredPrint(std::ostream &Out, int Space,
    const std::string &Str, char FillChar = ' ') {
    auto StrL = static_cast<int>(Str.length());
    int Extra = (Space - StrL) / 2;
    if (Extra > 0) {
      Out << std::setfill(FillChar) << std::setw(Extra + StrL) << Str;
      Out << std::setfill(FillChar) << std::setw(Space - Extra - StrL) << FillChar;
    }
    else {
      Out << std::setfill(FillChar) << std::setw(Space) << Str;
    }
    return Out;
  }

  /**
   * DO NOT MODIFY
   * print tree with the root at top
   *
      _____0______
   __1___      __2___
  3     4     5     6
   *
  **/
  static std::ostream &printTreeLevel(std::ostream &Out, std::queue<const Node *> &Q,
    int Width, int Depth, int MaxDepth) {
    const static char SP = ' ';
    const static char UND = '_';
    int Nodes = 0;
    int MaxN = static_cast<int>(pow(2, Depth - 1));
    int SpaceForEachItem = Width * static_cast<int>(pow(2, MaxDepth - 1)) / MaxN; // NOLINT
    std::string Bigspace = std::string(static_cast<uint64_t>(SpaceForEachItem / 4), SP);
    while (Nodes++ < MaxN) {
      const Node *Tp = Q.front();
      Node *TpL = nullptr;
      Node *TpR = nullptr;
      Q.pop();
      std::string Label = "N";
      if (Tp) {
        std::stringstream Ss;
        Ss << Tp->Data;
        Label = Ss.str();
        TpL = Tp->Left;
        TpR = Tp->Right;
      }
      char Filler = Depth == MaxDepth ? SP : UND;
      if (Depth == MaxDepth) {
        centeredPrint(Out, SpaceForEachItem, Label, Filler);
      }
      else {
        Out << Bigspace;
        centeredPrint(Out, SpaceForEachItem / 2, Label, Filler);
        Out << Bigspace;
        Q.push(TpL);
        Q.push(TpR);
      }
    }
    Out << std::endl;
    return Out;
  }

  // helper function for displaying tree sideways, works recursively
  static std::ostream &printVertical(std::ostream &Out, Node *Curr) {
    const static int WIDTH = 6;  // must be even
    if (!Curr)
      return Out << "[__]";
    // figure out the maximum depth which determines how wide the tree is
    int MaxDepth = getHeight(Curr);
    std::queue<const Node *> Q;
    Q.push(Curr);
    for (int Depth = 1; Depth <= MaxDepth; ++Depth) {
      printTreeLevel(Out, Q, WIDTH, Depth, MaxDepth);
    }
    return Out;
  }

public:
  // constructor, empty tree
  BST() = default;

  // constructor, tree with root
  explicit BST(const T &RootItem) {
    Root = new Node(RootItem);
    //Root->Data = RootItem;
    Root->Left = nullptr;
    Root->Right = nullptr;
  }

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (i.e. rebalance)
  // Assignment specification
  // NOLINTNEXTLINE
  BST(const T Arr[], int N) {
    Root = sortArrayBST(Arr, 0, N - 1);
  }

  // creates a sorted bst from an array
  // constructor helper
  Node* sortArrayBST(const T Array[], int Start, int End) {
    if (Start > End) {
      return nullptr;
    }

    int Middle = (Start + End) / 2;

    Node* NodePtr = new Node(Array[Middle]);
    NodePtr->Left = sortArrayBST(Array, Start, Middle - 1);
    NodePtr->Right = sortArrayBST(Array, Middle + 1, End);

    return NodePtr;
  }

  // copy constructor
  BST(const BST<T> &Bst) {
    if (Bst.Root == nullptr) {
      Root = nullptr;
    }
    else {
      Root = copyTree(Bst.Root);
    }
  }

  // copy helper
  Node* copyTree(const Node *CopyFrom) {
    if (CopyFrom == nullptr) {
      return  nullptr;
    }
    Node* CopyTo = new Node(CopyFrom->Data);
    CopyTo->Left = copyTree(CopyFrom->Left);
    CopyTo->Right = copyTree(CopyFrom->Right);
    return CopyTo;
  }

  // destructor
  virtual ~BST() {
    clear();
    delete Root;
  }

  // true if no nodes in BST
  bool isEmpty() const {
    return Root == nullptr;
  }

  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int getHeightNS() const {
    if (Root == nullptr) {
      return 0;
    }
    return getHeightNS(Root);
  }

  // getHeight helper
  int getHeightNS(Node* NodePtr) const {
    if (NodePtr == nullptr) {
      return 0;
    }
    int LeftHeight = getHeightNS(NodePtr->Left);
    int RightHeight = getHeightNS(NodePtr->Right);

    if (LeftHeight > RightHeight) {
      return 1 + LeftHeight;
    }

    return 1 + RightHeight;

  }

  // TFV Number of nodes in BST O(n)
  int numberOfNodes() const {
    return numberOfNodes(Root);
  }

  // TFV numberOfNodes helper
  int numberOfNodes(Node* NodePtr) const {
    // base case
    if (NodePtr == nullptr) {
      return 0;
    }
    int Count = 1;
    // left
    Count += numberOfNodes(NodePtr->Left);
    // right
    Count += numberOfNodes(NodePtr->Right);
    return Count;
  }

  // add a new item, return true if successful
  bool add(const T &Item) {
    std::cout << "Add " << Item << std::endl;
    if (add(Item, Root)) {
      std::cout << Item << " added!" << std::endl;
      return true;
    }
    std::cout << Item << " already in tree!" << std::endl;
    return false;
  }

  // add helper node*
  bool add(const T &Item, Node*& NodePtr) {
    // base check
    if (NodePtr == nullptr) {
      NodePtr = new Node(Item);
      return true;
    }
    // if < node data
    if (Item < NodePtr->Data) {
      add(Item, NodePtr->Left);
    }
    // if > node data
    else if (Item > NodePtr->Data) {
      add(Item, NodePtr->Right);
    }
    return false;
  }
  
  // remove item, return true if successful
  bool remove(const T &Item) {
    std::cout << "Removing " << Item << std::endl;
    if (remove(Item, Root)) {
      std::cout << Item << " removed!" << std::endl;
      return true;
    }
    std::cout << Item << " not found in tree!" << std::endl;
    return false;
  }

  // remove helper
  bool remove(const T &Item, Node*& NodePtr) {
    if (NodePtr == nullptr) { return false; }
    // if less than current node
    if (Item < NodePtr->Data) {
      return remove(Item, NodePtr->Left);
    }
    // if less than current node
    // NOLINTNEXTLINE
    else if (Item > NodePtr->Data) {
      return remove(Item, NodePtr->Right);
    }
    // else is equal
    // NOLINTNEXTLINE
    else {
      // no children
      if (NodePtr->Left == nullptr &&
          NodePtr->Right == nullptr) {
        delete NodePtr;
        NodePtr = nullptr;
        return true;
      }
      // no left leaf
      // NOLINTNEXTLINE
      else if (NodePtr->Left == nullptr) {
        Node* Tmp = NodePtr;
        NodePtr = NodePtr->Right;
        delete Tmp;

      }
      // no right leaf
      // NOLINTNEXTLINE
      else if (NodePtr->Right == nullptr) {
        Node* Tmp = NodePtr;
        NodePtr = NodePtr->Left;
        delete Tmp;
      }
      // no free leaf, find next to fill
      // NOLINTNEXTLINE
      else {
        Node* TmpNode = getSuccessor(NodePtr->Right);
        NodePtr->Data = TmpNode->Data;
        remove(TmpNode->Data, NodePtr->Right);
      }
      return true;
    }
  }

  // get successor
  Node* getSuccessor(Node* NodePtr) {
    // base
    if (NodePtr == nullptr) {
      return NodePtr;
    }
    Node* Curr = NodePtr;
    // find next successor
    while (Curr && Curr->Left != nullptr) {
      Curr = Curr->Left;
    }
    return Curr;
  }

  // true if item is in BST
  bool contains(const T &Item) const {
    return constains(Item, Root);
  }

  // contains helper
  bool constains(const T &Item, Node* NodePtr) const {
    // base check
    if (NodePtr == nullptr) {
      return false;
    }
    if (Item == NodePtr->Data) {
      return true;
    } // check left
    if (Item < NodePtr->Data) {
      return contains(Item, NodePtr->Left);
    } // check right
    // NOLINTNEXTLINE
    else {
      return contains(Item, Root->Right);
    }
  }

  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void inOrderTraverse(void Visit(const T &Item)) const {
    // base case
    if (Root == nullptr) {
      return;
    }
    // traverse with helper
    inOrderTraverse(Visit, Root);
  }

  // inOrder helper
  void inOrderTraverse(void Visit(const T &Item), Node* NodePtr) const {
    // base case
    if (NodePtr != nullptr) {
      inOrderTraverse(Visit, NodePtr->Left);
      T Item = NodePtr->Data;
      Visit(Item);
      inOrderTraverse(Visit, NodePtr->Right);
    }
  }

  // preorder traversal: root-left-right
  void preOrderTraverse(void Visit(const T &Item)) const {
    // base case
    if (Root == nullptr) {
      return;
    }
    // traverse with helper
    preOrderTraverse(Visit, Root);
  }

  // preOrder helper
  void preOrderTraverse(void Visit(const T &Item), Node* NodePtr) const {
    // base case
    if (NodePtr != nullptr) {
      // print curr node data
      T Item = NodePtr->Data;
      Visit(Item);
      // print left node
      preOrderTraverse(Visit, NodePtr->Left);
      // print right node
      preOrderTraverse(Visit, NodePtr->Right);
    }
  }

  // postOrder traversal: left-right-root
  void postOrderTraverse(void Visit(const T &Item)) const {
    // base case
    if (Root == nullptr) {
      return;
    }
    // traverse with helper
    postOrderTraverse(Visit, Root);
  }

  // postOrder helper
  void postOrderTraverse(void Visit(const T &Item), Node* NodePtr) const {
    // base case
    if (NodePtr != nullptr) {
      // print left node
      postOrderTraverse(Visit, NodePtr->Left);
      // print right node
      postOrderTraverse(Visit, NodePtr->Right);
      // print curr node data
      T Item = NodePtr->Data;
      Visit(Item);
    }
  }

  // create dynamic array, copy all the items to the array
  // and then read the array to re-create this tree from scratch
  // so that resulting tree is balanced
  void rebalance() {
    std::cout << "Rebalancing tree..." << std::endl;
    int NumberOfNodes = numberOfNodes();
    // inorder traversal into array

    // with array
    int CurrIndex = 0;
    int* Index = &CurrIndex;
    T *TreeArray = new T[NumberOfNodes];
    treeToArray(Root, TreeArray, *Index);
    std::cout << "Array created with " << NumberOfNodes << " nodes." << std::endl;

    // inorder traversal into vector
    // recreate tree from scratch
    std::cout << "Clearing old array..." << std::endl;

    std::cout << "Repopulating tree..." << std::endl;
    clear(Root);
    Root = sortArrayBST(TreeArray, 0, NumberOfNodes - 1);

    // debug
    std::cout << "Tree rebalanced!" << std::endl;
    // delete dynamic array
    delete[] TreeArray;
  }

  // make array
  // NOLINTNEXTLINE
  void treeToArray(Node* NodePtr, T* &NodeArray, int &CurrIndex) {
    // base check
    if (NodePtr == nullptr) {
      return;
    }
    // find first
    treeToArray(NodePtr->Left, NodeArray, CurrIndex);
    std::cout << "Adding " << NodePtr->Data << " to index " << CurrIndex << std::endl;
    // slot in array
    NodeArray[CurrIndex] = NodePtr->Data;
    CurrIndex++;
    treeToArray(NodePtr->Right, NodeArray, CurrIndex);
  }

  // delete all nodes in tree
  void clear() {
    // traverse tree and delete nodes
    clear(Root);
    // set root to null
    Root = nullptr;
  }

  // clear helper
  void clear(Node* NodePtr) {
    // base case
    if (NodePtr == nullptr) {
      return;
    }
    clear(NodePtr->Left);
    clear(NodePtr->Right);
    //std::cout << "Deleting node: " << NodePtr->Data << std::endl;
    delete NodePtr;
  }

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BST<T> &Other) const {
    return doubleEqualsHelper(Root, Other.Root);
  }

  // operator== helper
  bool doubleEqualsHelper(Node* CompareTo, Node *Other) const {
    // if both are null
    if (CompareTo == nullptr && Other == nullptr) {
      return true;
    }

    // if one is null
    if ((CompareTo == nullptr && Other != nullptr) ||
      (CompareTo != nullptr && Other == nullptr)) {
      return false;
    }

    bool ReturnBool = false;
    // compare data
    if (CompareTo->Data == Other->Data) {
      // left branch
      ReturnBool = doubleEqualsHelper(CompareTo->Left, Other->Left);
      //right branch
      ReturnBool = doubleEqualsHelper(CompareTo->Right, Other->Right);

    }
    return ReturnBool;
  }

  // not == to each other
  bool operator!=(const BST<T> &Other) const {
    return !(doubleEqualsHelper(Root, Other.Root));
  }
};

#endif  // BST_HPP
