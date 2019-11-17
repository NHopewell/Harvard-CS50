/*caesar.c
 * 
 * A simple caesar cypher which uses a
 * user passed key to encrypt a message.
 * The user passes the encrpytion key
 * as a command line arg when they run
 * caesar.c and a plaintext message to
 * encrpyt during runtime. Only encodes
 * letters, must skip grammar and spaces.
 * 
 * Example:
 *     $ ./caesar 1
 *     plaintext:  world, say hello!
 *     ciphertext: iadxp, emk tqxxa!
 */
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // convert to int if char representation of int
    // else return 0
    
    const int NUM_LETTERS = 26;
    int code = atoi(argv[1]);
    int z = (int) 'z';
    int Z = (int) 'Z';

    
    string usage = "Usage: ./caesar key\n";
    
    // exit if user passes more than 2 args
    // or arg 2 cant be parsed to int representation (not ASCII)
    if (argc != 2 || code == 0) {
        printf("%s", usage);
        exit(0);
    } 
    
    string plain_text = get_string("plaintext: ");
        
    printf("ciphertext: ");
    // for each char in str array,
    // convert to int, add value passed by user, print as char
    for (int i = 0, plain_text_len = strlen(plain_text); i < plain_text_len; i++) {
        // check if letter of alphabet, must skip grammar.
        if (plain_text[i] >= 'a' && plain_text[i] <= 'z') {
            int c = (int) plain_text[i]+code;
            // if lower case, check if result larger than 'z'
            // // if so minus NUM_LETTERS
            if (c > z) {
                c = c - NUM_LETTERS;
                printf("%c", c);
            } else {
                printf("%c", c);
            }
        } else if (plain_text[i] >= 'A' && plain_text[i] <= 'Z') {
            int c = (int) plain_text[i]+code;
            if (c > Z) {
                c = c - NUM_LETTERS;
                printf("%c", c);
            } else {
                printf("%c", c);
            }
        } else {
            // else make no changes
            printf("%c", plain_text[i]);
        }
    }
    printf("\n");
}    
