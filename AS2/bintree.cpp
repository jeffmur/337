// Jeffrey Murray CSS 343 B SP19
// Created: 4/16/19
// Last Modified:

#include "bintree.h"
#include <array>

using namespace std;
BinTree::BinTree() {
    root = nullptr;
}

BinTree::BinTree(const BinTree &old) {
    root = old.root;
    *this = old;
}

BinTree::~BinTree() {
    makeEmpty();
    delete root;
}

BinTree::Node::~Node() {
    delete left;
    delete right;
}

bool BinTree::isEmpty() const {
    return(root == nullptr);
}

void BinTree::makeEmpty() {
    deleteRecursive(root); //REDO!!!!!
    root = nullptr;
}

BinTree &BinTree::operator=(const BinTree &rhs) {
    if(this != &rhs){
        this->makeEmpty();
        setRecursive(rhs.root);
    }
    return *this;
}

ostream& operator<<(ostream& output, const BinTree& rhs) {
    if(rhs.isEmpty())
        output << "Empty!" << endl;
    else{ //print in order (Left, Root, Right)
        rhs.printInOrder();
    }
    output << endl;
    return output;
}

bool BinTree::compareRecur( Node* lhs, Node* rhs ) const{
    if(lhs != nullptr && rhs != nullptr) {
        if (lhs->data != rhs->data)
            return false;
        else {
            compareRecur(lhs->right, rhs->right);
            compareRecur(lhs->left, lhs->left);
            return true;
        }
    }
    //return true;
}

bool BinTree::operator==(const BinTree &rhs) const {
    return compareRecur( root, rhs.root );
}

bool BinTree::operator!=(const BinTree &rhs) const {
    return !(*this == rhs);


}//// Add Recursion !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool BinTree::insert(NodeData *item) {
    // bad data check
    if(item == nullptr)
        return false;
    // iterative pointers
    Node *cur;
    Node *parent = NULL;
    // create new node
    Node *newNode = new Node;
    newNode->data = item;
    newNode->left = NULL;
    newNode->right = NULL;
    // tree is empty
    if (isEmpty()) {
        root = newNode;
        return true;
    } else {
        cur = root;
        // traverse the tree ---- INFINITE LOOP -----
        for(;;) {
            parent = cur;
            // left of the tree
            if (*item < *parent->data) {
                cur = cur->left;
                if (cur == nullptr) {
                    parent->left = newNode;
                    cur = NULL;
                    newNode = NULL;
                    return true;
                }
            }
            // right of the tree
            else if(*item > *parent->data) {
                cur = cur->right;
                if (cur == nullptr) {
                    parent->right = newNode;
                    cur = NULL;
                    newNode = NULL;
                    return true;
                }
            }
            // duplicate data
            else {
                cur = NULL;
                newNode = NULL;
                return false;
            }
        }
    }
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool BinTree::retrieve(NodeData &targetData, NodeData* pointer) const{
    if(findRecursive(root, &targetData)){
        pointer = &targetData;
        return true;
    }
    pointer = nullptr; // Modified operator<< in NodeData.cpp to take in nullptr
    return false;

}

void BinTree::toArrayHelper(Node* current, NodeData* array[], int& i) const {
    // return if the current node is empty
    if (current == nullptr)
        return;
    // left of the tree
    toArrayHelper(current->left, array, i);
    // copy data to array
    array[i] = current->data;
    // set tree data to null
    current->data = nullptr;
    // increment to the next position in array
    i++;
    // right of the tree
    toArrayHelper(current->right, array, i);
    // both sides have been recurred
    // return to previous level
    return;
}

void BinTree::bstreeToArray(NodeData* array[]) const{
    int i = 0;
    toArrayHelper(root, array, i);
    for (int j = 0; j < 25; j++)
        cout << *array[j] << " ";
    cout << endl;
}

//void BinTree::arrayToBSTree(NodeData * array[]) const{
//
//}

int BinTree::heightRecursive(Node *cur, NodeData& targetData, int &height){
    // end of the tree
    if(cur == NULL)
        return 1;

    // recursive case (find the bottom)
    int lDepth = heightRecursive(cur->left, targetData, height);  // left most branch
    int rDepth = heightRecursive(cur->right, targetData, height); // right most branch
    // save height of node once reached
    if(*cur->data == targetData){
        if(lDepth > rDepth)
            height = lDepth;
        else
            height = rDepth;
    }
    if(lDepth > rDepth)
        return lDepth+1;
    else
        return rDepth+1;
}
// Assumptions: general binary tree where data could be stored anywhere
//
int BinTree::getHeight(NodeData &targetData){
    if(findRecursive(root, &targetData)){
        // go to bottom of left & right
        // count until hitting node
        int nodeHeight = 0;
        int treeHeight = heightRecursive(root, targetData, nodeHeight);
        return nodeHeight;
    }
    else
        return 0; // Node is not in the tree

}

void BinTree::printInOrder() const{
    inorderHelper(root);
}

// Recursive function to perform in-order traversal of the tree
void BinTree::inorderHelper(BinTree::Node *current) const {
    if (current == nullptr)
        return;
    inorderHelper(current->left);
    cout << *current->data << " ";
    inorderHelper(current->right);
}


//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
    sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
    if (current != nullptr) {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        // display information of object
        cout << *current->data << endl;
        sideways(current->left, level);
    }
}

void BinTree::setRecursive(Node *current) {
    if(current != nullptr){
        insert(current->data);
        setRecursive(current->left);
        setRecursive(current->right);
    }

}

void BinTree::deleteRecursive(Node *current) {
    if(current != nullptr){
        deleteRecursive(current->right);
        deleteRecursive(current->left);
        current = NULL;
    }
}

bool BinTree::findRecursive(Node *current, NodeData *target) const{
    // rainy day
    if(current == nullptr)
        return false;
    // base case
    if(*target == *current->data)
        return true;
    // greater than (right subtree)
    else if(*target > *current->data)
        findRecursive(current->right, target);
    else
        // less than (left subtree)
        findRecursive(current->left, target);
}



