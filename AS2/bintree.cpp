// Jeffrey Murray CSS 343 B SP19
// Created: 4/16/19
// Last Modified: 4/27/19

#include "bintree.h"
#include <array>
using namespace std;

//------------------------- BinTree ---------------------------------
// Constructor for BinTree
BinTree::BinTree() {
    root = nullptr;
}
//------------------------- BinTree ---------------------------------
// Constructor for BinTree that clones (deep copy) of rhs
BinTree::BinTree(const BinTree &old) {
    root = clone(old.root);
}
//------------------------- ~BinTree ---------------------------------
// Deconstructor for BinTree
BinTree::~BinTree() {
	// delete all data in tree
    makeEmpty();
	// delete root
    delete root;
	// set to NULL
    root = nullptr;
}
//------------------------- ~Node ---------------------------------
// Deconstructor for Node - deletes all data and pointers
BinTree::Node::~Node() {
    delete data;
    delete left;
    delete right;
}
//------------------------- isEmpty ---------------------------------
bool BinTree::isEmpty() const {
    return(root == nullptr);
}

//------------------------- makeEmpty ---------------------------------
// deletes all data in the tree, then assigns all pointers to NULL
void BinTree::makeEmpty() {
    deleteRecursive(root);
    root = nullptr;
}

//------------------------- deleteRecursive ---------------------------
// Recursively traverses tree until hitting null ptr (left or right)
// deletes the pointer then assigns pointer to NULL
// returns to previous level
void BinTree::deleteRecursive(Node *current) {
    if(current == NULL)
        return;

    // if left isn't empty set to NULL
    // recurse until hit child
    if(current->left != NULL)
        deleteRecursive(current->left);

    // if right isn't empty set to NULL
    // recurse until hit child
    if(current->right != NULL)
        deleteRecursive(current->right);

    // set both children to NULL
    current->left = NULL;
    current->right = NULL;

    delete current->data;
    current->data = NULL;

    delete current;
    current = NULL;

    return;
}
// end of makeEmpty 

//------------------------- operator= ---------------------------------
// Deletes lhs tree, then assigns lhs a deep copy of rhs
// Postconditions: rhs(copied) tree remains unchanged.
BinTree &BinTree::operator=(const BinTree &rhs) {
    if(*this != rhs){
        // delete remove all data
        makeEmpty();
        // deep copy of rhs
        root = clone(rhs.root);
    }
    return *this;
}
//------------------------- clone ---------------------------------
// Assignment operator recursive function helper 
// returns a pointer to the root
// Creates new nodes with new memory addresses for NodeData
BinTree::Node* BinTree::clone(Node* base){
    // bad data check
    if(base == NULL)
        return NULL;

    // base case
    NodeData* data = new NodeData(*base->data);
    Node *nNode = setData(data);
	
	// traverse left
    if(base->left != NULL)
        nNode->left = clone(base->left);

	// traverse right
    if(base->right != NULL)
        nNode->right = clone(base->right);

    return nNode;
}

//------------------------- operator<< ---------------------------------
// Calls printInOrder() to print out all of the data in the tree
// Overloads operator<< to take in BinTrees and prints in order
ostream& operator<<(ostream& output, const BinTree& rhs) {
    if(rhs.isEmpty())
        output << "Empty!" << endl;
    else{ //print in order (Left, Root, Right)
        rhs.printInOrder();
    }
    output << endl;
    return output;
}

//------------------------- operator== ---------------------------------
bool BinTree::operator==(const BinTree &rhs) const {
    return compareRecur( root, rhs.root );
}
//------------------------- operator!= ---------------------------------
bool BinTree::operator!=(const BinTree &rhs) const {
    return !(*this == rhs);
}
//------------------------- compareRecur ---------------------------------
// Returns true if no execption is found, otherise, return false;
// Note: Will return false if both trees are empty.
bool BinTree::compareRecur( Node* lhs, Node* rhs ) const{
    if(lhs != nullptr && rhs != nullptr) {
        if (*lhs->data != *rhs->data)
            return false;
        else { // continue traversing the tree
            compareRecur(lhs->right, rhs->right);
            compareRecur(lhs->left, lhs->left);
            return true;
        }
    }
    return false;
}
// end of operators

//------------------------- insert ---------------------------------
// inserts NodeData in to the BST and points to the new Node
// Postconditions: NodeData added to the tree
bool BinTree::insert(NodeData *item){

    // bad data check
    if (item == nullptr)
        return false;
    else {
		// assign root
        if (root == nullptr){
            root = setData(item);
            return true;
        }
        else // traverse the tree
            return setRecursive(root, item);
    }
}
//------------------------- setRecursive ---------------------------------
// Returns true if insertion is successful, otherwise returns false.
// For each recusive check, the pointer must be NULL before adding
// NodeData to the tree. 
// Postconditions: New node added to the tree containing desired NodeData
bool BinTree::setRecursive(Node *base, NodeData *toAdd) const{
    // base case
    if(base == nullptr){
        base = setData(toAdd);
        return true;
    }
    // recusive case - duplicate data
    if(*toAdd == *base->data){
        return false;
    }

    // recursive case - right
    if(*toAdd > *base->data){
        if(base->right == NULL){
            Node* rightPtr = setData(toAdd);
            base->right = rightPtr;
            return true;
        }
        else
            return setRecursive(base->right, toAdd);
    }
    // recursive case - left
    if (*toAdd < *base->data){
        if(base->left == NULL){
            Node* leftPtr = setData(toAdd);
            base->left = leftPtr;
            return true;
        }
        else
            return setRecursive(base->left, toAdd);
    }
    return false;
}
// end of insert

//------------------------- retrieve ---------------------------------
// Returns true if targetData is found, otherwise return false.
// Postconditions: pointer is assigned to the memory address of the NodeData if found
// otherwise, nullptr
// Modified operator<< in NodeData.cpp to take in nullptr -> "NULL"
bool BinTree::retrieve(NodeData &targetData, NodeData* &pointer) const{

    pointer = nullptr; 

    if(findRecursive(root, &targetData)){
        pointer = &targetData;
        return true;
    }
    return false;

}
//------------------------- findRecursive ---------------------------------
// Recursive function that returns true if target NodeData is found,
// otherwise, return false.
// Postconditions: BinTree is unchanged
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
// end of retrieve

//------------------------- bstreeToArray ---------------------------------
// Inorder traversal from BSTree to Array
// After recursive function, tree is full of NULL
// Then deleted via makeEmpty
// Postconditions: Deleted BSTree, Array full of tree values in order
void BinTree::bstreeToArray(NodeData* array[]) {
    int i = 0;
	// in-order traversal, add each value to the array 
    toArrayHelper(root, array, i);
	// delete tree
    makeEmpty();
}
//------------------------- toArrayHelper ---------------------------------
// Recursive helper performs an in-order traversal
// Sets tree data to NULL
// Postconditions: Array full of tree values in order, Tree is full of NULL
void BinTree::toArrayHelper(Node* current, NodeData* array[], int& i)  {
    // return if the current node is empty
    if (current == nullptr)
        return;
    // left of the tree
    toArrayHelper(current->left, array, i);
    // copy data to array
    array[i] = current->data;
    // set tree data to null
    current->data = NULL;
    // increment to the next position in array
    i++;
    // right of the tree
    toArrayHelper(current->right, array, i);
    // both sides have been recurred
    // return to previous level
    return;
}
// end of bstreeToArray

//------------------------- arrayToBSTree ---------------------------------
// Assumptions: Array is statically allocated with 100 elements
// root is assigned to the new tree created via pointers
// Postconditions: array is filled with NULL
void BinTree::arrayToBSTree(NodeData *array[]) {
    // calculate length of array
    int length = -1;
    for(int i = 0; i < 100; i++){
        if(array[i] == nullptr)
            break;
        length++;
    }
    // assign root to new tree
    root = balancedTree(array, 0, length);
}
//------------------------- balancedTree ---------------------------------
// Array to a new BSTree, each node is created recursively and added to the tree 
// with Array[(low+high)/2]
// Results in a balanced BSTree and array is full of NULL
BinTree::Node* BinTree::balancedTree(NodeData *nodeArray[], int low, int high) {
    // base case
    if(low > high)
        return NULL;

    // calculate middle element
    int mid = (low + high)/2;

    // root node
    Node *base = setData(nodeArray[mid]);

    // make array empty
    nodeArray[mid] = NULL;

    // recursive case
    base->left = balancedTree(nodeArray, low, mid-1);  // new left subtree
    base->right = balancedTree(nodeArray, mid+1, high);// new right subtree

    return base;

}
// end of arrayToBSTree

//------------------------- getHeight ---------------------------------
// Assumptions: general binary tree where data could be stored anywhere
// returns height of BinTree
// Postconditions: nodeHeight for individual node height passed via reference
int BinTree::getHeight(NodeData &targetData){
    if(findRecursive(root, &targetData)){
        // go to bottom of left & right
        // count until hitting node
        int nodeHeight = 0;
        int treeHeight = heightRecursive(root, targetData, nodeHeight) - 2;
        return nodeHeight;
    }
    else
        return 0; // Node is not in the tree

}
//------------------------- getHeightRecursive ---------------------------------
// Assumptions: general binary tree where data could be stored anywhere
// Passed by Reference: &height = individual node height
// Returns: height of BinTree
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
    // return height of the tree
    if(lDepth > rDepth)
        return lDepth+1;
    else
        return rDepth+1;
}
// end of getHeight

//------------------------- printInOrder ---------------------------------
// Displays NodeData via in-order traversal (Left, Root, Right)
// Preconditions: NONE
void BinTree::printInOrder() const{
    inorderHelper(root);
}


//------------------------- inorderHelper ---------------------------------
// Recursive function to perform in-order traversal of the tree
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::inorderHelper(BinTree::Node *current) const {
    if (current == nullptr)
        return;
    inorderHelper(current->left);
    cout << *current->data << " ";
    inorderHelper(current->right);
}
// end of printInOrder


//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
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
// end of displaySideways



