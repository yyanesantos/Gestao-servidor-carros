#include "veiculo.h"
#include "util.h"

void salvar_arquivo_veiculo(struct veiculo *veiculos[TAM_VEICULO], FILE *f_veiculo)
{
    char indices[TAM_VEICULO];
    for (int i = 1; i<TAM_VEICULO; i++)
    {
        indices[i] = 0;
    }
    for (int i = 1; i < TAM_VEICULO; ++i)
    {
        if(veiculos[i] != NULL)
        {
            for (int j = 1; j < TAM_VEICULO; ++j) {
                if(!indices[j])
                {
                    indices[j] = j;
                    break;
                }
            }
        }
    }
    f_veiculo = fopen("veiculo.bin", "wb");
    if(f_veiculo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    fseek(f_veiculo, 0, SEEK_END);
    for(int i = 1; i<TAM_VEICULO; i++)
    {
        if(indices[i] != 0)
        {
            fwrite(veiculos[indices[i]], sizeof(struct veiculo), 1, f_veiculo);
        }
    }
    fclose(f_veiculo);
}

void ler_arquivo_veiculo(struct veiculo *veiculos[TAM_VEICULO], FILE *f_veiculo)
{
    int lido;
    f_veiculo = fopen("veiculo.bin", "rb+");
    if(f_veiculo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    for(int i = 1; i<TAM_VEICULO; i++)
    {
        veiculos[i] = malloc(sizeof(struct veiculo));
        fseek(f_veiculo, sizeof(struct veiculo)*(i - 1), SEEK_SET);
        lido = fread(veiculos[i], sizeof(struct veiculo), 1, f_veiculo);
        if (lido == 0) {
            veiculos[i] = NULL;
            free(veiculos[i]);
            break;
        }
    }
    fclose(f_veiculo);
}

void detalhes_veiculo(int i, struct veiculo *veiculos[TAM_VEICULO])
{
    struct veiculo *c = veiculos[i];
    if(c == NULL)
    {
        return;
    }
    printf(" Codigo do(a) servidor(a): %s Codigo veiculo: %s Marca: %s Descricao: %s Placa: %s Modelo: %s\n",
           c->codigos_servidor_2, c->codigos_veiculo, c->marcas, c->descricaos, c->placas, c->modelos);
}

int obter_nome_servidor(char *info, FILE *f_servidor)
{
    extern struct servidor *servidores[TAM];
    ler_arquivo_servidor(servidores, f_servidor);
    for(int i = 1; i<TAM; i++){
        if(servidores[i] != NULL){
            if(!strcmp(info, servidores[i]->codigos_servidor)){
                printf("Proprietario(a) do veiculo: %s", servidores[i]->nomes);
                return 1;
            }
        }
    }
    if(!strcmp(info, "\n"))
    {
        return 1;
    }
    return 0;
}

void iniciar_veiculos(struct veiculo *veiculos[TAM_VEICULO], FILE *f_veiculo)
{
    for (int i = 1; i < TAM_VEICULO; ++i)
    {
        veiculos[i] = NULL;
    }
    salvar_arquivo_veiculo(veiculos, f_veiculo);
}

void liberar_veiculos(struct veiculo *veiculos[TAM_VEICULO])
{
    for (int i = 1; i < TAM_VEICULO; ++i)
    {
        if(veiculos[i] != NULL)
            free(veiculos[i]);
    }
}

void inserir_veiculo(struct veiculo *veiculos[TAM_VEICULO],
                     char *codigos_servidor_2, char *codigos_veiculo, char *marcas, char *descricaos, char *placas, char *modelos, FILE *f_veiculo) {
    int index = -1;
    for (int i = 1; i < TAM_VEICULO; ++i) {
        if (veiculos[i] == NULL)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Não há memória disponível. Tente liberar espaço ou reiniciar o programa.\n");
        return;
    }

    veiculos[index] = malloc(sizeof(struct veiculo));
    strcpy(veiculos[index]->codigos_servidor_2, codigos_servidor_2);
    strcpy(veiculos[index]->codigos_veiculo, codigos_veiculo);
    strcpy(veiculos[index]->marcas, marcas);
    strcpy(veiculos[index]->descricaos, descricaos);
    strcpy(veiculos[index]->placas, placas);
    strcpy(veiculos[index]->modelos, modelos);
    salvar_arquivo_veiculo(veiculos, f_veiculo);
}

void inserir_veiculo_ui(struct veiculo *veiculos[TAM_VEICULO], FILE *f_veiculo, FILE *f_servidor)
{
    espaco();
    int valor_lido[6] = {1,1,1,1,1,1};
    int valor_existente[2] = {1,1};
    int dono;
    char codigos_servidor_2[255];
    do{
        ler("\nDigite o codigo do(a) servidor(a) (CAMPO OBRIGATORIO):  " ,codigos_servidor_2);
        printf("(Se o servidor(a) ainda nao tiver sido adicionado(a), digite 'Sair')\n");
        valor_lido[0] = campo_obrigatorio(codigos_servidor_2);
        if(!strcmp(codigos_servidor_2, "Sair\n"))
        {
            return;
        }
        if(!valor_lido[0])
        {
            printf("O campo deve ser preenchido.\n");
        }
        dono = obter_nome_servidor(codigos_servidor_2, f_servidor);
        if(!dono)
        {
            printf("Nao foi encontrado servidor(a) com esse codigo. Tente novamente.");
        }
    } while(!valor_lido[0] || !dono);
    char codigos_veiculo[255];
    do{
        ler("\nDigite o codigo do veiculo (CAMPO OBRIGATORIO):  ",codigos_veiculo);
        valor_lido[1] = campo_obrigatorio(codigos_veiculo);
        if(!valor_lido[1])
        {
            printf("O campo deve ser preenchido.\n");
        }
        for(int i = 1; i<TAM_VEICULO; i++)
        {
            if(veiculos[i] != NULL)
            {
                valor_existente[0] = strcmp(codigos_veiculo, veiculos[i]->codigos_veiculo);
                if(!valor_existente[0])
                {
                    break;
                }
            }
        }
        if(!valor_existente[0]){
            printf("Um veiculo com essa informacao ja foi cadastrado. Tente novamente.");
        }
    } while(!valor_lido[1] || !valor_existente[0]);
    char marcas[255];
    do{
        ler("\nDigite a marca do veiculo (CAMPO OBRIGATORIO):  ", marcas);
        valor_lido[2] = campo_obrigatorio(marcas);
        if(!valor_lido[2])
        {
            printf("O campo deve ser preenchido.\n");
        }
    } while(valor_lido[2] == 0);
    char descricaos[255];
    do{
        ler("\nDigite a descricao do veiculo (CAMPO OBRIGATORIO):  ", descricaos);
        valor_lido[3] = campo_obrigatorio(descricaos);
        if(!valor_lido[3])
        {
            printf("O campo deve ser preenchido.\n");
        }
        for(int i = 1; i<TAM_VEICULO; i++){
            if(veiculos[i] != NULL){
                valor_existente[1] = strcmp(descricaos, veiculos[i]->descricaos);
            }
            if(!valor_existente[1])
            {
                break;
            }
        }
        if(!valor_existente[1]){
            printf("Um veiculo com essa informacao ja foi cadastrado. Tente novamente.");
        }
    } while(valor_lido[3] == 0 || valor_existente[1] == 0);
    char placas[255];
    do{
        ler("\nDigite a placa do veiculo (NO FORMATO 'ABC1234') (CAMPO OBRIGATORIO): ", placas);
        valor_lido[4] = campo_obrigatorio(placas);
        if(!valor_lido[4])
        {
            printf("O campo deve ser preenchido.\n");
        }
    } while(valor_lido[4] == 0);
    char modelos[255];
    do{
        ler("\nDigite o modelo do veiculo (CAMPO OBRIGATORIO): ", modelos);
        valor_lido[5] = campo_obrigatorio(modelos);
        if(!valor_lido[5])
        {
            printf("O campo deve ser preenchido.\n");
        }
    } while(valor_lido[5] == 0);
    inserir_veiculo(veiculos, codigos_servidor_2, codigos_veiculo, marcas, descricaos, placas, modelos, f_veiculo);
}

int pesquisa_por_codigo_veiculo(struct veiculo *veiculos[TAM_VEICULO], char *info, FILE *f_veiculo, FILE *f_servidor)
{
    ler_arquivo_veiculo(veiculos, f_veiculo);
    for(int i = 1; i<TAM_VEICULO; i++)
    {
        if(veiculos[i] != NULL)
        {
            if(!strcmp(info, veiculos[i]->codigos_veiculo))
            {
                detalhes_veiculo(i, veiculos);
                obter_nome_servidor(veiculos[i]->codigos_servidor_2, f_servidor);
                mostrar();
                return 1;
            }
        }
    }
    return 0;
}

void pesquisa_por_codigo_veiculo_ui(struct veiculo *veiculos[TAM_VEICULO], FILE *f_veiculo, FILE *f_servidor)
{
    espaco();
    char info[255], valor_lido, pesquisa_valida;
    do{
        ler("Digite o codigo do veiculo: \n(Se desejar sair, digite 'Sair')\n", info);
        valor_lido = campo_obrigatorio(info);
        pesquisa_valida = pesquisa_por_codigo_veiculo(veiculos, info, f_veiculo, f_servidor);
        if (!strcmp(info, "Sair\n"))
        {
            return;
        }
        if (pesquisa_valida == 0 && valor_lido == 1){
            printf("Nao foi encontrado veiculo com este codigo. Pressione 'Enter' duas vezes para tentar "
                   "novamente.\n");
        }
        mostrar();
    } while(!valor_lido||!pesquisa_valida);
}

int excluir_veiculo(char *info, struct veiculo *veiculos[TAM_VEICULO], FILE *f_veiculo)
{
    for(int i = 1; i<TAM_VEICULO; i++)
    {
        if(veiculos[i] != NULL)
        {
            if(!strcmp(info, veiculos[i]->codigos_veiculo))
            {
                free(veiculos[i]);
                veiculos[i] = NULL;
                salvar_arquivo_veiculo(veiculos, f_veiculo);
                return 1;
            }
        }
    }
    return 0;
}

void excluir_veiculo_ui(struct veiculo *veiculos[TAM_VEICULO], FILE *f_veiculo)
{
    char info[255], valor_lido, valor_existente;
    do{
        espaco();
        ler("Digite o codigo do veiculo a ser excluido (Se desejar sair, digite 'Sair'): \n", info);
        valor_lido = campo_obrigatorio(info);
        valor_existente = excluir_veiculo(info, veiculos, f_veiculo);
        if (!strcmp(info, "Sair\n")) {
            return;
        }
        if (valor_existente == 0 && valor_lido == 1){
            printf("Nao foi encontrado veiculo com este codigo. Tente novamente.\n");
        }
        if(valor_existente && valor_lido)
        {
            printf("Excluido com sucesso. Pressione 'Enter' duas vezes para continuar.\n");
            mostrar();
        }
    } while(!valor_lido||!valor_existente);
}

void alterar_cadastro_veiculo_ui(struct veiculo *veiculos[TAM_VEICULO], FILE *f_veiculo, FILE *f_servidor)
{
    enum alterar_veiculo{alt_codigo_serv = 1, alt_codigo_veic, alt_marca, alt_descricao, alt_placa, alt_modelo}alteracao_veic;
    char info[255];
    int valor_lido[6] = {1,1,1,1,1,1};
    int valor_existente[2] = {1,1};
    int campo_preenchido, dono;
    int index = -1;
    do{
        espaco();
        ler("(Se desejar sair, digite 'Sair')\nDigite o codigo do veiculo:\n ", info);
        campo_preenchido = campo_obrigatorio(info);
        if (!strcmp(info, "Sair\n"))
        {
            return;
        }
        if(!campo_preenchido)
        {
            printf("O campo deve ser preenchido.\n");
        }
        for(int i = 1; i<TAM_VEICULO; i++)
        {
            if(veiculos[i] != NULL)
            {
                if(!strcmp(veiculos[i]->codigos_veiculo, info))
                {
                    index = i;
                    printf("O veiculo selecionado tem placa %s. \n\n", veiculos[index]->placas);
                    break;
                }
            }
        }
        if(index == -1 && campo_preenchido != 0 && strcmp(info, "Sair\n") != 0)
        {
            printf("Codigo invalido! Pressione 'Enter' para repetir o processo.\n");
        }
    } while(!campo_preenchido || index == -1);
    if(campo_preenchido == 1)
    {
        printf("Digite o que voce deseja alterar desse veiculo: \n1. Codigo do servidor(a). \n2. Codigo veiculo. \n3. Marca. \n4. Descricao. \n5. Placa. \n6. Modelo.\nOu outro valor se deseja sair.\n");
        scanf("%d", &alteracao_veic);
        char codigos_servidor_2[255];
        char codigos_veiculo[255];
        char marcas[255];
        char descricaos[255];
        char placas[255];
        char modelos[255];
        switch(alteracao_veic)
        {
            case alt_codigo_serv:
                do{
                    espaco();
                    ler("Digite o novo codigo do(a) servidor(a): ", codigos_servidor_2);
                    valor_lido[0] = campo_obrigatorio(codigos_servidor_2);
                    if(!valor_lido[0])
                    {
                        printf("O campo deve ser preenchido.\n");
                    }
                    dono = obter_nome_servidor(codigos_servidor_2, f_servidor);
                    if(!dono)
                    {
                        printf("Nao foi encontrado servidor com esse codigo. Tente novamente.");
                    }
                } while(!valor_lido[0] || !dono);
                alterar_cadastro_veiculo(veiculos, codigos_servidor_2, index, alteracao_veic, f_veiculo);
                break;
            case alt_codigo_veic:
                do{
                    espaco();
                    ler("\nDigite o novo codigo do veiculo: ",codigos_veiculo);
                    valor_lido[1] = campo_obrigatorio(codigos_veiculo);
                    if(!valor_lido[1])
                    {
                        printf("O campo deve ser preenchido.\n");
                    }
                    for(int i = 1; i<TAM_VEICULO; i++){
                        if(veiculos[i] != NULL){
                            valor_existente[0] = strcmp(codigos_veiculo, veiculos[i]->codigos_veiculo);
                            if(valor_existente[0] == 0){
                                break;
                            }
                        }
                    }
                    if(!valor_existente[0]){
                        printf("Um veiculo com essa informacao ja foi cadastrado. Tente novamente.");
                    }
                } while(valor_lido[1] == 0 || valor_existente[0] == 0);
                alterar_cadastro_veiculo(veiculos, codigos_veiculo, index, alteracao_veic, f_veiculo);
                break;
            case alt_marca:
                do{
                    espaco();
                    ler("Digite a nova marca: ", marcas);
                    valor_lido[2] = campo_obrigatorio(marcas);
                    if(!valor_lido[2])
                    {
                        printf("O campo deve ser preenchido.\n");
                    }
                } while(valor_lido[2] == 0);
                alterar_cadastro_veiculo(veiculos, marcas, index, alteracao_veic, f_veiculo);
                break;
            case alt_descricao:
                do{
                    espaco();
                    ler("Digite a nova descricao: ", descricaos);
                    valor_lido[3] = campo_obrigatorio(descricaos);
                    if(!valor_lido[3])
                    {
                        printf("O campo deve ser preenchido.\n");
                    }
                    for(int i = 1; i<TAM_VEICULO; i++){
                        if(veiculos[i] != NULL){
                            valor_existente[1] = strcmp(descricaos, veiculos[i]->descricaos);
                        }
                        if(!valor_existente[1])
                        {
                            break;
                        }
                    }
                    if(!valor_existente[1]){
                        printf("Um veiculo com essa informacao ja foi cadastrado. Tente novamente.");
                    }
                } while(valor_lido[3] == 0 || valor_existente[1] == 0);
                alterar_cadastro_veiculo(veiculos, descricaos, index, alteracao_veic, f_veiculo);
                break;
            case alt_placa:
                do{
                    espaco();
                    ler("Digite a nova placa: ", placas);
                    valor_lido[4] = campo_obrigatorio(placas);
                    if(!valor_lido[4])
                    {
                        printf("O campo deve ser preenchido.\n");
                    }
                } while(valor_lido[4] == 0);
                alterar_cadastro_veiculo(veiculos, placas, index, alteracao_veic, f_veiculo);
                break;
            case alt_modelo:
                do{
                    espaco();
                    ler("Digite o novo modelo: ", modelos);
                    valor_lido[5] = campo_obrigatorio(modelos);
                    if(!valor_lido[5])
                    {
                        printf("O campo deve ser preenchido.\n");
                    }
                } while(valor_lido[5] == 0);
                alterar_cadastro_veiculo(veiculos, modelos, index, alteracao_veic, f_veiculo);
                break;
            default:
                break;

        }
    }
}
void alterar_cadastro_veiculo(struct veiculo *veiculos[TAM_VEICULO], char *info, int index, int op, FILE *f_veiculo)
{
    enum alterar_veiculo{alt_codigo_serv = 1, alt_codigo_veic, alt_marca, alt_descricao, alt_placa, alt_modelo}alteracao_veic;
    alteracao_veic = op;
    switch(alteracao_veic)
    {
        case alt_codigo_serv:
            strcpy(veiculos[index]->codigos_servidor_2, info);
            salvar_arquivo_veiculo(veiculos, f_veiculo);
            alteracao();
            break;
        case alt_codigo_veic:
            strcpy(veiculos[index]->codigos_veiculo, info);
            salvar_arquivo_veiculo(veiculos, f_veiculo);
            alteracao();
            break;
        case alt_marca:
            strcpy(veiculos[index]->marcas, info);
            salvar_arquivo_veiculo(veiculos, f_veiculo);
            alteracao();
            break;
        case alt_descricao:
            strcpy(veiculos[index]->descricaos, info);
            salvar_arquivo_veiculo(veiculos, f_veiculo);
            alteracao();
            break;
        case alt_placa:
            strcpy(veiculos[index]->placas, info);
            salvar_arquivo_veiculo(veiculos, f_veiculo);
            alteracao();
            break;
        case alt_modelo:
            strcpy(veiculos[index]->modelos, info);
            salvar_arquivo_veiculo(veiculos, f_veiculo);
            alteracao();
            break;
        default:
            break;
    }
}

int listagem_todos_veic_servidor(struct veiculo *veiculos[TAM_VEICULO], char *info, FILE *f_veiculo, FILE *f_servidor)
{
    extern struct servidor *servidores[TAM];
    ler_arquivo_veiculo(veiculos, f_veiculo);
    ler_arquivo_servidor(servidores, f_servidor);
    int existe_serv_sem_veiculo;
    for(int i = 1; i<TAM_VEICULO; i++)
    {
        if((veiculos[i] != NULL) && (!strcmp(info, veiculos[i]->codigos_servidor_2)))
        {
            detalhes_veiculo(i, veiculos);
            obter_nome_servidor(info, f_servidor);
            printf("\n");
        }
    }
    for(int i = 1; i<TAM_VEICULO; i++)
    {
        if(veiculos[i] != NULL)
        {
            if(!strcmp(info, veiculos[i]->codigos_servidor_2))
            {
                mostrar();
                return 1;
            }
        }
    }
    for(int i = 1; i<TAM; i++)
    {
        if(servidores[i] != NULL) {
            if (!strcmp(info, servidores[i]->codigos_servidor)) {
                existe_serv_sem_veiculo = -1;
                return existe_serv_sem_veiculo;
            }
        }
    }
    return 0;
}

void listagem_todos_veic_servidor_ui(struct veiculo *veiculos[TAM_VEICULO], FILE *f_veiculo, FILE *f_servidor)
{
    ler_arquivo_veiculo(veiculos, f_veiculo);
    char info[255];
    int valor_lido, valor_existente;
    do{
        espaco();
        ler("\n(Se desejar sair, digite 'Sair'.)\nDigite o codigo do(a) servidor(a): \n", info);
        valor_lido = campo_obrigatorio(info);
        if(!strcmp(info, "Sair\n"))
        {
            return;
        }
        if(!valor_lido)
        {
            printf("O campo deve ser preenchido.\n");
        }
        if(valor_lido == 1)
        {
            valor_existente = listagem_todos_veic_servidor(veiculos, info, f_veiculo, f_servidor);
        }
        if(valor_existente == 1)
        {
            printf("Pressione 'Enter' duas vezes para continuar. \n");
        }
        if(valor_lido == 1 && !valor_existente)
        {
            printf("Codigo invalido. Por favor, repita o processo.\n");
        }
        if(valor_existente == -1 && valor_lido == 1)
        {
            printf("O(a) servidor(a) nao possui veiculo(s) cadastrado(s). \n");
            mostrar();
        }
    } while(!valor_existente || !valor_lido);
}

int listagem_alfab_todos_veic_servidor(struct veiculo *veiculos[TAM_VEICULO], struct servidor *servidores[TAM], char *info, FILE *f_veiculo, FILE *f_servidor)
{
    int existe_serv_sem_veiculo;
    ler_arquivo_veiculo(veiculos, f_veiculo);
    ler_arquivo_servidor(servidores, f_servidor);
    char indices[TAM_VEICULO];
    for(int i = 1; i<TAM_VEICULO; i++)
    {
        indices[i] = 0;
    }
    for (int i = 1; i<TAM_VEICULO; i++)
    {
        if((veiculos[i] != NULL) && !strcmp(veiculos[i]->codigos_servidor_2, info))
        {
            for(int j = 1; j<TAM_VEICULO; j++)
            {
                if(!indices[j])
                {
                    indices[j] = i;
                    break;
                }
            }
        }
    }
    for (int i=1;i<TAM_VEICULO;i++) {
        for (int j=1;j<TAM_VEICULO - i;j++) {
            if (veiculos[indices[j]] != NULL && veiculos[indices[j+1]] != NULL && strcmp(veiculos[indices[j]]->modelos, veiculos[indices[j+1]]->modelos) > 0)
            {
                int aux = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = aux;
            }
        }
    }
    for (int i = 1; i<TAM_VEICULO; i++)
    {
        if (veiculos[indices[i]] != NULL)
        {
            detalhes_veiculo(indices[i], veiculos);
            obter_nome_servidor(veiculos[indices[i]]->codigos_servidor_2, f_servidor);
        }
    }
    for (int i = 1; i<TAM_VEICULO; i++)
    {
        if((veiculos[i] != NULL))
        {
            if(!strcmp(veiculos[i]->codigos_servidor_2, info))
            {
                mostrar();
                return 1;
            }
        }
    }
    for(int i = 1; i<TAM; i++)
    {
        if(servidores[TAM] != NULL)
        {
            if (!strcmp(info, servidores[i]->codigos_servidor)) {
                existe_serv_sem_veiculo = -1;
                return existe_serv_sem_veiculo;
            }
        }
    }
    return 0;
}


void listagem_alfab_todos_veic_servidor_ui(struct veiculo *veiculos[TAM_VEICULO], FILE *f_veiculo, FILE *f_servidor)
{
    extern struct servidor *servidores[TAM];
    ler_arquivo_veiculo(veiculos, f_veiculo);
    char info[255];
    int valor_lido, valor_existente;
    do{
        espaco();
        ler("(Se desejar sair, digite 'Sair'.)\nDigite o codigo do(a) servidor(a) para listar o(s) veiculo(s) dele(a): \n", info);
        valor_lido = campo_obrigatorio(info);
        if(!strcmp(info, "Sair\n"))
        {
            return;
        }
        if(!valor_lido)
        {
            printf("O campo deve ser preenchido.\n");
        }
        if(valor_lido == 1)
        {
            valor_existente = listagem_alfab_todos_veic_servidor(veiculos, servidores, info, f_veiculo, f_servidor);
        }
        if(valor_lido == 1 && !valor_existente)
        {
            printf("Codigo invalido. Por favor, repita o processo.\n");
        }
        if(valor_existente == -1 && valor_lido == 1)
        {
            printf("O(a) servidor(a) nao possui veiculos cadastrados. \n");
        }
    } while(!valor_existente || !valor_lido);
}