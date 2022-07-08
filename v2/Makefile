gen=`../tools/generator.py 10 0 10`

all:
	gcc *.c */*/*.c  -I. -fsanitize=address -g3 # -I./sortAlgorithm/chunk/ 

gen:
	export ARG= echo $(gen); \
	echo $(ARG)

test:
	@echo Lauch Vizualiser
	./a.out $(ARG) |  ../tools/visualizer/visualizer.py $(ARG)

bonus:
	gcc ./Bonus/*.c ./sortAlgorithm/suitSort/suitSortUtils.c initCheck.c utils.c ./stackManip/action/*.c -I. -fsanitize=address -g3 -o checker

PHONY: bonus