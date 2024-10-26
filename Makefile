# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAMEC = shell-chess

NAMEV = shell-chess-visual

SRCSBASE = srcs/shell/print.cpp \
	srcs/shell/algebraParser/algebraBase.cpp \
	srcs/shell/algebraParser/algebraChecker.cpp \
	srcs/shell/algebraParser/algebraParser.cpp \
	srcs/shell/algebraParser/algebraTools.cpp \
	srcs/shell/chessBoard/boardHeart.cpp \
	srcs/shell/chessBoard/boardCounter.cpp \
	srcs/shell/chessBoard/boardPrint.cpp \
	srcs/shell/chessBoard/boardTools.cpp \
	srcs/shell/chessBoard/boardInit.cpp \
	srcs/shell/chessBoard/boardFree.cpp \
	srcs/shell/chessBoard/checkers/boardEndChecker.cpp \
	srcs/shell/chessBoard/checkers/boardMoveChecker.cpp \
	srcs/shell/chessBoard/checkers/boardPieceChecker.cpp \

SRCSC = srcs/shell/shell.cpp \
	$(SRCSBASE) \

SRCSV = srcs/visual/visual.cpp \
	srcs/visual/visualGame/visualDisplay.cpp \
	srcs/visual/visualGame/visualFree.cpp \
	srcs/visual/visualGame/visualInit.cpp \
	srcs/visual/visualGame/visualTextures.cpp \
	srcs/visual/visualGame/visualEvent.cpp \
	srcs/visual/visualGame/visualTools.cpp \
	$(SRCSBASE) \

CXX = c++

CXXFLAGS = #-Wall -Wextra -Werror

SDLFLAGS = -lSDL2

OBJSC = $(SRCSC:.cpp=.o)

OBJSV = $(SRCSV:.cpp=.o)

## === RULES === ##

all: $(NAMEC)

$(NAMEC): $(OBJSC)
	$(CXX) $(CXXFLAGS) $(OBJSC) -o $(NAMEC)

visual: $(NAMEV)

$(NAMEV): $(OBJSV)
	$(CXX) $(CXXFLAGS) $(OBJSV) -o $(NAMEV) $(SDLFLAGS)

re: fclean all

clean:
	@rm -rf $(OBJSC) $(OBJSV)

fclean: clean
	@rm -rf $(NAMEC) $(NAMEV)