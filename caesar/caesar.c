/*
Caesar Cipher Practice Implementation
Author: Keenan Turley <keenan.turley@gmail.com>

"The encryption can also be represented using modular arithmetic by first
transforming the letters into numbers, according to the scheme,
A -> 0, B -> 1, ..., Z -> 25."[1]


Outputs ciphertext corresponding to a given message and key
using the Caesar Cipher.

The message is any string provided as a commandline argument.
The program ignores whitespace and non-alphabetic characters.
Output is in uppercase.

The key is a number indicating the amount of characters to shift
the alphabet for use in the transpositional cipher.
The key is given as an integer string and converted using atoi().

Sources:
[1] https://en.wikipedia.org/wiki/Caesar_cipher
[2] http://mathworld.wolfram.com/CaesarsMethod.html

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    // Plaintext message variable
    char* message;
    int key;
    char* ciphertext;

    // Must be 3 command line arguments
    // program name, message character, key
    if (argc != 3)
    {
        printf("Usage: ./caesar message key\n");
        printf("message is 1 alphabetic character\n");
        printf("key is an integer indicating the cipher shift\n");
        return 1;
    }

    // Set variables to arguments
    // message is the first argument
    message = malloc(strlen(argv[1]) + 1);
    strcpy(message, argv[1]);

    // key should be converted from string to int
    key = atoi(argv[2]);

    // Allocate memory for ciphertext string
    ciphertext = malloc(strlen(message) + 1);

    // Perform encryption
    for (int i = 0; i < strlen(message); i++)
    {
        // If character is not alphabetic
        if (!isalpha(message[i]))
        {
            // Put current character into ciphertext unchanged
            ciphertext[i] = message[i];
        }
        else
        {
            // Add key shift
            // Normalize letter to 0-25 by subtracting ASCII 'A'
            // Mod character by 26 to produce letter index [0 - 25]
            // Return to ASCII letter representation by adding 'A'
            ciphertext[i] = ((toupper(message[i]) + key - 'A') % 26) + 'A';
        }
    }

    // Output message and ciphertext
    printf("m = %s, c = %s\n", message, ciphertext);

    // Free string memory
    free(message);
    free(ciphertext);

    return 0;
}
