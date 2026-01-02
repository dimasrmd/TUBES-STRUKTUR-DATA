#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <thread> // Buat sleep (jeda waktu)
#include <chrono> // Buat hitungan detik/milidetik
#include <cstdlib> // Buat rand()
#include <ctime>   // Buat time()

using namespace std;

// Fungsi Animasi Teks Horor (Inline biar bisa dipanggil di mana aja)
inline void horrorGlitch(string teks) {
    // Loop untuk setiap huruf
    for (size_t i = 0; i < teks.length(); i++) {
        
        // Tentukan mau berapa kali 'glitch' (huruf acak) sebelum huruf asli muncul
        // Random antara 2 sampai 4 kali
        int gangguan = rand() % 3 + 2; 
        
        for (int j = 0; j < gangguan; j++) {
            // 1. Pilih karakter acak dari tabel ASCII (biar kelihatan kayak kode rusak)
            char acak = char(rand() % 94 + 33);
            
            // 2. Tampilkan karakter acak
            cout << acak << flush;
            
            // 3. Tunggu sebentar (efek cepat)
            this_thread::sleep_for(chrono::milliseconds(10 + rand() % 20));
            
            // 4. Hapus karakter acak tadi (Backspace)
            cout << "\b \b" << flush;
        }
        
        // Setelah efek glitch selesai, cetak huruf aslinya
        cout << teks[i] << flush;
        
        // Jeda sedikit antar huruf biar ada iramanya
        this_thread::sleep_for(chrono::milliseconds(20 + rand() % 40));
    }
    // Pindah baris di akhir teks
    cout << endl;
}

#endif