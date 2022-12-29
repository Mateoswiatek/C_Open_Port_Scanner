#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#define PORT_OD 9000
#define PORT_DO 9005
SOCKET otwarty_port(char IP[15], int port){

}

int main() {
    char adresIP[15];
    int pom_porty, port_min, port_max;
    printf("Podaj adres IP\n"); // "192.168.56.1"
    scanf("%s", adresIP);
    printf("porty wszystkie(od1024) czy z zakresu (0/1)\n");
    scanf("%d", &pom_porty);
    if(pom_porty){
        printf("porty od\n");
        scanf("%d", &port_min);
        printf("porty od\n");
        scanf("%d", &port_max);
    }
    else{
        port_min=1024;
        port_max=65536;
    }
    printf("adres: %s, min: %d, max: %d", adresIP, port_min, port_max);

// 1024 do 65_536 prywatne, 0-1024 przypisane
    //for(i;i<)
    return 0;
}
