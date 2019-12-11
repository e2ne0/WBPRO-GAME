#include <Arduino.h>
#include <wifiboypro.h>
#include "wb-sprite.h"

void blit_num256(uint16_t num, uint16_t x, uint16_t y, uint8_t color_mode)
{
    uint16_t d[5];

    d[0] = num / 10000;
    d[1] = (num - d[0] * 10000) / 1000;
    d[2] = (num - d[0] * 10000 - d[1] * 1000) / 100;
    d[3] = (num - d[0] * 10000 - d[1] * 1000 - d[2] * 100) / 10;
    d[4] = num - d[0] * 10000 - d[1] * 1000 - d[2] * 100 - d[3] * 10;

    for (int i = 0; i < 5; i++)
    {
        wbpro_blitBuf8(d[i] * 8 + 120, color_mode * 8, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites); //將d[0]~d[4]逐個顯示並排列
    }
}

void blit_str256(const char *str, int x, int y)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] >= '@' && str[i] <= ']')
            wbpro_blitBuf8(8 * (str[i] - '@'), 0, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites);
        if (str[i] >= '!' && str[i] <= '>')
            wbpro_blitBuf8(8 * (str[i] - '!'), 8, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites);
        if (str[i] == '?')
            wbpro_blitBuf8(8 * 14, 16, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites);
        if (str[i] == 'c')
            wbpro_blitBuf8(8 * 13, 16, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites);
        if (str[i] == 'w')
            wbpro_blitBuf8(7, 16, 240, x + i * 8, y, 26, 8, (uint8_t *)sprites);
        if (str[i] == 'x')
            wbpro_blitBuf8(42, 16, 240, x + i * 8, y, 61, 8, (uint8_t *)sprites);
    }
}
void blit_colour256(int x,int y,int width,int hight,uint8_t colour)
{
    for(int i = y; i < y + hight; i++)
    {
        for(int j = x; j < x + width; j++)
        {
            wbpro_setBuf8(i * 240 + j, colour);
        }
    }
}

void setup()
{
    wbpro_init();
    wbpro_initBuf8();
    for(int i=0; i<256; i++)
        wbpro_setPal8(i, wbpro_color565(sprite_pal[i][0],sprite_pal[i][1],sprite_pal[i][2]));
}

void loop()
{
    wbpro_clearBuf8();

    blit_num256(123, 0, 0, 1);
    blit_str256("HELLO WORLD",0,8);
    blit_colour256(0,16,240,8,5);

    wbpro_blit8();
}

