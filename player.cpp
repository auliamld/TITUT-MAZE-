#include <ncurses.h>
#include "player.h"
#include "maze.h"


bool gerakPemain(int level, int tombol, Player &pemain) {

    int tujuanX = pemain.x;
    int tujuanY = pemain.y;

    if (tombol == KEY_UP || tombol == 'w' || tombol == 'W') {
        tujuanY--;
    }
    else if (tombol == KEY_DOWN || tombol == 's' || tombol == 'S') {
        tujuanY++;
    }
    else if (tombol == KEY_LEFT || tombol == 'a' || tombol == 'A') {
        tujuanX--;
    }
    else if (tombol == KEY_RIGHT || tombol == 'd' || tombol == 'D') {
        tujuanX++;
    }
    else {
        return false;
    }

    
    if (getIsiLabirin(level, tujuanY, tujuanX) == '#') {
        return false;
    }

    pemain.x = tujuanX;
    pemain.y = tujuanY;

    return true;
}
