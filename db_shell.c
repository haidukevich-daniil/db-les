#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

     if(strcmp(argv[1],"STATS") == 0){
          print_stats(idx);
     }

     IndexHeader header;
     fseek(idx, 0, SEEK_SET);
     fread(&header, sizeof(IndexHeader), 1, idx);

     if(strcmp(argv[1], "FIND") == 0){
          int year = atoi(argv[2]);
          long offset = find_node(idx, header.root_offset, year);
          if(offset == -1){
                printf("No data found for year %d\n", year);     
          }
          else{
                print_same(idx, dat, offset);
          }
     }

     else if(strcmp(argv[1], "SUM") == 0){
          int from = atoi(argv[2]);
          int to = atoi(argv[3]);
          double total = previous_sum(idx, header.root_offset, to) - 
                            previous_sum(idx, header.root_offset, from - 1);
          printf("Total area from %d to %d: %.2lf\n", from, to, total);
     }

     fclose(idx);
     fclose(dat);

     return 0;
}