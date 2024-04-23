#include <stdio.h>
#include "../include/args.h"

void init_default(struct arguments *self) {
    self->width = 100;
    self->height = 100;
    self->delta_time = 0.05f;
    self->shrink_factor = 1;
}

void usage(struct arguments *_) {
    printf("Usage: %s [OPTIONS]...\n", PROGRAM_NAME);
    fputs("\n"
          "-w, --width=WIDTH            Adjust the width of the simulation, default is 100\n"
          "-h, --height=HEIGHT          Adjust the height of the simulation, default is 100\n"
          "-t, --delta-time=TIME        Adjust the time step for the simulation, default is 0.05\n"
          "-f, --shrink-factor=FACTOR   Adjust the shrink factor of the grid, this will make the grid smaller by a factor of the given number, default is 1\n"
          "-h, --help                   Display this help and exit\n"
          "-v, --version                Display version information and exit\n", stdout);
    exit(EXIT_SUCCESS);
}

void version(struct arguments *_) {
    printf("%s %s\n", PROGRAM_NAME, VERSION);
    printf("Written by %s\n", AUTHOR);
    printf("Github repository %s\n", GIT_REPO);
    exit(EXIT_FAILURE);
}
