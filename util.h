#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void espaco();
void ler(char *, char *);
int campo_obrigatorio(char *);
void tornar_caract_maiusculo(char s1[], char s2[]);
void mostrar();
void alteracao();
#endif