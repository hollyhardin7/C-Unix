default: include cos330.o sin330.o tan330.o arccos.o arcsin.o arctan.o exp330.o log330.o libmath330.a cli.o

include: math330.h
	mkdir -p include
	cp math330.h ./include/

cos330.o: trig/cos330.c
	gcc -c ./trig/cos330.c -I./include/

sin330.o: ./trig/sin330.c
	gcc -c ./trig/sin330.c -I./include/

tan330.o: ./trig/tan330.c
	gcc -c ./trig/tan330.c -I./include/ 

arccos.o: ./trig/arccos.c
	gcc -c ./trig/arccos.c -I./include/ 

arcsin.o: ./trig/arcsin.c
	gcc -c ./trig/arcsin.c -I./include/ 

arctan.o: ./trig/arctan.c
	gcc -c ./trig/arctan.c -I./include/

exp330.o: ./exp/exp330.c
	gcc -c ./exp/exp330.c -I./include/

log330.o: ./exp/log330.c
	gcc -c ./exp/log330.c -I./include/

libmath330.a: cos330.o sin330.o tan330.o arccos.o arcsin.o arctan.o exp330.o log330.o
	ar r libmath330.a cos330.o sin330.o tan330.o arccos.o arcsin.o arctan.o exp330.o log330.o
	mkdir -p lib
	cp libmath330.a ./lib/

cli.o: ./cli/cli.c ./lib/libmath330.a
	mkdir -p bin
	gcc ./cli/cli.c -o ./bin/cli -I./include/ -L./lib -lmath330 -lm

clean:
	rm *.a
	rm *.o
	rm -rf lib
	rm -rf include
	rm -rf bin
