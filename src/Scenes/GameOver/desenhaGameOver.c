#include <ncurses.h>
#include "../../state.h"

#define UNUSED(x) (void)(x)

void desenhaGameOver(WINDOW *window, State *state)
{
    UNUSED(window);
    UNUSED(state);
    noecho();

    int nrows, ncols;
    getmaxyx(stdscr, nrows, ncols);
    int y = (nrows / 2) - 4;
    int x = (ncols / 2) - 2;

    refresh();

    box(window, 0, 0); // desenhar caixa
  
    mvprintw(y , x-30   , "   ____    _    __  __ _____    _____     _______ ____    ");
    mvprintw(y+1 , x-30 , "  / ___|  / \\  |  \\/  | ____|  / _ \\ \\   / / ____|  _ \\   ");
    mvprintw(y+2 , x-30  , " | |  _  / _ \\ | |\\/| |  _|   | | | \\ \\ / /|  _| | |_) |  ");
    mvprintw(y+3 , x-30  , " | |_| |/ ___ \\| |  | | |___  | |_| |\\ V / | |___|  _ <   ");
    mvprintw(y+4 , x-30  , "  \\____/_/   \\_\\_|  |_|_____|  \\___/  \\_/  |_____|_| \\_\\  ");

    mvaddstr(nrows - 4, 2, "Pressione 'm' para voltar ao menu");
    mvaddstr(nrows - 2, 2, "Pressione 'q' para sair do jogo");
}