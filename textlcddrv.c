#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <linux/input.h>
#include <sys/ioctl.h> 
#include "textlcddrv.h"

stTextLCD stlcd;
static int fd = 0;
static int len  = 0;

int textinit(void){
	fd = open(TEXTLCD_DRIVER_NAME, O_RDWR);
	if(fd < 0){
		perror("driver open error!\n");
		return 1;
	}
	memset(&stlcd, 0,sizeof(stTextLCD));
}

int textwrite(char *a, const char *b){
	unsigned int linenum   = 0;
	linenum = strtol(a,  NULL, 10);
	printf("linenum : %d\n",linenum);
	if(linenum == 1){
		stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
	}
	else if(linenum == 2){
		stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
	}
	else{
		printf("linenum : %d wrong range(1~2)\n",linenum);
		return 1;
	}
	len = strlen(b);
	if(len >  COLUMN_NUM){
		memcpy(stlcd.TextData[stlcd.cmdData - 1], b, COLUMN_NUM);
	}
	else{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],b,len);
	}
	stlcd.cmd = CMD_WRITE_STRING;
	fd = open(TEXTLCD_DRIVER_NAME, O_RDWR);
	if(fd < 0){
		perror("driver open error!\n");
		return 1;
	}
	write(fd, &stlcd,sizeof(stTextLCD));
}

int textexit(void){
	close(fd);
	return 0;
}
