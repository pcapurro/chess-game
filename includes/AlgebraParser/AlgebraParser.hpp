#ifndef ALGEBRAPARSER_HPP
# define ALGEBRAPARSER_HPP

# include "Game.hpp"

struct Move
{
	std::string	move;
	char		action;
	
	char		obj;
	std::string	src;
	std::string	dest;
};

class AlgebraParser
{
	public:

		AlgebraParser(void)
			{ _turn = 0, _fail = false; };
		~AlgebraParser(void) = default;

		void		operator=(const std::string move);
		bool		fail(void) const;

		void		setTurn(const int turn)
			{ _turn = turn; };
		Move		getParsedMove(void) const
			{ return (_move); };

		static bool	isChessDigit(const char c);
		static bool	isChessPiece(const char c);
		static bool	isChessCoord(const char c);

	private:

		bool		isValid(void);
		
		bool		isGoodLength(void) const;
		bool		isValidComplexSequence(void) const;
		bool		isValidSimpleSequence(void) const;
		bool		isValidSequence(void) const;
		bool		isValidChar(void) const;

		std::string	getLeftSequence(void) const;
		std::string	getRightSequence(void) const;

		void		parseUniqueSequence(void);
		void		parseDoubleSequence(void);
		void		parseMove(void);

		bool		_fail;

		int			_turn;
		Move		_move;
};

std::vector<std::string>	getWatchersSequence(const char type, const std::string& move, const char sign);
std::vector<std::string>	getPawnSequence(const std::string& move, const int turn, const char sign);

#endif