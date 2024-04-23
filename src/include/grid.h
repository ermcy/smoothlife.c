#ifndef SMOOTHLIFE_C_GRID_H
#define SMOOTHLIFE_C_GRID_H

#include <math.h>
#include <string.h>

typedef struct {
    size_t width;
    size_t height;
    float **data;
} Grid;

static const int ra = 11;
static const float alpha_n = 0.028f;
static const float alpha_m = 0.147f;
static const float b1 = 0.278f;
static const float b2 = 0.365f;
static const float d1 = 0.267f;
static const float d2 = 0.445f;

static const char level[] = " .-=coaA@#";
#define level_count (sizeof(level)/sizeof(level[0]) - 1)

static int e_mod(int a, int b);

static float sigma(float x, float a, float alpha);

static float sigma_n(float x, float a, float b);

static float sigma_m(float x, float y, float m);

static float s(float n, float m);

static void clamp(float *x, float l, float h);

void empty(Grid *self, size_t width, size_t height, uint8_t shrink_factor);

void init(Grid *self, size_t width, size_t height, uint8_t shrink_factor);

void display(Grid *self);

void compute_diff(Grid *self, Grid *diff);

void apply_diff(Grid *self, Grid *diff, float delta_time);

#endif //SMOOTHLIFE_C_GRID_H
