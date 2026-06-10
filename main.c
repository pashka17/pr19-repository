#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Практична- 19",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* playerTexture = IMG_LoadTexture(renderer, "assets/player.bmp");

    if (!playerTexture) {
        printf("Image error: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Rect player = {100, 100, 64, 64};
    int speed = 5;

    SDL_Rect npc1 = {300, 120, 50, 50};
    SDL_Rect npc2 = {500, 300, 50, 50};
    SDL_Rect npc3 = {200, 420, 50, 50};

    int dx1 = 3;
    int dx2 = -4;
    int dy3 = 3;

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_UP:
                        player.y -= speed;
                        break;
                    case SDLK_DOWN:
                        player.y += speed;
                        break;
                    case SDLK_LEFT:
                        player.x -= speed;
                        break;
                    case SDLK_RIGHT:
                        player.x += speed;
                        break;
                }
            }
        }

        npc1.x += dx1;
        npc2.x += dx2;
        npc3.y += dy3;

        if (npc1.x < 0 || npc1.x > 750) dx1 = -dx1;
        if (npc2.x < 0 || npc2.x > 750) dx2 = -dx2;
        if (npc3.y < 0 || npc3.y > 550) dy3 = -dy3;

        int red = player.x / 4;
        int green = player.y / 3;
        int blue = 100;

        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, playerTexture, NULL, &player);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &npc1);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &npc2);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &npc3);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(playerTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}