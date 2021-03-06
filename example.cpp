/* 
 * WHAT THIS EXAMPLE DOES
 * 
 * We create a pool of 4 threads and then add 40 tasks to the pool(20 task1 
 * functions and 20 task2 functions). task1 and task2 simply print which thread is running them.
 * 
 * As soon as we add the tasks to the pool, the threads will run them. It can happen that 
 * you see a single thread running all the tasks (highly unlikely). It is up the OS to
 * decide which thread will run what. So it is not an error of the thread pool but rather
 * a decision of the OS.
 * 
 * */

#include <stdio.h>
#include <pthread.h>
#include "thpoolcpp.h"


void* task1(void*){
	printf("Thread #%u working on task1\n", (int)pthread_self());
	return NULL;
}


void* task2(void*){
	printf("Thread #%u working on task2\n", (int)pthread_self());
	return NULL;
}

class task3: public ThreadJob {
	public:
		void run() override {
			printf("Thread #%u working on task3\n", (int)pthread_self());
		}
};

int main(){
	
	puts("Making threadpool with 4 threads");
	new ThreadPool(4);

	puts("Adding 40 tasks to threadpool");
	int i;
	for (i=0; i<20; i++){
		ThreadPool::getSingletonPtr()->add(task1, NULL);
		ThreadPool::getSingletonPtr()->add(task2, NULL);
		ThreadPool::getSingletonPtr()->add(new task3);
	};

	puts("Killing threadpool");
	ThreadPool::getSingletonPtr()->wait();
	delete ThreadPool::getSingletonPtr();
	return 0;
}
