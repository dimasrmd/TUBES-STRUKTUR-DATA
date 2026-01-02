# 🏰 BIZARRE NIGHT AT CAMPUS: DATA STRUCTURE

> **Status:** ✅ Selesai (Finished)
> **Bahasa:** C++
> **Struktur Data:** Binary Search Tree (BST)

## 👥 Anggota Kelompok 👥
> Kelompok kecil yang memiliki keinginan untuk membuat game

| NO | Nama Anggota Kelompok | NIM | GitHub |
|:---:|:---------------------:|:---:|:------:|
| 1. | Dimas Ramadhani | 103112400065 | [Github - Dimas](https://github.com/dimasrmd) |
| 2. | Lutfi Shidqi Mardian | 103112400077 | [Github - Lutfi](https://github.com/chickenndrice) |
| 3. | Abisar Fathir | 103112400068 | [Github - Fathir](https://github.com/Sarrrrrrrrrrrrrr) |

## 📖 Deskripsi Proyek

### 🌙 Sinopsis

Kamu terbangun di sebuah lorong gelap yang asing. Kepala terasa berat, ingatan kabur. Hal terakhir yang kamu ingat adalah siang itu kamu sedang mempelajari mata kuliah Struktur Data di perpustakaan kampusmu.

Sekarang, kamu terjebak di dalam dimensi aneh yang menyerupai kampusmu—namun berbeda. Lorong-lorong yang seharusnya familiar kini terasa asing dan mencekam. Pintu-pintu terkunci dengan mekanisme misterius. Musuh yang kamu hadapi bukanlah hantu, namun adalah hal yang jauh mengerikan yang selama ini selalu menghantui di belakang kepalamu sebagai seorang Mahasiswa Teknik Informatika.

Mampukah kamu mengalahkan mereka semua dengan apa yang kamu pelajari selama satu semester pada mata kuliah Struktur Data? Pilihan ada di tanganmu.

**BIZARRE NIGHT AT CAMPUS: DATA STRUCTURE** adalah game petualangan horor berbasis teks yang menggabungkan eksplorasi, puzzle-solving, dan pertempuran berbasis pengetahuan. Kamu harus menjelajahi kampus yang terdistorsi ini, memecahkan teka-teki yang tersembunyi, dan menghadapi entitas supernatural yang menghalangi jalanmu.

Namun ada yang aneh... setiap puzzle, setiap pertempuran, semuanya terkait dengan **struktur data**. Seolah-olah dimensi ini dibentuk oleh konsep-konsep pemrograman yang kamu pelajari. Apakah ini hanya kebetulan? Atau ada sesuatu yang lebih dalam di balik semua ini?

### 📜 Plot

Protagonis kita adalah seorang mahasiswa Teknik Informatika semester 3 yang tidak disebutkan namanya. Di siang hari yang cerah, ia menghabiskan waktu berjam-jam di perpustakaan kampus, belajar mati-matian untuk menghadapi ujian Struktur Data esok hari—mata kuliah yang selama ini menjadi momok menakutkan baginya.

Tumpukan buku, catatan yang berantakan, dan layar laptop yang menyala terang menerangi wajahnya yang lelah. Linked List, Binary Tree, Stack, Queue—semua konsep itu berputar-putar di kepalanya hingga ia tidak tahan lagi. Kelelahan mengalahkannya. Kepalanya tertunduk di atas meja, dan ia tertidur.

**Ketika ia membuka mata, semuanya telah berubah.**

Perpustakaan yang tadinya ramai kini sunyi senyap. Lampu-lampu redup, lorong-lorong yang familiar kini terlihat kumuh dan menyeramkan. Ini bukan lagi dunia nyata—ini adalah **mimpi buruknya**. Sebuah manifestasi dari kelelahan mental dan ketakutannya terhadap mata kuliah yang telah menghantuinya sepanjang semester.

Di dalam mimpi ini, struktur data yang ia pelajari menjadi **hidup**. Mereka tidak lagi sekadar konsep abstrak di buku teks, melainkan monster-monster mengerikan yang menghalangi jalannya:

- **The Spectral Serpent** - Naga Linked List yang meliuk-liuk di kegelapan, representasi dari ketakutannya terhadap pointer dan traversal yang rumit.
- Dan masih banyak lagi monster struktur data yang menanti di chapter-chapter berikutnya...

Satu-satunya cara untuk mengalahkan mereka adalah dengan **menjawab serangkaian soal** yang mereka berikan dalam pertempuran—simbolisme dari usahanya mengingat kembali materi yang telah ia pelajari sebelum tertidur. Setiap jawaban benar adalah serangan, setiap jawaban salah adalah luka yang ia terima.

Mengalahkan satu monster bukan berarti semuanya selesai. Masih banyak bentuk struktur data lain yang perlu ia hadapi sebelum ia dapat terbangun dari mimpi buruknya. 

**Akankah ia berhasil mengalahkan semua ketakutannya dengan pengetahuan yang telah ia pelajari? Atau ia akan terjebak selamanya dalam labirin mimpi buruk ini?**

*To be continued...*

### 🎯 Tujuan Proyek

Di balik cerita yang mencekam, proyek ini dibuat untuk mendemonstrasikan implementasi **Binary Search Tree (BST)** dalam sistem peta game yang efisien. Berbeda dengan array 2D konvensional, BST memungkinkan pengelolaan dunia game yang luas dengan memori yang optimal—hanya menyimpan koordinat yang memiliki objek, bukan seluruh area kosong.

Setiap objek dalam game (tembok, pintu, item) adalah sebuah node dalam tree. Setiap langkah pemain melakukan pencarian di BST untuk menentukan interaksi. Ini adalah demonstrasi nyata bagaimana struktur data yang tepat dapat mengubah cara kita membangun sistem yang kompleks.

## 🎮 Fitur Utama
* **Eksplorasi Dunia Terbuka (Sederhana):** Bergerak bebas menggunakan tombol `W`, `A`, `S`, `D`.
* **Sistem Peta Dinamis:** Peta di-render secara *real-time* berdasarkan radius pandang pemain menggunakan BST.
* **Interaksi Objek:** Pemain dapat memeriksa objek (seperti buku, lukisan, atau pintu) untuk mendapatkan deskripsi atau petunjuk.
* **Visualisasi ASCII:** Menggunakan ASCII art untuk memberikan atmosfer visual pada objek tertentu (seperti buku clue atau pemandangan perpustakaan).
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
├── Assets/                      # Folder berisi ASCII Art untuk animasi dan visual game
│   ├── lorongFrames.h          # Animasi lorong
│   ├── serpentIntroFrames.h    # Intro animasi boss naga
│   ├── gameOverFrames.h        # Animasi game over
│   ├── headMeledakFrames.h     # Animasi kepala meledak
│   ├── nullFrames.h            # Frame null/placeholder
│   ├── orbMeledakFrames1.h     # Animasi orb meledak bagian 1
│   ├── orbMeledakFrames2.h     # Animasi orb meledak bagian 2
│   ├── pesanObjek.h            # ASCII art untuk pesan objek
│   ├── pintuMunculFrames.h     # Animasi pintu muncul
│   ├── transisiLorongFrames1.h # Transisi lorong bagian 1
│   ├── transisiLorongFrames2.h # Transisi lorong bagian 2
│   └── transisiLorongFrames3.h # Transisi lorong bagian 3
├── Database/                    # Library SQLite untuk sistem database
│   ├── sqlite3.h               # Header file SQLite
│   ├── sqlite3.c               # Source code SQLite
│   └── sqlite3.o               # Object file SQLite (compiled)
├── SkillTree/                   # Sistem skill tree dan karakter
│   ├── Character.h             # Header: Definisi struct karakter
│   ├── Skilltree.h             # Header: Definisi skill tree
│   ├── Skilltree.cpp           # Source: Implementasi skill tree
│   ├── effect.h                # Header: Definisi efek skill
│   ├── effect.cpp              # Source: Implementasi efek skill
│   └── Utilitas.h              # Header: Fungsi utility untuk skill tree
├── bstNode.h                    # Header: Definisi pointer dan struct BST
├── bstNode.cpp                  # Source: Implementasi primitif BST (Insert, Search)
├── database.h                   # Header: Definisi fungsi database SQLite
├── database.cpp                 # Source: Implementasi query SQL (Save/Load)
├── gameplay.h                   # Header: Definisi logika game
├── gameplay.cpp                 # Source: Implementasi core loop, render map, interaksi
├── BattleSystem.h               # Header: Definisi sistem battle
├── BattleSystem.cpp             # Source: Implementasi mechanics battle & quiz
├── main_game.cpp                # Main Program (Player Edition)
├── main_developer.cpp           # Main Program (Developer/Admin Edition)
└──  README.md                    # Dokumentasi proyek (file ini)
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
g++ -o game main_game.cpp gameplay.cpp BattleSystem.cpp bstNode.cpp database.cpp SkillTree/Skilltree.cpp SkillTree/effect.cpp Database/sqlite3.o -std=c++17 -lws2_32
```
Jalankan program:
```bash
./game
```

### 2. COMPILE MODE DEVELOPER (Admin)
Untuk menjalankan mode developer (menambah/edit objek peta):
```bash
g++ -o developer main_developer.cpp gameplay.cpp BattleSystem.cpp bstNode.cpp database.cpp SkillTree/Skilltree.cpp SkillTree/effect.cpp Database/sqlite3.o -std=c++17 -lws2_32
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
