#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node *prev;
};

void sortedInsert(Node *&head_ref, int data)
{
    Node *newNode = new Node{data, nullptr, nullptr};

    // Kasus 1: List masih kosong
    if (head_ref == nullptr)
    {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    // Kasus 2: Data baru lebih kecil dari head (sisipkan di awal)
    // 1. Jika data < head_ref->data, sisipkan sebelum head dan update head_ref
    if (data < head_ref->data)
    {
        // node baru jadi head
        Node *tail = head_ref->prev; // karena circular, head->prev adalah tail
        newNode->next = head_ref;
        newNode->prev = tail;
        tail->next = newNode;
        head_ref->prev = newNode;
        head_ref = newNode; // update head_ref ke node baru
        return;
    }

    // Kasus 3: Cari posisi yang tepat (tengah/akhir)
    Node *current = head_ref;
    // Loop sampai menemukan node setelah current yang >= data
    while (current->next != head_ref && current->next->data < data)
    {
        current = current->next;
    }
    // Sekarang, sisipkan newNode SETELAH current
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
}

void printList(Node *head_ref)
{
    if (head_ref == nullptr)
    {
        cout << "List kosong" << endl;
        return;
    }

    Node *current = head_ref;
    do
    {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

int main()
{
    Node *head = nullptr;

    // Test sorted insert
    sortedInsert(head, 30);
    sortedInsert(head, 10);
    sortedInsert(head, 40);
    sortedInsert(head, 20);

    cout << "Circular Doubly Linked List (sorted): ";
    printList(head);

    return 0;
}
