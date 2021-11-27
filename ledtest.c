#include <stdio.h>
#include "led.h"

int main(void){
	ledLibInit();//ledLibInit()확인
	
	ledLibRaw(0xFF);
	sleep(1);
	ledLibRaw(0xAA);
	sleep(1);
	ledLibRaw(0x55);
	sleep(1);
	ledLibRaw(0x0);
	int i=0;
	for(i = 0; i < 8; i++){
			ledLibOnOff(i, 1);//ledLibOnOff() 확인
			printf("0x%02X---- ok?\r\n",ledLibStatus());//ledLibStatus()동작 확인
			usleep(200*1000);
			ledLibOnOff(i, 0);
			usleep(200*1000);
	}
	ledLiblink(1, 10, 500);//ledLibblink() 확인 5번 led 10번 깜빡 100ms간격
	
	ledLibMorseBlink(2, 3, 500, 500); // on 0.5 off 0.5 3번 깜빡임 == S
	ledLibMorseBlink(2, 3, 1500, 500); // on 1.5 off 0.5 3번 깜빡임 == O
	ledLibMorseBlink(2, 3, 500, 500); // on 0.5 off 0.5 3번 깜빡임 == S
	ledLibGOahead(0x0);
	sleep(1);
	ledLibGOahead(0x01);
	sleep(1);
	ledLibGOahead(0x03);
	sleep(1);
	ledLibGOahead(0x07);
	sleep(1);
	ledLibGOahead(0x0F);
	sleep(1);
	ledLibGOahead(0x1F);
	sleep(1);
	ledLibGOahead(0x3F);
	sleep(1);
	ledLibGOahead(0x7F);
	sleep(1);
	ledLibGOahead(0xFF);
	sleep(1);
	sleep(2); //we whould check 
	ledLibExit();
}
