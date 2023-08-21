#include <stdio.h>
#include <stdlib.h>
#include <gpiod.h>
#include "dht22.h"


static const char *DHT22_RC_STRING[] = {
        "SUCCESS",
        "TIMEOUT",
        "CHECKSUM_FAIL",
        "GPIO_FAIL",
        "NULL_POINTER",
};

char const* dht22_rc_to_str(DHT22_RC rc) {
        const size_t DHT22_RC_STRING_size = sizeof(DHT22_RC_STRING) / sizeof(DHT22_RC_STRING[0]);
        if (0 > rc || rc >= DHT22_RC_STRING_size) {
                return NULL;
        }
        return DHT22_RC_STRING[rc];
}


int main(int argc, char* argv[]){
    if(argc != 2) {
        fprintf(stderr, "Usage: ./sample GPIO_NUMBER\n");
        return 1;
    }
    const int gpio = atoi(argv[1]);

    struct gpiod_chip *chip;
    struct gpiod_line *line;

    /* Use gpiodetect to get your GPIO chip dev file */
    chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip){
        printf("Error opening chip\n");
        return -1;
    }

    line = gpiod_chip_get_line(chip, gpio);
    if (!line) {
        gpiod_chip_close(chip);
        return -1;
    }

    /* Continuously get the temperature and humidity */
    while(1){
        float temp;
        float hum;
        /* All you need to read the sensor */
        DHT22_RC rc = dht22_read(line, &temp, &hum);
        if(rc == DHT22_SUCCESS) {
            printf("temperature=%2.2f humidity=%2.2f\n", temp, hum);
        } else {
            fprintf(stderr, "RC: %16s\n", dht22_rc_to_str(rc));
        }
        sleep(3);
    }

}
