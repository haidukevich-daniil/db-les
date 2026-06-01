#include <stdio.h>
#include "common.h"
#include "index.h"

int main() {

    FILE *in = fopen("input.txt","r");
    FILE *out = fopen("les.dat","wb");
    FILE *index = fopen("les.idx","wb");

    if( in == NULL || out == NULL || index == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    LesData data;
    long offset = 0;
    long root_offset = -1;


    while(fscanf(in, "%s %d %d %lf",
             data.code, 
             &data.year,
             &data.species,
             &data.area) == 4){
        fwrite(&data, sizeof(LesData), 1, out);

        root_offset = insert_node(index, root_offset, offset, data.year);
        offset += sizeof(LesData);
    }

    fclose(in);
    fclose(out);
    fclose(index);
        
    return 0;
}