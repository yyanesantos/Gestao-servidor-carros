#ifndef SERVIDOR_H

#define SERVIDOR_H
#define TAM 31
#define TAM_VEICULO 101
#include "veiculo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct servidor{
    char codigos_servidor[255];
    char nomes[255];
    char SIAPEs[255];
    char RGs[255];
    char CPFs[255];
    char enderecos[255];
    char salarios[255];
    char datas_nascimento[255];
    char tipos[255];
};

void salvar_arquivo_servidor(struct servidor *[], FILE *);
void ler_arquivo_servidor(struct servidor *[], FILE *);
int qtd_de_veic(char *);
void detalhes_servidor(int , struct servidor *[]);
int iniciar_servidores(struct servidor *[], FILE *, FILE *);
void iniciar_servidores_ui(struct servidor *[], FILE *, FILE *);
void liberar_servidores(struct servidor *[]);
void inserir_servidor(struct servidor *[],
                      char *, char *, char *, char *, char *, char *, char *, char *, char *, FILE *);
void listar_servidores(struct servidor *[], FILE *);
int pesquisa_por_codigo_servidor(struct servidor *[], char *, FILE *);
void pesquisa_por_codigo_servidor_ui(struct servidor *[], FILE *);
void inserir_servidor_ui(struct servidor *[], FILE *);
void listagem_alfabetica_servidor(struct servidor *[], FILE *);
void listagem_por_tipo(char *, struct servidor *[], FILE *);
void excluir_servidor_ui(struct servidor *[], FILE *, FILE *);
void excluir_servidor(char *, struct servidor *[], FILE *);
void alterar_cadastro_servidor(struct servidor *[], char *, int , int , FILE *);
void alterar_cadastro_servidor_ui(struct servidor *[], FILE *);
#endif