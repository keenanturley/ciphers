/*
Vigenere Cipher Practice Implementation
Author: Keenan Turley <keenan.turley@gmail.com>


Sources:
[1] https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
Function: validate_args

Validates commandline arguments based on following conditions:
- Must have 2 arguments: message, key
- key must contain only alphabetic characters

Parameters:
    int argc: Number of passed arguments, including program name.
        Intended to be passed from main's parameters.
    char* argv[]: array of arguments in string form, including program name.
        Intended to be passed from main's parameters..
*/
void validate_args(int argc, char* argv[]);

/*
Function: encrypt_char

Uses the Caesar cipher method of shifting to encrypt a character

NOTE: This function could be refactored into a more general character shift
    algorithm that can take an integer shift value

Parameters:
    char message_char: The character to be encrypted
    char key_char: The character used to encrypt the message character
        The key character should be alphabetic.

Returns:
    char: The resulting ciphertext character
*/
char encrypt_char(char message_char, char key_char);

/*
Function: encrypt_message

Encrypts a string using the Vigenere cipher with the provided key.

Parameters:
    char* message: The string to encrypt
    char* key: The key string used to encrypt the message
        This string should be entirely alphabetic.

Returns:
    char*: The resulting ciphertext string
*/
char* encrypt_message(char* message, char* key);

/*
Euclidian modulo operator
In C, if either operand of the % sign is negative we cannot rely
on a positive result

Parameters:
    int a: left-side operand
    int b: right-side operand
Returns:
    int: result of a mod b

Source: https://stackoverflow.com/a/4003287
*/
int mod (int a, int b);

int main(int argc, char* argv[])
{
    char* message;
    char* key;
    char* ciphertext;

    // Validate commandline arguments first
    validate_args(argc, argv);

    // Assign variables from arguments
    message = argv[1];
    key = argv[2];

    // Encrypt message and assign result to ciphertext
    ciphertext = encrypt_message(message, key);

    // Print out ciphertext
    printf("%s\n", ciphertext);

    // Free ciphertext before exiting to prevent memory leak
    free(ciphertext);

    return 0;
}

void validate_args(int argc, char* argv[])
{
    // Arguments must include message and key + program name
    if (argc != 3)
    {
        // Print correct usage and exit with error code 1
        fprintf(stderr, "Usage: ./vignere message key\n");
        exit(1);
    }

    // Check if key contains only alphabetic characters
    for (int i = 0; i < strlen(argv[2]); i++)
    {
        // If the current character is non-alphabetic
        if (!isalpha(argv[2][i]))
        {
            fprintf(stderr, "Key must contain only alphabetic characters.\n");
            exit(2);
        }
    }
}

char encrypt_char(char message_char, char key_char)
{
    char cipher_char;

    // If character isn't alphabetic, return it without converting
    if (!isalpha(message_char))
    {
        return message_char;
    }

    // Normalize characters by capitalizing them
    message_char = toupper(message_char);
    key_char = toupper(key_char);

    // Bound characters to 0-25 by subtracting by 'A'
    message_char -= 'A';
    key_char -= 'A';

    // Shift message character by key, modulo 26
    cipher_char = mod(message_char + key_char, 26);

    // Add 'A' to cipher character to return to uppercase ASCII alphabet
    cipher_char += 'A';

    // Return the resulting ciphertext character
    return cipher_char;
}

char* encrypt_message(char* message, char* key)
{
    // Allocate space for the resulting ciphertext.
    // It should be as long as the message and have enough space for the null
    // terminator '\0'
    char* ciphertext = malloc(strlen(message) + 1);

    // Encrypt each character and store it in the ciphertext string
    int i;
    for (i = 0; i < strlen(message); i++)
    {
        ciphertext[i] = encrypt_char(message[i], key[i % strlen(key)]);
    }

    // Append null terminator to ciphertext
    // i is used because it will have incremented to the last valid character
    // in ciphertext after the loop exits.
    ciphertext[i] = '\0';

    // Return completed ciphertext
    return ciphertext;
}

int mod(int a, int b)
{
    if(b < 0)
        return mod(a, -b);

    int ret = a % b;

    if(ret < 0)
        ret+=b;

    return ret;
}
