#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <string>
#include <conio.h>
#include "effect.h"
using namespace std;

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

// Traversal
void inorder(SkillNode* root);
void preorder(SkillNode* root);
void postorder(SkillNode* root);

// fungsi statistik
int countSkill(SkillNode* root);
SkillNode* maxExpSkill(SkillNode* root);
SkillNode* minExpSkill(SkillNode* root);
float averageLevel(SkillNode* root);
SkillNode* skillWithMostEffects(SkillNode* root);
void viewByCategory(SkillNode* root, string kategori);

// Utilitas
void clearAllSkills(SkillNode*& root);

//Ui menu
void bukaMenuSkill(SkillNode* &skillRoot);
void viewSkillsByCategory(SkillNode* root, string category);
void menuSkillTree(SkillNode* root);

#endif

