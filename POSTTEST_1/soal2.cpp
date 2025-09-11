#include <iostream>
using namespace std;

int main()
{
    int matrix[3][3] = {
        {2, 4, 6},
        {8, 5, 3},
        {7, 1, 9}};

    int jumlahUtama = 0;
    int jumlahSekunder = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
            {
                jumlahUtama += matrix[i][j];
            }
            if (i + j == 2)
            {
                jumlahSekunder += matrix[i][j];
            }
        }
    }

    cout << "Matriks 3x3:\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nJumlah diagonal utama: " << jumlahUtama << endl;
    cout << "Jumlah diagonal sekunder: " << jumlahSekunder << endl;
    cout << "Total (utama + sekunder): " << jumlahUtama + jumlahSekunder << endl;

    return 0;
}