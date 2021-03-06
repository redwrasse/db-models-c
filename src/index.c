#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "db.h"
#include "tnode.h"


struct tnode *buildindex(struct db *database, int col) {
    struct tnode *index = NULL;
    struct db *rowptr = database;
    while (rowptr != NULL) {
        if (rowptr->value[col]) {
            index = addtree(index, rowptr, col);
        }
        rowptr = rowptr-> next;
    }
    return index;
}

struct tnode **buildall(struct db *database) {
    struct tnode **indices = (struct tnode **) malloc(sizeof(struct tnode) * NCOLS);
    for (int col = 0; col < NCOLS; col++) {
        indices[col] = buildindex(database, col);
    }
    return indices;
}

struct db *lookup(struct tnode *index, char *value) {
    int cond;
    if (index == NULL) {
        return NULL;
    }
    if ((cond = strcmp(value, index->value)) == 0) {
        return index->rowptr;
    } else if (cond < 0) {
        return lookup(index->left, value);
    } else
        return lookup(index->right, value);
}

