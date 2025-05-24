#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    struct Node {
        int data;
        int startInterval;
        int endInterval;
        Node* left;
        Node* right;

        Node(int start, int end) : startInterval(start), endInterval(end), data(0), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* constructTree(const vector<int>& arr, int start, int end) {
        if (start == end) {
            Node* leaf = new Node(start, end);
            leaf->data = arr[start];
            return leaf;
        }
        Node* node = new Node(start, end);
        int mid = (start + end) / 2;
        node->left = constructTree(arr, start, mid);
        node->right = constructTree(arr, mid + 1, end);
        node->data = node->left->data + node->right->data;
        return node;
    }
    void display(Node* node) {
        if (!node) return;
        string str = "";
        if (node->left)
            str += "L=[" + to_string(node->left->startInterval) + "-" + to_string(node->left->endInterval) + "](" + to_string(node->left->data) + ") ";
        else
            str += "L=NULL ";

        str += "ROOT=[" + to_string(node->startInterval) + "-" + to_string(node->endInterval) + "](" + to_string(node->data) + ") ";
        if (node->right)
            str += "R=[" + to_string(node->right->startInterval) + "-" + to_string(node->right->endInterval) + "](" + to_string(node->right->data) + ")";
        else
            str += "R=NULL";
        cout << str << endl;
        display(node->left);
        display(node->right);
    }

    int query(Node* node, int qsi, int qei) {
        if (!node) return 0;
        if (node->startInterval >= qsi && node->endInterval <= qei)
            return node->data;
        if (node->endInterval < qsi || node->startInterval > qei)
            return 0;
        return query(node->left, qsi, qei) + query(node->right, qsi, qei);
    }

    int update(Node* node, int index, int value) {
        if (node->startInterval == node->endInterval) {
            node->data = value;
            return node->data;
        }
        int mid = (node->startInterval + node->endInterval) / 2;
        if (index <= mid)
            update(node->left, index, value);
        else
            update(node->right, index, value);

        node->data = node->left->data + node->right->data;
        return node->data;
    }

public:
    SegmentTree(const vector<int>& arr) {
        root = constructTree(arr, 0, arr.size() - 1);
    }
    void display() {
        display(root);
    }
    int query(int left, int right) {
        return query(root, left, right);
    }
    void update(int index, int value) {
        update(root, index, value);
    }
};

int main() {
    vector<int> arr = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    SegmentTree tree(arr);

    cout << "Initial tree:\n";
    tree.display();

    cout << "\nQuery(0, 4): " << tree.query(0, 4) << endl;

    tree.update(4, 10);
    cout << "\nAfter updating index 4 to 10:\n";
    tree.display();

    cout << "\nQuery(0, 4): " << tree.query(0, 4) << endl;
    return 0;
}
