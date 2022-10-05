/**
 * Distributed Systems Project Phase 1 :: Entry Module
 * Authors:
 * - Nuno Dias,    fc56330
 * - Bruna Santos, fc56328
 * - Pedro Pinto,  fc56369
 */

#include "data.h"
#include "entry.h"
#include <stdlib.h>
#include <string.h>

/* Função que cria uma entry, reservando a memória necessária para a
 * estrutura e inicializando os campos key e value, respetivamente, com a
 * string e o bloco de dados passados como parâmetros, sem reservar
 * memória para estes campos.

 */
struct entry_t *entry_create(char *key, struct data_t *data){
    struct entry_t *ptr;
    if(key == NULL || data == NULL)
        ptr = NULL;
    else {
        ptr = malloc(sizeof(struct entry_t));
        ptr->key = key;
        ptr->value = data;
    }
    return ptr;
}

/* Função que elimina uma entry, libertando a memória por ela ocupada
 */
void entry_destroy(struct entry_t *entry){
    if(entry != NULL){
        free(entry);
    }
}

/* Função que duplica uma entry, reservando a memória necessária para a
 * nova estrutura.
 */
struct entry_t *entry_dup(struct entry_t *entry){
    struct entry_t *newEntry = (struct entry_t*) malloc(sizeof(struct entry_t));

    newEntry->key = strdup(entry->key);
    newEntry->value = data_dup(entry->value);

    return newEntry;
}

/* Função que substitui o conteúdo de uma entrada entry_t.
*  Deve assegurar que destroi o conteúdo antigo da mesma.
*/
void entry_replace(struct entry_t *entry, char *new_key, struct data_t *new_value){
    entry->key = new_key;
    data_destroy(entry->value);
    entry->value = new_value;
}

/* Função que compara duas entradas e retorna a ordem das mesmas.
*  Ordem das entradas é definida pela ordem das suas chaves.
*  A função devolve 0 se forem iguais, -1 se entry1<entry2, e 1 caso contrário.
*/
int entry_compare(struct entry_t *entry1, struct entry_t *entry2){
    int result = 0;
    if(entry1 != NULL && entry2 != NULL){
        result = strcmp(entry1->key, entry2->key);
    }
    if(result != 0){
        result = (result > 0) ? 1 : -1;
    }
    return result;
}