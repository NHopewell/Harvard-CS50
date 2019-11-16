/*caesar.c
 * 
 * A simple caesar cypher which uses a
 * user passed key to encrypt a message.
 * The user passes the encrpytion key
 * as a command line arg when they run
 * caesar.c and a plaintext message to
 * encrpyt during runtime.
 * 
 * Example:
 *     $ ./caesar 1
 *     plaintext:  HELLO
 *     ciphertext: IFMMP
 */
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // convert to int if char representation of int
    // else return 0
    int code = atoi(argv[1]);
  
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
        int c = (int) plain_text[i]+code;
        printf("%c", c);
    }
}