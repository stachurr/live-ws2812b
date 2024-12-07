#ifndef THREADING_H
#define THREADING_H

#include <pthread.h>
#include <stdint.h>

static pthread_mutex_t g_mutex;

void thread_test(void);
void process_frame(const uint8_t* data, size_t size);

#endif // THREADING_H
