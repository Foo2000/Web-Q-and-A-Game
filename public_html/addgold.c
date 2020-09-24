//Name: Zhengwen Fu, ID: 260856256
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main() {
    //get the CGI payload
    char *data = getenv("QUERY_STRING");
    //initiate a array to store the user's gold
    char goldArray[4];
    //define a counter to go through the payload
    int c=0;
    //define a int as a boolean to decide when to start to copy the gold
    int start = 0;
    //define a index to help the array copy the gold
    int index = 0;
    for(; c<strlen(data); c++){
        //when firt meet the '=', the gold is reached
        if (*(data+c)=='='){
            start = 1;
            c++;
        }
        //copy the gold
        if(start&&(index<3)&&(*(data+c)!='&')&&(*(data+c)!='\0')){
            goldArray[index] = *(data+c);
            index++;
        }
    }

    int goldpieces;
    //add \0 at the end of the answer
    if(index == 2){
        goldArray[2] = '\0';
    }else{
        goldArray[3] = '\0';
    }
    //covert the gold array into an int
    goldpieces = atoi(goldArray);

    //copy the index.html
    FILE *page = fopen("../index.html","rt");
    char line[500];
    char *contained;
    int notAdded = 1;
    printf("Content-Type:text/html\n\n"); // CGI output tag
    fgets(line, 500, page);
    while(!feof(page)){
        printf("%s", line);
        //insert the argument for gold
        contained = strstr(line, "input");
        if ((contained!=NULL)&&(notAdded)){
            printf("<input type=\"hidden\" name=\"gold\" value=\"%d\">", goldpieces);
            notAdded = 0;
        }
        fgets(line, 500, page);
    }
    fclose(page);
    return 0;
}