# dht22_gpiod
DHT22 temperature sensor library that uses the standard Linux kernel GPIO interface.

## Usage

It is a header only library so all you need to do is include the `dht22.c` file in your project.

To use it you first need to initialize the gpiod structures.

```C
#include <gpiod.h>

int main(){

    struct gpiod_chip *chip;
	struct gpiod_line *line;

    /* Use gpiodetect to get your GPIO chip dev file */
    chip = gpiod_chip_open("/dev/gpiochip0");
	if (!chip){
		printf("Error opening chip\n");
		return -1;
	}

    /* The second parameter is the GPIO pin number */
	line = gpiod_chip_get_line(chip, 4);
	if (!line) {
		gpiod_chip_close(chip);
		return -1;
	}
}
```

As the sensor is very simple, it only contains a single function. Usage example:

```C
/* Continuously get the temperature and humidity */
float temp;
float hum;
while(1){
    /* All you need to read the sensor */
    DHT22_RC rc = dht22_read(line, &temp, &hum);

    if(rc != DHT22_SUCCESS){
        printf("RC: %d\n", rc);
    }

    printf("Temp: %f	Humi: %f\n", temp, hum);
    sleep(3);
}
```