run: sample
	sudo ./sample 17

sample: sample.c dht22.h
	gcc -lgpiod -I . $< -o $@
