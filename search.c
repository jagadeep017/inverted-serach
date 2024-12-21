#include "search.h"
#include "struct.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int hash(char ch){      //hash function
    if(ch>='a' && ch<='z'){
        return ch-'a';      //words starting with lower case
    }
    else if(ch>='A' && ch<='Z'){
        return ch-'A';      //words starting with upper case
    }
    else{
        return 26;  //for no alphabets like 0-9 or special characters
    }
}

void search(m_node **head){     //search function
    char str[20];   //buffer to store the word
    printf("Enter the word to search : ");
    scanf("%s",str);    //get the word
    int index=hash(*str);   //get the index
    m_node *temp=*(head+index);    //make a var temp to point to the index th node
    while(temp!=NULL){
        if(strcmp(temp->word,str)){     //check if the word is found
            temp=temp->link;
        }
        else{                                   //if found print its details and exit
            printf("Word %s found\n",str);
            printf("________________________________________________________________\n");
            printf("%-20s%-12s%-20s%-12s\n","WORD","FILE COUNT","FILE","WORD COUNT");
            printf("________________________________________________________________\n");
            print_node(temp);
            return;
        }
    }
    printf("Elemnet not found\n");      //if no match is found
}

void display(m_node **head){        //display function
    int count=0;     //to count the number of nodes
    char *str="________________________________________________________________\n";
    m_node **temp=head;
    printf("%-20s%-12s%-20s%-12s\n","WORD","FILE COUNT","FILE","WORD COUNT");   //print the headings
    printf("%s",str);
    for(int i=0;i<27;i++){
        if(*(temp+i)!=NULL){
            count++;
            m_node *temp1=*(temp+i);
            while(temp1!=NULL){
                print_node(temp1);      //call the function to print the main node and sub nodes
                temp1=temp1->link;
            }
        }
    }
    if(count==0){   //if no nodes are present
        printf("Database is empty\n");
    }
    printf("\n");
}

void print_node(m_node *temp){  //function to print the main node and sub nodes
    char *str="________________________________________________________________\n";
    printf("%-20s%-12d%-20s%-12d\n",temp->word,temp->file_count,temp->sub_link->file_name,temp->sub_link->word_count);
    s_node *temp1=temp->sub_link->link;
    while(temp1!=NULL){
        printf("%32s%-20s%-12d\n"," ",temp1->file_name,temp1->word_count);
        temp1=temp1->link;
    }
    printf("%s",str);
}