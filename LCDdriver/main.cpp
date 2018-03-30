#include "LCDdriver.h"
#include "pi_mmio.h"
#include <iostream>



int main()
{
    char null;
    int input=0;
    LCDdriver lcd;
    lcd.Inicjalizacja();
    /*
    for (int i=0; i< 15;i++)
    {
        sleep(1);
        lcd.turnOFF(spi);
        sleep(1);
        spi.send(0xAF,0);//display on
    }
    sleep(1);
    for(int i=0; i<16;i++)
        spi.send(i,1);
    lcd.turnOFF(spi);
    */
    //sleep(2);
    //std::cin>>input;
    /*
    for(int i=0;i<8;i++)
    {
        for(int k=0;k<128;k++)
            lcd.chMatrix[i][k] =input;
    }
    lcd.sendscreen();




    std::cin>>input;
    for(int i=0; i<1023;i++)
    {
        lcd.selected_spi.send(char(input), 1);
        //sleep(1);
    }

    //lcd.selected_spi.send(0x01, 1);
    */
    lcd.DRAWline(127,3,0,0);
    //lcd.puttext(0,0,&arial_10ptFontInfo,"Dupsko hahahaha");
    //lcd.chMatrix[0][0]=1;





    lcd.sendscreen();
    //for(int i=0;i<16;i++)
      //  lcd.selected_spi.send(0x01,1);
    pi_mmio_set_low(SDATACH);
    pi_mmio_set_low(SCLOCKCH);
    pi_mmio_set_low(SDCCH);
    pi_mmio_set_low(SCSCH);
    /*for(int k=0;k<10;k++)
    {
        std::cout<<10-k<<std::endl;
        sleep(1);
    }
    */

    std::cout<<"char to exit"<<std::endl;
    std::cin>>null;
    lcd.turnOFF();
    return 0;
}
