#ifndef VISUALTEXTURE_HPP
# define VISUALTEXTURE_HPP

# include "../../includes/Visual.hpp"

class VisualTexture
{
	public:

		VisualTexture(void);
		~VisualTexture(void);

		int				load(SDL_Renderer* renderer, const char* path, const char id = '0');

		SDL_Texture*	getTexture(void) const
			{ return (_texture); };
		char			getId(void) const
			{ return (_id); };

	private:
		SDL_Texture*	_texture;
		char			_id;
};

#endif