#include <ncurses.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#ifndef ___State_H___
#define ___State_H___

/* São as diferentes páginas que podem aparecer ao longo do jogo */
typedef enum scene
{
	MenuInicial,			 /* Primeira página que aparece no jogo */
	SelecionarJogador, /* Transição entre Menu Inicial e Jogo (para escolher o jogador) */
	Jogo,							 /* O jogo em si, com o status do jogador, mapa e inventário */
	GameOver,
	Definicoes,
	Controlos,
	Sobre,
	Sair,
} Scene;

typedef enum colors
{
	// ncurses default colors
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,

	// cores do FG-Foreground BG-Background
	FG_MapaVisivel,
	BG_MapaVisivel,

	FG_MapaMemoria,
	BG_MapaMemoria,

	FG_MapaDesconhecido,
	BG_MapaDesconhecido,

	FG_Portal,
	FG_Player,
	FG_Moeda,
	FG_Arma,
	FG_Objeto,
	FG_Mob,

	BG_Parede,
	BG_ParedeNaoVisivel,
} Colors;

typedef enum colorsSchema
{
	WhiteBlack,
	YellowBlack,
	BlueBlack,
	GreenBlack,
	BlackYellow,
	BlackRed,
	RedBlack,

	MapaPlayerColor,
	MapaPlayerSobAtaqueColor,

	MapaVisivelColor,
	MapaMemoriaColor,
	MapaDesconhecidoColor,

	PortalColor,
	MoedaColor,
	ArmaColor,
	ObjetoColor,
	MobColor,

	ParedeColor,
	ParedeNaoVisivelColor,

	ArmaBox,
	ObjetoBox,
	MobBox
} ColorsScheme;

typedef struct coordenadas
{
	int x, y;
} Coordenadas;

typedef enum catalogoObjetos
{
	PocaoVidaD,				// poção de vida que recupera toda a vida
	PocaoVidaG,				// poção de vida Grande (60 vida)
	PocaoVidaP,				// poção de vida Pequena (25 vida)
	PocaoAumentoVida, // poção que faz aumentar a vida máxima sem dar mais vida
	PocaoMagica,			// poção que recupera toda a vida e aumenta a vida máxima
	PortalDeBolso,		// um portal que envia o jogador ao próximo mapa

} CatalogoObjetos;

typedef struct objeto
{
	int index;
	CatalogoObjetos objeto;
	char *nome;			// nome para ser mostrado no inventário
	char *mensagem; // mensagem mostrada ao pegar no objeto

} Objeto;

typedef struct objetoNoMapa
{
	Coordenadas posicao;
	int disponivel; // 1 se está disponível no mapa; 0 se o objeto já foi apanhada
	Objeto objeto;
} ObjetoNoMapa;

/* Diferentes armas que o player e mobs pode ter */
typedef enum catalogoArmas
{
	Punhos,
	Garras,
	EspadaOxidada,
	EspadaLonga,
	Arco,
	Acido,
	Cetro,
	Aniquiladora,
	Foice,
	Computador,
} CatalogoArmas;

typedef struct arma
{
	int index;
	CatalogoArmas tipoArma;
	char *nome; // nome para ser mostrado no inventário
	int dano;
	int probabilidade; // probabilidade de o ataque acertar no objetivo, de 0 a 100
	char *mensagem;		 // texto que descreve a arma
} Arma;

typedef struct armaNoMapa
{
	Coordenadas posicao;
	int disponivel; /* 1 se está disponível no mapa; 0 se a arma já foi apanhada */
	Arma arma;
} ArmaNoMapa;

typedef enum catalogoMobs
{										// o tipo do mob a chamar
	Esqueleto,				/* E */
	SoldadoEsqueleto, /* S */
	Vampiro,					/* V */
	Mutante,					/* M */
	Aranha,						/* A */
	Zombie,						/* Z */
	Demonio,                    /* D */
	Morte,                      /* W */
	Informatico,				/* I */
										/* Possibilidade de adicionar mais no futuro */
} CatalogoMobs;

typedef struct mob
{												// podem haver mais que um mob com armas diferentes
	CatalogoMobs tipomob; // recebe qual o tipo do mob
	char *nome;						// nome do mob
	char charASCII;				// char pelo qual se refere ao mob
	Arma arma;						// o mob possui uma arma só. Aqui temos de aplicar uma das armas do struct Armas
	int vida;							// vida do mob instantanea
	int vidaMaxima;				// máxima vida do mob
	int raioVisao;				// o raio de visão pode variar entre 1 e 10 (provisório). o raio de visão mede-se em quantas 'casas' o mob consegue ver o jogador e começar a atacar
} Mob;

typedef struct mobNoMapa
{
	Coordenadas posicao;
	Mob mob;
} MobNoMapa;

typedef struct statusJogador
{
	Coordenadas posicao;
	char *username;
	int vida;				// valor entre 0 e ...
	int vidaMaxima; // vida máxima do jogador
	Arma armaPrincipal;
	Arma armaSecundaria;
	int numSave;
	int dinheiro;
	int numMapaAtual; /* Quantas mapas já foram passados */
	int quantidadeMortes;
} StatusJogador;

typedef enum dificuldadeJogo
{
	FACIL = 0,
	MEDIO = 1,
	DIFICIL = 2,
} DificuldadeJogo;

typedef struct controlosSceneVars
{
	int highlight;
	int side;
	int help;
} ControlosSceneVars;

typedef struct selecionarJogadorSceneVars
{
	int delete;			// 1modo_apagar_ligado
	int faildelete; // 1apagar_erro
	int askUser;		// 0 - nada; 1 - pergunta_username; 2 - continuar_para_jogo
} SelecionarJogadorSceneVars;

typedef struct definicoesSceneVars
{
	int ask_matrix_size;
} DefinicoesSceneVars;

typedef struct scenesVariables
{
	ControlosSceneVars controlosSceneVars;
	SelecionarJogadorSceneVars selecionarJogadorSceneVars;
	DefinicoesSceneVars definicoesSceneVars;
} ScenesVariables;

typedef struct jogoAtual
{
	StatusJogador jogador;
	DificuldadeJogo dificuldade; // dificuldade cresce há medida que o número é maior (mais fácil = 0)
	int iluminacao_ativa;				 // Se 1, o algoritmo da visão roda, se não, todo o mapa está visível
	int mapa_desconhecido_ativo; // Se 0, todos os blocos passam a ser conhecidos
	MobNoMapa *mobs;
	ArmaNoMapa *armas;
	ObjetoNoMapa *objetos;
	char *mensagem_descricao;	 /* Mensagem para mostrar um texto relevante. ex. algum informação do mapa, arma ou mob */
	char *mensagem_controlos;	 /* Mensagem para mostrar um como interagir com o mapa */
	char *mensagem_inventario; /* mensagem de baixo direita*/
	char *mensagem_inventario_controlos;
	int *quantidadeObjetos; // a quantidade de objetos que há no inventário
} JogoAtual;

typedef enum elementosDoMapaCatalogo
{
	Vazio,						/*   */
	Jogador,					/* @ */
	NPC,							/* & */
	Parede,						/* # */
	PortaNormal,			/* + - serve para fechar as salas, no futuro se for possível implementar o conceito de chaves escondidas */
	PortaProximoMapa, /* +++|+++|+++ - serve para mudar de mapa */
	Moeda,						/* c */
} ElementosDoMapaCatalogo;

typedef struct elementosDoMapa
{
	ElementosDoMapaCatalogo tipo;
	int visivel;		// 1 para visivel
	int descoberto; // 1 para descoberto
} ElementosDoMapa;

typedef struct terminal
{
	int height;
	int width;
} Terminal;

typedef struct mapa
{
	Terminal terminal;
	int display_height;
	int display_width;
	int matrix_height;
	int matrix_width;

	int qntMoedasNoMapaLength;
	int qntArmasNoMapaLength;
	int qntObjetosNoMapaLength;
	int qntMobsNoMapaLength;
	int qntPortaisNoMapaLength;

	ElementosDoMapa **matrix;
} Mapa;

typedef struct state
{
	Scene sceneAtual;

	ScenesVariables scenesVariables;

	JogoAtual jogoAtual;
	Mapa mapa;

	WINDOW *ncurses_screen;

} State;

State criarEstado(WINDOW *window, int colunas, int linhas);

extern Arma const punhos;
extern Arma const garras;
extern Arma const espadaOxidada;
extern Arma const espadaLonga;
extern Arma const arco;
extern Arma const acido;
extern Arma const cetro;

extern int const catalogoArmasLength;
extern Arma const catalogoArmas[];

extern Mob const esqueleto1;
extern Mob const esqueleto2;
extern Mob const soldadoEsqueleto1;
extern Mob const vampiro1;
extern Mob const vampiro2;
extern Mob const mutante1;
extern Mob const mutante2;
extern Mob const aranha1;
extern Mob const aranha2;
extern Mob const zombie1;

extern int const catalogoMobsLength;
extern Mob const catalogoMobs[];

extern Objeto const pocaoVidaD;
extern Objeto const pocaoVidaG;
extern Objeto const pocaoVidaP;
extern Objeto const pocaoAumentoVida;
extern Objeto const pocaoMagica;
extern Objeto const portalDeBolso;

extern int const catalogoObjetosLength;
extern Objeto const catalogoObjetos[];

#endif
