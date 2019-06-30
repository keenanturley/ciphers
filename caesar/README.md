# caesar
This program takes the plaintext or ciphertext from a Caesar Cipher and encrypts or decrypts it respectively. There are a few options available to present the output in different ways.

## Installation
On linux:
```
gcc caesar.c
```

## Usage
```
./caesar [options] "message" key
```

Default behavior is to capitalize and encrypt only alphabetical characters, outputting all other characters unmodified.

### Options
```
-e: Encrypt input using key (redundant)
-d: Decrypt input using key
-s: Strip non-alphabetic characters from output
-f: Remove whitespace from output (fold spaces)
-r: Retain letter case in output
-a: show output for all keys (1-25)
```

## Examples

### Default Encryption
```
$ ./caesar "Hello, world!" 3
KHOOR, ZRUOG!
```

### Decrypt Previous
```
$ ./caesar -d "KHOOR, ZRUOG!" 3
HELLO, WORLD!
```

### Obfuscated Ciphertext
```
$ ./caesar -sf "Have a great day! You can do this." 10
RKFOKQBOKDNKIIYEMKXNYDRSC

$ ./caesar -d "RKFOKQBOKDNKIIYEMKXNYDRSC" 10
HAVEAGREATDAYYOUCANDOTHIS
```

### Unobfuscated Ciphertext
```
$ ./caesar -r "Meet me at Disney World, 4:30PM. SHARP!" 17
Dvvk dv rk Uzjevp Nficu, 4:30GD. JYRIG!
```

### All Ciphertexts for Input
```
$ ./caesar -easf "Hello... Is this thing on?"
ROT1:   IFMMPJTUIJTUIJOHPO
ROT2:   JGNNQKUVJKUVJKPIQP
ROT3:   KHOORLVWKLVWKLQJRQ
ROT4:   LIPPSMWXLMWXLMRKSR
...
ROT25:  GDKKNHRSGHRSGHMFNM
```

### Key > 25
```
$ ./caesar "Hello, world!" 1574
VSZZC, KCFZR!

$ ./caesar "Hello, world!" 14
VSZZC, KCFZR!
```
Since `1574 mod 26 = 14`, both keys should produce the same output.
