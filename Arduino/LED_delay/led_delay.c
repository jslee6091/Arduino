// F_CPU는 ATmega328P의 CPU 코어의 동작 클럭을 정의하는 것
// _delay_ms()에서 1초의 시간을 결정함
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h> // _delay_ms()가 들어있는 파일

int main(){
    DDRB |= (1 << PB1);

    while(1){
        PORTB ^= (1 << PB1);

        _delay_ms(10000); // 1000ms delay
    }
}