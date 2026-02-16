CPP = c++
CPPFLAGS = -g3 -Wall -Wextra -Werror -MMD -MP -std=c++98
NAME = ircserv 

OBJ_DIR = ./.obj
SRC_DIR = ./sources
INC_DIR = ./includes

CLIENT_DIR = client
EXCEPT_DIR = exception
PARSE_DIR = parse
SERVER_DIR = server
COMMAND_DIR = command
RESPONSE_DIR = response
CHANNEL_DIR = channel

SRC =														\
		$(SRC_DIR)/main.cpp									\
		$(SRC_DIR)/$(CLIENT_DIR)/Client.cpp					\
		$(SRC_DIR)/$(EXCEPT_DIR)/Exception.cpp				\
		$(SRC_DIR)/$(PARSE_DIR)/Parse.cpp					\
		$(SRC_DIR)/$(SERVER_DIR)/acceptConnection.cpp		\
		$(SRC_DIR)/$(SERVER_DIR)/initServer.cpp				\
		$(SRC_DIR)/$(SERVER_DIR)/processClient.cpp			\
		$(SRC_DIR)/$(SERVER_DIR)/readClient.cpp				\
		$(SRC_DIR)/$(SERVER_DIR)/run.cpp					\
		$(SRC_DIR)/$(SERVER_DIR)/Server.cpp					\
		$(SRC_DIR)/$(SERVER_DIR)/serverUtils.cpp			\
		$(SRC_DIR)/$(COMMAND_DIR)/JoinCommand.cpp			\
		$(SRC_DIR)/$(COMMAND_DIR)/NickCommand.cpp			\
		$(SRC_DIR)/$(COMMAND_DIR)/PassCommand.cpp			\
		$(SRC_DIR)/$(COMMAND_DIR)/PrivMsgCommand.cpp		\
		$(SRC_DIR)/$(COMMAND_DIR)/UserCommand.cpp			\
		$(SRC_DIR)/$(COMMAND_DIR)/ACommand.cpp				\
		$(SRC_DIR)/$(COMMAND_DIR)/CommandFactory.cpp		\
		$(SRC_DIR)/$(CHANNEL_DIR)/Channel.cpp				\

INC_DIRS = 								\
		-I$(INC_DIR)/					\
		-I$(INC_DIR)/$(CLIENT_DIR)/		\
		-I$(INC_DIR)/$(EXCEPT_DIR)/		\
		-I$(INC_DIR)/$(PARSE_DIR)/		\
		-I$(INC_DIR)/$(SERVER_DIR)/ 	\
		-I$(INC_DIR)/$(COMMAND_DIR)/ 	\
		-I$(INC_DIR)/$(RESPONSE_DIR)/ 	\
		-I$(INC_DIR)/$(CHANNEL_DIR)/ 	\

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
