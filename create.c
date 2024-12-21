#include "create.h"
#include <stdlib.h>
#include <stdio.h>
#include "search.h"
#include "struct.h"
#include "string.h"

//head: address of hash table
//str: file name
void add_to_base(m_node **head,char *str){      //add to base function
    FILE *fptr=fopen(str,"r");  //open file in read mode
    if(fptr==NULL){         //if file does not exist
        printf("ERROR: unable to open file\n");
        return;
    }
    char temp[20];          //buffer
    while(fscanf(fptr,"%s",temp)!=EOF){    //scan each word of the file into the buffer
        insert_word(head,temp);     //insert the word into the hash table
        int index=hash(*temp);      //get the index
        m_node *temp1=*(head+index);    //make a var temp1 to point to the index th node
        while(temp1!=NULL){         //travserse the indedx th node
            if(strcmp(temp1->word,temp)){   //if the word is not found
                temp1=temp1->link;
            }
            else{       //if the word is found stop
                break;
            }
        }
        if(temp1->sub_link==NULL){  //if the sub node is null (empty)
            temp1->sub_link=(s_node *)malloc(sizeof(s_node));   //allocate memory for new sub node
            if(temp1->sub_link==NULL){  //if allocation fails
                printf("ERROR: unable to allocate moemory");
                return;
            }
            strcpy(temp1->sub_link->file_name,str);     //copy the file name into the sub node
            temp1->sub_link->word_count=1;      //set the word count to 1
            temp1->sub_link->link=NULL;     //set the link to null
            temp1->file_count++;        //increment the file count
            continue;
        }
        s_node *temp2=temp1->sub_link,*prev=NULL;   //take a var temp2 to insert the new sub node
        while(temp2!=NULL){
            if(strcmp(temp2->file_name,str)){   //if the file name is not found
                prev=temp2;
                temp2=temp2->link;
            }
            else{       //if the file name is found
                prev=temp2;
                break;
            }
        }
        if(prev==temp2){    //file name already exists just increment the word count
            prev->word_count++;
        }
        else{   //if the file name is not found insert the new sub node at the end
            temp1->file_count++;
            s_node *new=(s_node *)malloc(sizeof(s_node));   //allocate memory
            if(new==NULL){
                printf("ERROR: unable to allocate moemory");
                return;
            }
            strcpy(new->file_name,str);
            new->word_count=1;
            new->link=NULL;
            prev->link=new;
        }
    }
    fclose(fptr);   //close the file
}

//head: address of hash table
//str: word to inserted into to the hash table
void insert_word(m_node **head,char *str){
    int index=hash(*str);   //get the index
    m_node **temp=head;     //make a var temp to point to the hash table
    if(*(temp+index)==NULL){    //if the index th node is empty just add the word
        m_node *new=(m_node *)malloc(sizeof(m_node));   //new main node
        if(new==NULL){
            printf("ERROR: unable to allocate moemory");    //if allocation fails
            return;
        }
        strcpy(new->word,str);  //copy the word
        new->file_count=0;  //set the file count to 0
        new->link=NULL;
        new->sub_link=NULL;
        *(temp+index)=new;  //insert the new main node
        return ;
    }
    m_node *temp1=*(temp+index);    //make a var temp1 to point to the index th node
    m_node *prev=NULL;
    while(temp1!=NULL){     //traverse the index th nodes
        if(strcmp(temp1->word,str)){    //if the word is not found
            prev=temp1;
            temp1=temp1->link;
        }
        else{   //if the word is found stop no need to insert just return
            return;
        }
    }
    m_node *new=(m_node *)malloc(sizeof(m_node));   //new main node
    if(new==NULL){
        printf("ERROR: unable to allocate moemory");    //if allocation fails
        return;
    }
    strcpy(new->word,str);  //copy the word
    new->file_count=0;  //set the file count to 0
    new->link=NULL;
    new->sub_link=NULL;
    prev->link=new; //insert the new main node at the end
    return ;
}

