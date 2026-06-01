#include <stdio.h>
#include "common.h"
#include "index.h"

long create_node(FILE *index, int year, long data_offset) {
    IndexNode node;
    node.year = year;
    node.data_offset = data_offset;
    node.left = -1;
    node.right = -1;
    node.next = -1;

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
    else if(year > current.year){
        if(current.right == -1){
        long right_offset = create_node(index, year, data_offset);
        current.right = right_offset;
        write_node(index, root_offset, current);
        }else{
            insert_node(index, current.right, data_offset, year);
        }
    }else{
        long next_offset = create_node(index, year, data_offset);
        long list_offset = root_offset;
        IndexNode list = read_node(index, list_offset);

        while(list.next != -1){
            list_offset = list.next;
            list = read_node(index, list.next);
        }
        list.next = next_offset;
        write_node(index, root_offset, list);
    }
    return root_offset;
}

long find_node(FILE *index, long root_offset, int year){
    if(root_offset == -1){
        printf("Year not found\n");
        return -1;
    }

    IndexNode current = read_node(index, root_offset);

    if(year < current.year){
        return find_node(index, current.left, year);
    }
    else if(year > current.year){
        return find_node(index, current.right, year);
    }
    else return current.data_offset;
}

void print_same(FILE *index, FILE *data, long offset){
    while (offset != -1){
        IndexNode node = read_node(index, offset);
        LesData dat;
        fseek(data, node.data_offset, SEEK_SET);
        fread(&dat, sizeof(LesData), 1, data);
        printf("%s %d %d %.2lf\n", dat.code, dat.year, dat.species, dat.area);
        offset = node.next;
    }
}
