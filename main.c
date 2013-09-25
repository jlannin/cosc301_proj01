/*
 * Justin Lannin, 9/22/13
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "list.h"

void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}


int main(int argc, char **argv) {
	FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */
            /* just equate stdin with our datafile */
            datafile = stdin;
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /*
     * you should be able to just read from datafile regardless
     * whether it's stdin or a "real" file.
     */
	char *word, *tmp;
	const char *sep = " \n\t";
	char buffer[256];
	int goodword;
	int test;
	int convert;
	struct linkedlist *head = NULL;
	struct rusage getusagestats;
	while(fgets(buffer, 256, datafile) != NULL)
	{
		for(word = strtok_r(buffer, sep, &tmp); word != NULL; word = strtok_r(NULL, sep,&tmp))
		{
			test = 0;
			goodword = 1;
			if(word[0] == '#')  //rest of line is a comment
			{
				break;
			}
			//test for negative numbers
			if(strlen(word) > 1)
			{
				if(word[0] == '-')
				{
					test++;
				}
			}
			while(test < strlen(word))
			{
				if(!isdigit(word[test]))
				{
					if(word[test] == '#') //handles input in the form of 45#hello
					{
						word[test] = '\0';
						break;
					}
					goodword = 0;
					break;
				}
				test++;
			}
			if (goodword == 1)
			{
				convert = strtol(word, (char **) NULL, 10);
				insert_sort(convert, &head);
			}
		}
	}
	printf("%s\n", "***List Contents Begin***");
	print_list(head);
	printf("%s\n", "***List Contents End***");
	clear_list(head);
	if (fclose(datafile) != 0)
	{
		printf("Unable to close file %s\n", strerror(errno));
                exit(-1);

	}
	if (getrusage(RUSAGE_SELF, &getusagestats) == -1)
	{
		printf("Unable to get CPU Resource Statistics, Exiting Now %s\n", strerror(errno));
                exit(-1);

	}
	double systime = ((((getusagestats.ru_stime).tv_sec)/1.0) + (((getusagestats.ru_stime).tv_usec))/1000000.00);
        double usertime = ((((getusagestats.ru_utime).tv_sec)/1.0) + (((getusagestats.ru_utime).tv_usec))/1000000.00);
    	printf("%s%f\n","User time: ", usertime);
	printf("%s%f\n", "System time: ", systime);
	return 0;
}
