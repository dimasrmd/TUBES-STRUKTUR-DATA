#include "effect.h"

// Terima deskripsi di sini
effect* createeffect(string effectname, string desc) {
    effect* newEffect = new effect;
    newEffect->nama = effectname;
    newEffect->deskripsi = desc; // <--- Simpan deskripsi langsung!
    newEffect->next = nullptr;
    return newEffect;
}

// Terima deskripsi di sini juga
void addeffect(effect*& head, string effectname, string desc) {
    effect* newEffect = createeffect(effectname, desc);
    
    if (head == nullptr) {
        head = newEffect;
    } else {
        // Traversal ke ujung ekor anak
        effect* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newEffect;
    }
}

