#include "gameplay.h"
#include "pesanObjek.h"
#include "Skilltree/Skilltree.h"
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
int profil = 0;       // Inisialisasi defalut
int totalProfil = 0;  // Inisialisasi defalut
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
    
    // Lorong panjang sempit: 40 karakter panjang, lebar 3 (1 jalan tengah + 2 tembok samping)
    // Koordinat X: -11 (pintu perpustakaan) hingga 29 (pintu ujung lorong)
    // Koordinat Y: -1 (tembok bawah), 0 (jalan), 1 (tembok atas)
    
    // INSERT PINTU di ujung kiri (pintu perpustakaan - bisa dibuka)
    root = insert(root, -11, 0, "PintuPerpustakaan", "Pintu menuju Perpustakaan.", false);
    
    // INSERT PINTU di ujung kanan (pintu terkunci)
    root = insert(root, 29, 0, "PintuUjung", "Pintu terkunci rapat.", true);
    
    // Tembok atas lorong (Y = 1, dari X = -11 hingga X = 29)
    buatNodeTembok(root, -11, 1, 29, 1);
    
    // Tembok bawah lorong (Y = -1, dari X = -11 hingga X = 29)
    buatNodeTembok(root, -11, -1, 29, -1);
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

void buatUsername(int &profil) {
    sqlite3* data;
    string usn;

    // --- LANGKAH 1: BUKA KONEKSI DATABASE DULU ---
    // Tanpa ini, variabel 'data' isinya sampah dan insert pasti gagal
    int status = sqlite3_open("dataPemain.db", &data);
    if (status != SQLITE_OK) {
        cout << "Gagal membuka database!" << endl;
        return;
    }
    // ---------------------------------------------
    
    cout << "Masukkan username: ";
    cin.ignore();
    getline(cin, usn);
    if (usn.empty()) {
        cout << "Username tidak boleh kosong!" << endl;
        sqlite3_close(data); // Tutup dulu sebelum return
        return;
    }
    insertDataPemain(data, usn, profil); // buat sekaligus memakai usn nya
    sqlite3_close(data);
}

void menuProfil(int &profil) {
    sqlite3* data;
    int pilihanMenu;

    if(sqlite3_open("dataPemain.db", &data) == SQLITE_OK){
        // simpan hasilnya ke variabel global totalProfil
        totalProfil = hitungJumlahPemain(data);
        
        sqlite3_close(data); // Tutup lagi
    }
    system("cls");
    cout << "==================================" << endl;
    cout << "         PEMBUATAN PROFIL    " << endl;
    cout << "==================================" << endl;
    if (totalProfil == 0) {
        do {
            cout << "Tidak ada profil yang sudah dibuat!" << endl;
            cout << "1. Buat akun baru" << endl;
            cout << "2. kembali" << endl;
            cout << "-------------------------------------" << endl;
            cout << "> ";
            cin.ignore();
            cin >> pilihanMenu;
            switch (pilihanMenu)
            {
            case 1:
                buatUsername(profil);
                totalProfil++;
                break;
            case 2:
                cout << "Tekan apapun untuk lanjut...";
                getch();
                break;
            default:
                break;
            }
        } while (pilihanMenu > 2); // akan ulang terus kalo inputnya selain 1 dan 2
    } else { // bakal munculin semua profil yang ada
        if(sqlite3_open("dataPemain.db", &data) == SQLITE_OK){
            tampilkanDaftarPemain(data);
            sqlite3_close(data);
        }
        
        cout << "PILIH OPSI:" << endl;
        cout << "1. Pilih Profil (Masukkan ID)" << endl;
        cout << "2. Buat Profil Baru" << endl;
        cout << "-------------------------------------" << endl;
        cout << "> ";
        cin >> pilihanMenu;
        
        if (pilihanMenu == 2) {
             buatUsername(profil);
             totalProfil++;
        } else {
             // Asumsi input langsung ID
             cout << "Masukkan ID Profil yang ingin dimainkan: ";
             cin >> profil;
             cout << "Profil ID " << profil << " terpilih." << endl;
             cout << "Tekan apapun untuk lanjut...";
             getch();
        }
    }
}

void mulaiBermain(address &root, int radiusPandang, int &profil, SkillNode* SkillRoot) {
    int playerLevel = 150;
    sqlite3* data;
    
    // Open database before loading data
    if (sqlite3_open("dataPemain.db", &data) != SQLITE_OK) {
        cout << "Gagal membuka database saat mulai bermain!" << endl;
        return;
    }
    
    int x; 
    int y;
    ambilData(data, profil, x, y, kunciDimiliki, ruanganAktif);
    sqlite3_close(data); // Close after getting data
    
    // Pastikan spawn sesuai ruangan awal
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