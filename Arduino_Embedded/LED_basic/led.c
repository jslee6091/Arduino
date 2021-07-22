#include <avr/io.h>

int main(){
    int i,j;
    // ATmega328P의 핀 초기 설정
    // 1 을 1만큼 왼쪽으로 Shift 시킨 값으로 DDRB 초기값 설정
    DDRB |= (1 << PB1);

    while(1){
        // ATmega328P 핀으로부터 신호 출력
        // PORTB 레지스터의 1비트째를 1(HIGH)과 0(LOW)으로 상호 전환하여 기록
        PORTB ^= (1 << PB1);
        
        for(i=0; i<10; i++){ // for 문을 사용하여 시간 간격 생성
            for(j=0; j<10000; j++);
        }
    } 
}