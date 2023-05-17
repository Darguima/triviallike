#include <ncurses.h>
#include "../../state.h"
#include "../../SalvarJogo/salvarJogo.h"
#include "../../GeraMapa/geraMapa.h"

void jogar(State *state)
{
	if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 0 || state->scenesVariables.selecionarJogadorSceneVars.askUser == 2)
	{
		// Resetar valores para um novo jogo
		state->jogoAtual.jogador.vida = state->jogoAtual.jogador.vidaMaxima;
		state->jogoAtual.jogador.posicao.x = 1;
		state->jogoAtual.jogador.posicao.y = 1;
		state->jogoAtual.jogador.numMapaAtual = 1;
		state->jogoAtual.jogador.dinheiro = 0;
		state->jogoAtual.jogador.armaPrincipal = punhos;
		state->jogoAtual.jogador.armaSecundaria = punhos;

		load_game_state(state);

		geraMapa(state);

		state->scenesVariables.selecionarJogadorSceneVars.askUser = 0;
		state->sceneAtual = Jogo;
	}
}

void eventosSelecionarJogador(State *state)
{
	int key = getch();

	switch (key)
	{
	case '1':
		if (state->scenesVariables.selecionarJogadorSceneVars.delete == 1)
		{
			if (remove("1.json") != 0)
			{
				state->scenesVariables.selecionarJogadorSceneVars.faildelete = 1;
			}
			state->scenesVariables.selecionarJogadorSceneVars.delete = 0;
		}
		else if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 0 || state->scenesVariables.selecionarJogadorSceneVars.askUser == 2)
			{
				state->scenesVariables.selecionarJogadorSceneVars.askUser = 0;
				state->jogoAtual.jogador.numSave = 1;
				jogar(state);
			}
		break;

	case '2':
		if (state->scenesVariables.selecionarJogadorSceneVars.delete == 1)
		{
			if (remove("2.json") != 0)
			{
				state->scenesVariables.selecionarJogadorSceneVars.faildelete = 1;
			}
			state->scenesVariables.selecionarJogadorSceneVars.delete = 0;
		}
		else if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 0 || state->scenesVariables.selecionarJogadorSceneVars.askUser == 2)
		{
			state->scenesVariables.selecionarJogadorSceneVars.askUser = 0;
			state->jogoAtual.jogador.numSave = 2;
			jogar(state);
		}
		break;

	case '3':
		if (state->scenesVariables.selecionarJogadorSceneVars.delete == 1)
		{
			if (remove("3.json") != 0)
			{
				state->scenesVariables.selecionarJogadorSceneVars.faildelete = 1;
			}
			state->scenesVariables.selecionarJogadorSceneVars.delete = 0;
		}
		else if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 0 || state->scenesVariables.selecionarJogadorSceneVars.askUser == 2)
		{
			state->scenesVariables.selecionarJogadorSceneVars.askUser = 0;
			state->jogoAtual.jogador.numSave = 3;
			jogar(state);
		}
		break;

	case 'j':
		jogar(state);
		break;

	case 'd':
		state->scenesVariables.selecionarJogadorSceneVars.faildelete = 0;
		state->scenesVariables.selecionarJogadorSceneVars.delete = 1;
		break;

	case 'a':
		state->scenesVariables.selecionarJogadorSceneVars.faildelete = 0;
		state->scenesVariables.selecionarJogadorSceneVars.delete = 0;
		break;

	case 'q':
		state->sceneAtual = MenuInicial;
		break;
	}
}
