#ifndef SDL_HANDLER_H
#define SDL_HANDLER_H

#include "includes.h"
#include <SDL.h>

const int SCREEN_WIDTH{ 640 };
const int SCREEN_HEIGHT{ 480 };

class SDL_Handler {
public:
	SDL_Handler();

	SDL_Window* h_window{nullptr};

	SDL_Surface* h_windowSurface{ nullptr };

	bool init();

	void cleanUp();

	~SDL_Handler();

	void draw_Rectangle(SDL_Rect source, SDL_Rect drawTo, SDL_Texture* tex);

	SDL_Texture* load_Image(char const* filename);
};

#endif
