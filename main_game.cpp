#include "bstNode.h"
#include "gameplay.h"
#include "database.h"
#include "SkillTree/Skilltree.h"
#include "SkillTree/Character.h"

using namespace std;


int main () {
    sqlite3* databasePemain; // untuk menghubungkan ke database
    sqlite3* databaseDeveloper; // untuk menghubungkan ke database
    address root = NIL;
    SkillNode* skillRoot = nullptr; // Skill tree root
    int pilihanMenu;
    int radiusPandang = 5;

    
    // inisialisasi database
    buatDatabasePemain(databasePemain);
    buatDatabaseDeveloper(databaseDeveloper);
    
    // Inisialisasi skill tree
    initializeSkillTree(skillRoot);
    
    // Inisialisasi ruangan awal (Perpustakaan)
    pindahKeRuangan(root, /*playerX*/ *(new int(0)), /*playerY*/ *(new int(0)), 1, *new int(0));
    // NOTE: kita akan mengatur spawn pada mulaiBermain sehingga konstruktor di atas sekadar memastikan root terisi
    
    do {
        int extProfil = 0; // indikator exit di menu profil pas belom punya username
        system("cls");
        cout << setfill('=') << setw(50) << " " << endl; setfill(' ');
        cout << "\tTHE GAME: BIZZARE NIGHT AT CAMPUS      " << endl;
        cout << setfill('=') << setw(50) << " " << endl; setfill(' ');
        cout << "1. Mulai Bermain" << endl;
        cout << "2. Setting" << endl;
        cout << "3. Keluar" << endl;
        cout << setfill('-') << setw(50) << " " << endl; setfill(' ');
        cout << "Pilih menu (1-3): ";
        cin >> pilihanMenu;
        switch (pilihanMenu)
        {
        case 1:
            extProfil = menuProfil(profil);
            if (extProfil != 0) mulaiBermain(root, radiusPandang, profil, false, skillRoot);
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