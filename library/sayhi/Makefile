all:
# 生成静态链接库
	gcc -c sayhi.c -o sayhi.o
	gcc -c saybye.c -o saybye.o
	ar -r libsay.a sayhi.o saybye.o
# 生成动态链接库
	gcc -shared -fPIC sayhi.c saybye.c -o libsay.so

clean:
	rm -rf *.o *.a *.so
