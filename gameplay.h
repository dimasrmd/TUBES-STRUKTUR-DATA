#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "bstNode.h"
#include "database.h"
#include "pesanObjek.h"
#include "Skilltree/Utilitas.h"
#include "Skilltree/Character.h"
#include "Skilltree/effect.h"
#include "Skilltree/Skilltree.h"
#include <iostream>
#include <conio.h>

using namespace std;

// ============= Global Variables =============
extern bool kunciDimiliki;
extern bool aksesPerpustakaanTerbuka;
extern int ruanganAktif;
extern int profil;
extern int totalProfil;

// ============= Map Functions =============
bool apakahTembok(address root, int x, int y);
bool apakahObject(address root, int posisiX, int posisiY);
string cekPesanObj(address root, int x, int y);
string cariNamaObj(address root, int x, int y);
void ubahPropertiNode(address root, int x, int y, bool statusBaruDilewati, string pesanBaru);

// ============= Display Functions =============
void gambarPeta(address root, int posisiX, int posisiY, int radiusPandang);
void tampilkanTempatSampah();
void tampilkanArtPerpustakaan();
void tampilkanArtClue(int nomorClue);

// ============= Map Building =============
void buatNodeTembok(address &root, int xAwal, int yAwal, int xAkhir, int yAkhir);
void buatRakBuku(address &root, int xAwal, int yAwal, int xAkhir, int yAkhir, string pesan);
void inisialisasiPetaPerpustakaan(address &root);
void buatLorongKampus(address &root);
void pindahKeRuangan(address &root, int &x, int &y, int tujuan);

// ============= Settings & Developer =============
void lihatSetting(address &root, int &radiusPandang);
void menuDeveloper(address &root);
void inputTembok(address &root);
void inputObject(address &root);

// ============= Profile System =============
void buatUsername(int &profil);
void menuProfil(int &profil);

// ============= Main Gameplay =============
// Updated signature - sekarang menerima SkillNode sebagai parameter
void mulaiBermain(address &root, int radiusPandang, int &profil, SkillNode* skillRoot, CharacterStats* playerStats);

// ============= Initialize Skill Tree =============
// Function baru untuk initialize default skills
void initializeDefaultSkills(SkillNode*& root);

#endif