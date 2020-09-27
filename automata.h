#ifndef AUTOMATA_H
#define AUTOMATA_H

/* #include "tipos.h" */
/* #include "globales.h" */

typedef enum{
  INICIAL,FINAL,RECHAZO,OTRO
} TipoDeEstado;

typedef struct{
  int estado_origen;
  int estado_destino;
  char caracter;
} Transicion;

static boolean columnaCaracter(int columna_tabla_transicion, char caracterLeido);

void iniciar_automata();
static void imprimir_resultados();
static void reconocer_palabra();
static boolean es_estado_final(int estado);
static int transicion(char caracterLeido, int estadoOrigen);

static void mensaje();
static void imprimir_tabla_transicion();
static void imprimir_derivacion(char palabra[]);

extern char palabra[MAX_LONGITUD_PALABRA];
extern int longitud_palabra;
extern int estado_actual;

static void agregarTransicion(int Numero, Transicion t, Transicion* transiciones);
static void imprimirTransicion(Transicion t);
static Transicion crearTransicion(int origen, int destino, char caracter);

void evaluar_cadena(char *cadena);
void solicitar_evaluar_cadena(char *cadena);
void confirmar_evaluar_cadena();

extern Transicion *transiciones;

#endif
