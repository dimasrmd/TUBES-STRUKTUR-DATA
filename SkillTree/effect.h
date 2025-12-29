#ifndef EFFECT_H
#define EFFECT_H
#include <iostream>
#include <string>
using namespace std;

enum EffectType {
    PASSIVE,
    ACTIVE,
    TRIGGERED
};

struct effect {
    string nama;
    string deskripsi;
    EffectType type;
    string statAffected;
    int value;
    bool isActive;
    effect* next;
};

// Deklarasi fungsi effect
effect* createeffect(string effectname, string desc, 
                     EffectType type = PASSIVE, 
                     string statAffected = "", 
                     int value = 0);

void addeffect(effect*& head, string effectname, string desc, 
               EffectType type = PASSIVE, 
               string statAffected = "", 
               int value = 0);

void activateEffect(effect* effectNode);
void deactivateEffect(effect* effectNode);
effect* findEffect(effect* head, string effectName);

void displayEffects(effect* head);
void removeEffect(effect*& head, string effectname);
void clearAlleffects(effect*& head);

#endif