SRC_DIR= ../Sources/
SRC_BONUS_DIR= ../Sources_Bonus/
OBJ_DIR = Objects
# PROJDIR := $(realpath $(CURDIR)/..)

SRC =	main.c \
		elem2keepSwapFurther.c \
		gt_sort_BA.c \
		gt_sort_BA_2.c \
		gt_sort.c \
		gt_sortUtils.c \
		push.c \
		revRotat.c \
		rotat.c \
		swap.c \
		autoSwapCheck.c \
		initCheck.c \
		utils_shared.c \
		utils.c \
		utilss.c

SRC_BONUS =	utilss.c \
			initCheck.c \
			utils_shared.c \
			utils.c \
			swap.c \
			rotat.c \
			push.c \
			revRotat.c \
			bonus.c \
			get_next_line_utils.c \
			get_next_line.c \
			gnl_2000.c \
			bonus_utils.c

# $(shell find ../Sources/tools ../Sources/stackManip/action ../Sources_Bonus/ -type f -name \*.c -printf "%f ") 

# OBJ =  $(OBJ_DIR)/${SRC:.c=.o} #$(notdir ${SRC:%.c=%.o}) #
OBJ =  $(foreach file, ${SRC:.c=.o}, $(OBJ_DIR)/$(file))
OBJ_BONUS =  $(foreach file, ${SRC_BONUS:.c=.o}, $(OBJ_DIR)/$(file))

CFLAG = -fsanitize=address -g3 -Wall -Wextra -Werror
IFLAG = -I../Sources/tools -I../Sources_Bonus
NAME = push_swap
BONUS_TARGET = checker

vpath %.c $(SRC_DIR)sortAlgorithm/:$(SRC_DIR)stackManip/action/: \
			$(SRC_DIR)stackManip/optimisation/:$(SRC_DIR)tools/:$(SRC_DIR)main/:$(SRC_BONUS_DIR)

all: $(NAME)
	@echo regle 1 $@

## $@ = la cible de la regle
## $< = la premiere dependance de la regle
## $^ = les dependances de la regle

# C'est ça qui fait la regle : "${SRC:.c=.o}"
# et ça marche grace au vpath qui permet d'aller chercher des les dossiers spécifiés
$(OBJ_DIR)/%.o : %.c # %.c:%.o #
	@mkdir -p Objects
	@echo regle .c.o: $$\<: $< - $$\@: $@ \\n $(notdir $@)
	gcc  -c $(IFLAG) $< -o $@

# %.c : $(OBJ_DIR)/%.o # %.c:%.o #
# @mkdir -p Objects
# gcc  -c $(IFLAG) $@ -o $<

$(NAME)	: $(OBJ)
	@gcc $(OBJ) $(CFLAG) $(IFLAG) -o $@

bonus: $(OBJ_BONUS)
	@gcc $(OBJ_BONUS) $(CFLAG) $(IFLAG) -o $(BONUS_TARGET)

clean :
	@echo Clean done \(rm obj\)
	@rm -f $(OBJ)
	@rm -f $(OBJ_BONUS)

fclean : clean
	@echo Clean done \(rm executable\)
	@rm -f $(NAME)
	@rm -f $(BONUS_TARGET)

re:	fclean all

PHONY: bonus

show:
	@# @echo "SRC_DIR : $(SRC_DIR)\n"
	@echo "SRC :$(foreach file, $(SRC),\n\t$(file))\n"
	@echo "SRC_BONUS :$(foreach file, $(SRC_BONUS),\n\t$(file))\n"
	@echo "OBJS : $(foreach file, $(OBJS),\n\t$(file))\n"
	@# @echo "SRC_BONUS :$(foreach file, $(SRC_BONUS),\n\t$(file))\n"
	@# @echo "TEST_patsubst : $(foreach file, $(patsubst %.c,%.o,$(SRC)),\n\t$(file))\n"
	@# @echo "TEST_basename : $(foreach file, $(basename $(SRC)),\n\t$(file))\n"
#	@echo "TEST_notdir : $(foreach file, $(notdir $(SRC)),\n\t$(file))\n"
#	@echo RE ${SRC:%.c=%.o}
	@echo OBJ $(OBJ)
	@echo OBJS2 $(OBJS2)
