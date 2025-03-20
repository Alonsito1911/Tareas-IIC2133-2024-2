#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tienda.h"



/* Retorna true si ambos strings son iguales */
static bool string_equals(char *string1, char *string2) {
  return !strcmp(string1, string2);
}

static bool check_arguments(int argc, char **argv) {
  if (argc != 3) {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    exit(1);
  }
  return true;
}

int main(int argc, char **argv) {
  check_arguments(argc, argv);

  FILE *input_file = fopen(argv[1], "r");
  FILE *output_file = fopen(argv[2], "w");

  int K; // Capacidad de la tienda
  int P; // Número máximo de puffles
  int E; // Número de eventos (No considera los multiples inputs del evento ENTER)

  int result;
  result = fscanf(input_file, "%d", &K);
  if (result != 1) {
    printf("Error reading store capacity");
    return 1;
  }
  result = fscanf(input_file, "%d", &P);
  if (result != 1) {
    printf("Error reading maximum number of puffles");
    return 1;
  }
  result = fscanf(input_file, "%d", &E);
  if (result != 1) {
    printf("Error reading number of events");
    return 1;
  }


  /* Construcción de las estructuras */
    /* COMPLETAR */
    // Tenemos que crear una estructura que sea para la teienda con capacidad máxima K
  //Tienda 
  List* list = list_init(K);
  

  //Puffles
  int* puffles_totales = malloc(sizeof(int));
  *puffles_totales = 0;

  

  /* Eventos */
  char command[32];
  for (int i = 0; i < E; i++)
  {
    fscanf(input_file, "%s", command);
    if (string_equals(command, "ENTER")){
      int id;
      int N;
      fscanf(input_file, "%d %d", &id, &N);
      printf("Penguin %d with %d Puffles:\n", id, N);

      //Registramos la entrada de nuestros pinguinos 
     


      //Inicializamos nuestro pinguino y lista de puffles
      Pinguino* Pinguino = Pinguino_init(id, P);

      Puffle_List* puffle_list = puffle_list_init(P);

      Pinguino -> puffles = puffle_list;
      

      if (list->Capacidad_actual >= list ->K){
        fprintf(output_file, "Entry denied due to maximum capacity\n");
       
        }
      else 
        {    
          //Pinguino_print(Pinguino);
          fprintf(output_file, "Penguin %d has entered with %d puffles\n", id, N);
          list_append(list, Pinguino); 
          //list_print(list);
          }
          

      //printf("La lista con nuestros pinguinos contiene:\n");

       //vemo los elementos de nuestra tienda
      //printf("Capacidad máxima K: %d\n", list->K);
      //printf("Capacidad actual: %d\n", list->Capacidad_actual);
      
       Pinguino -> cantidad_puffles = N;
      
      /* COMPLETAR */
      for (int j = 0; j < N; j++)
      {
        int puffle_id;
        char color;
        fscanf(input_file, "%d %s", &puffle_id, &color);
        //printf("\tPuffle %d color %s\n", puffle_id, &color);
        
        /* COMPLETAR */
        puffle_list_append(puffle_list,puffle_id, &color);
        
      }
      *puffles_totales += N;
      

      printf("\tCANTIDAD FINAL %d\n", *puffles_totales);
    
    }
    

    
    
    else if (string_equals(command, "LEAVE")){

        int id; 
        fscanf(input_file, "%d", &id);

        list_eliminar(list, id, puffles_totales,output_file);
        //printf("\t\t CAPACIDAD FINAL %d\n" , *puffles_totales);
    }
    else if (string_equals(command, "STATUS")){
      fprintf(output_file, "%s: \n", command);
      fprintf(output_file, "\tTotal penguins: %d\n", list->Capacidad_actual);
      list_print(list, output_file);
      int puffles_totales_2 = contar_puffles(list);
      fprintf(output_file, "\tTotal puffles: %d\n", puffles_totales_2);
    }


//Por realizar
    else if (string_equals(command, "BUY-PUFFLE")){

      int penguin_id;
      int puffle_id;
      char color[20];  
      fscanf(input_file, "%d %d", &penguin_id, &puffle_id);
      fscanf(input_file, "%19s", color); 
      printf("Penguin %d bought %d\n", penguin_id, puffle_id);
      obtener_penguin_y_agregar_puffle(list,penguin_id,color,puffle_id, output_file);

    }

     else if (string_equals(command, "RUNAWAY-PUFFLE")){
      
      int penguin_id;
      int puffle_id;
      fscanf(input_file, "%d %d", &penguin_id, &puffle_id);
      fprintf(output_file, "%d ran away from %d\n", puffle_id, penguin_id);
      printf("%d ran away from %d\n", puffle_id, penguin_id);
      obtener_penguin_y_eliminar_puffle(list,penguin_id,puffle_id);
      //Se resta aqui dado que no existe un caso especial en los test case al parecer


     
    }






     else if (string_equals(command, "TRADE-PUFFLE")){

      int id_penguin_1;
      int id_penguin_2;
      int id_puffle_1;
      int id_puffle_2;
    
      fscanf(input_file, "%d %d %d %d", &id_penguin_1, &id_penguin_2, &id_puffle_1, &id_puffle_2);
      //fprintf(output_file, "Exchange between %d and %d  id1 %d id2 %d \n", id_penguin_1, id_penguin_2, id_puffle_1, id_puffle_2);
      fprintf(output_file, "Exchange between %d and %d\n", id_penguin_1, id_penguin_2);
      printf("Exchange between %d and %d  \n", id_penguin_1, id_penguin_2);
      trader_puffles(list, id_penguin_1, id_penguin_2, id_puffle_1, id_puffle_2);

     
    }







     else if (string_equals(command, "STEAL-PUFFLE")){

      int id_penguin_1;
      int id_penguin_2;
      char color[19];
      int N_LIMIT;
    
      fscanf(input_file, "%d %d %19s %d", &id_penguin_1, &id_penguin_2, color, &N_LIMIT);
      fprintf(output_file, "Steal %d from %d\n", id_penguin_1, id_penguin_2);
      //fprintf(output_file, "Steal %d from %d color %s  a lo mas %d\n", id_penguin_1, id_penguin_2, color, N_LIMIT);
      printf("Steal %d from %d n %d :\n ", id_penguin_1, id_penguin_2, N_LIMIT);
      steal_puffles(list, id_penguin_1, id_penguin_2, color, N_LIMIT, output_file );
    }


    else if (string_equals(command, "GIVE-PUFFLES")){

      int id_penguin_1;
      int id_penguin_2;
      int START;
      int END;
    
      fscanf(input_file, "%d %d %d %d", &id_penguin_1, &id_penguin_2,&START, &END);
      give_puffles(list, id_penguin_1, id_penguin_2, START, END, output_file);
      //fprintf(output_file, "\tTotal given awawy puffles: N\n");
    }





    else if (string_equals(command, "COLOR-AMOUNT")){
      int* cantidad_totales = malloc(sizeof(int));
      *cantidad_totales = 0;
      char color[20];
    
      fscanf(input_file, "%19s", color);
      obtener_cantidad_color(list,color,cantidad_totales);
      fprintf(output_file, "Total amount %s: %d\n" ,color, *cantidad_totales);
      free(cantidad_totales);
    }





  }
  
  
/* Cerramos los archivos */
  fclose(input_file);
  fclose(output_file);

/* Liberamos memoria */
    /* COMPLETAR */
  list_destroy(list);
  free(puffles_totales);

  return 0;
}