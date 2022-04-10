#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"
#include <stdio.h>

char *_getline(void)
{
    char buf[1024];
    char *ptr = NULL;
    char ptrlen = 0;

	/*Here we read input from stdin in 1024-byte chunks and store the input in a buffer*/
	while(fgets(buf, 1024, stdin))
	{
        	int buflen = strlen(buf);
	/*The first time we read input, we create our buffer using malloc*/
        if(!ptr)
        {
            ptr = malloc(buflen+1);
        }
	/*For subsequent chunks, we extend the buffer using realloc*/	
        else
        {
            char *ptr2 = realloc(ptr, ptrlen+buflen+1);

            if(ptr2)
            {
                ptr = ptr2;
            }
            else
            {
                free(ptr);
                ptr = NULL;
            }
        }

	/*We shouldn't encounter any memory issues here, 
	but if something wrong happens, we print an error message and return NULL*/
        if(!ptr)
        {
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }
	/*If everything goes well, we copy the chunk of 
	input we've just read from the user to our buffer, and we adjust our pointers accordingly*/
        strcpy(ptr+ptrlen, buf);
	
        if(buf[buflen-1] == '\n')		     /*Here, we check to see if the input we’ve got in the buffer ends with\n*/
        {
	    if(buflen == 1 || buf[buflen-2] != '\\') /* if so, if the \ is escaped by a backslash character \\. */
            {					     /* if the last\nis not escaped, the input line is complete and we return */
                return ptr;			     /*  it to the main() function*/	
            }

            ptr[ptrlen+buflen-2] = '\0'; 	     /* Otherwise we remove the two characters (\\and\n) */	
            buflen -= 2;	                     /* print PS2 and continue reading the input */
            print_prompt2();
        }

        ptrlen += buflen;
    }

    return ptr;
}
