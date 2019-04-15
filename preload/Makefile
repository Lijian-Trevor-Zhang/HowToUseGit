all:
# LD_RELOAD指定的动态链接库可以覆盖系统的动态链接库
	gcc main.c -o main
	./main
	gcc -shared -fPIC unrandom.c -o unrandom.so
	LD_PRELOAD=${PWD}/unrandom.so ./main

clean:
	rm -rf main *.so
