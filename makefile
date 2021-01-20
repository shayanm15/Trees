make all: ttest tree.o

tree.o : tree.c
	gcc -std=c99 -Wall -pedantic -c tree.c -o tree.o

ttest.o : ttest.c
	gcc -std=c99 -Wall -pedantic -c ttest.c -o ttest.o 

ttest: ttest.o tree.o 
	gcc -std=c99 -Wall -pedantic -o ttest ttest.o tree.o 

clean:
	rm ttest ttest.o tree.o