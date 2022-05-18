/*
Name: Jyoti Gurung
Period: 1
Project: Red-Black Tree; Add #s to the tree, and print tree
*/

#include <iostream>

using namespace std;

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

//Just Initialize Functions up here
Node * insert(Node* & root, int & data);
void print(Node *root, int space);

int main(){
  
  Node * root;
  root = NULL;
  char action;

  while (true) {
    
    cout << endl << "Type A to Add, B to Print" << endl;
    cin >> action;

    switch (action) {

      //ADD
      case 'A':

        cout << "Enter #: ";
        int input;
        cin >> input;

        if (input > 999 || input <= 0) {
          cout << "INVALID: Enter a # between 1-999!" << endl;
          break;
        }
        
        
        break;

      //PRINT
      case 'B':
        print(root, 0)
        break;
      
    }
  
  }  
  
}


//ADD
Node * insert(Node* & root, int & data) {
  //When it's the first time, or when root node is NULL you create a new node and add data to it, & create left & right nodes
  if(root == NULL) {
    root = new Node;
    root->data = data;
    root->right = NULL;
    root->left = NULL;
  }
  //When data is greater than "root" then add to the right branch recursively
  else if(root->data < data) {
    root->right = insert(root->right,data);
  }
  //When data is smaller than "root" then add to left branch recursively
  else {
    root->left = insert(root->left,data);
  }
  return root; 
}

//PRINT
void print(Node *root, int space) {

    if (root == NULL) {
      return;
    }
 
    //IMPORTLANT FOR VISUALS: Sideways screen height/width - Tab 1 - Keep += # same as Tab 2
    space += 10;
 
    // Process right child FIRST
    print(root->right, space);
 
    // Print current node after SPACE
    cout << endl;
    //IMPORTANT FOR VISUALS: Sideways screen width/height - Tab 2 - Keep i # same as Tab 1
    for (int i = 10; i < space; i++) {
      cout << " ";
    }
    cout << root->data << endl;
 
    // Process left child SECOND
    print(root->left, space);
  
}

/*
Sources:
https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/: code for printing stuff
Aneeq Chowdhury: to smoothen out add & peek
*/