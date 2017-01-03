#include <iostream> 
#include <istream> 
#include <fstream> 
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <utility>

// Stream manager structure.
// Use for reading/writing different data from/to the stream.
// It makes processing input and output easier.
struct stream_manager {
public:
    // function read_int - procedure for reading an integer from the stream.
    // parameter std::istream &_Istr - address of any input stream.
    // parameter int &data - address of the integer, where should be stored input data.
    static void read_int(std::istream &_Istr, int &data) {
        _Istr >> data;
    }

    // function read_vector - procedure for reading an vector of the size from the stream.
    // Before reading the data, vector is going to be cleaned.
    // So do not forget, that all the data stored in this vector will be lost.
    // parameter std::istream &_Istr - address of any input stream.
    // parameter std::vector<int> &vector - vector, where should be stored input data.
    // parameter const int size - number of times to read integers from the stream.
    // Also it is the new size of the vector.
    static void read_vector(
        std::istream &_Istr,
        std::vector<int> &vector,
        const int size) {
        vector.resize(size);
        for (int i = 0; i < size; ++i) {
            _Istr >> vector[i];
        }
    }

    // function write_int - procedure for writing an integer to the stream.
    // parameter std::ostream &_Istr - address of any output stream.
    // parameter const int data - integer, the value of which should be written to the stream.
    static void write_int(std::ostream &_Ostr, const int data) {
        _Ostr << data << " ";
    }
};


// Implicit treap node structure.
struct node {
    int size, value;
    node *left = nullptr;
    node *right = nullptr;
    node() {}
    // Initialization with given value.
    explicit node(int value) : value(value) {}
};

// function size - find number of childs in the node.
// returns size of the node (if node is not exist, returns 0).
int size(node *root) {
    return root ? root->size : 0;
}

// function update - update size of the node.
// parameter node *root - pointer to the node that must be updated.
void update(node *root) {
    if (!root) {
        return;
    }
    root->size = 1 + size(root->left) + size(root->right);
}

// function merge - merge two treaps into new one.
// parameter node *left - pointer to the first treap.
// parameter node *right - pointer to the second treap.
// parameter node *&result - node where should be stored the result of the merging.
void merge(node *left, node *right, node *&result) {
    if (!left) {
        result = right;
    } else if (!right) {
        result = left;
    } else if (left->value > right->value) {
        merge(left->right, right, left->right);
        result = left;
    } else {
        merge(left, right->left, right->left);
        result = right;
    }
    update(result);
}

// function split - split treap into two treaps by position in the array.
// parameter node *root - pointer to the treap that should be split.
// parameter node *&left - node where should be stored the first treap.
// parameter node *&right - node where should be stored the second treap.
// parameter const int position - position in the array.
void split(node *root, node *&left, node *&right, const int position) {
    if (!root) {
        left = right = nullptr;
        return;
    }
    if (position <= size(root->left)) {
        split(root->left, left, root->left, position), right = root;
    } else {
        split(root->right, root->right, right, position - 1 - size(root->left)), left = root;
    }
    update(root);
}

// function insert - insert new element into array by its position.
// parameter node *&root - pointer to the treap,
// where should be stored the result of inserting.
// parameter node *item - node to insert.
// parameter const int position - position in the array.
void insert(node *&root, node *item, const int position) {
    node *before, *after;
    split(root, before, after, position);
    merge(before, item, before);
    merge(before, after, root);
}

// function print - print array.
// parameter std::ostream &_Istr - address of any output stream.
// parameter node *root - treap to print.
void print(std::ostream &_Ostr, node *root) {
    if (root->left) {
        print(_Ostr, root->left);
    }
    stream_manager::write_int(_Ostr, root->value);
    if (root->right) {
        print(_Ostr, root->right);
    }
}

// function reorder - move subsegment to the start of the array.
// parameter node *root - pointer to the treap.
// parameter const int left - left position in the array.
// parameter const int right - right position in the array.
// return node* - pointer to the result of moving.
node *reorder(node *root, const int left, const int right) {
    node *before_left, *after_left;
    split(root, before_left, after_left, left - 1);

    node *between_left_and_right, *after_right;
    split(after_left, between_left_and_right, after_right, right - left + 1);


    node *temp, *result;
    merge(between_left_and_right, before_left, temp);
    merge(temp, after_right, result);

    return result;
}

// function build - create new treap.
// parameter const int size - number of elements in the array.
// return node* - pointer to the created treap.
node* build(const int size) {
    node *root = new node(1);
    for (int i = 2; i <= size; ++i) {
        insert(root, new node(i), i - 1);
    }
    return root;
}

// function solve - solve given problem.
void solve() {
    int size, queries;

    stream_manager::read_int(std::cin, size);
    stream_manager::read_int(std::cin, queries);

    node *root = build(size);

    for (int i = 0; i < queries; ++i) {
        int left, right;    
        stream_manager::read_int(std::cin, left);
        stream_manager::read_int(std::cin, right);
        root = reorder(root, left, right);
    }

    print(std::cout, root);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    solve();

    return 0;
}
