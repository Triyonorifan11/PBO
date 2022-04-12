#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

void mainMenu();
void pilihMenuPesan();

// simpan data menu
// class daftar menu
class Menu
{

private:
    string nama_menu;
    double harga;

public:
    Menu(string nama_menu, double harga)
    {
        this->nama_menu = nama_menu;
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
private:
    ifstream output;
    ofstream input;
    string fileName;
    string menu_pilih;
    string menu_update;
    double harga_pilih = 0;
    double harga_update = 0;
    double bayar;

public:
    Db(const char *fileName)
    {
        Db::fileName = fileName;
    }

    string getNamaMenu()
    {
        return menu_pilih;
    }

    string getUpdateNamaMenu()
    {
        return menu_update;
    }

    double getUpdateHargaMenu()
    {
        return harga_update;
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
        Db::input << "\t" << data.getharga();
        Db::input.close();
    }

    // save repository menu,harga untuk transaksi
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

    // Update database menu
    void updateDb(int indexUpdate)
    {
        cout << "update" << endl;
        Db::output.open(Db::fileName, ios::in);
        Db::input.open("temp.txt", ios::app);
        string updateNama;
        double updateHarga;

        int index = 1;

        while (!Db::output.eof())
        {
            Db::output >> updateNama;
            Db::output >> updateHarga;
            index++;
            if (indexUpdate == index - 1)
            {
                cout << "Masukan Nama menu update ";
                cin >> updateNama;
                cout << "Masukkan Harga menu update ";
                cin >> updateHarga;
                // this->menu_update = updateNama;
                // this->harga_update = updateHarga;
                // cout << index++ << updateNama << "\t" << updateHarga << endl;
            }
            // cout << index - 1 << updateNama << "\t" << updateHarga << endl;
            Db::input << "\n"
                      << updateNama;
            Db::input << "\t" << updateHarga;
            // this->menu_update = updateNama;
            // this->harga_update = updateHarga;
        }
        Db::output.close();
        Db::input.close();
        remove("Menu_restoran.txt");
        rename("temp.txt", "Menu_restoran.txt");
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
    void pesanMenu(int pilih, int porsi)
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
        if (pilih > index - 1)
        {
            cout << "nomer salah. input lagi" << endl;
            system("pause");
            pilihMenuPesan();
        }

        Db::output.close();
    }

    // fungsi total pesanan
    void totalpesanan()
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
            cout << index++ << " " << namaPilih << " " << fee << " x " << porsi << " = Rp" << total_fee << endl;
            bayar = bayar + total_fee;
        }
        cout << "\ntotal Pesanan = Rp" << bayar << endl;
        Db::bayar = bayar;
        Db::output.close();
    }

    void bayarpesanan()
    {

        double pesanan = this->bayar;
        double pajak = 0.01 * pesanan;
        double diskon = 0;
        double total_bayar = 0;
        double bayar_pelanggan = 0;
        double kembalian = 0;

        if (pesanan >= 100000.0)
        {
            diskon = 0.1 * pesanan;
        }

        total_bayar = pajak + pesanan - diskon;
        cout << "Total pesanan = Rp" << pesanan << endl;
        cout << "Pajak = Rp" << pajak << endl;
        cout << "Diskon = Rp" << diskon << endl;
        cout << "Total yang harus dibayar = Rp" << total_bayar << endl
             << endl;
        cout << "Bayar ? Rp ";
        cin >> bayar_pelanggan;
        kembalian = bayar_pelanggan - total_bayar;
        cout << "Kembali = Rp" << kembalian << endl;

        remove("RepoFee.txt");
    }
};

// class Transaksi:public Db{
//     public:
//     void bayar(){
//         cout <<"Bayar";
//     }
// };

// 1. fungsi input menu restaurant
void inputMenu()
{
    system("cls");
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
    cout << "\n\nData tersimpan !!\n"
         << endl;
    system("pause");
    mainMenu();
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

    dataBase.pesanMenu(pilihPesanan, porsi);
    repo_fee.save_fee(dataBase.getNamaMenu(), dataBase.getHargaMenu(), porsi);
    repo_fee.totalpesanan();

    cout << "tambah pesanan ? 1(yes)/2(no) ";
    cin >> tambah;

    switch (tambah)
    {
    case 1:
        pilihMenuPesan();
        break;

    case 2:
        repo_fee.bayarpesanan();
        break;
    default:
        break;
    }

    system("pause");
    mainMenu();
}

// https://stackoverflow.com/questions/34507989/update-and-delete-data-from-file-in-c
void update()
{
    Db dataBase = Db("Menu_restoran.txt");

    int update;
    system("cls");
    dataBase.showAll();
    cout << "\n\nPilih data yang akan di update = ";
    cin >> update;

    dataBase.updateDb(update);
    dataBase.showAll();
    // temp.save_update(dataBase.getUpdateNamaMenu(), dataBase.getUpdateHargaMenu());
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
    cout << "1. Input Menu" << endl;
    cout << "2. Lihat Menu" << endl;
    cout << "3. Pesan Menu" << endl;
    cout << "4. Update Menu" << endl;
    cout << "5. close" << endl;
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
        update();
    }
    else if (input == 5)
    {
        close();
    }
    else
    {
        cout << "salah input" << endl;
        system("pause");
        mainMenu();
    }
}

int main(int argc, char const *argv[])
{

    mainMenu();
    return 0;
}
