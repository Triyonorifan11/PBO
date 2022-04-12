#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

void mainMenu();

// simpan data menu
// class daftar menu
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
    double bayar;
    Db(const char *fileName)
    {
        Db::fileName = fileName;
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

    void save_fee(string namapilih, double hargapilih, int porsi)
    {
        Db::input.open(Db::fileName, ios::app);
        Db::input << "\n"
                  << namapilih;
        Db::input << " " << hargapilih;
        Db::input << " " << porsi;
        Db::input << " " << hargapilih * porsi;
        // Db::input << Db::harga_pilih;
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
                Db::menu_pilih = pilihNama;
                Db::harga_pilih = pilihHarga;
            }
        }

        Db::output.close();
        // cout << "\n\nHarga pilih : " << tampilHarga << endl;
    }

    void bayarpesanan()
    {
        Db::output.open(Db::fileName, ios::in);
        string namaPilih;
        double total_fee = 0, bayar, fee;
        int porsi;
        int index = 1;
        while (!Db::output.eof())
        {
            Db::output >> namaPilih;
            Db::output >> fee;
            Db::output >> porsi;
            Db::output >> total_fee;
            cout << index++ << " " << namaPilih << " " << fee << " x " << porsi << " = " << total_fee << endl;
            bayar = bayar + total_fee;
        }
        cout << "\ntotal bayar = " << bayar << endl;
        Db::bayar = bayar;

        // double total = Db::harga_pilih * porsi;
        // cout << "Harga yg harus dibayar = " << total << endl;
    }
};

class Transaksi : public Db
{
public:
    void bayarPelanggan()
    {
        cout << "Total bayar = " << Db::bayar << endl;
    }
};

// 1. fungsi input menu restaurant
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
    Db repo_fee = Db("RepoFee.txt");

    int pilihPesanan, porsi, tambah;
    system("cls");
    dataBase.showAll();
    cout << "\n\nPilih menu diatas : ";
    cin >> pilihPesanan;
    cout << "Banyak porsi : ";
    cin >> porsi;

    dataBase.pesanMenu(pilihPesanan);
    repo_fee.save_fee(dataBase.getNamaMenu(), dataBase.getHargaMenu(), porsi);
    repo_fee.bayarpesanan();

    cout << "tambah pesanan ? 1(yes)/2(no) ";
    cin >> tambah;

    switch (tambah)
    {
    case 1:
        pilihMenuPesan();
        break;

    case 2:
        bayar();
        break;
    default:
        break;
    }

    system("pause");
    mainMenu();
}

void bayar()
{
    Transaksi Bayarmenu;
    Bayarmenu.bayarPelanggan();
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
        system("pause");
        mainMenu();
    }
}

int main(int argc, char const *argv[])
{

    mainMenu();
    return 0;
}
