#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

/*
 * 1024 do 65_536 prywatne, 0-1024 przypisane
 *      sprawdza porty po kolei
 *      zapis do pliku
 * odczyt z pliku kolejnych adresów IP
 */

#define def_adres_IP "192.168.56.1"
#define PORT_OD 9000
#define PORT_DO 9020

int otwarty_port(char IP[15], int aktulany_port){
    int status, czy_otwarty;
    struct sockaddr_in ser;
    SOCKET gniazdo;
    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if(gniazdo==-1) {printf("blad socket\n");}

    ser.sin_family = AF_INET;
    ser.sin_port = htons(aktulany_port);
    ser.sin_addr.s_addr = inet_addr(IP);

    status = connect(gniazdo, (struct sockaddr *) &ser, sizeof(ser)); // łączenie gniazdo1 krotszy czas oczekiwania
    if (status < 0){ // blad polaczenia
        czy_otwarty=0;
    }
    else{
        czy_otwarty=1;
    }
    closesocket(gniazdo);
    return czy_otwarty;
} // zwraca 1 gdy port jest otwarty


int main() {
    char adresIP[15];
    int i, pom_porty, port_min, port_max, nr_portu;
    WSADATA wsaData; // przed inicjalizacją gniazd
    if (WSAStartup( MAKEWORD( 2, 0 ), &wsaData )){printf("blad WSDATA\n"); return 0;}

    // MENU:
    /*
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
    */

    //strcat(adresIP, def_adres_IP);
    sprintf(adresIP, def_adres_IP);
    port_min=PORT_OD;
    port_max=PORT_DO;
    printf("adres: #%s#, min: #%d#, max: #%d#\n", adresIP, port_min, port_max);
    
    for(i=port_min;i<=port_max;i++){
        printf("spr %d\n", i);
        nr_portu=otwarty_port(adresIP, i);
        if(nr_portu){printf("open port: %d\n", i);}
    }

    printf("koniec pracy\n");
    WSACleanup();
    return 0;
}
