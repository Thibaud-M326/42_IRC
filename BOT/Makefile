CPP = c++
CPPFLAGS = -g3 -Wall -Wextra -Werror -MMD -MP -std=c++98
NAME = feurbot

OBJ_DIR = ./.obj
SRC_DIR = ./sources
INC_DIR = ./includes
FEURBOT_DIR = $(SRC_DIR)/feurbot
SIGNAL_DIR = $(SRC_DIR)/signal

SRC =										\
	$(SRC_DIR)/main.cpp						\
	$(FEURBOT_DIR)/connectToChannels.cpp	\
	$(FEURBOT_DIR)/connectToServer.cpp		\
	$(FEURBOT_DIR)/FeurBot.cpp				\
	$(FEURBOT_DIR)/sayFeur.cpp				\
	$(SIGNAL_DIR)/SignalHandler.cpp			\
	$(SRC_DIR)/Parse.cpp					\

INC_DIRS = 			\
	-I$(INC_DIR)/	\

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
