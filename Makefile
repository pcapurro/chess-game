# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = shell-chess

SRCS = srcs/main.cpp \
	srcs/welcome.cpp \
	srcs/loading.cpp \
	srcs/game/chessBoard.cpp \
	srcs/game/algebraicChecker.cpp \

CXX = c++

CXXFLAGS = #-Wall -Wextra -Werror

OBJS = $(SRCS:.cpp=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)