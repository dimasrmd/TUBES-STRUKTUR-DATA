#include "bstNode.h"

address createNode(infoNode isi) {
    address node = new Node;
    node->info.nama = isi.nama;
    node->info.pesan = isi.pesan;
    node->info.solid = isi.solid;
    node->info.x = isi.x;
    node->info.y = isi.y;
    node->left = node->right = NIL;
    return node;
}

address insert(address root, infoNode isi){
    if (root == NIL) {
        root = createNode(isi);
        return root;
    }

    if (isi.x < root->info.x) root->left = insert(root->left, isi);
    else if (isi.x > root->info.x) root->right = insert(root->right, isi);
    else {
        if (isi.y < root->info.y) root->left = insert(root->left, isi);
        else root->right = insert(root->right, isi);
    }
    return root;
}

address insert(address root, int x, int y, string namaObj, string pesanObj, bool solid){
    infoNode dataBaru;
    dataBaru.x = x;
    dataBaru.y = y;
    dataBaru.nama = namaObj;
    dataBaru.pesan = pesanObj;
    dataBaru.solid = solid;
    return insert(root, dataBaru);
}

address cariNode(address root, int x, int y) {
    if (root == NIL) return NIL;
    if (root->info.x == x && root->info.y == y) return root;

    if (x < root->info.x) return cariNode(root->left, x, y);
    else if(x > root->info.x) return cariNode(root->right, x, y);
    else {
        if (y < root->info.y) return cariNode(root->left, x, y);
        else return cariNode(root->right, x, y);
    }
}

address findMin(address root) {
    while (root->left != NIL) {
        root = root->left;
    }
    return root;
}

address deleteNode(address root, int x, int y) {
    if (root == NIL) return root;

    if (x < root->info.x) root->left = deleteNode(root->left, x, y);
    else if(x > root->info.x) root->right = deleteNode(root->right, x, y);
    else {
        if (y < root->info.y) root->left = deleteNode(root->left, x, y);
        else if (y > root->info.y) root->right = deleteNode(root->right, x, y);
        
        // kalo si node itu cuma punya maksimal 1 anak.
        if (root->left == NIL) {
            address temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NIL) {
            address temp = root->left;
            delete root;
            return temp;
        }

        // kalo si node punya 2 anak
        address temp = findMin(root->right); // bakal cari elm kecil di right-nya
        root->info = temp->info;
        root->right = deleteNode(root->right, temp->info.x, temp->info.y);
    }
    return root;
}