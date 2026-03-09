BOLD_GREEN			=	\e[1;32m
BOLD_RED			=	\e[1;31m
BOLD_BLUE			=	\e[1;34m
BOLD_YELLOW			=	\e[1;33m
BOLD_PURPLE			=	\e[1;35m
BOLD_CYAN			=	\e[1;36m
STOP_COLOR			=	\e[0m

CXX = c++
CXXFLAGS = -g3 -Wall -Wextra -Werror -MMD -MP -std=c++98 $(REPLY)
NAME = feurbot

REPLY = -DREPLY=0
OBJ_DIR = ./.obj
SRC_DIR = ./sources
INC_DIR = ./includes
FEURBOT_DIR = $(SRC_DIR)/feurbot
SIGNAL_DIR = $(SRC_DIR)/signal
PARSE_DIR = $(SRC_DIR)/parse

SRC =								\
	$(SRC_DIR)/main.cpp				\
	$(FEURBOT_DIR)/FeurBot.cpp		\
	$(SIGNAL_DIR)/SignalHandler.cpp	\
	$(PARSE_DIR)/Parse.cpp			\

INC_DIRS =			\
	-I$(INC_DIR)/	\

OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.d)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "$(BOLD_YELLOW)Compilling $@ $(BOLD_PURPLE)"
	@$(CXX) $(INC_DIRS) $(CXXFLAGS) -c $< -o $@
	@echo -n "$(STOP_COLOR)"

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BOLD_BLUE)Creating executable $(NAME)...$(BOLD_PURPLE)"
	@$(CXX) $(OBJ) -o $(NAME)
	@echo "$(STOP_COLOR)$(BOLD_GREEN)SUCCESS !!!$(STOP_COLOR)"

quoi: fclean
	@$(MAKE) --no-print-directory REPLY=-DREPLY=1

clean:
	@echo "$(BOLD_BLUE)Delete obj...$(STOP_COLOR)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BOLD_RED)SUCCESS !!!$(STOP_COLOR)"

fclean: clean
	@echo "$(BOLD_BLUE)Make fclean...$(STOP_COLOR)"
	@rm -f $(NAME)
	@echo "$(BOLD_RED)SUCCESS !!!$(STOP_COLOR)"

re:     fclean all

-include $(DEP)

.PHONY: all clean fclean re
