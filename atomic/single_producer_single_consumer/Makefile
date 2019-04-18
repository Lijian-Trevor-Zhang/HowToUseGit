# atomic.c 标准的single producer/single consumer模型
# atomic_optimize.c 优化后的atomic.c，包含software caching/batching机制
# no_atomic.c 有问题的代码，需要mutex机制进行保护
# no_atomic_wizLock.c 采用mutext机制保护的代码
all:
	gcc atomic.c -lpthread -o atomic
	gcc atomic_optimize.c -lpthread -o atomic_optimize
	gcc no_atomic.c -lpthread -o no_atomic
	gcc no_atomic_wizLock.c -lpthread -o no_atomic_wizLock

clean:
	rm -rf atomic atomic_optimize no_atomic no_atomic_wizLock a.out
