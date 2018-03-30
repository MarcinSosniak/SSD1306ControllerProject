

#ifndef SPI_H_INCLUDED
#define SPI_H_INCLUDED

#include "pi_mmio.h"

class Spi
{
public:
    int m_iDataCH;
    int m_iClockCH;
    int m_iDCCH;
    int m_iCSCH;

    Spi();
    Spi(int iDataCH, int iClockCH, int iDCCH, int iCSCH);
    void Set(int iDataCH, int iClockCH, int iDCCH, int iCSCH);

void send(char chByte, bool bDC);
};
#endif // SPI_H_INCLUDED

#ifndef LCDDRIVER_H_INCLUDED
#define LCDDRIVER_H_INCLUDED
#include "Arial6vertical.h"
#include "Arial10vertical.h"
#define SDATACH 17
#define SCLOCKCH 27
#define SDCCH 22
#define SCSCH 18

//=============================================================================


class LCDdriver
{
    public:
    char chMatrix[8][128];

    //konstruktor
    LCDdriver();

//Spi selected_spi(SDATACH,SCLOCKCH, SDCCH,SCSCH);
Spi selected_spi;//(17, 27, 22, 18);


void sendscreen();//wysyla caly ekran z chMatrix
char byteread(int x, int y);
bool bitread(int x, int y);
void overwritepixel(int x, int y,bool bValue);
bool ifdiffrence(LCDdriver kopy);
void Inicjalizacja();
void turnOFF();
void puttext(int x, int y, FONT_INFO* pFont, char* pStr);
void DRAWline(int xF ,int yF,int xS,int yS );
void DRAWpoint(int x,int y,bool pixel);//uses mask
};
int round(float fInput);//funkcja do zaokrglania w sensie 0,5 i wiecej -> 1 oraz 0,4(9) ->0

#endif // LCDDRIVER_H_INCLUDED
