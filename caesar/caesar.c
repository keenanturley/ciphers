/*
Caesar Cipher Practice Implementation
Author: Keenan Turley <keenan.turley@gmail.com>

Sources:
https://en.wikipedia.org/wiki/Caesar_cipher
http://mathworld.wolfram.com/CaesarsMethod.html

*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // Plaintext message variable
    char message;
    int key;
    char ciphertext;

    // Must be 3 command line arguments
    // program name, message character, key
    if (argc != 3)
    {
        printf("Usage: ./caesar message key\n");
        printf("message is 1 alphabetical character\n");
        printf("key is an integer indicating the cipher shift\n");
        return 1;
    }

    // Set variables to arguments
    // message is the first character of the first argument
    message = argv[1][0];

    // key should be converted from string to int
    key = atoi(argv[2]);

    // Perform encryption
    // Normalize letter to 0-25 by subtracting ASCII 'a' (dec 97)
    ciphertext = message - 'a';

    // Add key and do modular math
    // c = (m + k) mod 26
    ciphertext = (ciphertext + key) % 26;

    // Return to correct ASCII value by adding 'a'
    ciphertext += 'a';

    // Output both characters
    printf("m = %c, c = %c\n", message, ciphertext);

    return 0;
}
