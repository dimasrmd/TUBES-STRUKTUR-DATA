#include "bstNode.h"
#include "gameplay.h"
#include "database.h"

using namespace std;


int main () {
    sqlite3* databasePemain; // untuk menghubungkan ke database
    sqlite3* databaseDeveloper; // untuk menghubungkan ke database
    address root = NIL;
    int pilihanMenu;
    int radiusPandang = 5;

    
    // inisialisasi database
    buatDatabasePemain(databasePemain);
    buatDatabaseDeveloper(databaseDeveloper);
    
    // Inisialisasi ruangan awal (Perpustakaan)
    pindahKeRuangan(root, /*playerX*/ *(new int(0)), /*playerY*/ *(new int(0)), 1, *new int(0));
    // NOTE: kita akan mengatur spawn pada mulaiBermain sehingga konstruktor di atas sekadar memastikan root terisi
    
    system("cls");
    cout << setfill('=') << setw(40) << "" << endl << setfill(' ');
    cout << "\tDEVELOPER MODE - LOGIN" << endl;
    cout << setfill('=') << setw(40) << "" << endl << setfill(' ');
    
    if (!authDeveloper()) {
        cout << "\nLogin gagal! tekan untuk lanjut...";
        _getch();
        return 0;
    }

    do {
        system("cls");
        cout << setfill('=') << setw(32) << "" << endl << setfill(' ');
        cout << "\t MENU DEVELOPER" << endl;
        cout << setfill('=') << setw(32) << "" << endl << setfill(' ');
        cout << "1. Menu Developer (input objek)" << endl;
        cout << "2. Test gameplay" << endl;
        cout << "3. Lihat Setting" << endl;
        cout << "4. Keluar" << endl;
        cout << setfill('-') << setw(32) << "" << endl << setfill(' ');
        cout << "Pilih menu: ";
        cin >> pilihanMenu;
        switch (pilihanMenu) {
            case 1:
                menuDeveloper(root);
                break;
            case 2:
                mulaiBermain(root, radiusPandang, profil, true);
                break;
            case 3:
                lihatSetting(root, radiusPandang);
                break;
            case 4:
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                _getch();
                break;
        }
    } while (pilihanMenu != 4);
}