#include "Renderer.h"

window_spec::window_spec() :
	window_spec("Window")
{}

window_spec::window_spec(const char* title) {
	object = SDL_CreateWindow(
		title,
		pos.x,
		pos.y,
		size.x,
		size.y,
		SDL_WINDOW_VULKAN
	);
}

Renderer::Renderer(window_spec const& window) {
	self = SDL_CreateRenderer(window.object, -1, 0);
}


void Renderer::draw_buffer() {
	for (auto& scheme : sprite_buffer) {
		copy(scheme);
	}
}

bool Renderer::load_texture(const char* path) {

	SDL_Surface* temp_surface{ SDL_LoadBMP(path) };

	texture->object = SDL_CreateTextureFromSurface(self, temp_surface);

	return texture;
}

void Renderer::clear() {
	SDL_RenderClear(self);
	buffer_clear();
}

void Renderer::copy(sprite_plan& scheme) {
	SDL_RenderCopy(self, texture->object, &scheme.sprite, &scheme.locale);
}

void Renderer::present() {
	SDL_RenderPresent(self);
}




