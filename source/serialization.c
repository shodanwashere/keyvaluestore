/**
 * Distributed Systems Project Phase 1 :: Data Module
 * Authors:
 * - Nuno Dias,    fc56330
 * - Bruna Santos, fc56328
 * - Pedro Pinto,  fc56369
 */
#include "serialization.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Serializa todas as keys presentes no array de strings keys
 * para o buffer keys_buf que será alocado dentro da função.
 * O array de keys a passar em argumento pode ser obtido através
 * da função tree_get_keys. Para além disso, retorna o tamanho do
 * buffer alocado ou -1 em caso de erro.
 */
int keyArray_to_buffer(char **keys, char **keys_buf){
  int bufSize = 0;

  for(int i = 0; keys[i] != NULL; i++){
    bufSize += strlen(keys[i])+1;                //Obter o tamanho necessário para o buffer
  }
  keys_buf = malloc(bufSize * sizeof(char*));    //Alocar memória

  if(keys_buf == NULL) return - 1;               //Erro malloc

  int bytesWritten = 0;

  for(int i = 0; bytesWritten < bufSize; i++){
    int key_str_size = strlen(keys[i]) + 1;

    if(memcpy(keys_buf + bytesWritten, keys[i], key_str_size) == NULL) return -1;
    bytesWritten += key_str_size;
  }
  return bufSize;
}

/* De-serializa a mensagem contida em keys_buf, com tamanho
 * keys_buf_size, colocando-a e retornando-a num array char**,
 * cujo espaco em memória deve ser reservado. Devolve NULL
 * em caso de erro.
 */
 char** buffer_to_keyArray(char *keys_buf, int keys_buf_size){
   int keyCount = 0;
   for(int i = 0; i < keys_buf_size; i++){      //Contar num de keys
     if(keys_buf[i] == '\0')
       keyCount++;
   }

   if(keyCount == 0) return NULL;

   char **keyArray = malloc(sizeof(char*) * keyCount);

   if(keyArray == NULL) return NULL;

   int counter = 0;
   for(int i = 0; i < keyCount; i++){
     int keySize = strlen(keys_buf + counter) + 1;
     keyArray[i] = malloc(sizeof(char) * keySize);
     memcpy(keyArray[i], keys_buf + counter, keySize);
     counter += keySize;
   }

   return keyArray;
 }
