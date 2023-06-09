#include <ncurses.h>
#include <json-c/json.h>
#include "../state.h"

// salvar jogo pra um JSON
void save_game_state(State *state)
{
	// Jogo Rápido [J] gerava o ficheiro "0.json"
	if (state->jogoAtual.jogador.numSave <= 0)
		return;

	char filename[16];
	sprintf(filename, "%d.json", state->jogoAtual.jogador.numSave);

	StatusJogador jogador = state->jogoAtual.jogador;
	int *quantidadeObjetos = state->jogoAtual.quantidadeObjetos;

	// Criar objeto JSON para reter estado do Jogo
	json_object *quantidadeObjetosJSON = json_object_new_array();

	for (int i = 0; i < catalogoObjetosLength; i++)
	{
		json_object_array_add(quantidadeObjetosJSON, json_object_new_int(quantidadeObjetos[i]));
	}

	// Criar objeto JSON para reter estado do Jogo
	json_object *game_state = json_object_new_object();

	// Pares estado do Jogo
	json_object_object_add(game_state, "vida", json_object_new_int(jogador.vida));
	json_object_object_add(game_state, "username", json_object_new_string(jogador.username));
	json_object_object_add(game_state, "numMapaAtual", json_object_new_int(jogador.numMapaAtual));
	json_object_object_add(game_state, "dinheiro", json_object_new_int(jogador.dinheiro));
	json_object_object_add(game_state, "quantidadeMortes", json_object_new_int(jogador.quantidadeMortes));
	json_object_object_add(game_state, "armaPrincipalIndex", json_object_new_int(jogador.armaPrincipal.index));
	json_object_object_add(game_state, "armaSecundariaIndex", json_object_new_int(jogador.armaSecundaria.index));
	json_object_object_add(game_state, "quantidadeObjetos", quantidadeObjetosJSON);

	// Converter objeto JSON para string
	const char *json_str = json_object_to_json_string_ext(game_state, JSON_C_TO_STRING_PRETTY);

	// Abrir ficheiro save para escrever
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Error: unable to open save file for writing\n");
		exit(1);
	}

	// Escrever JSON string para o ficheiro save
	fprintf(fp, "%s", json_str);

	// Fechar ficheiro libertar memoria
	fclose(fp);
	json_object_put(game_state);
}

// carregar jogo
void load_game_state(State *state)
{
	// No jogo rápido, o numMapaAtual == 1
	if (state->jogoAtual.jogador.numSave <= 0)
	{
		state->scenesVariables.selecionarJogadorSceneVars.askUser = 2;
		return;
	}

	char filename[16];
	sprintf(filename, "%d.json", state->jogoAtual.jogador.numSave);

	int arma1_index, arma2_index;
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json,
			*vida,
			*username,
			*numMapaAtual,
			*dinheiro,
			*quantidadeMortes,
			*armaPrincipalIndex,
			*armaSecundariaIndex,
			*quantidadeObjetos;

	// load ficheiro
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 0)
			state->scenesVariables.selecionarJogadorSceneVars.askUser = 1;
	}
	else
	{
		if (fread(buffer, 1024, 1, fp))
		{
		}
		fclose(fp);
		parsed_json = json_tokener_parse(buffer);

		json_object_object_get_ex(parsed_json, "vida", &vida);
		json_object_object_get_ex(parsed_json, "username", &username);
		json_object_object_get_ex(parsed_json, "numMapaAtual", &numMapaAtual);
		json_object_object_get_ex(parsed_json, "dinheiro", &dinheiro);
		json_object_object_get_ex(parsed_json, "quantidadeMortes", &quantidadeMortes);
		json_object_object_get_ex(parsed_json, "armaPrincipalIndex", &armaPrincipalIndex);
		json_object_object_get_ex(parsed_json, "armaSecundariaIndex", &armaSecundariaIndex);
		json_object_object_get_ex(parsed_json, "quantidadeObjetos", &quantidadeObjetos);

		state->jogoAtual.jogador.vida = json_object_get_int(vida);
		state->jogoAtual.jogador.username = (char *)json_object_get_string(username);
		state->jogoAtual.jogador.numMapaAtual = json_object_get_int(numMapaAtual);
		state->jogoAtual.jogador.dinheiro = json_object_get_int(dinheiro);
		state->jogoAtual.jogador.quantidadeMortes = json_object_get_int(quantidadeMortes);

		int tamanhoArrayGuardado = json_object_array_length(quantidadeObjetos);
		for (int i = 0; i < tamanhoArrayGuardado; i++)
		{
			state->jogoAtual.quantidadeObjetos[i] = json_object_get_int(json_object_array_get_idx(quantidadeObjetos, i));
		}

		arma1_index = json_object_get_int(armaPrincipalIndex);
		arma2_index = json_object_get_int(armaSecundariaIndex);

		state->jogoAtual.jogador.armaPrincipal = catalogoArmas[arma1_index];
		state->jogoAtual.jogador.armaSecundaria = catalogoArmas[arma2_index];

		state->scenesVariables.selecionarJogadorSceneVars.askUser = 2;
	}
}

// salvar settings do state pra um JSON
void save_settings_state(State *state)
{
	// Criar objeto JSON para reter estado do Jogo
	json_object *settings_state = json_object_new_object();

	// Pares estado do Jogo
	json_object_object_add(settings_state, "matrix_width", json_object_new_int(state->mapa.matrix_width));
	json_object_object_add(settings_state, "matrix_height", json_object_new_int(state->mapa.matrix_height));
	json_object_object_add(settings_state, "dificuldade", json_object_new_int(state->jogoAtual.dificuldade));
	json_object_object_add(settings_state, "iluminacao_ativa", json_object_new_int(state->jogoAtual.iluminacao_ativa));
	json_object_object_add(settings_state, "mapa_desconhecido_ativo", json_object_new_int(state->jogoAtual.mapa_desconhecido_ativo));

	// Converter objeto JSON para string
	const char *json_str = json_object_to_json_string_ext(settings_state, JSON_C_TO_STRING_PRETTY);

	// Abrir ficheiro save para escrever
	FILE *fp = fopen("settings.json", "w");

	if (fp == NULL)
	{
		printf("Error: unable to open save file for writing new settings.\n");
	}

	// Escrever JSON string para o ficheiro save
	fprintf(fp, "%s", json_str);

	fclose(fp);
	json_object_put(settings_state);
}

// carregar jogo
void load_settings_state(State *state)
{
	char buffer[1024];
	struct json_object *parsed_json;

	struct json_object *matrix_width,
			*matrix_height,
			*dificuldade,
			*iluminacao_ativa,
			*mapa_desconhecido_ativo;

	// load ficheiro
	FILE *fp = fopen("settings.json", "r");

	if (fp != NULL)
	{
		if (fread(buffer, 1024, 1, fp))
		{
		}
		fclose(fp);
		parsed_json = json_tokener_parse(buffer);

		json_object_object_get_ex(parsed_json, "matrix_width", &matrix_width);
		json_object_object_get_ex(parsed_json, "matrix_height", &matrix_height);
		json_object_object_get_ex(parsed_json, "dificuldade", &dificuldade);
		json_object_object_get_ex(parsed_json, "iluminacao_ativa", &iluminacao_ativa);
		json_object_object_get_ex(parsed_json, "mapa_desconhecido_ativo", &mapa_desconhecido_ativo);

		state->mapa.matrix_width = json_object_get_int(matrix_width);
		state->mapa.matrix_height = json_object_get_int(matrix_height);
		state->jogoAtual.dificuldade = json_object_get_int(dificuldade);
		state->jogoAtual.iluminacao_ativa = json_object_get_int(iluminacao_ativa);
		state->jogoAtual.mapa_desconhecido_ativo = json_object_get_int(mapa_desconhecido_ativo);
	}
}