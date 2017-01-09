#include "main.h"

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

void print(std::ostream &_Ostr, node *root) {
    if (root->left) {
        print(_Ostr, root->left);
    }
    stream_manager::write_int(_Ostr, root->value);
    if (root->right) {
        print(_Ostr, root->right);
    }
}

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

void solve() {
    int size, queries;

    stream_manager::read_int(std::cin, size);
    stream_manager::read_int(std::cin, queries);

    node *root = build(size, 1, size);

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
