#ifndef _COLORLED_H_
#define _COLORLED_H_


int pwmActiveAll(void);
int pwmInactiveAll(void);
int pwmSetDuty(int dutyCycle, int pwmIndex);
int pwmSetPeriod(int Period, int pwmIndex);
int pwmSetPercent(int percent, int ledColor);
int pwmStartAll(void);
int pwmLedInit(void);
int coloredmy1(void);
int coloredmy2(void);
int coloredmy3(void);
int coloredmy4(void);

#endif
