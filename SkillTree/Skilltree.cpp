#include "Skilltree.h"
#include "utilitas.h"


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

void clearAllSkills(SkillNode*& root) {
    if (root == nullptr) return;
    clearAllSkills(root->left);
    clearAllSkills(root->right);

    // clearAlleffects(root->data.effects);
 
    delete root;
    root = nullptr;
}

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

    // 1. Cari dulu nodenya ada di mana
    if (namaSkill < root->data.namaSkill) {
        deleteSkill(root->left, namaSkill);
    } else if (namaSkill > root->data.namaSkill) {
        deleteSkill(root->right, namaSkill);
    } else {
        // NODE KETEMU! Sekarang saatnya eksekusi.

        // LANGKAH PENTING: Hapus dulu anak-anaknya (List Effect)
        // Kalau tidak dihapus, memorinya nyangkut (Memory Leak)
        // clearAlleffects(root->data.effects);

        // Kasus 1: Tidak punya anak atau cuma 1 anak
        if (root->left == nullptr) {
            SkillNode* temp = root->right;
            delete root;
            root = temp;
        } else if (root->right == nullptr) {
            SkillNode* temp = root->left;
            delete root;
            root = temp;
        } else {
            // Kasus 2: Punya 2 anak (Kiri & Kanan)
            
            // Cari pengganti (Successor = terkecil di kanan)
            SkillNode* temp = minValueNode(root->right);

            // Salin data pengganti ke node ini
            root->data = temp->data;

            // PENTING BANGET: 
            // Kita harus putuskan hubungan pointer efek di node pengganti asli (temp)
            // Supaya pas temp dihapus di bawah, dia nggak ikut ngehapus efek yang barusan kita copy ke atas.
            temp->data.effects = nullptr;

            // Hapus node pengganti yang lama
            deleteSkill(root->right, temp->data.namaSkill);
        }
    }
}

// --- TRAVERSAL (Menampilkan Skill + Efeknya) ---
void inorder(SkillNode* root) {
    if (root == nullptr) return;

    // Ke Kiri
    inorder(root->left);

    // Cetak Data (Parent)
    cout << "---------------------------------" << endl;
    cout << "[SKILL] " << root->data.namaSkill << " (Lvl " << root->data.level << ")" << endl;
    cout << "Kategori: " << root->data.kategori << endl;
    
    // Cetak Efek (Child - Linked List)
    // Fungsi ini ada di effect.cpp
    // displayEffects(root->data.effects);

    // Ke Kanan
    inorder(root->right);
}

void viewByCategory(SkillNode* root, string kategori) {
    if (root == nullptr) return;

    viewByCategory(root -> left, kategori);
    if (root -> data.kategori == kategori) {
        cout <<" [+] " << root -> data.namaSkill << "(lvl " << root -> data.level << ")" << endl;
    }
    effect* temp = root -> data.effects;
    while (temp != nullptr) {
        cout << "  -> " << temp -> nama << ":" << temp -> deskripsi << endl;
        temp = temp -> next;
    }
    viewByCategory(root -> right, kategori);
}

void menuSkillTree(SkillNode *root) {
    string inputNama;
    while (true) {
        system("cls");
        horrorGlitch("=== THE MIND PALACE ===");
        
        // TAMPILAN 4 PILAR (ALA DISCO ELYSIUM)
        cout << "==================================================" << endl;
        
        cout << " [1] INTELLECT (Logika)" << endl;
        viewByCategory(root, "INTELLECT");
        cout << "--------------------------------------------------" << endl;
        cout << " [2] PSYCHE (Jiwa)" << endl;
        viewByCategory(root, "PSYCHE");
        cout << "--------------------------------------------------" << endl;
        cout << " [3] PHYSIQUE (Fisik)" << endl;
        viewByCategory(root, "PHYSIQUE");
        cout << "--------------------------------------------------" << endl;
        cout << " [4] MOTORICS (Gerak)" << endl;
        viewByCategory(root, "MOTORICS");
        cout << "==================================================" << endl;
        cout << "[Ketik Nama Skill untuk Upgrade] atau [X] Kembali" << endl;
        cout << ">> Pilihan: ";
        
        // ... (Sisa logika input, search, dan upgrade SAMA PERSIS dengan sebelumnya) ...
        if (cin.peek() == '\n') cin.ignore(); 
        getline(cin, inputNama);
        if (inputNama == "x" || inputNama == "X") break;
        
        // Logika Search & Upgrade (Copy dari kode sebelumnya)
        SkillNode* hasil = searchSkill(root, inputNama);
        if (hasil) {
            cout << "\n[!] Skill: " << hasil->data.namaSkill << " (" << hasil->data.kategori << ")" << endl;
            // ... logika upgrade level ...
            // Saat level naik, kamu bisa tambah Named Effect baru
            // Contoh:
            // if (level == 2 && nama == "Inland Empire") addeffect(..., "Dimension Hopper");
        } else {
            cout << "Suara itu tidak ada di kepalamu..." << endl;
        }
        _getch();
    }
}