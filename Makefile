# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAMEV = chess-game

NAMES = shell-chess

SRCSO = srcs/failPrint.cpp \
	srcs/algebraParser/algebraBase.cpp \
	srcs/algebraParser/algebraChecker.cpp \
	srcs/algebraParser/algebraParser.cpp \
	srcs/algebraParser/algebraTools.cpp \
	srcs/chessAi/chessAi.cpp \
	srcs/chessBoard/boardHeart.cpp \
	srcs/chessBoard/boardEvaluate.cpp \
	srcs/chessBoard/tools/boardCounter.cpp \
	srcs/chessBoard/tools/boardPrint.cpp \
	srcs/chessBoard/tools/boardTesters.cpp \
	srcs/chessBoard/tools/boardTools.cpp \
	srcs/chessBoard/boardInit.cpp \
	srcs/chessBoard/boardFree.cpp \
	srcs/chessBoard/checkers/boardEndCheckers.cpp \
	srcs/chessBoard/checkers/boardEvaluateCheckers.cpp \
	srcs/chessBoard/checkers/boardMoveCheckers.cpp \
	srcs/chessBoard/checkers/boardPieceCheckers.cpp \

SRCS_V = srcs/visualGame.cpp \
	srcs/visualGame/visualDisplay.cpp \
	srcs/visualGame/visualRoutine.cpp \
	srcs/visualGame/visualFree.cpp \
	srcs/visualGame/visualInit.cpp \
	srcs/visualGame/visualRessources.cpp \
	srcs/visualGame/visualTexture.cpp \
	srcs/visualGame/visualEvent.cpp \
	srcs/visualGame/visualTools.cpp \
	$(SRCSO)

SRCS_S = srcs/shellGame.cpp \
	srcs/shellGame/shellInit.cpp \
	srcs/shellGame/shellRoutine.cpp \
	srcs/shellGame/shellFree.cpp \
	$(SRCSO)

CXX = c++

CXXFLAGS = # -Wall -Wextra -Werror

SDLFLAG = -lSDL2

OBJSV = $(SRCS_V:.cpp=.o)

OBJSS = $(SRCS_S:.cpp=.o)

## === RULES === ##

visual: $(NAMEV)

shell: $(NAMES)

all: $(NAMEV) $(NAMES)

$(NAMEV): $(OBJSV)
	$(CXX) $(CXXFLAGS) $(OBJSV) -o $(NAMEV) $(SDLFLAG)

$(NAMES): $(OBJSS)
	$(CXX) $(CXXFLAGS) $(OBJSS) -o $(NAMES)

clean:
	@rm -rf $(OBJSS) $(OBJSV)

fclean: clean
	@rm -rf $(NAMEV) $(NAMES)