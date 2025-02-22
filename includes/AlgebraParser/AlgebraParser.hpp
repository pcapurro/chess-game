#ifndef ALGEBRAPARSER_HPP
# define ALGEBRAPARSER_HPP

# include "Game.hpp"

struct Move
{
	string	move;
	char	action;
	
	char	obj;
	string	src;
	string	dest;
};

class AlgebraParser
{
	public:

		AlgebraParser(void)
			{ _turn = 0, _fail = false; };
		~AlgebraParser(void) {};

		void		operator=(const string move);
		bool		fail(void) const;

		void		setTurn(const int turn)
			{ _turn = turn; };
		Move		getParsedMove(void) const
			{ return (_move); };

		static bool	isChessDigit(const char c);
		static bool	isChessPiece(const char c);
		static bool	isChessCoord(const char c);

	private:

		bool	isValid(void);
		
		bool	isGoodLength(void) const;
		bool	isValidComplexSequence(void) const;
		bool	isValidSimpleSequence(void) const;
		bool	isValidSequence(void) const;
		bool	isValidChar(void) const;

		string	getLeftSequence(void) const;
		string	getRightSequence(void) const;

		void	parseUniqueSequence(void);
		void	parseDoubleSequence(void);
		void	parseMove(void);

		bool	_fail;

		int		_turn;
		Move	_move;
};

vector<string>	getWatchersSequence(const char type, const string& move, const char sign);
vector<string>	getPawnSequence(const string& move, const int turn, const char sign);

#endif