// Bagian Nadine Game System

#include <ncurses.h> 
#include "game.h"    
#include "maze.h"    
#include "player.h"  
#include "display.h" 

// Fungsi untuk menjalankan game sesuai levelnya
void jalankanGame(int level) {

    Player pemain; // Membuat objek pemain

    // Menentukan posisi awal pemain
    pemain.x = 1;
    pemain.y = 1;

    int waktu = getWaktuLevel(level); // Mengambil waktu sesuai level
    int langkah = 0; // Menghitung jumlah langkah
    int tick = 0; // Menghitung interval waktu

    bool menang = false; // Status kemenangan
    bool keluar = false; // Status keluar dari game

    // Input diperiksa setiap 100 milidetik
    timeout(100);

    // Game berjalan selama waktu masih tersedia
    while (waktu > 0) {

        // Menampilkan kondisi permainan
        tampilkanGame(
            level,
            pemain.y,
            pemain.x,
            waktu,
            langkah
        );

        // Membaca tombol yang ditekan pemain
        int tombol = getch();

        // Keluar dari game jika menekan Q
        if (tombol == 'q' || tombol == 'Q') {
            keluar = true;
            break;
        }

        // Memproses gerakan pemain, langkah bertambah jika berhasil
        if (gerakPemain(level, tombol, pemain)) {
            langkah++;
        }

        // Mengecek apakah pemain sudah sampai pintu keluar
        if (getIsiLabirin(level, pemain.y, pemain.x) == 'E') {
            menang = true;
            break;
        }

        // Menghitung waktu permainan
        tick++;

        // Setiap 10 tick, waktu berkurang 1 detik
        if (tick >= 10) {
            waktu--;
            tick = 0;
        }
    }

    // Menghentikan fungsi jika pemain memilih keluar
    if (keluar) {
        return;
    }

    // Menampilkan hasil akhir permainan
    tampilkanHasil(menang);
}