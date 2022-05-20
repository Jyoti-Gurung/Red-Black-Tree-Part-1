/*
Name: Jyoti Gurung
Period: 1
Project: Red-Black Tree; Insert #s to the tree, and print tree
*/

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

using namespace std;
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

struct Node {
  int data;
  char color; //'r': Red, 'b': Black
  Node *left, *right, *parent;

  // Constructor
  Node(int data) {
    this->data = data;
    left = right = parent = NULL;
    this->color = 'r'; // all Nodes usually 'r' for Red
  }
};

// Class to represent Red-Black Tree
class RBTree {
private:
  Node *root;

protected:
  void rotateLeft(Node *&, Node *&);
  void rotateRight(Node *&, Node *&);
  void fixViolation(Node *&, Node *&);

public:
  // Constructor
  RBTree() { root = NULL; }
  void insert(const int &n);
  void printHelp();
};

// INSERT
Node *BSTInsert(Node *root, Node *pt) {
  // If the tree is empty, return a new node
  if (root == NULL) {
    return pt;
  }

  // Otherwise, and if Pt < root; recur down tree
  if (pt->data < root->data) {
    root->left = BSTInsert(root->left, pt);
    root->left->parent = root;
  }
  // Otherwise, and if Pt > root; recur down tree
  else if (pt->data > root->data) {
    root->right = BSTInsert(root->right, pt);
    root->right->parent = root;
  }

  // return the (unchanged) node root pointer
  return root;
}

/*
*
Left & Right Rotations with clauses inside them
*
*/
void RBTree::rotateLeft(Node *&root, Node *&pt) {
  Node *pt_right = pt->right;

  pt->right = pt_right->left;

  if (pt->right != NULL) {
    pt->right->parent = pt;
  }

  pt_right->parent = pt->parent;

  if (pt->parent == NULL) {
    root = pt_right;
  }

  else if (pt == pt->parent->left) {
    pt->parent->left = pt_right;
  }

  else {
    pt->parent->right = pt_right;
  }

  pt_right->left = pt;
  pt->parent = pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt) {
  Node *pt_left = pt->left;

  pt->left = pt_left->right;

  if (pt->left != NULL) {
    pt->left->parent = pt;
  }

  pt_left->parent = pt->parent;

  if (pt->parent == NULL) {
    root = pt_left;
  }

  else if (pt == pt->parent->left) {
    pt->parent->left = pt_left;
  }

  else {
    pt->parent->right = pt_left;
  }

  pt_left->right = pt;
  pt->parent = pt_left;
}

// Fix Violations After Insertion: we call the rotateRight & rotateLeft
// Functions here
void RBTree::fixViolation(Node *&root, Node *&pt) {
  Node *parent_pt = NULL;
  Node *grand_parent_pt = NULL;

  while ((pt != root) && (pt->color != 'b') && (pt->parent->color == 'r')) {

    parent_pt = pt->parent;
    grand_parent_pt = pt->parent->parent;

    /* Case: A
            Parent of pt is left child
            of Grand-parent of pt */
    if (parent_pt == grand_parent_pt->left) {

      Node *uncle_pt = grand_parent_pt->right;

      /* Case: 1
      The uncle of pt is also red:
      Only Recoloring required */
      if (uncle_pt != NULL && uncle_pt->color == 'r') {
        grand_parent_pt->color = 'r';
        parent_pt->color = 'b';
        uncle_pt->color = 'b';
        pt = grand_parent_pt;
      }

      else {
        /* Case: 2
        pt is right child of its parent
        Left-rotation required */
        if (pt == parent_pt->right) {
          rotateLeft(root, parent_pt);
          pt = parent_pt;
          parent_pt = pt->parent;
        }

        /* Case : 3
        pt is left child of its parent
        Right-rotation required */
        rotateRight(root, grand_parent_pt);
        swap(parent_pt->color, grand_parent_pt->color);
        pt = parent_pt;
      }
    }

    /* Case : B
    Parent of pt is right child
    of Grand-parent of pt */
    else {
      Node *uncle_pt = grand_parent_pt->left;

      /* Case : 1
              The uncle of pt is also red
              Only Recoloring required */
      if ((uncle_pt != NULL) && (uncle_pt->color == 'r')) {
        grand_parent_pt->color = 'r';
        parent_pt->color = 'b';
        uncle_pt->color = 'b';
        pt = grand_parent_pt;
      } else {
        /* Case : 2
        pt is left child of its parent
        Right-rotation required */
        if (pt == parent_pt->left) {
          rotateRight(root, parent_pt);
          pt = parent_pt;
          parent_pt = pt->parent;
        }

        /* Case : 3
        pt is right child of its parent
        Left-rotation required */
        rotateLeft(root, grand_parent_pt);
        swap(parent_pt->color, grand_parent_pt->color);
        pt = parent_pt;
      }
    }
  }

  root->color = 'b'; // reset root as Black
}

// Insert Driver: call on BSTInsert, and fix violations afterwards
void RBTree::insert(const int &data) {
  Node *pt = new Node(data);

  // Do a normal BST insert
  root = BSTInsert(root, pt);

  // fix Red Black Tree violations
  fixViolation(root, pt);
}

// PRINT
void print(Node *root, int space) {

  if (root == NULL) {
    return;
  }

  // IMPORTLANT FOR VISUALS: Sideways screen height/width - Tab 1 - Keep += #
  // same as Tab 2
  space += 10;

  // Process right child FIRST
  print(root->right, space);

  // Print current node after SPACE
  cout << endl;
  // IMPORTANT FOR VISUALS: Sideways screen width/height - Tab 2 - Keep i # same
  // as Tab 1
  for (int i = 10; i < space; i++) {
    cout << " ";
  }
  cout << root->data << root->color << endl;

  // Process left child SECOND
  print(root->left, space);
}

// Link print(root,0) so we can call it from main
void RBTree::printHelp() { print(root, 0); }

int main() {

  RBTree tree;

  char action;
  cout << endl
       << "WARNING: NO DUPLICATS OTHER WISE YOU WILL GET ERROR!" << endl;

  while (true) {

    cout << endl
         << "Type A to Insert, B to Print, C to Insert File & Print" << endl;
    cin >> action;

    switch (action) {

    // INSERT
    case 'A':

      cout << "Enter #: ";
      int input;
      cin >> input;

      if (input > 999 || input <= 0) {
        cout << "INVALID: Enter a # between 1-999!" << endl;
        break;
      }

      tree.insert(input);
      break;

    // PRINT
    case 'B':
      tree.printHelp();
      break;

    // FILE INSERT
    case 'C':

      string filename("input.txt");
      int number;

      ifstream input_file(filename);
      if (!input_file.is_open()) {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        return EXIT_FAILURE;
      }

      while (input_file >> number) {
        cout << number << " ";
        tree.insert(number);
      }
      cout << endl << endl;

      tree.printHelp();

      input_file.close();

      return EXIT_SUCCESS;

      break;
    }
  }
}

/*
Sources:
1. https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/:
Trouble with rotations and parenting
2. https://replit.com/@JyotiGurung/Binary-Search-Tree#main.cpp:
Smooth out Printing, and structure
3. https://www.delftstack.com/howto/cpp/read-int-from-file-cpp/:
Insert Numbers from a file
*/