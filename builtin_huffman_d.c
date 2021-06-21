#include "huffman.h"
#include "wrappers.h"
#include "huffman_func.h"
#include "minish.h"


int huffman_d(FILE *fp, char *file_name)
{
	FILE *decompr_file;
	Compr_header *header = malloc_or_exit(sizeof(Compr_header));
	int i;

	fread_or_exit(header, sizeof(Compr_header), 1, fp);
	Symcode sym_arr[header->sym_arraylen];

	for (i = 0; i<header->sym_arraylen;i++) {
		//sym_arr[i] = malloc_or_exit(sizeof(Symcode));
		fread_or_exit(&sym_arr[i], sizeof(Symcode), 1, fp);
	}

	Treenode *huffman_tree = malloc_or_exit(sizeof(Treenode));
	for( i = 0; i < header->sym_arraylen; i++ ){
		insert_symcode(huffman_tree, sym_arr[i].symbol, sym_arr[i].count, sym_arr[i].mask, sym_arr[i].masklen);			
	}

	sprintf(file_name, "%s.ori", file_name);

	if( (decompr_file=fopen(file_name, "w")) == NULL ){
	       return errno;
	}

	Treenode *tptr = huffman_tree;
	int bits;

	for (i = 0; i < (int)(header->filelen);) {
		bits = freadbits(fp);
		tptr = tptr->children[bits];
		if(is_leaf(tptr)) {
			putc(tptr->code->symbol, decompr_file);
			tptr = huffman_tree;
			i++;
		}
	}
	

	fflush(decompr_file);
	fclose(decompr_file);

	return 0;
}

int builtin_huffman_d(int argc, char **argv) 
{
	char usage_msg[] = "Usage: huffman-d archivo\n";
	FILE *fp;
	char *ext = ".huf";


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


	huffman_d(fp, strtok(argv[1], ext));

	return EXIT_SUCCESS;
}

