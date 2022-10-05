/**
 * Distributed Systems Project Phase 1 :: Tree Module
 * Authors:
 * - Nuno Dias,    fc56330
 * - Bruna Santos, fc56328
 * - Pedro Pinto,  fc56369
 */

#include "data.h"
#include "entry.h"
#include "tree.h"
#include "tree-private.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Função para criar uma nova árvore tree vazia.
 * Em caso de erro retorna NULL.
 */
struct tree_t *tree_create(){
    struct tree_t *ret = malloc(sizeof(struct tree_t));
    ret->entry = NULL;
    ret->leftNode = NULL;
    ret->rightNode = NULL;
    return ret;
}

/* Função para libertar toda a memória ocupada por uma árvore.
 */
void tree_destroy(struct tree_t *tree){
    if(tree != NULL){
        if(tree->leftNode != NULL)
            tree_destroy(tree->leftNode);
        if(tree->rightNode != NULL)
            tree_destroy(tree->rightNode);
        free(tree);
    }
}

/* Função para adicionar um par chave-valor à árvore.
 * Os dados de entrada desta função deverão ser copiados, ou seja, a
 * função vai *COPIAR* a key (string) e os dados para um novo espaço de
 * memória que tem de ser reservado. Se a key já existir na árvore,
 * a função tem de substituir a entrada existente pela nova, fazendo
 * a necessária gestão da memória para armazenar os novos dados.
 * Retorna 0 (ok) ou -1 em caso de erro.
 */
int tree_put(struct tree_t *tree, char *key, struct data_t *value){
    struct entry_t *entry = entry_create(key, value);

    if (entry == NULL) {
        return -1;
    }

    if(tree == NULL || key == NULL || value == NULL){
        return -1;
    }

    // Encontrar a posição para inserir a nova entrada (key, value).
    while(tree->entry != NULL) {
        switch(entry_compare(entry, tree->entry)) {
            case 0:
                //entry_replace(tree->entry, key, value);
                data_destroy(tree->entry->value);
                tree->entry->value = data_dup(value);
                                
                entry_destroy(entry);
                return 0;
            case -1: tree = tree->leftNode; break;
            default: tree = tree->rightNode; break;
        }
    }

    if (tree->entry == NULL) { 

        tree->entry = entry_dup(entry);// entry_create(key, value);
        tree->leftNode = tree_create();
        tree->rightNode = tree_create();

        if (tree->leftNode == NULL || tree->rightNode == NULL) {
            return -1;
        }
    }

    return 0;
}

/* Função para obter da árvore o valor associado à chave key.
 * A função deve devolver uma cópia dos dados que terão de ser
 * libertados no contexto da função que chamou tree_get, ou seja, a
 * função aloca memória para armazenar uma *CÓPIA* dos dados da árvore,
 * retorna o endereço desta memória com a cópia dos dados, assumindo-se
 * que esta memória será depois libertada pelo programa que chamou
 * a função. Devolve NULL em caso de erro.
 */
struct data_t *tree_get(struct tree_t *tree, char *key){
    int cmp;

    if (tree == NULL || key == NULL || tree->entry == NULL) {
        return NULL;
    }

    cmp = strcmp(tree->entry->key, key);

    if (cmp == 0) {
        struct data_t *d = data_dup(tree->entry->value);
        return d;
    } else {
        if (cmp < 0) {
            return tree_get(tree->rightNode, key);
        } else {
            return tree_get(tree->leftNode, key);
        }
    }
}

struct tree_t* minValueNode(struct tree_t* node)
{
    struct tree_t* current = node;
  
    while (current && current->leftNode != NULL && current->leftNode->entry != NULL)
        current = current->leftNode;
  
    return current;
}

struct tree_t * deleteNode(struct tree_t *root, char *key, int *found) {

    if (found)
    *found = 1;

    if (root == NULL || root->entry == NULL) {
        if (found)
        *found = 0;
        return root;
    }
  
    // If the key to be deleted 
    // is smaller than the root's
    // key, then it lies in left subtree
    if ( strcmp(key,  root->entry->key) < 0) {
        root->leftNode = deleteNode(root->leftNode, key, found);

    }
    // If the key to be deleted 
    // is greater than the root's
    // key, then it lies in right subtree
    else if (strcmp(key, root->entry->key) > 0) {
        root->rightNode = deleteNode(root->rightNode, key, found);
        }
  
    // if key is same as root's key, 
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->leftNode == NULL || root->leftNode->entry == NULL) {
            struct tree_t* temp = root->rightNode;
            entry_destroy(root->entry);
            free(root);
            return temp;
        }
        else if (root->rightNode == NULL || root->rightNode->entry == NULL) {
            struct tree_t* temp = root->leftNode;
            entry_destroy(root->entry);
            free(root);
            return temp;
        }

        // node with two children: 
        // Get the inorder successor
        // (smallest in the right subtree)
        struct tree_t* temp = minValueNode(root->rightNode);

        // Copy the inorder 
        // successor's content to this node
        root->entry = temp->entry;
  
        // Delete the inorder successor
        root->rightNode = deleteNode(root->rightNode, temp->entry->key, NULL);
    }
    return root;
}

/* Função para remover um elemento da árvore, indicado pela chave key,
 * libertando toda a memória alocada na respetiva operação tree_put.
 * Retorna 0 (ok) ou -1 (key not found).
 */
int tree_del(struct tree_t *tree, char *key){
    int found = 0;
    deleteNode(tree, key, &found);
    return  found==0 ? -1 : 0;
}

/* Função que devolve o número de elementos contidos na árvore.
 */
int tree_size(struct tree_t *tree){
    int total = 0;
    if(tree != NULL){
        if(tree->entry != NULL)
            total = 1 + tree_size(tree->leftNode) + tree_size(tree->rightNode);
    }
    return total;
}

/* Função que devolve a altura da árvore.
 */
int tree_height(struct tree_t *tree){
    int ret;
    if(tree == NULL)
        ret = 0;
    else {
        int leftHeight = tree_height(tree->leftNode);
        int rightHeight = tree_height(tree->rightNode);
        if(leftHeight > rightHeight) ret = leftHeight + 1;
        else ret = rightHeight + 1;
    }
    return ret;
}

/**
 * Mete as chaves no array especificado, numa inorder traversal, desta forma mantendo a
 * ordem lexografica das chaves
 */
void get_inorder_key(char **tree_key_arr, int *counter, struct tree_t *tree, int array_max){
    if(*counter >= array_max) return;

    if(tree->leftNode != NULL){
        get_inorder_key(tree_key_arr, counter, tree->leftNode, array_max);
    }
    if(tree->entry != NULL){
        tree_key_arr[*counter] = strdup(tree->entry->key);
        *counter += 1;
    }
    if(tree->rightNode != NULL){
        get_inorder_key(tree_key_arr, counter, tree->rightNode, array_max);
    }
}

/* Função que devolve um array de char* com a cópia de todas as keys da
 * árvore, colocando o último elemento do array com o valor NULL e
 * reservando toda a memória necessária. As keys devem vir ordenadas segundo a ordenação lexicográfica das mesmas.
 */
char **tree_get_keys(struct tree_t *tree){
    if(tree == NULL)
        return NULL;

    char **array;
    int tree_sz = tree_size(tree) + 1;
    array = (char **) malloc(sizeof(char *) * tree_sz);
    array[tree_sz - 1] = NULL;
    int counter = 0;
    get_inorder_key(array, &counter, tree, tree_sz - 2);
    return array;
}

/* Função que liberta toda a memória alocada por tree_get_keys().
 */
void tree_free_keys(char **keys){
    int i;
    for(i = 0; keys[i] != NULL; i++)
        free(keys[i]);
    free(keys[i]);
    free(keys);
}

/* Função que devolve um array de void* com a cópia de todas os values da
 * árvore, colocando o último elemento do array com o valor NULL e
 * reservando toda a memória necessária.
 */
void **tree_get_values(struct tree_t *tree){
    void **tree_values;
    if(tree == NULL)
        tree_values = NULL;
    else {
        int size = tree_size(tree);
        tree_values = (void**) malloc(sizeof(void*) * (size + 1));
        char **tree_keys = tree_get_keys(tree);
        int i;
        for(i = 0; tree_keys[i] != NULL; i++){
            struct data_t *toCopy = tree_get(tree, tree_keys[i]);
            tree_values[i] = malloc(toCopy->datasize);
            memcpy(tree_values[i], toCopy->data, toCopy->datasize);
        }
        tree_values[i] = NULL; // ultimo elemento do array == NULL
        tree_free_keys(tree_keys);
    }
    return tree_values;
}

/* Função que liberta toda a memória alocada por tree_get_values().
 */
void tree_free_values(void **values){
    int i;
    for(i = 0; values[i] != NULL; i++)
        free(values[i]);
    free(values[i]);
    free(values);
}