#ifndef VEICULO_H


#define VEICULO_H
#include "servidor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_VEICULO 101
struct veiculo{
    char codigos_servidor_2[255];
    char codigos_veiculo[255];
    char marcas[255];
    char descricaos[255];
    char placas[255];
    char modelos[255];
};

void salvar_arquivo_veiculo(struct veiculo *[], FILE *);
void ler_arquivo_veiculo(struct veiculo *[], FILE *);
void detalhes_veiculo(int , struct veiculo *[]);
int obter_nome_servidor(char *, FILE *);
void iniciar_veiculos(struct veiculo *[], FILE *);
void liberar_veiculos(struct veiculo *[]);
void inserir_veiculo(struct veiculo *[],
                     char *, char *, char *, char *, char *, char *, FILE *);
void inserir_veiculo_ui(struct veiculo *[], FILE *, FILE *);
int pesquisa_por_codigo_veiculo(struct veiculo *[], char *, FILE *, FILE *);
void pesquisa_por_codigo_veiculo_ui(struct veiculo *[], FILE *, FILE *);
int excluir_veiculo(char *, struct veiculo *[], FILE *);
void excluir_veiculo_ui(struct veiculo *[], FILE *);
void alterar_cadastro_veiculo_ui(struct veiculo *[], FILE *, FILE *);
void alterar_cadastro_veiculo(struct veiculo *[], char *, int , int , FILE *);
int listagem_todos_veic_servidor(struct veiculo *[], char *, FILE *, FILE *);
void listagem_todos_veic_servidor_ui(struct veiculo *[], FILE *, FILE *);
int listagem_alfab_todos_veic_servidor(struct veiculo *[], struct servidor *[], char *, FILE *, FILE *);
void listagem_alfab_todos_veic_servidor_ui(struct veiculo *[], FILE *, FILE *);
#endif