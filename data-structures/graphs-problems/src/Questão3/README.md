### Compile

```bash
g++ main.cpp -o out

```

## How the main program works

Reads the file "grafos.txt" containing multiple graphs. This file must be in the same folder as the program. The program reads all graphs and, in the same reading order, prints a number (referring to the test case) followed by a sequence of ordered pairs (i, j) indicating a street assigned from intersection i to intersection j. All pairs are printed in increasing order of i. Finally, a hash (#) is printed to indicate that all pairs for the current case have been printed.

> [!NOTE] Example files are provided in the source code folder for easier testing. To test a file, paste one of the example files into the folder and rename it to "grafos.txt".
