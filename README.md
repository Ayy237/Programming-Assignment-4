# Programming-Assignment-4

Solution

The program uses file I/O (fwrite and fread) to store seat reservation data in a binary file. When the program starts, it loads existing data. After any seat assignment or deletion, the program saves updates back to the file.

Pros
Data is persistent after the program ends
Simple binary storage
Easy to load and save the full structure
Cons
Binary file not readable
No error recovery if the file is corrupted
