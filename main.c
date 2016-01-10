#include <stdio.h>
#include <time.h>
//#include <fcntl.h>

#include "rpi.h"

extern struct bcm2835_peripheral gpio;
extern struct bcm2835_peripheral bsc0;

struct tm t;

/* Functions to do conversions between BCD and decimal */
unsigned int bcd_to_decimal(unsigned int bcd) {
    return ((bcd & 0xf0) >> 4) * 10 + (bcd & 0x0f);
}
unsigned int decimal_to_bcd(unsigned int d) {
    return ((d / 10) << 4) + (d % 10);
}

int main() {

    /* Gain access to raspberry pi gpio and i2c peripherals */
    if(map_peripheral(&gpio) == -1) {
        printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        return -1;
    }
    if(map_peripheral(&bsc0) == -1) {
        printf("Failed to map the physical BSC0 (I2C) registers into the virtual memory space.\n");
        return -1;
    }

    /* BSC0 is on GPIO 0 & 1 */
    i2c_init();

    printf("checking initial values of registers..\n");
    printf("ADDRESS: %8X\n",BSC0_A);
    printf("DIV: %8X\n",BSC0_DIV);

    printf("\n=============> working...\n\n");
    printf("set address\n");
    BSC0_A = 0x51;
    printf("ADDRESS: %8X\n",BSC0_A);



    /* Unmap the peripheral */
    unmap_peripheral(&gpio);
    unmap_peripheral(&bsc0);

    return 0;
}