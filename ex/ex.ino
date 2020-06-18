#include <Arduino.h>
#include <wifiboy_lib.h>
#include "wb-sprite.h"

// num 只能傳正整數
// x X座標
// y Y座標
// colourMode 顏色選擇
void blit_num256(uint16_t num, uint16_t x, uint16_t y, uint8_t colourMode)
{
	uint16_t d[5];

	d[0] = num / 10000;
	d[1] = (num - d[0] * 10000) / 1000;
	d[2] = (num - d[0] * 10000 - d[1] * 1000) / 100;
	d[3] = (num - d[0] * 10000 - d[1] * 1000 - d[2] * 100) / 10;
	d[4] = num - d[0] * 10000 - d[1] * 1000 - d[2] * 100 - d[3] * 10;

	for (int i = 0; i < 5; i++)
	{
		wb_blitBuf8(d[i] * 8 + 120, colourMode * 8, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites); //將d[0]~d[4]逐個顯示並排列
	}
}

// str 只能傳大寫英文字母
// x X座標
// y Y座標
void blit_str256(const char *str, int x, int y)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] >= '@' && str[i] <= ']')
			wb_blitBuf8(8 * (str[i] - '@'), 0, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites);
		if (str[i] >= '!' && str[i] <= '>')
			wb_blitBuf8(8 * (str[i] - '!'), 8, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites);
		if (str[i] == '?')
			wb_blitBuf8(8 * 14, 16, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites);
		if (str[i] == 'c')
			wb_blitBuf8(8 * 13, 16, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites);
		if (str[i] == 'w')
			wb_blitBuf8(7, 16, 240, x + i * 8, y, 26, 8, (uint8_t *)sprites);
		if (str[i] == 'x')
			wb_blitBuf8(42, 16, 240, x + i * 8, y, 61, 8, (uint8_t *)sprites);
	}
}
// width 色塊寬度
// height 色塊高度
// x X座標
// y Y座標
// colourMode 顏色選擇
void blit_colour256(int width,int height, int x,int y,uint8_t colourMode)
{
	for(int i = y; i < y + height; i++)
	{
		for(int j = x; j < x + width; j++)
		{
			wb_setBuf8(i * 240 + j, colourMode);
		}
	}
}
void setup()
{
	wb_init(1); // 初始化 wifi-boy
	wb_initBuf16(); // 初始化螢幕緩存
	Serial.begin(115200);
	// wb_drawString("ABC",100,100,2,2);
	for(int i=0; i<256; i++) // 定義 256色（唯一色庫）
		wb_setPal8(i, wb_color565(standardColour[i][0],standardColour[i][1],standardColour[i][2]));
}

void loop()
{
	wb_clearBuf8();
	wb_blitBuf8(0,0,240,0,0,240,240,(uint8_t *)sprites);
	wb_blit8();// 點亮螢幕（把東西秀在畫面上）
}
