#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "bstNode.h"
#include <cstdlib>
#include <conio.h>

// --gameplay.h--
// untuk mengecek apakah koordinat tertentu tembok
bool apakahTembok(address root, int x, int y);

// --gameplay.h--
// untuk mengecek apakah koordinat tertentu objek
bool apakahObject(address root, int x, int y);

// --gameplay.h--
// untuk mengecek pesan pada objek koordinat tertentu
string cekPesanObj(address root, int x, int y);

// --gameplay.h--
// mengubah properti dari node
void ubahPropertiNode(address root, int x, int y, 
    bool statusBaruDilewati, string pesanBaru);
    
// --gameplay.h--
// fungsi untuk menampilkan obejk tempat sampah
void tampilkanTempatSampah();
    
// --gameplay.h--
// mencari nama objek dan mengembalikan variabel tipe string
string cariNamaObj(address root, int x, int y);

// --gameplay.h--
// membuat peta, x dan y adalah posisi dari player
void gambarPeta(address root, int x, 
    int y, int radiusPandang);
    
// --gameplay.h--
// untuk developer mode membuat tembok
void buatNodeTembok(address &root, int xAwal, int yAwal, int xAkhir, int yAkhir);

// --gameplay.h--
// Membuat ruangan perpustakaan
void inisialisasiPetaPerpustakaan(address &root);

// --gameplay.h--
// Membuat lorong kampus
void buatLorongKampus(address &root);

// --gameplay.h--
// Membuat lorong kampus
void pindahKeRuangan(address &root, int &x, int &y, int tujuan);

// --gameplay.h--
// Buat liat Setting
void lihatSetting(address &root, int &radiusPandang);

// --gameplay.h--
// input objek atau buat objek baru
void inputObject(address &root);

// --gameplay.h--
// yang developer developer aja
void menuDeveloper(address &root);

// --gameplay.h
// untuk input tembok manual
void inputTembok(address &root);  

// --gameplay.h--
// untuk memulai gamenya
void mulaiBermain(address &root, int radiusPandang);

#endif