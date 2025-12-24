#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <string>
#include <conio.h>
#include <iostream>
#include "effect.h"
using namespace std;

// Forward declaration
struct CharacterStats;

struct Skill {
    string namaSkill;     
    string kategori;
    int level;
    int expCost[3];       
    effect* effects;      
};

struct SkillNode {
    Skill data;
    SkillNode* left;
    SkillNode* right;
    
};

// Operasi BST
SkillNode* createSkillNode(Skill data);
void insertSkill(SkillNode*& root, Skill data);
SkillNode* searchSkill(SkillNode* root, string namaSkill);
void updateSkill(SkillNode* root, string namaSkill);
void deleteSkill(SkillNode*& root, string namaSkill);
void clearAllSkills(SkillNode*& root);

// Traversal
void inorder(SkillNode*& root);
void viewByCategory(SkillNode* root, string kategori);

// fungsi statistik
int countSkill(SkillNode* root);
SkillNode* maxExpSkill(SkillNode* root);
SkillNode* minExpSkill(SkillNode* root);
float averageLevel(SkillNode* root);
SkillNode* skillWithMostEffects(SkillNode* root);


//Ui menu
void menuSkillTree(SkillNode* root, CharacterStats* playerStats);

void displaycategorySkills(SkillNode* root, string kategori);

SkillNode* minValueNode(SkillNode* node);

//Ui menu
void bukaMenuSkill(SkillNode* &skillRoot);
void viewSkillsByCategory(SkillNode* root, string category);
void menuSkillTree(SkillNode* root);

#endif

