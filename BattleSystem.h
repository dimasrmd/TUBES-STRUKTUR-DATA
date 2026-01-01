#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <thread>
#include <chrono>
#include "SkillTree/Character.h"
#include "SkillTree/Skilltree.h"

using namespace std;

struct Question {
    string soal;
    string opsiA;
    string opsiB;
    string opsiC;
    string opsiD;
    char jawabanBenar;
};
// 1. Cutscene Naga Muncul (Animasi 18 Frame + Narasi)
void serpentIntroductionCutscene();

// 2. Battle Quiz (Logika Soal, Nyawa, & Menang/Kalah)
bool startDragonBattle(CharacterStats& playerStats, SkillNode* skillRoot = nullptr);

// 3. Display Character Health Interface (untuk gameplay)
void displayCharacterHealthBar(const CharacterStats& playerStats);

#endif