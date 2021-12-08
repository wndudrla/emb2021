#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "colorLED.h"

int main(int argc, char *argv[]) {
   pwmLedInit(); //켜기 
   coloredmy4();
   usleep(1000000);
   coloredmy2();
   pwmInactiveAll();
}
