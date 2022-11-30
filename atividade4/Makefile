run:
	gcc ativ.c -o default
	gcc ativ.c -o vectorize -ftree-vectorize
	gcc ativ_intrinsics.c -o intrinsics -mavx2
	./default
	./vectorize
	./intrinsics

make clean:
	rm default
	rm intrinsics
	rm vectorize

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BIN)