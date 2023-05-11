#include <stdlib.h>
#include "state.h"

const Arma punhos = {0, Punhos, "Punhos", 7, 50, "Um par de punhos que, nas mãos adequadas, fazem grandes estragos "};
const Arma garras = {1, Garras, "Garras", 20, 60, "Garras ensanguentadas que saem das mãos de um grotesco monstro. Urghh..."};
const Arma espadaOxidada = {2, EspadaOxidada, "EspadaOxidada", 25, 75, "Espada que pertenceu a um soldado caído em combate."};
const Arma espadaLonga = {3, EspadaLonga, "EspadaLonga", 30, 95, "Espada forjada pelos melhores ferreiros. Embora não seja muito potente, raramente falha ao seu portador."};
const Arma arco = {4, Arco, "Arco", 45, 30, "Um arco bastante flexível que causa muito dano mas possui uma terrível precisão."};
const Arma acido = {5, Acido, "Acido", 40, 15, "Um líquido lançado por certos monstros que desfaz tudo o que toca."};
const Arma cetro = {6, Cetro, "Cetro", 15, 100, "Um cetro carregado de magia. O seu baixo dano é compensado com a precisão dos seus projéteis."};

const Arma catalogoArmas[] = {punhos, garras, espadaOxidada, espadaLonga, arco, acido, cetro};

Mob const esqueleto1 = {Esqueleto, "Esqueleto", 'E', espadaOxidada, 40, 40, 3};
Mob const esqueleto2 = {Esqueleto, "Esqueleto", 'E', punhos, 40, 40, 3};
Mob const soldadoEsqueleto1 = {SoldadoEsqueleto, "Soldado Esqueleto", 'S', espadaLonga, 60, 60, 4};
Mob const vampiro1 = {Vampiro, "Vampiro", 'V', garras, 70, 70, 8};
Mob const vampiro2 = {Vampiro, "Vampiro", 'V', cetro, 50, 50, 10};
Mob const mutante1 = {Mutante, "Mutante", 'M', punhos, 30, 30, 2};
Mob const mutante2 = {Mutante, "Mutante", 'M', punhos, 10, 10, 2};
Mob const aranha1 = {Aranha, "Aranha", 'A', acido, 30, 30, 10};
Mob const aranha2 = {Aranha, "Aranha", 'A', acido, 40, 40, 8};
Mob const zombie1 = {Zombie, "Zombie", 'Z', garras, 70, 70, 2};

int const mobsNoMapaLength = 10;
int const catalogoMobsLength = 10;
Mob const catalogoMobs[] = {esqueleto1, esqueleto2, soldadoEsqueleto1, vampiro1, vampiro2, mutante1, mutante2, aranha1, aranha2, zombie1};


State criarEstado(int colunas, int linhas)
{
	State state;
	ElementosDoMapa **matrix;

	// Allocate memory for the matrix
	matrix = (ElementosDoMapa **)malloc(colunas * sizeof(ElementosDoMapa *));
	for (int i = 0; i < colunas; i++)
	{
		matrix[i] = (ElementosDoMapa *)malloc(linhas * sizeof(ElementosDoMapa));
	}

	// Fill the matrix with values

	state.sceneAtual = MenuInicial;

	state.controloMenu.highlight = 1;
	state.controloMenu.side = 0;
	state.controloMenu.help = 0;

	state.jogoAtual.jogador.vida = 100;
	state.jogoAtual.jogador.username = "Joao";
	state.jogoAtual.jogador.vidaMaxima = 100;
	state.jogoAtual.jogador.posicao.x = 1;
	state.jogoAtual.jogador.posicao.y = 1;
	state.jogoAtual.jogador.numMapaAtual = 1;
	state.jogoAtual.jogador.inventario = NULL;
	state.jogoAtual.jogador.dinheiro = 0;
	state.jogoAtual.jogador.armaPrincipal = punhos;
	state.jogoAtual.jogador.armaSecundaria = punhos;
	state.jogoAtual.jogador.numSave = 0;

	state.jogoAtual.mobs = malloc(mobsNoMapaLength * sizeof(MobNoMapa));
	state.jogoAtual.armas = malloc(armasNoMapaLength * sizeof(ArmaNoMapa));
	state.jogoAtual.mensagem_descricao = "Encontra a porta para passar de mapa!";
	state.jogoAtual.mensagem_controlos = "Utiliza as setas para te movimentares.";

	state.mapa.terminal.width = colunas;
	state.mapa.terminal.height = linhas;
	state.mapa.width = colunas - 40;
	state.mapa.height = linhas - 10;
	state.mapa.matrix = matrix;

	return state;
}
