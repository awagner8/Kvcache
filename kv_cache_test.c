#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "kv_cache.h"

void usage() {
    printf("Usage: kv_test -n number_kvpairs -b hash_table_bins -t test_number\n");
    printf("  -n <number_kvpairs> Test with the specified number of key value pairs.\n");
    printf("  -b <hash_table bins> Number of bins in the hash table.\n");
    printf("  -t <test number> Specified test to run (0 = all).\n");
}


int main(int argc, char** argv) {
    int c = 0;
    unsigned int num_pairs = 1024, bins = 4, test = 0;

    srandom(210);
    while ((c = getopt(argc, argv, "n:b:t:")) != -1) {
        if (c == 'b') {
            bins = (unsigned int) atoi(optarg);
        } else if (c == 'n') {
            num_pairs = (unsigned int) atoi(optarg); 
        } else if (c == 't') {
            test = (unsigned int) atoi(optarg);
        }else {
            usage();
            exit(1);
        }
    }

    hits = misses = 0;
    run_tests(num_pairs,bins,test);
    
    return 0;
}