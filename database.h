#ifndef DATABASE_H
#define DATABASE_H

#include "Database/sqlite3.h"
#include <iostream>
using namespace std;

// --database.h--
// > fungsi untuk membuat database
void buatDatabase(sqlite3* data);

// --database.h--
// > fungsi untuk memasukkan data ke database
void insertDataPemain(sqlite3* data, string usn, int &profil);

// --database.h--
// > fungsi untuk memasukkan data ke database
void ambilData(sqlite3* data, int profil, int &x, int &y, bool &kunci, int &ruanganAktif);

// --file database.h--
// Fungsi untuk menghitung total data pemain
int hitungJumlahPemain(sqlite3* data);

// --file database.h--
// Fungsi untuk menampilkan daftar pemain
void tampilkanDaftarPemain(sqlite3* data);

#endif