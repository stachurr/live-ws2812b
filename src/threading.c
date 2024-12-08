#include "threading.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* my_thread_func(void* arg)
{
	printf("Sleeping for 1 second...\n");
	sleep(1);
	printf("Done sleeping\n");
	
	return NULL;
}

void thread_test(void)
{
	pthread_t thread_id;
	printf("Before thread\n");
	pthread_create(&thread_id, NULL, my_thread_func, NULL);
	pthread_join(thread_id, NULL);
	printf("After thread\n");

	return;
}

void process_frame(const uint8_t* data, size_t size)
{
	return;
}
