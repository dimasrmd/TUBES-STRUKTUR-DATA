#include "database.h"


void buatDatabase(sqlite3* data) {
    char* pesan; // wadah untuk pesan dari database
    sqlite3_open("dataPemain.db", &data); // untuk inisialisasi database
    string createTable = "CREATE TABLE IF NOT EXISTS pemain("
                        "ID INTEGER PRIMARY KEY AUTOINCREMENT, " // nyimpen id
                        "USERNAME TEXT NOT NULL, " // nyimpen username khsusus
                        "X INT NOT NULL, " // nyimpen posisi x terakhir
                        "Y INT NOT NULL, " // nyimpen y terakhir
                        "KUNCI BOOL NOT NULL, " // nyimpen kunci terakhir
                        "RUANGAN_AKTIF INT NOT NULL);"; // nyimpen ruangan terakhir

                        
    sqlite3_exec(data, createTable.c_str(), NULL, 0, &pesan); // buat tabelnya
}

void insertDataPemain(sqlite3* data, string usn, int &profil) {
    int X = 0; // agar saat mulai berada di posisi x adalah 0
    int Y = 0; // agar saat mulai berada di posisi y adalah 0
    bool kunci = false; // default belum punya kunci
    int ruanganAktif = 1; // 1 untuk perpustakaan
    char* pesanData; // untuk nyimpen feedback dari database nya

    // jangan lupa kalo mau buat querry yang non-string jadiin string dulu
    string querry = "INSERT INTO pemain (USERNAME, X, Y, KUNCI, RUANGAN_AKTIF) VALUES ('"
                    + usn + "', " 
                    + to_string(X) + ", " 
                    + to_string(Y) + ", '" 
                    + to_string(kunci) + "', " 
                    + to_string(ruanganAktif) + ");";

    int status = sqlite3_exec(data, querry.c_str(), NULL, 0, &pesanData);
    if (status != SQLITE_OK) {// jika status selain 0, maka querry ada yang salah karena 0 adalah querry berhasil
        cout << "Gagal insert pemain: " << pesanData << endl;
        sqlite3_free(pesanData); // untuk membebaskan memori pada penggunaan variabel pesanData
    } else {
        profil = (int)sqlite3_last_insert_rowid(data); // karena bawaannya adalah tipe long-long yang memiliki 8 byte maka ubah dulu ke int 4 byte
        cout << "Pemain baru berhasil dibuat!" << endl;
    }
}

void ambilData(sqlite3* data, int profil, int &x, int &y, bool &kunci, int &ruanganAktif) {
    sqlite3_stmt* statement;
    
    // 1. Susun SQL SELECT
    // Kita minta data X, Y, KUNCI, dan RUANGAN_AKTIF khusus untuk ID (profil) tersebut
    string query = "SELECT X, Y, KUNCI, RUANGAN_AKTIF FROM pemain WHERE ID = " + to_string(profil) + ";";

    // 2. Siapkan (Prepare) untuk mengecek apakah querry sudah benar atau tidak
    if(sqlite3_prepare_v2(data, query.c_str(), -1, &statement, NULL) != SQLITE_OK){
        cout << "Gagal ambil data: " << sqlite3_errmsg(data) << endl;
        return;
    }

    // 3. Jalankan (Step)
    // Pakai 'if' saja (bukan while), karena ID itu unik (datanya pasti cuma 1 baris)
    if(sqlite3_step(statement) == SQLITE_ROW){
        
        // 4. Ambil Data (Column)
        // Urutan indeks (0, 1, 2, 3) SANGAT PENTING.
        // 0 = X, 1 = Y, 2 = kunci, 3 = ruanganaktif
        
        x = sqlite3_column_int(statement, 0);
        y = sqlite3_column_int(statement, 1);
        
        // SQLite menyimpan bool sebagai integer (0 atau 1). 
        // C++ otomatis paham kalau 0=false, 1=true.
        kunci = sqlite3_column_int(statement, 2);
        ruanganAktif = sqlite3_column_int(statement, 3);
        
        // Debugging (Opsional: Cek apakah data benar-benar terambil)
        // cout << "Data loaded: Posisi(" << x << "," << y << ")" << endl;
        
    } else {
        cout << "Error: Save data tidak ditemukan untuk ID " << profil << endl;
    }

    // 5. Bersihkan (Finalize)
    sqlite3_finalize(statement);
}

int hitungJumlahPemain(sqlite3* data) {
    sqlite3_stmt* statement;
    int jumlah = 0;

    // Perintah SQL untuk menghitung total baris
    string query = "SELECT COUNT(*) FROM pemain;";

    // 1. cek querry jika 0 maka berhasil
    if(sqlite3_prepare_v2(data, query.c_str(), -1, &statement, NULL) == SQLITE_OK){
        
        // 2. Jalankan
        if(sqlite3_step(statement) == SQLITE_ROW){
            // 3. Ambil hasilnya (Angka hitungan ada di kolom 0)
            jumlah = sqlite3_column_int(statement, 0);
        }
    }

    // 4. Bersihkan memori statement
    sqlite3_finalize(statement);
    
    return jumlah; // Kembalikan angka totalnya
}