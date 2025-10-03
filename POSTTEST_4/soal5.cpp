#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node *prev;
};

void exchangeHeadAndTail(Node *&head_ref)
{
    // Hanya berjalan jika ada 2 node atau lebih
    if (head_ref == nullptr || head_ref->next == head_ref)
    {
        return;
    }

    Node *head = head_ref;
    Node *tail = head_ref->prev; // Tail adalah prev dari head

    // Simpan neighbor ( yaitu head_next dan tail_prev)
    Node *head_next = head->next;
    Node *tail_prev = tail->prev;
    // Jika hanya 2 node
    if (head_next == tail)
    {
        // Cukup tukar peran: tail jadi head
        tail->next = head;
        tail->prev = head;
        head->next = tail;
        head->prev = tail;
        head_ref = tail;
        return;
    }

    // ini untuk node yang lebih dari 3:
    // Sambungkan tail_prev ke head
    tail_prev->next = head;
    head->prev = tail_prev;

    // Sambungkan tail ke head_next
    tail->next = head_next;
    head_next->prev = tail;
    tail->prev = head;
    head->next = tail;

    // Update head_ref
    head_ref = tail;
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

void insertEnd(Node *&head_ref, int data)
{
    Node *newNode = new Node{data, nullptr, nullptr};

    if (head_ref == nullptr)
    {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    Node *tail = head_ref->prev;
    newNode->next = head_ref;
    newNode->prev = tail;
    head_ref->prev = newNode;
    tail->next = newNode;
}

int main()
{
    Node *head = nullptr;

    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);

    cout << "List sebelum exchange: ";
    printList(head);

    exchangeHeadAndTail(head);

    cout << "List setelah exchange head dan tail: ";
    printList(head);

    return 0;
}
