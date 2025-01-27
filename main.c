#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "complex.h"

#define MAX 255
#define GRIDSIZE 512

struct RGB
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

int iterate(struct Complex z0)
{
    struct Complex z1 = z0;
    for (int i = 0; i < MAX; i++)
    {
        if (square(z1) > 4.0)
        {
            return i;
        }
        z1 = multiply(z1, z1);
        z1 = add(z1, z0);
    }
    return MAX;
}

void set_color(const char *file, struct RGB *arr)
{
    FILE *fptr;
    char path[100];
    sprintf(path, "colorthemes/%s.mnd", file);

    fptr = fopen(path, "r");

    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < MAX; i++)
    {
        fscanf(fptr, "%hhu %hhu %hhu", &arr[i].r, &arr[i].g, &arr[i].b);
    }

    fclose(fptr);
}

void fill_rect(SDL_Renderer *renderer, struct RGB color, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderPoint(renderer, x, y);
}

void draw(SDL_Renderer *renderer, struct RGB *colArr, struct Complex centrum, double s)
{
#pragma omp parallel for collapse(2)
    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            struct Complex z;
            z.re = centrum.re - s / 2 + (s * i) / (GRIDSIZE - 1);
            z.im = centrum.im - s / 2 + (s * j) / (GRIDSIZE - 1);
            struct RGB color = colArr[iterate(z)];
#pragma omp critical
            fill_rect(renderer, color, i, j);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: %s <double1> <double2> <double3> <string>\n", argv[0]);
        return 1;
    }

    char *endptr;
    double re = strtod(argv[1], &endptr);
    double im = strtod(argv[2], &endptr);
    double s = strtod(argv[3], &endptr);
    const char *file = argv[4];

    struct RGB *colArr = malloc((MAX) * sizeof(struct RGB));

    struct Complex centrum;
    centrum.re = re;
    centrum.im = im;
    set_color(file, colArr);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("MANDELBROT", GRIDSIZE, GRIDSIZE, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, NULL);

    draw(renderer, colArr, centrum, s);
    SDL_RenderPresent(renderer);

    int running = 1;

    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = 0;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                double x = centrum.re - s / 2 + (s * event.button.x) / GRIDSIZE;
                double y = centrum.im - s / 2 + (s * event.button.y) / GRIDSIZE;
                centrum.re = x;
                centrum.im = y;
                s *= 0.8;
                draw(renderer, colArr, centrum, s);
                SDL_RenderPresent(renderer);
            }
        }
    }

    free(colArr);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
