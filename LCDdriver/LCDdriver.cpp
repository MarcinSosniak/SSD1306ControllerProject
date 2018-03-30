#include"pi_mmio.h"
#include<time.h>
#include"LCDdriver.h"
#include <iostream>
#include<stdio.h>
#define DEBUG_1


#define MAX_Y 63
#define MAX_X 127
//#define DEBUG_SEND_1
//---------------------------NON-class-functions-------------------------------

#ifdef DEBUG_SEND_1

#endif//DEBUG_SEND_1

void  turnOFF(Spi selected_spi)
{
    selected_spi.send(0xAE,0);
}

//==================================classes====================================
//------SPI----------------------------------------------
Spi::Spi()
{
}
Spi::Spi(int iDataCH, int iClockCH, int iDCCH, int iCSCH)
{
    m_iDataCH=iDataCH;
    m_iClockCH=iClockCH;
    m_iDCCH=iDCCH;
    m_iCSCH=iCSCH;

    pi_mmio_init();

    pi_mmio_set_output(m_iCSCH) ;
    pi_mmio_set_high(m_iCSCH);//chipselect

    pi_mmio_set_output(m_iDataCH);
    pi_mmio_set_output(m_iClockCH) ;
    pi_mmio_set_output(m_iDCCH) ;
}
void Spi::Set(int iDataCH, int iClockCH, int iDCCH, int iCSCH)//konstruktor
{
    m_iDataCH=iDataCH;
    m_iClockCH=iClockCH;
    m_iDCCH=iDCCH;
    m_iCSCH=iCSCH;

    pi_mmio_init();

    pi_mmio_set_output(m_iCSCH) ;
    pi_mmio_set_high(m_iCSCH);//chipselect

    pi_mmio_set_output(m_iDataCH);
    pi_mmio_set_output(m_iClockCH) ;
    pi_mmio_set_output(m_iDCCH) ;
}




void Spi::send(char chByte, bool bDC)//funkcja wymaga przygotowanych pinow
{
    pi_mmio_set_low(m_iCSCH);//chipselect wybrany
    #ifdef DEBUG_SEND_1
    std::cout<<"cs down :";
    #endif//DEBUG_SEND_1
    //for(int i=0;i<1000;i++);
    if(bDC)//jesli DC bit to 1
        {
            pi_mmio_set_high(m_iDCCH);
            #ifdef DEBUG_SEND_1
            std::cout<<" -DC high- ";
            #endif//DEBUG_SEND_1
        }
        else//jestli DC bit to 0
        {
            pi_mmio_set_low(m_iDCCH);
            #ifdef DEBUG_SEND_1
                std::cout<<" -DC low- ";
            #endif//DEBUG_SEND_1
        }//end if
    for(int i=0;i<8;i++)
    {
        pi_mmio_set_low(m_iClockCH);//clock na 0
        //for(int i=0;i<1000;i++);
        if(chByte&0x80)//jesli najstarszy bit to 1 to wyslij 1
        {
            pi_mmio_set_high(m_iDataCH);
            #ifdef DEBUG_SEND_1
            std::cout<<"1";
            #endif//DEBUG_SEND_1
        }
        else//jestli najstarszy bit to 0 to wyslij 0
        {
            pi_mmio_set_low(m_iDataCH);
            #ifdef DEBUG_SEND_1
            std::cout<<"0";
            #endif//DEBUG_SEND_1
        }
        //for(int i=0;i<1000;i++);
        pi_mmio_set_high(m_iClockCH);//clock na 1, zapisanie zmiennej
        //for(int i=0;i<1000;i++);
        chByte=chByte<<1;//przesun bajt o jeden w lewo drugi d6 zostaje d7 i zostanie wyslany w nastepnym przejsciu
    }//end for(int i=0;i<8;i++)
    pi_mmio_set_high(m_iCSCH);
    #ifdef DEBUG_SEND_1
    std::cout<<" :cs up"<<std::endl;
    #endif//DEBUG_SEND_1
    //for(int i=0; i<10000;i++);
}
//---------------------LCDdriver-----------------------------------------------
    //konstruktor
LCDdriver::LCDdriver()
{
        for(int i=0;i<8;i++)
            for(int k=0;k<128;k++)
                chMatrix[i][k]=0;

        selected_spi.Set(SDATACH,SCLOCKCH, SDCCH,SCSCH);
}


//---------------------------------------------------------
void LCDdriver::Inicjalizacja()
{


    //pi_mmio_set_high(iDataCH); return;
    // Set display on--------------------------------------
    /*
    selected_spi.send(0xA8,0); selected_spi.send(0x3F,0); //set MUX ratio (pierwsze to komenda drugie to dane)
    selected_spi.send(0xD3,0); selected_spi.send(0x00,0); //Set display Offset 0
    selected_spi.send(0x40,0); //set start line to 0
    selected_spi.send(0xA0,0); // segment remap, zero=zero
    selected_spi.send(0xC0,0); //Set com output scan direction COM0->COM16
    selected_spi.send(0xDA,0); selected_spi.send(0x02,0); // COM pin hardwarde configuration
    selected_spi.send(0x81,0); selected_spi.send(0x8F,0); // Set contrast
    selected_spi.send(0xA4,0); //display on, clear ram
    selected_spi.send(0xA6,0); //1 in RAM means pixel turned ON
    selected_spi.send(0xD5,0); selected_spi.send(0x80,0); // set clock (i have no idea what i'm doing)
    selected_spi.send(0x8D,0); selected_spi.send(0x14,0); // enable bump charge
    selected_spi.send(0xAF,0); //display on
    //prepare to show data---------------------------------
    selected_spi.send(0x20,0); selected_spi.send(0x01,0); // Vertical adressing mode
    selected_spi.send(0x21,0);selected_spi.send(0x00,0);selected_spi.send(127,0); // Set column strart/end adress
    selected_spi.send(0x22,0);selected_spi.send(0xB0,0);selected_spi.send(0xB7,0); // set page start/end adress B nie ma znaczenia bo przyjmuje tlyko trzy ostatnie bity

    */
        selected_spi.send(0xA8,0); selected_spi.send(0x3F,0); //set MUX ratio (pierwsze to komenda drugie to dane)
    selected_spi.send(0xD3,0); selected_spi.send(0x00,0); //Set display Offset 0
    selected_spi.send(0x40,0); //set start line to 0
    selected_spi.send(0xA0,0); // segment remap, zero=zero
    selected_spi.send(0xC0,0); //Set com output scan direction COM0->COM16
    selected_spi.send(0xDA,0); selected_spi.send(0x12,0); // COM pin hardwarde configuration
    selected_spi.send(0x81,0); selected_spi.send(0x8F,0); // Set contrast
    selected_spi.send(0xA4,0); //display on, clear ram
    selected_spi.send(0xA6,0); //1 in RAM means pixel turned ON
    selected_spi.send(0xD5,0); selected_spi.send(0x80,0); // set clock (i have no idea what i'm doing)
    selected_spi.send(0x8D,0); selected_spi.send(0x14,0); // enable bump charge
    selected_spi.send(0xAF,0); //display on
    //prepare to show data---------------------------------
    selected_spi.send(0x20,0); selected_spi.send(0x01,0); // Vertical adressing mode
    selected_spi.send(0x21,0);selected_spi.send(0x00,0);selected_spi.send(127,0); // Set column strart/end adress
    selected_spi.send(0x22,0);selected_spi.send(0xB0,0);selected_spi.send(0xB7,0); // set page start/end adress B nie ma znaczenia bo przyjmuje tlyko trzy ostatnie bity

}

void  LCDdriver::turnOFF()
{
    selected_spi.send(0xAE,0);
}

void LCDdriver::sendscreen()
{
    int i=0,k=0;
    for( k=0;k<128;k++)
        for(i=0;i<8;i++)
            selected_spi.send(chMatrix[i][k],1);

}
char LCDdriver::byteread(int x, int yByte)// y from 0 to 7, x from 0 to 127
{
    return chMatrix[yByte][x];
}

bool LCDdriver::bitread(int x, int y)
{
    int iBitnumber= y-((y/8)*8);
    int iBytenumber= (x/8);
    return (chMatrix[iBytenumber][x]&(0x01<<iBitnumber));
}



void LCDdriver::overwritepixel(int x, int y,bool bValue)//numeracja jest od LEWEGO GORNEGO rogu od 0,0
{
    int iBitnumber= y-((y/8)*8);
    int iBytenumber= (y/8);
    if(bValue)// jezeli to ma byc jeden
        if (!(chMatrix[iBytenumber][x]& (0x01<<iBitnumber)))// jezeli ten bit ktrego szukamy aktualnie jest 0  to dodajemy tyle zeby w  to miejsce wskoczyla jedynka
            chMatrix[iBytenumber][x] += (0x01<<iBitnumber);
    if(!bValue)//jezeli to ma byc zero
        if (chMatrix[iBytenumber][x]& (0x01<<iBitnumber))// jezeli ten bit ktrego szukamy aktualnie jest 1 to musimy odjac ja
            chMatrix[iBytenumber][x]-=(0x01<<iBitnumber);
}

bool LCDdriver::ifdiffrence(LCDdriver kopy)
{
    bool bReturn=0;
    for(int i=0;i<8 && bReturn==false;i++)
            for(int k=0;k<128&&bReturn==false;k++)
                if(kopy.byteread(i,k)!=byteread(i,k))
                    bReturn=1;
    return bReturn;
}

void LCDdriver::puttext(int x, int y, FONT_INFO* pFont, char* pStr)
{
    char chBackground;
    char chCurrent;
    int Counter=0;//liczy ile bajtow z danego znaku zostalo wprowadzonych
    int Offset=0;
    int CharWidth=0;
    int FontheightFullBytes=pFont->CharacterHeight;
    int BitCharacterHeight=((pFont->CharacterHeight)*8);
    unsigned int iByteYmin= y/8; // to jestnajnizszy pelny byte w ktorym zawiera sie tekst
    unsigned int iByteYmax=iByteYmin+FontheightFullBytes -1; // najwyzszy pelny byte w ktoyrm zawiera sie tekst
    unsigned int iBitYmin= y-(iByteYmin*8);//pierwszy bit tekstuw najnizszym bajcie
    unsigned int iBitYmax= (y+BitCharacterHeight)-((iByteYmax+1)*8);//pierwszy bit nie-tekstu w najwyzszym bajcie
    if(y>(63-int(pFont->CharacterHeight)))
    {
        std::cout<<"not enough space {y}"<<std::endl;
        return;
    }


    while (*pStr!='\0')// '\0' to null
    {
        //idioto odpornosc--------------------
        if(*pStr<pFont->StartCharacter || *pStr>pFont->EndCharacter)
        {
        pStr++;
        continue;
        }

        if(x>123)
            return;
        //wlasciwa funkcja

        Counter=0;
        Offset=pFont->Descriptors[int(*pStr-pFont->StartCharacter)].Offset;
        CharWidth=pFont->Descriptors[int(*pStr-pFont->StartCharacter)].CharWidth;
        for(int i=0;i<CharWidth;i++)
        {
            unsigned int iByte=iByteYmin;//iByte to atkualna linia na ktorej sie znajdujemy

            if(0==iBitYmin)
            {
                if(0==iBitYmax)
                {
                    for(;iByte<=iByteYmax;iByte++)
                    {
                        chMatrix[iByte][x]=pFont->Bitmaps[Offset+Counter];

                        #ifdef DEBUG_1
                        std::cout<<" iBitYmin=0, iBitYmax=0, counter="<<Counter<<", iByte="<<iByte<<", iByteYmax ="<<iByteYmax<<", iByteYmin ="<<iByteYmin<<std::endl;
                        std::cout<<" x="<<x<<std::endl;
                        printf("pFont->Bitmaps[Offset+Counter] 0x%x\n",pFont->Bitmaps[Offset+Counter]);
                        printf("chMatrix[0][0] 0x%x\n",chMatrix[0][0]);
                        printf("chMatrix[1][0] 0x%x\n",chMatrix[1][0]);

                        #endif//DEBUG_1
                        Counter++;
                    }//for(;iByte<=iByteYmax;iByte++)
                }
                if(0!=iBitYmax)
                {
                    for(;iByte<iByteYmax;iByte++)//ostatni bajt osobno
                    {
                        chMatrix[iByte][x]=pFont->Bitmaps[Offset+Counter];
                        Counter++;
                    }//for(;iByte<iByteYmax;iByte++)
                    iByte++;
                    chBackground=byteread(x,iByte);
                    chBackground=(chBackground&(0xFF>>iBitYmax));//przypisz copy to co wystaje nad nasz tekst a temu co jest nizej przypisz 0
                    chMatrix[iByte][x]=(pFont->Bitmaps[Offset+Counter]|chBackground);
                    Counter++;
                }
            }
            //---------------------------------------------------------
            if(0!=iBitYmin)
            {
                for(int k=0;k<FontheightFullBytes;k++)
                {
                    //robimy ta dolna/starsza czesc rozbitego bajtu
                    chBackground=(chMatrix[iByte][x]&(0xFF<<(8-iBitYmin)));
                    chCurrent=((pFont->Bitmaps[Offset+Counter])&(0xFF>>iBitYmin));//przesuwamy o tyle ile zostaje nam wolnego miejsca w linijce po tekstem
                    chMatrix[iByte][x]=(chBackground|chCurrent);
                    iByte++;
                    //teraz ta gorna/mlodsza czesc rozbitego bajtu
                    chBackground=(chMatrix[iByte][x]&(0xFF>>iBitYmin));
                    chCurrent=(pFont->Bitmaps[Offset+Counter]&(0xFF<<(8-iBitYmin)));
                    chMatrix[iByte][x]=(chBackground|chCurrent);
                    Counter++;
                }
                /*
                if(iBitYmax>iBitYmin)//jesli pozostala reszta (ostatni nie pelny bajt) sie zmiesci na naszej aktualnej lini
                {
                    chBackground=(chMatrix[iByte][x]&(0xFF-((0xFF>>iBitYmin)-(0xFF>>iBitYmax))));//[xxxxxxxx]-([0000xxxx]-[000000xx])=[xxxx00xx] iBitYmin=4, iBitYmax=6

                    chCurrent=(pFont->Bitmaps[Offset+Counter]>>iBitYmin);//mozna tak zostawic bo  reszta to zera wiec w/e
                    chMatrix[iByte][x]=(chBackground|chCurrent);
                }
                if(iBitYmax<=iBitYmin)//jesli nie pelny bajt wyjdzie po za nasza aktualna linie, to traktujemy go jak pelny z tym ze musimy bardziej przesunac tlo
                {
                    chBackground=(chMatrix[iByte][x]&(0xFF<<(8-iBitYmin)));
                    chCurrent=(pFont->Bitmaps[Offset+Counter]>>iBitYmin);
                    chMatrix[iByte][x]=(chBackground|chCurrent);
                    iByte++;
                    chBackground=(chMatrix[iByte][x]&(0xFF>>iBitYmin));
                    chCurrent=(pFont->Bitmaps[Offset+Counter]<<(8-iBitYmin));
                    chMatrix[iByte][x]=(chBackground|chCurrent);
                    Counter++;
                }//endif
                */








            }

            x++;
        }//for(int i=0;i<CharWidth;i++)


        /*
        else;
            for(int iByte=iBytemin;iByte<=iByteYmax;i++)//ostatni bajt zostoanie zrobiony osobno
                {
                    chBackground;
                }

        */
        pStr++;
        /*for(int kl;kl<iGap;kl++)
        {
            for(int l=0;l<FontheightFullBytes;l++)
            {
                chMatrix[]
            }
        }*/
        int iByte2=iByteYmin;
        for(int k=0;k<FontheightFullBytes;k++)
        {
            chMatrix[iByte2][x]=0;

        }
        x++;
    }
}
//===============================
void LCDdriver::DRAWpoint(int x,int y, bool pixel)
{
    int iByte=y/8;
    int iBit=y-(iByte*8);
    char chBackground=0;
    chBackground=(chMatrix[iByte][x]&(0xFF-(0x01<<iBit)));//background bez bitu o numerze iBit(ten bit jest 0)
    if(pixel)
        chMatrix[iByte][x]=chBackground+(0x01<<iBit);
    else
        chMatrix[iByte][x]=chBackground;
    return;
}
int round(float fIn)
{
    int iIpart=0;
    iIpart=int(fIn);
    fIn-=iIpart;
    if(fIn<0.5)
        return iIpart;
    else
        return (iIpart+1);
}
//===============================
void LCDdriver::DRAWline(int xF,int yF, int xS, int yS)
{
    int iStash=0;
    int iDistX=0;
    int iDistY=0;
    int iDist=0;
    int iX=0;
    int iY=0;
    float fX=0;
    float fY=0;
    float fStepX=0;
    float fStepY=0;
    //yF ma byc mniejszy od yS bo idziem od lewej, analogicznie zamieniam x zeby linia nie wyszla mi w druga strone
    if(yF>yS)
    {
        iStash=yS;
        yS=yF;
        yF=iStash;
        iStash=xS;
        xS=xF;
        xF=iStash;
        iStash=0;
    }
    iDistY=yS-yF;
    iDistX=xS-xF;
    if(iDistX<0){iDistX=((-1)*(iDistX));} //wartosc bezwzgledna z iDistX
    if(iDistX>iDistY)
        iDist=iDistX;
    else
        iDist=iDistY;

    if(0==iDist)
    {
        DRAWpoint(xF,yF,1);
        return;
    }
    //else
    fStepX=float(iDistX)/float(iDist);
    fStepY=float(iDistY)/float(iDist);
    iX=xF;
    iY=yF;
    fX=float(iX);
    fY=float(iY);
    for(int i=0;i<=iDist;i++)
    {
        DRAWpoint(round(fX),round(fY),1);
        fX+=fStepX;
        fY+=fStepY;
    }




}





















































