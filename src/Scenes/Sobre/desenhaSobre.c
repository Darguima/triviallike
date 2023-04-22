#include <ncurses.h>

#include "../../state.h"

/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

void desenhaSobre(WINDOW* window, State* state) {
  UNUSED(window);
  UNUSED(state);

  int nrows, ncols;
	getmaxyx(window, nrows, ncols);

  mvaddstr((nrows / 2) - 1, (ncols - 28) / 2, "Neste menu vao ser mostradas");
  mvaddstr((nrows / 2) + 0, (ncols - 21) / 2, "informacoes sobre nos");
  mvaddstr((nrows / 2) + 2, (ncols - 19) / 2, "press q para voltar");
}