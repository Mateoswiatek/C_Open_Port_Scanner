#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>
#include <conio.h> // ?


#pragma comment(lib,"ws2_32.lib")

/*
 * 1024 do 65_536 prywatne, 0-1024 przypisane
 *      sprawdza porty po kolei
 *      zapis do pliku
 * odczyt z pliku kolejnych adresów IP
 * skanowanie podsieci, ze też IP zmieniamy od jakiegos do jakiegos
 */

#define def_adres_IP "192.168.56.1"
#define PORT_OD 9000
#define PORT_DO 9007

int otwarty_port(char IP[15], int aktulany_port){
    int status;
    struct sockaddr_in ser;
    SOCKET gniazdo;
    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if(gniazdo==-1) {printf("blad socket\n");}

    ser.sin_family = AF_INET;
    ser.sin_port = htons(aktulany_port);
    ser.sin_addr.s_addr = inet_addr(IP);

    status = connect(gniazdo, (struct sockaddr *) &ser, sizeof(ser)); // łączenie gniazdo1 krotszy czas oczekiwania
    closesocket(gniazdo);
    return status;
}

int main() {
    char adresIP[15];
    int i, pom_porty, port_min, port_max, status_portu;
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


    time_t czas;
    struct tm * data;
    char godzina[80];
    time(& czas);
    data = localtime(& czas);
    strftime( godzina, 80, "_%Y_%m_%w_%H_%M", data ); // wyświetla podane elementy czasu
    printf("godzina to: %s\n", godzina);

    char nazwa_pliku[150];
    FILE *Otwarte, *Inne;
    printf("%s_%s%s\n", adresIP, godzina, "_Open.txt");
    strcat(nazwa_pliku, adresIP);
    strcat(nazwa_pliku,godzina);
    strcat(nazwa_pliku,"_Open.txt");
    printf("nazwa pliku: #%s#\n" ,nazwa_pliku);

    Otwarte=fopen(nazwa_pliku, "a");
    //Inne=fopen(strcat(adresIP, "_I.txt"), "a");

    for(i=port_min;i<=port_max;i++){ // omijamy zamkniete porty
        status_portu=otwarty_port(adresIP, i);
        printf("port: %d status: %d\n", i, status_portu);
        if(status_portu >=0){
            // tu zapis do pliku z otwartymi
            printf("otwarty: %d\n", i);
        }
        else if (status_portu<-1){ // a tu zapis w przyszliscido pliku z innymi bledami
            printf("nie otwarty\n");
        }
    }

    printf("koniec pracy\n");
    WSACleanup();
    return 0;
}
