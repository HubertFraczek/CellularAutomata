#include <iostream>
#include <SDL.h>
#include "Renderer.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#define fps 60
#define screen_width 1600
#define screen_height 900
void DrawRect(Renderer &renderer, int x, int  y, int w) {
	SDL_Rect temp = { x, y, w, w };
	SDL_RenderFillRect(renderer.get_renderer(), &temp);
}
/*
void SetGliderGun(int *tab[][160], int mx, int my) {
	tab[my / 10][mx / 10] = 1;
	tab[my / 10 + 1][mx / 10] = 1;
	tab[my / 10][mx / 10 + 1] = 1;
	tab[my / 10 + 1][mx / 10 + 1] = 1;
	tab[my / 10][mx / 10 + 10] = 1;
	tab[my / 10 + 1][mx / 10 + 10] = 1;
	tab[my / 10 + 2][mx / 10 + 10] = 1;
	tab[my / 10 - 1][mx / 10 + 11] = 1;
	tab[my / 10 + 3][mx / 10 + 11] = 1;
	tab[my / 10 - 2][mx / 10 + 12] = 1;
	tab[my / 10 - 2][mx / 10 + 13] = 1;
	tab[my / 10 + 4][mx / 10 + 12] = 1;
	tab[my / 10 + 4][mx / 10 + 13] = 1;
	tab[my / 10 + 1][mx / 10 + 14] = 1;

}*/
int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	atexit(SDL_Quit);
	Renderer renderer(screen_width, screen_height);
	Uint32 starting_tick;
	SDL_Event event;
	bool running = true, start = false, random = false, left_mouse_down = false, right_mouse_down = false, glider = false;
	srand(time(NULL));
	int r;
	int tab[90][160];
	int tab2[90][160];

	int mouse_x, mouse_y;
	while (running) {
		starting_tick = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_SPACE) {
					if (start) start = false;
					else start = true;
				}
				if (event.key.keysym.sym == SDLK_r) {
					random = true;
				}
				if (event.key.keysym.sym == SDLK_c) {
					for (int i = 0; i < 90; i++) {
						for (int j = 0; j < 160; j++) {
							tab[i][j] = 0;
						}
					}
				}
			}

			//INBAAAAA

			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					left_mouse_down = true;
					right_mouse_down = false;
				}
				else if (event.button.button == SDL_BUTTON_RIGHT) {
					right_mouse_down = true;
					left_mouse_down = false;
				}
				else if (event.button.button == SDL_BUTTON_MIDDLE) {
					glider = true;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP) {
				left_mouse_down = false;
				right_mouse_down = false;
				glider = false;
			}
		}
		SDL_GetMouseState(&mouse_x, &mouse_y);
		if (left_mouse_down) {
			tab[mouse_y / 10][mouse_x / 10] = 1;
		}
		if (right_mouse_down) {
			tab[mouse_y / 10][mouse_x / 10] = 0;
		}

		if (glider) {
			//SetGliderGun(tab, mouse_x, mouse_y);
		}
		//INBAAAAA



		if (random) {
			for (int i = 0; i < 90; i++) {
				for (int j = 0; j < 160; j++) {
					r = rand() % 4;
					if (r == 1) tab[i][j] = 1;
					else tab[i][j] = 0;
				}
			}
			random = false;
		}
		if (start) {
			for (int i = 0; i < 90; i++) {
				for (int j = 0; j < 160; j++) {
					int how_many_somsiads = 0;
					if (j < 160 && tab[i][j + 1] == 1) how_many_somsiads++;
					if (i < 90 && tab[i + 1][j] == 1) how_many_somsiads++;
					if (j < 160 && i < 90 && tab[i + 1][j + 1]) how_many_somsiads++;
					if (i > 0 && j > 0 && tab[i - 1][j - 1]) how_many_somsiads++;
					if (i > 0 && tab[i - 1][j]) how_many_somsiads++;
					if (j > 0 && tab[i][j - 1]) how_many_somsiads++;
					if (i < 90 && j > 0 && tab[i + 1][j - 1]) how_many_somsiads++;
					if (i > 0 && j < 160 && tab[i - 1][j + 1]) how_many_somsiads++;
					tab2[i][j] = how_many_somsiads;
				}
			}
			SDL_SetRenderDrawColor(renderer.get_renderer(), 255, 255, 255, 255);
			for (int i = 0; i < 90; i++) {
				for (int j = 0; j < 160; j++) {
					if ((tab2[i][j] == 2 && tab[i][j] == 1) || (tab2[i][j] == 3)) tab[i][j] = 1;
					else tab[i][j] = 0;
					if (tab[i][j] == 1) DrawRect(renderer, j * 10, i * 10, 10);
				}
			}
		}
		else {
			SDL_SetRenderDrawColor(renderer.get_renderer(), 255, 255, 255, 255);
			for (int i = 0; i < 90; i++) {
				for (int j = 0; j < 160; j++) {
					if (tab[i][j] == 1) DrawRect(renderer, j * 10, i * 10, 10);
				}
			}
		}
		SDL_SetRenderDrawColor(renderer.get_renderer(), 0, 0, 0, 255);
		for (int i = 10; i < screen_width; i += 10) {
			SDL_RenderDrawLine(renderer.get_renderer(), i, 0, i, screen_height);
		}
		for (int i = 10; i < screen_height; i += 10) {
			SDL_RenderDrawLine(renderer.get_renderer(), 0, i, screen_width, i);
		}
		renderer.update_screen();
		if ((1000 / fps) > SDL_GetTicks() - starting_tick) {
			SDL_Delay(1000 / fps - (SDL_GetTicks() - starting_tick));
		}
	}
	return 0;
}