#include "gameplay.h"
#include "pesanObjek.h"
#include "lorongFrames.h"
#include "transisiLorongFrames1.h"
#include "transisiLorongFrames2.h"
#include "transisiLorongFrames3.h"
#include "BattleSystem.h"

// --gameplay.h--
// variabel global kunci
// --- DEFINISI VARIABEL GLOBAL ---
bool kunciDimiliki = false;

// variabel global status pintu perpustakaan
bool aksesPerpustakaanTerbuka = false;

// --gameplay.h--
// variabel global info ruangan
// 1 = Perpustakaan, 2 = Lorong Kampus
int ruanganAktif = 1;
// -----------------------------------------------------

bool apakahTembok(address root, int x, int y) {
    if (root == NIL) return false;
    if (root->x == x && root->y == y) return root->tembus; // jika dilewati true => penghalang

    if (x < root->x) return apakahTembok(root->left, x, y);
    else if(x > root->x) return apakahTembok(root->right, x, y);
    else {
        if (y < root->y) return apakahTembok(root->left, x, y);
        else return apakahTembok(root->right, x, y);
    }
}

bool apakahObject(address root, int posisiX, int posisiY) {
    if (root == NIL) return false;
    if (root->x == posisiX && root->y == posisiY) return true;

    if (posisiX < root->x) return apakahObject(root->left, posisiX, posisiY);
    else if(posisiX> root->x) return apakahObject(root->right, posisiX, posisiY);
    else {
        if (posisiY < root->y) return apakahObject(root->left, posisiX, posisiY);
        else return apakahObject(root->right, posisiX, posisiY);
    }
}

string cekPesanObj(address root, int x, int y) {
    if (root == NIL) return "";
    if (root->x == x && root->y == y) return root->pesan;

    if (x < root->x) return cekPesanObj(root->left, x, y);
    else if(x> root->x) return cekPesanObj(root->right, x, y);
    else {
        if (y < root->y) return cekPesanObj(root->left, x, y);
        else return cekPesanObj(root->right, x, y);
    }
}

void ubahPropertiNode(address root, int x, int y, bool statusBaruDilewati, string pesanBaru) {
    address node = cariNode(root, x, y);
    if (node != NIL) {
        node->tembus = statusBaruDilewati;
        node->pesan = pesanBaru;
    }
}

void tampilkanTempatSampah() {
    system("cls");
    cout << trash << std::endl;
    cout << "\n(Tenpat sampah?)\n";
    _getch();
}

void tampilkanArtPerpustakaan() {
    system("cls");
    cout << artPerpustakaan << std::endl;
    _getch();
}

void tampilkanArtClue(int nomorClue) {
    system("cls");
    if (nomorClue == 1) cout << artClue1 << endl;
    else if (nomorClue == 2) cout << artClue2 << endl;
    else if (nomorClue == 3) cout << artClue3 << endl;
    else if (nomorClue == 4) cout << artClue4 << endl;
    
    cout << "\n(Anda menemukan petunjuk!)\n";
    _getch();
}

// Fungsi untuk cutscene membuka pintu (auto-play)
void doorOpeningCutscene() {
    // Array pointer ke semua frame cutscene (21 frames)
    const char* cutsceneFrames[21] = {
        doorFrame1, doorFrame2, doorFrame3, doorFrame4, doorFrame5,
        doorFrame6, doorFrame7, doorFrame8, doorFrame9, doorFrame10,
        doorFrame11, doorFrame12, doorFrame13, doorFrame14, doorFrame15,
        doorFrame16, doorFrame17, doorFrame18, doorFrame19, doorFrame20,
        doorFrame21
    };
    
    // Play semua frame dengan durasi berbeda
    for (int i = 0; i < 21; i++) {
        system("cls");
        cout << cutsceneFrames[i] << endl;
        
        if (i < 20) {
            Sleep(300); // Frame 1-20: 300ms (0.3 detik)
        } else {
            Sleep(5000); // Frame 21 (terakhir): 5000ms (5 detik)
        }
    }
}

// Fungsi untuk cutscene transisi (cahaya terang -> terbangun) - 72 FRAMES TOTAL
void transisiCutscene() {
    // PART 1: Frame 1-28 (dari transisiLorongFrames1.h)
    const char* part1Frames[28] = {
        transisiFrame1, transisiFrame2, transisiFrame3, transisiFrame4, transisiFrame5,
        transisiFrame6, transisiFrame7, transisiFrame8, transisiFrame9, transisiFrame10,
        transisiFrame11, transisiFrame12, transisiFrame13, transisiFrame14, transisiFrame15,
        transisiFrame16, transisiFrame17, transisiFrame18, transisiFrame19, transisiFrame20,
        transisiFrame21, transisiFrame22, transisiFrame23, transisiFrame24, transisiFrame25,
        transisiFrame26, transisiFrame27, transisiFrame28
    };
    
    // PART 2: Frame 29-44 (dari transisiLorongFrames2.h)
    const char* part2Frames[16] = {
        transisiFrame29, transisiFrame30, transisiFrame31, transisiFrame32, transisiFrame33,
        transisiFrame34, transisiFrame35, transisiFrame36, transisiFrame37, transisiFrame38,
        transisiFrame39, transisiFrame40, transisiFrame41, transisiFrame42, transisiFrame43,
        transisiFrame44
    };
    
    // PART 3: Frame 45-72 (dari transisiLorongFrames3.h)
    const char* part3Frames[28] = {
        transisiFrame45, transisiFrame46, transisiFrame47, transisiFrame48, transisiFrame49,
        transisiFrame50, transisiFrame51, transisiFrame52, transisiFrame53, transisiFrame54,
        transisiFrame55, transisiFrame56, transisiFrame57, transisiFrame58, transisiFrame59,
        transisiFrame60, transisiFrame61, transisiFrame62, transisiFrame63, transisiFrame64,
        transisiFrame65, transisiFrame66, transisiFrame67, transisiFrame68, transisiFrame69,
        transisiFrame70, transisiFrame71, transisiFrame72
    };
    
    // Play PART 1 (Frame 1-28) - 300ms per frame
    for (int i = 0; i < 28; i++) {
        system("cls");
        cout << part1Frames[i] << endl;
        Sleep(300); // 0.3 detik per frame
    }
    
    // Play PART 2 (Frame 29-44) - 300ms per frame
    for (int i = 0; i < 16; i++) {
        system("cls");
        cout << part2Frames[i] << endl;
        Sleep(300); // 0.3 detik per frame
    }
    
    // Play PART 3 (Frame 45-72) - 300ms per frame
    for (int i = 0; i < 28; i++) {
        system("cls");
        cout << part3Frames[i] << endl;
        Sleep(300); // 0.3 detik per frame
    }
}

// Fungsi untuk menampilkan animasi first-person walking
void firstPersonWalking(int &playerX, int &playerY) {
    // Array pointer ke semua frame
    const char* frames[17] = {
        lorongFrame1, lorongFrame2, lorongFrame3, lorongFrame4, lorongFrame5,
        lorongFrame6, lorongFrame7, lorongFrame8, lorongFrame9, lorongFrame10,
        lorongFrame11, lorongFrame12, lorongFrame13, lorongFrame14, lorongFrame15,
        lorongFrame16, lorongFrame17
    };
    
    int currentFrame = 0;
    char input;
    
    // Tampilkan frame pertama (tanpa instruksi)
    system("cls");
    cout << frames[currentFrame] << endl;
    
    while (currentFrame < 16) {  // 0-16 = 17 frames
        input = _getch();
        
        // Hanya terima input 'W' atau 'w'
        if (input == 'w' || input == 'W') {
            currentFrame++;
            
            // Tampilkan frame berikutnya (tanpa instruksi)
            system("cls");
            cout << frames[currentFrame] << endl;
        }
    }
    
    // Setelah frame 17, tunggu player tekan W lagi untuk trigger cutscene
while (_kbhit()) _getch(); 

    // --- EVENT LANGSUNG JALAN (TANPA WHILE LAGI) ---
    // Begitu nyampe ujung (loop jalan kelar), langsung gas event!
    
    Sleep(500); // Jeda dikit biar napas
    
    // 1. Cutscene Pintu & Transisi
    doorOpeningCutscene();
    transisiCutscene();
    
    // 2. Cutscene Naga
    serpentIntroductionCutscene();
    
    // 3. Battle Quiz
    startDragonBattle();
    
    // Setelah cutscene selesai, teleport player ke koordinat (37, 0)
    // 2 karakter di sebelah kiri pintu yang ada di (39, 0)
    playerX = 37;
    playerY = 0;
    
    // Langsung kembali ke gameplay tanpa pesan
}

string cariNamaObj(address root, int x, int y) {
    address node = cariNode(root, x, y);
    if (node != NIL) return node->nama;
    return "";
}

void gambarPeta(address root, int posisiX, int posisiY, int radiusPandang) {
    for (int y = posisiY + radiusPandang; y >= posisiY - radiusPandang; y--) {
        for (int x = posisiX - radiusPandang; x <= posisiX + radiusPandang; x++) {
            
            // 1. Posisi Player
            if (x == posisiX && y == posisiY) {
                cout << "P ";
                continue;
            } 
            
            // Cek apakah ada Node di koordinat ini
            if (apakahObject(root, x, y)) {
                string namaObjek = cariNamaObj(root, x, y);
                
                // PRIORITASKAN SIMBOL KHUSUS
                if (namaObjek == "Pintu" || namaObjek == "PintuPerpustakaan" || namaObjek == "PintuRuangKelas" || namaObjek == "PintuKeluar") {
                    cout << "= ";
                } 
                else if (namaObjek == "Tembok") {
                    cout << "# ";
                }
                else if (namaObjek == "RakBuku") {
                    cout << "||";
                }
                else {
                    cout << "* ";
                }
            }
            // 3. Cek Tembok (Hanya jika tidak ada Object/Pintu yang terdeteksi di atas)
            else if (apakahTembok(root, x, y)) { 
                cout << "# ";
            } 
            // 4. Area Kosong
            else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void buatNodeTembok(address &root, int xAwal, int yAwal, int xAkhir, int yAkhir) {
    for (int y = yAwal; y <= yAkhir; y++) {
        for (int x = xAwal; x <= xAkhir; x++) {
            root = insert(root, x, y, "Tembok", "AWAS! Ada tembok, tidak bisa lewat!", true);
        }
    }
}

void buatRakBuku(address &root, int xAwal, int yAwal, int xAkhir, int yAkhir, string pesan) {
    for (int y = yAwal; y <= yAkhir; y++) {
        for (int x = xAwal; x <= xAkhir; x++) {
            root = insert(root, x, y, "RakBuku", pesan, true);
        }
    }
}

void inisialisasiPetaPerpustakaan(address &root) {
    root = NIL;
    const int BATAS = 7; 

    // INSERT PINTU SEBELUM TEMBOK supaya tidak tertimpa tembok
    root = insert(root, BATAS, 0, "Pintu", "Pintu terkunci. Temukan Kunci!", true);

    // --- Membuat Tembok Pembatas Perpustakaan (Ukuran -7 hingga 7) ---
    buatNodeTembok(root, -BATAS, -BATAS, BATAS, -BATAS); // Bawah
    buatNodeTembok(root, -BATAS, BATAS, BATAS, BATAS);  // Atas
    buatNodeTembok(root, -BATAS, -BATAS, -BATAS, BATAS); // Kiri
    buatNodeTembok(root, BATAS, -BATAS, BATAS, BATAS);  // Kanan
    
    // --- CLUE DIGIT (Ditaruh SEBELUM rak supaya tidak tertimpa/shadowing) ---
    // statusDilewati = true supaya 'keras' seperti rak buku (tidak bisa ditembus)
    // Digit 1: 4
    root = insert(root, -5, 3, "BukuClue1", "Buku 'Sejarah 4 Penjuru Mata Angin'.", true);
    // Digit 2: 8
    root = insert(root, -3, -2, "BukuClue2", "Buku '8 Keajaiban Dunia'.", true);
    // Digit 3: 2
    root = insert(root, 1, 4, "BukuClue3", "Buku 'Biografi Presiden Ke-2'.", true);
    // Digit 4: 6
    root = insert(root, 3, -3, "BukuClue4", "Buku '6 Langkah Menuju Sukses'.", true);

    // --- Menambahkan Rak Buku (Tembok internal) ---
    // Konfigurasi: 6 kolom rak, terbelah di tengah (y=0) untuk jalan
    // Kolom X: -5, -3, -1, 1, 3, 5
    
    // Rak Kiri Luar (-5) - Sejarah
    buatRakBuku(root, -5, -5, -5, -1, "Area Sejarah: Buku-buku kuno berdebu.");
    buatRakBuku(root, -5, 1, -5, 5, "Area Sejarah: Buku-buku kuno berdebu.");

    // Rak Kiri Tengah (-3) - Bahasa
    buatRakBuku(root, -3, -5, -3, -1, "Area Bahasa: Kamus dan buku tata bahasa.");
    buatRakBuku(root, -3, 1, -3, 5, "Area Bahasa: Kamus dan buku tata bahasa.");

    // Rak Kiri Dalam (-1) - Sains
    buatRakBuku(root, -1, -5, -1, -1, "Area Sains: Ensiklopedia alam semesta.");
    buatRakBuku(root, -1, 1, -1, 5, "Area Sains: Ensiklopedia alam semesta.");

    // Rak Kanan Dalam (1) - Matematika
    buatRakBuku(root, 1, -5, 1, -1, "Area Matematika: Rumus-rumus yang memusingkan.");
    buatRakBuku(root, 1, 1, 1, 5, "Area Matematika: Rumus-rumus yang memusingkan.");

    // Rak Kanan Tengah (3) - Fiksi
    buatRakBuku(root, 3, -5, 3, -1, "Area Fiksi: Novel dan cerita rakyat.");
    buatRakBuku(root, 3, 1, 3, 5, "Area Fiksi: Novel dan cerita rakyat.");

    // Rak Kanan Luar (5) - Umum
    buatRakBuku(root, 5, -5, 5, -1, "Area Umum: Koran dan majalah.");
    buatRakBuku(root, 5, 1, 5, 5, "Area Umum: Koran dan majalah.");
    
    // --- Objek PENTING ---
    // Objek 1: Panel Pembuka Pintu
    root = insert(root, 6, 0, "Panel", "Panel akses pintu.", false);
    
    // Objek 3: Pesan Awal
    root = insert(root, 0, 0, "Pesan", "Anda di dalam perpustakaan. Pintu terkunci dengan password. Cari petunjuk di buku-buku!", false);

    // Objek 4: Lukisan Art (Interaksi Point) - DIKEMBALIKAN (Geser ke 4,0)
    root = insert(root, 4, 0, "Lukisan", "Sebuah karya seni misterius.", false);
}

void buatLorongKampus(address &root) {
    root = NIL;
    const int BATAS = 12;

    // INSERT PINTU-PIINTU SEBELUM MENAMBAHKAN TEMBOK agar tidak tertindih
    // Pintu menuju Perpustakaan (di sisi kiri)
    root = insert(root, -BATAS, 0, "PintuPerpustakaan", "Pintu menuju Perpustakaan kecil.", false); // bisa dilewati
    // Pintu ke ruang kelas di sisi kanan (tertutup untuk contoh)
    root = insert(root, BATAS, 0, "PintuRuangKelas", "Pintu menuju Ruang Kelas A. Terkunci.", true); // tertutup

    // Dinding luar lorong
    buatNodeTembok(root, -BATAS, -BATAS, BATAS, -BATAS);
    buatNodeTembok(root, -BATAS, BATAS, BATAS, BATAS);
    buatNodeTembok(root, -BATAS, -BATAS, -BATAS, BATAS);
    buatNodeTembok(root, BATAS, -BATAS, BATAS, BATAS);

    // Beberapa dekorasi / objek di lorong
    root = insert(root, -3, 1, "Poster", "Poster acara kampus terpampang.", false);
    root = insert(root, 4, -1, "Tempat Sampah", "Tempat sampah kosong.", false);

    // Pesan titik spawn/intro
    root = insert(root, 0, 2, "PesanLorong", "Anda sekarang berada di lorong kampus. Ada pintu ke ruang kelas di sebelah kanan.", false);
}

void pindahKeRuangan(address &root, int &x, int &y, int tujuan) {
    ruanganAktif = tujuan;
    if (tujuan == 1) {
        inisialisasiPetaPerpustakaan(root);
        x = 6; y = 0;
    } else if (tujuan == 2) {
        buatLorongKampus(root);
        // Spawn point di lorong (kiri agak masuk)
        x = -11; y = 0;
    }
}

void lihatSetting(address &root, int &radiusPandang) {
    int pilihanSetting;
    do {
        system("cls");
        cout << "=========================" << endl;
        cout << "         SETTING       " << endl;
        cout << "=========================" << endl;
        cout << "1. Mengubah jarak pandang. (Saat ini " << radiusPandang << " m)" << endl;
        cout << "2. Developer Mode" << endl;
        cout << "3. Keluar" << endl;
        cout << "-------------------------" << endl;
        cout << "Pilih menu (1-3): ";
        cin >> pilihanSetting;
        switch (pilihanSetting)
        {
        case 1:
            cout << "Masukkan radius yang diinginkan: ";
            cin >> radiusPandang;
            break;
        case 2:
            menuDeveloper(root);
            break;
        default:
            break;
        }
    } while (pilihanSetting != 3);
}

void inputObject(address &root) {
    root = insert(root, 0, -2, "Bunga", "NIH BUNGA BUAT KAMU", false); 
}

void menuDeveloper(address &root) {
    int pililihanDeveloper;
    do {
        system("cls");
        cout << "=========================" << endl;
        cout << "      SANG DEVELOPER    " << endl;
        cout << "=========================" << endl;
        cout << "1. Tambahin tembok" << endl;
        cout << "2. Tambahin Object" << endl;
        cout << "3. Keluar" << endl;
        cout << "-------------------------" << endl;
        cout << "Pilih menu (1-3): ";
        cin >> pililihanDeveloper;
        switch (pililihanDeveloper)
        {
        case 1:
            inputTembok(root);
            break;
        case 2:     
            inputObject(root);
            break;
        default:
            break;
        }
    } while (pililihanDeveloper != 3);
}

// Fungsi developer kecil untuk menambah tembok/object (tetap ada jika ingin)
void inputTembok(address &root) {
    int xAwal, xAkhir, yAwal, yAkhir, temp;
    system("cls");
    cout << "=========================" << endl;
    cout << "      PEMBUATAN TEMBOK    " << endl;
    cout << "=========================" << endl;
    cout << "Input xAwal: ";
    cin >> xAwal;
    cout << "Input yAwal: ";
    cin >> yAwal;
    cout << "Input xAkhir: ";
    cin >> xAkhir;
    cout << "Input yAkhir: ";
    cin >> yAkhir;
    if (xAwal > xAkhir) { temp = xAwal; xAwal = xAkhir; xAkhir = temp; }
    if (yAwal > yAkhir) { temp = yAwal; yAwal = yAkhir; yAkhir = temp; }

    buatNodeTembok(root, xAwal, yAwal, xAkhir, yAkhir);
}

void mulaiBermain(address &root, int radiusPandang) {
    int x; 
    int y;
    if (ruanganAktif == 1) { x = 0; y = 0; }
    else if (ruanganAktif == 2) { x = -10; y = 0; }

    bool masihBermain = true;
    char pilihanBermain;
    string pesanObj;
    do {
        system("cls");
        cout << "======== PERMainan CAMPUS - RUANGAN " << ruanganAktif << " ========" << endl;
        cout << "Posisi: " << x << ", " << y << endl;
        
        // --- Menampilkan Inventori ---
        cout << "Item: ";
        cout << "Pecahan Kode"; // Logic item kunci sudah dihapus
        cout << endl;
        // ------------------------------
        
        cout << "P: Player, #: Tembok, *: Objek, =: Pintu" << endl << endl;

        gambarPeta(root, x, y, radiusPandang);
        
        cout << "\n>Pesan: " << pesanObj;
        pesanObj = ""; // reset pesan

        cout << "\n>Gunakan x untuk keluar ke menu\n";
        cout << ">Gunakan (w/a/s/d) untuk bergerak\n";
        cout << ">K untuk Inventori\n";
        cout << "input: ";
        pilihanBermain = static_cast<char>(_getch());
        
        int langkahX = x;
        int langkahY = y;
        switch (pilihanBermain)
        {
        case 'w':
            langkahY++;
            break;
        case 's':
            langkahY--;
            break;
        case 'a':
            langkahX--;
            break;
        case 'd':
            langkahX++;
            break;
        case 'x':
            masihBermain = false;
        default:
            break;
        }
 
        // Ambil pesan & nama objek di langkah target (jika ada)
        pesanObj = cekPesanObj(root, langkahX, langkahY);
        string namaObjekLangkah = cariNamaObj(root, langkahX, langkahY);

        // --- Interaksi TEMPAT SAMPAH di ruangan 2 ---
        if (ruanganAktif == 2 && namaObjekLangkah == "Tempat Sampah") {
            tampilkanTempatSampah();   // <--- menampilkan ASCII
            pesanObj = "Kamu melihat sesuatu... tapi tempat sampahnya kosong.";
        }

        // --- Interaksi LUKISAN di ruangan 1 ---
        // (Dihapus karena diganti Meja)
        
        // --- Interaksi LUKISAN di ruangan 1 ---
        if (ruanganAktif == 1 && namaObjekLangkah == "Lukisan") {
            tampilkanArtPerpustakaan();
            pesanObj = "Perpustakaan sudah kosong, seram sekali.";
        }

        // --- Interaksi CLUE ---
        if (namaObjekLangkah == "BukuClue1") { tampilkanArtClue(1); pesanObj = "Aneh sekali, aku tidak tau mereka punya buku seperti ini di perpustakaan. Pasti ini digit yang kubutuhkan."; }
        if (namaObjekLangkah == "BukuClue2") { tampilkanArtClue(2); pesanObj = "Ketemu lagi, aku harus cari sisanya.."; }
        if (namaObjekLangkah == "BukuClue3") { tampilkanArtClue(3); pesanObj = "Ini dia, aku hanya butuh satu digit lagi.."; }
        if (namaObjekLangkah == "BukuClue4") { tampilkanArtClue(4); pesanObj = "Terakhir, sekarang sudah lengkap untuk membuka password pintu."; }

        // --- Interaksi PANEL (PASSWORD) ---
        if (ruanganAktif == 1 && namaObjekLangkah == "Panel") {
            // Cek jika sudah terbuka
            if (aksesPerpustakaanTerbuka) {
                // Langsung skip ke logika buka pintu
                // Kita gunakan trik 'goto' atau sekadar set inputKode = "4826" (simulasi)
                // Tapi lebih rapi kita handle di bawah atau duplikasi logika pindah
                // Opsi paling bersih:
                system("cls");
                cout << "Status: Pintu sudah TERBUKA." << endl;
                cout << "Tekan tombol apa saja untuk keluar." << endl;
                _getch();
                 pindahKeRuangan(root, langkahX, langkahY, 2);
                 x = langkahX;
                 y = langkahY;
                 continue;
            }

            system("cls");
            cout << "=== PANEL AKSES PINTU ===" << endl;
            cout << "PETUNJUK (Riddle):" << endl;
            cout << "Digit 1: Aku seringkali dilupakan, di antara debu masa lalu." << endl;
            cout << "Digit 2: Jika ingin fasih berkata-kata, temukan aku di sana." << endl;
            cout << "Digit 3: Tempat di mana angka dan rumus berkuasa." << endl;
            cout << "Digit 4: Dunia khayalan dan cerita rakyat bersembunyi di sini." << endl;
            cout << "========================" << endl;
            cout << "Masukan 4 digit kode akses (backspace untuk kembali) : ";
            
            // IMPLEMENTASI INPUT MANUAL DENGAN BACKSPACE
            string inputKode = "";
            char ch;
            bool cancelInput = false;

            while (true) {
                ch = _getch(); // Ambil input tanpa echo otomatis

                if (ch == 13) { // ENTER
                    break; 
                } else if (ch == 8) { // BACKSPACE
                    if (inputKode.length() > 0) {
                        cout << "\b \b"; // Hapus karakter di layar
                        inputKode.pop_back();
                    } else {
                        // Jika buffer kosong dan tekan backspace -> CANCEL
                        cancelInput = true;
                        break;
                    }
                } else {
                    cout << ch; // Tampilkan karakter
                    inputKode += ch;
                }
            }

            if (cancelInput) {
                 pesanObj = "Input dibatalkan.";
            } else if (aksesPerpustakaanTerbuka) {
                 // Jika sudah terbuka sebelumnya, langsung lewat
                 cout << "\nAKSES DITERIMA (Tersimpan). Pintu terbuka!" << endl;
                 cout << "Tekan tombol apa saja..." << endl;
                 _getch();
                 
                  // pindah ke ruangan 2 (Lorong)
                 pindahKeRuangan(root, langkahX, langkahY, 2);
                 x = langkahX;
                 y = langkahY;
                 continue;
            } else if (inputKode == "4826") {
                aksesPerpustakaanTerbuka = true; // Simpan status terbuka
                cout << "\nAKSES DITERIMA. Pintu terbuka!" << endl;
                cout << "Tekan tombol apa saja..." << endl;
                _getch();
                
                 // pindah ke ruangan 2 (Lorong)
                pindahKeRuangan(root, langkahX, langkahY, 2);
                x = langkahX;
                y = langkahY;
                continue;
            } else {
                pesanObj = "Akses Ditolak! Kode salah.";
            }
        }


        // --- Interaksi Umum: Kunci ---
        if (namaObjekLangkah == "Kunci") {
            if (!kunciDimiliki) {
                kunciDimiliki = true;
                pesanObj = "Anda mengambil Kunci Emas! Pintu perpustakaan sekarang bisa dibuka!";
                // jika ingin buka pintu perpustakaan otomatis
                // ubahPropertiNode(root, 7, 0, false, "Pintu terbuka! Keluar!");
            } else {
                pesanObj = "Anda sudah memiliki kunci.";
            }
        }

        // --- Interaksi PINTU ---
        if (namaObjekLangkah == "Pintu" || namaObjekLangkah == "PintuPerpustakaan" || namaObjekLangkah == "PintuRuangKelas" || namaObjekLangkah == "PintuKeluar") {
            // Perilaku berbeda bergantung pada nama pintu dan ruangan aktif
            if (ruanganAktif == 1 && (namaObjekLangkah == "Pintu" || namaObjekLangkah == "PintuPerpustakaan")) {
                 pesanObj = "Pintu terkunci secara elektronik. Gunakan Panel di sebelahnya (X=6, Y=0).";
            } else if (ruanganAktif == 2 && namaObjekLangkah == "PintuPerpustakaan") {
                // balik ke perpustakaan (mis. pintu di lorong yang menuju perpustakaan)
                system("cls");
                cout << "Anda memasuki kembali Perpustakaan..." << endl;
                cout << "Tekan tombol apa saja untuk melanjutkan." << endl;
                _getch();

                pindahKeRuangan(root, langkahX, langkahY, 1);
                x = langkahX;
                y = langkahY;
                continue;
            } else if (ruanganAktif == 2 && namaObjekLangkah == "PintuRuangKelas") {
                // contoh pintu ruang kelas yang terkunci
                address nodePintuKelas = cariNode(root, langkahX, langkahY);
                if (nodePintuKelas != NIL && nodePintuKelas->tembus == true) {
                    pesanObj = "Pintu ruang kelas terkunci.";
                } else {
                    // jika dibuka : bisa buat pindah ke ruangan lain
                    pesanObj = "Anda masuk ke Ruang Kelas A (belum diimplementasikan).";
                }
            }
        }
        
        // --- Logika Pergerakan: jika bukan tembok maka gerak ---
        if (!apakahTembok(root, langkahX, langkahY)) {
            x = langkahX;
            y = langkahY;
        } 

    } while (masihBermain);
}