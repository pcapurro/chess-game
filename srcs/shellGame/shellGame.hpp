#ifndef SHELLGAME_HPP
# define SHELLGAME_HPP

# include "../../includes/game.hpp"
# include "../../includes/shell.hpp"
# include "../chessBoard/chessBoard.hpp"
# include "../chessAi/chessAi.hpp"
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
		chessAi         _ai;
		algebraParser	*_checker;

		const bool		_blindMode;
		const bool		_sandBoxMode;

		int				_aiSide;

		bool			_systemFail;
		bool			_memoryFail;

};

#endif