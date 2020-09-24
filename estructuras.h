/* typedef enum{INICIAL,FINAL,RECHAZO,ACEPTACION} Estado; */

typedef enum{
  INICIAL=0,FINAL=5,RECHAZO=6, ACEPTACION
} Estado;

typedef enum{false, true}boolean;

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

