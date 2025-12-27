#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "bstNode.h"
#include "database.h"
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include "Skilltree/Skilltree.h"


/*gameplay.h
**Fungsinya: kasih tau udah punya kunci atau belom di ruangan perpuastakaan
*/
extern bool kunciDimiliki;

/*gameplay.h
**Fungsinya: Indikator untuk ruangan yang sedang ditempati
*/
extern int ruanganAktif;

/*gameplay.h
**Fungsinya: sebagai pilihan dalam pemilihan user
*/
extern int profil; 

/*gameplay.h
**Fungsinya: mengecek tembok berdasarkan solid atau tidak
*/
bool apakahTembok(address root, int x, int y);

/*gameplay.h
**Fungsinya: Indikator untuk ruangan yang sedang ditempati
*/
bool apakahObject(address root, int x, int y);

/*gameplay.h
**Fungsinya: Indikator untuk pesan objek, return pesannya
*/
string cekPesanObj(address root, int x, int y);

/*gameplay.h
**Fungsinya: mengubah variabel solid suatu node
*/
void ubahPropertiNode(address root, int x, int y, bool statusBaruDilewati, string pesanBaru);
    
/*gameplay.h
**Fungsinya: menampilkan ASCII tempat sampah
*/
void tampilkanTempatSampah();

/*gameplay.h
**Fungsinya: menampilkan ASCII perpustakaan
*/
void tampilkanArtPerpustakaan();

/*gameplay.h
**Fungsinya: menampilkan ASCII buku sesuai dengan nomor clue
*/
void tampilkanArtClue(int nomorClue);
   
/*gameplay.h
**Fungsinya: mencari nama objek di tree, return nama objek
*/
string cariNamaObj(address root, int x, int y);

/*gameplay.h
**Fungsinya: menggambar peta tergantung posisi player dan radius pandang
*/
void gambarPeta(address root, int x, int y, int radiusPandang);
    
/*gameplay.h
**Fungsinya: membuat tembok
*/
void buatNodeTembok(address &root, int xAwal, int yAwal, int xAkhir, int yAkhir);

/*gameplay.h
**Fungsinya: membuat rak buku pada perpustakaan
*/
void buatRakBuku(address &root, int xAwal, int yAwal, int xAkhir, int yAkhir, string pesan);

/*gameplay.h
**Fungsinya: pembuatan root baru dimana semua objek baru di perpus
*/
void inisialisasiPetaPerpustakaan(address &root);

/*gameplay.h
**Fungsinya: membuat root baru untuk lorong dan objek barunya
*/
void buatLorongKampus(address &root, int trg_lorong);

/*gameplay.h
**Fungsinya: berpindah ruangan tergantung tujuannya dan mengembalikan posisi player di setiap ruangan
*/
void pindahKeRuangan(address &root, int &x, int &y, int tujuan, int trg_lorong);

/*gameplay.h
**Fungsinya: melihat setting
*/
void lihatSetting(address &root, int &radiusPandang);

/*gameplay.h
**Fungsinya: input objek tambahan
*/
void inputObject(address &root);

/*gameplay.h
**Fungsinya: masuk ke menu developer
*/
void menuDeveloper(address &root);

/*gameplay.h
**Fungsinya: input tembok
*/
void inputTembok(address &root);  

/*gameplay.h
**Fungsinya: THE GAME 
*/
void mulaiBermain(address &root, int radiusPandang, int &profil, SkillNode* rootSkill); 
// void mulaiBermain(address &root, int radiusPandang, SkillNode* SkillRoot);

/*gameplay.h
**Fungsinya: masuk ke menu profil
*/
int menuProfil(int &profil);

#endif