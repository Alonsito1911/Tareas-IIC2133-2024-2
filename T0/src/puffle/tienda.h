

//Codigo escrito en este archivo contiene similitudes y partes del taller C IIC2133 2021-2 Taller 1 y 0


//Como crear estructuras propias fue extraido en este video https://www.youtube.com/watch?v=leHnsH0gx2A

#include <stdio.h>
// Indica que este archivo solo se debe incluir una vez en la compilación
#pragma once

// Declaramos el struct para un nodo de la lista
struct puffle_node;
// Definimos un alias para el struct nodo.
// La sintaxis es "typedef tipo alias"
typedef struct puffle_node Puffle_Node;

// Definimos el struct nodo
struct puffle_node
{
  /** El valor que guarda el nodo */
  int id; 
  char* color;
  /** Un puntero al siguiente nodo de la lista */
  Puffle_Node* next;
};

// Declaramos el struct para la lista
struct puffle_linked_list;
// Definimos un alias para el struct lista
typedef struct puffle_linked_list Puffle_List;

// Definimos el struct lista
struct puffle_linked_list
{
  /** El primer nodo de la lista */
  Puffle_Node* head;
  /** El último nodo de la lista */
  Puffle_Node* tail;
  
  int P;

  int Capacidad_actual; 
};

// Declaramos el struct para la lista
struct Pinguino_estructura {
    int ID;
    int P;
    int cantidad_puffles;
    Puffle_List* puffles;
};

// Ahora puedes usar "Pinguino" o "struct Pinguino_estructura"
typedef struct Pinguino_estructura Pinguino;

// Declaramos el struct para un nodo de la lista
struct linked_list_node;
// Definimos un alias para el struct nodo.
// La sintaxis es "typedef tipo alias"
typedef struct linked_list_node Node;

// Definimos el struct nodo
struct linked_list_node
{
  /** El valor que guarda el nodo */
  Pinguino* value;
  /** Un puntero al siguiente nodo de la lista */
  Node* next;
};

// Declaramos el struct para la lista
struct linked_list;
// Definimos un alias para el struct lista
typedef struct linked_list List;

// Definimos el struct lista
struct linked_list
{
  /** El primer nodo de la lista */
  Node* head;
  /** El último nodo de la lista */
  Node* tail;
  
  int K;

  int Capacidad_actual; 
};

// Declaramos las funciones asociadas
//Inicializar Pinguino
Pinguino* Pinguino_init();
void Pinguino_print(Pinguino* pinguino);

/** Inicializa una lista vacía */
List* list_init();
Puffle_List* puffle_list_init();

//COLOR-AMOUNT COL
void obtener_cantidad_color(List* list, char* color, int* cantidad);

//BUY-PUFFLE RUNAWAY-PUFFLE
void obtener_penguin_y_agregar_puffle(List* list, int id, char* color, int id_puffle, FILE* output_file);


void obtener_penguin_y_eliminar_puffle(List* list, int id, int id_puffle);


//TRADE-PUFFLE 

void trader_puffles(List* list, int penguin_id_1, int penguin_id_2, int puffle_id_1,int puffle_id_2);

//STEAL
void steal_puffles(List* list,int penguin_id_1, int penguin_id_2,char* color, int N_LIMIT, FILE* output_file);
void puffle_steal(Puffle_List* list,Puffle_List* list_2 ,char* color, int N_LIMIT, FILE* output_file);

int contar_puffles(List* list);
//GIVE PUFFLES
void give_puffles(List* list,int penguin_id_1, int penguin_id_2, int STAR,int END, FILE* output_file);
void puffle_give(Puffle_List* list,Puffle_List* list_2 ,int START, int END, FILE* output_file);





/** Inserta un nuevo elemento al final de la lista */
void list_append(List* list, Pinguino* value);
void puffle_list_append(Puffle_List* list,  int puffle_id, char* color ); 
void agregar_puffle_n_posicion(Puffle_List* list, int n, int puffle_id, char* color);

/** Imprime todos los elementos de la lista */
void list_print(List* list, FILE* output_file);
void puffle_list_print(Puffle_List* list, FILE* output_file);
void puffle_list_print_2(Puffle_List* list );
/** Libera todos los recursos asociados a esta lista */
void list_destroy(List* list);
void puffle_list_destroy(Puffle_List* list);
void Pinguino_free(Pinguino* pinguino);


//W
void list_eliminar(List* list, int id, int* puffles_totales, FILE* output_file);
void puffle_list_eliminar(Puffle_List* list, int id);
void imprimirAtributosLista(List* lista);
