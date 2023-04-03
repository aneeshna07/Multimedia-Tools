#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "volume.h"
#include "TE.h"
#include "filter.h"

void delay(float seconds){
    // Converting time into milli_seconds
    int milli_seconds = 1000 * seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);

}


int main(){
    char* ch = "Welcome to Multimedia tools!\nWhich tool would you like to use?\n1.Text Editor\n2.Volume mixer\n3.Image filters\nAny other key to exit";
    int i = 0;
    while(*(ch+i) != 0){
        printf("%c",*(ch+i));
        delay(0.075);
        i++;
    }
    char s[5];
    int n = 0;
    do{
        printf("Enter your choice as either 1/2/3\n");
        scanf("%s",s);
        n = atoi(s);
    }while(n < 1 || n > 3);

    switch(n){
        case 1: TE();
                break;
        case 2: volume();
                break;
        case 3: //filters();
                break;
        default: exit(0);
    }
}