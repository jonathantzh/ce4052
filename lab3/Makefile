#defing a variable 'objects'
objects = hellomain.o hellofunct.o

#linking rules
Hello: $(objects)
	gcc -o hello hellomain.o hellofunct.o

#Compiling rules
hellomain.o: hellomain.c
	gcc -Wall -g -c hellomain.c

hellofunct.o: hellofunct.c
	gcc -Wall -g -c hellofunct.c

#Others
clean:
	rm -f $(objects)
