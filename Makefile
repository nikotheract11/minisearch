all:
	gcc -g app.c api.c trie.c app_functions.c ./heaps/PQ*.c -lm -o minisearch
clean:
	rm ./minisearch
