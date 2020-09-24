#define TABLA_TRANSICION_COLUMNAS 4
#define CANTIDAD_ESTADOS 6
#define ESTADO_INICIAL 0
#define ESTADO_FINAL 4
#define ESTADO_RECHAZO 5

boolean columnaCaracter(int columna_tabla_transicion, char caracterLeido);

boolean estaEntreLosNumeros(int minimo, int maximo, char caracter);

boolean esElCaracter(char caracter, char caracterLeido);

int char_to_int(char c);

int transicion(char caracterLeido, int estadoOrigen);


