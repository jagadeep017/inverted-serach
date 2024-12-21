#include "struct.h"
#include "file.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//argc: number of command line arguments
//argv: array of command line arguments
//file_list: pointer to the linked list of files
void validate_args(int argc,char **argv,files **file_list){  //read and validate the file name
    files *temp;
    for(int i=1;i<argc;i++){
        char *token=strstr(argv[i],".");    //check file type
        if(token==NULL||strcmp(token,".txt")){        //if file type is not .txt
            printf("%s is of not a valid type. must be of <.txt> file\n",argv[i]);
            continue;
        }
        FILE *fptr=fopen(argv[i],"r");      //open file
        if(fptr==NULL){
            printf("%s does not exist\n",argv[i]);  //if file does not exist
            continue;
        }
        fseek(fptr,0,SEEK_END);
        if(ftell(fptr)==0){                         //to check if file is empty
            printf("File %s is empty\n",argv[i]);
            continue;
        }
        temp=*file_list;
        while(temp!=NULL){                                  //to check if file already exists in the database 
            if(strcmp(temp->file,argv[i])==0){      //if file already exists continue
                printf("File %s already exists\n",argv[i]);
                fclose(fptr);
                break;
            }
            temp=temp->link;
        }
        if(temp==NULL){
            insert_file(file_list,argv[i]);          //insert file in the list
            fclose(fptr);
            printf("INFO: file %s added to the files list\n",argv[i]);
        }
    }
}

//str: file name
//file_list: pointer to the linked list of files
void insert_file(files **file_list,char * str){ //insert file name at last
    files *nu=(files *)malloc(sizeof(files));
    if(nu==NULL){
        return ;
    }
    nu->file=malloc(strlen(str));       //allocating memory
    strcpy(nu->file,str);             //copying the file name
    nu->link=NULL;
    if(*file_list==NULL){
        *file_list=nu;
        return ;
    }
    files *temp=*file_list;
    while(temp->link!=NULL){             //inserting at last
        temp=temp->link;
    }
    temp->link=nu;
}

//head: pointer to the hash table
void save(m_node **head){           //save function to save to a <.txt> file
    printf("Enter a file name :");
    char file[20];
    scanf("%s",file);       //scaning the file name
    char *ptr=strstr(file,".");     //check file type
    if(strcmp(ptr,".txt")){                 //if file type is not .txt
        printf("Invalid file type\n");
        return ;
    }
    FILE *fptr=fopen(file,"w");     //open file
    if(fptr==NULL){
        printf("ERROR: unable to open file\n");
        return ;
    }
    m_node **temp=head;
    int flag=0;
    for(int i=0;i<27;i++){
        if(*(temp+i)!=NULL){
            m_node *temp1=*(temp+i);
            while(temp1!=NULL){
                if(temp1!=*(temp)){
                    fprintf(fptr,"\n");     //print a new line if the main node is not the first node
                }
                fprintf(fptr,"#%d;%s;%d;",i,temp1->word,temp1->file_count);     //print the main node contents to the file
                s_node *temp2=temp1->sub_link;
                while(temp2!=NULL){
                    fprintf(fptr, "%s;%d;",temp2->file_name,temp2->word_count); //print the sub node contents to the file
                    temp2=temp2->link;
                }
                fprintf(fptr,"#");  //print a # at the end of the main node
                temp1=temp1->link;
            }
        }
    }
    fclose(fptr);   //close the file
}

//head: pointer to the hash table
//list: pointer to the linked list of files which are added to the database
void update(m_node **head,files **list){
    char str[200];          //buffer to store the file name and file contents
    printf("Enter the database file <.txt> to update : ");
    scanf("%s",str);        //scan the file name
    char *ptr=strstr(str,".");  //check file type
    if(strcmp(ptr,".txt")){    //if file type is not .txt
        printf("Invalid file type\n");
        return ;
    }
    FILE *fptr=fopen(str,"r");  //open the file in read mode
    if(fptr==NULL){
        printf("ERROR: unable to open file\n");    //if file does not exist
        return ;
    }
    m_node *temp;
    str[0]=fgetc(fptr);     //read the first character
    fseek(fptr,-2,SEEK_END);
    str[1]=fgetc(fptr);     //read the last charecter before EOF and /n
    if(str[0]!='#'&&str[1]!='#'){           //if the first and last character are not # i.e the file is not in correct format
        printf("Invalid file format\n");
        fclose(fptr);
        return ;
    }
    fseek(fptr,0,SEEK_SET);     //reset the file pointer
    while(feof(fptr)==0){
        fscanf(fptr,"%s",str);      //scan each line of the file into the buffer
        if(str[0]!='#'){        //if the first character is not # then invalid format
            printf("Invalid file format\n");
            fclose(fptr);
            return ;
        }
        int i=1,index=0;        //index to access the buffer elements
        while(str[i]!=';'){     //extract the index until ';'
            index=index*10+(str[i]-'0');    //ascii to int
            i++;
        }
        m_node *new=(m_node *)malloc(sizeof(m_node));   //create a new main node
        if(new==NULL){      //if memory allocation fails
            printf("ERROR: unable to allocate moemory\n");
            fclose(fptr);
            return ;
        }
        int j=0;
        while(str[++i]!=';'){           //extract the word until ';'
            new->word[j++]=str[i];
        }
        new->word[j]='\0';      //null char at end of the word
        i++;
        j=0;
        while(str[i]!=';'){     //extract till ';'
            j=j*10+(str[i]-'0');    //ascii to int
            i++;
        }
        new->file_count=j;      //also representing the number of sub nodes
        new->link=NULL;
        s_node **prev=&(new->sub_link); //     
        for(int k=0;k<j;k++){   //looping file_count times
            s_node *new1=(s_node *)malloc(sizeof(s_node));  //create a new sub node
            if(new1==NULL){     //if memory allocation fails
                printf("ERROR: unable to allocate moemory\n");
                fclose(fptr);
                return ;
            }
            int count=0;
            i++;
            while(str[i]!=';'){     //extract the file name until ';'
                new1->file_name[count++]=str[i++];
            }
            new1->file_name[count]='\0';    //null char at end of the file name
            i++;
            files *temp=*list;              //check if file already exists
            while(temp!=NULL){
                if(strcmp(temp->file,new1->file_name)==0){    //if file already exists
                    break;
                }
                temp=temp->link;
            }
            if(temp==NULL){     //if file does not exist
                insert_file(list, new1->file_name);     //insert file in the data_base_list
            }
            count=0;
            while(str[i]!=';'){     //extract the word count till ';'
                count=count*10+(str[i++]-'0');      //ascii to int
            }
            new1->word_count=count;
            new1->link=NULL;
            *prev=new1;             //connect the sub nodes
            prev=&(new1->link);     //update prev with the address of the next sub node->link
        }
        if(*(head+index)==NULL){    //if the index is empty
            *(head+index)=new;
            continue;
        }
        temp=*(head+index);     //traverse the linked list
        while(temp->link!=NULL){    //insert the new main node at the end
            temp=temp->link;
        }
        temp->link=new;     
        if(str[++i]!='#'){  //if the next character is not # inavalid format
            printf("Invalid file format\n");
            fclose(fptr);
            return ;
        }
    }
}