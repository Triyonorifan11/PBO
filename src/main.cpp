#include <iostream>
#include <string>
#include <fstream>

using namespace std;

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

class Db
{
public:
    ifstream output;
    ofstream input;
    string fileName;

    Db(const char *fileName)
    {
        Db::fileName = fileName;
    }

    // fungsi menyimpan data
    void save(Menu data)
    {
        cout << data.nama_menu << endl;
        cout << data.harga << endl;

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

        while (!Db::output.eof())
        {
            Db::output >> tampilNama;
            Db::output >> tampilHarga;
            cout << index++ << "\t" << tampilNama << "\t" << tampilHarga << endl;
        }

        Db::output.close();
    }
};

void inputMenu()
{
    Db dataBase = Db("Manu_restoran.txt");
    string namaMenu;
    double harga;
    cout << "Input Menu" << endl;
    cout << "Nama : ";
    cin >> namaMenu;
    cout << "Harga : ";
    cin >> harga;

    // save data
    Menu menu1 = Menu(namaMenu, harga);
    dataBase.save(menu1);
}

// menampilkan daftar menu
void tampilMenu()
{
    Db dataBase = Db("Manu_restoran.txt");
    // tampilkan data
    dataBase.showAll();
}

void close()
{
    cout << "terima kasih" << endl;
}

void mainMenu()
{
    int input;
    cout << " silahkan pilih menu" << endl;
    cout << "1. Input menu" << endl;
    cout << "2. Lihat menu" << endl;
    cout << "3. close" << endl;
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
