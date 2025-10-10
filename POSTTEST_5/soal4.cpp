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

void postOrderTraversal(Node *root)
{
    // jika nodenya kosong maka berhenti
    if (root == nullptr)
        return;
    // ke kiri dulu terus ke kanan setelah itu cetak diri sendiri
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout << root->data << " ";
}

int main()
{
    Node *root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    cout << "Post-order traversal dari tree adalah: ";
    postOrderTraversal(root);
    cout << endl;
    return 0;
}