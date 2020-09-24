#ifndef FUNCIONES
#define FUNCIONES

#include <stdio.h>
#include "estructuras.h"
#include "funciones.h"

int TABLA_DE_TRANSICION[6][4] = {
  {1,5,5,5}, // ESTADO_0
  {3,2,5,4}, // ESTADO_1
  {4,5,4,5}, // ESTADO_2
  {3,5,5,4}, // ESTADO_3
  {5,5,5,5}, // ESTADO_4
  {5,5,5,5}, // ESTADO_5
};

/* printf("TABLA:%d\n", TABLA_DE_TRANSICION[0][0]); */
/* printf("CoolumnaCaracter: %d\n: ",columnaCaracter(0, '1')); */

/* printf("---------------------------------\n"); */

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
  return caracter == caracterLeido;
}

// retorna el siguiente estado
int transicion(char caracterLeido, int estadoOrigen){
  int estadoDestino;
  int estadoOk = false;

  printf("caracterLeido:%c, estadoOrigen:%d\n", caracterLeido, estadoOrigen);

  for(int columna=0; columna <= TABLA_TRANSICION_COLUMNAS; columna++){
    // si la transición tiene un estado de rechazo,
    // entonces saltamos a la siguiente iteración del for (lo que le siga no será evaluado)
    // creo que habría que mejorar el concepto de RECHAZO (?)
    if(TABLA_DE_TRANSICION[estadoOrigen][columna] == ESTADO_RECHAZO){
      continue;
    }

    if(columnaCaracter(columna, caracterLeido)){
      estadoOk = true;
      estadoDestino = TABLA_DE_TRANSICION[estadoOrigen][columna];
      break;
    }
  }

  if(estadoOk)
    return estadoDestino;
  else
    return ESTADO_RECHAZO;
}

boolean columnaCaracter(int columna_tabla_transicion, char caracterLeido){
  switch(columna_tabla_transicion){
  case 0: // Columna 1
    return estaEntreLosNumeros(0, 1, caracterLeido);
    break;
  case 1: // columna 2
      return esElCaracter('.', caracterLeido);
      break;
  case 2: // columna 3
      return estaEntreLosNumeros(2, 9, caracterLeido);
      break;
  case 3: // columna 4
      return esElCaracter('B', caracterLeido);
      break;
  default: // estado de rechazo
    return false;
    break;
  }
}

#endif
