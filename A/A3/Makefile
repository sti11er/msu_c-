all: A3

A3: main.o read_numbers.o shrink_numbers.o print_numbers.o
	gcc main.o read_numbers.o shrink_numbers.o print_numbers.o -o my_binary

main.o: main.c
	gcc -c main.c

read_numbers.o: read_numbers.c
	gcc -c read_numbers.c

shrink_numbers.o: shrink_numbers.c
	gcc -c shrink_numbers.c 

print_numbers.o: print_numbers.c
	gcc -c print_numbers.c

clean:
	rm -rf *.o A3
