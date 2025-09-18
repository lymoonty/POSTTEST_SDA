#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Item
{
    string namaItem;
    int jumlah;
    string tipe;
    Item *next;
};

Item *buatItem(string nama, int jumlahAwal, string tipe)
{
    Item *newItem = new Item;
    newItem->namaItem = nama;
    newItem->jumlah = jumlahAwal;
    newItem->tipe = tipe;
    newItem->next = nullptr;
    return newItem;
}

string centerText(string text, int width)
{
    if (text.length() >= width)
    {
        return text;
    }
    int totalPadding = width - text.length();
    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;
    return string(leftPadding, ' ') + text + string(rightPadding, ' ');
}

void tampilkanMenu(string nama, string nim)
{
    const int lebar = 50;

    cout << "+" << string(lebar - 2, '-') << "+" << endl;
    cout << "|" << centerText("🎮 GAME INVENTORY MANAGEMENT 🎮", lebar - 2) << "|" << endl;

    string identitas = nama + " - " + nim;
    cout << "|" << centerText(identitas, lebar - 2) << "|" << endl;

    cout << "+" << string(lebar - 2, '-') << "+" << endl;
    cout << "| 1. Tambah Item Baru                         |" << endl;
    cout << "| 2. Sisipkan Item                            |" << endl;
    cout << "| 3. Hapus Item Terakhir                      |" << endl;
    cout << "| 4. Gunakan Item                             |" << endl;
    cout << "| 5. Tampilkan Inventory                      |" << endl;
    cout << "| 0. Keluar                                   |" << endl;
    cout << "+" << string(lebar - 2, '-') << "+" << endl;
    cout << "Pilih menu: ";
}

void tambahItem(Item *&head, string nama, int jumlahAwal, string tipe)
{
    Item *newItem = buatItem(nama, jumlahAwal, tipe);
    if (head == nullptr)
    {
        head = newItem;
    }
    else
    {
        Item *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newItem;
    }
    cout << "✅ Item \"" << nama << "\" berhasil ditambahkan dengan jumlah " << jumlahAwal << ".\n";
}

void sisipItem(Item *&head, string nama, int jumlahAwal, string tipe, int posisi)
{
    if (posisi <= 0)
    {
        cout << "❌ Posisi tidak valid!\n";
        return;
    }

    Item *newItem = buatItem(nama, jumlahAwal, tipe);

    if (posisi == 1)
    {
        newItem->next = head;
        head = newItem;
        cout << "✅ Item \"" << nama << "\" disisipkan di posisi 1.\n";
        return;
    }

    Item *temp = head;
    for (int i = 1; i < posisi - 1 && temp != nullptr; i++)
    {
        temp = temp->next;
    }

    if (temp == nullptr)
    {
        cout << "Posisi melebihi jumlah item yang ada!\n";
        delete newItem;
        return;
    }

    newItem->next = temp->next;
    temp->next = newItem;
    cout << "✅ Item \"" << nama << "\" disisipkan di posisi " << posisi << ".\n";
}

void hapusItemTerakhir(Item *&head)
{
    if (head == nullptr)
    {
        cout << "Inventory kosong, tidak ada item untuk dihapus.\n";
        return;
    }

    if (head->next == nullptr)
    {
        cout << "Item terakhir \"" << head->namaItem << "\" dihapus.\n";
        delete head;
        head = nullptr;
        return;
    }

    Item *temp = head;
    while (temp->next != nullptr && temp->next->next != nullptr)
    {
        temp = temp->next;
    }

    cout << "Item terakhir \"" << temp->next->namaItem << "\" dihapus.\n";
    delete temp->next;
    temp->next = nullptr;
}

void gunakanItem(Item *&head, string nama)
{
    if (head == nullptr)
    {
        cout << "❌ Inventory kosong, tidak ada item untuk digunakan.\n";
        return;
    }

    Item *current = head;
    Item *prev = nullptr;

    while (current != nullptr && current->namaItem != nama)
    {
        prev = current;
        current = current->next;
    }

    if (current == nullptr)
    {
        cout << "❌ Item \"" << nama << "\" tidak ditemukan.\n";
        return;
    }

    current->jumlah--;

    if (current->jumlah == 0)
    {
        cout << "✨ Item \"" << nama << "\" habis dan dihapus dari inventory.\n";

        if (prev == nullptr)
        {
            head = current->next;
        }
        else
        {
            prev->next = current->next;
        }

        delete current;
    }
    else
    {
        cout << "✨ Item \"" << nama << "\" digunakan. Sisa: " << current->jumlah << ".\n";
    }
}

void tampilkanInventory(Item *head)
{
    if (head == nullptr)
    {
        cout << "📦 Inventory anda kosong.\n";
        return;
    }

    cout << "\n=== 🎒 INVENTORY ANDA ===\n";
    Item *temp = head;
    int index = 1;
    while (temp != nullptr)
    {
        cout << index << ". " << temp->namaItem
             << " (Tipe: " << temp->tipe
             << ", Jumlah: " << temp->jumlah << ")\n";
        temp = temp->next;
        index++;
    }
    cout << "=========================\n";
}

void bersihkanInventory(Item *&head)
{
    while (head != nullptr)
    {
        Item *temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    string namaPengguna, nimPengguna;
    Item *inventory = nullptr;

    cout << "=== SELAMAT DATANG DI SISTEM INVENTORY GAME ===\n";
    cout << "Masukkan Nama Anda: ";
    getline(cin, namaPengguna);
    cout << "Masukkan NIM Anda: ";
    getline(cin, nimPengguna);

    int duaDigitTerakhir;
    if (nimPengguna.length() >= 2)
    {
        duaDigitTerakhir = stoi(nimPengguna.substr(nimPengguna.length() - 2));
    }
    else
    {
        duaDigitTerakhir = stoi(nimPengguna);
    }

    int digitTerakhir = nimPengguna.back() - '0';
    int posisiSisip = digitTerakhir + 1;

    cout << "\n🎮 Sistem berhasil dikonfigurasi!\n";
    cout << "📌 Jumlah awal setiap item baru: " << duaDigitTerakhir << "\n";
    cout << "📌 Posisi sisip item: " << posisiSisip << "\n";

    int pilihan;
    do
    {
        tampilkanMenu(namaPengguna, nimPengguna);

        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
        {
            string nama, tipe;
            cout << "Masukkan nama item: ";
            getline(cin, nama);
            cout << "Masukkan tipe item : ";
            getline(cin, tipe);
            tambahItem(inventory, nama, duaDigitTerakhir, tipe);
            break;
        }
        case 2:
        {
            string nama, tipe;
            cout << "Masukkan nama item: ";
            getline(cin, nama);
            cout << "Masukkan tipe item: ";
            getline(cin, tipe);
            sisipItem(inventory, nama, duaDigitTerakhir, tipe, posisiSisip);
            break;
        }
        case 3:
            hapusItemTerakhir(inventory);
            break;
        case 4:
        {
            string nama;
            cout << "Masukkan nama item yang ingin digunakan: ";
            getline(cin, nama);
            gunakanItem(inventory, nama);
            break;
        }
        case 5:
            tampilkanInventory(inventory);
            break;
        case 0:
            cout << "Terima kasih telah menggunakan sistem inventory game!\n";
            break;
        default:
            cout << "Pilihan tidak valid, silakan coba lagi.\n";
        }

        if (pilihan != 0)
        {
            cout << "\nTekan Enter untuk kembali ke menu...";
            cin.get();
        }
    } while (pilihan != 0);

    bersihkanInventory(inventory);
    return 0;
}