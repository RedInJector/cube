// here we generate a pseudo-random line after each click of the mouse.
// there is also an option to generate triangles

#include <string.h>
#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <time.h>

#include "SDL.h"
#include "Bresenham.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

SDL_Window* window;
SDL_Renderer* renderer;
int mode = 0;

typedef struct {
    int x;
    int y;
} Point2D;

void plotPixel(int x, int y) { SDL_RenderDrawPoint(renderer, x, y); }

void plotLinePoints(Point2D point0, Point2D point1) { 
    std::function<void(int, int)> plot = plotPixel;
    plotLine(plot, point0.x, point0.y, point1.x, point1.y);
}

void start() {
    Point2D p0, p1, p2;
    p0.x = rand() % SCREEN_WIDTH;
    p0.y = rand() % SCREEN_HEIGHT;

    p1.x = rand() % SCREEN_WIDTH;
    p1.y = rand() % SCREEN_HEIGHT;

    p2.x = rand() % SCREEN_WIDTH;
    p2.y = rand() % SCREEN_HEIGHT;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    plotLinePoints(p0, p1);
    if (mode == 1) {
        plotLinePoints(p1, p2);
        plotLinePoints(p0, p2);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    if (argc != 1) {
        if (strcmp(argv[1], "l") == 0) {
            mode = 0;
        }
        if (strcmp(argv[1], "t") == 0) {
            mode = 1;
        }
    }
    printf("mode is: %d", mode);
    // boilerplate
    window = SDL_CreateWindow("Test", 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        printf("Error window creation\n");
        return 3;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    start();
    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e) > 0) {
            if (e.type == SDL_QUIT) {
                break;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                start();
            }
        }
    }

    // more boilerplate
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
