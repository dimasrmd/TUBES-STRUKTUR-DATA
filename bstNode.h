#ifndef BST_H
#define BST_H
#define NIL NULL

#include <iostream>
using namespace std;
typedef struct Node *address; // bstNode.h: address menyimpan alamat node
struct infoNode { // bstNode.h: struktur info node
    int x, y;
    string nama, pesan;
    bool solid;
};

struct Node { // bstNode.h: struktur dari node
    infoNode info;
    address left, right;
};

address createNode(infoNode info); // bstNode.h: Membuat node baru
address insert(address root, infoNode info); // bstNode.h: Memasukkan data baru ke bst
address insert(address root, int x, int y, string namaObj, string pesanObj, bool solid); // bstNode.h: Memasukkan data baru ke bst
address cariNode(address root, int x, int y); // bstNode.h: mencari node khsusus
address findMin(address root);
address deleteNode(address root, int x, int y);

#endif