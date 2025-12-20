#include "bstNode.h"
#include "gameplay.h"
#include "Skilltree.h"
#include "Utilitas.h" 
#include "pesanObjek.h"

using namespace std;

void initDiscoSkills(SkillNode*& root) {
    // === 1. INTELLECT ===
    // Parent: Logic
    Skill s1; s1.namaSkill = "Logic"; s1.kategori = "INTELLECT"; s1.level = 1; s1.effects = nullptr;
    insertSkill(root, s1);
    
    // Cari Parent-nya, lalu pasang Child-nya
    SkillNode* logic = searchSkill(root, "Logic");
    if(logic) {
        // LIHAT! Langsung masukkan Nama Anak & Deskripsinya disini
        addeffect(logic->data.effects, "Visual Calculus", "Merekonstruksi kejadian masa lalu lewat jejak visual.");
    }

    // Parent: Encyclopedia
    Skill s2; s2.namaSkill = "Encyclopedia"; s2.kategori = "INTELLECT"; s2.level = 1; s2.effects = nullptr;
    insertSkill(root, s2);
    
    SkillNode* enc = searchSkill(root, "Encyclopedia");
    if(enc) {
        // Child: Trivia Rain
        addeffect(enc->data.effects, "Trivia Rain", "Banjir fakta sejarah yang kadang berguna, kadang berisik.");
    }

    // === 2. PSYCHE ===
    // Parent: Inland Empire
    Skill s3; s3.namaSkill = "Inland Empire"; s3.kategori = "PSYCHE"; s3.level = 1; s3.effects = nullptr;
    insertSkill(root, s3);
    
    SkillNode* inland = searchSkill(root, "Inland Empire");
    if(inland) {
        // Child: Talking Object
        addeffect(inland->data.effects, "Talking Object", "Firasat buruk... Dasi dan sentermu mulai berbicara.");
        
        // Kalau mau nambah Child kedua (Adik) juga gampang:
        // addeffect(inland->data.effects, "Dream Walker", "Bisa melihat mimpi orang lain.");
    }

    // ... Lanjutkan untuk skill lainnya (Shivers, Perception, dll) dengan cara yang sama ...
    
    // Skill: Shivers
    Skill s5; s5.namaSkill = "Shivers"; s5.kategori = "PHYSIQUE"; s5.level = 1; s5.effects = nullptr;
    insertSkill(root, s5);
    SkillNode* shiv = searchSkill(root, "Shivers");
    if(shiv) {
        addeffect(shiv->data.effects, "The Campus Whisper", "Angin lorong memberitahumu ada bahaya di lantai atas.");
    }

    // Skill: Perception
    Skill s7; s7.namaSkill = "Perception"; s7.kategori = "MOTORICS"; s7.level = 1; s7.effects = nullptr;
    insertSkill(root, s7);
    SkillNode* perc = searchSkill(root, "Perception");
    if(perc) {
        addeffect(perc->data.effects, "Ghost Sight", "Bisa melihat benda-benda remang yang tersembunyi.");
    }
    
    // Skill Polos (Tanpa Child)
    Skill s4; s4.namaSkill = "Volition"; s4.kategori = "PSYCHE"; s4.level = 1; s4.effects = nullptr; insertSkill(root, s4);
    Skill s6; s6.namaSkill = "Endurance"; s6.kategori = "PHYSIQUE"; s6.level = 1; s6.effects = nullptr; insertSkill(root, s6);
    Skill s8; s8.namaSkill = "Hand/Eye Coordination"; s8.kategori = "MOTORICS"; s8.level = 1; s8.effects = nullptr; insertSkill(root, s8);
}

int main () {
    // 1. Setup Random Seed
    srand(time(0));

    // 2. Setup Peta (BST)
    address rootMap = NIL;
    // Inisialisasi awal peta (Room 1: Perpustakaan)
    pindahKeRuangan(rootMap, *(new int(0)), *(new int(0)), 1);

    // 3. Setup Skill Tree (MLL) - KHUSUS DISCO STYLE
    SkillNode* rootSkill = nullptr;
    
    // Panggil fungsi inisialisasi yang baru kita buat di atas
    initDiscoSkills(rootSkill); 

    int pilihanMenu;
    int radiusPandang = 5;

    do {
        system("cls");
        horrorGlitch("=== BIZZARE NIGHT==="); 
        cout << "1. Mulai Bermain" << endl;
        cout << "2. Setting" << endl;
        cout << "3. Keluar" << endl;
        cout << "-------------------------" << endl;
        cout << "Pilih menu (1-3): ";
        cin >> pilihanMenu;
        
        switch (pilihanMenu)
        {
        case 1:

            mulaiBermain(rootMap, radiusPandang, rootSkill); 
            break;
        case 2:
            lihatSetting(rootMap, radiusPandang);
            break;
        case 3:
            cout << "Pikiranmu perlahan memudar... (Keluar)" << endl;
            break;
        default:
            break;
        }
    } while (pilihanMenu != 3);
    
    // Bersih-bersih memori (Opsional tapi bagus)
    // clearAllSkills(rootSkill);
    
    return 0;
}