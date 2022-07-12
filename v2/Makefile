gen=`../tools/generator.py 10 0 10`
VAR=0
SRC_DIR = sortAlgorithm
OBJ_DIR = obj
SRC_BONUS_DIR = src_bonus
OBJ_BONUS_DIR = obj_bonus

SRC = 

all:
	gcc *.c */*/*.c  -I. -fsanitize=address -g3 -o push_swap # -I./sortAlgorithm/chunk/

myVar:
	VAR=$(gen)

gen:
	# export ARG=$(shell `$(gen)`);
	# echo $(ARG)
	echo $(VAR)

test:
	@echo Lauch Vizualiser
	./a.out $(ARG) |  ../tools/visualizer/visualizer.py $(ARG)

bonus:
	gcc ./Bonus/*.c ./sortAlgorithm/suitSort/suitSortUtils.c initCheck.c utils.c ./stackManip/action/*.c -I. -fsanitize=address -g3 -o checker

PHONY: bonus