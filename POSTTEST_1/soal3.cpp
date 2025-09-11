#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa
{
    string nama;
    string nim;
    float ipk;
};

int main()
{
    Mahasiswa mhs[5];

    for (int i = 0; i < 5; i++)
    {
        cout << "\n--- Mahasiswa " << i + 1 << " ---" << endl;
        cout << "Nama: ";
        getline(cin, mhs[i].nama);
        cout << "NIM : ";
        getline(cin, mhs[i].nim);
        cout << "IPK : ";
        cin >> mhs[i].ipk;
        cin.ignore();
    }

    int idxTertinggi = 0;
    for (int i = 1; i < 5; i++)
    {
        if (mhs[i].ipk > mhs[idxTertinggi].ipk)
        {
            idxTertinggi = i;
        }
    }

    cout << "\n=== Mahasiswa dengan IPK Tertinggi ===" << endl;
    cout << "Nama: " << mhs[idxTertinggi].nama << endl;
    cout << "NIM : " << mhs[idxTertinggi].nim << endl;
    cout << "IPK : " << mhs[idxTertinggi].ipk << endl;

    return 0;
}