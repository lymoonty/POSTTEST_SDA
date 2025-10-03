#include <iostream>
#include <string>
using namespace std;

struct Node
{
    char data;
    Node *next;
};

// ini itu fungsi untuk masukin karakter ke puncak stack (push)
void push(Node *&top, char data)
{
    Node *newNode = new Node{data, top};
    top = newNode;
}

// ini fungsi untuk ambil karakter dari puncak stack (pop)
char pop(Node *&top)
{
    if (top == nullptr)
        return '\0';
    Node *temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

// ini itu fungsi utama untuk ngebalik string menggunakan stack
string reverseString(string s)
{
    Node *stackTop = nullptr;
    string reversed = "";

    // karena stacknya bersifat LIFO maka karakter terakhir akan berada dipuncak
    for (int i = 0; i < s.length(); i++)
    {
        push(stackTop, s[i]);
    }
    // Karakter yang keluar pertama adalah yang terakhir dimasukkan (urutan terbalik).
    while (stackTop != nullptr)
    {
        reversed += pop(stackTop);
    }

    return reversed; // mengembalikan string yang sudah terbalik
}

// ini program utamanya
int main()
{
    string text = "Struktur Data";
    cout << "Teks asli: " << text << endl;
    cout << "Teks terbalik: " << reverseString(text) << endl; // ini outputnyaaa
    return 0;
}
