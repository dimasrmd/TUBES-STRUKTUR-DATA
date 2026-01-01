#include "effect.h"
#include <iomanip>

// Fungsi untuk membuat node effect baru
effect* createeffect(string effectname, string desc, EffectType type, 
                     string statAffected, int value) {
    effect* newEffect = new effect;
    newEffect->nama = effectname;
    newEffect->deskripsi = desc;
    
    newEffect->type = type;
    newEffect->statAffected = statAffected;
    newEffect->value = value;
    
    // Otomatis aktif jika tipenya PASSIVE
    newEffect->isActive = (type == PASSIVE); 
    
    newEffect->next = nullptr;
    return newEffect;
}

void displayEffects(effect* head) {
    if (head == nullptr) {
        cout << "|" << setw(68) << "  [No Effects]" << "|" << endl;
        return;
    }
    
    effect* temp = head;
    while (temp != nullptr) {
        string status = temp->isActive ? "[ACTIVE]" : "[INACTIVE]";
        
        // Baris 1: Nama effect + status (sejajar kanan)
        cout << "|  • " << left << setw(49) << temp->nama 
             << right << setw(12) << status << "   |" << endl;
        
        // Baris 2: Deskripsi
        cout << "|     " << left << setw(70) << temp->deskripsi << " |" << endl;
    
        // Baris 3: Effect value (jika ada)
        if (temp->statAffected != "" && temp->value != 0) {
            string effectText = "Effect: ";
            effectText += temp->statAffected + " ";
            if (temp->value > 0) effectText += "+";
            effectText += to_string(temp->value);
            
            cout << "|     " << left << setw(59) << effectText << " |" << endl;
        }
        
        temp = temp->next;
    }
}

void activateEffect(effect* effectNode) {
    if (effectNode != nullptr && effectNode->type != PASSIVE) {
        effectNode->isActive = true;
        cout << "[+] Effect '" << effectNode->nama << "' activated!" << endl;
    }
}

// PERBAIKAN UTAMA ADA DI SINI:
// Parameter harus lengkap sesuai header (type, statAffected, value)
void addeffect(effect*& head, string effectname, string desc, EffectType type, string statAffected, int value) {
    
    // Panggil createeffect dengan semua data
    effect* newEffect = createeffect(effectname, desc, type, statAffected, value);
    
    if (head == nullptr) {
        head = newEffect;
    } else {
        // Traversal ke ujung ekor
        effect* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newEffect;
    }
}

void removeEffect(effect*& head, string effectname) {
    if (head == nullptr) return;
    
    // Jika head yang mau dihapus
    if (head->nama == effectname) {
        effect* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    
    // Cari di linked list
    effect* current = head;
    while (current->next != nullptr) {
        if (current->next->nama == effectname) {
            effect* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return;
        }
        current = current->next;
    }
}

void clearAlleffects(effect*& head) {
    while (head != nullptr) {
        effect* temp = head;
        head = head->next;
        delete temp;
    }
}
