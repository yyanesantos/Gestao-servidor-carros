#include "util.h"
void espaco()
{
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}
void ler(char *msg, char *str)
{
    printf(msg);
    fgets(str, 255, stdin);
}
int campo_obrigatorio(char *c)
{
    if(!strcmp(c, "\n")){
        return 0;
    }
    return 1;
}
void tornar_caract_maiusculo(char s1[], char s2[])
{
    int i = 0;
    while(s1[i] != '\0'){
        s2[i] = toupper(s1[i]);
        i++;
    }
    s2[i] = '\0';
}

void mostrar()
{
    getchar();
    getchar();
}

void alteracao()
{
    printf("Alterado com sucesso.");
    getchar();
}