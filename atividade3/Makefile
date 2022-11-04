all:
	gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge main.c -o main -lm

test:
	gcc -o main main.c -pg -lm -march=native
	gcc -o mainO1 main.c -pg -lm -O1 -march=native
	gcc -o mainO2 main.c -pg -lm -O2 -march=native
	gcc -o mainO3 main.c -pg -lm -O3 -march=native
	gcc -o mainFlags main.c -pg -lm -fdce -fstrict-aliasing -ftree-pre -ftree-vrp -freorder-functions -fsignaling-nans -ffp-contract=on -fipa-profile -fsched-spec -funroll-all-loops -march=native
	./main $(ARGS)
	gprof main gmon.out > semOtimizacao.txt
	./mainO1 $(ARGS)
	gprof mainO1 gmon.out > O1.txt
	./mainO2 $(ARGS)
	gprof mainO2 gmon.out > O2.txt
	./mainO3 $(ARGS)
	gprof mainO3 gmon.out > O3.txt
	./mainFlags $(ARGS)
	gprof mainFlags gmon.out > flags.txt

run:
	./a 50000000