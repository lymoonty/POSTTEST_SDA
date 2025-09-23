#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Item
{
    string nama_item;
    int jumlah;
    string tipe;
    Item *next;
    Item *prev;
};

Item *buatItem(string nama, int jumlah_awal, string tipe)
{
    Item *item_baru = new Item;
    item_baru->nama_item = nama;
    item_baru->jumlah = jumlah_awal;
    item_baru->tipe = tipe;
    item_baru->next = nullptr;
    item_baru->prev = nullptr;
    return item_baru;
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

void tampilan_menu(string nama, string nim)
{
    const int lebar = 50;

    cout << "+" << string(lebar - 2, '-') << "+" << endl;
    cout << "|" << centerText("🎮 GAME INVENTORY MANAGEMENT 🎮", lebar - 2) << "|" << endl;

    string identitas = nama + " - " + nim;
    cout << "|" << centerText(identitas, lebar - 2) << "|" << endl;

    cout << "+" << string(lebar - 2, '-') << "+" << endl;
    cout << "| " << left << setw(47) << "1. Tambah Item Baru" << " |" << endl;
    cout << "| " << setw(47) << "2. Sisipkan Item" << " |" << endl;
    cout << "| " << setw(47) << "3. Hapus Item Terakhir" << " |" << endl;
    cout << "| " << setw(47) << "4. Gunakan Item" << " |" << endl;
    cout << "| " << setw(47) << "5. Tampilkan Inventory" << " |" << endl;
    cout << "| " << setw(47) << "6. Tampilkan Inventory (Reverse)" << " |" << endl;
    cout << "| " << setw(47) << "7. Tampilkan Detail Item by ID" << " |" << endl;
    cout << "| " << setw(47) << "0. Keluar" << " |" << endl;
    cout << "+" << string(lebar - 2, '-') << "+" << endl;
    cout << "Pilih menu: ";
}

void tambahItem(Item *&head, string nama, int jumlah_awal, string tipe)
{
    Item *item_baru = buatItem(nama, jumlah_awal, tipe);
    if (head == nullptr)
    {
        head = item_baru;
    }
    else
    {
        Item *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = item_baru;
        item_baru->prev = temp;
    }
    cout << "✅ Item \"" << nama << "\" berhasil ditambahkan dengan jumlah " << jumlah_awal << ".\n";
}

void sisipItem(Item *&head, string nama, int jumlah_awal, string tipe, int posisi)
{
    if (posisi <= 0)
    {
        cout << "❌ Posisi tidak valid!\n";
        return;
    }

    Item *item_baru = buatItem(nama, jumlah_awal, tipe);

    if (posisi == 1)
    {
        item_baru->next = head;
        if (head != nullptr)
            head->prev = item_baru;
        head = item_baru;
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
        cout << "❌ Posisi melebihi jumlah item yang ada!\n";
        delete item_baru;
        return;
    }

    item_baru->next = temp->next;
    item_baru->prev = temp;

    if (temp->next != nullptr)
        temp->next->prev = item_baru;

    temp->next = item_baru;
    cout << "✅ Item \"" << nama << "\" disisipkan di posisi " << posisi << ".\n";
}

void hapusItemTerakhir(Item *&head)
{
    if (head == nullptr)
    {
        cout << "❌ Inventory kosong, tidak ada item untuk dihapus.\n";
        return;
    }

    if (head->next == nullptr)
    {
        cout << "🗑️ Item terakhir \"" << head->nama_item << "\" dihapus.\n";
        delete head;
        head = nullptr;
        return;
    }

    Item *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    cout << "🗑️ Item terakhir \"" << temp->nama_item << "\" dihapus.\n";
    temp->prev->next = nullptr;
    delete temp;
}

void gunakanItem(Item *&head, string nama)
{
    if (head == nullptr)
    {
        cout << "❌ Inventory kosong, tidak ada item untuk digunakan.\n";
        return;
    }

    Item *current = head;

    while (current != nullptr && current->nama_item != nama)
    {
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

        if (current == head)
        {
            head = current->next;
            if (head != nullptr)
                head->prev = nullptr;
        }
        else
        {
            current->prev->next = current->next;
            if (current->next != nullptr)
                current->next->prev = current->prev;
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

    cout << "\n=== 🎒 INVENTORY ANDA (mengurutkan dari belakang ke depan) ===\n";
    cout << left << setw(5) << "ID"
         << setw(20) << "Nama Item"
         << setw(15) << "Tipe"
         << setw(10) << "Jumlah" << endl;
    cout << string(55, '-') << endl;

    Item *temp = head;
    int index = 1;
    while (temp != nullptr)
    {
        cout << left << setw(5) << index
             << setw(20) << temp->nama_item
             << setw(15) << temp->tipe
             << setw(10) << temp->jumlah << endl;
        temp = temp->next;
        index++;
    }
    cout << string(55, '=') << endl;
}

void tampilkanInventoryReverse(Item *head)
{
    if (head == nullptr)
    {
        cout << "📦 Inventory anda kosong.\n";
        return;
    }

    Item *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    cout << "\n=== 🎒 INVENTORY ANDA (mengurutkan dari belakang ke depan) ===\n";
    cout << left << setw(5) << "ID"
         << setw(20) << "Nama Item"
         << setw(15) << "Tipe"
         << setw(10) << "Jumlah" << endl;
    cout << string(55, '-') << endl;

    int index = 1;
    while (temp != nullptr)
    {
        cout << left << setw(5) << index
             << setw(20) << temp->nama_item
             << setw(15) << temp->tipe
             << setw(10) << temp->jumlah << endl;
        temp = temp->prev;
        index++;
    }
    cout << string(55, '=') << endl;
}

void tampilkanDetailByID(Item *head, int id)
{
    if (head == nullptr)
    {
        cout << "❌ Inventory kosong.\n";
        return;
    }

    Item *temp = head;
    int index = 1;
    while (temp != nullptr && index < id)
    {
        temp = temp->next;
        index++;
    }

    if (temp == nullptr)
    {
        cout << "❌ Item dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    cout << "\n=== 📄 DETAIL ITEM (ID: " << id << ") ===\n";
    cout << left << setw(15) << "Nama Item" << ": " << temp->nama_item << endl;
    cout << setw(15) << "Tipe" << ": " << temp->tipe << endl;
    cout << setw(15) << "Jumlah" << ": " << temp->jumlah << endl;
    cout << string(40, '=') << endl;
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
        tampilan_menu(namaPengguna, nimPengguna);

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
        case 6:
            tampilkanInventoryReverse(inventory);
            break;
        case 7:
        {
            int id;
            cout << "Masukkan ID item (nomor urut): ";
            cin >> id;
            cin.ignore();
            tampilkanDetailByID(inventory, id);
            break;
        }
        case 0:
            cout << "Terima kasih telah menggunakan sistem inventory game!\n";
            break;
        default:
            cout << "❌ Pilihan tidak valid, silakan coba lagi.\n";
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