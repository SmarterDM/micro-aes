all:
	cd ./test && gcc encrypt.c ../aes.c -o encrypt
clean:
	rm ./test/encrypt
clang:
	cd ./test && clang -Wall encrypt.c ../aes.c -o encrypt
	
