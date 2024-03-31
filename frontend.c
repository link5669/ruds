/*---------------------------------------------------------------------------------

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <dswifi9.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdio.h>
#include <string.h>

#include "yard.h"

void getHttp(char* url);
	
int main(void) {
    videoSetMode(MODE_5_2D);

	videoSetModeSub(MODE_0_2D); //sub bg 0 will be used to print text

	vramSetBankA(VRAM_A_MAIN_BG);

	consoleDemoInit();  

	// int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);

	// set up our bitmap background
	bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0,0);
	
	decompress(yardBitmap, BG_GFX,  LZ77Vram);
    
	if(!Wifi_InitDefault(WFC_CONNECT)) {
		iprintf("Failed to connect!");
        while(1) {
            swiWaitForVBlank();
            int keys = keysDown();
            if(keys & KEY_START) break;
            return 0;
	    }
    }
        iprintf("\n  Upcoming Arrivals at The Yard");

        iprintf("\n");
        // iprintf("\n\t Weekend 1 - 15 minutes");
        // iprintf("\n\t Weekend 2 - 26 minutes");
        // iprintf("\n\t Weekend 2 - 48 minutes");

		getHttp("localhost");	
	
	while(1) {
        swiWaitForVBlank();
        int keys = keysDown();
        if(keys & KEY_START) break;
        return 0;
	}
	

	return 0;
}

void getHttp(char* url) {
    

   const char * request_text = 
        "GET / HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "User-Agent: Nintendo DS\r\n\r\n";

    struct hostent * myhost = gethostbyname( url );

    int my_socket;
    my_socket = socket( AF_INET, SOCK_STREAM, 0 );

    struct sockaddr_in sain;
    sain.sin_family = AF_INET;
    sain.sin_port = htons(8080);
    sain.sin_addr.s_addr= *( (unsigned long *)(myhost->h_addr_list[0]) );
    connect( my_socket,(struct sockaddr *)&sain, sizeof(sain) );

    send( my_socket, request_text, strlen(request_text), 0 );

    int recvd_len;
    char incoming_buffer[256];

    while( ( recvd_len = recv( my_socket, incoming_buffer, 255, 0 ) ) != 0 )  
        if(recvd_len>0) {
            incoming_buffer[recvd_len] = 0; 
            iprintf(incoming_buffer);
		}
	}

	shutdown(my_socket,0); 

	closesocket(my_socket); 

}
