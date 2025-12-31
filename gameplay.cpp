#include <windows.h> // Untuk Sleep() - cutscene timing (harus di atas untuk avoid byte conflict)
#include "gameplay.h"
#include "pesanObjek.h"
#include "lorongFrames.h"
#include "transisiLorongFrames1.h"
#include "transisiLorongFrames2.h"
#include "transisiLorongFrames3.h"
#include "BattleSystem.h"

#include "Skilltree/Skilltree.h"

int ruanganAktif = 1;
int profil = 0; 
int totalProfil = 0; 


bool apakahTembok(address root, int x, int y) {
    if (root == NIL) return false;
    if (root->info.x == x && root->info.y == y) return root->info.solid; // jika dilewati true => penghalang

    if (x < root->info.x) return apakahTembok(root->left, x, y);
    else if(x > root->info.x) return apakahTembok(root->right, x, y);
    else {
        if (y < root->info.y) return apakahTembok(root->left, x, y);
        else return apakahTembok(root->right, x, y);
    }
}

bool apakahObject(address root, int posisiX, int posisiY) {
    if (root == NIL) return false;
    if (root->info.x == posisiX && root->info.y == posisiY) return true;

    if (posisiX < root->info.x) return apakahObject(root->left, posisiX, posisiY);
    else if(posisiX> root->info.x) return apakahObject(root->right, posisiX, posisiY);
    else {
        if (posisiY < root->info.y) return apakahObject(root->left, posisiX, posisiY);
        else return apakahObject(root->right, posisiX, posisiY);
    }
}

string cekPesanObj(address root, int x, int y) {
    if (root == NIL) return "";
    if (root->info.x == x && root->info.y == y) return root->info.pesan;

    if (x < root->info.x) return cekPesanObj(root->left, x, y);
    else if(x> root->info.x) return cekPesanObj(root->right, x, y);
    else {
        if (y < root->info.y) return cekPesanObj(root->left, x, y);
        else return cekPesanObj(root->right, x, y);
    }
}

void ubahPropertiNode(address root, int x, int y, bool statusBaruDilewati, string pesanBaru) {
    address node = cariNode(root, x, y);
    if (node != NIL) {
        node->info.solid = statusBaruDilewati;
        node->info.pesan = pesanBaru;
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
    
   
    playerX = 37;
    playerY = 0;
    
   
}


string cariNamaObj(address root, int x, int y) {
    address node = cariNode(root, x, y);
    if (node != NIL) return node->info.nama;
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

void buatLorongKampus(address &root, int trg_lorong) {
    root = NIL;
    
    // Lorong panjang sempit: 50 karakter panjang, lebar 3 (1 jalan tengah + 2 tembok samping)
    // Koordinat X: -11 (pintu perpustakaan) hingga 39 (pintu ujung lorong)
    // Koordinat Y: -1 (tembok bawah), 0 (jalan), 1 (tembok atas)
    
    // INSERT PINTU di ujung kiri (pintu perpustakaan - bisa dibuka)
    root = insert(root, -11, 0, "PintuPerpustakaan", "Pintu menuju Perpustakaan.", false);
    
    if (trg_lorong == 0) {
        // INSERT TRIGGER POINT untuk first-person walking di koordinat (10, 0)
        root = insert(root, 10, 0, "TriggerLorongFP", "Lorong ini sangat panjang, rasanya sangat tidak nyaman...", false);
    }
    
    // INSERT PINTU di ujung kanan (pintu terkunci)
    root = insert(root, 39, 0, "PintuUjung", "Pintu terkunci rapat.", true);
    
    // Tembok atas lorong (Y = 1, dari X = -11 hingga X = 39)
    buatNodeTembok(root, -11, 1, 39, 1);
    
    // Tembok bawah lorong (Y = -1, dari X = -11 hingga X = 39)
    buatNodeTembok(root, -11, -1, 39, -1);
}

void pindahKeRuangan(address &root, int &x, int &y, int tujuan, int trg_lorong) {
    ruanganAktif = tujuan;
    if (tujuan == 1) {
        inisialisasiPetaPerpustakaan(root);
        x = 6; y = 0;
    } else if (tujuan == 2) {
        buatLorongKampus(root, trg_lorong);
        // Spawn point di lorong (kiri agak masuk)
        x = -10; y = 0;
    }
}

bool keamananPass(string pass) {
    bool adaSimbol = false;
    bool adaHurufKecil = false;
    bool adaHurufBesar = false;
    bool adaNomor = false;

    if (pass.length() < 8) {
        return false;
    }

    for (char c : pass) {
        if (isupper(c)) adaHurufBesar = true;
        else if (islower(c)) adaHurufKecil = true;
        else if (ispunct(c)) adaSimbol = true;
        else if (isdigit(c)) adaNomor = true;
    }

    return adaSimbol && adaHurufBesar && adaHurufKecil && adaNomor;
} 

bool authDeveloper(){
    string keyWord;
    cout << "Sebutkan kata kunci nya: ";
    cin.ignore();
    getline(cin, keyWord);
    if (keyWord != "aku cinta bahlil") return false;
    cout << "\n[SYSTEM] Kata kunci diterima!..."; _getch();

    string usn, pass;
    int choise;
    char ch;
    bool ada = false;
    do {
        system("cls");
        cout << setfill('=') << setw(10) << "" << endl;
        cout << setfill(' ');
        cout << "1. Daftar\n2. Login\n3. Keluar\n";
        cout << setfill('=') << setw(10) << "" << endl;
        cout << setfill(' ');
        cout << "Pilih: "; cin >> choise;
        switch (choise)
        {
        case 1:
            system("cls");
            cout << setfill('=') << setw(8) << "" << " BUAT AKUN " << setfill('=') << setw(8) << "" << endl;
            cout << setfill(' ');
            cout << "Username: "; cin >> usn;
            cout << "Password: "; cin >> pass;
            if (keamananPass(pass) == false) {
                cout << "Password minimal ada simbol, nomor, huruf besar dan kecil, dan 8 karakter";
                _getch();
            } else {
                insertAccDeveloper(usn, pass);
                cout << "Akun berhasil dibuat! Tekan untuk lanjut..."; _getch();
            }
            break;
        case 2:
            usn = "";
            pass = "";
            system("cls");
            cout << setfill('=') << setw(8) << "" << " LOGIN AKUN " << setfill('=') << setw(8) << "" << endl;
            cout << setfill(' ');
            cout << "Username: "; cin >> usn;
            cout << "Password: ";
            while (true) {
                ch = _getch();
                if (ch == 13) break; // tombol enter
                else if (ch == 8) { // tombol backspace
                    if (!pass.empty()) {
                        pass.pop_back();
                        cout << "\b \b";
                    }
                }
                else {
                    pass.push_back(ch);
                    cout << "*";
                }
            }
            cout << endl << setfill('=') << setw(28) << ""  << endl;
            cout << setfill(' ');
            ada = cekAccDeveloper(usn, pass);

            if (ada) {
                cout << "\n[SYSTEM] Login berhasil, tekan untuk lanjut...";
            } else {
                cout << "\n[SYSTEM] Login gagal, tekan untuk lanjut...";
            }
            _getch();
            break;
        default:
            break;
        }
    } while (choise != 3 && ada == false);
    return ada;
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
            if (authDeveloper()) menuDeveloper(root);
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

int buatUsername(int &profil) {
    sqlite3* data;
    string usn;

    // --- LANGKAH 1: BUKA KONEKSI DATABASE DULU ---
    // Tanpa ini, variabel 'data' isinya sampah dan insert pasti gagal
    int status = sqlite3_open("dataPemain.db", &data);
    if (status != SQLITE_OK) {
        cout << "Gagal membuka database!" << endl;
        return 0;
    }
    // ---------------------------------------------
    
    cout << "Masukkan username: ";
    cin.ignore();
    getline(cin, usn);
    if (usn.empty()) {
        cout << "Username tidak boleh kosong!..." << endl;
        sqlite3_close(data); // Tutup dulu sebelum return
        _getch();
        return 0;
    }
    sqlite3_close(data); // kenapa di close? karena di cekDupenama ada open, open ketemu open = error
    if (cekDupeNama(usn)) {
        cout << "\n[SYSTEM]: Username " << usn << " sudah dibuat, gunakan username lain!\n";
        cout << "Tekan apapun untuk kembali ke menu...";
        _getch();
        return 0;
    }
    sqlite3_open("dataPemain.db", &data);
    insertDataPemain(data, usn, profil); // buat sekaligus memakai usn nya
    sqlite3_close(data);
    return 1;
}

int menuProfil(int &profil) {
    sqlite3* data;
    int tempProfil = 0; // untuk memilih menu & pilih id player
    bool idPlayer; // untuk mengecek id player ada atau tidak

    if(sqlite3_open("dataPemain.db", &data) == SQLITE_OK){
        // simpan hasilnya ke variabel global totalProfil
        totalProfil = hitungJumlahPemain(data);
        
        sqlite3_close(data); // Tutup lagi
    }
    if (totalProfil == 0) {
        do {
            system("cls");
            cout << "==================================" << endl;
            cout << "         PEMBUATAN PROFIL    " << endl;
            cout << "==================================" << endl;
            cout << "Tidak ada profil yang sudah dibuat!" << endl;
            cout << "1. Buat akun baru" << endl;
            cout << "2. kembali" << endl;
            cout << "-------------------------------------" << endl;
            cout << "> ";
            cin.ignore();
            cin >> tempProfil;
            switch (tempProfil)
            {
            case 1:
                buatUsername(profil);
                return 1;
                break;
            case 2:
                cout << "Tekan apapun untuk lanjut...";
                getch();
                return 0; // atinya dia tidak bisa bermain karena memilih exit
            default:
                break;
            }
        } while (tempProfil > 2); // akan ulang terus kalo inputnya selain 1 dan 2
    } else { // bakal munculin semua profil yang ada
        system("cls");
        if(sqlite3_open("dataPemain.db", &data) == SQLITE_OK){
            tampilkanDaftarPemain(data);
            sqlite3_close(data);
        }
        cout << "[0] untuk buat ID baru | Pilih ID: "; 
        cin.ignore();
        cin >> tempProfil;
        if (cin.fail()) {
            cout << "Input salah! Harap masukkan angka." << endl;
            
            // 1. Reset status error di cin agar bisa dipakai lagi
            cin.clear(); 
            
            // 2. Buang sisa input "sampah" (huruf tadi) dari memori buffer
            // numeric_limits...max() artinya "buang sebanyak mungkin karakter sampai ketemu Enter"
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return 0;
        }
        
        if (tempProfil == 0 && buatUsername(profil) == 0) return 0; // kalo dupe nama
        else if (tempProfil == 0) tempProfil = profil;
        
        // profil = tempProfil;
        idPlayer = cekIdPemain(tempProfil);
        if (idPlayer) {
            cout << "Profil ID " << tempProfil << " terpilih." << endl;
            profil = tempProfil;
            cout << "Tekan apapun untuk lanjut...";
            getch();
        } else {
            cout << "Profil ID " << tempProfil << " tidak ada." << endl;
            cout << "Tekan apapun untuk lanjut...";
            getch();
            return 0;
        }
    }
    return 1; // artinya dia bisa masuk ke fungsi mulaiBermain
}

void mulaiBermain(address &root, int radiusPandang, int &profil, SkillNode* SkillRoot) {
    int playerLevel = 150;
    sqlite3* data;
    if (sqlite3_open("dataPemain.db", &data) != SQLITE_OK) {
        cout << "Gagal membuka database saat mulai bermain!" << endl;
        return;
    }

    int x; 
    int y;
    int trg_Lorong;
    int aksesPerpustakaanTerbuka;
    ambilData(data, profil, x, y, ruanganAktif, trg_Lorong, aksesPerpustakaanTerbuka);
    sqlite3_close(data); // Close after getting data

    if (ruanganAktif == 1) inisialisasiPetaPerpustakaan(root);
    else if (ruanganAktif == 2) buatLorongKampus(root, trg_Lorong);

    // if (trg_Lorong == 0) root = insert(root, 10, 0, "TriggerLorongFP", "Lorong ini sangat panjang, rasanya sangat tidak nyaman...", false);
    
    // Pastikan spawn sesuai ruangan awal
    // if (ruanganAktif == 1) { x = 0; y = 0; }
    // else if (ruanganAktif == 2) { x = -10; y = 0; }

    bool masihBermain = true;
    char pilihanBermain;
    string pesanObj, namaRuangan;
    do {
        system("cls");
        if (ruanganAktif == 1) namaRuangan = "PERPUSTAKAAN";
        else if (ruanganAktif == 2) namaRuangan = "LORONG";
        cout << "======== PERMainan CAMPUS - RUANGAN " << namaRuangan << " ========" << endl;
        cout << "ID: " << profil << endl << endl;
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
        case 'k':
            if (playerLevel >= 2){
                // menuSkillTree(SkillRoot); SANG PEMBUAT EROR
            } else {
                pesanObj = "SKill tree terkunci....(Kill The BEAST to unlock)";
            } 
            break;
        case 'x':
            updateDataPemain(data, profil, x, y, ruanganAktif, trg_Lorong, aksesPerpustakaanTerbuka);
            masihBermain = false;
        default:
            break;
        }
 
        // Ambil pesan & nama objek di langkah target (jika ada)
        pesanObj = cekPesanObj(root, langkahX, langkahY);
        string namaObjekLangkah = cariNamaObj(root, langkahX, langkahY);
        
        // --- Interaksi Suasana di ruangan 1 ---
        if (ruanganAktif == 1 && namaObjekLangkah == "Lukisan") {
            tampilkanArtPerpustakaan();
            pesanObj = "Perpustakaan sudah kosong, seram sekali.";
        }

        // --- Interaksi CLUE ---
        if (namaObjekLangkah == "BukuClue1") { tampilkanArtClue(1); pesanObj = "Aneh sekali, aku tidak tau mereka punya buku seperti ini di perpustakaan. Pasti ini digit yang kubutuhkan."; }
        if (namaObjekLangkah == "BukuClue2") { tampilkanArtClue(2); pesanObj = "Ketemu lagi, aku harus cari sisanya.."; }
        if (namaObjekLangkah == "BukuClue3") { tampilkanArtClue(3); pesanObj = "Ini dia, aku hanya butuh satu digit lagi.."; }
        if (namaObjekLangkah == "BukuClue4") { tampilkanArtClue(4); pesanObj = "Terakhir, sekarang sudah lengkap untuk membuka password pintu."; }

        // --- Interaksi TRIGGER LORONG FIRST PERSON ---
        if (ruanganAktif == 2 && namaObjekLangkah == "TriggerLorongFP") {
            // Tampilkan pesan trigger
            system("cls");
            cout << "Lorong ini sangat panjang, rasanya sangat tidak nyaman..." << endl;
            cout << "\nTekan tombol apapun untuk melanjutkan..." << endl;
            _getch();
            
            // Aktifkan first-person walking animation
            firstPersonWalking(x, y);
            
            // Update langkahX dan langkahY agar tidak ada konflik
            langkahX = x;
            langkahY = y;
            if (trg_Lorong == 0) {
                // Hapus trigger point agar tidak bisa diaktifkan lagi
                // ubahPropertiNode(root, 10, 0, true, "");
                deleteNode(root, 10, 0);
                trg_Lorong = 1; // artinya sudah pernah ke trigger
            }
            
            pesanObj = "Syukurlah ada pintu diujung sini";
            continue; // Skip movement check
        }


        // --- Interaksi PANEL (PASSWORD) ---
        if (ruanganAktif == 1 && namaObjekLangkah == "Panel") {
            // Cek jika sudah terbuka
            if (aksesPerpustakaanTerbuka == 1) {
                // Langsung skip ke logika buka pintu
                // Kita gunakan trik 'goto' atau sekadar set inputKode = "4826" (simulasi)
                // Tapi lebih rapi kita handle di bawah atau duplikasi logika pindah
                // Opsi paling bersih:
                system("cls");
                cout << "Status: Pintu sudah TERBUKA." << endl;
                cout << "Tekan tombol apa saja untuk keluar." << endl;
                _getch();
                pindahKeRuangan(root, langkahX, langkahY, 2, trg_Lorong);
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
            } else if (aksesPerpustakaanTerbuka == 1) {
                 // Jika sudah terbuka sebelumnya, langsung lewat
                 cout << "\nAKSES DITERIMA (Tersimpan). Pintu terbuka!" << endl;
                 cout << "Tekan tombol apa saja..." << endl;
                 _getch();
                 
                  // pindah ke ruangan 2 (Lorong)
                 pindahKeRuangan(root, langkahX, langkahY, 2, trg_Lorong);
                 x = langkahX;
                 y = langkahY;
                 continue;
            } else if (inputKode == "4826") {
                aksesPerpustakaanTerbuka = 1; // Simpan status terbuka
                cout << "\nAKSES DITERIMA. Pintu terbuka!" << endl;
                cout << "Tekan tombol apa saja..." << endl;
                _getch();
                
                 // pindah ke ruangan 2 (Lorong)
                pindahKeRuangan(root, langkahX, langkahY, 2, trg_Lorong);
                x = langkahX;
                y = langkahY;
                continue;
            } else {
                pesanObj = "Akses Ditolak! Kode salah.";
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

                pindahKeRuangan(root, langkahX, langkahY, 1, trg_Lorong);
                x = langkahX;
                y = langkahY;
                continue;
            } else if (ruanganAktif == 2 && namaObjekLangkah == "PintuRuangKelas") {
                // contoh pintu ruang kelas yang terkunci
                address nodePintuKelas = cariNode(root, langkahX, langkahY);
                if (nodePintuKelas != NIL && nodePintuKelas->info.solid == true) {
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