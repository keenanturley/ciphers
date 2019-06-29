/*
Caesar Cipher Practice Implementation
Author: Keenan Turley <keenan.turley@gmail.com>

Sources:
https://en.wikipedia.org/wiki/Caesar_cipher
http://mathworld.wolfram.com/CaesarsMethod.html

*/

#include <stdio.h>

int main(void)
{
    // Plaintext message variable
    char message;
    int key;
    char ciphertext;

    // Introduce program
    printf("-- Caesar Cipher --\n");
    printf("Encrypts plaintext letter to ciphertext letter\n");
    printf("using a given key / rotation shift.\n\n");

    // Get input from user
    printf("Enter a lowercase letter to encrypt: ");
    scanf("%c", &message);

    // Get key from user
    printf("Enter an integer key: ");
    scanf("%d", &key);

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
