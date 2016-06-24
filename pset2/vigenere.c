#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



int main(int argc, string argv[]){
    string command = argv[0];
    int commandLength = strlen(command);
    int commandValidity;
    
    if (commandLength > 10) {
    commandValidity = strncmp(command, "./vigenere", commandLength);
    }
    else {
    commandValidity = strncmp(command, "./vigenere", 10);
    }
    
    if (argc != 2 || commandValidity != 0) {
    printf("You must insert a key!\n");
    return 1;
    }
    
    string key = argv[1];
    int keyLength = strlen(key);
    
    
    for (int i = 0; i<keyLength ; i++) {
            if (isalpha(key[i]) == 0) {
                printf("You must insert a key!\n");
                return 1;
            } 
        }
    
    string text = GetString();
    int textLength = strlen(text);
    int j = 0;
    int v;  // value
    
    for (int i = 0; i<textLength ; i++) {
    
    if(j==keyLength) {
       j = 0;
    } 
    
    if(isalpha(text[i])) {
            if(islower(text[i])) {
                v = ((char) text[i] - 97 + (char) tolower(key[j]) - 97) % 26;
                printf("%c", v+97);
            }
            
            else {
            v = ((char) text[i] - 65 + (char) tolower(key[j]) - 97) % 26;
                printf("%c", v+65);
                
            }
            j++;
        }
        
        else {
        printf("%c", text[i]);
        }
        
    }
    printf("\n");
    return 0;
    
   }
