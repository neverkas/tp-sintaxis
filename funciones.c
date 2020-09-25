#ifndef FUNCIONES
#define FUNCIONES

#include "tipos.h"
#include "funciones.h"

#include <stdio.h>
#include <ctype.h> // isdigit

int char_to_int(char c){
  return c - '0';
}

boolean estaEntreLosNumeros(int minimo, int maximo, char caracter){
  if(isdigit(caracter)){
    int num = char_to_int(caracter);

    return num >= minimo || num <= maximo;
  }

  return false;
}

boolean esElCaracter(char caracter, char caracterLeido){
  if(isprint(caracter))
    return caracter == caracterLeido;
}

#endif
