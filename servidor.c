#include "servidor.h"
#include "util.h"

void salvar_arquivo_servidor(struct servidor *servidores[TAM], FILE *f_servidor)
{
    char indices[TAM];
    for (int i = 1; i<TAM; i++)
    {
        indices[i] = 0;
    }
    for (int i = 1; i < TAM; ++i)
    {
        if(servidores[i] != NULL)
        {
            for (int j = 1; j < TAM; ++j) {
                if(!indices[j])
                {
                    indices[j] = j;
                    break;
                }
            }
        }
    }
    f_servidor = fopen("servidor.bin", "wb");
    if(f_servidor == NULL)
    {
        printf("Nao foi possivel abrir o arquivo. O servidor nao foi armazenado, exclua-o e tente cadastra-lo novamente.\n");
        return;
    }
    fseek(f_servidor, 0, SEEK_END);
    for(int i = 1; i<TAM; i++)
    {
        if(indices[i] != 0)
        {
            fwrite(servidores[indices[i]], sizeof(struct servidor), 1, f_servidor);
        }
    }
    fclose(f_servidor);
}

void ler_arquivo_servidor(struct servidor *servidores[TAM], FILE *f_servidor)
{
    int lido;
    f_servidor = fopen("servidor.bin", "rb+");
    if(f_servidor == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    for(int i = 1; i<TAM; i++)
    {
        servidores[i] = malloc(sizeof(struct servidor));
        fseek(f_servidor, sizeof(struct servidor)*(i - 1), SEEK_SET);
        lido = fread(servidores[i], sizeof(struct servidor), 1, f_servidor);
        if (lido == 0) {
            servidores[i] = NULL;
            free(servidores[i]);
            break;
        }

    }

    fclose(f_servidor);
}

int qtd_de_veic(char *info)
{
    int numero_de_veic = 0;
    extern struct veiculo *veiculos[TAM_VEICULO];
    for(int i = 1; i<TAM_VEICULO; i++)
    {
        if(veiculos[i] != NULL)
        {
            if(!strcmp(info, veiculos[i]->codigos_servidor_2))
            {
                numero_de_veic = numero_de_veic + 1;
            }
        }
    }
    return numero_de_veic;
}

void remover_veiculos_com_servidor(char *info, FILE *f_veiculo)
{
    extern struct veiculo *veiculos[TAM_VEICULO];
    for(int i = 1; i<TAM_VEICULO; i++)
    {
        if(veiculos[i] != NULL)
        {
            if(!strcmp(info, veiculos[i]->codigos_servidor_2))
            {
                excluir_veiculo(veiculos[i]->codigos_veiculo, veiculos, f_veiculo);
            }
        }
    }
}
void detalhes_servidor(int i, struct servidor *servidores[TAM])
{
    struct servidor *c = servidores[i];
    if(c == NULL)
    {
        return;
    }
    printf(" Codigo do(a) servidor(a): %s Nome: %s SIAPE: %s RG: %s CPF: %s Endereco: %s Salario: R$%s Data de nascimento: %s Tipo: %s\n\n", c->codigos_servidor, c->nomes, c->SIAPEs, c->RGs, c->CPFs, c->enderecos, c->salarios, c->datas_nascimento, c->tipos);
}

int iniciar_servidores(struct servidor *servidores[TAM], FILE *f_servidor, FILE *f_veiculo)
{
    extern struct veiculo *veiculos[TAM_VEICULO];
    ler_arquivo_veiculo(veiculos, f_veiculo);
    int reinicio_valido;
    for(int i = 1; i<TAM_VEICULO; i++)
    {
        if(veiculos[i] != NULL)
        {
            reinicio_valido = 0;
            return reinicio_valido;
        }
    }
    for (int i = 1; i < TAM; ++i)
    {
        servidores[i] = NULL;
    }
    salvar_arquivo_servidor(servidores, f_servidor);
    return 1;
}

void iniciar_servidores_ui(struct servidor *servidores[TAM], FILE *f_servidor, FILE *f_veiculo)
{
    extern struct veiculo *veiculos[TAM_VEICULO];
    enum reiniciar{reiniciar_tudo = 1}reinicio;
    int reinicio_valido;
    reinicio_valido = iniciar_servidores(servidores, f_servidor, f_veiculo);
    if(!reinicio_valido)
    {
        printf("Ha servidores com veiculos cadastrados. "
               "Recomenda-se excluir tais veiculos antes de reiniciar o programa de servidores.\n Ainda assim,"
               "digite 1 se quiser reiniciar tanto o programa de servidores, quanto o de veiculos. \n "
               "Ou outro valor se quiser sair e excluir os veiculos manualmente.\n");
    }
    if(!reinicio_valido)
    {
        scanf("%d", &reinicio);
        switch (reinicio)
        {
            case reiniciar_tudo:
                iniciar_veiculos(veiculos, f_veiculo);
                iniciar_servidores(servidores, f_servidor, f_veiculo);
                break;
            default:
                return;
        }
    }
}
void liberar_servidores(struct servidor *servidores[TAM])
{
    for (int i = 1; i < TAM; ++i)
    {
        if(servidores[i] != NULL)
        {
            free(servidores[i]);
        }
    }
}

void inserir_servidor(struct servidor *servidores[TAM],
                      char *codigos_servidor, char *nomes, char *SIAPEs, char *RGs, char *CPFs, char *enderecos, char *salarios, char *datas_nascimento, char *tipos, FILE *f_servidor)
{
    fopen("f_servidor", "rb+");
    int index = -1;
    for (int i = 1; i < TAM; ++i)
    {
        if(servidores[i] == NULL)
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        printf("Não há memória disponível. Tente liberar espaço ou reiniciar o programa.\n");
        return;
    }

    servidores[index] = malloc(sizeof(struct servidor));
    strcpy(servidores[index]->codigos_servidor, codigos_servidor);
    strcpy(servidores[index]->nomes, nomes);
    strcpy(servidores[index]->SIAPEs, SIAPEs);
    strcpy(servidores[index]->RGs, RGs);
    strcpy(servidores[index]->CPFs, CPFs);
    strcpy(servidores[index]->enderecos, enderecos);
    strcpy(servidores[index]->salarios, salarios);
    strcpy(servidores[index]->datas_nascimento, datas_nascimento);
    strcpy(servidores[index]->tipos, tipos);
    salvar_arquivo_servidor(servidores, f_servidor);
}

void listar_servidores(struct servidor *servidores[TAM], FILE *f_servidor)
{
    ler_arquivo_servidor(servidores, f_servidor);
    for (int i = 1; i < TAM; ++i)
    {
        if(servidores[i] != NULL)
        {
            detalhes_servidor(i, servidores);
        }
    }
    mostrar();
}

int pesquisa_por_codigo_servidor(struct servidor *servidores[TAM], char *info, FILE *f_servidor)
{
    ler_arquivo_servidor(servidores, f_servidor);
    for(int i = 1; i<TAM; i++)
    {
        if(servidores[i] != NULL)
        {
            if(!strcmp(info, servidores[i]->codigos_servidor))
            {
                detalhes_servidor(i, servidores);
                return 1;
            }
        }
    }
    return 0;
}

void pesquisa_por_codigo_servidor_ui(struct servidor *servidores[TAM], FILE *f_servidor)
{
    espaco();
    char info[255], valor_lido, pesquisa_valida;
    do{
        ler("Digite o codigo do(a) servidor(a): \n(Se desejar sair, digite 'Sair')\n", info);
        valor_lido = campo_obrigatorio(info);
        pesquisa_valida = pesquisa_por_codigo_servidor(servidores, info, f_servidor);
        if (!strcmp(info, "Sair\n"))
        {
            return;
        }
        if (pesquisa_valida == 0 && valor_lido == 1)
        {
            printf("Nao foi encontrado servidor(a) com este codigo. Tente novamente.\n");
        }
        mostrar();
    } while(!valor_lido||!pesquisa_valida);
}

void inserir_servidor_ui(struct servidor *servidores[TAM], FILE *f_servidor)
{
    espaco();
    int valor_lido[6] = {1,1,1,1,1,1};
    int valor_existente[3] = {1,1,1};
    char codigos_servidor[255];
    do{
        ler("\nDigite o codigo do(a) servidor(a) (CAMPO OBRIGATORIO): ",codigos_servidor);
        valor_lido[0] = campo_obrigatorio(codigos_servidor);
        if(!valor_lido[0])
        {
            printf("O campo deve ser preenchido.\n");
        }
        for(int i = 1; i<TAM; i++)
        {
            if(servidores[i] != NULL)
            {
                valor_existente[0] = strcmp(codigos_servidor, servidores[i]->codigos_servidor);
            }
            if(!valor_existente[0])
            {
                break;
            }
        }
        if(!valor_existente[0])
        {
            printf("Um(a) servidor(a) com essa informacao ja foi cadastrado. Tente novamente.");
        }
    } while(!valor_lido[0] || !valor_existente[0]);
    char nomes[255];
    do{
        ler("\nDigite o nome (CAMPO OBRIGATORIO): ", nomes);
        valor_lido[1] = campo_obrigatorio(nomes);
        if(!valor_lido[1])
        {
            printf("O campo deve ser preenchido.\n");
        }
    } while(!valor_lido[1]);
    tornar_caract_maiusculo(nomes, nomes);
    char SIAPEs[255];
    do{
        ler("\nDigite o SIAPE (CAMPO OBRIGATORIO): ", SIAPEs);
        valor_lido[2] = campo_obrigatorio(SIAPEs);
        if(!valor_lido[2])
        {
            printf("O campo deve ser preenchido.\n");
        }
        for(int i = 1; i<TAM; i++)
        {
            if(servidores[i] != NULL)
            {
                valor_existente[1] = strcmp(SIAPEs, servidores[i]->SIAPEs);
                if(valor_existente[1] == 0)
                {
                    break;
                }
            }
        }
        if(!valor_existente[1])
        {
            printf("Um(a) servidor(a) com essa informacao ja foi cadastrado. Tente novamente.");
        }
    } while(!valor_lido[2] || !valor_existente[1]);
    char RGs[255];
    ler("\nDigite o RG: ", RGs);
    char CPFs[255];
    do{
        ler("\nDigite o CPF (CAMPO OBRIGATORIO): ", CPFs);
        valor_lido[3] = campo_obrigatorio(CPFs);
        if(!valor_lido[3])
        {
            printf("O campo deve ser preenchido.\n");
        }
        for(int i = 1; i<TAM; i++)
        {
            if(servidores[i] != NULL)
            {
                valor_existente[2] = strcmp(CPFs, servidores[i]->CPFs);
            }
            if(!valor_existente[2])
            {
                break;
            }
        }
        if(!valor_existente[2])
        {
            printf("Um(a) servidor(a) com essa informacao ja foi cadastrado. Tente novamente.");
        }
    } while(!valor_lido[3] || !valor_existente[2]);
    char enderecos[255];
    ler("\nDigite o endereço: ", enderecos);
    char salarios[255];
    ler("\nDigite o salario: R$", salarios);
    char datas_nascimento[255];
    do{
        ler("\nDigite a data de nascimento (NO FORMATO 'ddmmaa') (CAMPO OBRIGATORIO): ", datas_nascimento);
        valor_lido[4] = campo_obrigatorio(datas_nascimento);
        if(!valor_lido[4])
        {
            printf("O campo deve ser preenchido.\n");
        }
    } while(!valor_lido[4]);
    char tipos[255];
    do{
        ler("\nDigite 1 se for 'Docente' ou 2 se for 'Tecnico Administrativo' (Ou pressione 'Enter' se nao quiser adicionar essa informacao): ", tipos);
        valor_lido[5] = campo_obrigatorio(tipos);
        if(!strcmp(tipos, "1\n"))
        {
            strcpy(tipos, "Docente");
            valor_lido[5] = 0;
        }
        if(!strcmp(tipos, "2\n"))
        {
            strcpy(tipos, "Tecnico Administrativo");
            valor_lido[5] = 0;
        }
    } while(valor_lido[5] == 1);
    inserir_servidor(servidores, codigos_servidor, nomes, SIAPEs, RGs, CPFs, enderecos, salarios, datas_nascimento, tipos, f_servidor);
}

void listagem_alfabetica_servidor(struct servidor *servidores[TAM], FILE *f_servidor)
{
    ler_arquivo_servidor(servidores, f_servidor);
    char indices[TAM];
    for(int i = 1; i<TAM; i++)
    {
        indices[i] = 0;
    }
    for (int i = 1; i<TAM; i++)
    {
        if(servidores[i] != NULL)
        {
            indices[i] = i;
        }
    }
    for (int i=1;i<TAM;i++)
    {
        for (int j=1;j<TAM - i;j++)
        {
            if (servidores[indices[j]] != NULL && servidores[indices[j+1]] != NULL && strcmp(servidores[indices[j]]->nomes, servidores[indices[j+1]]->nomes) > 0)
            {
                int aux = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = aux;
            }
        }
    }
    for (int i = 1; i<TAM; i++)
    {
        detalhes_servidor(indices[i], servidores);
    }
    mostrar();
}

void listagem_por_tipo(char *c, struct servidor *servidores[TAM], FILE *f_servidor)
{
    ler_arquivo_servidor(servidores, f_servidor);
    char indices[TAM];
    for(int i = 1; i<TAM; i++)
    {
        indices[i] = 0;
    }
    for (int i = 1; i<TAM; i++)
    {
        if((servidores[i] != NULL))
        {
            if(!strcmp(servidores[i]->tipos, c))
            {
                for(int j = 1; j<TAM; j++)
                {
                    if(!indices[j])
                    {
                        indices[j] = i;
                        break;
                    }
                }
            }
        }
    }
    for (int i=1;i<TAM;i++) {
        for (int j=1;j<TAM - i;j++) {
            if (servidores[indices[j]] != NULL && servidores[indices[j+1]] != NULL && strcmp(servidores[indices[j]]->nomes, servidores[indices[j+1]]->nomes) > 0)
            {
                int aux = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = aux;
            }
        }
    }
    for (int i = 1; i<TAM; i++)
    {
        if (servidores[indices[i]] != NULL)
        {
            detalhes_servidor(indices[i], servidores);
        }
    }
    mostrar();
}

void excluir_servidor_ui(struct servidor *servidores[TAM], FILE *f_servidor, FILE *f_veiculo)
{
    ler_arquivo_servidor(servidores, f_servidor);
    espaco();
    enum escolha_para_remocao{remover_na_hora = 1, remover_manualmente}excluir_na_hora;
    char info[255], valor_lido, excluir_valido, posses_veic = -1;
    do{
        ler("Digite o codigo do(a) servidor(a) a ser excluido(a) (Se quiser sair do processo, digite 'Sair'): \n", info);
        valor_lido = campo_obrigatorio(info);
        if(!valor_lido)
        {
            printf("O campo deve ser preenchido.\n");
        }
        if (!strcmp(info, "Sair\n"))
        {
            return;
        }
        if(valor_lido)
        {
            for(int i = 1; i<TAM; i++)
            {
                if(servidores[i] != NULL)
                {
                    if(!strcmp(info, servidores[i]->codigos_servidor))
                    {
                        excluir_valido = 1;
                        break;
                    } else{
                        excluir_valido = 0;
                    }
                }
            }
        }
        if(valor_lido && excluir_valido)
        {
            posses_veic = qtd_de_veic(info);
            printf("O(a) servidor(a) possui %d veiculo(s) cadastrado(s).\n", posses_veic);
        }
        if(posses_veic == 0 && excluir_valido)
        {
            printf("Como o(a) servidor(a) nao possui veiculo(s) cadastrado(s), ele(a) ja foi excluido(a).\n");
            excluir_servidor(info, servidores, f_servidor);
        }
        if(posses_veic > 0 && excluir_valido)
        {
            do{
                printf("Eh recomendado que o(s) veiculo(s) cadastrado(s) seja(m) excluido(s) manualmente.\n Ainda assim, "
                       "digite 1 se quiser que o(a) servidor(a) "
                       "e o(s) veiculo(s) dele(a) seja(m) excluido(s) ou 2 se desejar excluir os veiculos dele(a) manualmente.\n");
                scanf("%d", &excluir_na_hora);
                switch(excluir_na_hora)
                {
                    case remover_na_hora:
                        remover_veiculos_com_servidor(info, f_veiculo);
                        excluir_servidor(info, servidores, f_servidor);
                        printf("O(a) servidor(a) e o(s) veiculo(s) foram excluidos.");
                        break;
                    case remover_manualmente:
                        return;
                    default:
                        printf("Opcao invalida. Digite novamente.\n");
                        break;
                }
            } while(excluir_na_hora != 1);
        }
        if (!excluir_valido && valor_lido == 1)
        {
            printf("Nao foi encontrado(a) servidor(a) com este codigo. Tente novamente.\n");
        }
    } while(!valor_lido|| posses_veic == -1);
    mostrar();
}

void excluir_servidor(char *info, struct servidor *servidores[TAM], FILE *f_servidor)
{
    for(int i = 1; i<TAM; i++)
    {
        if(servidores[i] != NULL)
        {
            if(!strcmp(info, servidores[i]->codigos_servidor))
            {
                free(servidores[i]);
                servidores[i] = NULL;
                salvar_arquivo_servidor(servidores, f_servidor);
            }
        }
    }
}

void alterar_cadastro_servidor(struct servidor *servidores[TAM], char *info, int index, int op, FILE *f_servidor)
{
    ler_arquivo_servidor(servidores, f_servidor);
    enum alterar_serv{alt_codigo = 1, alt_nome, alt_SIAPE, alt_RG, alt_CPF, alt_endereco, alt_salario, alt_dat_nasc, alt_tipo}alteracao_serv;
    alteracao_serv = op;
    switch(alteracao_serv)
    {
        case alt_codigo:
            strcpy(servidores[index]->codigos_servidor, info);
            alteracao();
            salvar_arquivo_servidor(servidores, f_servidor);
            break;
        case alt_nome:
            strcpy(servidores[index]->nomes, info);
            alteracao();
            salvar_arquivo_servidor(servidores, f_servidor);
            break;
        case alt_SIAPE:
            strcpy(servidores[index]->SIAPEs, info);
            alteracao();
            salvar_arquivo_servidor(servidores, f_servidor);
            break;
        case alt_RG:
            strcpy(servidores[index]->RGs, info);
            alteracao();
            salvar_arquivo_servidor(servidores, f_servidor);
            break;
        case alt_CPF:
            strcpy(servidores[index]->CPFs, info);
            alteracao();
            salvar_arquivo_servidor(servidores, f_servidor);
            break;
        case alt_endereco:
            strcpy(servidores[index]->enderecos, info);
            alteracao();
            salvar_arquivo_servidor(servidores, f_servidor);
            break;
        case alt_salario:
            strcpy(servidores[index]->salarios, info);
            alteracao();
            salvar_arquivo_servidor(servidores, f_servidor);
            break;
        case alt_dat_nasc:
            strcpy(servidores[index]->datas_nascimento, info);
            alteracao();
            salvar_arquivo_servidor(servidores, f_servidor);
            break;
        case alt_tipo:
            strcpy(servidores[index]->tipos, info);
            alteracao();
            salvar_arquivo_servidor(servidores, f_servidor);
            break;
        default:
            break;
    }
}
void alterar_cadastro_servidor_ui(struct servidor *servidores[TAM], FILE *f_servidor)
{
    int valor_lido[6] = {1,1,1,1,1,1};
    int valor_existente[3] = {1,1,1};
    enum alterar_serv{alt_codigo = 1, alt_nome, alt_SIAPE, alt_RG, alt_CPF, alt_endereco, alt_salario, alt_dat_nasc, alt_tipo}alteracao_serv;
    char info[255];
    int valor_valido;
    int index = -1;
    do{
        espaco();
        ler("(Se desejar sair, digite 'Sair')\nDigite o codigo do(a) servidor(a):\n ", info);
        valor_valido = campo_obrigatorio(info);
        if (!strcmp(info, "Sair\n"))
        {
            return;
        }
        if(!valor_valido)
        {
            printf("O campo deve ser preenchido.\n");
        }
        for(int i = 1; i<TAM; i++)
        {
            if(servidores[i] != NULL)
            {
                if(!strcmp(servidores[i]->codigos_servidor, info))
                {
                    index = i;
                    printf("O(a) servidor(a) selecionado foi %s. \n\n", servidores[index]->nomes);
                    break;
                }
            }
        }
        if(index == -1 && valor_valido != 0)
        {
            printf("Codigo invalido! Pressione 'Enter' para repetir o processo.\n");
        }
    } while(!valor_valido || index == -1);
    if(valor_valido == 1)
    {
        printf("Digite o que voce deseja alterar desse(a) servidor(a): \n1. Codigo. \n2. Nome. \n3. SIAPE. \n4. RG. \n5. CPF. \n6. Endereco. \n7. Salario. \n8. Data de nascimento. \n9. Tipo(Docente ou Tecnico Administrativo). \nOu outro valor se deseja sair.\n");
        scanf("%d", &alteracao_serv);
        char codigos_servidor[255];
        char nomes[255];
        char SIAPEs[255];
        char RGs[255];
        char CPFs[255];
        char enderecos[255];
        char salarios[255];
        char datas_nascimento[255];
        char tipos[255];
        switch(alteracao_serv)
        {
            case alt_codigo:
                do{
                    espaco();
                    ler("Digite o novo codigo: \n", codigos_servidor);
                    valor_lido[0] = campo_obrigatorio(codigos_servidor);
                    if(!valor_lido[0])
                    {
                        printf("O campo deve ser preenchido.\n");
                    }
                    for(int i = 1; i<TAM; i++)
                    {
                        if(servidores[i] != NULL)
                        {
                            valor_existente[0] = strcmp(codigos_servidor, servidores[i]->codigos_servidor);
                        }
                        if(!valor_existente[0])
                        {
                            break;
                        }
                    }
                    if(!valor_existente[0])
                    {
                        printf("Um(a) servidor(a) com essa informacao ja foi cadastrado. Tente novamente.");
                    }
                } while(!valor_lido[0] || !valor_existente[0]);
                alterar_cadastro_servidor(servidores, codigos_servidor, index, alteracao_serv, f_servidor);
                break;
            case alt_nome:
                do{
                    espaco();
                    ler("Digite o novo nome: \n", nomes);
                    valor_lido[1] = campo_obrigatorio(nomes);
                    tornar_caract_maiusculo(nomes, nomes);
                    if(!valor_lido[1])
                    {
                        printf("O campo deve ser preenchido.\n");
                    }
                } while(!valor_lido[1]);
                alterar_cadastro_servidor(servidores, nomes, index, alteracao_serv, f_servidor);
                break;
            case alt_SIAPE:
                do{
                    espaco();
                    ler("Digite o novo SIAPE: \n", SIAPEs);
                    valor_lido[2] = campo_obrigatorio(SIAPEs);
                    if(!valor_lido[2])
                    {
                        printf("O campo deve ser preenchido.\n");
                    }
                    for(int i = 1; i<TAM; i++)
                    {
                        if(servidores[i] != NULL)
                        {
                            valor_existente[1] = strcmp(SIAPEs, servidores[i]->SIAPEs);
                        }
                        if(!valor_existente[1])
                        {
                            break;
                        }
                    }
                    if(!valor_existente[1])
                    {
                        printf("Um(a) servidor(a) com essa informacao ja foi cadastrado. Tente novamente.");
                    }
                } while (!valor_existente[1] || !valor_lido[2]);
                alterar_cadastro_servidor(servidores, SIAPEs, index, alteracao_serv, f_servidor);
                break;
            case alt_RG:
                espaco();
                ler("Digite o novo RG: \n", RGs);
                alterar_cadastro_servidor(servidores, RGs, index, alteracao_serv, f_servidor);
                break;
            case alt_CPF:
                do{
                    espaco();
                    ler("Digite o novo CPF: \n", CPFs);
                    valor_lido[3] = campo_obrigatorio(CPFs);
                    if(!valor_lido[3])
                    {
                        printf("O campo deve ser preenchido.\n");
                    }
                    for(int i = 1; i<TAM; i++)
                    {
                        if(servidores[i] != NULL)
                        {
                            valor_existente[2] = strcmp(CPFs, servidores[i]->CPFs);
                        }
                        if(!valor_existente[2])
                        {
                            break;
                        }
                    }
                    if(!valor_existente[2])
                    {
                        printf("Um(a) servidor(a) com essa informacao ja foi cadastrado. Tente novamente.");
                    }
                } while (!valor_existente[2] || !valor_lido[3]);
                alterar_cadastro_servidor(servidores, CPFs, index, alteracao_serv, f_servidor);
                break;
            case alt_endereco:
                espaco();
                ler("Digite o novo endereço: \n", enderecos);
                alterar_cadastro_servidor(servidores, enderecos, index, alteracao_serv, f_servidor);
                break;
            case alt_salario:
                espaco();
                ler("Digite o novo salario: \n", salarios);
                alterar_cadastro_servidor(servidores, salarios, index, alteracao_serv, f_servidor);
                break;
            case alt_dat_nasc:
                do{
                    espaco();
                    ler("Digite a nova data de nascimento: \n", datas_nascimento);
                    valor_lido[4] = campo_obrigatorio(datas_nascimento);
                    if(!valor_lido[4])
                    {
                        printf("O campo deve ser preenchido.\n");
                    }
                } while(!valor_lido[4]);
                alterar_cadastro_servidor(servidores, datas_nascimento, index, alteracao_serv, f_servidor);
                break;
            case alt_tipo:
                do{
                    espaco();
                    ler("Digite 1 para 'Docente' ou 2 para 'Tecnico Administrativo'. \n", tipos);
                    valor_lido[5] = campo_obrigatorio(tipos);
                    if(!strcmp(tipos, "1\n"))
                    {
                        strcpy(tipos, "Docente");
                        valor_lido[5] = 0;
                    }
                    if(!strcmp(tipos, "2\n"))
                    {
                        strcpy(tipos, "Tecnico Administrativo");
                        valor_lido[5] = 0;
                    }
                } while(valor_lido[5] == 1);
                alterar_cadastro_servidor(servidores, tipos, index, alteracao_serv, f_servidor);
                break;
            default:
                break;
        }
    }
}
