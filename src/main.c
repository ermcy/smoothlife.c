#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include "include/grid.h"
#include "include/args.h"


int main(int argc, char **argv) {
    opterr = 0;
    struct arguments args = {0};
    init_default(&args);
    int arg;
    while (1) {
        arg = getopt_long_only(argc, argv, "w:t:f:h:v", long_options, NULL);
        if (arg == -1) break;
        switch (arg) {
            // Width
            case 'w': {
                size_t w = strtoul(optarg, NULL, 10);
                if (w == 0 || w == SIZE_MAX) {
                    fprintf(stderr, "Width cannot be 0 or %llu.", SIZE_MAX);
                    exit(EXIT_FAILURE);
                }
                args.width = w;
                break;
            }
                // Height
            case 'h': {
                size_t h = strtoul(optarg, NULL, 10);
                if (h == 0 || h == SIZE_MAX) {
                    fprintf(stderr, "Height cannot be 0 or %zu.", SIZE_MAX);
                    exit(EXIT_FAILURE);
                }
                args.height = h;
                break;
            }
                // Shrink Factor
            case 'f': {
                uint8_t f = (uint8_t) strtol(optarg, NULL, 10);
                if (f == 0 || f == UINT8_MAX) {
                    fprintf(stderr, "Factor cannot be 0 or %d.", UINT8_MAX);
                    exit(EXIT_FAILURE);
                }
                break;
            }
                // Time step
            case 't': {
                float t = strtof(optarg, NULL);
                if (t == ERANGE) {
                    fprintf(stderr,
                            "Time step could not be parsed. Make sure you are doing --delta-time=TIME and not -t TIME");
                    exit(EXIT_FAILURE);
                }
                args.delta_time = t;
                break;
            }
                // Version
            case 'v': {
                version(&args);
                break;
            }
            default: {
                usage(&args);
                break;
            }
        }
    }
    if (optind < argc) {
        fprintf(stderr, "Irrelevant arguments in the invocation.\n");
        while (argc > optind) {
            printf(" %s ", argv[optind]);
            optind++;
        }
        putchar('\n');
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    Grid grid = {0};
    init(&grid, args.width, args.height, args.shrink_factor);
    Grid diff = {0};
    empty(&diff, args.width, args.height, args.shrink_factor);
    display(&grid);
    for (;;) {
        compute_diff(&grid, &diff);
        apply_diff(&grid, &diff, args.delta_time);
        display(&grid);
    }
}
