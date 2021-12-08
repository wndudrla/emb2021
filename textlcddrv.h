#ifndef __TEXTLCD_DRV_H__
#define __TEXTLCD_DRV_H__
#define LINE_NUM 2
#define COLUMN_NUM 16
#define TEXTLCD_DRIVER_NAME "/dev/peritextlcd"
#define LINE_BUFF_NUM (COLUMN_NUM + 4) // for dummy
typedef struct TextLCD_tag
{
	unsigned char cmd; 
	unsigned char cmdData;
	unsigned char reserved[2];//4BYTE단위로 처리 자리 byte를 맞추기위해 끝에 2개를 나둠
	
	char TextData[LINE_NUM][LINE_BUFF_NUM];
}stTextLCD,*pStTextLCD;

#define MODE_CMD 0
#define MODE_DATA 1

#define CMD_DISPLAY_MODE 0x10 //display를 한다 ex) cmd
	#define BIT_DISPLAY_MODE_CURSOR_DISP 0x01//커서 보이게 ex) cmddata
	#define BIT_DISPLAY_MODE_CURSOR_BLINK 0x02//커서 깜박거리게
	#define BIT_DISPLAY_MODE_DISP_ENABLE 0x04

#define CMD_CURSOR_MOVE_MODE 0x11//커서가 앞뒤로 움직인다
	#define CURSOR_MOVE_MODE_ENABLE 0x01
	#define CURSOR_MOVE_MODE_RIGHT_DIR 0x02

#define CMD_CURSOR_MOVE_POSITION 0x12//커서가 움직인다
	#define CURSOR_MOVE_X_MASK 0x3F
	#define CURSOR_MOVE_Y_MASK 0xC0

#define CMD_WRITE_STRING 0x20//text를 쓴다
	#define CMD_DATA_WRITE_BOTH_LINE 0 //몇번째 라인에 쓸건가
	#define CMD_DATA_WRITE_LINE_1 1
	#define CMD_DATA_WRITE_LINE_2 2
	
#define CMD_TEST_GPIO_HIGH 0x30
#define CMD_TEST_GPIO_LOW
int textinit(void);
int textwrite(char *a,const char *b);
int textexit(void);

#endif //__TEXTLCD_DRV_H__
