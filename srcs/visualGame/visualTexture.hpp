#ifndef VISUALTEXTURE_HPP
# define VISUALTEXTURE_HPP

# include "../../includes/visual.hpp"

class visualTexture
{
	public:

		visualTexture();
		~visualTexture();

		void		*load(SDL_Renderer *renderer, SDL_Surface *surface, \
							int &baseCheck, const char *path);

		SDL_Texture	*getTexture(void) const { return (_texture); };

	private:
		SDL_Texture	*_texture;
};

#endif