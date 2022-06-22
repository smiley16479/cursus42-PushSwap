gen=`../tools/generator.py 10 0 10`

all:
	gcc *.c */*/*.c  -I. # -I./sortAlgorithm/chunk/ -fsanitize=address -g3

gen:
	export ARG= echo $(gen); \
	echo $(ARG)

test:
	@echo Lauch Vizualiser
	./a.out $(ARG) |  ../tools/visualizer/visualizer.py $(ARG)