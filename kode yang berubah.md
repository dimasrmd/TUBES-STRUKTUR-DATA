# 🔧 Dokumentasi Detail Perubahan Kode

> **Dokumentasi teknis detail untuk semua perubahan kode**

---

## 📁 Perubahan Per File

### 1. BattleSystem.cpp

#### **Fungsi:** `startDragonBattle()`
**Lokasi:** Baris 340-823

#### **Perubahan 1: Alur Pemilihan Skill (Baris 408-476)**

**Konteks:**
Bagian ini menangani logika ketika pengguna memilih skill ('S') dalam menu battle.

**Before:**
```cpp
if (skillChoice > 0) {
    // ... skill activation code ...
    activeSkill = selectedSkill->data.namaSkill;
    skillUsedThisTurn = true;
}

cout << "\nTekan tombol apapun untuk kembali ke soal...";
_getch();
continue; // Ulangi loop untuk tampilkan soal lagi
```

**After:**
```cpp
if (skillChoice > 0) {
    // ... skill activation code ...
    activeSkill = selectedSkill->data.namaSkill;
    skillUsedThisTurn = true;
    
    // Setelah skill diaktifkan, langsung lanjut ke soal
    cout << "\nTekan tombol apapun untuk melihat soal...";
    _getch();
    // Tidak ada continue, langsung lanjut ke bagian soal di bawah
} else {
    // Jika skillChoice == 0 (skip), kembali ke menu
    continue;
}
```

**Dampak:**
- **Sebelum:** Pengguna harus kembali ke menu battle → pilih 'A' → baru melihat soal
- **Sesudah:** Pengguna langsung melihat soal setelah skill diaktifkan

**Error Handling:**
```cpp
// Jika skill points tidak cukup
if (playerStats.battleSkillPoints < selectedSkill->data.skillPointCost) {
    // ... error message ...
    continue; // Kembali ke menu battle
}

// Jika skill tidak ditemukan
if (selectedSkill == nullptr) {
    // ... error message ...
    continue; // Kembali ke menu battle
}
```

**Diagram Alur:**

**Sebelum:**
```
Pengguna pilih 'S' 
  → Lihat skill 
  → Pilih skill 
  → Skill diaktifkan 
  → "Tekan untuk kembali ke soal" 
  → [CONTINUE] 
  → Kembali ke menu battle (A/S) 
  → Pengguna pilih 'A' 
  → Soal muncul
```

**Sesudah:**
```
Pengguna pilih 'S' 
  → Lihat skill 
  → Pilih skill 
  → Skill diaktifkan 
  → "Tekan untuk melihat soal" 
  → [TIDAK ADA CONTINUE] 
  → Soal langsung muncul
```

**Alur Kode:**
```cpp
if (battleMenuChoice == 'S') {
    // ... pemilihan skill ...
    if (skillChoice > 0 && skillActivated) {
        // TIDAK ADA CONTINUE DI SINI - langsung lanjut ke soal
    } else {
        continue; // Error atau skip → kembali ke menu
    }
}

// Bagian soal (Baris 470+)
// Tampilkan Soal
int soalIndex = currentQ % questions.size();
cout << "[SOAL #" << (currentQ + 1) << "]" << endl;
// ... sisa tampilan soal ...
```

---

### 2. README.md

#### **Perubahan: Format Tabel (Baris 10-14)**

**Before:**
```markdown
| NO | Nama Anggota Kelompok | NIM | GitHUb |
| :---: | :---: | :---: | :---: |
```

**After:**
```markdown
| NO | Nama Anggota Kelompok | NIM | GitHub |
|:---:|:---------------------:|:---:|:------:|
```

**Perubahan:**
1. **Perbaikan Typo:** `GitHUb` → `GitHub`
2. **Alignment:** 
   - Sebelum: `:---:` (tengah, tapi spacing tidak konsisten)
   - Sesudah: `:---:` dengan alignment lebar kolom yang tepat
3. **Lebar Kolom:** Disesuaikan untuk keterbacaan yang lebih baik

**Sintaks Tabel Markdown:**
- `:---:` = Alignment tengah
- `:---` = Alignment kiri  
- `---:` = Alignment kanan
- `---` = Default (biasanya kiri)

---

## 🔍 Detail Teknis

### BattleSystem.cpp - Analisis Alur Kontrol

#### **Alur Asli:**
```cpp
while (lives > 0 && correctCount < 5) {
    drawBattleInterface(lives, correctCount);
    
    // Menu battle
    cout << "A - Jawab Pertanyaan" << endl;
    cout << "S - Lihat Lifeline/Skill" << endl;
    
    char battleMenuChoice = toupper(_getch());
    
    if (battleMenuChoice == 'S') {
        // ... skill selection ...
        continue; // ← MASALAH: Kembali ke awal loop
    }
    
    // Tampilkan soal
    // ...
}
```

#### **Alur Baru:**
```cpp
while (lives > 0 && correctCount < 5) {
    drawBattleInterface(lives, correctCount);
    
    // Menu battle
    cout << "A - Jawab Pertanyaan" << endl;
    cout << "S - Lihat Lifeline/Skill" << endl;
    
    char battleMenuChoice = toupper(_getch());
    
    if (battleMenuChoice == 'S') {
        // ... skill selection ...
        if (skillActivated) {
            // NO CONTINUE - langsung lanjut ke soal
        } else {
            continue; // Error → kembali ke menu
        }
    }
    
    // Tampilkan soal (langsung dieksekusi jika skill diaktifkan)
    // ...
}
```

### Variabel Kunci:

```cpp
string activeSkill = "";           // Nama skill yang aktif
bool skillUsedThisTurn = false;    // Flag apakah skill digunakan
```

**Penggunaan:**
- `activeSkill`: Menyimpan nama skill untuk menampilkan efek
- `skillUsedThisTurn`: Flag untuk menentukan apakah efek skill harus ditampilkan

---

## 🧪 Skenario Pengujian

### Kasus Uji 1: Pemilihan Skill Normal
**Input:** Pengguna pilih 'S' → Pilih skill 1 → Skill points cukup  
**Ekspektasi:** Skill diaktifkan → Pertanyaan langsung muncul  
**Hasil:** ✅ LULUS

### Kasus Uji 2: Skill Points Tidak Cukup
**Input:** Pengguna pilih 'S' → Pilih skill 1 → Skill points tidak cukup  
**Ekspektasi:** Pesan error → Kembali ke menu battle  
**Hasil:** ✅ LULUS

### Kasus Uji 3: Pilihan Skill Tidak Valid
**Input:** Pengguna pilih 'S' → Pilih skill yang tidak ada  
**Ekspektasi:** Pesan error → Kembali ke menu battle  
**Hasil:** ✅ LULUS

### Kasus Uji 4: Skip Skill
**Input:** Pengguna pilih 'S' → Pilih 0 (skip)  
**Ekspektasi:** Kembali ke menu battle  
**Hasil:** ✅ LULUS

### Kasus Uji 5: Jawab Langsung (Tanpa Skill)
**Input:** Pengguna pilih 'A' langsung  
**Ekspektasi:** Pertanyaan langsung muncul  
**Hasil:** ✅ LULUS (perilaku tidak berubah)

---

## 📊 Metrik Kode

### BattleSystem.cpp:
- **Baris yang Diubah:** ~15 baris
- **Fungsi yang Dimodifikasi:** 1 (`startDragonBattle()`)
- **Kompleksitas:** Tidak meningkat (logika sama, alur lebih baik)
- **Breaking Changes:** Tidak ada

### README.md:
- **Baris yang Diubah:** 2 baris
- **Hanya Formatting:** Ya
- **Breaking Changes:** Tidak ada

---

## 🔐 Keamanan & Validasi

### Validasi Input:
```cpp
// Validasi pilihan skill
if (skillInput >= '0' && skillInput <= '9') {
    skillChoice = skillInput - '0';
} else {
    skillChoice = -1; // Input tidak valid
}

// Validasi skill points
if (playerStats.battleSkillPoints >= selectedSkill->data.skillPointCost) {
    // Lanjutkan aktivasi
} else {
    // Error: skill points tidak cukup
}
```

### Pengecekan Null:
```cpp
if (selectedSkill != nullptr) {
    // Aman untuk menggunakan selectedSkill
} else {
    // Error: skill tidak ditemukan
}
```

---

## 📝 Komentar Kode

### Komentar yang Ditambahkan:
```cpp
// Setelah skill diaktifkan, langsung lanjut ke soal
cout << "\nTekan tombol apapun untuk melihat soal...";
_getch();
// Tidak ada continue, langsung lanjut ke bagian soal di bawah
```

### Komentar yang Sudah Ada (Dipertahankan):
```cpp
// Mark skill sebagai digunakan untuk soal ini
activeSkill = selectedSkill->data.namaSkill;
skillUsedThisTurn = true;
```

---

## 🚨 Masalah Potensial & Solusi

### Masalah 1: Bagaimana jika pengguna ingin menggunakan beberapa skill?
**Perilaku Saat Ini:** Pengguna harus menjawab soal dulu, baru bisa pilih skill lagi di soal berikutnya  
**Solusi:** Implementasi saat ini sudah benar - satu skill per pertanyaan

### Masalah 2: Bagaimana jika efek skill tidak diterapkan?
**Perilaku Saat Ini:** Efek skill diterapkan segera ketika skill diaktifkan  
**Solusi:** Efek diterapkan di blok aktivasi skill (Baris 424-438)

### Masalah 3: Pembersihan buffer
**Perilaku Saat Ini:** Input buffer dibersihkan sebelum mendapatkan pilihan skill  
**Solusi:** Sudah ditangani dengan `while (_kbhit()) _getch();`

---

## 📚 File Terkait

### File yang Mungkin Terpengaruh:
1. **BattleSystem.h** - Tidak perlu perubahan (tanda tangan fungsi tidak berubah)
2. **gameplay.cpp** - Tidak perlu perubahan (battle system terpisah)
3. **main_game.cpp** - Tidak perlu perubahan (battle system terpisah)

### Dependensi:
- `SkillTree/Skilltree.h` - Untuk `SkillNode` dan `displayAvailableLifelines()`
- `SkillTree/Character.h` - Untuk `CharacterStats` dan `applyCharacterEffect()`
- `SkillTree/effect.h` - Untuk struct `effect` dan tipe `ACTIVE`

---

## ✅ Checklist Verifikasi

- [x] Kode dikompilasi tanpa error
- [x] Tidak ada error linting
- [x] Alur logika benar
- [x] Penanganan error lengkap
- [x] Pengalaman pengguna meningkat
- [x] Tidak ada breaking changes
- [x] Komentar jelas
- [x] Kode mengikuti gaya yang ada

---

**Terakhir Diperbarui:** Sesi Terakhir  
**Status Dokumentasi:** ✅ Lengkap

