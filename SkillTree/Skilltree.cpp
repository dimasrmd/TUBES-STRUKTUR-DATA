#include <windows.h>
#include <iomanip>
#include "Skilltree.h"
#include "utilitas.h"
#include "Character.h"
#include "effect.h"

// Forward declaration untuk helper function
SkillNode* findLifelineByIndexHelper(SkillNode* node, int& idx, int target);

SkillNode* createSkillNode(Skill data) {
    SkillNode* newNode = new SkillNode();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

bool insertSkill(SkillNode*& root, Skill data) {
    if (root == nullptr) {
        root = createSkillNode(data);
        return true;
    } else if (data.namaSkill < root->data.namaSkill) {
        return insertSkill(root->left, data);
    } else {
        return insertSkill(root->right, data);
    }
}

SkillNode* searchSkill(SkillNode* root, string namaSkill) {
    if (root == nullptr || root->data.namaSkill == namaSkill) {
        return root;
    }
    if (namaSkill < root->data.namaSkill) {
        return searchSkill(root->left, namaSkill);
    }
    return searchSkill(root->right, namaSkill);
}

bool updateSkill(SkillNode* root, string namaSkill) {
    SkillNode* skillNode = searchSkill(root, namaSkill);
    if (skillNode != nullptr) {
        cout << "Updating Skill: " << skillNode->data.namaSkill << endl;
        cout << "Enter new level: ";
        cin >> skillNode->data.level;
        cout << "Level updated successfully." << endl;
        return true;
    } else {
        cout << "Skill not found." << endl;
        return false;
    }
};

int countSkill(SkillNode* root) {
    if (root == nullptr ) return 0;
    return 1 + countSkill(root -> left) + countSkill(root -> right);
}

SkillNode* minValueNode(SkillNode* node) {
    SkillNode* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

bool deleteSkill(SkillNode*& root, string namaSkill) {
    if (root == nullptr) return false;

    if (namaSkill < root->data.namaSkill) {
        return deleteSkill(root ->left, namaSkill);
    } else if (namaSkill > root->data.namaSkill) {
        return deleteSkill(root ->right, namaSkill);
    } else {
        clearAlleffects(root->data.effects);
        if (root -> left == nullptr) {
            SkillNode* temp = root ->right;
            delete root;
            root = temp;
        } else if (root -> right == nullptr){
            SkillNode* temp = root -> left;
            delete root;
            root = temp;
        } else {
            SkillNode* temp = minValueNode(root->right);
            root -> data = temp -> data;
            temp -> data.effects = nullptr;
            deleteSkill(root ->right, temp -> data.namaSkill);
        }
        return true;
    }

} 

bool clearAllSkills(SkillNode*& root){
    if (root == nullptr) return true;
    clearAllSkills(root->left);
    clearAllSkills(root->right);
    delete root;
    root = nullptr;
    return true;
}

bool inorder(SkillNode*& root){
    if (root == nullptr) return true;
    inorder(root ->left);

    cout << "Skill " << root ->data.namaSkill << " (level " << root -> data.level << ")" << endl;
    cout << "Kategori: " << root -> data.kategori << endl;
    displayEffects(root ->data.effects);

    inorder(root ->right);
    return true;
}

bool viewByCategory(SkillNode* root, string kategori){
    if (root == nullptr) return true;
    viewByCategory(root->left, kategori);
    if (root ->data.kategori == kategori){
        cout << "[ + ] " << root ->data.namaSkill << " (Lvl " << root-> data.level << "/3)" << endl;
     //Display Effect
        effect* temp = root -> data.effects;
        while(temp != nullptr) {
            cout << " -> " << temp -> nama << ": " << temp->deskripsi << endl;
            temp = temp -> next;
        }
    }
    viewByCategory(root -> right, kategori);
    return true;
}

bool displayCategorySkills(SkillNode* root, string category){
    if (root == nullptr) return true;

    displayCategorySkills(root ->left, category);

    if (root ->data.kategori == category)
       cout << " * " << root -> data.namaSkill << " (Lvl " << root -> data.level << "/3)" << endl;

    displayCategorySkills(root ->right, category);
    return true;
}

bool menuSkillTree(SkillNode* root, CharacterStats* playerStats) {
    if (playerStats == nullptr) {
        cout <<  "error" << endl;
        _getch();
        return false;
    }

    string inputNama;
    while(true) {
        system("cls");
        horrorGlitch("=== The Mind Palace ===");
        cout << "Health: " << playerStats->health << "/" << playerStats->maxHealth << endl;
        cout << "Skill Points: " << playerStats->availableSkillPoints << endl;

        cout << "\n[ INTELLECT ]" << endl;
        viewByCategory(root, "INTELLECT");

        cout << "\n[ PSYCHE ]" << endl;
        viewByCategory(root, "PSYCHE");

        cout << "\n[ PHYSIQUE ]" << endl;
        viewByCategory(root, "PHYSIQUE");

        cout << "\n[ MOTORICS ]" << endl;
        viewByCategory(root, "MOTORICS");

        cout << "\n========================================" << endl;
        cout << "Ketik nama skill persis untuk upgrade (Case Sensitive)" << endl;
        cout << "Ketik 'x' atau 'X' untuk kembali." << endl;
        cout << ">> Input: ";
        
        if (cin.peek() == '\n') cin.ignore(); 
        getline(cin, inputNama);
        if (inputNama == "x" || inputNama == "X") break;
        
        // Search skill
        SkillNode* hasil = searchSkill(root, inputNama);
        
        if (hasil) {
            system("cls");
            cout << "+" << setfill('-') << setw(68) << "" << "+" << endl; cout << setfill(' ');
            cout << "| " << setw(66) << "[SKILL]: " + hasil->data.namaSkill << " |" << endl; cout << setfill(' ');
            cout << "| " << setw(66) << "Category: " + hasil->data.kategori << " |" << endl; cout << setfill(' ');
            cout << "| " << setw(66) << "Current Level: " + hasil->data.level << " |" << endl; cout << setfill(' ');
            cout << "+" << setfill('-') << setw(68) << "" << "+" << endl; cout << setfill(' ');
            cout << "| " << setw(66) << "EFFECTS: " + hasil->data.level << " |" << endl; cout << setfill(' ');
            displayEffects(hasil->data.effects);
            cout << "+" << setfill('-') << setw(68) << "" << "+" << endl; cout << setfill(' ');
            
            // Upgrade logic
            if (hasil->data.level >= 3) {
                cout << "\n[!] Skill sudah MAX LEVEL!" << endl;
            } else if (playerStats->availableSkillPoints <= 0) {
                cout << "\n[!] Tidak punya Skill Points!" << endl;
            } else {
                cout << "\n[?] Upgrade ke Level " << (hasil->data.level + 1) << "? (Y/N): ";
                char confirm;
                cin >> confirm;
                
                if (confirm == 'Y' || confirm == 'y') {
                    // Deduct skill point
                    playerStats->availableSkillPoints--;
                    
                    // Level up
                    hasil->data.level++;
                    
                    // Apply all PASSIVE effects
                    effect* eff = hasil->data.effects;
                    while (eff != nullptr) {
                        if (eff->type == PASSIVE) {
                            string effectTypeUpper = eff->statAffected;
                            for (auto& c : effectTypeUpper) c = toupper(c);
                            applyCharacterEffect(*playerStats, effectTypeUpper, eff->value);
                            cout << "[+] " << eff->nama << " activated!" << endl;
                        }
                        eff = eff->next;
                    }
                    
                    cout << "\n[✓] " << hasil->data.namaSkill << " upgraded to Level " 
                         << hasil->data.level << "!" << endl;
                }
            }
        } else {
            cout << "\n[!] Skill tidak ditemukan..." << endl;
        }
        
        cout << "\nTekan tombol apapun untuk melanjutkan...";
        _getch();
    }
    return true;
}
// ===== LIFELINE/BATTLE SKILL FUNCTIONS =====

bool displayAvailableLifelines(SkillNode* root, const CharacterStats& playerStats) {
    system("cls");
    SetConsoleOutputCP(CP_UTF8);
    
    cout << "\n   ╔═══════════════════════════════════════════════════╗" << endl;
    cout << "   ║     AVAILABLE LIFELINES / SKILLS                  ║" << endl;
    cout << "   ╠═══════════════════════════════════════════════════╣" << endl;
    cout << "   ║  Skill Points: " << playerStats.battleSkillPoints << "/" << playerStats.maxBattleSkillPoints << setw(32) << " " << "║" << endl;
    cout << "   ╠═══════════════════════════════════════════════════╣" << endl;
    
    int count = 0;
    displayLifelinesHelper(root, playerStats, count);
    
    if (count == 0) {
    cout << "   ║  Tidak ada skill tersedia                         ║" << endl;
    }
    
    cout << "   ╠═══════════════════════════════════════════════════╣" << endl;
    cout << "   ║  [0] Skip Skill                                   ║" << endl;
    cout << "   ╚═══════════════════════════════════════════════════╝" << endl;
    return true;
}

bool displayLifelinesHelper(SkillNode* root, const CharacterStats& playerStats, int& count) {
    if (root == nullptr) return true;
    
    displayLifelinesHelper(root->left, playerStats, count);
    
    if (root->data.isLifeline) {
        count++;
        string skillName = root->data.namaSkill;
        int cost = root->data.skillPointCost;
        
        // Format: [X] Nama Skill (X pt)
        // Panjang maksimal nama: 28 karakter (agar pas dengan lebar tabel 47)
        int maxNameLength = 28;
        if (skillName.length() > maxNameLength) {
            skillName = skillName.substr(0, maxNameLength - 3) + "...";
        }
        
        // Format dengan padding yang rapi
        // Total lebar konten: 6 (spasi + [X] + spasi) + 28 (nama) + 8 ( (X pt)) = 42
        cout << "   ║  [" << setw(2) << count << "] " << left << setw(maxNameLength) << skillName 
             << " (" << setw(2) << cost << " pt)" << setw(8) << " " << "║" << endl;
    }
    
    displayLifelinesHelper(root->right, playerStats, count);
    return true;
}

bool useLifeline(SkillNode* root, string skillName, CharacterStats& playerStats) {
    SkillNode* skill = searchSkill(root, skillName);
    
    if (skill == nullptr) {
        cout << "Skill not found!" << endl;
        return false;
    }
    
    if (!skill->data.isLifeline) {
        cout << "This is not a lifeline skill!" << endl;
        return false;
    }
    
    if (playerStats.battleSkillPoints >= skill->data.skillPointCost) {
        playerStats.battleSkillPoints -= skill->data.skillPointCost;
        return true;
    }
    
    cout << "Skill tidak cukup " << skill->data.skillPointCost 
         << " Point mu tersisa " << playerStats.battleSkillPoints << endl;
    return false;
}

bool resetBattleSkillPoints(CharacterStats& playerStats) {
    playerStats.battleSkillPoints = playerStats.maxBattleSkillPoints;
    return true;
}

// ===== UNIFIED SKILL MENU =====
bool bukaMenuSkill(SkillNode* &skillRoot, CharacterStats* playerStats) {
    if (playerStats == nullptr) {
        cout << "Error: Player stats tidak ditemukan!" << endl;
        _getch();
        return false;
    }

    int pilihan = 0;
    while(true) {
        system("cls");
        horrorGlitch("=== SKILL MENU ===");
        
        cout << "\nNama Karakter: [Protagonist]" << endl;
        cout << "Health: " << playerStats->health << "/" << playerStats->maxHealth << endl;
        cout << "Skill Points: " << playerStats->availableSkillPoints << endl;
        cout << "Battle Skill Points: " << playerStats->battleSkillPoints << "/" << playerStats->maxBattleSkillPoints << endl;
        
        cout << "\n================================" << endl;
        cout << "[1] Lihat Semua Skill (Mind Palace)" << endl;
        cout << "[2] Lihat Skill Lifeline (Battle)" << endl;
        cout << "[3] Kembali" << endl;
        cout << "================================" << endl;
        cout << ">> Pilihan: ";
        
        cin >> pilihan;
        cin.ignore();
        
        if (pilihan == 1) {
            menuSkillTree(skillRoot, playerStats);
        } 
        else if (pilihan == 2) {
            displayAvailableLifelines(skillRoot, *playerStats);
            cout << "\n>> Pilih Skill (0 untuk skip): ";
            int lifelineChoice;
            cin >> lifelineChoice;
            
            if (lifelineChoice > 0) {
                // Find the specific lifeline skill by index
                SkillNode* selectedSkill = nullptr;
                int count = 0;
                
                selectedSkill = findLifelineByIndexHelper(skillRoot, count, lifelineChoice);
                
                if (selectedSkill != nullptr) {
                    if (useLifeline(skillRoot, selectedSkill->data.namaSkill, *playerStats)) {
                        cout << "\n╔════════════════════════════════════════╗" << endl;
                        cout << "║ [✓] " << selectedSkill->data.namaSkill << " DIAKTIFKAN!" << endl;
                        cout << "╠════════════════════════════════════════╣" << endl;
                        
                        // Apply ACTIVE effects
                        effect* eff = selectedSkill->data.effects;
                        while (eff != nullptr) {
                            if (eff->type == ACTIVE) {
                                string effectTypeUpper = eff->statAffected;
                                for (auto& c : effectTypeUpper) c = toupper(c);
                                applyCharacterEffect(*playerStats, effectTypeUpper, eff->value);
                                
                                cout << "║ " << eff->nama << endl;
                                cout << "║" << endl;
                                cout << "║ " << eff->deskripsi << endl;
                            }
                            eff = eff->next;
                        }
                        
                        cout << "║" << endl;
                        cout << "║ Sisa Skill Points: " << playerStats->battleSkillPoints << "/" << playerStats->maxBattleSkillPoints << endl;
                        cout << "╚════════════════════════════════════════╝" << endl;
                    }
                }
            }
            
            cout << "\nTekan tombol apapun untuk melanjutkan...";
            _getch();
        }
        else if (pilihan == 3) {
            break;
        }
        else {
            cout << "[!] Pilihan tidak valid!" << endl;
            _getch();
        }
    }
    
    return true;
}

// ===== HELPER FUNCTION FOR FINDING LIFELINEBYINDEX =====
SkillNode* findLifelineByIndexHelper(SkillNode* node, int& idx, int target) {
    if (node == nullptr) return nullptr;
    
    SkillNode* left = findLifelineByIndexHelper(node->left, idx, target);
    if (left != nullptr) return left;
    
    if (node->data.isLifeline) {
        idx++;
        if (idx == target) return node;
    }
    
    return findLifelineByIndexHelper(node->right, idx, target);
}

// ===== SKILL TREE INITIALIZATION =====
void initializeSkillTree(SkillNode*& root) {
    // ===== BATTLE LIFELINE SKILLS =====
    // Konsep: Inner dialogue dengan otak sendiri untuk bantu jawab soal
    
    // 1. Analytical Mind - Analisa soal secara logis
    Skill analyticalMind;
    analyticalMind.namaSkill = "Analytical Mind";
    analyticalMind.kategori = "INTELLECT";
    analyticalMind.level = 1;
    analyticalMind.skillPointCost = 1;
    analyticalMind.isLifeline = true;
    analyticalMind.effects = nullptr;
    addeffect(analyticalMind.effects, "[OTAK]: Analisa Logis", 
              "[EFEK] Eliminasi 2 pilihan yang PASTI SALAH\n      Sisa 2 pilihan untuk dipilih\n      'Analisis ini... eliminasi yang tidak logis!'", 
              ACTIVE, "intellect", 2);
    insertSkill(root, analyticalMind);
    
    // 2. Memory Recall - Ingat konsep dari pelajaran
    Skill memoryRecall;
    memoryRecall.namaSkill = "Memory Recall";
    memoryRecall.kategori = "INTELLECT";
    memoryRecall.level = 1;
    memoryRecall.skillPointCost = 1;
    memoryRecall.isLifeline = true;
    memoryRecall.effects = nullptr;
    addeffect(memoryRecall.effects, "[OTAK]: Recall Memori", 
              "[EFEK] Eliminasi 1 pilihan yang salah\n      Sisa 3 pilihan untuk dipilih\n      'Soal ini... aku ingat variasinya...'", 
              ACTIVE, "intellect", 1);
    insertSkill(root, memoryRecall);
    
    // 3. Intuition Strike - Intuisi yang kuat
    Skill intuitionStrike;
    intuitionStrike.namaSkill = "Intuition Strike";
    intuitionStrike.kategori = "PSYCHE";
    intuitionStrike.level = 1;
    intuitionStrike.skillPointCost = 2;
    intuitionStrike.isLifeline = true;
    intuitionStrike.effects = nullptr;
    addeffect(intuitionStrike.effects, "[OTAK]: Firasat Kuat", 
              "[EFEK] LANGSUNG TAHU JAWABAN YANG BENAR!\n      Menampilkan jawaban yang 100% BENAR\n      'TUNGGU! Aku YAKIN... jawaban yang benar adalah...'", 
              ACTIVE, "psyche", 3);
    insertSkill(root, intuitionStrike);
    
    // 4. Clear Mind - Tenangkan pikiran yang kalut
    Skill clearMind;
    clearMind.namaSkill = "Clear Mind";
    clearMind.kategori = "PSYCHE";
    clearMind.level = 1;
    clearMind.skillPointCost = 1;
    clearMind.isLifeline = true;
    clearMind.effects = nullptr;
    addeffect(clearMind.effects, "[OTAK]: Pikiran Jernih", 
              "[EFEK] Eliminasi 1 pilihan yang salah\n      Sisa 3 pilihan untuk dipilih\n      'Tenang... fokus... pikiran jernih membuka jalan...'", 
              ACTIVE, "psyche", 2);
    insertSkill(root, clearMind);
    
    // 5. Focused Concentration - Fokus total
    Skill focusedConcentration;
    focusedConcentration.namaSkill = "Focused Concentration";
    focusedConcentration.kategori = "MOTORICS";
    focusedConcentration.level = 1;
    focusedConcentration.skillPointCost = 1;
    focusedConcentration.isLifeline = true;
    focusedConcentration.effects = nullptr;
    addeffect(focusedConcentration.effects, "[OTAK]: Konsentrasi Penuh", 
              "[EFEK] Eliminasi 2 pilihan yang salah\n      Sisa 2 pilihan untuk dipilih\n      'FOKUS TOTAL! Semua gangguan hilang...'", 
              ACTIVE, "motorics", 2);
    insertSkill(root, focusedConcentration);
}