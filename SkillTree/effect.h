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

effect* createeffect(string effectname);
void addeffect(effect*& head,string effectname);
void removeEffect(effect*& head, string effectname);
void displayEffects(effect* head);
void clearAlleffects(effect*& head);

#endif
