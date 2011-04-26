

#include <avr/io.h>
#include <util/delay.h>
#include "ads1194.h"

/* FIXME/Note:
 * This method assumes nothing else than the ADS is on the spi in that the !CS pin of the ADS
 * is pulled low. If you want to change this, you will have to pull it low each time a command
 * or data is sent/to be received to/from the ADS.
 */
void init_ads_pass1(){
	ADS_CKSEL_DDR |= 1<<ADS_CKSEL_PIN;
	ADS_PWDN_DDR |= 1<<ADS_PWDN_PIN;
	ADS_RESET_DDR |= 1<<ADS_RESET_PIN;
	ADS_CS_DDR |= 1<<ADS_CS_PIN;
	
	ADS_PWDN_PORT |= 1<<ADS_PWDN_PIN;
	ADS_RESET_PORT |= 1<<ADS_RESET_PIN;
	ADS_CKSEL_PORT |= 1<<ADS_CKSEL_PIN;
}

/* FIXME/Note:
 * This method incorporates a 1ms delay. The delay needs to be at least 18 times the ocillator
 * period of the ads long, which is about 9ms in case of the internatl osc.
 */
void init_ads_pass2(){
	ADS_RESET_PORT &= ~(1<<ADS_RESET_PIN);
	nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop(); //About 1us @ 1MHz. Not critical.
	ADS_RESET_PORT |= 1<<ADS_RESET_PIN;
	_delay_ms(1); //That you'll have to cope with... or split this method, introduce a callback
		      //etc.
	
}

