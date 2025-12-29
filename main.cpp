#include "bstNode.h"
#include "gameplay.h"
#include "database.h"

using namespace std;

int main () {
    sqlite3* databasePemain; // untuk menghubungkan ke database
    address root = NIL;
    int pilihanMenu;
    int radiusPandang = 5;
    SkillNode* skillRoot = nullptr;
    CharacterStats* playerStats = new CharacterStats();

    // inisialisasi database
    buatDatabase(databasePemain);

    // Inisialisasi ruangan awal (Perpustakaan)
    int tempX = 0, tempY = 0;
    pindahKeRuangan(root, tempX, tempY, 1);
    // NOTE: kita akan mengatur spawn pada mulaiBermain sehingga konstruktor di atas sekadar memastikan root terisi
    
    // Inisialisasi default skills
    initializeDefaultSkills(skillRoot);

    do {
        system("cls");
        cout << "=========================" << endl;
        cout << "      RENDERING GAME      " << endl;
        cout << "=========================" << endl;
        cout << "1. Mulai Bermain" << endl;
        cout << "2. Setting" << endl;
        cout << "3. Keluar" << endl;
        cout << "-------------------------" << endl;
        cout << "Pilih menu (1-3): ";
        cin >> pilihanMenu;
        switch (pilihanMenu)
        {
        case 1:
            menuProfil(profil);
            mulaiBermain(root, radiusPandang, profil, skillRoot, playerStats);
            break;
        case 2:
            lihatSetting(root, radiusPandang);
            break;
        case 3:
            cout << "Terimakasih telah bermain!" << endl;
            break;
        default:
            break;
        }
    } while (pilihanMenu != 3);
    return 0;
}