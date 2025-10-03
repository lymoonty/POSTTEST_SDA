#include <iostream>
#include <string>
using namespace std;

struct Node
{
    char data;
    Node *next;
};

// fungsi push
void push(Node *&top, char data)
{
    Node *newNode = new Node{data, top};
    top = newNode;
}

// Fungsi pop
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

bool areBracketsBalanced(string expr)
{
    Node *stackTop = nullptr;

    // 1. Loop setiap karakter dalam `expr`.
    for (int i = 0; i < expr.length(); i++)
    {
        char c = expr[i];

        // 2. Jika karakter adalah kurung buka '(', '{', '[', push ke stack.
        if (c == '(' || c == '{' || c == '[')
        {
            push(stackTop, c);
        }
        // 3. Jika karakter adalah kurung tutup ')', '}', ']', cek:
        else if (c == ')' || c == '}' || c == ']')
        {
            //    a. Apakah stack kosong? Jika ya, return false.
            if (stackTop == nullptr)
            {
                return false;
            }
            //    b. Pop stack, lalu cek apakah kurung tutup cocok dengan kurung buka. Jika tidak, return false.
            char openBracket = pop(stackTop);

            // mengecek apakah pasangan kurungnya cocok
            if ((c == ')' && openBracket != '(') ||
                (c == '}' && openBracket != '{') ||
                (c == ']' && openBracket != '['))
            {
                return false;
            }
        }
    }
    return stackTop == nullptr;
}
int main()
{
    string expr1 = "{[()]}";
    cout << expr1 << " -> " << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") << endl;
    string expr2 = "{[(])}";
    cout << expr2 << " -> " << (areBracketsBalanced(expr2) ? "Seimbang" : "Tidak Seimbang") << endl;

    return 0;
}
