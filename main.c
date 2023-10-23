#include "servidor.h"
#include "veiculo.h"
#include "util.h"
struct servidor *servidores[TAM];
struct veiculo *veiculos[TAM_VEICULO];
FILE *f_servidor;
FILE *f_veiculo;
int main()
{
    f_veiculo = fopen("veiculo.bin", "rb+");
    if (f_veiculo == NULL)
    {
        f_veiculo = fopen("veiculo.bin", "wb+");
        iniciar_veiculos(veiculos, f_veiculo);
    }
    if (f_veiculo == NULL)
    {
        printf("Erro: Nao foi possivel abrir o arquivo veiculo.\n");
        return -1;
    }

    f_servidor = fopen("servidor.bin", "rb+");
    if (f_servidor == NULL)
    {
        f_servidor = fopen("servidor.bin", "wb+");
        iniciar_servidores(servidores, f_servidor, f_veiculo);
    }

    if (f_servidor == NULL)
    {
        printf("Erro: Nao foi possivel abrir o arquivo servidor.\n");
        return -1;
    }

    int info;
    enum menu_servidor{cadastro_servidor = 1, listagem_servidores, pesquisar_servidor, excluir_servi, reiniciar_programa_serv, alterar_cadastro_serv, sair_prog_serv} menu_servidor;
    enum servidor_listagem{listagem_servidor = 1, listagem_alfab, listagem_docente, listagem_TA} listagem_serv;
    enum menu_veiculo{cadastro_veiculo = 1, listagem_veiculos, pesquisar_veiculo, excluir_vei, alterar_cadastro_veic, reiniciar_programa_veic, sair_prog_veic} menu_veiculo;
    enum veiculo_listagem{listagem_todos_veic_por_serv = 1, listagem_alfab_todos_veic_por_serv} listagem_veic;
    enum menus {menu_serv = 1, menu_veic, sair_programa_main} menu;
    do {
        printf("\n----------MENU----------\n");
        printf("Digite 1 para acessar o menu dos servidores, 2 para acessar o menu dos veiculos ou 3 para sair do programa. \n\n(Eh recomendado o cadastro de um servidor antes de acessar o menu dos veiculos.)\n");
        printf("\n----------MENU----------\n");
        scanf("%d", &info);
        menu = info;
        switch (menu)
        {
            case menu_serv:
                do{
                    printf("\n----------MENU----------");
                    printf("\nDigite de acordo com sua preferencia: ");
                    printf("\n1-Cadastrar servidor. \n2-Listar servidor. \n3-Pesquisar servidor. \n4-Excluir cadastro. \n5-Reiniciar o programa. \n6-Alterar cadastro. \n7-Sair.\n\n");
                    printf("\n----------MENU----------\n");
                    scanf("%d", &menu_servidor);
                    switch(menu_servidor)
                    {
                        case cadastro_servidor:
                            inserir_servidor_ui(servidores, f_servidor);
                            break;
                        case listagem_servidores:
                            printf("\nDigite 1 para a listagem de todos os servidores sem ordem especifica. \nDigite 2 para a listagem de todos os servidores em ordem alfabetica. \nDigite 3 para a listagem de todos os professores em ordem alfabetica. \nDigite 4 para a listagem de todos os tecnicos administrativos em ordem alfabetica. \nDigite outro valor para sair do modo ''Listar''.\n\n");
                            scanf("%d", &listagem_serv);
                            switch(listagem_serv)
                            {
                                case listagem_servidor:
                                    listar_servidores(servidores, f_servidor);
                                    break;
                                case listagem_alfab:
                                    listagem_alfabetica_servidor(servidores, f_servidor);
                                    break;
                                case listagem_docente:
                                    listagem_por_tipo("Docente", servidores, f_servidor);
                                    break;
                                case listagem_TA:
                                    listagem_por_tipo("Tecnico Administrativo", servidores, f_servidor);
                                    break;
                                default:
                                    system("exit");
                            }
                            break;
                        case pesquisar_servidor:
                            pesquisa_por_codigo_servidor_ui(servidores, f_servidor);
                            break;
                        case excluir_servi:
                            excluir_servidor_ui(servidores, f_servidor, f_veiculo);
                            break;
                        case reiniciar_programa_serv:
                            iniciar_servidores_ui(servidores, f_servidor, f_veiculo);
                            break;
                        case alterar_cadastro_serv:
                            alterar_cadastro_servidor_ui(servidores, f_servidor);
                            break;
                        case sair_prog_serv:
                            break;
                        default:
                            printf("Opçao invalida. Digite novamente.\n");
                            mostrar();
                    }
                } while(menu_servidor != 7);
                break;
            case menu_veic:
                do{
                    printf("\n----------MENU----------");
                    printf("\nDigite de acordo com sua preferencia: ");
                    printf("\n1-Cadastrar veiculo. \n2-Listar veiculos de um servidor. \n3-Pesquisar veiculo. \n4-Excluir cadastro de veiculo. \n5-Alterar cadastro. \n6-Reiniciar o programa dos veiculos. \n7-Sair\n\n");
                    printf("\n----------MENU----------\n");
                    scanf("%d", &menu_veiculo);
                    switch(menu_veiculo)
                    {
                        case cadastro_veiculo:
                            inserir_veiculo_ui(veiculos, f_veiculo, f_servidor);
                            break;
                        case listagem_veiculos:
                            printf("\nDigite 1 para a listar todos os veiculos de um servidor. \nDigite 2 para a listar todos os veiculos de um servidor em ordem alfabetica quanto ao nome. \nDigite outro valor para sair do modo ''Listar''.\n\n");
                            scanf("%d", &listagem_veic);
                            switch(listagem_veic)
                            {
                                case listagem_todos_veic_por_serv:
                                    listagem_todos_veic_servidor_ui(veiculos, f_veiculo, f_servidor);
                                    break;
                                case listagem_alfab_todos_veic_por_serv:
                                    listagem_alfab_todos_veic_servidor_ui(veiculos, f_veiculo, f_servidor);
                                    break;
                                default:
                                    system("exit");
                            }
                            break;
                        case pesquisar_veiculo:
                            pesquisa_por_codigo_veiculo_ui(veiculos, f_veiculo, f_servidor);
                            break;
                        case excluir_vei:
                            excluir_veiculo_ui(veiculos, f_veiculo);
                            break;
                        case alterar_cadastro_veic:
                            alterar_cadastro_veiculo_ui(veiculos, f_veiculo, f_servidor);
                            break;
                        case reiniciar_programa_veic:
                            iniciar_veiculos(veiculos, f_veiculo);
                            break;
                        case sair_prog_veic:
                            break;
                        default:
                            printf("Opçao invalida. Digite novamente.\n");
                            mostrar();
                    }
                } while(menu_veiculo != 7);
                break;
            case sair_programa_main:
                liberar_servidores(servidores);
                liberar_veiculos(veiculos);
                break;
            default:
                printf("Opçao invalida. Pressione 'Enter' para repetir o processo.\n");
                mostrar();
                break;
        }
    } while (menu != 3);
    fclose(f_servidor);
    fclose(f_veiculo);
}