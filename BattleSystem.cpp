#include <windows.h>
#include "serpentIntroFrames.h"
#include "BattleSystem.h"
#include <iostream>
#include <conio.h>
#include <vector>

using namespace std;

// --- LOAD SOAL (Sama seperti sebelumnya) ---
vector<Question> loadQuestions() {
    vector<Question> q;
    q.push_back({"Kompleksitas waktu terburuk menghapus elemen TERAKHIR Singly Linked List (hanya punya head)?", "O(1)", "O(log n)", "O(n)", "O(n log n)", 'C'});
    q.push_back({"Apa keunggulan utama Doubly Linked List dibanding Singly?", "Memori lebih sedikit", "Bisa telusuri depan & belakang", "Pencarian O(log n)", "Tidak butuh NULL", 'B'});
    q.push_back({"Dalam Circular Linked List, pointer 'next' node terakhir menunjuk ke...?", "NULL", "Node tengah", "Node pertama (Head)", "Dirinya sendiri", 'C'});
    q.push_back({"Teknik paling efisien menemukan node TENGAH dalam satu kali penelusuran?", "Hitung total bagi dua", "Dua pointer (Slow & Fast)", "Rekursif", "Salin ke Array", 'B'});
    q.push_back({"Operasi manakah yang memiliki kompleksitas waktu O(1) pada Singly Linked List?", "Menambah node di awal (Prepend)", "Menghapus node berdasarkan nilai", "Mencari nilai (Search)", "Menghapus node di akhir", 'A'});
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
    cin.get();
    
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
    cout << "                   ║" << endl;

    cout << "   ║                                                      ║" << endl;

    cout << "   ║  Naga      : 🐲  [";
    
    for (int i = 0; i < 5; i++) {
        if (i < correctCount) cout << "💥"; // Node Hancur (Emoji ledakan)
        else                  cout << "🟢"; // Node Utuh (Emoji hijau)
    }
    cout << "]           ║" << endl;

    cout << "   ║                                                      ║" << endl;
    cout << "   ╚══════════════════════════════════════════════════════╝" << endl;
    cout << endl;
}

// ==========================================
// 2. FUNGSI BATTLE (QUIZ LOGIC)
// ==========================================
void startDragonBattle() {
    vector<Question> questions = loadQuestions();
    int lives = 3;
    int correctCount = 0;
    int currentQ = 0;

    // Loop Battle
    while (lives > 0 && correctCount < 5) {
        // Tampilkan UI Battle yang cantik
        drawBattleInterface(lives, correctCount);

        // Tampilkan Soal (Looping jika soal habis)
        int soalIndex = currentQ % questions.size();
        
        cout << "[SOAL #" << (correctCount + 1) << "]" << endl;
        cout << questions[soalIndex].soal << endl << endl;
        cout << "A. " << questions[soalIndex].opsiA << endl;
        cout << "B. " << questions[soalIndex].opsiB << endl;
        cout << "C. " << questions[soalIndex].opsiC << endl;
        cout << "D. " << questions[soalIndex].opsiD << endl << endl;
        cout << ">> JAWABAN: ";

        // Bersihkan input buffer sebelum menunggu jawab
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
        // VICTORY SCENE
        cout << "========================================" << endl;
        cout << "             VICTORY ACHIEVED           " << endl;
        cout << "========================================" << endl;
        cout << "\n[HEAD] Naga meledak berkeping-keping!" << endl;
        cout << "Struktur data telah berhasil dibersihkan." << endl;
        cout << "\n[SYSTEM]: MEMORY LEAK FIXED." << endl;
        Sleep(2000);
    } else {
        // GAME OVER SCENE
        cout << "========================================" << endl;
        cout << "               GAME OVER                " << endl;
        cout << "========================================" << endl;
        cout << "\nKamu gagal me-management pointer." << endl;
        cout << "Naga itu memakanmu..." << endl;
        Sleep(2000);
    }
    
    cout << "\nTekan tombol apapun untuk lanjut..." << endl;
    while (_kbhit()) _getch(); // Bersihkan buffer
    _getch();
}