#pragma once

#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <utility>

struct treap {
public:
    // Initialization - create new treap with elements from 1 up to size.
    // Parameter const int size - number of elements in the array.
    explicit treap(const int size);

    // Initialization - create new treap.
    // Parameter std::vector<int> &values - elements in the array.
    explicit treap(std::vector<int> &values);

    // Function reorder - move subsegment to the start of the array.
    // Parameter const int left - left position in the array.
    // Parameter const int right - right position in the array.
    void reorder(const int left, const int right);

    // Function get_elements - retrieve elements from the treap in the correct order.
    // Return std::vector<int> - list of elements.
    std::vector<int> get_elements();

    // Function get_description - get description of the treap - print array.
    // Parameter std::string separator - elements in the treap will be separeted by this string.
    // Return std::string - description of the array.
    std::string get_description(const std::string separator = " ");

private:
    // Implicit treap node structure.
    struct node {
        // Field size - number of childs in the node.
        int size;

        // Field value - value that the node stores.
        const int value;

        // Pointer to the left child.
        node *left = nullptr;

        // Pointer to the right child.
        node *right = nullptr;

        // Initialization.
        node();

        // Initialization with given value.
        explicit node(const int value);
    };

    // Pointer to the root element in the tree.
    node *root = nullptr;

    // Function build - create new treap.
    // Parameter const int left - left bulding border.
    // Parameter const int right - right bulding border.
    // Parameter std::vector<int> &values - elements in the array.
    // Return node* - pointer to the created treap.
    node* build(
        const int left,
        const int right,
        std::vector<int> &values);

    // Function update - update size of the node.
    // Parameter node *root - pointer to the node that must be updated.
    void update(node *root);

    // Function size - find number of childs in the node.
    // Returns size of the node (if node is not exist, returns 0).
    int size(node *root);

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

    // Function reorder - move subsegment to the start of the array.
    // Parameter node *root - pointer to the treap.
    // Parameter const int left - left position in the array.
    // Parameter const int right - right position in the array.
    // Return node* - pointer to the result of moving.
    node* reorder(node *root, const int left, const int right);

    // Function get_elements - insert elements from the node to the list.
    // Parameter node *root - pointer to the treap.
    // Parameter std::vector<int> &elements - list, where elements should be stored.
    void get_elements(node *root, std::vector<int> &elements);

    // Function get_description - get description of the node - print array.
    // Parameter node *root - treap to print.
    // Return std::string - description of the array.
    std::string get_description(node *root);
};

// Struct query.
// Used for describing the given query with left and right indexes.
struct query {
public:
    // Field int left_position - left index.
    int left_position;

    // Field int right_position - right index.
    int right_position;

    // Default initialization that gives indexes value 0.
    query();

    // Initialization with given indexes.
    query(const int left, const int right);
};

// Function solve - solve given problem.
// Parameter const int size - number of elements in the array.
// Parameter const int queries_count - number of queries.
// Parameter std::vector<query> &queries - list of queries,
// that contains left and right indexes of each query.
// Return std::vector<int> - elements after processing queries.
std::vector<int> solve(
    const int size,
    const int queries_count,
    std::vector<query> &queries);

// Function read_data - process input.
// Parameter std::istream &_Istr - input stream.
// Parameter const int size - number of elements in the array.
// Parameter const int queries_count - number of queries.
// Parameter std::vector<query> &queries - list of queries,
// that contains left and right indexes of each query.
void read_data(
    std::istream &_Istr,
    int &size,
    int &queries_count,
    std::vector<query> &queries);

// Function write_data - process output.
// Parameter std::ostream &_Ostr - output stream.
// Parameter std::vector<int> &data - list of integer data to write.
void write_data(
    std::ostream &_Ostr,
    std::vector<int> &data);

// Main function.
const int main();
