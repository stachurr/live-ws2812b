CC = gcc
INCLUDE = -Iinclude -lpthread
OPTIONS = -Ofast


all: src/capture.c src/serial.c src/threading.c src/yuy2_to_rgb.c
	$(CC) $(OPTIONS) src/capture.c src/serial.c src/threading.c src/yuy2_to_rgb.c $(INCLUDE) -o capture

yuy2_to_rgb: src/yuy2_to_rgb.c
	$(CC) $(OPTIONS) src/yuy2_to_rgb.c $(INCLUDE) -o yuy2_to_rgb

