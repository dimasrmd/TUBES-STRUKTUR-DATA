# 🏰 Campus Mystery: Text-Based Adventure Game

> **Status:** ✅ Selesai (Finished)
> **Bahasa:** C++
> **Struktur Data:** Binary Search Tree (BST)

## 👥 Anggota Kelompok 👥
> Kelompok kecil yang memiliki keinginan untuk membuat game

| NO | Nama Anggota Kelompok | NIM | GitHUb |
| :---: | :---: | :---: | :---: |
| 1. | Dimas Ramadhani | 103112400065 | [Github - Dimas](https://github.com/dimasrmd) |
| 2. | Lutfi Shidqi Mardian | 103112400077 | [Github - Lutfi](https://github.com/chickenndrice) |
| 3. | Abisar Fathir | 103112400068 | [Github - Fathir](https://github.com/Sarrrrrrrrrrrrrr) |

## 📖 Deskripsi Proyek
**Campus Mystery** adalah game petualangan berbasis teks (console) dengan nuansa horor/misteri. Pemain terjebak di dalam lingkungan kampus (dimulai dari Perpustakaan) dan harus mencari petunjuk, memecahkan teka-teki, dan menemukan jalan keluar.

Proyek ini dibuat untuk mendemonstrasikan implementasi struktur data **Binary Search Tree (BST)** dalam pengelolaan sistem peta (mapping) game, menggantikan penggunaan Array 2D konvensional untuk efisiensi memori pada peta yang luas (sparse matrix).

## 🎮 Fitur Utama
* **Eksplorasi Dunia Terbuka (Sederhana):** Bergerak bebas menggunakan tombol `W`, `A`, `S`, `D`.
* **Sistem Peta Dinamis:** Peta di-render secara *real-time* berdasarkan radius pandang pemain menggunakan BST.
* **Interaksi Objek:** Pemain dapat memeriksa objek (seperti buku, lukisan, atau pintu) untuk mendapatkan deskripsi atau petunjuk.
* **Visualisasi ASCII:** Menggunakan seni ASCII untuk memberikan atmosfer visual pada objek tertentu (seperti buku clue atau pemandangan perpustakaan).
* **Mekanisme Puzzle:** Mencari digit password yang tersembunyi di berbagai lokasi untuk membuka pintu terkunci.
* **Turn-Based Battle System:** Melawan Boss Naga menggunakan "Knowledge Battle", dimana pemain harus menjawab pertanyaan seputar materi Kuliah (Linked List) untuk menyerang.
* **Database & Save System:** Menggunakan **SQLite** untuk menyimpan akun pemain, progress permainan (posisi terakhir, status pintu), dan data developer.
* **Developer Mode:** Mode khusus (CRUD) untuk admin/developer menambahkan objek atau tembok baru ke dalam peta secara dinamis tanpa mengubah kodingan (disimpan di database).

## 🛠️ Arsitektur Teknis (Struktur Data)

### Mengapa Binary Search Tree (BST)?
Dalam game ini, setiap objek (tembok, item, pintu) direpresentasikan sebagai sebuah **Node**. Kami menggunakan BST untuk menyimpan koordinat objek-objek tersebut.

* **Efisiensi Memori:** Berbeda dengan Array 2D yang harus mengalokasikan memori untuk area kosong, BST hanya menyimpan koordinat yang memiliki objek.
* **Pencarian Cepat:** Saat pemain bergerak ke koordinat `(x, y)`, program melakukan pencarian di Tree (Kompleksitas O(log n)) untuk menentukan apakah ada objek atau tembok di sana.

### Struktur Node (`bstNode.h`)
Setiap node dalam tree menyimpan data berikut:
```cpp
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
```

### 📂 Struktur File
```
.
├── Assets/                 # Header file berisi ASCII Art
│   ├── lorongFrames.h
│   ├── serpentIntroFrames.h
│   └── ... (Art Assets lainnya)
├── Database/               # Folder penyimpanan file database
├── bstNode.h               # Header: Definisi pointer dan struct BST
├── bstNode.cpp             # Source: Implementasi primitif BST (Insert, Search)
├── database.h              # Header: Definisi fungsi database SQLite
├── database.cpp            # Source: Implementasi query SQL (Save/Load)
├── gameplay.h              # Header: Definisi logika game
├── gameplay.cpp            # Source: Implementasi core loop, render map, interaksi
├── BattleSystem.h          # Header: Definisi sistem battle
├── BattleSystem.cpp        # Source: Implementasi mechanics battle & quiz
├── main_game.cpp           # Main Program (Player Edition)
└── main_developer.cpp      # Main Program (Developer/Admin Edition)
```

### Integrasi Database (SQLite)
Game ini menggunakan SQLite untuk memisahkan data statis dan dinamis:
- `dataPemain.db`: Menyimpan akun user (username), posisi terakhir (X, Y), dan status progress (misal: apakah pintu sudah dibuka).
- `dataDeveloper.db`: Menyimpan akun developer dan daftar seluruh objek dalam game. Ketika game mulai, program akan meload semua objek dari database ini ke dalam BST.

### 🚀 Cara Menjalankan
Prasyarat:
- Compiler C++ (GCC/G++ atau MinGW) dengan library **sqlite3** sudah terinstall.
- Terminal / Command Prompt.

Langkah-langkah
Clone repository ini:
```Bash
git clone https://github.com/dimasrmd/TUBES-STRUKTUR-DATA.git
```
Masuk ke direktori project.

### 1. COMPILE GAME UTAMA (Player)
Jalan perintah berikut di terminal:
```bash
g++ main_game.cpp gameplay.cpp bstNode.cpp database.cpp BattleSystem.cpp -o game -lsqlite3
```
Jalankan program:
```bash
./game
```

### 2. COMPILE MODE DEVELOPER (Admin)
Untuk menjalankan mode developer (menambah/edit objek peta):
```bash
g++ main_developer.cpp gameplay.cpp bstNode.cpp database.cpp BattleSystem.cpp -o developer -lsqlite3
```
Jalankan program:
```bash
./developer
```

### 🗺️ Roadmap & Status Pengembangan
Berikut adalah daftar fitur yang sudah diimplementasikan dan rencana pengembangan selanjutnya:

[x] **Core System:** Implementasi BST untuk koordinat peta.

[x] **Rendering:** Menampilkan peta dengan simbol (#, P, =) sesuai radius pandang.

[x] **Collision:** Deteksi tabrakan tembok.

[x] **Puzzle Dasar:** Panel password pintu perpustakaan dengan riddle.

[x] **Battle System:** Turn-based quiz melawan boss Naga dengan animasi ASCII art.

[x] **Database:** Integrasi SQLite untuk login, save/load progress pemain, dan manajemen objek developer.

[x] **Developer Mode:** Fitur login khusus dan input objek baru ke database.

[x] **Art:** Integrasi ASCII art untuk clue visual, cutscene, dan battle.