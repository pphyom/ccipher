#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 1024      // length of the char array

// FUNCTION PROTOTYPES
void shifting (int a, char arr[], char c, int key);
void reverse_shifting(int a, char arr[], char c, int key);

int main (int argc, char *argv[])
{
    char buff[SIZE];                   // to store the file
    char ch;
    int i, currentLine = 1;
    int fd, numRead = 0, shift = 0, reverse = 0, lineNum = 0, args = argc, key;
    int eolFlag = 0;

    // check the number of arguments
    if (argc == 1) {    // where there is only 1 argument
        printf("\nUsage: %s -srn filename.txt\n", argv[0]);
        return 1;
    }

    // parsing the flags
    while (args--) {
        if (argv[args][0] == '-') {
            int switch_len = (int) strlen(argv[args]);
            while(switch_len--) {
                if(argv[args][switch_len]=='n')
                    lineNum = 1;
                if(argv[args][switch_len]=='s')
                    shift = 1;
                if(argv[args][switch_len]=='r')
                    reverse = 1;
            }
        }
    }

    // open the file in read only mode
    fd = open(argv[argc-1], O_RDONLY);

    // if the file does not exist, print error message.
    if (fd == -1) {
        printf("Unable to open file!\n");
        return 1;
    }

    while((numRead = read(fd, buff, SIZE)) > 0) {
        if (argc >= 2) {            // only works if there are at least 2 arguments
            if (shift) {            // shift value == 1 means input flag has 's'
                printf("Enter key to shift: ");
                scanf("%d", &key);
                for (i = 0; i < numRead; i++) {
                    ch = buff[i];
                    shifting(i, buff, ch, key);
                }
                printf("\n**Encrypted message:** \n\n%s\n", buff);
            } 
            else if (reverse) {     // reverse value == 1 means input flag has 'r'
                printf("Enter key to undue: ");
                scanf("%d", &key);
                for (i = 0; i < numRead; i++) {
                    ch = buff[i];
                    reverse_shifting(i, buff, ch, key);
                }
                printf("\n**Decrypted message:** \n\n%s\n", buff);
            } 
            else {                  // numbering the lines -- argument 'n'
                for (i = 0; i < numRead; i++) {
                    ch = buff[i];
                    if (lineNum && (eolFlag || currentLine == 1)) {
                        printf("   %d ", currentLine++);
                        eolFlag = 0;
                    }
                    if (ch == '\n') {
                        printf("\n");
                    } else {
                        printf("%c", ch);
                    }
                    if (lineNum && ch == '\n')
                        eolFlag = 1;
                }
            }
        }
    }
    close(fd);
    return 0;
}


// letter shifting algorithm based on user's key input
void shifting (int a, char arr[], char c, int key) {

    if (c >= 'a' && c <= 'z') {
        c = c + key;
        if (c > 'z') {
            c = c - 'z' + 'a' - 1;
        }
        arr[a] = c;
    }
    else if (c >= 'A' && c <= 'Z') {
        c = c + key;
        if (c > 'Z') {
            c = c - 'Z' + 'A' - 1;
        }
        arr[a] = c;
    }
    //printf("\n\n**Encrypted message:** \n\n%s", arr);
}

// letter reverse-shifting algorithm based on user's key input
void reverse_shifting(int a, char arr[], char c, int key) {
    if (c >= 'a' && c <= 'z') {
        c = c - key;
        if (c < 'a') {
            c = c + 'z' - 'a' + 1;
        }
        arr[a] = c;
    }
    else if (c >= 'A' && c <= 'Z') {
        c = c - key;
        if (c < 'A') {
            c = c + 'Z' - 'A' + 1;
        }
        arr[a] = c;
    }
    //printf("\n\n**Decrypted message:** \n\n%s", arr);
}