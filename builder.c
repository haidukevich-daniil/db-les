#include <stdio.h>
#include "common.h"
#include "index.h"

void builder(FILE *in, FILE *out, FILE *index){

     FILE *in = fopen("input.txt","r");
     FILE *out = fopen("les.dat","wb");
     FILE *index = fopen("les.idx","wb");

     if( in == NULL || out == NULL || index == NULL) {
          printf("Error opening file\n");
          return;
     }

     LesData data;
     IndexHeader header = {0, 0.0, -1};
     fwrite(&header, sizeof(IndexHeader), 1, index);
     long offset = 0;

     while(fscanf(in, "%s %d %d %lf",
               data.code, 
               &data.year,
               &data.species,
               &data.area) == 4){
          fwrite(&data, sizeof(LesData), 1, out);

          header.root_offset = insert_node(index, header.root_offset, offset, data.year, data.area);
          offset += sizeof(LesData);
          header.count++;
          header.total_area += data.area;
     }

     fseek(index, 0, SEEK_SET);
     fwrite(&header, sizeof(IndexHeader), 1, index);

     fclose(in);
     fclose(out);
     fclose(index);
}