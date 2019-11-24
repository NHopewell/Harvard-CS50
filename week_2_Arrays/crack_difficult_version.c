#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc !=2 || argv[1] == NULL) {
        string usage = "Usage: ./crack hash\n";
        printf("%s", usage);
        exit(1);
    }
    
    // 26 lowercase + 26 uppercase + \0 counts as 1 character = 53
    const int NUM_LETTERS = 53;

    // looping will halt at null bit - this is used to halt below
    string all_letters = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    char salt[3];         
    char to_check[5] = "\0\0\0\0\0";            
    //second char of user passed string into salt
    strncpy(salt, argv[1], 2); 
    salt[2] = '\0';

    for (int m = 0; m < NUM_LETTERS; m++){
        for (int l = 0; l < NUM_LETTERS; l++){
            for (int k = 0; k < NUM_LETTERS; k++){
                for (int j = 0; j < NUM_LETTERS; j++){
                    for (int i = 1; i < NUM_LETTERS; i++){
                        // first pass through all_letters, other positions held null
                        to_check[0] = all_letters[i];  
                        to_check[1] = all_letters[j]; 
                        to_check[2] = all_letters[k];  
                        to_check[3] = all_letters[l]; 
                        to_check[4] = all_letters[m]; 
                        if (strcmp(crypt(to_check, salt), argv[1]) == 0){
                            printf("%s\n", to_check);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}


