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


const vector<string> LABIRIN2 = {
    "#########################################",
    "#P      #       #         #             #",
    "####### # ##### # ####### # ########### #",
    "#       # #     #       # #           # #",
    "# ####### # ########### # ######### # # #",
    "#       # #           # #         # #   #",
    "####### # ######### # # ######### # #####",
    "#     # #         # # #         # #     #",
    "# ### # ######### # # ######### # ##### #",
    "# #   #         # # #       #   #     # #",
    "# # ########### # # ####### # ####### # #",
    "# #           # # #       # #       # # #",
    "# ########### # # ####### # ####### # # #",
    "#           # # #       # #     #   # # #",
    "########### # # ####### # ##### # ### # #",
    "#         # # #       # #     # #     # #",
    "# ####### # # ####### # ##### # ####### #",
    "# #     # #         #       # #       # #",
    "# # ### # ######### ####### # ####### # #",
    "#   #   #                 #         #  E#",
    "#########################################"};


const vector<string> LABIRIN3 = {
    "###########################################################",
    "#P      #       #       #         #       #               #",
    "####### # ##### # ##### # ####### # ##### # ###############",
    "#       # #     #     # #       # #     # #               #",
    "# ####### # ######### # ####### # ##### # ############### #",
    "#       # #         # #       # #     # #       #         #",
    "####### # ######### # ####### # ##### # ####### # ####### #",
    "#     # #       #   #       # #     # #       # #       # #",
    "# ### # # ##### # ######### # ##### # ####### # ####### # #",
    "# #   #       # #         # #     # #       # #     #   # #",
    "# # ######### # ######### # ##### # ####### # ##### # ### #",
    "# #         # #       #   #     # #       # #     # #     #",
    "# ######### # ####### # ####### # ####### # ##### # #######",
    "#       #   #       # #       # #       # #       #       #",
    "####### # ####### # ####### # ####### # ##### # ####### # #",
    "#     # #       # #       # #       # #     # #       # # #",
    "# ### # ####### # ####### # ####### # ##### # ####### # # #",
    "# #   #       # #     #   #     #   #     # #     #   # # #",
    "# # ####### # # ##### # ####### # ####### # ##### # ### # #",
    "# #       # # #     # #       # #       # #     # #     # #",
    "# ####### # # ##### # ####### # ####### # ##### # ####### #",
    "#       # # #     # #       # #     #   #     #         # #",
    "####### # # ##### # ####### # ##### # ####### # ####### # #",
    "#     # # #     # #     #   #     # #       # #       # # #",
    "# ### # # ##### # ##### # ####### # ####### # ####### # # #",
    "# #   # #     # #     # #       # #     #   #     #   # # #",
    "# # ### ##### # ##### # ####### # ##### # ####### # ### # #",
    "# #         #       #         #       #           #     # #",
    "# ######### ######### ####### ######### ########### ##### #",
    "#                                                   #    E#",
    "###########################################################"};




bool adalahTembok(const vector<string> & maze, int y, int x)
{
    if (y < 0 || y >= (int)maze.size()) return false;
    if (x < 0 || x >= (int)maze[y].size()) return false;
    return maze[y][x] == '#';
}

chtype pilihGaris(const vector<string> & maze, int y, int x)
{
    bool atas = adalahTembok(maze, y - 1, x);
    bool bawah = adalahTembok(maze, y + 1, x);
    bool kiri = adalahTembok(maze, y, x - 1);
    bool kanan = adalahTembok(maze, y, x + 1);

    if (atas && bawah && kiri && kanan) return ACS_PLUS;    // perempatan
    if (atas && bawah && kanan) return ACS_LTEE;            // T ke kanan
    if (atas && bawah && kiri) return ACS_RTEE;             // T ke kiri
    if (kiri && kanan && bawah) return ACS_TTEE;            // T ke bawah
    if (kiri && kanan && atas) return ACS_BTEE;             // T ke atas
    if (atas && bawah) return ACS_VLINE;                    // garis tegak
    if (kiri && kanan) return ACS_HLINE;                    // garis datar
    if (bawah && kanan) return ACS_ULCORNER;                // sudut kiri-atas
    if (bawah && kiri) return ACS_URCORNER;                 // sudut kanan-atas
    if (atas && kanan) return ACS_LLCORNER;                 // sudut kiri-bawah
    if (atas && kiri) return ACS_LRCORNER;                  // sudut kanan-bawah
    if (atas || bawah) return ACS_VLINE;                    // ujung garis tegak
    return ACS_HLINE;                                       // ujung garis datar / sendirian
}

void gambarLabirin(const vector<string> &maze, int pemainY, int pemainX,
                   int offsetY, int offsetX)
{
    for (int y = 0; y < (int)maze.size(); y++)
    {
        for (int x = 0; x < (int)maze[y].size(); x++)
        {
            int layarY = offsetY + y;
            int layarX = offsetX + x * 2;

            if (y == pemainY && x == pemainX)
            {
                mvprintw(layarY, layarX, "@ ");
            }
            else if (maze[y][x] == '#')
            {
                mvaddch(layarY, layarX, pilihGaris(maze, y, x));
                if (adalahTembok(maze, y, x + 1))
                    mvaddch(layarY, layarX + 1, ACS_HLINE);
                else
                    mvaddch(layarY, layarX + 1, ' ');
            }
            else if (maze[y][x] == 'E')
            {
                mvprintw(layarY, layarX, "EX");
            }
            else
            {
                mvprintw(layarY, layarX, "  ");
            }
        }
    }
}

int main()
{

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int lv;

    while (true)
    {
        erase();

        mvprintw(2, 25, "=== GAME MODE ===");
        mvprintw(4, 25, "1. EASY");
        mvprintw(5, 25, "2. NORMAL");
        mvprintw(6, 25, "3. HARD");
        mvprintw(7, 25, "=================");
        mvprintw(8, 25, "=={CHOOSE(1-3)}==");
        refresh();

        lv = getch();

        if (lv >= '1' && lv <= '3')
            break;
    }

    vector<string> maze;
    switch(lv)
    {
        case '1':
        maze = LABIRIN1;
        break;
        case '2':
        maze = LABIRIN2;
        break;
        case '3':
        maze = LABIRIN3;
        break;
        

    }

    int tinggi = maze.size();
    int lebar = maze[0].size();

    int pemainY = 1, pemainX = 1;
    for (int y = 0; y < tinggi; y++)
    {
        for (int x = 0; x < lebar; x++)
        {
            if (maze[y][x] == 'P')
            {
                pemainY = y;
                pemainX = x;
                maze[y][x] = ' ';
            }
        }
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int layarTinggi, layarLebar;
    getmaxyx(stdscr, layarTinggi, layarLebar);
    int offsetY = (layarTinggi - tinggi) / 2;
    int offsetX = (layarLebar - lebar * 2) / 2;
    if (offsetY < 2) offsetY = 2;
    if (offsetX < 0) offsetX = 0;

    int langkah = 0;
    bool menang = false;
    bool jalan = true;

    while (jalan)
    {
        erase();

        mvprintw(offsetY - 2, offsetX, "=== GAME MAZE ===");
        mvprintw(offsetY + tinggi + 1, offsetX, "Langkah: %d", langkah);
        mvprintw(offsetY + tinggi + 2, offsetX, "Panah/WASD = gerak | Q = keluar");

        gambarLabirin(maze, pemainY, pemainX, offsetY, offsetX);

        if (menang)
        {
            mvprintw(offsetY + tinggi + 4, offsetX,
                     "SELAMAT! Kamu menang dalam %d langkah!", langkah);
            mvprintw(offsetY + tinggi + 5, offsetX, "Tekan tombol apa saja...");
            refresh();
            getch();
            break;
        }

        refresh();

        int tombol = getch();
        int barY = pemainY;
        int barX = pemainX;

        switch (tombol)
        {
        case KEY_UP:
        case 'w':
        case 'W':
            barY--;
            break;
        case KEY_DOWN:
        case 's':
        case 'S':
            barY++;
            break;
        case KEY_LEFT:
        case 'a':
        case 'A':
            barX--;
            break;
        case KEY_RIGHT:
        case 'd':
        case 'D':
            barX++;
            break;
        case 'q':
        case 'Q':
            jalan = false;
            break;
        }

        if (jalan && maze[barY][barX] != '#' && (barY != pemainY || barX != pemainX))
        {
            pemainY = barY;
            pemainX = barX;
            langkah++;

            if (maze[pemainY][pemainX] == 'E')
                menang = true;
        }
    }

    endwin();
    return 0;
}