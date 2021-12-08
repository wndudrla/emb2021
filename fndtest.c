#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <pthread.h>
#include <linux/input.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/ioctl.h> 
#include "fnd.h"

int main(int argc, char **argv){
	int number;
	number = atoi("60161795");
	fndDisp(number, 0);
	
	sleep(5);
	fndAllOff();
}
	
