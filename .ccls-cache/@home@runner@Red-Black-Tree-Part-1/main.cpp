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
  void peekHelp(int input);
  void deleteHelp(int input);
  void rightDeleteRotate(Node * x);
  void leftDeleteRotate(Node * x);
  void deleteFix(Node * x, Node * root);
  void dele

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

// PEEK
void peek(Node *root, int space, int input) {

  if (root == NULL) {
    return;
  }

  // Process right child FIRST
  peek(root->right, space, input);

  if (root->data == input) {
    cout << root->data << root->color << " is found! " << endl;
  }

  // Process left child SECOND
  peek(root->left, space, input);

}

Node * minimum(Node * node) {
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
}

void RBTree::leftDeleteRotate(Node * x) {
    Node * y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent ==  NULL) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

void RBTree::rightDeleteRotate(Node * x) {
    Node * y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

void RBTree::deleteFix(Node * x, Node * root) {
  Node * s;
  while (x != root && x->color == 0) {
    if (x == x->parent->left) {
      s = x->parent->right;
      if (s->color == 1) {
        s->color = 0;
        x->parent->color = 1;
        leftDeleteRotate(x->parent);
        s = x->parent->right;
      }

      if (s->left->color == 0 && s->right->color == 0) {
        s->color = 1;
        x = x->parent;
      } else {
        if (s->right->color == 0) {
          s->left->color = 0;
          s->color = 1;
          rightDeleteRotate(s);
          s = x->parent->right;
        }

        s->color = x->parent->color;
        x->parent->color = 0;
        s->right->color = 0;
        leftDeleteRotate(x->parent);
        x = root;
      }
    } else {
      s = x->parent->left;
      if (s->color == 1) {
        s->color = 0;
        x->parent->color = 1;
        rightDeleteRotate(x->parent);
        s = x->parent->left;
      }

      if (s->right->color == 0 && s->right->color == 0) {
        s->color = 1;
        x = x->parent;
      } else {
        if (s->left->color == 0) {
          s->right->color = 0;
          s->color = 1;
          leftDeleteRotate(s);
          s = x->parent->left;
        }

        s->color = x->parent->color;
        x->parent->color = 0;
        s->left->color = 0;
        rightDeleteRotate(x->parent);
        x = root;
      }
    }
  }
  x->color = 0;
}

void RBTree::deleteNodeHelper(Node * root, int key) {
  Node * z = NULL;
  Node * x;
  Node * y;
  while (root != NULL) {
    if (root->data == key) {
      z = root;
    }

    if (root->data <= key) {
      root = root->right;
    } else {
      root = root->left;
    }
  }

  if (z == NULL) {
    cout << "Key not found in the tree" << endl;
    return;
  }

  y = z;
  int y_original_color = y->color;
  if (z->left == NULL) {
    x = z->right;
    // Transplant z & z->right
    if (z->parent == nullptr) {
      root = z->right;
    } else if (z == z->parent->left) {
      z->parent->left = z->right;
    } else {
      z->parent->right = z->right;
    }
    z->right->parent = z->parent;
  } else if (z->right == NULL) {
    x = z->left;
    // Transplant z & z->left)
    if (z->parent == nullptr) {
      root = z->left;
    } else if (z == z->parent->left) {
      z->parent->left = z->left;
    } else {
      z->parent->right = z->left;
    }
    z->left->parent = z->parent;
  } else {
    y = minimum(z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      // Transplan y & y->right)
      if (y->parent == nullptr) {
        root = y->right;
      } else if (y == y->parent->left) {
        y->parent->left = y->right;
      } else {
        y->parent->right = y->right;
      }
      y->right->parent = y->parent;
      // ^Transplant finished^
      y->right = z->right;
      y->right->parent = y;
    }

    // Transplant z & y
    if (z->parent == nullptr) {
      root = y;
    } else if (z == z->parent->left) {
      z->parent->left = y;
    } else {
      z->parent->right = y;
    }
    y->parent = z->parent;
    // ^Transplant finished^
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  delete z;
  if (y_original_color == 0) {
    deleteFix(x, root);
  }
}

// Link print(root,0), peak(root,0) & deleteNode()  so we can call it from main
void RBTree::printHelp() { print(root, 0); }
void RBTree::peekHelp(int input) { peek(root,0, input);}
void RBTree::deleteHelp(int input) {deleteNodeHelper(root, input);}

int main() {

  RBTree tree;

  char action;
  cout << endl
       << "WARNING: NO DUPLICATS OTHER WISE YOU WILL GET ERROR!" << endl;

  while (true) {

    cout << endl
         << "Type A to Insert, B to Print, C to Peek, D to Delete & E to Insert File & Print" << endl;
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

      
    // PEEK
    case 'C':
      cout << "Enter # to Peek: ";
      int input2;
      cin >> input2;

      tree.peekHelp(input2);
      break;
    
    // DELETE
    case 'D':
      cout << "Delete" << endl;
    
      break;
      
    // FILE INSERT
    case 'E':

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