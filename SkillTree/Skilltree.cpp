#include "Skilltree.h"
#include "utilitas.h"
#include "Character.h"
#include "effect.h"


SkillNode* createSkillNode(Skill data) {
    SkillNode* newNode = new SkillNode();
    newNode->data = data;
    newNode->data.effects = nullptr; 
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

void insertSkill(SkillNode*& root, Skill data) {
    if (root == nullptr) {
        root = createSkillNode(data);
    } else if (data.namaSkill < root->data.namaSkill) {
        insertSkill(root->left, data);
    } else {
        insertSkill(root->right, data);
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

void updateSkill(SkillNode* root, string namaSkill) {
    SkillNode* skillNode = searchSkill(root, namaSkill);
    if (skillNode != nullptr) {
        cout << "Updating Skill: " << skillNode->data.namaSkill << endl;
        cout << "Enter new level: ";
        cin >> skillNode->data.level;
        cout << "Level updated successfully." << endl;
    } else {
        cout << "Skill not found." << endl;
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

void deleteSkill(SkillNode*& root, string namaSkill) {
    if (root == nullptr) return;

    if (namaSkill < root->data.namaSkill) {
        deleteSkill(root ->left, namaSkill);
    } else if (namaSkill > root->data.namaSkill) {
        deleteSkill(root ->right, namaSkill);
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

    }

} 

void clearAllSkills(SkillNode*& root){
    if (root == nullptr) return;
    clearAllSkills(root->left);
    clearAllSkills(root->right);
    delete root;
    root = nullptr;
}

void inorder(SkillNode*& root){
    if (root == nullptr) return;
    inorder(root ->left);

    cout << "Skill" << root ->data.namaSkill << " (level " << root -> data.level << ")" << endl;
    cout << "kategori" << root -> data.kategori << endl;
    displayEffects(root ->data.effects);

    inorder(root ->right);
}

void viewByCategory(SkillNode* root, string kategori){
    if (root == nullptr) return;
    viewByCategory(root->left, kategori);
    if (root ->data.kategori == kategori){
        cout << "[ + ]" << root ->data.namaSkill << "(Lvl)" << root-> data.level << "/3)" << endl;
     //Display Effect
        effect* temp = root -> data.effects;
        while(temp != nullptr) {
            cout << " -> " << temp -> nama << ": " << temp->deskripsi << endl;
            temp = temp -> next;
        }
    }
    viewByCategory(root -> right, kategori);
}

void displayCategorySkills(SkillNode* root, string category){
    if (root == nullptr) return;

    displayCategorySkills(root ->left, category);

    if (root ->data.kategori == category)
       cout << " * " << root -> data.namaSkill << "(Lvl" << root -> data.level << "/3)" << endl;

}

void menuSkillTree(SkillNode* root, CharacterStats* playerStats) {
    if (playerStats == nullptr) {
        cout <<  "error" << endl;
        _getch();
        return;
    }

    string inputNama;
    while(true) {
        system("cls");
        horrorGlitch("=== The mind Palace ===");
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
            cout << "\n╔════════════════════════════════════════╗" << endl;
            cout << "║ [SKILL]: " << hasil->data.namaSkill << endl;
            cout << "║ Category: " << hasil->data.kategori << endl;
            cout << "║ Current Level: " << hasil->data.level << "/3" << endl;
            cout << "╠════════════════════════════════════════╣" << endl;
            cout << "║ EFFECTS:" << endl;
            displayEffects(hasil->data.effects);
            cout << "╚════════════════════════════════════════╝" << endl;
            
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
                             applyCharacterEffect(*playerStats, eff->statAffected, eff->value);
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
}
