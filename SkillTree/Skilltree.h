#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <string>
#include <conio.h>
#include <iostream>
#include "effect.h"
using namespace std;

// Forward declaration
struct CharacterStats;

// Skill categories & types
enum SkillCategory {
    OFFENSIVE,
    DEFENSIVE,
    LIFELINE  // Battle lifelines (Analytical Mind, Memory Recall, etc)
};

struct Skill {
    string namaSkill;     
    string kategori;
    int level;
    int expCost[3];
    int skillPointCost;   // Cost untuk use lifeline (HSR-style)
    effect* effects;      
    bool isLifeline;      // Flag untuk battle lifelines
};

struct SkillNode {
    Skill data;
    SkillNode* left;
    SkillNode* right;
    
};

// Operasi BST
SkillNode* createSkillNode(Skill data);
bool insertSkill(SkillNode*& root, Skill data);
SkillNode* searchSkill(SkillNode* root, string namaSkill);
bool updateSkill(SkillNode* root, string namaSkill);
bool deleteSkill(SkillNode*& root, string namaSkill);
bool clearAllSkills(SkillNode*& root);

// Traversal
bool inorder(SkillNode*& root);
bool viewByCategory(SkillNode* root, string kategori);

// fungsi statistik
int countSkill(SkillNode* root);
SkillNode* maxExpSkill(SkillNode* root);
SkillNode* minExpSkill(SkillNode* root);
float averageLevel(SkillNode* root);
SkillNode* skillWithMostEffects(SkillNode* root);

// Battle lifeline functions (Skill Category: LIFELINE)
bool displayAvailableLifelines(SkillNode* root, const CharacterStats& playerStats);
bool displayLifelinesHelper(SkillNode* root, const CharacterStats& playerStats, int& count);
bool useLifeline(SkillNode* root, string skillName, CharacterStats& playerStats);
bool resetBattleSkillPoints(CharacterStats& playerStats);

//Ui menu
bool menuSkillTree(SkillNode* root, CharacterStats* playerStats);

bool displayCategorySkills(SkillNode* root, string kategori);

SkillNode* minValueNode(SkillNode* node);

// ===== HELPER FUNCTION =====
SkillNode* findLifelineByIndexHelper(SkillNode* node, int& idx, int target);

//Menu Skill dengan lifeline
bool bukaMenuSkill(SkillNode* &skillRoot, CharacterStats* playerStats);

// ===== SKILL INITIALIZATION =====
void initializeSkillTree(SkillNode*& root);

#endif

