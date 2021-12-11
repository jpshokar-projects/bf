/* 
* Author: Jashanpreet Shokar
* License: MIT; see end of file.
* Date: Dec. 10. 2021
* Description:
*    This is a brainfuck embeddable interpreter with an easy to use API.
*/ 

#ifndef BRAINFUCK_H
#define BRAINFUCK_H
#include <stdio.h>
#include <stdlib.h>

#define BF_VERSION_MAX 1
#define BF_VERSION_MID 0
#define BF_VERSION_MIN 0 /* 1.0.0 */
/*
* function: bfStringLength(char* length)
 * description:
*    Fetches total length of a string.
* arguments:
*    char* length | string to be evaluated.
*/
int  bfStringLength(char* length);
/*
* function: bfStringCompare(char* string, char* string2)
 * description:
*    Compares two strings.
* arguments:
*   string | first string to be evaluated.
*   string2| second string to be evaluated.
*/
int  bfStringCompare(char* string, char* string2);

/*
* function: bfRunRawData(char* raw_data, int cell_size, int debugger, int limit_cells);
 * description:
*    bfRunRawData interprets brainfuck code via a char array instead of using bfRunProgram. 
* arguments:
*   char* raw_data    | the data to be interpreted.
*   int   cell_size   | the total cell size to be allocated, set to 0 to make it dynamically allocated.
*   int   debugger    | uses a debugger, {1 - just show all cells }, {2 - show cells in real-time}
*   int   limit_cells | the limit for cells to be shown with debugger. 
*/
void bfRunRawData(char* raw_data, int cell_size, int debugger, int limit_cells);
/*
* function: bfRunProgram(char* file, int cell_size, int debugger, int limit_cells);
 * description:
*    bfRunProgram interprets brainfuck code by file name, it opens the file for you.
* arguments:
*   char* file        | the file to be interpreted
*   int   cell_size   | the total cell size to be allocated, set to 0 to make it dynamically allocated.
*   int   debugger    | uses a debugger, {1 - just show all cells }, {2 - show cells in real-time}
*   int   limit_cells | the limit for cells to be shown with debugger. 
*/
void bfRunProgram(char* file, int cell_size, int debugger, int limit_cells);
#ifdef BRAINFUCK_IMPL
/*
* function: bfStringLength(char* length)
 * description:
*    Fetches total length of a string.
* arguments:
*    char* length | string to be evaluated.
*/
int bfStringLength(char* string)
{
    int length = 0;
    while(string[length++] != '\0');
    return length;
}
/*
* function: bfStringCompare(char* string, char* string2)
 * description:
*    Compares two strings.
* arguments:
*   string | first string to be evaluated.
*   string2| second string to be evaluated.
*/
int bfStringCompare(char* string, char* string2)
{
    while (*string){
        if (*string != *string2)break;
        *string++;
        *string2++;
    };
    return *(const unsigned char*)string -  *(const unsigned char*)string2;
}

/*
* function: bfRunRawData(char* raw_data, int cell_size, int debugger, int limit_cells);
 * description:
*    bfRunRawData interprets brainfuck code via a char array instead of using bfRunProgram. 
* arguments:
*   char* raw_data    | the data to be interpreted.
*   int   cell_size   | the total cell size to be allocated, set to 0 to make it dynamically allocated.
*   int   debugger    | uses a debugger, {1 - just show all cells }, {2 - show cells in real-time}
*   int   limit_cells | the limit for cells to be shown with debugger. 
*/
void bfRunRawData(char* raw_data, int cell_size, int debugger, int limit_cells)
{
    int success = 1;
    
    int cell_used;
    unsigned char* cells;
    int defaults_enabled = 0;
    if (cell_size != 0)
    {
        cells = malloc(sizeof(unsigned char) * cell_size);
    } else
    {
        defaults_enabled = 1;
        cell_size = 2;
        cell_used = 0;
        cells = malloc(sizeof(unsigned char) * cell_size);
        
    }
    
    
    if (cells == NULL)
    {
        printf("bf: error: could not allocate memory.");
        success = 0;
    }
    int raw_data_size = bfStringLength(raw_data);
    
    int cell_marker = 0;
    int start_loop = 0;
    for (int i=0;i<raw_data_size;i++)
    {
        
        switch( raw_data[i] )
        {
            
            case '[':
            {
                
                start_loop = i;
                
            }break;
            case ']':
            {
                if (cells[cell_marker] != 0)
                    i = start_loop;
                
            }break;
            case '>':
            {
                
                cell_marker += 1;
                cell_used += 1;
                if (debugger == 2)
                    printf("[%i]\n", cells[cell_marker]);
            } break;
            case '<':
            {
                cell_marker -= 1;
                if (debugger == 2)
                    printf("[%i]\n", cells[cell_marker]);
            } break;
            case '+':
            {
                
                cells[cell_marker] +=1;
                if (debugger == 2)
                    printf("[%i]\n", cells[cell_marker]);
                
            } break;
            case '-':
            {
                cells[cell_marker] -= 1;
                if (debugger == 2)
                    printf("[%i]\n", cells[cell_marker]);
                
            } break;
            case '!':
            {
                exit(0);
            } break;
            case ',':
            {
                cells[cell_marker] = getchar();
                if (debugger == 2)
                    printf("[%i]\n", cells[cell_marker]);
            } break;
            case '.':
            {
                
                printf("%c", cells[cell_marker]);
                if (debugger == 2)
                    printf("\n[%i]\n", cells[cell_marker]);
            } break;
            case 0: exit(0); break;
        }
        if (defaults_enabled == 1){
            if (cell_used >= cell_size)
            {
                cell_size *= 2;
                
                cells = realloc(cells, sizeof(unsigned char) * cell_size);
                if (cells == NULL)
                {
                    printf("bf: error: could not allocate memory.");
                    exit(1);
                    success = 0;
                }
                
            }
            
        }
    }
    
    if (debugger)
    {
        if (limit_cells == 0)
            limit_cells = cell_size;
        printf("\n\nbf: debugger: cells values up to: %i\n", limit_cells);
        if (cell_size > limit_cells)
        {
            
            for (int i=0;i<limit_cells;i++)
            {
                printf("[%i]", cells[i]);
                
            }
        } else
        {
            for (int i=0;i<cell_size;i++)
            {
                printf("[%i]", cells[i]);
                
            }
        }
        printf("\n");
    }
    
    if (!success){
        printf("bf: fatal error: could not run.\n");
        exit(1);
    }
}

/*
* function: bfRunProgram(char* file, int cell_size, int debugger, int limit_cells);
 * description:
*    bfRunProgram interprets brainfuck code by file name, it opens the file for you.
* arguments:
*   char* file        | the file to be interpreted
*   int   cell_size   | the total cell size to be allocated, set to 0 to make it dynamically allocated.
*   int   debugger    | uses a debugger, {1 - just show all cells }, {2 - show cells in real-time}
*   int   limit_cells | the limit for cells to be shown with debugger. 
*/
void bfRunProgram(char* file, int cell_size, int debugger, int limit_cells)
{
    FILE* file_stream = fopen(file, "rwb");
    
    int success = 1;
    if (file_stream == NULL)
    {
        printf("bf: error: %s: No such file or directory.\n", file);
        success = 0;
        exit(1);
    }
    
    long bytes = 0;
    fseek(file_stream, bytes, SEEK_END);
    bytes = ftell(file_stream);
    rewind(file_stream);
    
    char* file_contents = malloc(bytes);
    
    if (file_contents == NULL)
    {
        printf("bf: error: %s: could not allocate memory.", file);
        success = 0;
    }
    
    if (fread(file_contents, 1, bytes, file_stream) == 1)
    {
        printf("bf: fatal error: could not read.\n");
        success = 0;
    };
    if (!success){
        printf("bf: fatal error: could not run.\n");
        exit(1);
    }
    
    bfRunRawData(file_contents, cell_size,  debugger, limit_cells);
    
}

#endif
#endif
/*
Copyright Jashanpreet Shokar 2021

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
