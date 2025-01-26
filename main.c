#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("WINDOW", 1000, 1000, 0);
    SDL_Delay(3000);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
