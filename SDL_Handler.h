#ifndef SDL_HANDLER
#define SDL_HANDLER

#include <memory>
#include <SDL.h>
#include <SDL_vulkan.h>
#include "vector.h"

using pos2d = vi32_t;
using uint_t = uint32_t;

namespace SDL {
	struct Target {
		Target(SDL_Rect& SDL_R) :
			rect{ SDL_R },
			width{ SDL_R.w },
			height{ SDL_R.h },
			pos_x{ SDL_R.x },
			pos_y{ SDL_R.y },
			position{ pos_x, pos_y },
			dimension{ width, height }
		{}

		SDL_Rect& rect;

		vector2d<int&> position;
		vector2d<int&> dimension;

		int& width;
		int& height;

		int& pos_x;
		int& pos_y;

		void set_dimension(int w, int h) {
			width = w;
			height = h;
		}

		void set_dimension(vi32_t v) { set_dimension(v.x, v.y); }

		void set_position(int x, int y) {
			pos_x = x;
			pos_y = y;
		}

		void set_position(vi32_t v) { set_position(v.x, v.y); }

		void set_index(int x, int y) {
			set_position(width * x, height * y);
		}

		void set_index(vector2d<int> v) {
			set_index(v.x, v.y);
		}

		void set_default() {
			set_position(0,0);
			set_dimension(0,0);
		}

	};

	inline vector2d<int> position_of(SDL_Rect const& rect) {
		return { rect.x, rect.y };
	}
	inline vector2d<int> dimension_of(SDL_Rect const& rect) {
		return { rect.w, rect.h };
	}

	struct Rect : SDL_Rect {

		Rect(int _width=0, int _height=0) :
			pos_x{ x },
			pos_y{ y },
			width{ w },
			height{ h },
			position{ pos_x, pos_y },
			dimension{ width, height }
		{
			x = 0;
			y = 0;
			w = _width;
			h = _height;
		}

		Rect(vector2d<int> const& v) :
			Rect(v.x, v.y)
		{}

		vector2d<int&> position;
		vector2d<int&> dimension;

		int& pos_x;
		int& pos_y;

		int& width;
		int& height;

		void set_position(int _x, int _y) {
			pos_x = _x; pos_y = _y;
		}
		void set_position(vector2d<int> const& v) {
			set_position(v.x, v.y);
		}

		void set_dimension(int w, int h) {
			width = w; height = h;
		}
		void set_dimension(vector2d<int> const& v) {
			set_dimension(v.x, v.y);
		}

		void set_index(int x, int y) {
			set_position(width * x, height * y);
		}
		void set_index(vector2d<int> v) {
			set_index(v.x, v.y);
		}

	};

}

using SDL::Target;

#endif

