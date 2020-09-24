//Name: Zhengwen Fu, ID: 260856256
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main() {
    //get the CGI payload
    char *data = getenv("QUERY_STRING");
    //initiate a array to store the user's command
    char command[6];
    //initiate a array to store the user's gold
    char goldArray[4];
    //define a counter to go through the payload
    int c=0;
    //define a int as a boolean to decide when to start to copy the command
    int start = 0;
    //define a int as a boolean to check if there's gold argument
    int hasGold = 0;
    //define a int as a boolean to decide when to start to copy the gold
    int startGold = 0;
    //define a index to help the array copy the command
    int index = 0;
    //define a index to help the array copy the gold
    int goldIndex = 0;
    for(; c<strlen(data); c++){
        //when firt meet the '=', the command is reached
        if (*(data+c)=='='){
            start = 1;
            c++;
        }
        //when meet the '&', the command is finished and there is a gold argument
        if(*(data+c)=='&'){
            hasGold = 1;
            break;
        }
        //copy the command
        if(start&&(index<5)){
            command[index] = *(data+c);
            index++;
        }
   }
   //if there's gold argument, read it
    if(hasGold){
        for(; c<strlen(data); c++){
            //when firt meet the '=', the gold is reached
            if(*(data+c)=='='){
                startGold = 1;
                c++;
            }
            //copy the gold
            if(startGold&&(goldIndex<3)){
                goldArray[goldIndex] = *(data+c);
                goldIndex++;
            }
        }
    }
    //add \0 at the end of the command
    if(index == 4){
        command[4] = '\0';
    }else{
        command[5] = '\0';
    }
    //add a int value to gold
    int gold;
    //if there's a existing gold argument, assign it to int gold
    if (hasGold){
        //add \0 at the end of the gold argument
        if(goldIndex == 2){
            goldArray[2] = '\0';
        }else{
            goldArray[3] = '\0';
        }
        //covert the gold array into an int
        gold = atoi(goldArray);
    }
    //if not, initiate the gold to be 10
    else{
        gold = 10;
    }
    
    
    
    

    //check the command and gold and take corresponding actions
    printf("Content-Type:text/html\n\n"); // CGI output tag
    printf("<html><body>");
    //check gold
    if(gold <= 0){
        printf("You lose!");
    }else if (gold >= 100){
        printf("You win!");
    }else{
        //check command
        if (strcmp("NORTH", command) == 0){
            printf("<a href=\"http://www.cs.mcgill.ca/~xdeng10/cgi-bin/addgold.cgi?gold=%d\">Press HERE to go North</a>", gold);
        }
        else if (strcmp("SOUTH", command) == 0){
            printf("<a href=\"https://www.cs.mcgill.ca/~czhou22/cgi-bin/addgold.cgi?gold=%d\">Press HERE to go South</a>", gold);
        }
        else if (strcmp("EAST", command) == 0){
            printf("<a href=\"https://www.cs.mcgill.ca/~xshen16/cgi-bin/addgold.cgi?gold=%d\">Press HERE to go East</a>", gold);
        }
        else if (strcmp("WEST", command) == 0){
            printf("<a href=\"https://www.cs.mcgill.ca/~zgao20/cgi-bin/addgold.cgi?gold=%d\">Press HERE to go West</a>", gold);
        }
        else if (strcmp("GOLD", command) == 0){
            printf("You currently have %d gold<br />", gold);
            printf("<a href=\"https://www.cs.mcgill.ca/~zfu5/cgi-bin/addgold.cgi?gold=%d\">Press HERE to continue</a>", gold);
        }
        else if ((strcmp("link", command) == 0)||(strcmp("Link", command) == 0)||(strcmp("LINK", command) == 0)){
            gold+=10;
            printf("You are right!<br />");
            if(gold >= 100){
                printf("You win!");
            }else{
                printf("<a href=\"https://www.cs.mcgill.ca/~zfu5/cgi-bin/addgold.cgi?gold=%d\">Press HERE to continue</a>", gold);
            }
        }
        else{
            gold-=5;
            printf("The answer is wrong. Right answer: LINK<br />");
            if (gold <= 0){
                printf("You lose!");
            }else{
                printf("<a href=\"https://www.cs.mcgill.ca/~zfu5/cgi-bin/addgold.cgi?gold=%d\">Press HERE to continue</a>", gold);
            }
            
        }
    }
    printf("</body></html>");
    
    
    return 0;
}