#ifndef SMOOTHLIFE_C_ARGS_H
#define SMOOTHLIFE_C_ARGS_H


#include <stdlib.h>
#include <getopt.h>


#define PROGRAM_NAME "smoothlife"
#define VERSION "0.1.0"
#define AUTHOR "ermcy @ https://github.com/ermcy"
#define GIT_REPO "https://github.com/ermcy/smoothlife.c"

static struct option long_options[] = {
        {"width",         optional_argument, 0, 'w'},
        {"height",        optional_argument, 0, 'h'},
        {"shrink-factor", optional_argument, 0, 'f'},
        {"delta-time",    optional_argument, 0, 't'},
        {"version",       no_argument,       0, 'v'},
        {0,               0,                 0, 0}
};

struct arguments {
    size_t width; /* The width of the simulation, default is 100 */
    size_t height; /* The height of the simulation, default is 100 */
    size_t shrink_factor;  /* The shrink factor of the grid, this will make the grid smaller by a factor of the given number, default is 1 */
    float delta_time; /* The time step for the simulation, default is 0.05 */
};

void init_default(struct arguments *self);

void usage(struct arguments *self);

void version(struct arguments *self);

#endif //SMOOTHLIFE_C_ARGS_H
