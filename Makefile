# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = shell-chess

SRCS = srcs/shell/shell.cpp \
	srcs/shell/print.cpp \
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

CXX = c++

CXXFLAGS = #-Wall -Wextra -Werror

SDLFLAGS = -lSDL2

OBJS = $(SRCS:.cpp=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(SDLFLAGS)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)