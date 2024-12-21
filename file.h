#ifndef FILE_H
#define FILE_H
#include "struct.h"

void validate_args(int argc,char **argv,files **file_list);

void insert_file(files **file_list,char * str);

void save(m_node **head);

void update(m_node **head,files **list);

#endif