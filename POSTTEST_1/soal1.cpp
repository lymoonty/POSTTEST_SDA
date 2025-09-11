#include <iostream>
using namespace std;

void balikArray(int *array, int jumlah)
{
    int i = 0;
    int j = jumlah - 1;

    while (i < j)
    {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
        j--;
    }
}

int main()
{
    int arr[7];

    for (int i = 0; i < 7; i++)
    {
        arr[i] = (i + 1) * 3;
    }

    cout << "Sebelum dibalik: ";
    for (int i = 0; i < 7; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    balikArray(arr, 7);

    cout << "Setelah dibalik : ";
    for (int i = 0; i < 7; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}