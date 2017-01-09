#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <utility>

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

    // Function write_string - procedure for writing an string to the stream.
    // Parameter std::ostream &_Istr - address of any output stream.
    // Parameter const string data - string, the value of which should be written to the stream.
    static void write_string(std::ostream &_Ostr, std::string &data);
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







void stream_manager::read_int(std::istream &_Istr, int &data) {
    _Istr >> data;
}

void stream_manager::read_vector(
    std::istream &_Istr,
    std::vector<int> &vector,
    const int size
) {
    vector.resize(size);
    for (int i = 0; i < size; ++i) {
        _Istr >> vector[i];
    }
}

void stream_manager::write_int(std::ostream &_Ostr, const int data) {
    _Ostr << data << " ";
}

void stream_manager::write_string(std::ostream &_Ostr, std::string &data) {
    _Ostr << data << "\n";
}


node::node() {}
node::node(int value) : value(value) {}

int size(node *root) {
    return root ? root->size : 0;
}

void update(node *root) {
    if (!root) {
        return;
    }
    root->size = 1 + size(root->left) + size(root->right);
}

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

void insert(node *&root, node *item, const int position) {
    node *before, *after;
    split(root, before, after, position);
    merge(before, item, before);
    merge(before, after, root);
}

std::string get_description(node *root) {
    std::string res = "";
    if (root->left) {
        res = res + get_description(root->left);
    }
    res = res + std::to_string(root->value) + " ";
    if (root->right) {
        res = res + get_description(root->right);
    }
    return res;
}

node* reorder(node *root, const int left, const int right) {
    node *before_left, *after_left;
    split(root, before_left, after_left, left - 1);

    node *between_left_and_right, *after_right;
    split(after_left, between_left_and_right, after_right, right - left + 1);


    node *temp, *result;
    merge(between_left_and_right, before_left, temp);
    merge(temp, after_right, result);

    return result;
}

node* build(const int size, const int left, const int right) {
    const int element = (left + right + 1) / 2;
    if (element > size || element <= 0 || left > right) {
        return nullptr;
    }
    node *root = new node(element);
    root->left = build(size, left, element - 1);
    root->right = build(size, element + 1, right);
    update(root);
    return root;
}

std::string solve(
    const int size,
    const int queries_count,
    std::vector<std::pair<int, int>> &queries
) {
    node *root = build(size, 1, size);

    for (int i = 0; i < queries_count; ++i) {
        root = reorder(root, queries[i].first, queries[i].second);
    }

    return get_description(root);
}

void read_data(
    int &size,
    int &queries_count,
    std::vector<std::pair<int, int>> &queries
) {

    stream_manager::read_int(std::cin, size);
    stream_manager::read_int(std::cin, queries_count);

    queries.resize(queries_count);

    for (int i = 0; i < queries_count; ++i) {
        stream_manager::read_int(std::cin, queries[i].first);
        stream_manager::read_int(std::cin, queries[i].second);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int size, queries_count;
    std::vector<std::pair<int, int>> queries;

    read_data(size, queries_count, queries);

    std::string answer = solve(size, queries_count, queries);

    stream_manager::write_string(std::cout, answer);

    return 0;
}
