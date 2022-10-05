/**
 * Distributed Systems Project Phase 1 :: Data Module
 * Authors:
 * - Nuno Dias,    fc56330
 * - Bruna Santos, fc56328
 * - Pedro Pinto,  fc56369
 */

#include "data.h"
#include <string.h>
#include <stdlib.h>

/* Função que cria um novo elemento de dados data_t, reservando a memória
 * necessária para armazenar os dados, especificada pelo parâmetro size 
 */
struct data_t *data_create(int size){
    struct data_t *newElement;

    if(size < 1)
        newElement = NULL;
    else {
        newElement = malloc(sizeof(struct data_t));
        newElement->datasize = size;
        newElement->data = malloc(size);
    }

    return newElement;
}

/* Função que cria um novo elemento de dados data_t, inicializando o campo
 * data com o valor passado no parâmetro data, sem necessidade de reservar
 * memória para os dados.
 */
struct data_t *data_create2(int size, void *data){
    struct data_t *ptr;
    
    if(size < 1 || data == NULL) ptr = NULL;
    else {
        ptr = (struct data_t*) malloc(sizeof(struct data_t));
        ptr->datasize = size;
        ptr->data = data;
    }

    return ptr;
}

/* Função que elimina um bloco de dados, apontado pelo parâmetro data,
 * libertando toda a memória por ele ocupada.
 */
void data_destroy(struct data_t *data){
    if(data != NULL){
        if(data->data != NULL)
            free(data->data);
        free(data);
    }
}

/* Função que duplica uma estrutura data_t, reservando toda a memória
 * necessária para a nova estrutura, inclusivamente dados.
 */
struct data_t *data_dup(struct data_t *data){
    // first, check that the data that is being duplicated is valid
    if(data == NULL)
        return NULL;
    if(data->data == NULL)
        return NULL;
    
    // everything is ok! begin duplication
    struct data_t *ptr = data_create(data->datasize); // creating a new data structure with the
                                                      // same datasize as the original
    if(ptr != NULL){
        memcpy(ptr->data, data->data, data->datasize); // copying the data from the original to
                                                       // the duplicate.
    }

    return ptr;
}

/* Função que substitui o conteúdo de um elemento de dados data_t.
*  Deve assegurar que destroi o conteúdo antigo do mesmo.
*/
void data_replace(struct data_t *data, int new_size, void *new_data){
        if(data != NULL){
            free(data->data);
            data->datasize = new_size;
            data->data = new_data;
        }
}