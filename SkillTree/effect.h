#ifndef EFFECT_H
#define EFFECT_H
#include <iostream>
#include <string>
using namespace std;

struct effect{
    string nama;
    string deskripsi; 
    effect* next;
};

// Update parameternya: tambah string deskripsi
effect* createeffect(string effectname, string desc);
void addeffect(effect*& head, string effectname, string desc);

void removeEffect(effect*& head, string effectname);
void displayEffects(effect* head);
void clearAlleffects(effect*& head);

#endif