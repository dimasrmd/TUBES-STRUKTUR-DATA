#include <windows.h>
#include "Assets/serpentIntroFrames.h"
#include "Assets/orbMeledakFrames1.h"
#include "Assets/orbMeledakFrames2.h"
#include "Assets/headMeledakFrames.h"
#include "Assets/nullFrames.h"
#include "Assets/gameOverFrames.h"
#include "Assets/pintuMunculFrames.h"
#include "BattleSystem.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>  // Untuk shuffle
#include <random>  // Untuk shuffle
#include <cstdlib>    // Untuk srand dan rand
#include <ctime>      // Untuk time (random seed)

using namespace std;

// --- LOAD SOAL ---
vector<Question> loadQuestions() {
    vector<Question> q;
    q.push_back({"Kompleksitas waktu terburuk menghapus elemen TERAKHIR Singly Linked List (hanya punya head)?", "O(1)", "O(log n)", "O(n)", "O(n log n)", 'C'});
    q.push_back({"Apa keunggulan utama Doubly Linked List dibanding Singly?", "Memori lebih sedikit", "Bisa telusuri depan & belakang", "Pencarian O(log n)", "Tidak butuh NULL", 'B'});
    q.push_back({"Dalam Circular Linked List, pointer 'next' node terakhir menunjuk ke...?", "NULL", "Node tengah", "Node pertama (Head)", "Dirinya sendiri", 'C'});
    q.push_back({"Teknik paling efisien menemukan node TENGAH dalam satu kali penelusuran?", "Hitung total bagi dua", "Dua pointer (Slow & Fast)", "Rekursif", "Salin ke Array", 'B'});
    q.push_back({"Operasi manakah yang memiliki kompleksitas waktu O(1) pada Singly Linked List?", "Menambah node di awal (Prepend)", "Menghapus node berdasarkan nilai", "Mencari nilai (Search)", "Menghapus node di akhir", 'A'});
    q.push_back({"Apa yang terjadi jika kita tidak memperbarui pointer 'head' saat menyisipkan node baru di posisi paling depan?", "Node baru akan otomatis terhubung ke node terakhir", "List akan mengalami kebocoran memori (memory leak)", "Node baru tidak akan dianggap sebagai bagian dari list saat traversal dari awal", "Program akan langsung berhenti (crash)", 'C'});
    q.push_back({"Algoritma Floyd's Cycle-Finding (sering disebut algoritma Kura-kura dan Kelinci) digunakan untuk mendeteksi apa pada Linked List?", "Node yang memiliki nilai duplikat", "Keberadaan siklus (loop) di dalam list", "Panjang total dari list", "Node yang tidak terhubung ke head", 'B'});
    q.push_back({"Berapa banyak pointer yang perlu diubah untuk menghapus node di tengah-tengah pada Doubly Linked List?", "1", "2", "3", "4", 'B'});
    q.push_back({"Apa kelemahan utama Linked List dibandingkan dengan Array?", "Ukurannya tetap (fixed size)", "Tidak mendukung akses acak (random access) berdasarkan indeks", "Proses penyisipan elemen selalu lambat", "Memerlukan blok memori yang harus berurutan (contiguously)", 'B'});
    q.push_back({"Jika Anda ingin mengimplementasikan struktur data Stack menggunakan Linked List, di posisi mana operasi Push dan Pop paling efisien dilakukan?", "Di bagian akhir (Tail)", "Di bagian awal (Head)", "Di posisi acak", "Di bagian tengah", 'B'});
    q.push_back({"Kondisi manakah yang menunjukkan bahwa sebuah Singly Linked List kosong?", "head.next == NULL", "head == NULL", "head.data == 0", "head.data == NULL", 'B'});
    q.push_back({"Mengapa Doubly Linked List membutuhkan memori lebih banyak daripada Singly Linked List?", "Karena menyimpan data dua kali lipat", "Karena setiap node menyimpan dua pointer (prev dan next)", "Karena memerlukan node dummy di setiap sisipan", "Karena ukurannya selalu dua kali lipat dari Singly Linked List", 'B'});
    q.push_back({"Apa risiko utama saat melakukan operasi penghapusan node pada Linked List dalam bahasa pemrograman yang tidak memiliki Garbage Collection (seperti C++)?", "Stack Overflow", "Segmentation Fault saat akses berikutnya", "Kebocoran memori (Memory Leak) jika memori node tidak dibebaskan", "Data otomatis terhapus secara permanen dari hardisk", 'C'});
    q.push_back({"Operasi manakah yang membutuhkan penelusuran (traversal) seluruh list pada Singly Linked List?", "Mendapatkan elemen pertama", "Menghapus elemen setelah node tertentu yang sudah diketahui", "Membalikkan urutan seluruh list (Reverse)", "Mengubah nilai data pada node head", 'C'});
    q.push_back({"Apa fungsi dari 'Dummy Node' atau 'Sentinel Node' dalam implementasi Linked List?", "Untuk menyimpan cadangan data jika list rusak", "Menyederhanakan kode dengan menghindari pengecekan kondisi khusus (seperti list kosong atau operasi di head)", "Mempercepat proses pencarian data hingga 50%", "Menghubungkan dua linked list yang berbeda secara otomatis", 'B'});
    
    return q;
}

// ==========================================
// 1. FUNGSI CUTSCENE INTRO (NAGA MUNCUL)
// ==========================================
void serpentIntroductionCutscene() {
    // Array frame animasi naga dari file header
    const char* introFrames[18] = {
        serpentIntroFrame1, serpentIntroFrame2, serpentIntroFrame3,
        serpentIntroFrame4, serpentIntroFrame5, serpentIntroFrame6,
        serpentIntroFrame7, serpentIntroFrame8, serpentIntroFrame9,
        serpentIntroFrame10, serpentIntroFrame11, serpentIntroFrame12,
        serpentIntroFrame13, serpentIntroFrame14, serpentIntroFrame15,
        serpentIntroFrame16, serpentIntroFrame17, serpentIntroFrame18
    };

    // Play Animasi 18 Frame
    for (int i = 0; i < 18; i++) {
        system("cls");
        cout << introFrames[i] << endl;
        Sleep(300); // Speed animasi
    }
    
    // Pause setelah frame terakhir - tunggu player tekan ENTER
    cout << "\nTekan ENTER untuk lanjut..." << endl;
    cin.ignore();
    cin.get(); // untuk membaca 1 karakter saja
    
    // === NARASI MONOLOG KARAKTER (4 BAGIAN) ===
    
    // Bagian 1
    system("cls");
    cout << "Apa... apa ini?!" << endl;
    cout << "Naga raksasa... dengan rune aneh yang bercahaya!" << endl;
    Sleep(2000);
    
    cout << "\nTekan tombol apapun untuk lanjut..." << endl;
    _getch();
    
    // Bagian 2
    system("cls");
    cout << "Tunggu... rune ini..." << endl;
    cout << "HEAD... DATA... NULL..." << endl;
    Sleep(2000);
    
    cout << "\nTekan tombol apapun untuk lanjut..." << endl;
    _getch();
    
    // Bagian 3
    system("cls");
    cout << "Ini... LINKED LIST?!" << endl;
    cout << "Struktur yang kupelajari di mata kuliah Struktur Data!" << endl;
    Sleep(2000);
    
    cout << "\nTekan tombol apapun untuk lanjut..." << endl;
    _getch();
    
    // Bagian 4
    system("cls");
    cout << "Aku harus mengingat pelajaranku..." << endl;
    cout << "Jika aku bisa memahami strukturnya..." << endl;
    cout << "mungkin aku bisa mengalahkannya!" << endl;
    Sleep(2000);
    
    cout << "\nTekan tombol apapun untuk lanjut..." << endl;
    _getch();
    
    // === REMINDER ZOOM OUT SEBELUM BATTLE ===
    system("cls");
    cout << "========================================" << endl;
    cout << "         BATTLE DIMULAI!               " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "PENTING: Zoom out terminal kamu!" << endl;
    cout << "(Ctrl + Scroll atau Ctrl + -)" << endl;
    cout << endl;
    cout << "Cutscene akan muncul saat battle." << endl;
    cout << "========================================" << endl;
    
    cout << "\nTekan tombol apapun untuk lanjut..." << endl;
    _getch();
}

void drawBattleInterface(int lives, int correctCount) {
    system("cls");
    
    // Pastikan terminal support emoji (UTF-8)
    SetConsoleOutputCP(CP_UTF8); 

    cout << "\n";
    cout << "   ╔══════════════════════════════════════════════════════╗" << endl;
    cout << "   ║                                                      ║" << endl;
    cout << "   ║  Player HP : ";
    for (int i = 0; i < 3; i++) {
        if (i < lives) cout << "❤️ ";  // Nyawa penuh
        else           cout << "💀 ";  // Nyawa hilang
    }
    cout << "                                  ║" << endl;

    cout << "   ║                                                      ║" << endl;

    cout << "   ║  Naga      : 🐲  [";
    
    for (int i = 0; i < 5; i++) {
        if (i < correctCount) cout << "💥"; // Node Hancur (Emoji ledakan)
        else                  cout << "🟢"; // Node Utuh (Emoji hijau)
    }
    cout << "]                        ║" << endl;

    cout << "   ║                                                      ║" << endl;
    cout << "   ╚══════════════════════════════════════════════════════╝" << endl;
    cout << endl;
}

// Fungsi untuk cutscene orb 1 meledak (19 frames)
void orb1MeledakCutscene() {
    const char* orb1Frames[19] = {
        orb1MeledakFrame1, orb1MeledakFrame2, orb1MeledakFrame3, orb1MeledakFrame4,
        orb1MeledakFrame5, orb1MeledakFrame6, orb1MeledakFrame7, orb1MeledakFrame8,
        orb1MeledakFrame9, orb1MeledakFrame10, orb1MeledakFrame11, orb1MeledakFrame12,
        orb1MeledakFrame13, orb1MeledakFrame14, orb1MeledakFrame15, orb1MeledakFrame16,
        orb1MeledakFrame17, orb1MeledakFrame18, orb1MeledakFrame19
    };
    
    for (int i = 0; i < 19; i++) {
        system("cls");
        cout << orb1Frames[i] << endl;
        Sleep(200); // 0.2 detik per frame (lebih cepat untuk efek ledakan)
    }
}

// Fungsi untuk cutscene orb 2 meledak (20 frames)
void orb2MeledakCutscene() {
    const char* orb2Frames[20] = {
        orb2MeledakFrame1, orb2MeledakFrame2, orb2MeledakFrame3, orb2MeledakFrame4,
        orb2MeledakFrame5, orb2MeledakFrame6, orb2MeledakFrame7, orb2MeledakFrame8,
        orb2MeledakFrame9, orb2MeledakFrame10, orb2MeledakFrame11, orb2MeledakFrame12,
        orb2MeledakFrame13, orb2MeledakFrame14, orb2MeledakFrame15, orb2MeledakFrame16,
        orb2MeledakFrame17, orb2MeledakFrame18, orb2MeledakFrame19, orb2MeledakFrame20
    };
    
    for (int i = 0; i < 20; i++) {
        system("cls");
        cout << orb2Frames[i] << endl;
        Sleep(200); // 0.2 detik per frame
    }
}

// Fungsi untuk cutscene head meledak (29 frames) 
void headMeledakCutscene() {
    const char* headFrames[29] = {
        headMeledakFrame1, headMeledakFrame2, headMeledakFrame3, headMeledakFrame4,
        headMeledakFrame5, headMeledakFrame6, headMeledakFrame7, headMeledakFrame8,
        headMeledakFrame9, headMeledakFrame10, headMeledakFrame11, headMeledakFrame12,
        headMeledakFrame13, headMeledakFrame14, headMeledakFrame15, headMeledakFrame16,
        headMeledakFrame17, headMeledakFrame18, headMeledakFrame19, headMeledakFrame20,
        headMeledakFrame21, headMeledakFrame22, headMeledakFrame23, headMeledakFrame24,
        headMeledakFrame25, headMeledakFrame26, headMeledakFrame27, headMeledakFrame28,
        headMeledakFrame29
    };
    
    for (int i = 0; i < 29; i++) {
        system("cls");
        cout << headFrames[i] << endl;
        Sleep(200); // 0.2 detik per frame
    }
}

// Fungsi untuk cutscene game over (30 frames)
void gameOverCutscene() {
    const char* gameOverFrames[30] = {
        gameOverFrame1, gameOverFrame2, gameOverFrame3, gameOverFrame4,
        gameOverFrame5, gameOverFrame6, gameOverFrame7, gameOverFrame8,
        gameOverFrame9, gameOverFrame10, gameOverFrame11, gameOverFrame12,
        gameOverFrame13, gameOverFrame14, gameOverFrame15, gameOverFrame16,
        gameOverFrame17, gameOverFrame18, gameOverFrame19, gameOverFrame20,
        gameOverFrame21, gameOverFrame22, gameOverFrame23, gameOverFrame24,
        gameOverFrame25, gameOverFrame26, gameOverFrame27, gameOverFrame28,
        gameOverFrame29, gameOverFrame30
    };
    
    for (int i = 0; i < 30; i++) {
        system("cls");
        cout << gameOverFrames[i] << endl;
        Sleep(200); // 0.2 detik per frame
    }
}

// Fungsi untuk cutscene NULL jiwa beterbangan (20 frames)
void nullJiwaCutscene() {
    const char* nullFrames[20] = {
        nullFrame1, nullFrame2, nullFrame3, nullFrame4,
        nullFrame5, nullFrame6, nullFrame7, nullFrame8,
        nullFrame9, nullFrame10, nullFrame11, nullFrame12,
        nullFrame13, nullFrame14, nullFrame15, nullFrame16,
        nullFrame17, nullFrame18, nullFrame19, nullFrame20
    };
    
    for (int i = 0; i < 20; i++) {
        system("cls");
        cout << nullFrames[i] << endl;
        Sleep(200); // 0.2 detik per frame
    }
}

// Fungsi untuk cutscene pintu muncul (29 frames)
void pintuMunculCutscene() {
    const char* pintuFrames[29] = {
        pintuFrame1, pintuFrame2, pintuFrame3, pintuFrame4,
        pintuFrame5, pintuFrame6, pintuFrame7, pintuFrame8,
        pintuFrame9, pintuFrame10, pintuFrame11, pintuFrame12,
        pintuFrame13, pintuFrame14, pintuFrame15, pintuFrame16,
        pintuFrame17, pintuFrame18, pintuFrame19, pintuFrame20,
        pintuFrame21, pintuFrame22, pintuFrame23, pintuFrame24,
        pintuFrame25, pintuFrame26, pintuFrame27, pintuFrame28,
        pintuFrame29
    };
    
    for (int i = 0; i < 29; i++) {
        system("cls");
        cout << pintuFrames[i] << endl;
        Sleep(200); // 0.2 detik per frame
    }
}

// Fungsi untuk menampilkan ending sequence setelah victory
void victoryEndingSequence() {
    // 1. Display monologue
    system("cls");
    cout << "\n\n";
    cout << "\n\nAkhirnya... naga itu sudah tidak ada lagi." << endl;
    Sleep(2000);
    cout << "\nAku bisa merasakan beban di pundakku" << endl;
    cout << "sedikit berkurang..." << endl;
    Sleep(2000);
    cout << "\nTapi..." << endl;
    Sleep(1500);
    cout << "\nAku merasa... ini belum berakhir." << endl;
    Sleep(2000);
    
    // 2. Display pintu muncul cutscene
    system("cls"); 
    cout << "\nPASTIKAN terminal sudah di-zoom out!" << endl;
    cout << "(Ctrl + Scroll atau Ctrl + -)" << endl;
    cout << "\nTekan tombol apapun untuk lanjut..." << endl;
    _getch();
    
    pintuMunculCutscene();
    
    // 3. Display "Chapter 1: Single Linked List - CLEARED"
    system("cls");
    cout << "\n\n\n\n\n\n";
    cout << "========================================" << endl;
    cout << "   Chapter 1: Single Linked List       " << endl;
    cout << "              - CLEARED -               " << endl;
    cout << "========================================" << endl;
    Sleep(3000);
    
    // 4. Display "TO BE CONTINUED..."
    system("cls");
    cout << "\n\n\n\n\n\n\n\n";
    cout << "           TO BE CONTINUED..." << endl;
    Sleep(3000);
}

// ==========================================
// 2. FUNGSI BATTLE (QUIZ LOGIC)
// ==========================================
bool startDragonBattle() {
    // Seed random number generator (hanya sekali di awal)
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    
    bool playAgain = true;
    bool kembaliMenu = true;
    
    do {
        vector<Question> questions = loadQuestions();
        random_device indikatorAcak;
        mt19937 g(indikatorAcak());
        
        // SHUFFLE SOAL agar urutan berbeda setiap kali main
        // random_shuffle(questions.begin(), questions.end());
        shuffle(questions.begin(), questions.end(), g);
        
        int lives = 3;
        int correctCount = 0;
        int currentQ = 0;

        // Loop Battle
        while (lives > 0 && correctCount < 5) {
            // Tampilkan UI Battle yang cantik
            drawBattleInterface(lives, correctCount);

            // Tampilkan Soal (Looping jika soal habis)
            int soalIndex = currentQ % questions.size();
            
            cout << "[SOAL #" << (currentQ + 1) << "]" << endl; // tadinya correctCount
            cout << questions[soalIndex].soal << endl << endl;
            cout << "A. " << questions[soalIndex].opsiA << endl;
            cout << "B. " << questions[soalIndex].opsiB << endl;
            cout << "C. " << questions[soalIndex].opsiC << endl;
            cout << "D. " << questions[soalIndex].opsiD << endl << endl;
            cout << ">> JAWABAN: ";

            // Bersihkan input buffer sebelum menunggu jawab (menghapus buffer inputan)
            while (_kbhit()) _getch();
            
            char jawab = toupper(_getch());
            cout << jawab << endl << endl;
            
            // Validasi input - hanya terima A, B, C, atau D
            if (jawab != 'A' && jawab != 'B' && jawab != 'C' && jawab != 'D') {
                cout << "[INVALID] Inputmu tidak valid! Hanya A, B, C, atau D yang diterima." << endl;
                cout << "Tekan apapun untuk coba lagi..." << endl;
                _getch();
                continue; // Ulangi soal yang sama
            }

            // --- CEK JAWABAN ---
            if (jawab == questions[soalIndex].jawabanBenar) {
                correctCount++;
                cout << "\n[BENAR] Syntax Valid!" << endl;
                Sleep(500); // Jeda dikit biar gak kaget
                
                // --- SCENE KHUSUS SAAT NODE HANCUR ---
                
                // SCENE 1: NODE PERTAMA HANCUR (2 Benar)
                if (correctCount == 2) {
                    // Reminder zoom out
                    cout << "\nPASTIKAN terminal sudah di-zoom out!" << endl;
                    cout << "(Ctrl + Scroll atau Ctrl + -)" << endl;
                    cout << "\nTekan tombol apapun untuk lanjut..." << endl;
                    _getch();
                    
                    // Play cutscene orb 1 meledak
                    orb1MeledakCutscene();
                    
                    // Text narasi setelah cutscene
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "           !!! CRITICAL HIT !!!         " << endl;
                    cout << "========================================" << endl;
                    cout << "\nKamu berhasil menghapus pointer node pertama!" << endl;
                    cout << "Tubuh naga mulai memendek..." << endl;
                    cout << "\n[SYSTEM]: Node Data 1 -> DELETED." << endl;
                    cout << "\nTekan sembarang tombol..." << endl;
                    _getch();
                } 
                // SCENE 2: NODE KEDUA HANCUR (4 Benar)
                else if (correctCount == 4) {
                    // Reminder zoom out
                    cout << "\nPASTIKAN terminal sudah di-zoom out!" << endl;
                    cout << "(Ctrl + Scroll atau Ctrl + -)" << endl;
                    cout << "\nTekan tombol apapun untuk lanjut..." << endl;
                    _getch();
                    
                    // Play cutscene orb 2 meledak
                    orb2MeledakCutscene();
                    
                    // Text narasi setelah cutscene
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "           !!! CRITICAL HIT !!!         " << endl;
                    cout << "========================================" << endl;
                    cout << "\nSatu lagi node hancur!" << endl;
                    cout << "Naga meraung kesakitan, tubuhnya tinggal kepala!" << endl;
                    cout << "\n[SYSTEM]: Node Data 2 -> DELETED." << endl;
                    cout << "\nTekan sembarang tombol..." << endl;
                    _getch();
                } 
                // SCENE 3: MENANG (5 Benar)
                else if (correctCount == 5) {
                    break; // Keluar loop, lanjut ke End Game
                } 
                else {
                    // Kalo bener biasa (1 atau 3)
                    cout << "Serangan masuk! Lanjut!" << endl;
                    Sleep(1000);
                }
                currentQ++; 

            } else {
                lives--;
                cout << "\n[SALAH] Segmentation Fault!" << endl;
                cout << "Jawaban yang benar adalah: [" << questions[soalIndex].jawabanBenar << "]" << endl;
                cout << "Kamu terkena damage! Nyawa tersisa: " << lives << " / 3" << endl;
                Sleep(2000);
                currentQ++; // Tetap ganti soal
            }
        }

        // --- END GAME CONDITIONS ---
        system("cls");
        if (correctCount >= 5) {
            // Reminder zoom out untuk victory cutscene
            cout << "\nPASTIKAN terminal sudah di-zoom out!" << endl;
            cout << "(Ctrl + Scroll atau Ctrl + -)" << endl;
            cout << "\nTekan tombol apapun untuk lanjut..." << endl;
            _getch();
            
            // VICTORY CUTSCENE
            headMeledakCutscene();
            
            // NULL JIWA CUTSCENE
            nullJiwaCutscene();
            
            // VICTORY TEXT
            system("cls");
            cout << "========================================" << endl;
            cout << "             VICTORY ACHIEVED           " << endl;
            cout << "========================================" << endl;
            cout << "\n[HEAD] Naga meledak berkeping-keping!" << endl;
            cout << "Struktur data telah berhasil dibersihkan." << endl;
            cout << "\n[SYSTEM]: MEMORY LEAK FIXED." << endl;
            Sleep(2000);
            
            // Display victory ending sequence
            victoryEndingSequence();
            
            // Setelah victory, langsung keluar dari loop (kembali ke main menu)
            playAgain = false;
            
        } else {
            // Reminder zoom out untuk game over cutscene
            cout << "\nPASTIKAN terminal sudah di-zoom out!" << endl;
            cout << "(Ctrl + Scroll atau Ctrl + -)" << endl;
            cout << "\nTekan tombol apapun untuk lanjut..." << endl;
            _getch();
            
            // GAME OVER CUTSCENE
            gameOverCutscene();
            
            // GAME OVER TEXT
            system("cls");
            cout << "========================================" << endl;
            cout << "               GAME OVER                " << endl;
            cout << "========================================" << endl;
            cout << "\nKamu gagal me-management pointer." << endl;
            cout << "Naga itu memakanmu..." << endl;
            Sleep(2000);
            
            // === PLAY AGAIN PROMPT (hanya untuk game over) ===
            cout << "\n\n========================================" << endl;
            cout << "         PLAY AGAIN?                    " << endl;
            cout << "========================================" << endl;
            cout << "\n[Y] YES - Coba lagi " << endl;
            cout << "[N] NO  - Kembali ke main menu" << endl;
            cout << "\n>> Pilihan: ";
            
            // Bersihkan buffer
            while (_kbhit()) _getch();
            
            char choice = toupper(_getch());
            cout << choice << endl;
            
            if (choice == 'Y') {
                playAgain = true;
                kembaliMenu = false;
                system("cls");
                cout << "\nMemulai ulang battle..." << endl;
                Sleep(1000);
            } else {
                playAgain = false;
                cout << "\nKembali ke main menu..." << endl;
                Sleep(1000);
            }
        }
        
    } while (playAgain);
    return kembaliMenu;
}