#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "bstNode.h"
#include <cstdlib>
#include <conio.h>


// --gameplay.h--
// variabel global kunci
extern bool kunciDimiliki; // pake extern karena buat nunjukin kalo isi dari variabelnya 

// --gameplay.h--
// variabel global info ruangan
// 1 = Perpustakaan, 2 = Lorong Kampus
extern int ruanganAktif;

// --gameplay.h--
// untuk memilih profil yang akan dimainkan
extern int profil; 

// --gameplay.h--
// variabel menghitung jumlah profil yang dibuat
extern int totalProfil;

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
// function untuk menampilkan obejk tempat sampah
void tampilkanTempatSampah();

// menampilkan art di perpustakaan
void tampilkanArtPerpustakaan();

// menampilkan art clue
void tampilkanArtClue(int nomorClue);


    
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
// untuk membuat rak buku
void buatRakBuku(address &root, int xAwal, int yAwal, int xAkhir, int yAkhir, string pesan);

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

// --gameplay.h--
// untuk memilih profil yang akan dimainkan
void menuProfil(int &profil);

#endif