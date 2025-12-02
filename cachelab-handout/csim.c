#include "cachelab.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    // command line args
    int set_bits = 0;
    int lines = 0;
    int block_bits = 0;
    char verbose = 0;

    // declare string for trace name and location + file pointer
    // trace_location needs initial size to be used with sprintf I think
    char trace_name[20];
    char trace_location[30];
    FILE *fp;

    // cpunts for cache performance
    int hit_count = 0;
    int miss_count = 0;
    int eviction_count = 0;

    // read in command line args and set
    int opt;

    while((opt = getopt(argc, argv, "s:E:b:vt:")) != -1) {
        switch (opt) {
            case 's':
                set_bits = atoi(optarg);
                break;
            case 'E':
                lines = atoi(optarg);
                break;
            case 'b':
                block_bits = atoi(optarg);
                break;
	    case 't':
		//trace_name = optarg;
		strncpy(trace_name, optarg, strlen(optarg)+1);
		break;	
            case 'v':
                verbose = 1;
            default:
                printf("incorect usage, use only flags s, E, b and optionally v\n");
                return 0;
        }
    }

    sprintf(trace_location, "traces/%s", trace_name);
    printf("Trace: %s\n", trace_location);
    fp = fopen(trace_location, "r");
    if (fp == NULL){
    	    printf(" trace file null\n");
	    return 1;
	}
    //print all text in file to confirm
    // fscanf the trace and update the cache accordingly


    // setup simulated cache based on command line arguments
    int sets = 1<<set_bits;
    //int block_size = 1<<block_bits;
    //int tag_bits = 64-block_bits-set_bits;

    // malloc malloc for 2d array
    // for each set
    int** cache = malloc(sizeof(*cache) * sets);
    int ** valid_bits = malloc(sizeof(*valid_bits) * sets);
    int64_t ** tags = malloc(sizeof(*tags) * sets);
    for (int s=0; s<sets; s++) {
        // for each line in a set
        cache[s] = malloc (sizeof(int) * lines);
        valid_bits[s] = malloc(sizeof(int) * lines);
        tags[s] = malloc(sizeof(int64_t) * lines);
    }
    


    // how to do LRU?

       
    // free malloced memory
    for (int s=0; s<sets; s++) {
        free(cache[s]);
        free(valid_bits[s]);
        free(tags[s]);
    }
    free(cache);
    free(valid_bits);
    free(tags);

    //close the trace file
    fclose(fp);

    printf("Set bits: %d\nLines: %d\nBlock bits: %d\nVerbose: %d\n", set_bits, lines, block_bits, verbose);
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
