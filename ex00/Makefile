SRCS		= main.cpp BitcoinExchange.cpp
INCS		= BitcoinExchange.hpp
OBJS		= ${SRCS:.cpp=.o}
NAME		= btc
CXX			= c++
CXXFLAGS		= -Wall -Wextra -Werror -std=c++98

$(NAME):	${OBJS} ${INCS}
			${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all