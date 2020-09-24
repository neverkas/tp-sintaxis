#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "tipos.h"

typedef enum{
  INICIAL=0,RECHAZO=6
} Estado;

typedef struct{
  int estado_origen;
  int estado_destino;
  char caracter_leido;
} Transicion;

typedef struct{
  Estado estado;
  char caracter_leido;
  int cantidad_estados;
  char *alfabeto;
  /* int tabla_transicion[6][4]; // matriz[][] */
} Automata;

static boolean columnaCaracter(int columna_tabla_transicion, char caracterLeido);

void iniciar_automata();
static void imprimir_resultados();
static void reconocer_palabra();
static boolean es_estado_final(int estado);
static int transicion(char caracterLeido, int estadoOrigen);

#endif
