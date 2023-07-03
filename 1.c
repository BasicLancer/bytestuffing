#include <stdio.h>
#include <string.h>

#define FLAG_BYTE 0x7E  // Flag byte used for framing
#define ESCAPE_BYTE 0x7D  // Escape byte used for escaping special characters
#define ESCAPE_MASK 0x20  // Mask byte used to xor with special characters

// Function to perform byte stuffing on data
void byteStuffing(char* input, int length, char* output) {
    int i, j;
    j = 0;

    // Add flag byte at the beginning
    output[j++] = FLAG_BYTE;

    for (i = 0; i < length; i++) {
        // Check for special characters
        if (input[i] == FLAG_BYTE || input[i] == ESCAPE_BYTE) {
            // Add escape byte
            output[j++] = ESCAPE_BYTE;
            // Xor with the escape mask
            output[j++] = input[i] ^ ESCAPE_MASK;
        } else {
            // Add normal byte 
            output[j++] = input[i];
        }
    }

    // Add flag byte at the end
    output[j++] = FLAG_BYTE;
}

// Function to perform byte unstuffing on data
void byteUnstuffing(char* input, int length, char* output) {
    int i, j;
    j = 0;

    for (i = 1; i < length - 1; i++) {
        // Check for escape byte
        if (input[i] == ESCAPE_BYTE) {
            // Xor with the escape mask to retrieve original character
            output[j++] = input[++i] ^ ESCAPE_MASK;
        } else {
            // Add normal byte
            output[j++] = input[i];
        }
    }
}

int main() {
    char input[] = {0x7E, 0x01, 0x02, 0x7D, 0x7E};
    int inputLength = sizeof(input) / sizeof(input[0]);

    char stuffed[2 * inputLength];
    byteStuffing(input, inputLength, stuffed);

    printf("Stuffed data: ");
    for (int i = 0; i < 2 * inputLength; i++) {
        printf("%02X ", (unsigned char) stuffed[i]);
    }
    printf("\n");

    char unstuffed[inputLength];
    byteUnstuffing(stuffed, 2 * inputLength, unstuffed);

    printf("Unstuffed data: ");
    for (int i = 0; i < inputLength; i++) {
        printf("%02X ", (unsigned char) unstuffed[i]);
    }
    printf("\n");

    return 0;
}
