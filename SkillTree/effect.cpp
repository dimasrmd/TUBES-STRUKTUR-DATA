#include "effect.h"

// Membuat node efek baru
effect* createeffect(string effectname) {
    effect* newEffect = new effect;
    newEffect->nama = effectname;
    newEffect->deskripsi = "Deskripsi default"; 
    newEffect->next = nullptr;
    return newEffect;
}

// Menambah efek di belakang list (Insert Last)
void addeffect(effect*& head, string effectname) {
    effect* newEffect = createeffect(effectname);
    if (head == nullptr) {
        head = newEffect;
    } else {
        effect* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newEffect;
    }
}

// Menghapus satu efek spesifik
void removeEffect(effect*& head, string effectname) {
    if (head == nullptr) return;

    // Jika yang dihapus adalah kepala (Head)
    if (head->nama == effectname) {
        effect* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // Cari di tengah atau akhir
    effect* current = head;
    effect* prev = nullptr;
    while (current != nullptr && current->nama != effectname) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return; // Gak ketemu

    prev->next = current->next;
    delete current;
}

// Menampilkan semua efek (Traversal Child)
void displayEffects(effect* head) {
    if (head == nullptr) {
        cout << "      (Tidak ada efek tambahan)" << endl;
        return;
    }
    effect* temp = head;
    while (temp != nullptr) {
        cout << "      -> [Efek] " << temp->nama << endl;
        temp = temp->next;
    }
}

// Bersihkan semua efek (dipakai saat Skill dihapus)
void clearAlleffects(effect*& head) {
    effect* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}