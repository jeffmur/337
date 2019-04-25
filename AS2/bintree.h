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
    BinTree(const BinTree &);				// deep copy constructor
    ~BinTree();								// destructor, calls makeEmpty
    bool isEmpty() const;					// true if tree is empty, otherwise false
    void makeEmpty();						// make the tree empty so isEmpty returns true
    BinTree& operator=(const BinTree &rhs);
    bool operator==(const BinTree &rhs) const;
    bool operator!=(const BinTree &rhs) const;
    bool insert(NodeData* item);
    bool retrieve(NodeData &targetData, NodeData* pointer) const;
    void displaySideways() const;			// provided below, displays the tree sideways
    void bstreeToArray(NodeData* []) const;
    void arrayToBSTree(NodeData* array[]);
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

// utility functions
    void inorderHelper(Node*) const;
    void sideways(Node*, int) const;		// provided below, helper for displaySideways()
    void setRecursive(Node*);
    void deleteRecursive(Node*);
    bool findRecursive(Node*, NodeData*) const;
    int heightRecursive(Node *cur, NodeData &targetData, int &height);
    bool compareRecur( Node* lhs, Node* rhs ) const;
    void toArrayHelper(Node* current, NodeData* array[], int& i) const;

};

#endif  /* BINTREE_H */