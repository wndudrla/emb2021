#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <linux/input.h>
#include <sys/ioctl.h> 

#include "fnd.h"

int fndDisp(int num, int dotflag)// 0~999999 숫자, 비트로 인코딩된 dot on/off
{
	int fd;
	int temp, i;
	stFndWriteForm stWriteData;
	for(i = 0; i < MAX_FND_NUM; i++){
		stWriteData.DataDot[i] = (dotflag & (0x1 << i)) ? 1 : 0;
		stWriteData.DataValid[i] = 1;
	}
	// if 6 fnd
	temp = num % 1000000; stWriteData.DataNumeric[0] = temp / 100000; // 한자리씩 넣어주는 구문
	temp = num % 100000; stWriteData.DataNumeric[1] = temp / 10000;
	temp = num % 10000; stWriteData.DataNumeric[2] = temp / 1000;
	temp = num % 1000; stWriteData.DataNumeric[3] = temp / 100;
	temp = num % 100; stWriteData.DataNumeric[4] = temp / 10;
	stWriteData.DataNumeric[5] = num % 10;
	fd = open(FND_DRIVER_NAME, O_RDWR);
	if(fd < 0){
		perror("drivet open error\n");
		return 0;
	}
	write(fd, &stWriteData, sizeof(stFndWriteForm));
	close(fd);
	return 1;
}
int fndAllOff() {
	int fd,i;
	stFndWriteForm stWriteData;
	
	for (i = 0; i < MAX_FND_NUM ; i++ ){
		stWriteData.DataDot[i] =  0;  
		stWriteData.DataNumeric[i] = 0;
		stWriteData.DataValid[i] = 0;
	}
	fd = open(FND_DRIVER_NAME,O_RDWR); 
	if ( fd < 0 ) 
	{
		perror("driver open error.\n");
		return 0;
	}	
	
	write(fd,&stWriteData,sizeof(stFndWriteForm)); 
	close(fd);  
	return 1;
}

