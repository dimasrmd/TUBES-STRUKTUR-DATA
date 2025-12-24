#include "bstNode.h"

address createNode(int objectX, int objectY, string namaObject, string pesanObject, bool statusDilewati) {
    address node = new Node;
    node->x = objectX;
    node->y = objectY;
    node->nama = namaObject;
    node->pesan = pesanObject;
    node->tembus = statusDilewati;
    node->left = node->right = NIL;
    return node;
}

address insert(address root, int x, int y, string namaObj, string pesanObj, bool statusDilewati){
    if (root == NIL) {
        root = createNode(x, y, namaObj, pesanObj, statusDilewati);
        return root;
    }

    // Prioritas X, lalu Y (sederhana)
    if (x < root->x) root->left = insert(root->left, x, y, namaObj, pesanObj, statusDilewati);
    else if (x > root->x) root->right = insert(root->right, x, y, namaObj, pesanObj, statusDilewati);
    else {
        if (y < root->y) root->left = insert(root->left, x, y, namaObj, pesanObj, statusDilewati);
        else root->right = insert(root->right, x, y, namaObj, pesanObj, statusDilewati);
    }
    return root;
}

address cariNode(address root, int x, int y) {
    if (root == NIL) return NIL;
    if (root->x == x && root->y == y) return root;

    if (x < root->x) return cariNode(root->left, x, y);
    else if(x > root->x) return cariNode(root->right, x, y);
    else {
        if (y < root->y) return cariNode(root->left, x, y);
        else return cariNode(root->right, x, y);
    }
}