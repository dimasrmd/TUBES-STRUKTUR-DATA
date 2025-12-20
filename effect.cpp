#include "effect.h"


effect* createeffect(string effectname, string desc) {
    effect* newEffect = new effect;
    newEffect->nama = effectname;
    newEffect->deskripsi = desc; // Simpan deskripsi
    newEffect->next = nullptr;
    return newEffect;
}


void addeffect(effect*& head, string effectname, string desc) {
    effect* newEffect = createeffect(effectname, desc);
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


void removeEffect(effect*& head, string effectname) {
    if (head == nullptr) return;

    // Jika yang dihapus adalah kepala (Head)
    if (head->nama == effectname) {
        effect* temp = head;
        head = head->next;
        delete temp;
        return;
    }


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


void displayEffects(effect* head) {
    if (head == nullptr) {
        cout << "      (Tidak ada efek tambahan)" << endl;
        return;
    }
    effect* temp = head;
    while (temp != nullptr) {
      
        cout << "      -> [Efek] " << temp->nama << ": " << temp->deskripsi << endl;
        temp = temp->next;
    }
}


void clearAlleffects(effect*& head) {
    effect* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}