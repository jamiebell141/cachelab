#include "cachelab.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <string.h>



int main(int argc, char *argv[])
{
    // read in command line args DONE
    int set_bits = 0;
    int lines = 0;
    int block_bits = 0;
    char verbose = 0;
    char trace_name[60];

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
		strncpy(trace_name, optarg, strlen(optarg));
		break;	
            case 'v':
                verbose = 1;
            default:
                printf("incorect usage, use only flags s, E, b and optionally v\n");
                return 0;
        }
    }

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

    int hit_count = 0;
    int miss_count = 0;
    int eviction_count = 0;

    // fscanf the trace and update the cache accordingly

    // free malloced memory
    for (int s=0; s<sets; s++) {
        free(cache[s]);
        free(valid_bits[s]);
        free(tags[s]);
    }
    free(cache);
    free(valid_bits);
    free(tags);

    printf("Set bits: %d\nLines: %d\nBlock bits: %d\nVerbose: %d\nTrace:%s\n", set_bits, lines, block_bits, verbose, trace_name);
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
