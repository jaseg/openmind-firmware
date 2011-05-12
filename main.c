
#include "main.h"
#include "ads1194.h"
#include <util/delay.h>

int main(void){
	ads_init_pass1();
	DDRD |= 0x1C;
	_delay_ms(500); //Wait for the power supplies to settle (Should not need that much time)
	ads_init_pass2();
	_delay_ms(1000); //Wait for the ads to initialize...
	ads_init_pass3();
	_delay_ms(500); //Wait for the ads's internal reference to settle
	ads_init_pass4();
	//The ads is ready for use!
	uint8_t val[4];
	while(1){
		ads_read_registers(ADS_REG_ID, 4, val);
		uint8_t i=0;
		while(i<8){
			uint8_t tmp=val[i>>1];
			if(i&1)
				tmp&=0x0F;
			else
				tmp>>=4;
			for(uint8_t j=0; j<tmp; j++){
				PORTD |= 0x10;
				_delay_ms(250);
				PORTD &= ~0x10;
				_delay_ms(250);
			}
			PORTD |= 0x08;
			_delay_ms(500);
			PORTD &= ~0x08;
			_delay_ms(500);
			i++;
		}
		PORTD |= 0x04;
		_delay_ms(2000);
		PORTD &= ~0x04;
		_delay_ms(2000);
	}
}

