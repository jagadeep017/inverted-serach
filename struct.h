#ifndef STRUCT_H
#define STRUCT_H

#define FAILURE -1
#define SUCCESS 0
typedef struct main{    //main node
    char word[20];
    int file_count;
    struct sub *sub_link;
    struct main *link;
}m_node;

typedef struct sub{     //sub node
    char file_name[20];
    int word_count;
    struct sub *link;
}s_node;

typedef struct list{     //linked list of files
    char *file;
    struct list *link;
}files;

#endif