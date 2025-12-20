#include "gameplay.h"
#include "pesanObjek.h"
#include  "Skilltree.h"
// --gameplay.h--
// variabel global kunci
bool kunciDimiliki = false;

// --gameplay.h--
// variabel global info ruangan
// 1 = Perpustakaan, 2 = Lorong Kampus
int ruanganAktif = 1;

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
    
    // --- Menambahkan Rak Buku (Tembok internal) ---
    buatNodeTembok(root, -5, -5, -5, 5); // Rak Kiri
    buatNodeTembok(root, 5, -5, 5, 5);  // Rak Kanan
    
    // --- Objek PENTING ---
    // Objek 1: Kunci yang harus ditemukan (*)
    root = insert(root, 6, 6, "Kunci", "Anda menemukan KUNCI EMAS!", false);
    
    // Objek 3: Pesan Awal
    root = insert(root, 0, 0, "Pesan", "Anda di dalam perpustakaan. Cari kunci (X=6, Y=6) dan Pintu (X=7, Y=0) untuk keluar!", false);
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
        x = 0; y = 0;
    } else if (tujuan == 2) {
        buatLorongKampus(root);
        // Spawn point di lorong (kiri agak masuk)
        x = -10; y = 0;
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

void mulaiBermain(address &root, int radiusPandang, SkillNode* SkillRoot) {

    int playerLevel = 150;
    int x = 0, y = 0;
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
        if (kunciDimiliki) cout << "Kunci Emas";
        else cout << "Kosong";
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
                menuSkillTree(SkillRoot);
            } else {
                pesanObj = "SKill tree terkunci....(Kill The BEAST to unlock)";
            } 
            continue;
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

        // --- Interaksi PINTU bergantung ruangan aktif dan nama pintu ---
        if (namaObjekLangkah == "Pintu" || namaObjekLangkah == "PintuPerpustakaan" || namaObjekLangkah == "PintuRuangKelas" || namaObjekLangkah == "PintuKeluar") {
            // Perilaku berbeda bergantung pada nama pintu dan ruangan aktif
            if (ruanganAktif == 1 && (namaObjekLangkah == "Pintu" || namaObjekLangkah == "PintuPerpustakaan")) {
                // Ini pintu perpustakaan -> pindah ke lorong (ruangan 2) bila kunci dimiliki
                if (kunciDimiliki) {
                    // Pesan transisi
                    system("cls");
                    cout << "Anda membuka pintu perpustakaan dan keluar..." << endl;
                    cout << "Tekan tombol apa saja untuk melanjutkan ke Lorong Kampus." << endl;
                    _getch();

                    // pindah ke ruangan 2 (Lorong)
                    pindahKeRuangan(root, langkahX, langkahY, 2);

                    // set posisi player ke spawn ruangan baru
                    x = langkahX;
                    y = langkahY;

                    // lanjut loop untuk render ruangan baru
                    continue;
                } else {
                    // pintu terkunci - bersifat penghalang jika dilewati==true
                    pesanObj = "Pintu terkunci. Temukan kunci terlebih dahulu!";
                    // tidak bergerak
                }
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