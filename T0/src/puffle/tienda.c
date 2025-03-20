#include "tienda.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Inicializa una lista vacía */
List* list_init(int K)
{
  List* list = malloc(sizeof(List));
  list -> head = NULL;
  list -> tail = NULL;
  list -> K = K;
  list ->Capacidad_actual = 0;

  return list;
}

Puffle_List* puffle_list_init(int P)
 {
  Puffle_List* puffle_list = malloc(sizeof(List));
  puffle_list -> head = NULL;
  puffle_list -> tail = NULL;
  puffle_list -> P = P;
  puffle_list ->Capacidad_actual = 0;
  return  puffle_list;
 }

Pinguino* Pinguino_init(int ID, int  P)
{
  Pinguino* estructura = malloc(sizeof(Pinguino));
  estructura -> ID = ID;
  estructura -> P = P;
  estructura -> cantidad_puffles = 0;

  
  return estructura;
}
/** Inserta un nuevo elemento al final de la lista */
void list_append(List* list, Pinguino* value)
{
  //printf("Entramos a append\n");

  Node* node = malloc(sizeof(Node));
  node -> value = value;
  node -> next = NULL;
  
  // Si la lista está vacía entonces queda como el primer elemento
  if(list -> head == NULL)
  {
    list -> head = node;
  }
  // Sino, se pone como el siguiente del ultimo
  else
  {
    //printf("Nodo cola: %d\n", list->tail->value->ID);
    
    list -> tail -> next = node;
  }
  // Luego se deja a este nodo como el último
  list -> tail = node;
  //printf("Nodo cola final: %d\n", list->tail->value->ID);
  
  list ->Capacidad_actual++;
}
void puffle_list_append(Puffle_List* list,  int puffle_id, char* color)
{
  Puffle_Node* node = malloc(sizeof(Puffle_Node));
  node -> color = strdup(color); 
  node -> id = puffle_id;
  node -> next = NULL;
 // Si la lista está llena, no se puede agregar más
    if (list->Capacidad_actual >= list->P) {
        printf("\t NO SE PUEDE AGREGAR MAS\n");  
        return;
    }

    // Caso de lista vacía
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;  // También debe ser tail, ya que es el único nodo
    } else {
        // Caso de lista con al menos un nodo
        list->tail->next = node;  // Conectar al final de la lista existente
        list->tail = node;  // Actualizar tail para que apunte al nuevo nodo
    }

    list->Capacidad_actual++; 
 
}

//En la siguientes funciones que constan de eliminar elementos de una lista ligada tuve varias complicaciones, en especial cuando tenia que eliminar un elemento que estaba final a la lista, por que eliminaba el tail de esta jajaj, por lo cual
//realice prompts puntuales en GPT para encontrar el problema.
//Pero la forma de recorrer nodos esta extraida del taller C IIC2133 2021-2 Taller 1 y 0
//Los casos posibles que hay que considerar al eliminar un elemento de una lista ligada con ayuda  de prompts GPT
//y la logica fue con ayuda de estos videos https://www.youtube.com/watch?v=vldM-3PYAmo
//https://www.youtube.com/watch?v=TjsDuUT4P74
void list_eliminar(List* list, int id, int* puffles_totales, FILE* output_file){
    Node* current = list->head;
    Node* previous = NULL;
    //printf("\tTotal puffl PRINCIPPPes: %d\n", *puffles_totales);
    if (current != NULL && current->value->ID == id) {
        list->head = current->next;  
      //  printf("puffles aeliminar : %d\n", current->value->cantidad_puffles);
        fprintf(output_file, "Leaving %d with %d puffles \n", current->value->ID, current->value->puffles->Capacidad_actual);
        *puffles_totales -= current->value->cantidad_puffles;
        puffle_list_destroy( current->value->puffles);
        free(current); 
        list -> Capacidad_actual--;
        return;
    }
    for (current = list->head; current != NULL; previous = current, current = current->next) {
         if (current->value->ID == id) {
          //printf("Nodo encontrado con ID: %d\n", current->value->ID);
          //printf("puffles aeliminar : %d\n", current->value->cantidad_puffles);
          fprintf(output_file, "Leaving %d with %d puffles \n", current->value->ID, current->value->puffles->Capacidad_actual);
          *puffles_totales -= current->value->cantidad_puffles;
           if (current->next == NULL) {
                if (previous != NULL) {
                    previous->next = NULL;
                    list->tail = previous;
                } else {
                    // Esto maneja el caso si la lista tiene solo un nodo y se elimina el último nodo
                    list->head = NULL;
                    list->tail = NULL;
                }
                //printf("Nodo current: %d\n", current->value->ID);
    
                //list_print(list);
                list -> Capacidad_actual--;
                puffle_list_destroy( current->value->puffles);
                 return ;
            }
            else
            {
              previous->next = current->next;
              puffle_list_destroy( current->value->puffles);
              free(current);
              list -> Capacidad_actual--;
              return;
            }
         }     
    }
}


void puffle_list_eliminar(Puffle_List* list, int id){
  //Sigo la misma logica que en la funcion anterior
    //dos variables auxliares
    Puffle_Node* current = list->head;
    Puffle_Node* previous = NULL;
    if (current != NULL && current->id== id) {
        list->head = current->next;  
        free(current); 
        list -> Capacidad_actual--;
        return;
    }
    for (current = list->head; current != NULL; previous = current, current = current->next) {
         if (current->id == id) {
          //printf("Nodo encontrado con ID: %d\n", current->value->ID);
          //printf("puffles aeliminar : %d\n", current->value->cantidad_puffles)
           if (current->next == NULL) {
                if (previous != NULL) {
                    previous->next = NULL;
                    list->tail = previous;
                } else {
                    list->head = NULL;
                    list->tail = NULL;
                }
                list -> Capacidad_actual--;
                 return ;
            }
            else
            {
              previous->next = current->next;
              free(current);
              list -> Capacidad_actual--;
              return;
            }
         }     
    }
}


//STEAL
void puffle_steal(Puffle_List* list, Puffle_List* list_2, char* color, int n_limit, FILE* output_file) {
    Puffle_Node* previous = NULL;
    Puffle_Node* current = list->head;
    int posicion = 0;

    for (; current != NULL && posicion < n_limit; ) {
        Puffle_Node* temp = current;
        
        if (strcmp(current->color, color) == 0 && list_2->Capacidad_actual < list_2->P) {
            // Si estamos en el head de la lista
            if (current == list->head) {
                list->head = current->next;
                if (list->head == NULL) {
                    list->tail = NULL;
                }
                current = list->head; 
            } else {
                previous->next = current->next;
                if (previous->next == NULL) {
                    list->tail = previous;
                }
                current = previous->next; 
            }
            
            // Añadir el nodo a la lista destino
            puffle_list_append(list_2, temp->id, strdup(temp->color));

            // Imprimir información sobre el puffle robado
            //fprintf(output_file, "\tstolen puffles: %d ca %d\n", list_2->Capacidad_actual, temp->id);


            free(temp->color);  
            free(temp);         

            list->Capacidad_actual--;
            posicion++;

        } else {

            previous = current;
            current = current->next;
        }
    }

    // Imprimir el total de puffles robados
    fprintf(output_file, "\tTotal stolen puffles: %d\n", posicion);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7777
void steal_puffles(List* list,int penguin_id_1, int penguin_id_2,char* color, int N_LIMIT, FILE* output_file){
Node* penguin_node_1 = NULL;
Node* penguin_node_2 = NULL;
//printf("Color a eliminar : %s\n", color);
for (Node* current = list->head; current; current = current->next) {
    if (current->value->ID == penguin_id_1) {
        penguin_node_1 = current;
    }
    if (current->value->ID == penguin_id_2) {
        penguin_node_2 = current;
    }
    if (penguin_node_1 != NULL && penguin_node_2 != NULL) {
        break;
    }
}
  puffle_steal(penguin_node_2->value->puffles, penguin_node_1->value->puffles,color, N_LIMIT, output_file);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7777



int contar_puffles(List* list) {
    int puffles_totales_2 = 0;  // Inicializa el contador
    for (Node* current = list->head; current; current = current->next) {
        for (Puffle_Node* puffle_current = current->value->puffles->head; puffle_current; puffle_current = puffle_current->next) {
            puffles_totales_2 += 1;  
        }
    }
    return puffles_totales_2;  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7777




/** Imprime todos los elementos de la lista */
void list_print(List* list, FILE* output_file)
{
  for(Node* current = list -> head; current; current = current -> next)
  {
    fprintf(output_file, "\tPenguin %d:\n", current -> value -> ID);
    
    if(current->value->puffles->Capacidad_actual != 0)
      {
        puffle_list_print(current->value->puffles, output_file);;
      }
    else{
      fprintf(output_file, "\t\tDoes not have puffles\n");
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7777



void puffle_list_print(Puffle_List* list,FILE* output_file )
{
  for(Puffle_Node* current = list -> head; current; current = current -> next)
  {
    fprintf(output_file, "\t\tPuffle %d\n", current -> id);}
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7777



void puffle_list_print_2(Puffle_List* list )
{
  for(Puffle_Node* current = list -> head; current; current = current -> next)
  {
    printf("\t\tPuffle %d color %s\n", current -> id, current->color);}
}

//////////////////////////////7777777777777

//Obtener CANTIDAD COLOR

void obtener_cantidad_color(List* list, char* color, int* cantidad){
  *cantidad = 0;
  for(Node* current = list -> head; current; current = current -> next)
  {    
     for(Puffle_Node* puffle_current = current->value ->puffles->head; puffle_current; puffle_current = puffle_current -> next)
  {
    if (strcmp(puffle_current->color, color) == 0){
        (*cantidad)++;
    }
  }
  }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7777


//Obtener Penguin y agregar 
void obtener_penguin_y_agregar_puffle(List* list, int id, char* color, int puffle_id, FILE* output_file){
    for(Node* current = list -> head; current; current = current -> next)
      {
        if (current->value->ID == id) {
          if (current->value->puffles->Capacidad_actual < current->value->P){
              fprintf(output_file, "Penguin %d bought %d\n", current->value->ID, puffle_id);
              puffle_list_append(current->value->puffles,puffle_id, color);
            } 
          else{            
            fprintf(output_file,"Purchase denied\n");
          }}
      }
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7777






//TRADE PUFFLES

void trader_puffles(List* list, int penguin_id_1, int penguin_id_2, int puffle_id_1,int puffle_id_2){
  Node* penguin_node_1 = NULL;
  Node* penguin_node_2 = NULL;
  Puffle_Node* puffle_node_1 = NULL;
  Puffle_Node* puffle_node_2 = NULL;

  int puffle_position_1 = 0; 
  int puffle_position_2 = 0;
//printf("Color a eliminar : %s\n", color);
 //Obtenemos la direccion de memoria del penguin 1 y su puffle
  for (Node* current = list->head; current; current = current->next) {
    if (current->value->ID == penguin_id_1) {
        penguin_node_1 = current;
        int position = 0;
        for(Puffle_Node* puffle_current = current->value ->puffles->head; puffle_current; puffle_current = puffle_current -> next)
        {
          if (puffle_current->id == puffle_id_1) {
                        puffle_node_1 = puffle_current;
                        puffle_position_1 = position;
                        break; 
                    }
          position++;
        }
        }
    //Obtenemos la direccion de memoria del penguin 2 y su puffle
    if (current->value->ID == penguin_id_2) {
        penguin_node_2 = current;
        int position = 0;
        for(Puffle_Node* puffle_current = current->value ->puffles->head; puffle_current; puffle_current = puffle_current -> next)
        {
              if (puffle_current->id == puffle_id_2) {
                puffle_node_2 = puffle_current;
                puffle_position_2 = position;
                break; 
            }
        position++;
        }
    }

    if (penguin_node_1 != NULL && penguin_node_2 != NULL && puffle_node_1 != NULL && puffle_node_2 != NULL) {
        break;
    } 
    /////////////////////////////////////////7777
    //Ahora que tenemos los nodos y las posiciones agregaremos en ambos listas de puffles 
    //agregar_puffle_n_posicion(penguin_node_1->value->puffles,puffle_position_1, puffle_id_2, puffle_node_2->color );
    //agregar_puffle_n_posicion(penguin_node_2->value->puffles,puffle_position_2, puffle_id_1, puffle_node_1->color );
}
    agregar_puffle_n_posicion(penguin_node_1->value->puffles,puffle_position_1, puffle_id_2, puffle_node_2->color );
    agregar_puffle_n_posicion(penguin_node_2->value->puffles,puffle_position_2, puffle_id_1, puffle_node_1->color );
    }

//La lógica fue con ayuda de este video https://www.youtube.com/watch?v=vldM-3PYAmo&t=679s pero agregue los pasos necesarios que una vez agregado el puffle en la posicion, se eliminara el puffle sobrante
  void agregar_puffle_n_posicion(Puffle_List* list, int n, int puffle_id, char* color){
    printf("En nuestra funcino\n");
    Puffle_Node* node = malloc(sizeof(Puffle_Node));
    node -> color = strdup(color); 
    node -> id = puffle_id;
    node -> next = NULL;
    if (list->head == NULL || n == 0){
      node->next = list->head;
      list->head = node;
       if (node->next != NULL){
          Puffle_Node* a_eliminar = node->next;
          node->next = a_eliminar->next;}

        if (node->next == NULL) {
                list->tail = node;
            }
    }
    else{
      Puffle_Node* puntero = list->head;
      int posicion = 0;
      while(posicion < n -1  && puntero -> next){
        puntero = puntero -> next;
        posicion++;}
        //conectamos por la derecha y por la izquierda
        node->next = puntero->next;
        puntero ->next = node;
      //PROCEDEREMOS A ELIMINAR EL ELEMENTO QUE ESTA A LA DRECHA DEL NUEVO ELEMENTO AGREGADO
      
        //VERFICIAMOS QUE no sea null elemento que esta al lado
        if (node->next != NULL){
          Puffle_Node* a_eliminar = node->next;
           printf("Eliminando nodo con id: %d y color: %s\n", a_eliminar->id, a_eliminar->color);
          node->next = a_eliminar->next;
          //Manejamos no cargarnos la cola de nuestra lista 
          if (node->next == NULL) {
                list->tail = node;
            }
       } 
      }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7777

//GIVE-PUFFLES id_penguin_1 id_penguin_2 start


void give_puffles(List* list,int penguin_id_1, int penguin_id_2, int START,int END, FILE* output_file){
Node* penguin_node_1 = NULL;
Node* penguin_node_2 = NULL;
//printf("Color a eliminar : %s\n", color);
int puffles_a_dar = END-START;
//fprintf(output_file, "Nuestro Pinguino tiene :puffles y le daremos: %d\n",puffles_a_dar);
for (Node* current = list->head; current; current = current->next) {
    if (current->value->ID == penguin_id_1) {
        penguin_node_1 = current;
    }
    if (current->value->ID == penguin_id_2) {
        penguin_node_2 = current;
    }
    if (penguin_node_1 != NULL && penguin_node_2 != NULL) {
        break;
    }
}

  if (penguin_node_2->value->puffles->Capacidad_actual + puffles_a_dar < penguin_node_2->value->P){
     fprintf(output_file, "Gift from %d to %d\n", penguin_id_1, penguin_id_2);
    //fprintf(output_file,"Nuestro Pinguino 2 %d tiene : %d  puffles y le daremos: %d\n", penguin_id_2, penguin_node_2->value->puffles->Capacidad_actual, puffles_a_dar);
    //fprintf(output_file, "Nuestro Pinguino 1 %d tiene : %d  puffles y le quitaremos: %d\n", penguin_id_1, penguin_node_1->value->puffles->Capacidad_actual, puffles_a_dar);
    puffle_give(penguin_node_1->value->puffles,penguin_node_2->value->puffles ,START, END, output_file); }
  else{
    fprintf(output_file, "Gift denied: %d would be full\n", penguin_id_2);
  }

  
}

  

void puffle_give(Puffle_List* list, Puffle_List* list_2,int START, int END, FILE* output_file){
    Puffle_Node* previous = NULL;
    int posicion = 0;
    int puffles_regalados= 0;
    for (Puffle_Node* current = list->head; current != NULL;) {
        Puffle_Node* temp = current;
        if (START - 1 < posicion && posicion <= END ){
            // Si estamos en el head de la lista
            if (current == list->head) {
                list->head = current->next;
                if (list->head == NULL) {
                    list->tail = NULL;
                }
                current = list->head;
            } else {
                previous->next = current->next;
                if (previous->next == NULL) {
                    list->tail = previous;
                }
                current = previous->next;
            }
            puffle_list_append(list_2, temp->id, temp->color);
            list->Capacidad_actual--;
            puffles_regalados++;
            free(temp);
            //fprintf(output_file, "\tCantidad puffles lista 2: %d capacidad %d\n", list_2->Capacidad_actual, list_2->P);
            
          
        } else {
            previous = current;
            current = current->next;
        }
      posicion++;
    }
    //puffle_list_print(list, output_file);
    fprintf(output_file, "\tTotal given away puffles: %d\n", puffles_regalados);
}









//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void obtener_penguin_y_eliminar_puffle(List* list, int id,int puffle_id){
for(Node* current = list -> head; current; current = current -> next)
  {
    if (current->value->ID == id) {
          puffle_list_eliminar(current->value->puffles,puffle_id);
         }  
  }

}





/** Libera todos los recursos asociados a esta lista */
void list_destroy(List* list)
{
  // Liberamos los nodos
  if(list -> head)
  {
    Node* curr = list -> head -> next;
    Node* prev = list -> head;

    while(curr)
    {
      puffle_list_destroy(prev->value->puffles);
      //free(prev->value->puffles);
      Pinguino_free(prev->value);
      free(prev);
      prev = curr;
      curr = curr -> next;
    }
    
    puffle_list_destroy(prev->value->puffles);
    //free(prev->value->puffles);
    Pinguino_free(prev->value);
    free(prev);
  }
  // Liberamos la lista en si
  free(list);
}
void Pinguino_free(Pinguino* pinguino) {
    if (pinguino) {
        free(pinguino);
    }
}

/** Libera todos los recursos asociados a esta lista */
void puffle_list_destroy(Puffle_List* list)
{
  // Liberamos los nodos
  if(list -> head)
  {
    Puffle_Node* curr = list -> head -> next;
    Puffle_Node* prev = list -> head;

    while(curr)
    {
      free(prev->color);
      free(prev);
      prev = curr;
      curr = curr -> next;
    }
    free(prev->color);
    free(prev);
  }
  free(list);
}
