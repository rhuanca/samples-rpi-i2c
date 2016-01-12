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
    int data = 0;
    printf("\n\nstarting program...\n");
    printf("=====================\n");

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

    // 0x82;

    /* I2C Device Address 0x51 (See Datasheet) */
    BSC0_A = 0x51;

    /* Write operation to restart the PCF8563 register at index 2 ('secs' field) */
    BSC0_DLEN = 1;            // one byte
    BSC0_FIFO = 2;            // value 2
    BSC0_S = CLEAR_STATUS;    // Reset status bits (see #define)
    BSC0_C = START_WRITE;     // Start Write (see #define)

    wait_i2c_done();

//    /* Start Read of RTC chip's time */
//    BSC0_DLEN = 7;
//    BSC0_S = CLEAR_STATUS;  // Reset status bits (see #define)
//    BSC0_C = START_READ;    // Start Read after clearing FIFO (see #define)
//
//    wait_i2c_done();
//
//    /* Store values in struct */
//    t.tm_sec = bcd_to_decimal(BSC0_FIFO & 0x7f);
//    t.tm_min = bcd_to_decimal(BSC0_FIFO & 0x7f);
//    t.tm_hour = bcd_to_decimal(BSC0_FIFO & 0x3f);
//    t.tm_mday = bcd_to_decimal(BSC0_FIFO & 0x3f);
//    t.tm_wday = bcd_to_decimal(BSC0_FIFO & 0x07);
//    t.tm_mon = bcd_to_decimal(BSC0_FIFO & 0x1f) - 1; // 1-12 --> 0-11
//    t.tm_year = bcd_to_decimal(BSC0_FIFO) + 100;
//
//    printf("%02d:%02d:%02d %02d/%02d/%02d (UTC on PCF8563)\n",
//           t.tm_hour,t.tm_min,t.tm_sec,
//           t.tm_mday,t.tm_mon + 1,t.tm_year - 100);

    printf("* BSC0_S: %08X\n", BSC0_S);

    /* Unmap the peripheral */
    unmap_peripheral(&gpio);
    unmap_peripheral(&bsc0);
    return 0;
}