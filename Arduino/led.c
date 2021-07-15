#include <avr/io.h>

int main(){
    int i,j;
    DDRB != (1 << PB1);

    while(1){
        PORTB ^= (1 << PB1);
        for(i=0; i<10; i++){
            for(j=0; j<10000; j++);
        }
    } 
}