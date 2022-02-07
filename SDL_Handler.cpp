#include "SDL_Handler.h"

SDL_Handler::SDL_Handler() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL failed to initialize. SDL_Error: " << SDL_GetError() << '\n';
	}
	else {
		h_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (!h_window) {
			std::cout << "SDL Window Fail. SDL_Error: " << SDL_GetError() << '\n';
		}
	}
}

bool init() {
	return true;
}

void cleanUp() {

}

SDL_Handler::~SDL_Handler() {}