// Jeffrey Murray CSS 343 B SP19
// Created: 4/16/19
// Last Modified:

#ifndef BINTREE_H
#define BINTREE_H

#include "nodedata.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class BinTree {				// you add class/method comments and assumptions
    friend ostream& operator<< (ostream& output, const BinTree& n); // output tree data in order
public:
    BinTree();								// constructor
    BinTree(const BinTree &rhs);				// deep copy constructor
    ~BinTree();								// destructor, calls makeEmpty
    bool isEmpty() const;					// true if tree is empty, otherwise false
    void makeEmpty();						// make the tree empty so isEmpty returns true
    BinTree& operator=(const BinTree &rhs);
    bool operator==(const BinTree &rhs) const;
    bool operator!=(const BinTree &rhs) const;
    bool insert(NodeData* item);
    bool retrieve(NodeData &targetData, NodeData* &pointer) const;
    void displaySideways() const;			// provided below, displays the tree sideways
    void bstreeToArray(NodeData* []);
    void arrayToBSTree(NodeData* []);
    int getHeight(NodeData &);
    void printInOrder() const;

private:
    struct Node {
        virtual ~Node();

        NodeData* data;						// pointer to data object
        Node* left;							// left subtree pointer
        Node* right;						// right subtree pointer
    };
    Node* root;								// root of the tree

    struct Node* setData(NodeData *item) const{
        Node *temp = new Node();
        temp->data = item;
        temp->left = nullptr;
        temp->right = nullptr;
        return temp;
    }


// utility functions
    void inorderHelper(Node*) const;
    void sideways(Node*, int) const;		// provided below, helper for displaySideways()
    void deleteRecursive(Node*);
    void toArrayHelper(Node* current, NodeData* array[], int& i);
    BinTree::Node* clone(Node* base);
    BinTree::Node* balancedTree(NodeData* [], int low, int high);
    bool setRecursive(Node *base, NodeData *data) const;
    bool findRecursive(Node*, NodeData*) const;
    bool compareRecur( Node* lhs, Node* rhs ) const;
    int heightRecursive(Node *cur, NodeData &targetData, int &height);

};

#endif  /* BINTREE_H */