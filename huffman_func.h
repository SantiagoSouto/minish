#include <stdio.h>

extern Heap * new_empty_treenode_heap(int capacity);
extern int is_leaf(Treenode *tn);
extern int treenode_min_compare(const void *p, const void *q);
extern Treenode * pop_heap(Heap *H);
extern void push_heap(Heap *H, Treenode *tn);
extern size_t fwrite_bitcode(Symcode *sn, FILE *fp_comprfile);
//extern size_t fwrite_symcodes(Treenode *tn, FILE *fp_comprfile);
//extern void generate_bitcodes(Treenode *tn, unsigned long int mask, unsigned int  masklen);
extern Symcode * new_symcode(unsigned int symb, unsigned int count, unsigned int mask,
                    unsigned int masklen);
extern Treenode * new_treenode(Symcode *sn);
extern Treenode * insert_symcode(Treenode *root, unsigned int symbol, unsigned int count,
                    unsigned int mask, unsigned int masklen);
//extern Treenode * build_huffman_tree(Heap *H);

extern void set_mask(Treenode *tn, int mask[], int masklen);

extern size_t fputbits(int mask, int  masklen, FILE *fp);
extern size_t freadbits(FILE *fp);
