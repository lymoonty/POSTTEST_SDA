#include <iostream>
using namespace std;
// Struktur Node untuk Binary Tree
struct Node
{
    int data;
    Node *left;
    Node *right;

    // Constructor
    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Fungsi insert untuk membangun tree
Node *insert(Node *root, int val)
{
    if (root == nullptr)
    {
        return new Node(val);
    }
    if (val < root->data)
    {
        root->left = insert(root->left, val);
    }
    else if (val > root->data)
    {
        root->right = insert(root->right, val);
    }
    return root;
}

int findMaxValue(Node *root)
{
    // jika tree nya kosong maka kembalikan nila -1
    if (root == nullptr)
    {
        return -1;
    }
    // nilai yang terbesar ada di node paling kanan
    while (root->right != nullptr)
    {
        root = root->right;
    }
    return root->data;
}

int main()
{
    Node *root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 80);

    cout << "Nilai terbesar dalam tree adalah: " << findMaxValue(root) << endl;
    return 0;
}