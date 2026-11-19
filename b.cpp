// GAME MAZE SEDERHANA (tanpa warna)
// Kompilasi: g++ maze_simple.cpp -o maze_simple -lncurses
// Jalankan : ./maze_simple
// Kontrol  : panah atau w a s d, tekan q untuk keluar

#include <ncurses.h>
#include <string>
#include <vector>
using namespace std;

const vector<string> LABIRIN1 = {
    "################################",
    "#P    #       #       #        #",
    "##### # ##### # ##### # #####  #",
    "#     # #     #     # #     #  #",
    "# ##### # ######### # ##### #  #",
    "#       #       #   #     #    #",
    "####### ####### # ####### #### #",
    "#     #       # #       #      #",
    "# ### ####### # ####### ###### #",
    "#   #       # #       #      # #",
    "### ####### # ####### ######## #",
    "#         #         #          #",
    "# ####### ######### ########## #",
    "#       #                   # E#",
    "################################"};

int main(){

    initscr();
    

     for (int a = 0; a<LABIRIN1.size(); a++) {
        for (int b = 0; b<LABIRIN1[a].size(); b++) {
            mvaddch(a, b, LABIRIN1[a][b]);
        }
    }

    refresh();

    getch();

    endwin(); // kembalikan terminal ke normal
    return 0;
}