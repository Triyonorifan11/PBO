#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// simpan data menu
class Db
{
public:
    ifstream input;
    ofstream output;
    string fileName;

    Db(const char *fileName)
    {
        Db::fileName = fileName;
    }
};

class Menu
{
public:
    string Nama_menu;
    double harga;
};

int main(int argc, char const *argv[])
{
    Db dataBase = Db("Manu_restoran.txt");
    return 0;
}
