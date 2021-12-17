#include <stdio.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h> 
#include "touch.h"
#include "buzzer.h"
#include "textlcddrv.h"
#include "fnd.h"
#include "led.h"
#include "colorLED.h"
#include "button.h"
#include "temperature.h"
int temp;
int count = 1;
static pthread_t buttonTh_id2; // 쓰레드를 이용해서 제어
static pthread_t buttonTh_id3; // 쓰레드를 이용해서 제어
static pthread_t buttonTh_id4; // 쓰레드를 이용해서 제어
int main(int argc, char *argv[])
{
	time_t t = time(NULL); //년 / 월 / 일을 표시하기 위한 함수
	struct tm tm = *localtime(&t);
	char s1[16];
	distemp(); // 온도센서를 이용하기 위한 함수
	sprintf(s1, "%d %d %d %d %d",temp, tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_wday); //sprintf를 이용하여 날짜, 온도를 순차적으로 s1에 넣어줌 
	textinit(); //textlcd on, 1번째 줄 날짜, 온도, 2번째 줄 악기 소리 종류 피아노,런치패드1,런치패드2
	textwrite("1", s1); //1번째 라인에 s1표기
	textwrite("2", "Instrument"); //2번째 라인은 악기 종류 표기
	startbu(); //buzzer 도레미로 울림
	ledLibInit(); // led사용 위함(volup 누를 시 1칸씩 증가)(voldown은 1칸씩 감소)
	touchInit(); // touchscreen
	pthread_create(&buttonTh_id2, NULL, buttonInit, NULL); // 버튼 message send
	pthread_create(&buttonTh_id3, NULL, buttonmere, NULL); // 버튼 message recv led제어 포함,  종료시 부저, textlcd, led, button, touch, buzzer exit포함 
	pthread_create(&buttonTh_id4, NULL, minucount, NULL); // fnd 제어, colorled 포함
	int msgID = msgget( MESSAGE_ID, IPC_CREAT|0666);
	TOUCH_MSG_T recvMsg;
	while (1)
	{
		msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		switch (recvMsg.keyInput)
		{
			case 999:
				if (recvMsg.pressed == 1)
				{
					if (recvMsg.x > 0 && recvMsg.x < 344 && recvMsg.y > 0 && recvMsg.y < 207) // 3x3 패드의 각각의 좌표를 받아옴
					{
						printf ("No.1\r\n");
						if(count == 1) doo();
						else if(count == 2) dooo();
						else if(count == 3) mix0();
if(temp>30) doo();
					}
					else if (recvMsg.x > 360 && recvMsg.x < 680 && recvMsg.y > 0 && recvMsg.y < 207)
					{
						printf ("No.2\r\n");
						if(count == 1)  ree();
						else if(count == 2) reee();
						else if(count == 3) mix1();
if(temp>30) doo();
					}
					else if (recvMsg.x > 690 && recvMsg.x < 1024 && recvMsg.y > 0 && recvMsg.y < 207)
					{
						printf ("No.3\r\n");
						if(count == 1)  mee();
						else if(count == 2) meee();
						else if(count == 3) mix2();
if(temp>30) doo();
					}
                  else if (recvMsg.x > 344 && recvMsg.x < 360 && recvMsg.y > 0 && recvMsg.y < 620)
					{
						printf ("Wrong place!\r\n");
if(temp>30) doo();
					}
                  else if (recvMsg.x > 680 && recvMsg.x < 690 && recvMsg.y > 0 && recvMsg.y < 620)
					{
						printf ("Wrong place!\r\n");
if(temp>30) doo();
					}
					else if (recvMsg.x > 0 && recvMsg.x < 344 && recvMsg.y > 210 && recvMsg.y < 410)
					{
						printf ("No.4\r\n");
						if(count == 1)  faa();
						else if(count == 2) faaa();
						else if(count == 3) mix3();
if(temp>30) doo();
					}
					else if (recvMsg.x > 360 && recvMsg.x < 680 &&  recvMsg.y > 210 && recvMsg.y < 410)
					{
						printf ("No.5\r\n");
						if(count == 1)  soll();
						else if(count == 2) solll();
						else if(count == 3) mix4();
if(temp>30) doo();
					}
				    else if (recvMsg.x > 690 && recvMsg.x < 1024 &&  recvMsg.y > 210 && recvMsg.y < 410)
					{
						printf ("No.6\r\n");
						if(count == 1)  raa();
						else if(count == 2) raaa();
						else if(count == 3) mix5();
if(temp>30) doo();
					}
                 else if (recvMsg.x > 0 && recvMsg.x < 1024 && recvMsg.y > 207 && recvMsg.y < 210)
					{
						printf ("Wrong place!\r\n");
if(temp>30) doo();
					}
                 else if (recvMsg.x > 0 && recvMsg.x < 1024 && recvMsg.y > 410 && recvMsg.y < 420)
					{
						printf ("Wrong place!\r\n");
if(temp>30) doo();
					}
					else if (recvMsg.x > 0 && recvMsg.x < 344 && recvMsg.y > 420 && recvMsg.y < 620)
					{
						printf ("No.7\r\n");
						if(count == 1)  sii();
						else if(count == 2) siii();
						else if(count == 3) mix6();
if(temp>30) doo();
					}
					else if (recvMsg.x > 360 && recvMsg.x < 680 &&  recvMsg.y > 420 && recvMsg.y < 620)
					{
						printf ("No.8\r\n");
						if(count == 1)  dooo();
						else if(count == 2) siii();
						else if(count == 3) count = 1;
if(temp>30) doo();
					}
				    else if (recvMsg.x > 690 && recvMsg.x < 1024 && recvMsg.y > 420 && recvMsg.y < 620)
					{
						printf ("No.9\r\n");
						//reee();
						count++;
						printf("%d\n",count);
						if(count == 4) count =1;
if(temp>30) doo();
					}
				}
			break;
		}
	}
}
