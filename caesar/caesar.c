/*
Caesar Cipher Practice Implementation
Author: Keenan Turley <keenan.turley@gmail.com>

"The encryption can also be represented using modular arithmetic by first
transforming the letters into numbers, according to the scheme,
A -> 0, B -> 1, ..., Z -> 25."[1]


Outputs ciphertext or a message corresponding to a given input and key
using the Caesar Cipher. The output is determined by the flag passed to the
program. '-e' for encryption, '-d' for decryption. If neither is provided
encryption is performed.

The message is any string provided as a commandline argument.
The program ignores whitespace and non-alphabetic characters.
Output is in uppercase.

The key is a number indicating the amount of characters to shift
the alphabet for use in the transpositional cipher.
The key is given as a positive integer string and converted using atoi().

Options:
    -e: Encrypt input using key
    -d: Decrypt input using key
    -s: Strip non-alphabetic characters from output
    -f: Remove whitespace from output (fold spaces)
    -r: Retain letter case in output
    -a: show output for all keys (1-25)

Sources:
[1] https://en.wikipedia.org/wiki/Caesar_cipher
[2] http://mathworld.wolfram.com/CaesarsMethod.html

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

/* Flags */
int encrypt_flag = 0;
int decrypt_flag = 0;
int strip_flag = 0;
int fold_flag = 0;
int retain_case_flag = 0;
int all_output_flag = 0;
int error_flag = 0;

/*
Handles the command-line arguments and sets global flags based on them

Parameters:
    int argc: argument count from main() arguments
    char* argv[]: argument vector from main() arguments
*/
void handle_options(int argc, char* argv[]);

/*
Encrypts the message using the Caesar Cipher

Parameters:
    char* message: the string that will be encrypted
    int key: the key / number of letter shifts to perform for the cipher
Returns:
    char*: The resulting ciphertext string
*/
char* encrypt(char* message, int key);

/*
Decrypts the ciphertext using the Caesar Cipher encryption and a modified key

Parameters:
    char* ciphertext: the string that will be decrypted
    int key: the key / number of letter shifts to perform for the decryption
Returns:
    char*: the resulting message string

*/
char* decrypt(char* ciphertext, int key);

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
    char* input;
    int key;
    char* output;

    handle_options(argc, argv);

    // Set variables to arguments
    input = malloc(strlen(argv[optind]) + 1);
    if (input == NULL)
    {
        fprintf(stderr, "Failed to allocate space for input string\n");
        exit(1);
    }
    strcpy(input, argv[optind]);

    // If printing out all possible output, key is not required
    if (all_output_flag)
    {
        // loop through each key (1-25)
        for (key = 1; key < 26; key++)
        {
            output = (decrypt_flag) ? decrypt(input, key) : encrypt(input, key);

            // Print the key and cipher / plaintext
            printf("ROT%d:\t%s\n", key, output);

            // Free the string, since it's on the heap
            free(output);
        }

        // Free input before exiting early
        free(input);

        // Done outputting, exit program
        exit(0);
    }

    // key should be converted from string to int
    key = atoi(argv[optind + 1]);

    // Perform encryption
    output = (decrypt_flag) ? decrypt(input, key) : encrypt(input, key);

    // Print input and output
    printf("%s\n", output);

    // Free string memory
    free(input);
    free(output);

    return 0;
}

void handle_options(int argc, char* argv[])
{
    // Current option character
    int c;

    // Iterate through provided options
    while((c = getopt(argc, argv, "edsfra")) != -1)
    {
        switch(c)
        {
            case 'e':
                if (decrypt_flag)
                    error_flag++;
                else
                    encrypt_flag++;
                break;
            case 'd':
                if (encrypt_flag)
                    error_flag++;
                else
                    decrypt_flag++;
                break;
            case 's':
                strip_flag++;
                break;
            case 'f':
                fold_flag++;
                break;
            case 'r':
                retain_case_flag++;
                break;
            case 'a':
                all_output_flag++;
                break;
            case '?':
            fprintf(stderr, "Unrecognized option: '-%c'\n", optopt);
            error_flag++;
        }
    }
    if (error_flag)
    {
        fprintf(stderr, "usage: ./caesar [-e|-d] [-s] [-f] [-r] [-a] input key\n");
        exit(1);
    }
}

char* encrypt(char* message, int key)
{
    // Allocate space for the string
    // length of message + 1 is used to accompany the '\0' character
    char* ciphertext = malloc(strlen(message) + 1);
    if (ciphertext == NULL)
    {
        fprintf(stderr, "Failed to allocate space for ciphertext string\n");
        exit(1);
    }

    // Temporary character
    char c;
    int i;

    // Offset to character insertion index
    int offset = 0;

    for (i = 0; i < strlen(message); i++)
    {
        // If character is not alphabetic
        if (!isalpha(message[i]))
        {
            /*
            If the strip flag is on and the character is not a space, don't
            put it in the ciphertext.
            Also, if the fold flag is on and the character is a space, don't
            put it in the ciphertext.
            Do not do this for the null terminator.
            */
            if (message[i] != '\0' &&
                ((strip_flag && !isspace(message[i])) ||
                (fold_flag && isspace(message[i]))))
            {
                offset++;
                continue;
            }
            // Put current character into ciphertext unchanged
            ciphertext[i - offset] = message[i];
        }
        // Encrypt retaining case
        else if (retain_case_flag)
        {
            c = message[i];
            // Either 'A' or 'a' matching case of c
            char alpha_operand = (isupper(c)) ? 'A' : 'a';
            // Add key shift (using remainder in case of overflow)
            c += (key % 26);
            // Normalize letter to 0-25 by subtracting ASCII 'A'
            c -= alpha_operand;
            // Mod character by 26 to produce letter index [0 - 25]
            c = mod(c, 26);
            // Return to ASCII letter representation by adding 'A'
            c += alpha_operand;

            ciphertext[i - offset] = c;
        }
        // Encrypt with all caps
        else
        {
            c = toupper(message[i]);
            // Add key shift (using remainder in case of overflow)
            c += (key % 26);
            // Normalize letter to 0-25 by subtracting ASCII 'A'
            c -= 'A';
            // Mod character by 26 to produce letter index [0 - 25]
            c = mod(c, 26);
            // Return to ASCII letter representation by adding 'A'
            c += 'A';

            ciphertext[i - offset] = c;
        }
    }
    // Add null terminator, i will be one more than the
    ciphertext[i] = '\0';
    return ciphertext;
}

char* decrypt(char* ciphertext, int key)
{
    /* Since the decryption algorithm is the same as the encryption,
        besides the key being negative, we can use the encrypt function
        with a slightly different key argument. */
    return encrypt(ciphertext, -key);
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
