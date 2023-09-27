# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 20:34:23 by ajeanne           #+#    #+#              #
#    Updated: 2023/09/25 10:55:10 by ajeanne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = PmergeMe

SRCS_DIR =	$(shell find srcs -type d)
INC_DIR =	includes
OBJS_DIR =	objects
DEPS_DIR =	deps

vpath %.cpp $(foreach dir, $(SRCS_DIR), $(dir):)

OBJS =	$(addprefix $(OBJS_DIR)/, $(SRCS:%.cpp=%.o))

SRCS =	main.cpp	\
		PmergeMe.cpp

CC =				c++
CFLAGS =			-Wall -Werror -Wextra -std=c++98 -g3
INCLUDES_FLAGS =	$(addprefix -I,$(INC_DIR))
DEPS_FLAGS =		-MT $@ -MMD -MP -MF $(DEPS_DIR)/$*.d
DEPS =				$(SRCS:%.cpp=$(DEPS_DIR)/%.d)

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR) $(DEPS_DIR)
	@echo "Creating $@"
	@-$(CC) $(CFLAGS) $(DEPS_FLAGS) $(INCLUDES_FLAGS) -c $< -o $@

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compile $(NAME)"
	@-$(CC) $(CFLAGS) $(OBJS) $(INCLUDES_FLAGS) -o $(NAME)
	@echo "========      COMPLETE       ========"

$(OBJS_DIR):
	@echo "Creating $@"
	@-mkdir -p $@

$(DEPS_DIR):
	@echo "Creating $@"
	@-mkdir -p $@

.PHONY: clean
clean:
	@echo "Deleting $(OBJS_DIR)"
	@-rm -rf $(OBJS_DIR)
	@echo "Deleting $(DEPS_DIR)"
	@-rm -rf $(DEPS_DIR)
	@echo "========      COMPLETE      ========"

.PHONY: fclean
fclean: clean
	@echo "Deleting $(NAME)"
	@-rm -f $(NAME)
	@echo "========    COMPLETE    ========"

.PHONY: re
re: fclean $(NAME)

-include $(DEPS)