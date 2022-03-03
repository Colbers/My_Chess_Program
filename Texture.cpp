#include "Texture.h"

Texture::~Texture() {
	if (object) {
		SDL_DestroyTexture(object);
		object = nullptr;
	}
}





