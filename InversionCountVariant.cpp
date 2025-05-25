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

    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> arr(n);
        for(int i=0;i<n;i++){cin>>arr[i];arr[i]--;}
        vector<int> jar(n,0);
        SegmentTree tree(jar);
        long long count=0;
        for(int i=0;i<n;i++){
            count+=tree.query(arr[i]+1,n-1);
            int q=tree.query(arr[i],arr[i]);
            tree.update(arr[i],q+1);
        }
        sort(arr.begin(),arr.end());
        int rec=1;
        for(int i=1;i<n;i++){
            if(arr[i]!=arr[i-1]){
                
                count+=1LL*rec*(rec-1)/2;
                rec=1;
            }
            else rec++;
        }
        count+=1LL*rec*(rec-1)/2;
        cout<<count<<endl;
    }
    
}
