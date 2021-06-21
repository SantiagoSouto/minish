#include "huffman.h"
#include "heap_generic.h"
#include "huffman_func.h"
#include "wrappers.h"
#define leftmostbit(mask, masklen) ((mask >> (masklen-1)) & 1)

Heap *new_empty_treenode_heap(int capacity) {
    Heap *h;
    h = malloc_or_exit(sizeof(Heap));
    h->capacity = capacity;
    h->used = 0;
    h->nodearray = calloc_or_exit(capacity, sizeof(Treenode *));
    return h;
}

int is_leaf(Treenode *tn) {
    return (tn->children[0] == NULL && tn->children[1] == NULL);
}

Treenode *new_treenode(Symcode *sym) {
    Treenode *tn;
    tn = (Treenode *) malloc_or_exit(sizeof(Treenode));
    tn->code = sym;
    tn->children[0] = NULL;
    tn->children[1] = NULL;
    return tn;
}

Treenode *pop_heap(Heap *H) {
    Treenode *tn = H->nodearray[0];
    swap_heap_elem(H->nodearray, H->used, sizeof(Treenode *), 0, H->used-1);
    heap_bubbledown(H->nodearray, H->used-1, sizeof(Treenode *), 0, treenode_min_compare);
    H->used--;
    return tn;
}

void push_heap(Heap *h, Treenode *tn) {
    h->nodearray[h->used++] = tn;
    heap_bubbleup(h->nodearray, h->used, sizeof(Treenode *), h->used-1, treenode_min_compare);
}

int treenode_min_compare(const void *fp, const void *sp) {
    Treenode * const *ftn = fp;
    Treenode * const *stn = sp;
    return (*ftn)->code->count < (*stn)->code->count;
}

Symcode *new_symcode(unsigned int symb, unsigned int count, unsigned int mask, unsigned int masklen) {
    Symcode *sym;
    sym = (Symcode *) malloc_or_exit(sizeof(Symcode));

    sym->symbol = symb;
    sym->count = count;
    sym->mask = mask;
    sym->masklen = masklen;
    return sym;
}

size_t fwrite_bitcode(Symcode *sn, FILE *fp_comprfile) {
    if (sn == NULL) {
        return fputbits(0, 0, fp_comprfile);
    } else {
        return fputbits(sn->mask, sn->masklen, fp_comprfile);
    }
}

Treenode * insert_symcode(Treenode *root, unsigned int symbol, unsigned int count, unsigned int mask, unsigned int masklen) {
    Treenode *tn = malloc_or_exit(sizeof(Treenode));
    tn = root;
    int pos;
    for (int i = masklen; i > 0; i--) {
        pos = leftmostbit(mask, i);
        if (!(tn->children[pos])) {
            tn->children[pos] = malloc_or_exit(sizeof(Treenode));
        }
        tn = tn->children[pos];
    }
    tn->code = new_symcode(symbol, count, mask, masklen);
    
    return root;
}




void set_mask(Treenode *tn, int mask[], int masklen) {
    if (is_leaf(tn)) {
        tn->code->masklen = masklen;
       	for (int i = 0; i < masklen; i++) {
            tn->code->mask |= mask[i];
            tn->code->mask <<= 1;
       	}
        tn->code->mask >>= 1;
        return;
    } else {
        mask[masklen] = 0;
        set_mask(tn->children[0], mask, masklen+1);
        mask[masklen] = 1;
        set_mask(tn->children[1], mask, masklen+1);
   	return;
    }

}
