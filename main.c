/*
 * File:   main.c
 * Author: User
 *
 * Created on 31 January 2024, 14:59
 */


#include <xc.h>
#include <stdio.h>
#include "constVar.h"
#include "configOsc.h"
#include "configEUSART.h"
#include "putch.h"
#include "configPORTS.h"
#include "configSPI.h"
#include "configADC.h"
#include "writeSPIcommand.h"
#include "writeSPIdata.h"
#include "configSSD1309.h"
#include "clearSSD1309.h"
#include "getYposition.h"
#include "setColAddr.h"
#include "drawPixel.h"
#include "drawArray.h"
#include "rightScroll.h"
#include "interrupt.h"
#include "configTMR0interrupt.h"
#include "setMemoryAddressingMode.h"

void main(void) 
{
    
    configOsc();
    configPORTS();
    configEUSART();
    configSPI();
    configADC();
    
    
    configSSD1309();
    __delay_ms(1000);
    clearSSD1309();
    
    
    pix *ptr;
    pix var;
    ptr = &var;
    ptr->yVal = 45;
    //var.yVal = 1;
    //var.yVal = 37;
    //or
   // ptr->yVal = 8;
    //ptr->yByte = 0xfa;
    //ptr->page = 7;
    //printf("main getPixelPosition %d     %d\n", ptr->yByte, ptr->page);
    getYposition(&var);
    printf("second main getPixelPosition %d     %d\n", ptr->yByte, ptr->page); 
   // printf("sizeof %d\n", sizeof(newQuad));//768
   
    /*drawPixel(64,32);
    drawPixel(10,7);
    drawPixel(117,7);
    drawPixel(117,53);
    drawPixel(10,53);*/
    
    drawArray();
   // rightScroll();
    __delay_ms(1500);
    clearSSD1309();
    configTMR0interrupt();
    drawPixel(0,0);
    drawPixel(127,0);
    drawPixel(0,63);
    drawPixel(127,63);
     __delay_ms(500);
    uint8_t angle = 45;
    int16_t opposite = 0;
    int16_t adjacent = 0;
    uint8_t ycoord = 0;
    uint8_t xcoord = 0;
    //uint8_t x, y;
    uint8_t rad = 63;
    clearSSD1309();
    
    
    while(1)
   
        {
        ADCON0bits.GO_nDONE = HI;
        while(ADCON0bits.GO_nDONE == HI)
        {
          ;  // wait for adc conversion to complete
        }
        adcVal =  (ADRESH<<8|ADRESL) + 1;
        PIR1bits.ADIF = LO;
        
           /******needle clamping at lower and upper ranges*/
        if(adcVal <=30)
        {
            adcVal = 30;
        }
        
         if(adcVal >=150)
        {
            adcVal = 150;
        }
       
        for(rad = 0; rad < 64; rad++)
        {
            opposite = (uint16_t)sineLookUp[adcVal] * (uint16_t)rad;
            adjacent = (uint16_t)cosineLookUp[adcVal] * (uint16_t)rad;
        
        
        ycoord = (uint8_t)(opposite>>8)+ 61;
        xcoord = (uint8_t)(adjacent>>8)-4;
      
        drawPixel(ycoord, xcoord);
        }     
    }
}
           
       
    
   

  

