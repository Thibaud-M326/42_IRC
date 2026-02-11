CPP = c++
# CPPFLAGS = -g3 -Wall -Wextra -Werror -MMD -MP -std=c++98
CPPFLAGS = -g3 -Wall -Wextra -MMD -MP -std=c++98
NAME = ircserv 

OBJ_DIR = ./.obj
SRC_DIR = ./sources
INC_DIR = ./includes

SERVER_DIR = server
CLIENT_DIR = client 
SRC =											\
		$(SRC_DIR)/main.cpp						\
		$(SRC_DIR)/$(SERVER_DIR)/Server.cpp		\
# 		$(SRC_DIR)/$(CLIENT_DIR)/Client.cpp		\

INC_DIRS = 										\
		-I$(INC_DIR)/server/ 					\
# 		-I$(INC_DIR)/client/					\

OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.d)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp Makefile
		mkdir -p $(dir $@)
		$(CPP) $(INC_DIRS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJ)
		$(CPP) $(OBJ) -o $(NAME)

-include $(DEP)

clean:
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -f $(NAME)

re:     fclean all

.PHONY: all clean fclean re
