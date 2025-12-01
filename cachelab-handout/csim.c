#include "cachelab.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    // read in command line args DONE
    int set_bits = 0;
    int lines = 0;
    int block_bits = 0;
    char verbose = 0;

    int opt;

    while((opt = getopt(argc, argv, "s:E:b:v")) != -1) {
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
            case 'v':
                verbose = 1;
            default:
                printf("incorect usage, use only flags s, E, b and optionally v\n");
                return 0;
        }
    }

    // setup simulated cache based on command line arguments
    // how to do LRU?

    int hit_count = 0;
    int miss_count = 0;
    int eviction_count = 0;

    // fscanf the trace and update the cache accordingly

    printf("Set bits: %d\nLines: %d\nBlock bits: %d\nVerbose: %d\n", set_bits, lines, block_bits, verbose);
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
