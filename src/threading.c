#include "threading.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MIN(a, b)		((a)<(b)?(a):(b))
#define MAX(a, b)		((a)>(b)?(a):(b))
#define CLAMP(val, min, max)	(MIN(max, MAX(min, val)))
#define CLAMP_RGB(val)		(CLAMP(val, 0, 255))

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
	printf("Joining thread...\n");
	pthread_join(thread_id, NULL);
	printf("After thread\n");

	return;
}

void process_frame(const uint8_t* data, size_t size)
{
	// Convert center macro pixel to RGB
	const uint8_t* center = data + (size / 2);

	const uint8_t Y1 = center[0];
        const uint8_t U  = center[1];
        const uint8_t Y2 = center[2];
        const uint8_t V  = center[3];

	// Convert first pixel (Y1, U, V) to RGB
        int R1 = Y1 + 1.402 * (V - 128);
        int G1 = Y1 - 0.344136 * (U - 128) - 0.714136 * (V - 128);
        int B1 = Y1 + 1.772 * (U - 128);

	// Convert second pixel (Y2, U, V) to RGB
        int R2 = Y2 + 1.402 * (V - 128);
        int G2 = Y2 - 0.344136 * (U - 128) - 0.714136 * (V - 128);
        int B2 = Y2 + 1.772 * (U - 128);

	R1 = CLAMP_RGB(R1);
	G1 = CLAMP_RGB(G1);
	B1 = CLAMP_RGB(B1);
	
	R2 = CLAMP_RGB(R2);
	G2 = CLAMP_RGB(G2);
	B2 = CLAMP_RGB(B2);

	printf("macro pixel: 0x%02x%02x%02x 0x%02x%02x%02x\n", R1,G1,B1, R2,G2,B2);

	return;
}
