#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL_Handler.h"

namespace sprite {
	inline vi32_t default_dim{ 16,16 };
}
struct Texture {
	Texture() = default;
	~Texture();

	SDL_Texture* object{ nullptr };

};

struct Sprite {
	Sprite();
	Sprite(int, int);
	Sprite(vi32_t v) : Sprite(v.x, v.y) {}

	SDL::Rect object{};

};

#endif