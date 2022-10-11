#ifndef _TREE_PRIVATE_H
#define _TREE_PRIVATE_H

#include "tree.h"
#include "entry.h"

struct tree_t {
	struct entry_t* entry;
	struct tree_t* leftNode;
	struct tree_t* rightNode;
};

/**
 * Obtém o sucessor inorder do nó atual tendo em conta apenas a
 * subárvore cuja raíz é o nó introduzido no parametro.
 *
 * Funções retiradas de : https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
 */
struct tree_t* minValueNode(struct tree_t* node);

struct tree_t * deleteNode(struct tree_t *root, char *key, int *found);



#endif
