SRC=main

all:
	gcc -o $(SRC) $(SRC).c -pg
	./$(SRC) $(ARGS)
	gprof $(SRC) gmon.out > $(NAME).txt
	python3 gprof2dot.py $(NAME).txt > $(NAME).dot
	dot -Tpng -o $(NAME).png $(NAME).dot

