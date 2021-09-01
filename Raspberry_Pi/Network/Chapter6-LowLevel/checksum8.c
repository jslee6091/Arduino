// -----------------------------
// checksum8.c (8비트 체크섬)
// -----------------------------
#include <stdio.h>

unsigned char test(unsigned char *, int, int);

int main(void){
    unsigned char message[5] = {'A', 'B', 'C', 'D'};
    unsigned char ans;
    test(&message[4], 5, 1);

    printf("송신시 결과 = %d\n", (int) message[4]);
    ans = test(&message[4], 5, 2);
    printf("수신시 결과 = %d\n", (int) ans);

    return 0;
}

unsigned char test(unsigned char *p, int cnt, int flag){
    unsigned short int hap = 0;
    unsigned char *z;

    z = p;

    while(cnt--){
        hap = hap + *p--;

        if (hap & 0xFF00){               // 캐리 발생
            hap = hap & 0xFF;
            hap = hap + 1;
        }

        printf("cnt = %d hap = %d\n", cnt, hap);
    }

    if (flag == 1){
        *z = !(hap & 0xFF);
        return 0;
    }

    else{
        return !(hap & 0xFF);
    }
}
