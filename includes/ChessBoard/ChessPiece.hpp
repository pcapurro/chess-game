#ifndef CHESSPIECE_HPP
# define CHESSPIECE_HPP

# include "Game.hpp"

class ChessPiece
{
	public:
		
		ChessPiece(const std::string& color, const std::string& pos)
		{
			_color = color;
			_moves = 0;

			_originalPos = pos;
			_pos = pos;

			_x = pos[0] - 97;
			_y = atoi(pos.c_str() + 1);

			_visible = true;
		}

		virtual ~ChessPiece() {};

		bool	isVisible(void) const
			{ return (_visible); }
		void	setVisibility(void)
			{ _visible == true ? _visible = false : _visible = true; }

		std::string	getColor() const
			{ return (_color); }
		char	getType() const
			{ return (_type); }
		
		int		getMoves(void)
			{ return (_moves); }

		std::string	getCoord(void) const
			{ return (_pos); }
		std::string	getOriginalCoord(void) const
			{ return (_originalPos); }

		int		getX(void) const
			{ return (_x); }
		int		getY(void) const
			{ return (_y); }

		void	move(void)
			{ _moves++; };

		void	updatePos(const std::string& coord)
		{
			_pos = coord;
			_x = coord[0] - 97;
			_y = atoi(coord.c_str() + 1);
		}

		virtual bool	isOnMyWay(const std::string& target, const std::vector<std::string>& boardCoords = {}, \
			const int value = 0, const std::string& enPassant = "") const = 0;

	protected:

		std::string	_color;
		char		_type;

		int			_moves;

		std::string	_originalPos;
		std::string	_pos;

		int			_x;
		int			_y;

		bool		_visible;

};

#endif