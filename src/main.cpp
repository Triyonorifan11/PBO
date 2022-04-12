#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

void mainMenu();

// simpan data menu

class Menu
{
public:
    string nama_menu;
    double harga;

    Menu(string nama_menu, double harga)
    {
        Menu::nama_menu = nama_menu;
        Menu::harga = harga;
    }

    string getMenu()
    {
        return "\n" + nama_menu;
    }

    double getharga()
    {
        return harga;
    }
};

// class database untuk menyimpan data Menu ke file txt
class Db
{
public:
    ifstream output;
    ofstream input;
    string fileName;

    string menu_pilih;
    double harga_pilih = 0;

    Db(const char *fileName)
    {
        Db::fileName = fileName;
    }

    Db(string feeNama, double feeHarga)
    {
        Db::menu_pilih = feeNama;
        Db::harga_pilih = feeHarga;
    }

    string getNamaMenu()
    {
        return menu_pilih;
    }
    double getHargaMenu()
    {
        return harga_pilih;
    }

    // fungsi menyimpan data
    void save(Menu data)
    {
        Db::input.open(Db::fileName, ios::app);
        Db::input << data.getMenu();
        Db::input << " " << data.getharga();
        Db::input.close();
    }

    // fungsi tampilkan data
    void showAll()
    {
        Db::output.open(Db::fileName, ios::in);
        string tampilNama;
        double tampilHarga;
        int index = 1;

        cout << "No "
             << "\t"
             << "Daftar Menu"
             << "\t"
             << "Daftar Harga" << endl;
        while (!Db::output.eof())
        {
            Db::output >> tampilNama;
            Db::output >> tampilHarga;

            cout << index++ << "\t" << tampilNama << "\t" << tampilHarga << endl;
        }

        cout << "jumlah Menu: " << index - 1 << endl;

        Db::output.close();
    }

    // untuk pilih menu pesanan dan ambil harga pesanan
    void pesanMenu(int pilih)
    {
        Db::output.open(Db::fileName, ios::in);
        string pilihNama;
        double pilihHarga;

        int index = 1;

        while (!Db::output.eof())
        {
            Db::output >> pilihNama;
            Db::output >> pilihHarga;
            index++;
            if (pilih == index - 1)
            {
                cout << pilih << endl;
                cout << "Menu : " << pilihNama << endl;
                cout << "Harga : " << pilihHarga << endl;
                // Db send = Db(pilihNama, pilihHarga);
                Db::menu_pilih = pilihNama;
                Db::harga_pilih = pilihHarga;
            }
        }

        Db::output.close();
        // cout << "\n\nHarga pilih : " << tampilHarga << endl;
    }
};

// class tranksasi pembayaran
class Db_fee
{
public:
    double harga_menu;
    string nama_menu;
    double total_bayar;
    double bayar;
    string db_feeName;
    ifstream output_fee;
    ofstream input_fee;

    Db_fee(const char *filename)
    {
        Db_fee::db_feeName = filename;
    }

    void save_fee(Db repo_fee)
    {
        Db_fee::input_fee.open(Db_fee::db_feeName, ios::in);
        Db_fee::input_fee << repo_fee.getNamaMenu();
        Db_fee::input_fee << repo_fee.getHargaMenu();
        Db_fee::input_fee.close();
    }
};

// 1. fungsi input menu baru
void inputMenu()
{
    Db dataBase = Db("Menu_restoran.txt");
    string namaMenu;
    double harga;
    cout << "Catatan !! jika ada spasi ganti _" << endl;
    cout << "\nInput Menu" << endl;
    cout << "Nama : ";
    cin >> namaMenu;
    cout << "Harga : ";
    cin >> harga;

    Menu menu1 = Menu(namaMenu, harga);
    // save data
    dataBase.save(menu1);
}

// 2. menampilkan daftar menu
void tampilMenu()
{
    system("cls");
    Db dataBase = Db("Menu_restoran.txt");
    // tampilkan data
    dataBase.showAll();
    system("Pause");
    mainMenu();
}

// 3. memilih menu untuk pemesanan
void pilihMenuPesan()
{
    Db dataBase = Db("Menu_restoran.txt");
    Db_fee fee = Db_fee("fee.txt");
    int pilihPesanan;
    system("cls");
    dataBase.showAll();
    cout << "\n\nPilih menu diatas : ";
    cin >> pilihPesanan;

    dataBase.pesanMenu(pilihPesanan);
    cout << "Menu pilih = " << dataBase.getNamaMenu() << endl;
    cout << "Harga dipilih = " << dataBase.getHargaMenu() << endl;
    system("pause");
    mainMenu();
}

// tutup Aplikasi
void close()
{
    system("cls");
    cout << "terima kasih" << endl;
}

// Main menu
void mainMenu()
{
    system("cls");
    int input;
    cout << " silahkan pilih menu" << endl;
    cout << "1. Input menu" << endl;
    cout << "2. Lihat menu" << endl;
    cout << "3. Pesan Menu" << endl;
    cout << "4. close" << endl;
    cout << "Pilih: ";
    cin >> input;

    if (input == 1)
    {
        inputMenu();
    }
    else if (input == 2)
    {
        tampilMenu();
    }
    else if (input == 3)
    {
        pilihMenuPesan();
    }
    else if (input == 4)
    {
        close();
    }
    else
    {
        cout << "salah input";
        mainMenu();
    }
}

int main(int argc, char const *argv[])
{

    mainMenu();
    return 0;
}
