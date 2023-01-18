# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 15:33:50 by vfiszbin          #+#    #+#              #
#    Updated: 2023/01/18 09:22:43 by vfiszbin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g

NAME1 = exec_with_std
NAME2 = exec_with_ft

NAME3 = bench_with_std
NAME4 = bench_with_ft

SOURCE1 = main.cpp
SOURCE2 = main2.cpp

INCLUDES = map.hpp vector.hpp stack.hpp iterator.hpp utils.hpp avl_tree.hpp

all : $(NAME1) $(NAME2) $(NAME3) $(NAME4)

$(NAME1) : $(SOURCE1)
	$(CXX) $(CXXFLAGS) -DNAMESPACE=1 -o $(NAME1) $(SOURCE1)

$(NAME2) : $(SOURCE1) $(INCLUDES)
	$(CXX) $(CXXFLAGS) -DNAMESPACE=0 -o $(NAME2) $(SOURCE1)

$(NAME3) : $(SOURCE2) $(INCLUDES)
	$(CXX) $(CXXFLAGS) -DNAMESPACE=1 -o $(NAME3) $(SOURCE2)

$(NAME4) : $(SOURCE2) $(INCLUDES)
	$(CXX) $(CXXFLAGS) -DNAMESPACE=0 -o $(NAME4) $(SOURCE2)

clean :
	

fclean : clean
	$(RM) $(NAME1)
	$(RM) $(NAME2)
	$(RM) $(NAME3)
	$(RM) $(NAME4)

re : fclean all

.PHONY : all clean fclean re