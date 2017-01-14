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
        int value;

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
int main();


treap::treap(const int size) {
    std::vector<int> values(size);
    for (int i = 0; i < size; ++i) {
        values[i] = i + 1;
    }
    root = build(1, size, values);
}

treap::treap(std::vector<int> &values) {
    root = build(1, values.size(), values);
}

void treap::reorder(const int left, const int right) {
    root = reorder(root, left, right);
}

std::string treap::get_description(const std::string separator) {
    // return get_description(root);

    std::vector<int> elements = get_elements();
    if (elements.size() == 0) {
        return "";
    }
    std::string description = std::to_string(elements[0]);
    for (int i = 1; i < elements.size(); ++i) {
        description += separator + std::to_string(elements[i]);
    }
    return description;
}

treap::node::node() {}
treap::node::node(const int value) : value(value) {}

int treap::size(node *root) {
    return root ? root->size : 0;
}

void treap::update(node *root) {
    if (!root) {
        return;
    }
    root->size = 1 + size(root->left) + size(root->right);
}

void treap::merge(node *left, node *right, node *&result) {
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

void treap::split(node *root, node *&left, node *&right, const int position) {
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

void treap::insert(node *&root, node *item, const int position) {
    node *before, *after;
    split(root, before, after, position);
    merge(before, item, before);
    merge(before, after, root);
}

void treap::get_elements(node *root, std::vector<int> &elements) {
    if (root->left) {
        get_elements(root->left, elements);
    }
    elements.push_back(root->value);
    if (root->right) {
        get_elements(root->right, elements);
    }
}

std::vector<int> treap::get_elements() {
    std::vector<int> result;
    if (root) {
        get_elements(root, result);
    }
    return result;
}

std::string treap::get_description(node *root) {
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

treap::node* treap::reorder(node *root, const int left, const int right) {
    node *before_left, *after_left;
    split(root, before_left, after_left, left - 1);

    node *between_left_and_right, *after_right;
    split(after_left, between_left_and_right, after_right, right - left + 1);

    node *temp, *result;
    merge(between_left_and_right, before_left, temp);
    merge(temp, after_right, result);

    return result;
}

treap::node* treap::build(
    const int left,
    const int right,
    std::vector<int> &values) {

    const int index = (left + right + 1) / 2;
    if (index > values.size() || index <= 0 || left > right) {
        return nullptr;
    }
    node *root = new node(values[index - 1]);
    root->left = build(left, index - 1, values);
    root->right = build(index + 1, right, values);
    update(root);
    return root;
}


query::query() : left_position(0), right_position(0) {}

query::query(const int left, const int right) 
    : left_position(left), 
      right_position(right) {}


std::vector<int> solve(
    const int size,
    const int queries_count,
    std::vector<query> &queries) {

    treap *root = new treap(size);

    for (int i = 0; i < queries_count; ++i) {
        root->reorder(queries[i].left_position, queries[i].right_position);
    }

    return root->get_elements();
}

void read_data(
    std::istream &_Istr,
    int &size,
    int &queries_count,
    std::vector<query> &queries) {

    _Istr >> size;
    _Istr >> queries_count;

    queries.resize(queries_count);

    for (int i = 0; i < queries_count; ++i) {
        _Istr >> queries[i].left_position;
        _Istr >> queries[i].right_position;
    }
}

void write_data(
    std::ostream &_Ostr,
    std::vector<int> &data) {

    for (int i = 0; i < data.size(); ++i) {
        _Ostr << data[i] << " ";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int size, queries_count;
    std::vector<query> queries;

    read_data(std::cin, size, queries_count, queries);

    std::vector<int> result = solve(size, queries_count, queries);

    write_data(std::cout, result);

    return 0;
}
