
#include "debug.h"
#include "spi.h"
#include <util/delay.h>

void debug_init(){
	DEBUG_CS_DDR |= (1<<DEBUG_CS_PIN);
	DEBUG_CS_PORT |= (1<<DEBUG_CS_PIN);
}

void debug_begin(){
	DEBUG_CS_PORT &= ~(1<<DEBUG_CS_PIN);
}

void debug_end(){
	DEBUG_CS_PORT |= (1<<DEBUG_CS_PIN);
}

void debug_send_c(char c){
	DEBUG_CS_PORT &= ~(1<<DEBUG_CS_PIN);
	_delay_us(20);
	spi_send(c);
	_delay_us(100);
	DEBUG_CS_PORT |= (1<<DEBUG_CS_PIN);
}

void debug_send_s(char* str){
	DEBUG_CS_PORT &= ~(1<<DEBUG_CS_PIN);
	char c;
	while(!(c=*(str++))){
		spi_send(c);
		_delay_us(100);
	}
	DEBUG_CS_PORT |= (1<<DEBUG_CS_PIN);
}

void debug_send_hex(uint8_t v){
	uint8_t h=v>>4;
	DEBUG_CS_PORT &= ~(1<<DEBUG_CS_PIN);
	spi_send((h&0x0F)<0x0A?0x30+(h&0x0F):0x37+(h&0x0F));
	_delay_ms(10);
	spi_send((v&0x0F)<0x0A?0x30+(v&0x0F):0x37+(v&0x0F));
	DEBUG_CS_PORT |= (1<<DEBUG_CS_PIN);
}

void debug_send_hex_raw(uint8_t v){
	uint8_t h=v>>4;
	spi_send((h&0x0F)<0x0A?0x30+(h&0x0F):0x37+(h&0x0F));
	_delay_ms(50);
	spi_send((v&0x0F)<0x0A?0x30+(v&0x0F):0x37+(v&0x0F));
}

void debug_send_p(char* s){
	char c;
	uint8_t i=0;
	DEBUG_CS_PORT &= ~(1<<DEBUG_CS_PIN);
	while((c=pgm_read_byte(s++))){
		_delay_us(20);
		spi_send(c);
	}
	DEBUG_CS_PORT |= (1<<DEBUG_CS_PIN);
}
				

