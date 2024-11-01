#ifndef SHELLGAME_HPP
# define SHELLGAME_HPP

# include "../../include/chessGame.hpp"
# include "../chessBoard/chessBoard.hpp"
# include "../aiChess/aiChess.hpp"
# include "../algebraParser/algebraParser.hpp"

class shellGame
{
	public:

		shellGame(const bool blindMode, const bool sandBoxMode);
		~shellGame(void);

		bool	fail(void) const
		{
			if (_systemFail == true || _memoryFail == true)
				return (true);
			return (false);
		}

		void	shellRoutine(void);
		string  getShellAnswer(void) const;

	private:

		chessBoard		*_board;
		algebraParser	*_checker;

		const bool		_sandBoxMode;
		const bool		_blindMode;

		int				_aiSide;

		bool			_systemFail;
		bool			_memoryFail;

};

#endif