#include "gameplay.h"
#include "pesanObjek.h"
#include <conio.h>

// --- DEFINISI VARIABEL GLOBAL ---
bool kunciDimiliki = false;
bool aksesPerpustakaanTerbuka = false;
int ruanganAktif = 1;
int profil = 0;       
int totalProfil = 0;  

// ==========================================
// FUNGSI BANTUAN DATABASE & PROFIL
// ==========================================

void buatUsername(int &profil) {
    sqlite3* data;
    string usn;

    int status = sqlite3_open("dataPemain.db", &data);
    if (status != SQLITE_OK) {
        cout << "Gagal membuka database!" << endl;
        return;
    }
    
    cout << "Masukkan username: ";
    cin.ignore();
    getline(cin, usn);
    if (usn.empty()) {
        cout << "Username tidak boleh kosong!" << endl;
        sqlite3_close(data); 
        return;
    }
    insertDataPemain(data, usn, profil); 
    sqlite3_close(data);
}

void menuProfil(int &profil) {
    sqlite3* data;
    int pilihanMenu;

    if(sqlite3_open("dataPemain.db", &data) == SQLITE_OK){
        totalProfil = hitungJumlahPemain(data);
        sqlite3_close(data); 
    }
    system("cls");
    cout << "==================================" << endl;
    cout << "         PEMBUATAN PROFIL    " << endl;
    cout << "==================================" << endl;
    if (totalProfil == 0) {
        do {
            cout << "Tidak ada profil yang sudah dibuat!" << endl;
            cout << "1. Buat akun baru" << endl;
            cout << "2. Kembali" << endl;
            cout << "> ";
            cin >> pilihanMenu; 
            
            switch (pilihanMenu)
            {
            case 1:
                buatUsername(profil);
                totalProfil++;
                break;
            case 2:
                cout << "Tekan apapun untuk lanjut...";
                _getch();
                break;
            default:
                break;
            }
        } while (pilihanMenu > 2); 
    } else { 
        if (profil == 0) profil = 1; 
        cout << "PROFIL DITEMUKAN (Total: " << totalProfil << ")" << endl;
        cout << "Menggunakan Profil ID: " << profil << endl;
        cout << "KLIK UNTUK LANJUT" << endl;
        _getch();
    }
}

// ==========================================
// LOGIKA GAMEPLAY & MAP
// ==========================================

bool apakahTembok(address root, int x, int y) {
    if (root == NIL) return false;
    if (root->x == x && root->y == y) return root->tembus; 
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

string cariNamaObj(address root, int x, int y) {
    address node = cariNode(root, x, y);
    if (node != NIL) return node->nama;
    return "";
}

// --- DISPLAY ART ---
void tampilkanTempatSampah() {
    system("cls");
    cout << trash << std::endl; 
    cout << "\n(Tempat sampah?)\n";
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

void gambarPeta(address root, int posisiX, int posisiY, int radiusPandang) {
    for (int y = posisiY + radiusPandang; y >= posisiY - radiusPandang; y--) {
        for (int x = posisiX - radiusPandang; x <= posisiX + radiusPandang; x++) {
            
            if (x == posisiX && y == posisiY) {
                cout << "P ";
                continue;
            } 
            
            if (apakahObject(root, x, y)) {
                string namaObjek = cariNamaObj(root, x, y);
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
            else if (apakahTembok(root, x, y)) { 
                cout << "# ";
            } 
            else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

// --- BUILDER MAP ---
void buatNodeTembok(address &root, int xAwal, int yAwal, int xAkhir, int yAkhir) {
    for (int y = yAwal; y <= yAkhir; y++) {
        for (int x = xAwal; x <= xAkhir; x++) {
            root = insert(root, x, y, "Tembok", "AWAS! Ada tembok!", true);
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
    root = insert(root, BATAS, 0, "Pintu", "Pintu terkunci. Temukan Kunci!", true);
    buatNodeTembok(root, -BATAS, -BATAS, BATAS, -BATAS); 
    buatNodeTembok(root, -BATAS, BATAS, BATAS, BATAS);  
    buatNodeTembok(root, -BATAS, -BATAS, -BATAS, BATAS); 
    buatNodeTembok(root, BATAS, -BATAS, BATAS, BATAS);  
    
    // Clues
    root = insert(root, -5, 3, "BukuClue1", "Buku 'Sejarah 4 Penjuru Mata Angin'.", true);
    root = insert(root, -3, -2, "BukuClue2", "Buku '8 Keajaiban Dunia'.", true);
    root = insert(root, 1, 4, "BukuClue3", "Buku 'Biografi Presiden Ke-2'.", true);
    root = insert(root, 3, -3, "BukuClue4", "Buku '6 Langkah Menuju Sukses'.", true);

    // Rak Buku
    buatRakBuku(root, -5, -5, -5, -1, "Area Sejarah");
    buatRakBuku(root, -5, 1, -5, 5, "Area Sejarah");
    buatRakBuku(root, -3, -5, -3, -1, "Area Bahasa");
    buatRakBuku(root, -3, 1, -3, 5, "Area Bahasa");
    buatRakBuku(root, -1, -5, -1, -1, "Area Sains");
    buatRakBuku(root, -1, 1, -1, 5, "Area Sains");
    buatRakBuku(root, 1, -5, 1, -1, "Area Matematika");
    buatRakBuku(root, 1, 1, 1, 5, "Area Matematika");
    buatRakBuku(root, 3, -5, 3, -1, "Area Fiksi");
    buatRakBuku(root, 3, 1, 3, 5, "Area Fiksi");
    buatRakBuku(root, 5, -5, 5, -1, "Area Umum");
    buatRakBuku(root, 5, 1, 5, 5, "Area Umum");
    
    // Objek Penting
    root = insert(root, 6, 0, "Panel", "Panel akses pintu.", false);
    root = insert(root, 0, 0, "Pesan", "Cari petunjuk!", false);
    root = insert(root, 4, 0, "Lukisan", "Sebuah karya seni misterius.", false);
}

void buatLorongKampus(address &root) {
    root = NIL;
    const int BATAS = 12;
    root = insert(root, -BATAS, 0, "PintuPerpustakaan", "Pintu menuju Perpustakaan.", false);
    root = insert(root, BATAS, 0, "PintuRuangKelas", "Pintu menuju Ruang Kelas A. Terkunci.", true);

    buatNodeTembok(root, -BATAS, -BATAS, BATAS, -BATAS);
    buatNodeTembok(root, -BATAS, BATAS, BATAS, BATAS);
    buatNodeTembok(root, -BATAS, -BATAS, -BATAS, BATAS);
    buatNodeTembok(root, BATAS, -BATAS, BATAS, BATAS);

    root = insert(root, -3, 1, "Poster", "Poster acara kampus.", false);
    root = insert(root, 4, -1, "Tempat Sampah", "Tempat sampah kosong.", false);
    root = insert(root, 0, 2, "PesanLorong", "Anda di lorong kampus.", false);
}

void pindahKeRuangan(address &root, int &x, int &y, int tujuan) {
    ruanganAktif = tujuan;
    if (tujuan == 1) {
        inisialisasiPetaPerpustakaan(root);
        x = 6; y = 0;
    } else if (tujuan == 2) {
        buatLorongKampus(root);
        x = -11; y = 0;
    }
}

// --- MENU SETTING & DEV ---
void inputTembok(address &root) {
    int xAwal, xAkhir, yAwal, yAkhir, temp;
    system("cls");
    cout << "Input xAwal: "; cin >> xAwal;
    cout << "Input yAwal: "; cin >> yAwal;
    cout << "Input xAkhir: "; cin >> xAkhir;
    cout << "Input yAkhir: "; cin >> yAkhir;
    if (xAwal > xAkhir) { temp = xAwal; xAwal = xAkhir; xAkhir = temp; }
    if (yAwal > yAkhir) { temp = yAwal; yAwal = yAkhir; yAkhir = temp; }
    buatNodeTembok(root, xAwal, yAwal, xAkhir, yAkhir);
}

void inputObject(address &root) {
    root = insert(root, 0, -2, "Bunga", "NIH BUNGA BUAT KAMU", false); 
}

void menuDeveloper(address &root) {
    int pil;
    do {
        system("cls");
        cout << "1. Tambah Tembok\n2. Tambah Object\n3. Keluar\nPilih: ";
        cin >> pil;
        if(pil==1) inputTembok(root);
        else if(pil==2) inputObject(root);
    } while (pil != 3);
}

void lihatSetting(address &root, int &radiusPandang) {
    int pil;
    do {
        system("cls");
        cout << "Setting Radius (" << radiusPandang << ")\n1. Ubah\n2. Dev Mode\n3. Keluar\nPilih: ";
        cin >> pil;
        if(pil==1) { cout<<"Radius: "; cin>>radiusPandang; }
        else if(pil==2) menuDeveloper(root);
    } while (pil != 3);
}

// ==========================================
// CORE GAME LOOP
// ==========================================

void mulaiBermain(address &root, int radiusPandang, int &profil, SkillNode* skillRoot, CharacterStats* playerStats) {
    sqlite3* data;
    int x = 0; 
    int y = 0;

    if (playerStats == nullptr) {
        playerStats = new CharacterStats();
        playerStats->health = 100;
        playerStats->maxHealth = 100;
        playerStats->morale = 50;
        playerStats->maxMorale = 100;
        playerStats->availableSkillPoints = 5;
        playerStats->playerLevel = 1;
    }
    
    // Pastikan database terbuka untuk load posisi
    int dbStatus = sqlite3_open("dataPemain.db", &data);
    if(dbStatus == SQLITE_OK) {
        ambilData(data, profil, x, y, kunciDimiliki, ruanganAktif);
        sqlite3_close(data);
    } else {
        cout << "Warning: Gagal load data database. Menggunakan default." << endl;
    }

    // Inisialisasi Peta berdasarkan data load
    if (ruanganAktif == 1) { 
        inisialisasiPetaPerpustakaan(root);
        if(x==0 && y==0) { x=0; y=0; }
    }
    else if (ruanganAktif == 2) { 
        buatLorongKampus(root);
        if(x==0 && y==0) { x=-10; y=0; }
    }

    bool masihBermain = true;
    char pilihanBermain;
    string pesanObj;
    
    do {
        system("cls");
        cout << "======== RUANGAN " << ruanganAktif << " ========" << endl;
        cout << "Posisi: " << x << ", " << y << endl;
        
        // Menampilkan Stat dari playerStats
        cout << "HP: " << playerStats->health << "/" << playerStats->maxHealth 
             << " | Morale: " << playerStats->morale << "/" << playerStats->maxMorale 
             << " | SP: " << playerStats->availableSkillPoints << endl;
        
        cout << "------------------------------------------" << endl;
        gambarPeta(root, x, y, radiusPandang);
        
        if (!pesanObj.empty()) cout << "\n> INFO: " << pesanObj;
        pesanObj = ""; 

        cout << "\n\n[W/A/S/D] Gerak | [K] Skill Tree | [X] Keluar Menu: ";
        pilihanBermain = static_cast<char>(_getch());
        
        int langkahX = x;
        int langkahY = y;
        
        // Kontrol
        switch (pilihanBermain) {
            case 'w': langkahY++; break;
            case 's': langkahY--; break;
            case 'a': langkahX--; break;
            case 'd': langkahX++; break;
            case 'k':
                if (playerStats->playerLevel >= 1) {
                    menuSkillTree(skillRoot,playerStats);
                } else {
                    pesanObj = "Skill tree terkunci.";
                }
                continue; 
            case 'x': masihBermain = false; break;
        }

        if (!masihBermain) break;
        
        string namaObjekLangkah = cariNamaObj(root, langkahX, langkahY);
        string pesanTemp = cekPesanObj(root, langkahX, langkahY);
        
        // Cek Tembok
        if (!apakahTembok(root, langkahX, langkahY)) {
            x = langkahX;
            y = langkahY;
            if (!pesanTemp.empty()) pesanObj = pesanTemp;
        } else {
             pesanObj = "Ada tembok menghalangi!";
        }

        // --- INTERAKSI KHUSUS ---
        if (ruanganAktif == 2 && namaObjekLangkah == "Tempat Sampah") {
            tampilkanTempatSampah();
            pesanObj = "Kosong melompong.";
        }
        if (ruanganAktif == 1 && namaObjekLangkah == "Lukisan") {
            tampilkanArtPerpustakaan();
            pesanObj = "Seram sekali lukisannya.";
        }
        if (namaObjekLangkah.find("BukuClue") != string::npos) {
            if (namaObjekLangkah == "BukuClue1") tampilkanArtClue(1);
            else if (namaObjekLangkah == "BukuClue2") tampilkanArtClue(2);
            else if (namaObjekLangkah == "BukuClue3") tampilkanArtClue(3);
            else if (namaObjekLangkah == "BukuClue4") tampilkanArtClue(4);
            pesanObj = "Petunjuk ditemukan!";
        }

        // Panel Pintu
        if (ruanganAktif == 1 && namaObjekLangkah == "Panel") {
             if (aksesPerpustakaanTerbuka) {
                 cout << "\nPintu sudah terbuka! Pindah ruangan..." << endl;
                 _getch();
                 pindahKeRuangan(root, x, y, 2); 
             } else {
                system("cls");
                cout << "=== MASUKKAN PASSCODE 4 DIGIT ===" << endl;
                string inputKode = "";
                char ch;
                while(true) {
                    ch = _getch();
                    if(ch == 13) break; 
                    if(ch == 8) { if(!inputKode.empty()) { cout << "\b \b"; inputKode.pop_back(); } }
                    else { cout << "*"; inputKode += ch; }
                }
                
                if (inputKode == "4826") {
                    aksesPerpustakaanTerbuka = true;
                    cout << "\nAKSES DITERIMA!" << endl;
                    _getch();
                    pindahKeRuangan(root, x, y, 2);
                } else {
                    pesanObj = "Password Salah!";
                }
             }
        }

        if (namaObjekLangkah == "PintuPerpustakaan" && ruanganAktif == 2) {
             pindahKeRuangan(root, x, y, 1);
        }

    } while (masihBermain);
}

void initializeDefaultSkills(SkillNode*& root) {
    // ===== INTELLECT SKILLS =====
    Skill logic;
    logic.namaSkill = "Logic";
    logic.kategori = "INTELLECT";
    logic.level = 0;
    logic.expCost[0] = 10;
    logic.expCost[1] = 20;
    logic.expCost[2] = 30;
    logic.effects = nullptr;
    addeffect(logic.effects, "Clear Mind", "Boost puzzle solving", PASSIVE, "INTELLECT", 1);
    insertSkill(root, logic);
    
    // ===== PSYCHE SKILLS =====
    Skill empathy;
    empathy.namaSkill = "Empathy";
    empathy.kategori = "PSYCHE";
    empathy.level = 0;
    empathy.expCost[0] = 10;
    empathy.expCost[1] = 20;
    empathy.expCost[2] = 30;
    empathy.effects = nullptr;
    addeffect(empathy.effects, "Emotional Insight", "Sense hidden truths", PASSIVE, "PSYCHE", 1);
    insertSkill(root, empathy);
    
    // ===== PHYSIQUE SKILLS =====
    Skill endurance;
    endurance.namaSkill = "Endurance";
    endurance.kategori = "PHYSIQUE";
    endurance.level = 0;
    endurance.expCost[0] = 10;
    endurance.expCost[1] = 20;
    endurance.expCost[2] = 30;
    endurance.effects = nullptr;
    addeffect(endurance.effects, "Tough Body", "More health", PASSIVE, "MAX_HEALTH", 5);
    insertSkill(root, endurance);
    
    // ===== MOTORICS SKILLS =====
    Skill perception;
    perception.namaSkill = "Perception";
    perception.kategori = "MOTORICS";
    perception.level = 0;
    perception.expCost[0] = 10;
    perception.expCost[1] = 20;
    perception.expCost[2] = 30;
    perception.effects = nullptr;
    addeffect(perception.effects, "Sharp Eyes", "Notice details", PASSIVE, "MOTORICS", 1);
    insertSkill(root, perception);
}