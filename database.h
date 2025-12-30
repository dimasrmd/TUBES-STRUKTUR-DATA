#ifndef DATABASE_H
#define DATABASE_H

#include "Database/sqlite3.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// --file database.h--
// Fungsi untuk mendapatkan waktu komputer
string ambilWaktu();

// --database.h--
// > fungsi untuk membuat database
void buatDatabasePemain(sqlite3* data);

// --database.h--
// > fungsi untuk membuat database
void buatDatabaseDeveloper(sqlite3* data);

// --database.h--
// > fungsi untuk memasukkan data ke database
void insertDataPemain(sqlite3* data, string usn, int &profil);

// --database.h--
// > fungsi untuk memasukkan data ke database
void ambilData(sqlite3* data, int profil, int &x, int &y,  int &ruanganAktif, int &trg_lorong, int &aksesPerpus);

// --file database.h--
// Fungsi untuk update data
void updateDataPemain(sqlite3* data, int idPemain, int x, int y, int ruanganAktif, int trg_lorong, int aksesPerpus);

// --file database.h--
// Fungsi untuk menghitung total data pemain
int hitungJumlahPemain(sqlite3* data);

// --file database.h--
// Fungsi untuk menampilkan daftar pemain
void tampilkanDaftarPemain(sqlite3* data);

// --file database.h--
// Fungsi untuk mengecek id yang dicari
bool cekIdPemain(int idCari);

// --file database.h--
// Fungsi untuk mengecek id yang dicari
bool cekDupeNama(string cariNama);

// --file database.h--
// Fungsi untuk input akun developer
void insertAccDeveloper(string username, string password);

// --file database.h--
// Fungsi untuk mengecek akun developer
bool cekAccDeveloper(string username, string password);
#endif