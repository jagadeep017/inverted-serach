#include "search.h"
#include "struct.h"
#include "file.h"
#include <stdlib.h>
#include <stdio.h>
#include "create.h"
#include <string.h>


int main(int argc, char **argv){
    m_node **hash_table;    //hash table
    int create_flag=0;      //flag to check if the database is created
    hash_table=(m_node **)calloc(sizeof(m_node*),27);       //creating the hash table with NULL of size 27
    if(hash_table==NULL){
        fprintf(stderr,"ERROR:failed to create the hash table\n");
        return FAILURE;
    }
    files *file_list=NULL;          //files list given taken from cmd line argvs
    files *data_base_files=NULL;    //files list which are added to the database
    validate_args(argc,argv,&file_list);        //validating the arguments and appending to the file list
    do {
    printf("1. Create Database\n2. Search\n3. Display\n4. Save\n5. Update\n6. Exit\nSelect option : ");
    int choice;
    scanf("%d",&choice);    //scaning the choice
    switch (choice) {
        case 1:         //creating the database from give files
            if(create_flag==1){
                printf("Database already exists\n");    //making sure that the database is not created twice
                break;
            }
            create_flag++;
            files *temp1=file_list;
            if(temp1==NULL){
                printf("No files found\n");
                break;
            }
            while(temp1!=NULL){
                files *temp2=data_base_files;
                while(temp2!=NULL){     //checking if the file is already in the database
                    if(strcmp(temp1->file,temp2->file)==0){
                        break;
                    }
                    temp2=temp2->link;
                }
                if(temp2!=NULL){
                    printf("Info : File content of %s already exists in the database\n",temp1->file);
                    temp1=temp1->link;      //if the file is already in the database skipping insertion its data
                    continue;
                }
                insert_file(&data_base_files, temp1->file);     //inserting the file name ti the data_base_files list
                add_to_base(hash_table,temp1->file);        //function to insert the file content to the hash table
                printf("Info : File content of %s added to the database\n",temp1->file);
                temp1=temp1->link;
            }
            break;
        case 2:
            search(hash_table);     //function to search the database
            break;
        case 3:
            display(hash_table);    //function to display the database
            break;
        case 4:
            save(hash_table);       //function to save the database to a <.txt> file
            break;
        case 5:
            if(create_flag==1){
                printf("Database is not empty.\n");     //making sure that the database is not empty
                break;
            }
            update(hash_table,&data_base_files);    //function to update the database from a <.txt> file
            //files *temp=data_base_files;
            break;
        case 6:
            printf("Exiting the program.\n");    //exiting the program
            return 0;
        default:
            printf("Invalid choice.\n");        //invalid choice
            break;
    }
    }while (1);     //infinite loop till the user wants to exit
    return 0;
}