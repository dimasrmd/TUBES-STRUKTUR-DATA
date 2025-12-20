#include "Skilltree.h"


SkillNode* createSkillNode(Skill data) {
    SkillNode*newNode = new SkillNode();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
};

void insertSkill(SkillNode*& root, Skill data) {
    if (root == nullptr) {
        root = createSkillNode(data);
    } else if (data.namaSkill < root->data.namaSkill) {
        insertSkill(root->left, data);
    } else {
        insertSkill(root->right, data);
    }
}

SkillNode* searchSkill(SkillNode* root, string namaSkill) {
    if (root == nullptr || root->data.namaSkill == namaSkill) {
        return root;
    }
    if (namaSkill < root->data.namaSkill) {
        return searchSkill(root->left, namaSkill);
    }
    return searchSkill(root->right, namaSkill);
}

void updateSkill(SkillNode* root, string namaSkill) {
    SkillNode* skillNode = searchSkill(root, namaSkill);
    if (skillNode != nullptr) {
        cout << "Updating Skill: " << skillNode->data.namaSkill << endl;
        cout << "Enter new level: ";
        cin >> skillNode->data.level;
        cout << "Level updated successfully." << endl;
    } else {
        cout << "Skill not found." << endl;
    }
};

