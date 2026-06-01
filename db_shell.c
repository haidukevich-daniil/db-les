#include <stdio.h>
#include "common.h"
#include "index.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: %s <year>\n", argv[0]);
        return 1;
    }

    FILE *idx = fopen("les.idx","rb");
    FILE *dat = fopen("les.dat","rb");

    if( idx == NULL || dat == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    if(strcmp(argv[1], "FIND") == 0){
        int year = atoi(argv[2]);
        long offset = find_node(idx, 0, year);
        if(offset == -1){
            printf("No data found for year %d\n", year);     
        }
        else{
        print_same(idx, dat, offset);
        }
    }

    if(strcmp(argv[1], "SUM") == 0){
        int from = atoi(argv[2]);
        int to = atoi(argv[3]);
        long offset_from = find_node(idx, 0, from);
    }

    fclose(index);
    fclose(data);

    return 0;
}