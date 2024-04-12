build:
	gcc -g -o tema1 main.c Functii.c
	
run:
	./tema1

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind-out.txt ./tema1

clean:
	rm tema1
