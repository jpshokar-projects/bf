
#define  BRAINFUCK_IMPL
#include "brainfuck.h"

int main(int argc, char** argv)
{
    
    int size = 0, debugger = 0, limit_cells = 0, next_argument = 0;
    for (int i=0;i<argc;i++)
    {
        
        
        if ((bfStringCompare(argv[i], "--help") == 0) | (bfStringCompare(argv[i], "-h") == 0))
        {
            printf("bf: usage: %s [files] [arguments]\n", argv[0]);
            printf("Arguments\t          \tInformation\n");
            printf("--help\t       \t      \tShows a help menu\n");
            printf("--version\t          \tShows the version\n");
            printf("--debugger\t         \tEnables the debugger for brainfuck\n");
            printf("--debugger-verbose\t\tEnables verbose debugger mode\n");
            printf("--limit-cells [size]\t\tLimits cells preview on debugger\n");
            printf("--cell_size [size]\t\tSets up the cell size\n");
            if (next_argument == 0)
                next_argument = i;
        }
        else if ((bfStringCompare(argv[i], "--version") == 0))
        {
            printf("bf (Brainfuck) Interpreter 1.0.0\nCopyright (C) 2021 Jashanpreet Shokar\nThis program is open sourced and is under a MIT license.\n");
            if (next_argument == 0)
                next_argument = i;
        } else if ((bfStringCompare(argv[i], "--cell_size") == 0))
        {
            size = atoi(argv[i+1]);
            if (next_argument == 0)
                next_argument = i;
        }
        else if ((bfStringCompare(argv[i], "--debugger") == 0))
        {
            debugger = 1;
            if (next_argument == 0)
                next_argument = i;
        }
        else if ((bfStringCompare(argv[i], "--debugger-verbose") == 0))
        {
            debugger = 2;
            if (next_argument == 0)
                next_argument = i;
        }
        else if ((bfStringCompare(argv[i], "--limit-cells") == 0))
        {
            limit_cells = atoi(argv[i+1]);
            if (next_argument == 0)
                next_argument = i;
        } 
        
    }
    if (next_argument == 0)
        next_argument = argc;
    for (int i=1;i<next_argument;i++)
    {
        bfRunProgram(argv[i], size, debugger, limit_cells);
    }
    
    
    
    
    
}