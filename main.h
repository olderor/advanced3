#pragma once

#include <iostream>
#include <istream>
#include <vector>

// Stream manager structure.
// Use for reading/writing different data from/to the stream.
// It makes processing input and output easier.
struct stream_manager {

    // Function read_int - procedure for reading an integer from the stream.
    // Parameter std::istream &_Istr - address of any input stream.
    // Parameter int &data - address of the integer, where should be stored input data.
    static void read_int(std::istream &_Istr, int &data);

    // Function read_vector - procedure for reading an vector of the size from the stream.
    // Before reading the data, vector is going to be cleaned.
    // So do not forget, that all the data stored in this vector will be lost.
    // Parameter std::istream &_Istr - address of any input stream.
    // Parameter std::vector<int> &vector - vector, where should be stored input data.
    // Parameter const int size - number of times to read integers from the stream.
    // Also it is the new size of the vector.
    static void read_vector(
        std::istream &_Istr,
        std::vector<int> &vector,
        const int size
    );

    // Function write_int - procedure for writing an integer to the stream.
    // Parameter std::ostream &_Istr - address of any output stream.
    // Parameter const int data - integer, the value of which should be written to the stream.
    static void write_int(std::ostream &_Ostr, const int data);
};

// Implicit treap node structure.
struct node {

    // Field size - number of childs in the node.
    int size;

    // Field value - value that the node stores.
    int value;

    // Pointer to the left child.
    node *left = nullptr;

    // Pointer to the right child.
    node *right = nullptr;

    // Initialization.
    node();

    // Initialization with given value.
    explicit node(int value);
};

// Function size - find number of childs in the node.
// Returns size of the node (if node is not exist, returns 0).
int size(node *root);


// Function update - update size of the node.
// Parameter node *root - pointer to the node that must be updated.
void update(node *root);


// Function merge - merge two treaps into new one.
// Parameter node *left - pointer to the first treap.
// Parameter node *right - pointer to the second treap.
// Parameter node *&result - node where should be stored the result of the merging.
void merge(node *left, node *right, node *&result);


// Function split - split treap into two treaps by position in the array.
// Parameter node *root - pointer to the treap that should be split.
// Parameter node *&left - node where should be stored the first treap.
// Parameter node *&right - node where should be stored the second treap.
// Parameter const int position - position in the array.
void split(node *root, node *&left, node *&right, const int position);

// Function insert - insert new element into array by its position.
// Parameter node *&root - pointer to the treap,
// where should be stored the result of inserting.
// Parameter node *item - node to insert.
// Parameter const int position - position in the array.
void insert(node *&root, node *item, const int position);

// Function print - print array.
// Parameter std::ostream &_Istr - address of any output stream.
// Parameter node *root - treap to print.
void print(std::ostream &_Ostr, node *root);

// Function reorder - move subsegment to the start of the array.
// Parameter node *root - pointer to the treap.
// Parameter const int left - left position in the array.
// Parameter const int right - right position in the array.
// Return node* - pointer to the result of moving.
node* reorder(node *root, const int left, const int right);

// Function build - create new treap.
// Parameter const int size - number of elements in the array.
// Parameter const int left - left bulding border.
// Parameter const int right - right bulding border.
// Return node* - pointer to the created treap.
node* build(const int size, const int left, const int right);

// Function solve - solve given problem.
void solve();

// Main function.
int main();
