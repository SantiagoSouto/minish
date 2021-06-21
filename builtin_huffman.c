#include "huffman.h"
#include "huffman_func.h"
#include "wrappers.h"
#include <stdio.h>

void insert_header (uint16_t magic_nbr, uint8_t sym_arraylen, uint8_t sym_arraysize, uint32_t filelen, FILE *fp) 
{
	Compr_header *header = malloc_or_exit(sizeof(Compr_header));
	header->magic_nbr = magic_nbr;
	header->sym_arraylen = sym_arraylen;
	header->sym_arraysize = sym_arraysize;
	header->filelen = filelen;
	
	fwrite_or_exit(header, sizeof(Compr_header), 1, fp);
}

void fwrite_symcode (Symcode symcode, FILE *fp) 
{
	fwrite_or_exit(&symcode, sizeof(Symcode), 1, fp);
}



int huffman(FILE *fp, char *file_name)
{
	FILE *compr_file;
	Heap *heap;
	Symcode sym_arr[MAXSYMBOL] = {0};
	int c, i, sym_qty, byte_count;

	byte_count = 0;
	sym_qty = 0;
	while( (c=fgetc(fp)) != EOF){
		byte_count++;
		if (sym_arr[c].symbol == 0) {
			sym_arr[c].symbol = c;
			sym_qty++;
		}
		sym_arr[c].count++;
	}

	if( (unsigned)byte_count > MAXFILELEN ){
		return 1;
	}

	heap = new_empty_treenode_heap(sym_qty);

	Treenode *tn;
	for( i = 0; i < MAXSYMBOL; i++ ){
		if( sym_arr[i].count > 0 ){
			tn = new_treenode(&sym_arr[i]);
			push_heap(heap, tn);			
		}
	}

	Treenode *left, *right;
	Symcode *sc;

	while (heap->used > 1) {
		left = pop_heap(heap);
		right = pop_heap(heap);
		sc = new_symcode(0, (left->code->count + right->code->count), -1, -1);
		tn = new_treenode(sc);
		tn->children[0] = left;
		tn->children[1] = right;
		push_heap(heap, tn);
	}

	Treenode *huffman_tree = heap->nodearray[0];
	int mask[BITSFORMASK] = {0};

	set_mask(huffman_tree, mask, 0);

	sprintf(file_name, "%s.huf", file_name);

	if( (compr_file=fopen(file_name, "w")) == NULL ){
	       return errno;
	}

	insert_header((uint16_t) MYMAGICNBR, (uint8_t) sym_qty, (uint8_t) sizeof(Symcode), (uint32_t) byte_count, compr_file);

	for( i = 0; i < MAXSYMBOL; i++ ){
		if( sym_arr[i].count > 0 ){
			fwrite_symcode(sym_arr[i], compr_file);			
		}
	}

	rewind(fp);
	i = 0;
	while( (c=fgetc(fp)) != EOF ){
		sc = &sym_arr[c];
		i = fwrite_bitcode(sc, compr_file);
	}
	if( i > 0 ){
		fwrite_bitcode(NULL, compr_file);
	}

	fflush(compr_file);
	fclose(compr_file);

	return 0;
}




int builtin_huffman(int argc, char **argv) 
{
	char usage_msg[] = "Usage: huffman archivo\n";
	FILE *fp;


	if( argc != 2 ){
		if( argc == 1 ){
			fprintf(stderr, "Argumentos insuficientes!\n");
		} else {
			fprintf(stderr, "Demasiados argumentos!\n");
		}
		fprintf(stderr, "%s", usage_msg);
	}
	
	if( (fp=fopen(argv[1], "r")) == NULL ){
	       return errno;
	}

	huffman(fp, argv[1]);

	return EXIT_SUCCESS;
}

