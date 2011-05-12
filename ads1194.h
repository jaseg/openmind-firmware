

#ifndef __ADS1194_H__
#define __ADS1194_H__

extern void ads_init_pass1(void);
extern void ads_init_pass2(void);
extern void ads_read_register(uint8_t address, uint8_t count, uint8_t* buffer);
extern void ads_write_register(uint8_t address, uint8_t count, uint8_t* buffer);

//ADS1X9X SPI commands
#define ADS_WAKEUP	0x02
#define ADS_STANDBY	0x04
#define ADS_RESET	0x06
#define ADS_START	0x08
#define ADS_STOP	0x0A
#define ADS_RDATAC	0x10
#define ADS_SDATAC	0x11
#define ADS_RDATA	0x12

#endif//__ADS1194_H__
