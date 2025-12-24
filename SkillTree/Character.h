#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <map>
#include <iostream>
#include "effect.h"
using namespace std;

// ❌ HAPUS deklarasi ini (pindah ke effect.h):
// void removeEffect(effect*& head, string effectname);
// void displayEffects(effect* head);
// void clearAlleffects(effect*& head);

struct CharacterStats {
    int intellect;
    int psyche;
    int physique;
    int motorics;
    
    // Derived Stats
    int health;
    int maxHealth;
    int morale;
    int maxMorale;
    
    // Skill-specific bonuses
    map<string, int> bonuses;
    
    // Experience & Progression
    int totalExp;
    int availableSkillPoints;
    int playerLevel;
    
    // Constructor
    CharacterStats() {
        intellect = 1;
        psyche = 1;
        physique = 1;
        motorics = 1;
        
        maxHealth = 10;
        health = maxHealth;
        maxMorale = 10;
        morale = maxMorale;
        
        totalExp = 0;
        availableSkillPoints = 3;
        playerLevel = 1;
    }
};

// ✅ RENAME fungsi-fungsi ini (tambah prefix "character"):
inline void applyCharacterEffect(CharacterStats& stats, string effectType, int value) {
    if (effectType == "HEALTH") {
        stats.health += value;
        if (stats.health > stats.maxHealth) stats.health = stats.maxHealth;
        if (stats.health < 0) stats.health = 0;
    }
    else if (effectType == "MAX_HEALTH") {
        stats.maxHealth += value;
        if (stats.maxHealth < 1) stats.maxHealth = 1;
    }
    else if (effectType == "MORALE") {
        stats.morale += value;
        if (stats.morale > stats.maxMorale) stats.morale = stats.maxMorale;
        if (stats.morale < 0) stats.morale = 0;
    }
    else if (effectType == "MAX_MORALE") {
        stats.maxMorale += value;
        if (stats.maxMorale < 1) stats.maxMorale = 1;
    }
    else if (effectType == "INTELLECT") {
        stats.intellect += value;
        if (stats.intellect < 0) stats.intellect = 0;
    }
    else if (effectType == "PSYCHE") {
        stats.psyche += value;
        if (stats.psyche < 0) stats.psyche = 0;
    }
    else if (effectType == "PHYSIQUE") {
        stats.physique += value;
        if (stats.physique < 0) stats.physique = 0;
    }
    else if (effectType == "MOTORICS") {
        stats.motorics += value;
        if (stats.motorics < 0) stats.motorics = 0;
    }
    else {
        // Custom bonuses
        stats.bonuses[effectType] += value;
    }
}

inline void removeCharacterEffect(CharacterStats& stats, string effectType, int value) {
    applyCharacterEffect(stats, effectType, -value);
}

inline void addCharacterExp(CharacterStats& stats, int amount) {
    stats.totalExp += amount;
    while (stats.totalExp >= 100) {
        stats.availableSkillPoints++;
        stats.totalExp -= 100;
    }
}

inline void displayCharacterStats(const CharacterStats& stats) {
    cout << "\n╔═══════════════════════════════════════╗" << endl;
    cout << "║        CHARACTER STATUS                ║" << endl;
    cout << "╠═══════════════════════════════════════╣" << endl;
    cout << "║ Level: " << stats.playerLevel << "                             ║" << endl;
    cout << "║ Health: " << stats.health << "/" << stats.maxHealth << "  Morale: " << stats.morale << "/" << stats.maxMorale << "       ║" << endl;
    cout << "╠═══════════════════════════════════════╣" << endl;
    cout << "║ INTELLECT:  " << stats.intellect << "                        ║" << endl;
    cout << "║ PSYCHE:     " << stats.psyche << "                        ║" << endl;
    cout << "║ PHYSIQUE:   " << stats.physique << "                        ║" << endl;
    cout << "║ MOTORICS:   " << stats.motorics << "                        ║" << endl;
    cout << "╠═══════════════════════════════════════╣" << endl;
    cout << "║ Skill Points: " << stats.availableSkillPoints << "                      ║" << endl;
    cout << "║ EXP: " << stats.totalExp << "/100                         ║" << endl;
    cout << "╚═══════════════════════════════════════╝" << endl;
}

#endif