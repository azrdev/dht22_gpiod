run: sample
	sudo ./sample

sample: sample.c dht22.h
	gcc -lgpiod -I . $< -o $@
