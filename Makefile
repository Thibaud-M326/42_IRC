BOLD_GREEN			=	\e[1;32m
BOLD_RED			=	\e[1;31m
BOLD_BLUE			=	\e[1;34m
BOLD_YELLOW			=	\e[1;33m
BOLD_PURPLE			=	\e[1;35m
BOLD_CYAN			=	\e[1;36m
STOP_COLOR			=	\e[0m

CXX = c++
CXXFLAGS = -g3 -Wall -Wextra -Werror -MD -MP -std=c++98
NAME = ircserv 

OBJ_DIR = .obj
SRC_DIR = sources
INC_DIR = includes

SUBDIR = client \
		 exception \
		 parse \
		 server \
		 command \
		 response \
		 channel \
		 signal

vpath %.cpp $(SRC_DIR)
vpath %.cpp $(addprefix $(SRC_DIR)/, $(SUBDIR))

vpath %.hpp $(INC_DIR)
vpath %.hpp $(addprefix $(INC_DIR)/, $(SUBDIR))

SRCS =	main.cpp \
		acceptConnection.cpp \
		initServer.cpp \
		processClient.cpp \
		readClient.cpp \
		run.cpp \
		Server.cpp \
		serverUtils.cpp \
		shutDown.cpp \
		Client.cpp \
		Channel.cpp \
		Exception.cpp \
		Parse.cpp \
		ACommand.cpp \
		CommandFactory.cpp \
		InviteCommand.cpp \
		JoinCommand.cpp \
		KickCommand.cpp \
		ListCommand.cpp \
		ModeCommand.cpp \
		NickCommand.cpp \
		PassCommand.cpp \
		PartCommand.cpp \
		PrivMsgCommand.cpp \
		QuitCommand.cpp \
		TopicCommand.cpp \
		UserCommand.cpp \
		SignalHandler.cpp \
		verifArgs.cpp

INC_DIRS = -I$(INC_DIR) \
           $(addprefix -I$(INC_DIR)/,$(SUBDIR))

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))
DEPS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.d))

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(BOLD_YELLOW)Compilling $@ $(BOLD_PURPLE)"
	@$(CXX) $(INC_DIRS) $(CXXFLAGS) -c $< -o $@
	@echo -n "$(STOP_COLOR)"

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BOLD_BLUE)Creating executable $(NAME)...$(BOLD_PURPLE)"
	@$(CXX) $(OBJS) -o $(NAME)
	@echo "$(STOP_COLOR)$(BOLD_GREEN)SUCCESS !!!$(STOP_COLOR)"

clean:
	@echo "$(BOLD_BLUE)Delete obj...$(STOP_COLOR)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BOLD_RED)SUCCESS !!!$(STOP_COLOR)"

fclean: clean
	@echo "$(BOLD_BLUE)Make fclean...$(STOP_COLOR)"
	@rm -f $(NAME)
	@echo "$(BOLD_RED)SUCCESS !!!$(STOP_COLOR)"

re:     fclean all

-include $(DEPS)

.PHONY: all clean fclean re
