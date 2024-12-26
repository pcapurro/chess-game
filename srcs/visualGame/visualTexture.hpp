#ifndef VISUALTEXTURE_HPP
# define VISUALTEXTURE_HPP

# include "../../includes/visual.hpp"

class visualTexture
{
	public:

		visualTexture();
		~visualTexture();

		int			load(SDL_Renderer *renderer, const char *path);

		SDL_Texture	*getTexture(void) const { return (_texture); };

	private:
		SDL_Texture	*_texture;
};

#endif