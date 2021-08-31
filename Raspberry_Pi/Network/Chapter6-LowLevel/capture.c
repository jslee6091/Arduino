//---------------------------------------------
// capture.c (raw socket)
// 실행: $ sudo ./capture wlan0 10
//---------------------------------------------
#include  <stdio.h>
#include  <string.h>
#include  <stdlib.h>
#include  <net/ethernet.h>
#include  <unistd.h>
#include  <sys/ioctl.h>
#include  <arpa/inet.h>
#include  <sys/socket.h>
#include  <linux/if.h>
#include  <netpacket/packet.h>
#include  <netinet/if_ether.h>
#include  <netinet/ip.h>
#include  <netinet/tcp.h>

int print_ETHER_header(struct ether_header *eh);
int print_IP_header(struct iphdr *iphdr, u_char *option, int option_length);
int print_TCP_header(struct tcphdr *tcphdr);
int TCP_analysis(u_char *data, int size);
int IP_analysis(u_char *data, int size);
int PACKET_analysis(u_char *data, int size);

struct ether_header *eh;		// 이더넷헤더
struct iphdr *iphdr;			// IP 헤더
u_char *option;
int option_length;
int original_size;				// 패킷 크기
int count;				// 캡처하려는 패킷의 개수

//----------- main -------------------------
// raw socket 생성, 무차별모드 설정, 패킷 수신
//------------------------------------------

int main(int argc,char *argv[],char *envp[]){
    int  sock,size;
    u_char  buf[65535];
    struct ifreq  ifreq;

    if(argc != 3){
        printf("file_name device-name packet_count\n");
        return -1;
    }

    count = atoi(argv[2]);
 
    if((sock= socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP))) < 0){
        perror("raw_socket creation error");
        return -1;
    }
 
    memset(&ifreq,0,sizeof(struct ifreq));
    strcpy(ifreq.ifr_name, argv[1]);
 
    if(ioctl(sock, SIOCGIFFLAGS, &ifreq) < 0){
        perror("ioctl");
        close(sock);
        return -1;
    }
 
    ifreq.ifr_flags = ifreq.ifr_flags | IFF_PROMISC;
 
    if(ioctl(sock, SIOCSIFFLAGS, &ifreq) < 0){
        perror("ioctl: promiscous mode");
        close(sock);
        return -1;
    }

    while(1){
        if((size = read(sock, buf, sizeof(buf))) <= 0){
            perror("read");
            return -1;
        }

        else{
            PACKET_analysis(buf, size);         // 이더넷 헤더분석
        }
    }

    close(sock);
    return 0;
}

//----------- 이더넷 헤더 분석 -----------
int PACKET_analysis(u_char *data, int size){
    u_char  *pointer;
    int  rest;

    original_size = size; 				// 전체 패킷 크기
    pointer = data;
    rest = size;

    if(rest < sizeof(struct ether_header)){
        printf("rest(%d)<sizeof(struct ether_header)\n",rest);
        return -1;
    }

    eh = (struct ether_header *)pointer; 		// 이더넷 헤더 포인터
    pointer = pointer + sizeof(struct ether_header);
    rest = rest - sizeof(struct ether_header);
    if(ntohs(eh->ether_type) == ETHERTYPE_IP){ 	// 0x800	
        IP_analysis(pointer,rest); 			// IP 헤더분석 함수호출
    }
    return 0;
}

//----------- IP 헤더분석 -----------
int IP_analysis(u_char *data, int size){
    u_char  *pointer;
    int  rest;

    pointer = data;
    rest = size;
    if(rest < sizeof(struct iphdr)){
        printf("rest(%d)<sizeof(struct iphdr)\n", rest);
        return -1;
    }

     iphdr = (struct iphdr *)pointer;
     pointer = pointer + sizeof(struct iphdr);
     rest = rest - sizeof(struct iphdr); 
     option_length = iphdr->ihl*4 - sizeof(struct iphdr);

    if(option_length > 0){
        if(option_length >= 1500){
            printf("IP option_length(%d):길이 초과\n",option_length);
            return -1;
        }
        option = pointer;
        pointer = pointer + option_length;
        rest = rest - option_length;
    }

    if(iphdr->protocol == IPPROTO_TCP){
        TCP_analysis(pointer, rest);     // TCP 헤더분석 함수호출
    }
}

//---------- TCP 헤더분석 -----------
int TCP_analysis(u_char *data, int size){
    u_char  *pointer;
    int  rest;
    static int i = 0;
    int x;
    struct tcphdr  *tcphdr;

    pointer = data;
    rest = size;
    if(rest < sizeof(struct tcphdr)){
        printf("rest(%d)<sizeof(struct tcphdr)\n",rest);
        return -1;
    }

    tcphdr = (struct tcphdr *)pointer; 
    pointer = pointer + sizeof(struct tcphdr);
    rest = rest - sizeof(struct tcphdr);
    printf("\nPacket[%d bytes]\n", original_size);	// 패킷크기

    //----------- 응용 메시지 출력 -----------
    printf("\nApplication Message\n");
    for(x=0; x<rest; x++){
        if(isprint(pointer[x]))
            putchar(pointer[x]);
        else
            putchar('.');
    }
    printf("\n");

    print_TCP_header(tcphdr);			// TCP 헤더 출력
    print_IP_header(iphdr, option, option_length);  // IP 헤더 출력
    print_ETHER_header(eh); 			// Ethernet 헤더 출력
 
    i = i+1;
    if(i >= count)
        exit(-1);
    else
        return 0;
}

//----------- TCP 헤더 출력 -----------
int print_TCP_header(struct tcphdr *tcphdr){
    printf("----------< TCP header >----------\n");
    printf("source_port=%u,",ntohs(tcphdr->source)); 	// 송신지 포트번호
    printf("dest_port=%u\n",ntohs(tcphdr->dest));		// 수신지 포트번호
    printf("seq_num=%u\n",ntohl(tcphdr->seq)); 		// 순서번호
    printf("ack_num=%u\n",ntohl(tcphdr->ack_seq)); 	// 액노리지먼트 번호
    printf("data_offset=%u,",tcphdr->doff); 		// 헤더크기
    printf("urg=%u,",tcphdr->urg); 			// 긴급데이터
    printf("ack=%u,",tcphdr->ack); 			// ACK
    printf("psh=%u,",tcphdr->psh); 			// PUSH
    printf("rst=%u,",tcphdr->rst); 			// RESET
    printf("syn=%u,",tcphdr->syn); 			// SYN
    printf("fin=%u\n",tcphdr->fin); 			// FIN
    printf("window=%u, ",ntohs(tcphdr->window)); 		// 윈도우 크기
    printf("chksum=%u, ",ntohs(tcphdr->check)); 		// 체크섬
    printf("urgent_pointer=%u\n",ntohs(tcphdr->urg_ptr)); 	// 긴급포인터

    return 0;
}

//----------- IP 헤더 출력 -----------
int print_IP_header(struct iphdr *iphdr, u_char *option,int option_length){
    int   i;
    char  buf[80];

    printf("----------< IP header >----------\n");
    printf("version=%u,",iphdr->version);  			// 버전
    printf("IP_header_length=%u,",iphdr->ihl*4); 		// 헤더크기
    printf("type_of_service=%x,\n",iphdr->tos);		// type of service
    printf("total_length=%u,",ntohs(iphdr->tot_len));  	// IP+TCP+데이터
    printf("ID=%u, ",ntohs(iphdr->id));  			// 고유번호(ID)
    printf("frag_offset=%x,%u,\n",(ntohs(iphdr->frag_off)>>13)&0x07, ntohs(iphdr->frag_off)&0x1FFF); 	// 단편화 옵셋
    printf("TTL=%u,",iphdr->ttl); 				// Time to Live
    printf("protocol=%u",iphdr->protocol); 		// 상위계층 프로토콜

    if(iphdr->protocol == 6){   				// TCP이면
        printf("(%s),","TCP");
    }

    else{
        printf("(undefined),");
    }

    printf("checksum=%x\n",iphdr->check); 		// 체크섬
    printf("source_IP=%s, ", inet_ntop(AF_INET, (struct in_addr *)&iphdr->saddr, buf, sizeof(buf))); // 송신지 IP주소
    printf("dest_IP=%s\n", inet_ntop(AF_INET, (struct in_addr *)&iphdr->daddr, buf, sizeof(buf))); // 수신지 IP주소

    if(option_length > 0){ 				// 옵션처리
        printf("option:");

        for(i=0; i<option_length; i++){
            if(i != 0){
               printf(":%02x",option[i]);
            }
            else{
               printf("%02x",option[i]);
            }
        }
    }
    return 0;
}

//----------- 이더넷 헤더 출력 -----------
int print_ETHER_header(struct ether_header *eh){
    char  buf[80];
    u_char  *hwaddr;
    socklen_t  size;

    printf("----------< ETHERNET header >----------\n");
    hwaddr = eh->ether_dhost;
    size = sizeof(buf);
    snprintf(buf, size, "%02x:%02x:%02x:%02x:%02x:%02x", hwaddr[0], hwaddr[1], hwaddr[2], hwaddr[3], hwaddr[4], hwaddr[5]);
    printf("ether_destin_host=%s\n",buf);
    
    hwaddr = eh->ether_shost;
    snprintf(buf, size, "%02x:%02x:%02x:%02x:%02x:%02x", hwaddr[0], hwaddr[1], hwaddr[2], hwaddr[3], hwaddr[4], hwaddr[5]);
    printf("ether_source_host=%s\n",buf);
    printf("ether_type=%02X",ntohs(eh->ether_type));
    
    switch(ntohs(eh->ether_type)){
        case   ETH_P_IP:
                printf("(IP)\n");
                break;
        default:
                printf("(unknown)\n");
                break;
    }
    return 0;
}