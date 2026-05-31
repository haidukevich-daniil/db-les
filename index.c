#include <stdio.h>
#include "common.h"

long create_node(FILE *index, int year, long data_offset) {
    IndexNode node;
    node.year = year;
    node.data_offset = data_offset;
    node.left = -1;
    node.right = -1;

    fseek(index, 0, SEEK_END);
    long offset = ftell(index);
    fwrite(&node, sizeof(IndexNode), 1, index);
    return offset;
}

IndexNode read_node(FILE *index, long offset){
    IndexNode node;
    fseek(index, offset, SEEK_SET);
    fread(&node, sizeof(IndexNode), 1, index);
    return node;
}

void write_node(FILE *index, long offset, IndexNode node){
    fseek(index, offset, SEEK_SET);
    fwrite(&node, sizeof(IndexNode), 1, index);
}

long insert_node(FILE *index, long root_offset, long data_offset, int year){
    if(root_offset == -1){
        return create_node(index, year, data_offset);
    }

    IndexNode current = read_node(index, root_offset);

    if(year < current.year){
        if(current.left == -1){
        long left_offset = create_node(index, year, data_offset);
        current.left = left_offset;
        write_node(index, root_offset, current);
        }else{
            insert_node(index, current.left, data_offset, year);
        }
    }
    if(year > current.year){
        if(current.right == -1){
        long right_offset = create_node(index, year, data_offset);
        current.right = right_offset;
        write_node(index, root_offset, current);
        }else{
            insert_node(index, current.right, data_offset, year);
        }
    }
    return root_offset;
}