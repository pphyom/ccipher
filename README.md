# ccipher
Linux Encryption/Decryption application using command line arguments in C

Useing system calls to create a Caesar cipher application in C.

## How it works
Take command line arguments for the number of letters to shift and for the name of the file to
open, read, and close.

Example usage:

  Name
  ccipher
  Synopsis
  ccipher [OPTION] … [FILE]...
  Description
  Caesar cipher the contents of FILE, then concatenate to standard
  output.
  OPTIONS:
  -s NUM
  NUM represent the number of letters to shift
  -r
  -r should reverse or ‘undue’.
  EX: -r -s 5: This will undue a message shifted 5.
  -n
  number all output lines
