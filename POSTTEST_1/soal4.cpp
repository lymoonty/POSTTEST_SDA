#include <iostream>
using namespace std;

void tukar(int **a, int **b)
{
    int temp = **a;
    **a = **b;
    **b = temp;
}

int main()
{
    int x, y;
    int *ptrX, *ptrY;

    cout << "Masukkan nilai pertama: ";
    cin >> x;
    cout << "Masukkan nilai kedua  : ";
    cin >> y;

    ptrX = &x;
    ptrY = &y;

    cout << "\n--- Sebelum ditukar ---" << endl;
    cout << "Nilai pertama: " << x << endl;
    cout << "Nilai kedua  : " << y << endl;

    tukar(&ptrX, &ptrY);

    cout << "\n--- Setelah ditukar ---" << endl;
    cout << "Nilai pertama: " << x << endl;
    cout << "Nilai kedua  : " << y << endl;

    return 0;
}