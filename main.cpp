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

void stream_manager::write_string(std::ostream &_Ostr, std::string &data) {
    _Ostr << data << "\n";
}




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

std::string treap::get_description(std::string separator) {
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
treap::node::node(int value) : value(value) {}

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
    std::vector<int> &values
) {
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

std::string solve(
    const int size,
    const int queries_count,
    std::vector<std::pair<int, int>> &queries
) {
    treap *root = new treap(size);

    for (int i = 0; i < queries_count; ++i) {
        root->reorder(queries[i].first, queries[i].second);
    }

    return root->get_description();
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
