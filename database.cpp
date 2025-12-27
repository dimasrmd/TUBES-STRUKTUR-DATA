#include "database.h"

string ambilWaktu() {
    time_t waktu = time(0);

    tm *waktuSekarang = localtime(&waktu);

    char buffer[80];

    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", waktuSekarang);

    return string(buffer);
}

void buatDatabase(sqlite3* data) {
    char* pesan; // wadah untuk pesan dari database
    if (sqlite3_open("dataPemain.db", &data) != SQLITE_OK) {  
        // untuk inisialisasi database dan memastikan database dapat dibuka
        return;
    }
   
    sqlite3_exec(data, "PRAGMA foreign_keys = ON;", NULL, 0, &pesan); // mengaktifkan FK
    string createTablePemain = "CREATE TABLE IF NOT EXISTS pemain("
                        "ID INTEGER PRIMARY KEY AUTOINCREMENT, " // nyimpen id
                        "USERNAME TEXT NOT NULL, " // nyimpen username khsusus
                        "X INT NOT NULL, " // nyimpen posisi x terakhir
                        "Y INT NOT NULL, " // nyimpen y terakhir
                        "KUNCI BOOL NOT NULL, " // nyimpen kunci terakhir
                        "RUANGAN_AKTIF INT NOT NULL, " // nyimpen ruangan terakhir
                        "WAKTU_LOGIN TEXT NOT NULL);"; // nyimpen ruangan terakhir           
    sqlite3_exec(data, createTablePemain.c_str(), NULL, 0, &pesan); // buat tabelnya

    string createTableProgress = "CREATE TABLE IF NOT EXISTS progress_player("
                                "ID_PROG INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "ID_PEMAIN INTEGER NOT NULL, "
                                "INTERAKSI_LORONG INT NOT NULL, " // 0 untuk false, 1 untuk true
                                "AKSES_PERPUS INT NOT NULL, "
                                "FOREIGN KEY(ID_PEMAIN) REFERENCES pemain(ID) ON DELETE CASCADE);";
                                // ON DELTE CASCADE, kalau ada id di tabel pemain terhapus, maka data yang tersambung
                                // ke tabel progress juga terhapus
    sqlite3_exec(data, createTableProgress.c_str(), NULL, 0, &pesan);
}

void insertDataPemain(sqlite3* data, string usn, int &profil) {
    int X = 0; // agar saat mulai berada di posisi x adalah 0
    int Y = 0; // agar saat mulai berada di posisi y adalah 0
    bool kunci = false; // default belum punya kunci
    int ruanganAktif = 1; // 1 untuk perpustakaan (default kalo baru buat akun)
    char* pesanData; // untuk nyimpen feedback dari database nya
    string waktu = ambilWaktu();

    // jangan lupa kalo mau buat querry yang non-string jadiin string dulu
    string querry = "INSERT INTO pemain (USERNAME, X, Y, KUNCI, RUANGAN_AKTIF, WAKTU_LOGIN) VALUES ('"
                    + usn + "', " 
                    + to_string(X) + ", " 
                    + to_string(Y) + ", " 
                    + to_string(kunci) + ", " 
                    + to_string(ruanganAktif) + ", '"
                    + waktu + "');";

    int status = sqlite3_exec(data, querry.c_str(), NULL, 0, &pesanData);

    if (status != SQLITE_OK) {// jika status selain 0, maka querry ada yang salah karena 0 adalah querry berhasil
        cout << "Gagal insert pemain: " << pesanData << endl;
        sqlite3_free(pesanData); // untuk membebaskan memori pada penggunaan variabel pesanData
    }

    int trg_lorong = 0;
    int aksesPerpus = 0;
    char* pesanDataProg; // untuk nyimpen feedback dari database nya
    int idBaru = (int)sqlite3_last_insert_rowid(data);
    profil = idBaru;

    string querryProgress = "INSERT INTO progress_player (ID_PEMAIN, INTERAKSI_LORONG, AKSES_PERPUS) VALUES ("
                    + to_string(idBaru) + ", "
                    + to_string(trg_lorong) + ", "
                    + to_string(aksesPerpus) + ");";

    int statusProg = sqlite3_exec(data, querryProgress.c_str(), NULL, 0, &pesanDataProg);
    if (pesanDataProg != SQLITE_OK) {
        cout << "Gagal menyimpan progress: " << pesanDataProg << endl;
        sqlite3_free(pesanDataProg);
    } else {
        cout << "Pemain dan progress baru berhasil dibuat!" << endl;
    }
}

void ambilData(sqlite3* data, int profil, int &x, int &y, bool &kunci, int &ruanganAktif, int &trg_lorong, int &aksesPerpus) {
    sqlite3_stmt* statement;
    
    // 1. Susun SQL SELECT
    // Kita minta data X, Y, KUNCI, dan RUANGAN_AKTIF khusus untuk ID (profil) tersebut
    // string query = "SELECT X, Y, KUNCI, RUANGAN_AKTIF FROM pemain WHERE ID = " + to_string(profil) + ";";
    string query = "SELECT p.X, p.Y, p.KUNCI, p.RUANGAN_AKTIF, pp.INTERAKSI_LORONG, pp.AKSES_PERPUS from progress_player AS pp "
                    "INNER JOIN pemain AS p ON pp.ID_PEMAIN = p.ID "
                    "WHERE p.ID = " + to_string(profil) + ";";

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
        trg_lorong = sqlite3_column_int(statement, 4);
        aksesPerpus = sqlite3_column_int(statement, 5);
        
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

void tampilkanDaftarPemain(sqlite3* data) {
    sqlite3_stmt* statement;
    string ruangan;
    string query = "SELECT ID, USERNAME, RUANGAN_AKTIF, WAKTU_LOGIN FROM pemain;";
    
    // Prepare statement
    if (sqlite3_prepare_v2(data, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        cout << setfill('=') << setw(70) << "" << endl;
        cout << setfill(' ');
        
        cout << left << setw(5) << "ID" << left << setw(10) << "nama" << left << setw(20) << "Ruangan Terakhir" << left <<  setw(35) << "Last Login" << "" << endl;
        
        cout << setfill('-') << setw(70) << "" << endl;
        cout << setfill(' ');
        
        bool adaPemain = false;
        while (sqlite3_step(statement) == SQLITE_ROW) {
            adaPemain = true;
            int id = sqlite3_column_int(statement, 0);
            const unsigned char* username = sqlite3_column_text(statement, 1);
            int ruanganAktif = sqlite3_column_int(statement, 2);
            const unsigned char* waktu = sqlite3_column_text(statement, 3);
            if (ruanganAktif == 1) ruangan = "PERPUSTAKAAN";
            else if (ruanganAktif == 2) ruangan = "LORONG";
            else ruangan = "BELUM MASUK RUANGAN";
            cout << left << setw(5) << id << left << setw(10) << username << left << setw(20) << ruangan << left << setw(35) << waktu << endl;
            
            // cout << id << ". " << username << endl;
        }
        
        if (!adaPemain) {
            cout << "(Belum ada pemain)" << endl;
        }
        cout << setfill('=') << setw(70) << "" << endl;
        cout << setfill(' ');
    } else {
        cout << "Gagal mengambil daftar pemain: " << sqlite3_errmsg(data) << endl;
    }
    
    sqlite3_finalize(statement);
}

bool cekIdPemain(int idCari) {
    sqlite3* data;
    sqlite3_stmt* statement;
    bool ketemu = false; // Anggap default-nya tidak ketemu

    // 1. Buka Database
    if (sqlite3_open("dataPemain.db", &data) == SQLITE_OK) {
        
        // 2. Query sederhana: Coba ambil ID-nya saja
        string query = "SELECT ID FROM pemain WHERE ID = " + /*ubah int ke string*/ to_string(idCari) + ";";

        if (sqlite3_prepare_v2(data, query.c_str(), -1, &statement, NULL) == SQLITE_OK) { // mengecek apakah queerynya benar atau tidak
            
            // 3. Cek hasil step
            // Jika SQLITE_ROW, berarti ada datanya (baris ditemukan)
            if (sqlite3_step(statement) == SQLITE_ROW) {
                ketemu = true;
            }
        }
        sqlite3_finalize(statement); // Bersihkan statement
    }
    
    sqlite3_close(data); // Tutup database
    return ketemu;
}

void updateDataPemain(sqlite3* data, int idPemain, int x, int y, int ruanganAktif, bool kunci, int trg_lorong, int aksesPerpus) {
    char* pesanError;
    string waktu = ambilWaktu();

    if (sqlite3_open("dataPemain.db", &data) == SQLITE_OK) {

        string query = "UPDATE pemain SET X = " 
                        + to_string(x) 
                        + ", Y = " + to_string(y)
                        + ", RUANGAN_AKTIF = " + to_string(ruanganAktif)
                        + ", KUNCI = " + to_string(kunci)
                        + ", WAKTU_LOGIN = '" + waktu
                        + "' WHERE ID = " + to_string(idPemain) + ";";
        
        int status = sqlite3_exec(data, query.c_str(), NULL, 0, &pesanError);

        if (status != SQLITE_OK) {
            cout << "Gagal menyimpan progress: " << pesanError << endl;
            sqlite3_free(pesanError);
        }
        
        char* pesanErrorProg;
        string queryProgress = "UPDATE progress_player SET INTERAKSI_LORONG = " 
                        + to_string(trg_lorong) 
                        + ", AKSES_PERPUS = " + to_string(aksesPerpus)
                        + " WHERE ID_PEMAIN = " + to_string(idPemain) + ";";
        
        int statusProg = sqlite3_exec(data, queryProgress.c_str(), NULL, 0, &pesanErrorProg);

        if (statusProg != SQLITE_OK) {
            cout << "Gagal menyimpan progress: " << pesanErrorProg << endl;
            sqlite3_free(pesanErrorProg);
        }

        sqlite3_close(data);
    } else {
        cout << "Gagal membuka database untuk menyimpan!" << endl;
    }
}