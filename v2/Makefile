gen=`../tools/generator.py 100 0 100`

all:
	gcc *.c */*.c */*/*.c  -I. -fsanitize=address -g3

gen:
	ARG= echo $(gen); \
	echo $(ARG)

test:
	@echo Lauch Vizualiser
	./a.out $(ARG) |  ../tools/visualizer/visualizer.py $(ARG)