#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../include/grid.h"

static float random_float(void) {
    return (float) rand() / (float) RAND_MAX;
}

void empty(Grid *self, size_t width, size_t height, uint8_t shrink_factor) {
    self->height = height;
    self->width = width;
    self->data = malloc(height * sizeof(float *));
    if (self->data == NULL) {
        fprintf(stderr, "Couldn't allocate memory for the grid.");
        exit(EXIT_FAILURE);
    }
    for (size_t y = 0; y < height; ++y) {
        self->data[y] = malloc(width * sizeof(float));
        if (self->data[y] == NULL) {
            fprintf(stderr, "Couldn't allocate memory for the grid (x2).");
            exit(EXIT_FAILURE);
        }
    }
    for (size_t y = 0; y < self->height / shrink_factor; ++y) {
        for (size_t x = 0; x < self->width / shrink_factor; ++x) {
            self->data[y][x] = 0;
        }
    }

}

void init(Grid *self, size_t width, size_t height, uint8_t shrink_factor) {
    empty(self, width, height, shrink_factor);
    for (size_t y = 0; y < self->height; ++y) {
        for (size_t x = 0; x < self->width; ++x) {
            self->data[y][x] = random_float();
        }
    }
}

void display(Grid *self) {
    for (size_t y = 0; y < self->height; ++y) {
        for (size_t x = 0; x < self->width; ++x) {
            float value = self->data[y][x];
            char c = level[(int) (value * (level_count - 1))];
            fputc(c, stdout);
            fputc(c, stdout);
        }
        fputc('\n', stdout);
    }
}

void compute_diff(Grid *self, Grid *diff) {
    for (int cy = 0; cy < self->height; ++cy) {
        for (int cx = 0; cx < self->width; ++cx) {
            float m = 0, M = 0;
            float n = 0, N = 0;
            int ri = ra / 3;
            for (int dy = -(ra - 1); dy <= (ra - 1); ++dy) {
                for (int dx = -(ra - 1); dx <= (ra - 1); ++dx) {
                    int x = e_mod(cx + dx, self->width);
                    int y = e_mod(cy + dy, self->height);
                    if (dx * dx + dy * dy <= ri * ri) {
                        m += self->data[y][x];
                        M += 1;
                    } else if (dx * dx + dy * dy <= ra * ra) {
                        n += self->data[y][x];
                        N += 1;
                    }
                }
            }
            m /= M;
            n /= N;
            float q = s(n, m);
            diff->data[cy][cx] = 2 * q - 1;
        }
    }
}

int e_mod(int a, int b) {
    return (a % b + b) % b;
}

float sigma(float x, float a, float alpha) {
    return 1.0f / (1.0f + expf(-(x - a) * 4 / alpha));
}

float sigma_n(float x, float a, float b) {
    return sigma(x, a, alpha_n) * (1 - sigma(x, b, alpha_n));
}

float sigma_m(float x, float y, float m) {
    return x * (1 - sigma(m, 0.5f, alpha_m)) + y * sigma(m, 0.5f, alpha_m);
}

float s(float n, float m) {
    return sigma_n(n, sigma_m(b1, d1, m), sigma_m(b2, d2, m));
}

void clamp(float *x, float l, float h) {
    if (*x < l) *x = l;
    if (*x > h) *x = h;
}

void apply_diff(Grid *self, Grid *diff, float delta_time) {
    for (size_t y = 0; y < self->height; ++y) {
        for (size_t x = 0; x < self->width; ++x) {
            self->data[y][x] += delta_time * diff->data[y][x];
            clamp(&self->data[y][x], 0, 1);
        }
    }
}
