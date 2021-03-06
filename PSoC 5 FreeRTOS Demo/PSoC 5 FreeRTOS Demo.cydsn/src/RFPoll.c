#include <project.h>
#include <protocol.h>
#include <variables.h>
#include <RFPoll.h>
#include <LCD.h>
#include <I2C.h>
#include "Printing.h"
#include <device.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* RTOS includes. */
#include <FreeRTOS.h>
#include <semphr.h>
#include "os_resource.h"

extern xSemaphoreHandle g_pUARTSemaphore;
uint8_t lengthPrint;

void RFTotalA(void)
{
    uint16 x,y,z;
    
    for(x = 0; x < 100; x ++)
    {
        buffer_txTotals[x] = 0x00;        
    }
    
        pollTotals = 0;
        y = 0;
        buffer_txTotals[y] = 0xBC; y++;
        buffer_txTotals[y] = 0xCB; y++;
        buffer_txTotals[y] = 0xC8; y++;
        buffer_txTotals[y] = IDCast[0]; y++;
        buffer_txTotals[y] = IDCast[1]; y++;
        buffer_txTotals[5] = side.a.dir; y++;
        buffer_txTotals[y] = 0xE8; y++;
        buffer_txTotals[y] = side.a.rfState; y++;
        buffer_txTotals[y] = 0x00; y++;
        
        for(z = 1;z <= side.a.hoseNumber; z++)
        {
            buffer_txTotals[y] = z; y++;                    
            if (digits == 6 || digits == 5)
            {                            
                for(x = 8; x > 0; x--)
                {  
                    //Volumen
                    buffer_txTotals[y] = (side.a.totalsHandle[z - 1][0][x]) - 48; y++;
                }
                for(x =0; x < 4; x++)
                {
                    buffer_txTotals[y] = 0x00; y++;
                }
                for(x = 8; x > 0; x--)
                {  
                    //Dinero
                    buffer_txTotals[y] = (side.a.totalsHandle[z - 1][1][x]) - 48; y++;
                }
                for(x =0; x < 4; x++)
                {
                    buffer_txTotals[y] = 0x00; y++;
                }
            }
            else{
                for(x = 12; x > 0; x--)
                { 
                    //Volumen              
                    buffer_txTotals[y] = (side.a.totalsHandle[z - 1][0][x]) - 48; y++;
                }                        
                for(x = 12; x > 0; x--)
                { 
                    //Dinero
                    buffer_txTotals[y] = (side.a.totalsHandle[z - 1][1][x]) - 48; y++;
                }                        
            } 
        }
        buffer_txTotals[8] = y - 9;
        buffer_txTotals[y] = verificar_check(buffer_txTotals,y + 1);y++;                 
        
        for (x = 0; x < y; x++)
        {
            RF_Connection_PutChar(buffer_txTotals[x]);
        }        
       
    bufferAready = 0; 
    FlagTotal = 0;
    pollTotals = 0;
    return;
}

void RFTotalB(void)
{
    uint16 x,y,z;
    for(x = 0; x < 100; x ++)
    {
        buffer_txTotals[x] = 0x00;        
    }
    
        pollTotals = 0;
        y = 0;
        buffer_txTotals[y] = 0xBC; y++;
        buffer_txTotals[y] = 0xCB; y++;
        buffer_txTotals[y] = 0xC8; y++;
        buffer_txTotals[y] = IDCast[0]; y++;
        buffer_txTotals[y] = IDCast[1]; y++;
        buffer_txTotals[5] = side.b.dir; y++;
        buffer_txTotals[y] = 0xE8; y++;
        buffer_txTotals[y] = side.b.rfState; y++;
        buffer_txTotals[y] = 0x00; y++;
        for(z = 1; z <= side.b.hoseNumber; z++)
        {
            buffer_txTotals[y] = z; y++;                    
            if (digits == 6 || digits == 5)
            {   
                //Volumen
                for(x = 8; x > 0; x--)
                { 
                    buffer_txTotals[y] = (side.b.totalsHandle[z - 1][0][x]) - 48; y++;
                }
                for(x = 0; x < 4; x++)
                {
                    buffer_txTotals[y] = 0x00; y++;
                }
                for(x = 8; x > 0; x--)
                {//Dinero
                    buffer_txTotals[y] = (side.b.totalsHandle[z - 1][1][x]) - 48; y++;
                }
                for(x = 0; x < 4; x++)
                {
                    buffer_txTotals[y] = 0x00; y++;
                }
            }else
            {
                 //Volumen
                for(x = 12; x > 0; x--)
                {
                    buffer_txTotals[y] = (side.b.totalsHandle[z - 1][0][x]) - 48; y++;
                }     
                
                //Dinero
                for(x = 12; x > 0; x--)
                {
                    buffer_txTotals[y] = (side.b.totalsHandle[z - 1][1][x]) - 48; y++;
                }                        
            } 
        }
        buffer_txTotals[8] = y - 9;
        buffer_txTotals[y] = verificar_check(buffer_txTotals,y + 1);y++;                 
        
        for (x = 0; x < y; x++)
        {
            RF_Connection_PutChar(buffer_txTotals[x]);
        }        
        side.b.RFstateReport = 0;
        bufferAreadyB = 0; 
        FlagTotalB = 0;
        pollTotals = 0;
        return;
       
    }    
    
void RFTotalC(void)
{
    uint16 x,y,z;
    for(x = 0; x < 100; x ++)
    {
        buffer_txTotals[x] = 0x00;        
    }

        pollTotals = 0;
        y = 0;
        buffer_txTotals[y] = 0xBC; y++;
        buffer_txTotals[y] = 0xCB; y++;
        buffer_txTotals[y] = 0xC8; y++;
        buffer_txTotals[y] = IDCast[0]; y++;
        buffer_txTotals[y] = IDCast[1]; y++;
        buffer_txTotals[5] = side.c.dir; y++;
        buffer_txTotals[y] = 0xE8; y++;
        buffer_txTotals[y] = side.c.rfState; y++;
        buffer_txTotals[y] = 0x00; y++;
        
        for(z = 1;z <= side.c.hoseNumber; z++)
        {
            buffer_txTotals[y] = z; y++;                    
            if (digits == 6 || digits == 5)
            {                            
                for(x = 8; x > 0; x--)
                {  
                    //Volumen
                    buffer_txTotals[y] = (side.c.totalsHandle[z - 1][0][x]) - 48; y++;
                }
                for(x =0; x < 4; x++)
                {
                    buffer_txTotals[y] = 0x00; y++;
                }
                for(x = 8; x > 0; x--)
                {  
                    //Dinero
                    buffer_txTotals[y] = (side.c.totalsHandle[z - 1][1][x]) - 48; y++;
                }
                for(x =0; x < 4; x++)
                {
                    buffer_txTotals[y] = 0x00; y++;
                }
            }else{
                for(x = 12; x > 0; x--)
                { 
                    //Volumen              
                    buffer_txTotals[y] = (side.c.totalsHandle[z - 1][0][x]) - 48; y++;
                }                        
                for(x = 12; x > 0; x--)
                { 
                    //Dinero
                    buffer_txTotals[y] = (side.c.totalsHandle[z - 1][1][x]) - 48; y++;
                }                        
            } 
        }
        buffer_txTotals[8] = y - 9;
        buffer_txTotals[y] = verificar_check(buffer_txTotals,y + 1);y++;                 
        
        for (x = 0; x < y; x++)
        {
            RF_Connection_PutChar(buffer_txTotals[x]);
        }        
       
    bufferAreadyC = 0; 
    FlagTotalC = 0;
    pollTotals = 0;
    return;
}

void RFTotalD(void)
{
    uint16 x,y,z;
    for(x = 0; x < 100; x ++)
    {
        buffer_txTotals[x] = 0x00;        
    }
    
        pollTotals = 0;
        y = 0;
        buffer_txTotals[y] = 0xBC; y++;
        buffer_txTotals[y] = 0xCB; y++;
        buffer_txTotals[y] = 0xC8; y++;
        buffer_txTotals[y] = IDCast[0]; y++;
        buffer_txTotals[y] = IDCast[1]; y++;
        buffer_txTotals[5] = side.d.dir; y++;
        buffer_txTotals[y] = 0xE8; y++;
        buffer_txTotals[y] = side.d.rfState; y++;
        buffer_txTotals[y] = 0x00; y++;
        for(z = 1; z <= side.d.hoseNumber; z++)
        {
            buffer_txTotals[y] = z; y++;                    
            if (digits == 6 || digits == 5)
            {   
                //Volumen
                for(x = 8; x > 0; x--)
                { 
                    buffer_txTotals[y] = (side.d.totalsHandle[z - 1][0][x]) - 48; y++;
                }
                for(x = 0; x < 4; x++)
                {
                    buffer_txTotals[y] = 0x00; y++;
                }
                for(x = 8; x > 0; x--)
                {//Dinero
                    buffer_txTotals[y] = (side.d.totalsHandle[z - 1][1][x]) - 48; y++;
                }
                for(x = 0; x < 4; x++)
                {
                    buffer_txTotals[y] = 0x00; y++;
                }
            }else
            {
                 //Volumen
                for(x = 12; x > 0; x--)
                {
                    buffer_txTotals[y] = (side.d.totalsHandle[z - 1][0][x]) - 48; y++;
                }     
                
                //Dinero
                for(x = 12; x > 0; x--)
                {
                    buffer_txTotals[y] = (side.d.totalsHandle[z - 1][1][x]) - 48; y++;
                }                        
            } 
        }
        buffer_txTotals[8] = y - 9;
        buffer_txTotals[y] = verificar_check(buffer_txTotals,y + 1);y++;                 
        
        for (x = 0; x < y; x++)
        {
            RF_Connection_PutChar(buffer_txTotals[x]);
        }        
        side.d.RFstateReport = 0;
        bufferAreadyD = 0; 
        FlagTotalD = 0;
        pollTotals = 0;
        return;
       
    }

/*
*********************************************************************************************************
*                             uint8 verificar_check(uint8 *datos, uint16 size)
*
* Description : calcula el checksum
*               

*********************************************************************************************************
*/
uint8 verificar_check(uint8 *datos, uint16 size){
	uint8 checksum,index; 
	uint16 i;
    uint8 table[256] = { 
    0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
    157,195, 33,127,252,162, 64, 30, 95,  1,227,189, 62, 96,130,220,
    35,125,159,193, 66, 28,254,160,225,191, 93,  3,128,222, 60, 98,
    190,224,  2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
    70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89,  7,
    219,133,103, 57,186,228,  6, 88, 25, 71,165,251,120, 38,196,154,
    101, 59,217,135,  4, 90,184,230,167,249, 27, 69,198,152,122, 36,
    248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91,  5,231,185,
    140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
    17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
    175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
    50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
    202,148,118, 40,171,245, 23, 73,  8, 86,180,234,105, 55,213,139,
    87,  9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
    233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
    116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53};	
	checksum=0;
	for(i = 0; i < (size - 1);i++)
    {
		index = (uint8)(checksum ^ datos[i]);
		checksum = table[index];				
	}
	return checksum;
}


void pollingRF_Rx(uint8 PRF_rxBuffer[])
{
    uint16  x, y;      
    uint8 EEpromGradeAddress;
   
    ActiveRF = 1;
    counterRF = 0;   
    y = 0;
    buffer_tx[y] = 0xBC; y++;
    buffer_tx[y] = 0xCB; y++;
    buffer_tx[y] = 0xC8; y++;
    buffer_tx[y] = IDCast[0]; y++;
    buffer_tx[y] = IDCast[1]; y++;
        
        // Query Command Action
        if(((PRF_rxBuffer[0] == 0xBC) && (PRF_rxBuffer[1] == 0xBB) && (PRF_rxBuffer[2] == 0xB8) && (PRF_rxBuffer[3] == IDCast[0]) && (PRF_rxBuffer[4] == IDCast[1])) )
        {                  
            switch(PRF_rxBuffer[6])
            {
               case 0xA1:                  // Status
                // Position 1
                if(PRF_rxBuffer[5] == side.a.dir)                  
                {   
                    //Zero sale
                    if(bufferDisplay1.zeroSend  == 1){
                            side.a.rfState = RF_ZERO_SALE;
                            bufferDisplay1.zeroSend = 0;
                        }
                    // Idle state
                    if(bufferAready == 0 && FlagTotal == 0)
                    {                          
                        buffer_tx[5] = side.a.dir; y++;
                        buffer_tx[y] = 0xA1; y++;
                        buffer_tx[y] = side.a.rfState; y++;
                        buffer_tx[y] = verificar_check(buffer_tx,y+1); y++;
                                                        
                        /*Send Data */
                        for (x = 0; x < y; x++)
                        {
                            RF_Connection_PutChar(buffer_tx[x]);
                        }  
                    }
                    
                    // Preset or End Sale
                    if(bufferAready == 1)
                    {                                                                    
                        for (x = 1; x < buffer_A[0]; x++)
                        { 
                            RF_Connection_PutChar(buffer_A[x]);
                        }                       
                        bufferAready = 0;
                        DeliveryStateA = 0;
                          
                    }
                    
                    // Authorization Request
                    if(bufferAready == 2)
                    {                                                             
                        for (x = 0; x < 37; x++)
                        { 
                            RF_Connection_PutChar(buffer_A[x]);
                        }
                        bufferAready = 0;
                        side.a.rfState = RF_CREDITSALEAUTH;
                    }
                    
                    // Authorization Request ACK
                    if(bufferAready == 3)
                    {                                                             
                        for (x = 0; x < 10; x++)
                        { 
                            RF_Connection_PutChar(buffer_A[x]);
                        }
                        bufferAready = 0;
                        AckFlag = 0;
                    }                   
                    
                    // Total
                    if(bufferAready == 0 && FlagTotal == 1)
                    {                                           
                        RFTotalA();
                        bufferAready = 0;
                        FlagTotal = 0;
                        pollTotals = 0;
                        
                    }      
                }
                
                // Position 2
                if(PRF_rxBuffer[5] == side.b.dir)
                {
                    if(bufferDisplay2.zeroSend  == 1){
                        side.b.rfState = RF_ZERO_SALE;
                        bufferDisplay2.zeroSend = 0;
                    }
                    if(bufferAreadyB == 0 && FlagTotalB == 0)
                    {                        
                        buffer_tx[5] = side.b.dir; y++;
                        buffer_tx[y] = 0xA1; y++;
                        buffer_tx[y] = side.b.rfState;y++;
                        buffer_tx[y] = verificar_check(buffer_tx,y+1);y++;
                        for (x = 0; x < y; x++)
                        {
                            RF_Connection_PutChar(buffer_tx[x]);
                        }
                    }
                    
                    // Si el estado es PRESET o Fin Venta
                    if(bufferAreadyB == 1)
                    {                                                                   
                        for (x = 0; x < buffer_B[100]; x++)
                        {
                            RF_Connection_PutChar(buffer_B[x]);         
                        }
                     
                        bufferAreadyB = 0;
                        DeliveryStateB = 0;
                    }
                    
                    // Authorization Request
                    if(bufferAreadyB == 2)
                    {                                                             
                        for (x = 0; x < 37; x++)
                        { 
                            RF_Connection_PutChar(buffer_B[x]);
                        }
                        bufferAreadyB = 0;
                        side.b.rfState = RF_CREDITSALEAUTH;
                        
                    }
                                                                                              
                    // Totales
                    if(bufferAreadyB == 0 && FlagTotalB == 1)
                    {                                           
                        RFTotalB(); 
                        bufferAreadyB = 0;
                        FlagTotalB = 0;
                        pollTotals = 0;
                    }           
                }
                
                // Position 3
                if(PRF_rxBuffer[5] == side.c.dir)                  
                {
                    if(bufferDisplay3.zeroSend  == 1){
                        side.c.rfState = RF_ZERO_SALE;
                        bufferDisplay3.zeroSend = 0;
                    }
                    // Idle state
                    if(bufferAreadyC == 0 && FlagTotalC == 0)
                    {                         
                        buffer_tx[5] = side.c.dir; y++;
                        buffer_tx[y] = 0xA1; y++;
                        buffer_tx[y] = side.c.rfState; y++;
                        buffer_tx[y] = verificar_check(buffer_tx, y + 1); y++;
                                                        
                        /*Send Data */
                        for (x = 0; x < y; x++)
                        {
                            RF_Connection_PutChar(buffer_tx[x]);
                        }  
                        
                    }
                    
                    // Preset or End Sale
                    if(bufferAreadyC == 1)
                    {                                                                    
                        for (x = 1; x < buffer_C[0]; x++)
                        { 
                            RF_Connection_PutChar(buffer_C[x]);
                        }                       
                        bufferAreadyC = 0;
                        DeliveryStateC = 0;
                    }
                    
                    // Authorization Request
                    if(bufferAreadyC == 2)
                    {                                                             
                        for (x = 0; x < 37; x++)
                        { 
                            RF_Connection_PutChar(buffer_C[x]);
                        }
                        bufferAreadyC = 0;
                        side.c.rfState = RF_CREDITSALEAUTH;
                    }
                    
                    // Authorization Request ACK
                    if(bufferAreadyC == 3)
                    {                                                             
                        for (x = 0; x < 10; x++)
                        { 
                            RF_Connection_PutChar(buffer_C[x]);
                        }
                        bufferAreadyC = 0;
                        AckFlag = 0;
                    }                   
                    
                    // Total
                    if(bufferAreadyC == 0 && FlagTotalC == 1)
                    {                                           
                        RFTotalC();
                        bufferAreadyC = 0;
                        FlagTotalC = 0;
                        pollTotals = 0;
                        
                    }      
                }
                
                // Position 4
                if(PRF_rxBuffer[5] == side.d.dir)                  
                {
                    if(bufferDisplay4.zeroSend  == 1){
                        side.d.rfState = RF_ZERO_SALE;
                        bufferDisplay4.zeroSend = 0;
                    }
                    // Idle state
                    if(bufferAreadyD == 0 && FlagTotalD == 0)
                    {                        
                        buffer_tx[5] = side.d.dir; y++;
                        buffer_tx[y] = 0xA1; y++;
                        buffer_tx[y] = side.d.rfState; y++;
                        buffer_tx[y] = verificar_check(buffer_tx,y+1); y++;
                                                        
                        /*Send Data */
                        for (x = 0; x < y; x++)
                        {
                            RF_Connection_PutChar(buffer_tx[x]);
                        }  
                    }
                    
                    // Preset or End Sale
                    if(bufferAreadyD == 1)
                    {                                                                    
                        for (x = 1; x < buffer_D[0]; x++)
                        { 
                            RF_Connection_PutChar(buffer_D[x]);
                        }                       
                        bufferAreadyD = 0;
                        DeliveryStateD = 0;
                    }
                    
                    // Authorization Request
                    if(bufferAreadyD == 2)
                    {                                                             
                        for (x = 0; x < 37; x++)
                        { 
                            RF_Connection_PutChar(buffer_D[x]);
                        }
                        bufferAreadyD = 0;
                        side.d.rfState = RF_CREDITSALEAUTH;
                    }
                    
                    // Authorization Request ACK
                    if(bufferAreadyD == 3)
                    {                                                             
                        for (x = 0; x < 10; x++)
                        { 
                            RF_Connection_PutChar(buffer_D[x]);
                        }
                        bufferAreadyD = 0;
                        AckFlag = 0;
                    }                   
                    
                    // Total
                    if(bufferAreadyD == 0 && FlagTotalD == 1)
                    {                                           
                        RFTotalD();
                        bufferAreadyD = 0;
                        FlagTotalD = 0;
                        pollTotals = 0;
                        
                    }      
                }
             
                RF_Connection_ClearRxBuffer(); 
                break;
                
                case 0xA3:               //Credit Authorization Response
                    if(PRF_rxBuffer[5] == side.a.dir)
                    {
                        if(PRF_rxBuffer[8] == 0x01)
                        {                                                                 
                            // PPU                                                        
                            for(x = 19; x < 24 ; x++ )
                            {
                                ppuiButtonA[x - 19] = PRF_rxBuffer[x];                            
                            } 
                       
                            for(x = 0; x < 5 ; x++ )
                            {
                                if(ppuiButtonA[x] == 0x00)
                                { 
                                    ppuiButtonA[x] = '0';
                                }                                
                            }
                            
                            bufferDisplay1.CreditpresetType[0]= 2;
                            bufferDisplay1.CreditpresetType[1]= 'D';
                            for(x= 16; x > 8; x-- )
                            {
                                if(PRF_rxBuffer[x] != 0x00)
                                {
                                    bufferDisplay1.CreditpresetValue[0][0]= 8-(16-x);
                                    bufferDisplay1.CreditpresetValue[1][0]= 8-(16-x);
                                    break;
                                }
                            }
                            
                            for(x = 0; x < bufferDisplay1.CreditpresetValue[0][0] ; x++)
                            {
                                bufferDisplay1.CreditpresetValue[0][x + 1] = PRF_rxBuffer[(bufferDisplay1.CreditpresetValue[0][0]-x)+8];
                                bufferDisplay1.CreditpresetValue[1][x + 1] = PRF_rxBuffer[(bufferDisplay1.CreditpresetValue[0][0]-x)+8];                                
                            }
                            
                           
                            //Grade
                            side.a.grade = PRF_rxBuffer[18];
                            
                            buffer_A[0]  = 0xBC;
                            buffer_A[1]  = 0xCB;
                            buffer_A[2]  = 0xC8;
                            buffer_A[3]  = IDCast[0];
                            buffer_A[4]  = IDCast[1];
                            buffer_A[5]  = side.a.dir;
                            buffer_A[6]  = 0xA7;
                            buffer_A[7]  = RF_IDLE;
                            buffer_A[8]  = ACK;
                            buffer_A[9]  = buffer_A[36] = verificar_check(buffer_A, 9);
                            
                            for (x = 0; x < 10; x++)
                            { 
                                RF_Connection_PutChar(buffer_A[x]);
                            }
                            
                            Credit_Auth_OK = 1;
                            bufferAready = 0; 
                            PresetFlag = 1;
                            AuthType = 1;
                            side.a.BusyChange = 1;
                        }
                        else
                        {                           
                            PresetFlag = 0;
                            iButtonFlag = 0;                           
                            AckFlag = 1;
                            CreditAuth = 0;
                            Credit_Auth_OK = 0;
                            bufferAready = 0;
                            bufferDisplay1.flagPrint = 0;
                            buffer_A[0]  = 0xBC;
                            buffer_A[1]  = 0xCB;
                            buffer_A[2]  = 0xC8;
                            buffer_A[3]  = IDCast[0];
                            buffer_A[4]  = IDCast[1];
                            buffer_A[5]  = side.a.dir;
                            buffer_A[6]  = 0xA7;
                            buffer_A[7]  = RF_IDLE;
                            buffer_A[8]  = ACK;
                            buffer_A[9]  = buffer_A[36] = verificar_check(buffer_A, 9);
                            
                            for (x = 0; x < 10; x++)
                            { 
                                RF_Connection_PutChar(buffer_A[x]);
                            }
                            flowDisplay1 = 21;
                                                                           
                        }
                    } 
                    
                    if(PRF_rxBuffer[5] == side.b.dir)
                    {
                        if(PRF_rxBuffer[8] == 0x01)
                        {                           
                            // PPU
                            for(x = 19; x < 24 ; x++ )
                            {
                                ppuiButtonB[x - 19] = PRF_rxBuffer[x];                            
                            }  
                            
                            for(x = 0; x < 5 ; x++ )
                            {
                                if(ppuiButtonB[x] == 0x00)
                                { 
                                    ppuiButtonB[x] = '0';
                                }
                                
                            }
                            
                            //Preset
                            bufferDisplay2.CreditpresetType[0]= 2;
                            bufferDisplay2.CreditpresetType[1]= 'D';
                            for(x= 16; x > 8; x-- )
                            {
                                if(PRF_rxBuffer[x] != 0x00)
                                {
                                    bufferDisplay2.CreditpresetValue[0][0]= 8-(16-x);
                                    bufferDisplay2.CreditpresetValue[1][0]= 8-(16-x);
                                    break;
                                }
                            }
                            
                            for(x = 0; x < bufferDisplay2.CreditpresetValue[0][0] ; x++)
                            {
                                bufferDisplay2.CreditpresetValue[0][x + 1] = PRF_rxBuffer[(bufferDisplay2.CreditpresetValue[0][0]-x)+8];
                                bufferDisplay2.CreditpresetValue[1][x + 1] = PRF_rxBuffer[(bufferDisplay2.CreditpresetValue[0][0]-x)+8];                                
                            }
                            //Grade
                            side.b.grade = PRF_rxBuffer[18];
                            
                            buffer_B[0]  = 0xBC;
                            buffer_B[1]  = 0xCB;
                            buffer_B[2]  = 0xC8;
                            buffer_B[3]  = IDCast[0];
                            buffer_B[4]  = IDCast[1];
                            buffer_B[5]  = side.b.dir;
                            buffer_B[6]  = 0xA7;
                            buffer_B[7]  = RF_IDLE;
                            buffer_B[8]  = ACK;
                            buffer_B[9]  = buffer_B[36] = verificar_check(buffer_B, 9);
                            
                            for (x = 0; x < 10; x++)
                            { 
                                RF_Connection_PutChar(buffer_B[x]);
                            }
                           
                            Credit_Auth_OK2 = 1;
                            bufferAreadyB = 0;
                            PresetFlag2 = 1; 
                            AuthType2 = 1;
                            side.b.BusyChange = 1;                           
                        }
                        else
                        {
                           
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;                           
                            AckFlag2 = 1;
                            CreditAuth2 = 0;
                            Credit_Auth_OK2 = 0;
                            bufferAreadyB = 0;
                            bufferDisplay2.flagPrint = 0;
                            buffer_B[0]  = 0xBC;
                            buffer_B[1]  = 0xCB;
                            buffer_B[2]  = 0xC8;
                            buffer_B[3]  = IDCast[0];
                            buffer_B[4]  = IDCast[1];
                            buffer_B[5]  = side.b.dir;
                            buffer_B[6]  = 0xA7;
                            buffer_B[7]  = RF_IDLE;
                            buffer_B[8]  = ACK;
                            buffer_B[9]  = buffer_B[36] = verificar_check(buffer_B, 9);
                            for (x = 0; x < 10; x++)
                            { 
                                RF_Connection_PutChar(buffer_B[x]);
                            }    
                            flowDisplay2 = 21;
                        }
                    } 
                    
                    if(PRF_rxBuffer[5] == side.c.dir)
                    {
                        if(PRF_rxBuffer[8] == 0x01)
                        {                                                                 
                            // PPU                                                        
                            for(x = 19; x < 24 ; x++ )
                            {
                                ppuiButtonA[x - 19] = PRF_rxBuffer[x];                            
                            } 
                       
                            for(x = 0; x < 5 ; x++ )
                            {
                                if(ppuiButtonA[x] == 0x00)
                                { 
                                    ppuiButtonA[x] = '0';
                                }                                
                            }
                            
                            bufferDisplay3.CreditpresetType[0]= 2;
                            bufferDisplay3.CreditpresetType[1]= 'D';
                            for(x= 16; x > 8; x-- )
                            {
                                if(PRF_rxBuffer[x] != 0x00)
                                {
                                    bufferDisplay3.CreditpresetValue[0][0]= 8-(16-x);
                                    bufferDisplay3.CreditpresetValue[1][0]= 8-(16-x);
                                    break;
                                }
                            }
                            
                            for(x = 0; x < bufferDisplay3.CreditpresetValue[0][0] ; x++)
                            {
                                bufferDisplay3.CreditpresetValue[0][x + 1] = PRF_rxBuffer[(bufferDisplay3.CreditpresetValue[0][0]-x)+8];
                                bufferDisplay3.CreditpresetValue[1][x + 1] = PRF_rxBuffer[(bufferDisplay3.CreditpresetValue[0][0]-x)+8];                                
                            }
                            
                           
                            //Grade
                            side.c.grade = PRF_rxBuffer[18];
                            
                            buffer_C[0]  = 0xBC;
                            buffer_C[1]  = 0xCB;
                            buffer_C[2]  = 0xC8;
                            buffer_C[3]  = IDCast[0];
                            buffer_C[4]  = IDCast[1];
                            buffer_C[5]  = side.d.dir;
                            buffer_C[6]  = 0xA7;
                            buffer_C[7]  = RF_IDLE;
                            buffer_C[8]  = ACK;
                            buffer_C[9]  = buffer_C[36] = verificar_check(buffer_C, 9);
                            
                            for (x = 0; x < 10; x++)
                            { 
                                RF_Connection_PutChar(buffer_C[x]);
                            }
                            
                            Credit_Auth_OK3 = 1;
                            bufferAreadyC = 0; 
                            PresetFlag3 = 1;
                            AuthType3 = 1;
                            side.c.BusyChange = 1;
                        }
                        else
                        {                           
                            PresetFlag3     = 0;
                            iButtonFlag3    = 0;                           
                            AckFlag         = 1;
                            CreditAuth3     = 0;
                            Credit_Auth_OK3 = 0;
                            bufferAreadyC   = 0;
                            bufferDisplay3.flagPrint = 0;
                            buffer_C[0]  = 0xBC;
                            buffer_C[1]  = 0xCB;
                            buffer_C[2]  = 0xC8;
                            buffer_C[3]  = IDCast[0];
                            buffer_C[4]  = IDCast[1];
                            buffer_C[5]  = side.c.dir;
                            buffer_C[6]  = 0xA7;
                            buffer_C[7]  = RF_IDLE;
                            buffer_C[8]  = ACK;
                            buffer_C[9]  = buffer_C[36] = verificar_check(buffer_C, 9);
                            
                            for (x = 0; x < 10; x++)
                            { 
                                RF_Connection_PutChar(buffer_C[x]);
                            }
                            flowDisplay3 = 21;
                                                                           
                        }
                    }
                    
                    if(PRF_rxBuffer[5] == side.d.dir)
                    {
                        if(PRF_rxBuffer[8] == 0x01)
                        {                           
                            // PPU
                            for(x = 19; x < 24 ; x++ )
                            {
                                ppuiButtonB[x - 19] = PRF_rxBuffer[x];                            
                            }  
                            
                            for(x = 0; x < 5 ; x++ )
                            {
                                if(ppuiButtonB[x] == 0x00)
                                { 
                                    ppuiButtonB[x] = '0';
                                }
                                
                            }
                            
                            //Preset
                            bufferDisplay4.CreditpresetType[0]= 2;
                            bufferDisplay4.CreditpresetType[1]= 'D';
                            for(x= 16; x > 8; x-- )
                            {
                                if(PRF_rxBuffer[x] != 0x00)
                                {
                                    bufferDisplay4.CreditpresetValue[0][0]= 8-(16-x);
                                    bufferDisplay4.CreditpresetValue[1][0]= 8-(16-x);
                                    break;
                                }
                            }
                            
                            for(x = 0; x < bufferDisplay4.CreditpresetValue[0][0] ; x++)
                            {
                                bufferDisplay4.CreditpresetValue[0][x + 1] = PRF_rxBuffer[(bufferDisplay4.CreditpresetValue[0][0]-x)+8];
                                bufferDisplay4.CreditpresetValue[1][x + 1] = PRF_rxBuffer[(bufferDisplay4.CreditpresetValue[0][0]-x)+8];                                
                            }
                            //Grade
                            side.d.grade = PRF_rxBuffer[18];
                            
                            buffer_D[0]  = 0xBC;
                            buffer_D[1]  = 0xCB;
                            buffer_D[2]  = 0xC8;
                            buffer_D[3]  = IDCast[0];
                            buffer_D[4]  = IDCast[1];
                            buffer_D[5]  = side.d.dir;
                            buffer_D[6]  = 0xA7;
                            buffer_D[7]  = RF_IDLE;
                            buffer_D[8]  = ACK;
                            buffer_D[9]  = buffer_D[36] = verificar_check(buffer_D, 9);
                            
                            for (x = 0; x < 10; x++)
                            { 
                                RF_Connection_PutChar(buffer_D[x]);
                            }
                           
                            Credit_Auth_OK4 = 1;
                            bufferAreadyD = 0;
                            PresetFlag4 = 1; 
                            AuthType4 = 1;
                            side.d.BusyChange = 1;
                                                       
                        }
                        else
                        {
                           
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;                           
                            AckFlag2 = 1;
                            CreditAuth4 = 0;
                            Credit_Auth_OK4 = 0;
                            bufferAreadyD = 0;
                            bufferDisplay4.flagPrint = 0;
                            buffer_D[0]  = 0xBC;
                            buffer_D[1]  = 0xCB;
                            buffer_D[2]  = 0xC8;
                            buffer_D[3]  = IDCast[0];
                            buffer_D[4]  = IDCast[1];
                            buffer_D[5]  = side.d.dir;
                            buffer_D[6]  = 0xA7;
                            buffer_D[7]  = RF_IDLE;
                            buffer_D[8]  = ACK;
                            buffer_D[9]  = buffer_D[36] = verificar_check(buffer_D, 9);
                            for (x = 0; x < 10; x++)
                            { 
                                RF_Connection_PutChar(buffer_D[x]);
                            }    
                            flowDisplay4 = 21;
                        }
                    }
                break;
                  
                             
                case 0xA5:               // Total Request
                    
                    if(PRF_rxBuffer[5] == side.a.dir)
                    {                      
                        pollTotals = 1;                     
                        return;
                    }                
                    
                    if(PRF_rxBuffer[5] == side.b.dir)
                    {                      
                        pollTotals = 2;
                        return;
                    }  
                    if(PRF_rxBuffer[5] == side.c.dir)
                    {                      
                        pollTotals = 3;
                        return;
                    }
                    if(PRF_rxBuffer[5] == side.d.dir)
                    {                      
                        pollTotals = 4;
                        return;
                    }
                 
                break;
                
                case 0xA6:               //PPU configure
                    
                    if(PRF_rxBuffer[5] == side.a.dir)
                    {                        
                        for(x = 9; x < 14 ; x++ )
                        {
                            side.a.ppuAuthorized[PRF_rxBuffer[8]][x - 9] = PRF_rxBuffer[x];
                        }
                        
                        if(PRF_rxBuffer[8] == 0)
                        {
                            EEpromGradeAddress = 20; //Address 20 to 24
                        }
                        
                        if(PRF_rxBuffer[8] == 1)
                        {
                            EEpromGradeAddress = 25; //Address 25 to 29
                        }
                        
                        if(PRF_rxBuffer[8] == 2)
                        {
                            EEpromGradeAddress = 30; //Address 30 to 34
                        }
                        
                        if(PRF_rxBuffer[8] == 3)
                        {
                            EEpromGradeAddress = 35; //Address 35 to 39
                        }
                                                
                        for(x = 0; x < 5 ; x++ )
                        {
                           EEPROM_1_WriteByte(side.a.ppuAuthorized[PRF_rxBuffer[8]][x], EEpromGradeAddress + x); //PPU to EEprom
                        }
                        
                        side.a.changePPU = true;
                        side.a.grade = PRF_rxBuffer[8];
                        buffer_tx[5] = side.a.dir; y++;
                        buffer_tx[6] = 0xA6; y++;
                        buffer_tx[7] = 0x03; y++;
                 
                    }                   
                    if(PRF_rxBuffer[5] == side.b.dir)
                    {                        
                        for(x = 9; x < 14 ; x++ )
                        {
                            side.b.ppuAuthorized[PRF_rxBuffer[8]][x - 9] = PRF_rxBuffer[x];
                        }
                        
                        if(PRF_rxBuffer[8] == 0)
                        {
                            EEpromGradeAddress = 40; //Address 40 to 44
                        }
                        
                        if(PRF_rxBuffer[8] == 1)
                        {
                            EEpromGradeAddress = 45; //Address 45 to 49
                        }
                        
                        if(PRF_rxBuffer[8] == 2)
                        {
                            EEpromGradeAddress = 50; //Address 50 to 54
                        }
                        
                        if(PRF_rxBuffer[8] == 3)
                        {
                            EEpromGradeAddress = 55; //Address 55 to 59
                        }
                        
                        for(x = 0; x < 5 ; x++ )
                        {
                            EEPROM_1_WriteByte(side.b.ppuAuthorized[PRF_rxBuffer[8]][x], EEpromGradeAddress + x); //PPU to EEprom
                        }
                        
                        side.b.changePPU = true;
                        side.b.grade = PRF_rxBuffer[8];
                        buffer_tx[5] = side.b.dir; y++;
                        buffer_tx[6] = 0xA6; y++;
                        buffer_tx[7] = 0x03; y++;
                       
                    }                     
                    if(PRF_rxBuffer[5] == side.c.dir)
                    {                        
                        for(x = 9; x < 14 ; x++ )
                        {
                            side.c.ppuAuthorized[PRF_rxBuffer[8]][x - 9] = PRF_rxBuffer[x];
                        }
                         if(PRF_rxBuffer[8] == 0)
                        {
                            EEpromGradeAddress = 60; //Address 40 to 44
                        }
                        
                        if(PRF_rxBuffer[8] == 1)
                        {
                            EEpromGradeAddress = 65; //Address 45 to 49
                        }
                        
                        if(PRF_rxBuffer[8] == 2)
                        {
                            EEpromGradeAddress = 70; //Address 50 to 54
                        }
                        
                        if(PRF_rxBuffer[8] == 3)
                        {
                            EEpromGradeAddress = 75; //Address 55 to 59
                        }
                        
                        for(x = 0; x < 5 ; x++ )
                        {
                            EEPROM_1_WriteByte(side.c.ppuAuthorized[PRF_rxBuffer[8]][x], EEpromGradeAddress + x); //PPU to EEprom
                        }
                        
                        side.c.changePPU = true;
                        side.c.grade = PRF_rxBuffer[8];
                        buffer_tx[5] = side.c.dir; y++;
                        buffer_tx[y] = 0xA6;y++;
                        buffer_tx[y] = 0x03;y++;
                    } 
                    if(PRF_rxBuffer[5] == side.d.dir)
                    {                        
                        for(x = 9; x < 14 ; x++ )
                        {
                            side.d.ppuAuthorized[PRF_rxBuffer[8]][x - 9] = PRF_rxBuffer[x];
                        }
                         if(PRF_rxBuffer[8] == 0)
                        {
                            EEpromGradeAddress = 80; //Address 40 to 44
                        }
                        
                        if(PRF_rxBuffer[8] == 1)
                        {
                            EEpromGradeAddress = 85; //Address 45 to 49
                        }
                        
                        if(PRF_rxBuffer[8] == 2)
                        {
                            EEpromGradeAddress = 90; //Address 50 to 54
                        }
                        
                        if(PRF_rxBuffer[8] == 3)
                        {
                            EEpromGradeAddress = 95; //Address 55 to 59
                        }
                        
                        for(x = 0; x < 5 ; x++ )
                        {
                            EEPROM_1_WriteByte(side.d.ppuAuthorized[PRF_rxBuffer[8]][x], EEpromGradeAddress + x); //PPU to EEprom
                        }
                        side.d.changePPU = true;
                        side.d.grade = PRF_rxBuffer[8];
                        buffer_tx[5] = side.d.dir; y++;
                        buffer_tx[6] = 0xA6;y++;
                        buffer_tx[7] = 0x03;y++;
                    }
                    
                    buffer_tx[8] = verificar_check(buffer_tx, y + 1); y++;
                                      
                    for (x = 0; x < 9; x++)
                    {
                        PPUAux =   buffer_tx[x];                   
                        RF_Connection_PutChar(PPUAux);
                    }

                    return;
                                                       
                break;
                
                case 0xA7:               //Impresion general

                    for(x = 0; x < 250; x++)
                    {
                        buffer_print[x] = 0x00;
                    }
                    
                    if(PRF_rxBuffer[5] == side.a.dir)
                    {                                                
                        buffer_tx[5] = side.a.dir;
                        buffer_tx[6] = 0xA7;
                        buffer_tx[7] = side.a.rfState;
                        buffer_tx[8] = 0x03;
                        buffer_tx[9] = verificar_check(buffer_tx,10); 
                        
                        for(x = 9; x <= PRF_rxBuffer[8] + 8; x++)
                        {
                            buffer_print[x - 9] = PRF_rxBuffer[x];                     
                        }
                        
                        for(x = 0; x <= PRF_rxBuffer[8]; x++)
                        {
                            write_psoc1(printPortA, buffer_print[x]);
                        }
                        
                        write_psoc1(printPortA, 0x0A);
                                               
                        for (x = 0; x < 9; x++)
                        {
                            RF_Connection_PutChar(buffer_tx[x]);
                        } 
                        bufferDisplay1.PrintCopy = 0;
                    }  
                    
                    if(PRF_rxBuffer[5] == side.b.dir)
                    {
                        buffer_tx[5] = side.b.dir;
                        buffer_tx[6] = 0xA7;
                        buffer_tx[7] = side.b.rfState;
                        buffer_tx[8] = 0x03;
                        buffer_tx[9] = verificar_check(buffer_tx, 10);
                        
                        for(x = 9; x <= PRF_rxBuffer[8] + 8; x++)
                        {
                            buffer_print[x - 9] = PRF_rxBuffer[x];                     
                        }
                        
                        for(x = 0; x <= PRF_rxBuffer[8]; x++)
                        {
                            write_psoc1(printPortB, buffer_print[x]);
                        }
                        
                        write_psoc1(printPortB,0x0A);                      
                        for (x = 0; x < 9; x++)
                        {
                            RF_Connection_PutChar(buffer_tx[x]);
                        }
                        
                        bufferDisplay2.PrintCopy = 0;
                    }
                    
                    if(PRF_rxBuffer[5] == side.c.dir)
                    {
                        buffer_tx[5] = side.c.dir;
                        buffer_tx[6] = 0xA7;
                        buffer_tx[7] = side.c.rfState;
                        buffer_tx[8] = 0x03;
                        buffer_tx[9] = verificar_check(buffer_tx, 10);
                        
                        for(x = 9; x <= PRF_rxBuffer[8] + 8; x++)
                        {
                            buffer_print[x - 9] = PRF_rxBuffer[x];                     
                        }
                        
                        for(x = 0; x <= PRF_rxBuffer[8]; x++)
                        {
                            write_psoc1(printPortA, buffer_print[x]);
                        }
                        
                        write_psoc1(printPortA,0x0A);                      
                        for (x = 0; x < 9; x++)
                        {
                            RF_Connection_PutChar(buffer_tx[x]);
                        }
                        bufferDisplay3.PrintCopy = 0;
                    }
                    
                    if(PRF_rxBuffer[5] == side.d.dir)
                    {
                        buffer_tx[5] = side.d.dir;
                        buffer_tx[6] = 0xA7;
                        buffer_tx[7] = side.d.rfState;
                        buffer_tx[8] = 0x03;
                        buffer_tx[9] = verificar_check(buffer_tx, 10);
                        
                        for(x = 9; x <= PRF_rxBuffer[8] + 8; x++)
                        {
                            buffer_print[x - 9] = PRF_rxBuffer[x];                     
                        }
                        
                        for(x = 0; x <= PRF_rxBuffer[8]; x++)
                        {
                            write_psoc1(printPortB, buffer_print[x]);
                        }
                        
                        write_psoc1(printPortB,0x0A);                      
                        for (x = 0; x < 9; x++)
                        {
                            RF_Connection_PutChar(buffer_tx[x]);
                        }
                        bufferDisplay4.PrintCopy = 0;
                    }

                break;
                
                case 0xA8:          //Print credit sale
                    
                    if(PRF_rxBuffer[5] == side.a.dir)
                    {   
                        for(x = 0; x < 10; x++)
                        {
                            side.a.saleNumber[x] = 0x00;
                        }
                        
                        // Id transaction
                        for(x = 0; x < 10; x++)
                        {
                            side.a.saleNumber[x] = PRF_rxBuffer[x + 8];
                        }   
                         
                        for(x = 0; x < 8; x++)
                        {
                            LicensePlate[x] = 0x00; 
                        }
                        
                        // Licese plate
                        for(x = 0; x < 8; x++)
                        {
                            LicensePlate[x] = PRF_rxBuffer[x + 18]; 
                        }                                                  

                        for(x = 0; x < 10; x++)
                        {
                            BalanceA[x] = 0x00; 
                        }
                        
                        // Balance
                        for(x = 0; x < 10; x++)
                        {
                            BalanceA[x] = PRF_rxBuffer[x + 26]; 
                        }
                        
                        for(x = 0; x < 20; x++)
                        {
                            Company[x] = 0x00; 
                        }   
                        // Company
                        for(x = 0; x < 20; x++)
                        {
                            Company[x] = PRF_rxBuffer[x + 36]; 
                        }   

                        for(x = 0; x < 20; x++)
                        {
                            CountID[x] = 0x00; 

                        }
                        // Count ID
                        for(x = 0; x < 20; x++)
                        {
                            CountID[x] = PRF_rxBuffer[x + 36]; 
                        }  

                        DayVisit = PRF_rxBuffer[76] + 0x30;
                        WeekVisit = PRF_rxBuffer[77] + 0x30;
                        MonthVisit = PRF_rxBuffer[78] + 0x30;

                        for(x = 0; x < 7; x++)
                        {
                            VolumeDay[x] = 0x00; 
                        }
                        
                        //Volume for day
                        for(x = 0; x < 7; x++)
                        {
                            VolumeDay[x] = PRF_rxBuffer[x + 79]; 
                        } 

                        for(x = 0; x < 7; x++)
                        {
                            VolumeWeek[x] = 0x00; 
                        }
                        
                        //Volume for Week
                        for(x = 0; x < 7; x++)
                        {
                            VolumeWeek[x] = PRF_rxBuffer[x + 86]; 
                        }
                         
                        for(x = 0; x < 7; x++)
                        {
                            VolumeMonth[x] = 0x00; 
                        }
                        
                         //Volume for Month
                        for(x = 0; x < 7; x++)
                        {
                            VolumeMonth[x] = PRF_rxBuffer[x + 93]; 
                        }
                       

                        for(x = 0; x < 16; x++)
                        {
                            CountType[x] = 0x00; 
                        }
                        
                        //Count type
                        for(x = 0; x < 16; x++)
                        {
                            CountType[x] = PRF_rxBuffer[x + 100]; 
                        }
                        
                        ControlType = PRF_rxBuffer[116];

                        return;

                    }

                    if(PRF_rxBuffer[5] == side.b.dir)
                    {
                        for(x = 0; x < 10; x++)
                        {
                            side.b.saleNumber[x] = 0x00;
                        }
                        
                        // Id transaction
                        for(x = 0; x < 10; x++)
                        {
                            side.b.saleNumber[x] = PRF_rxBuffer[x + 8];
                        }   
                        
                        //Licese plate
                        for(x = 0; x < 8; x++)
                        {
                            LicensePlate2[x] = 0x00; 
                        }
                        
                        for(x = 0; x < 8; x++)
                        {
                            LicensePlate2[x] = PRF_rxBuffer[x + 18]; 
                        }                                                  
                        
                        //Balance
                        for(x = 0; x < 10; x++)
                        {
                            BalanceB[x] = 0x00; 
                        }
                        
                        for(x = 0; x < 10; x++)
                        {
                            BalanceB[x] = PRF_rxBuffer[x + 26]; 
                        }                
                            
                        //Company
                        for(x = 0; x < 20; x++)
                        {
                            CompanyB[x] = PRF_rxBuffer[x + 36]; 
                        }   

                        //Count ID
                        for(x = 0; x < 20; x++)
                        {
                            CountIDB[x] = PRF_rxBuffer[x + 36]; 
                        }  
                                                
                        DayVisitB = PRF_rxBuffer[76] + 0x30;
                        WeekVisitB = PRF_rxBuffer[77] + 0x30;
                        MonthVisitB = PRF_rxBuffer[78] + 0x30;

                        //Volume for day
                        for(x = 0; x < 7; x++)
                        {
                            VolumeDayB[x] = PRF_rxBuffer[x + 79]; 
                        } 

                        //Volume for Week
                        for(x = 0; x < 7; x++)
                        {
                            VolumeWeekB[x] = PRF_rxBuffer[x + 86]; 
                        }
                         
                         //Volume for Month
                        for(x = 0; x < 7; x++)
                        {
                            VolumeMonthB[x] = PRF_rxBuffer[x + 93]; 
                        }
                       

                        //Count type
                        for(x = 0; x < 16; x++)
                        {
                            CountTypeB[x] = PRF_rxBuffer[x + 100]; 
                        }
                        
                        ControlType = PRF_rxBuffer[116];
                                                                 
                        return;
                    }
                    
                    if(PRF_rxBuffer[5] == side.c.dir)
                    {   
                        for(x = 0; x < 10; x++)
                        {
                            side.c.saleNumber[x] = 0x00;
                        }
                        
                        // Id transaction
                        for(x = 0; x < 10; x++)
                        {
                            side.c.saleNumber[x] = PRF_rxBuffer[x + 8];
                        }   
                         
                        for(x = 0; x < 8; x++)
                        {
                            LicensePlate[x] = 0x00; 
                        }
                        
                        // Licese plate
                        for(x = 0; x < 8; x++)
                        {
                            LicensePlate[x] = PRF_rxBuffer[x + 18]; 
                        }                                                  

                        for(x = 0; x < 10; x++)
                        {
                            BalanceA[x] = 0x00; 
                        }
                        
                        // Balance
                        for(x = 0; x < 10; x++)
                        {
                            BalanceA[x] = PRF_rxBuffer[x + 26]; 
                        }
                        
                        for(x = 0; x < 20; x++)
                        {
                            Company[x] = 0x00; 
                        }   
                        // Company
                        for(x = 0; x < 20; x++)
                        {
                            Company[x] = PRF_rxBuffer[x + 36]; 
                        }   

                        for(x = 0; x < 20; x++)
                        {
                            CountID[x] = 0x00; 

                        }
                        // Count ID
                        for(x = 0; x < 20; x++)
                        {
                            CountID[x] = PRF_rxBuffer[x + 36]; 
                        }  

                        DayVisit = PRF_rxBuffer[76] + 0x30;
                        WeekVisit = PRF_rxBuffer[77] + 0x30;
                        MonthVisit = PRF_rxBuffer[78] + 0x30;

                        for(x = 0; x < 7; x++)
                        {
                            VolumeDay[x] = 0x00; 
                        }
                        
                        //Volume for day
                        for(x = 0; x < 7; x++)
                        {
                            VolumeDay[x] = PRF_rxBuffer[x + 79]; 
                        } 

                        for(x = 0; x < 7; x++)
                        {
                            VolumeWeek[x] = 0x00; 
                        }
                        
                        //Volume for Week
                        for(x = 0; x < 7; x++)
                        {
                            VolumeWeek[x] = PRF_rxBuffer[x + 86]; 
                        }
                         
                        for(x = 0; x < 7; x++)
                        {
                            VolumeMonth[x] = 0x00; 
                        }
                        
                         //Volume for Month
                        for(x = 0; x < 7; x++)
                        {
                            VolumeMonth[x] = PRF_rxBuffer[x + 93]; 
                        }
                       

                        for(x = 0; x < 16; x++)
                        {
                            CountType[x] = 0x00; 
                        }
                        
                        //Count type
                        for(x = 0; x < 16; x++)
                        {
                            CountType[x] = PRF_rxBuffer[x + 100]; 
                        }
                        
                        ControlType = PRF_rxBuffer[116];

                        return;

                    }
                    
                    if(PRF_rxBuffer[5] == side.d.dir)
                    {
                        for(x = 0; x < 10; x++)
                        {
                            side.d.saleNumber[x] = 0x00;
                        }
                        
                        // Id transaction
                        for(x = 0; x < 10; x++)
                        {
                            side.d.saleNumber[x] = PRF_rxBuffer[x + 8];
                        }   
                        
                        //Licese plate
                        for(x = 0; x < 8; x++)
                        {
                            LicensePlate2[x] = 0x00; 
                        }
                        
                        for(x = 0; x < 8; x++)
                        {
                            LicensePlate2[x] = PRF_rxBuffer[x + 18]; 
                        }                                                  
                        
                        //Balance
                        for(x = 0; x < 10; x++)
                        {
                            BalanceB[x] = 0x00; 
                        }
                        
                        for(x = 0; x < 10; x++)
                        {
                            BalanceB[x] = PRF_rxBuffer[x + 26]; 
                        }                
                            
                        //Company
                        for(x = 0; x < 20; x++)
                        {
                            CompanyB[x] = PRF_rxBuffer[x + 36]; 
                        }   

                        //Count ID
                        for(x = 0; x < 20; x++)
                        {
                            CountIDB[x] = PRF_rxBuffer[x + 36]; 
                        }  
                                                
                        DayVisitB = PRF_rxBuffer[76] + 0x30;
                        WeekVisitB = PRF_rxBuffer[77] + 0x30;
                        MonthVisitB = PRF_rxBuffer[78] + 0x30;

                        //Volume for day
                        for(x = 0; x < 7; x++)
                        {
                            VolumeDayB[x] = PRF_rxBuffer[x + 79]; 
                        } 

                        //Volume for Week
                        for(x = 0; x < 7; x++)
                        {
                            VolumeWeekB[x] = PRF_rxBuffer[x + 86]; 
                        }
                         
                         //Volume for Month
                        for(x = 0; x < 7; x++)
                        {
                            VolumeMonthB[x] = PRF_rxBuffer[x + 93]; 
                        }
                       

                        //Count type
                        for(x = 0; x < 16; x++)
                        {
                            CountTypeB[x] = PRF_rxBuffer[x + 100]; 
                        }
                        
                        ControlType = PRF_rxBuffer[116];
                                                                 
                        return;
                    }

                break;

                case 0xA9:              // ID Transaction
                   
                    if(PRF_rxBuffer[5] == side.a.dir)
                    {
                        for(x = 0; x < 10; x++)
                        {
                            side.a.saleNumber[x] = PRF_rxBuffer[x+8];
                        }                          
                    }
                    
                    if(PRF_rxBuffer[5] == side.b.dir)
                    {
                        for(x = 0; x < 10; x++)
                        {
                            side.b.saleNumber[x] = PRF_rxBuffer[x+8];
                        }                        
                    }
                    
                    if(PRF_rxBuffer[5] == side.c.dir)
                    {
                        for(x = 0; x < 10; x++)
                        {
                            side.c.saleNumber[x] = PRF_rxBuffer[x + 8];
                        }
                    }
                    if(PRF_rxBuffer[5] == side.d.dir)
                    {
                        for(x = 0; x < 10; x++)
                        {
                            side.d.saleNumber[x] = PRF_rxBuffer[x + 8];
                        }
                    }
                    
                break;
                             
                case 0xE1:               //Configuracion de la estacion
                    
                    symbols[1] = PRF_rxBuffer[8];
                    date[0]    = PRF_rxBuffer[9];
                    date[1]    = PRF_rxBuffer[10];
                    date[2]    = PRF_rxBuffer[11];
                    time[1]    = PRF_rxBuffer[12];
                    time[0]    = PRF_rxBuffer[13];
                    
                    for(x = 17; x < 47; x++)
                    {
                        Encabezado1[x-16] = PRF_rxBuffer[x];
                    }
                    for(x = 47; x < 77; x++)
                    {
                        Encabezado2[x-46] = PRF_rxBuffer[x];
                    }
                    for(x = 77; x < 107; x++)
                    {
                        Encabezado3[x-76] = PRF_rxBuffer[x];
                    }
                    for(x = 107; x < 137; x++)
                    {
                        Encabezado4[x-106] = PRF_rxBuffer[x];
                    }
                    for(x = 137; x < 167; x++)
                    {
                        Encabezado5[x-136] = PRF_rxBuffer[x];
                    }
                    for(x = 167; x < 197; x++)
                    {
                        Pie1[x-166] = PRF_rxBuffer[x];
                    }
                    for(x = 197; x < 227; x++)
                    {
                        Pie2[x-196] = PRF_rxBuffer[x];
                    }
                    for(x = 227; x < 257; x++)
                    {
                        Pie3[x-226] = PRF_rxBuffer[x];
                    }
                    for(x = 257; x < 273; x++)
                    {
                        Product1[x-256] = PRF_rxBuffer[x];
                    }
                    for(x = 273; x < 289; x++)
                    {
                        Product2[x-272] = PRF_rxBuffer[x];
                    }
                    for(x = 289; x < 305; x++)
                    {
                        Product3[x-288] = PRF_rxBuffer[x];
                    }
                    for(x = 305; x < 321; x++)
                    {
                        Product4[x-304] = PRF_rxBuffer[x];
                    }
                    Encabezado1[0]   = 30;
                    Encabezado2[0]   = 30;
                    Encabezado3[0]   = 30;
                    Encabezado4[0]   = 30;
                    Encabezado5[0]   = 30;
                    Pie1[0]          = 30;
                    Pie2[0]          = 30;
                    Pie3[0]          = 30;
                    Product1[0]      = 16;
                    Product2[0]      = 16;
                    Product3[0]      = 16;
                    Product4[0]      = 16;
                    CopiasCredito = PRF_rxBuffer[16];
                    write_hora();
                    write_fecha(); 
                    logoPrint[0] = 0x01;
                    logoPrint[1] = PRF_rxBuffer[15];
                    WriteEeprom(0,logoPrint);
                    WriteEeprom(30,Encabezado1);
                    WriteEeprom(65,Encabezado2);
                    WriteEeprom(100,Encabezado3);
                    WriteEeprom(135,Encabezado4);
                    WriteEeprom(200,Encabezado5);
                    for(x = 1; x < 31; x++){
                        EEPROM_1_WriteByte(Pie1[x],x+100);
                    }
                    //WriteEeprom(500,Pie1);
                    //vTaskDelay( 20 / portTICK_PERIOD_MS );
                    WriteEeprom(600,Pie2);
                    vTaskDelay( 20 / portTICK_PERIOD_MS );
                    for(x = 1; x < 31; x++){
                        EEPROM_1_WriteByte(Pie3[x],x+130);
                    }
                    //WriteEeprom(700,Pie3);
                    //vTaskDelay( 20 / portTICK_PERIOD_MS );
                    WriteEeprom(335,Product1);
                    WriteEeprom(355,Product2);
                    vTaskDelay( 20 / portTICK_PERIOD_MS );
                    WriteEeprom(375,Product3);
                    WriteEeprom(395,Product4);
                break;
               
                case 0xE2:               //Configuracion de la posicion                                                 
                    
                    if(PRF_rxBuffer[5] == side.a.dir)
                    {
                        for(x = 8; x < 12; x++){
                            side.a.GradesHose[x-7] = PRF_rxBuffer[x];
                        }
                    }
                    if(PRF_rxBuffer[5] == side.b.dir)
                    {
                        for(x = 8; x < 12; x++){
                            side.b.GradesHose[x-7] = PRF_rxBuffer[x];
                        }
                    }
                    if(PRF_rxBuffer[5] == side.c.dir)
                    {
                        for(x = 8; x < 12; x++){
                            side.c.GradesHose[x-7] = PRF_rxBuffer[x];
                        }
                    }
                    if(PRF_rxBuffer[5] == side.d.dir)
                    {
                        for(x = 8; x < 12; x++){
                            side.d.GradesHose[x-7] = PRF_rxBuffer[x];
                        }
                    }
                    side.a.GradesHose[0] = 0x04;  //Recordar modificar donde aparezcan
                    side.b.GradesHose[0] = 0x04;
                    side.c.GradesHose[0] = 0x04;
                    side.d.GradesHose[0] = 0x04;
                    PrinterType[0]       = 0x01;
                    
                    lockTurn = PRF_rxBuffer[12];
                    EEPROM_1_WriteByte(lockTurn,7);
                    
                    PrinterType[1] = PRF_rxBuffer[7];
                    WriteEeprom(2,PrinterType);
                    WriteEeprom(4,side.a.GradesHose);
                    WriteEeprom(9,side.b.GradesHose);
                    WriteEeprom(14,side.c.GradesHose);
                    WriteEeprom(19,side.d.GradesHose);
                break;
                
                case 0xE4:               //Turno  
                    
                    if(PRF_rxBuffer[5] == side.a.dir)//if(PRF_rxBuffer[5] == side.a.dir && ShiftDone == 0)
                    {
                        ShiftDone = 1;
                        if(PRF_rxBuffer[7] == 0x02)
                        {                        
                            SetPicture(1,DISPLAY_PASSWORD_INVALIDO);
                            vTaskDelay( 900 / portTICK_PERIOD_MS );
                            flowDisplay1 = 0;
                            ShiftState = 0;
                            side.a.rfState = RF_IDLE;
                            side.a.RFstateReport = 0;
                        }
                        else
                        {
                            SetPicture(1,DISPLAY_ID_RECONOCIDO);
                            vTaskDelay( 900 / portTICK_PERIOD_MS );
                            ShiftState = 0;
                            lockTurn = PRF_rxBuffer[7];
                            EEPROM_1_WriteByte(lockTurn,7);
                            flowDisplay1 = 0;
                            if(NumPositions == 2){
                                SetPicture(1, DISPLAY_INICIO0);
                            }else{
                                SetPicture(1, DISPLAY_SELECCIONE_POSICION);
                            }
                            side.a.RFstateReport = 0;
                            side.a.rfState = RF_IDLE; 
                            return;
                        }
                    }   
                    
                    if(PRF_rxBuffer[5] == side.b.dir) //if(PRF_rxBuffer[5] == side.b.dir && ShiftDone == 0)
                    {
                        ShiftDone = 1;
                        if(PRF_rxBuffer[7] == 0x02)
                        {                        
                            SetPicture(2,DISPLAY_PASSWORD_INVALIDO);
                            vTaskDelay( 900 / portTICK_PERIOD_MS );
                            flowDisplay2 = 0;
                            ShiftState = 0;
                            side.b.rfState = RF_IDLE;
                            side.b.RFstateReport = 0;
                        }
                        else
                        {
                            SetPicture(2,DISPLAY_ID_RECONOCIDO);
                            vTaskDelay( 900 / portTICK_PERIOD_MS );
                            ShiftState = 0;
                            lockTurn = PRF_rxBuffer[7];
                            EEPROM_1_WriteByte(lockTurn,7);
                            flowDisplay2 = 0;
                            if(NumPositions == 2){
                                SetPicture(2, DISPLAY_INICIO0);
                            }else{
                                SetPicture(2, DISPLAY_SELECCIONE_POSICION);
                            } 
                            side.b.RFstateReport = 0;
                            side.b.rfState = RF_IDLE; 
                            return;
                        }
                    } 
                    
                    if(PRF_rxBuffer[5] == side.c.dir)//if(PRF_rxBuffer[5] == side.a.dir && ShiftDone == 0)
                    {
                        ShiftDone = 1;
                        if(PRF_rxBuffer[7] == 0x02)
                        {                        
                            SetPicture(1,DISPLAY_PASSWORD_INVALIDO);
                            vTaskDelay( 900 / portTICK_PERIOD_MS );
                            flowDisplay3 = 0;
                            ShiftState = 0;
                            side.c.rfState = RF_IDLE;
                            side.c.RFstateReport = 0;
                        }
                        else
                        {
                            SetPicture(1,DISPLAY_ID_RECONOCIDO);
                            vTaskDelay( 900 / portTICK_PERIOD_MS );
                            ShiftState = 0;
                            lockTurn = PRF_rxBuffer[7];
                            EEPROM_1_WriteByte(lockTurn,7);
                            flowDisplay3 = 0;
                            if(NumPositions == 2){
                                SetPicture(1, DISPLAY_INICIO0);
                            }else{
                                SetPicture(1, DISPLAY_SELECCIONE_POSICION);
                            }
                            side.c.RFstateReport = 0;
                            side.c.rfState = RF_IDLE; 
                            return;
                        }
                    }
                    
                    if(PRF_rxBuffer[5] == side.d.dir) //if(PRF_rxBuffer[5] == side.b.dir && ShiftDone == 0)
                    {
                        ShiftDone = 1;
                        if(PRF_rxBuffer[7] == 0x02)
                        {                        
                            SetPicture(2,DISPLAY_PASSWORD_INVALIDO);
                            vTaskDelay( 900 / portTICK_PERIOD_MS );
                            flowDisplay4 = 0;
                            ShiftState = 0;
                            side.d.rfState = RF_IDLE;
                            side.d.RFstateReport = 0;
                        }
                        else
                        {
                            SetPicture(2,DISPLAY_ID_RECONOCIDO);
                            vTaskDelay( 900 / portTICK_PERIOD_MS );
                            ShiftState = 0;
                            lockTurn = PRF_rxBuffer[7];
                            EEPROM_1_WriteByte(lockTurn,7);
                            flowDisplay4 = 0;
                            if(NumPositions == 2){
                                SetPicture(2, DISPLAY_INICIO0);
                            }else{
                                SetPicture(2, DISPLAY_SELECCIONE_POSICION);
                            }
                            side.d.RFstateReport = 0;
                            side.d.rfState = RF_IDLE; 
                            return;
                        }
                    }
               break;                
           }                       
        } 

    RF_Connection_ClearRxBuffer(); 
}


void pollingRFA_Tx(){   
    uint16 x,y;
    
    /////////////// TICKET COPY //////////////////
    if(side.a.rfStateCopy == RF_COPY_RECEIPT && side.a.RFstateReport == 1){ 
        buffer_A[0]   = 10;
		buffer_A[1]   = 0xBC;                                 // Encabezado byte 1
        buffer_A[2]   = 0xCB;                                 // Encabezado byte 2
        buffer_A[3]   = 0xC8;                                 // Encabezado byte 3
        buffer_A[4]   = IDCast[0];                            // ID estacion byte 1
        buffer_A[5]   = IDCast[1];                            // ID estacion byte 2
        buffer_A[6]   = side.a.dir;                           // ID posicion 
        buffer_A[7]   = 0xE6;
        buffer_A[8]   = RF_COPY_RECEIPT;
        buffer_A[9]   = verificar_check(buffer_A,10);        
		side.a.RFstateReport = 0;
        side.a.rfState = RF_IDLE;
        bufferAready = 1;
        if(PrinterType[1] == 1)
        {
            printLogoP(printPortA,11);    
        }       
        write_psoc1(printPortA,10);
        
        side.a.rfStateCopy = 0;
    }
    ////////////// PRESET - BUSY ////////////////////////////////////
    if(side.a.pumpState == PUMP_BUSY && side.a.RFstateReport == 1 && bufferDisplay1.saleType == 1)
    {
        buffer_A[0]   = 40;
		buffer_A[1]   = 0xBC;                                 // Encabezado byte 1
        buffer_A[2]   = 0xCB;                                 // Encabezado byte 2
        buffer_A[3]   = 0xC8;                                 // Encabezado byte 3
        buffer_A[4]   = IDCast[0];                            // ID estacion byte 1
        buffer_A[5]   = IDCast[1];                            // ID estacion byte 2
        buffer_A[6]   = side.a.dir;                           // ID posicion 
        buffer_A[7]   = 0xAA;                                 // Comando   
        buffer_A[8]   = RF_DELIVERING;                        // Estado de la posicion
        buffer_A[9]   = side.a.activeHose;                    
        buffer_A[10]  = bufferDisplay1.presetType[0] & 0x03; 
                
        for(x = bufferDisplay1.presetValue[0][0] ; x > 0; x--)
        {
            tempPreset[bufferDisplay1.presetValue[0][0] - x] = (bufferDisplay1.presetValue[0][x]); 
        }
        
        for(x = 11; x <= 18; x++)
        {
            buffer_A[x] = tempPreset[x - 11];
            
            if(buffer_A[x]== 0x00)
            {
                buffer_A[x] = 0x30;
            }
        }        
        buffer_A[19]  = 0x00;        
        for(x = 0; x < 8 ; x++)
        {
            buffer_A[20 + x] = bufferDisplay1.licenceSale[x + 1];
            tempPreset[x] = 0x00;
        }      
        for(x = 28; x <= 38; x++)
        {
            buffer_A[x] = 0x30;
        }
        buffer_A[39] = verificar_check(buffer_A, 40);                                
        side.a.rfState = RF_DELIVERING;     
        side.a.RFstateReport = 0;
        bufferAready = 1;
        FlagTotal = 0;  
        
    }            
    ////////////// END SALE - CASH ////////////////////////////////////
    if(bufferDisplay1.flagEndSale && side.a.RFstateReport == 1) //if((side.a.pumpState == PUMP_PEOT || side.a.pumpState == PUMP_FEOT) && side.a.RFstateReport == 1)
    {        
        for(x = 0; x < 255; x++)
        {
            buffer_A[x] = 0x00;
        }        
        buffer_A[0]  = 32;
		buffer_A[1]  = 0xBC;
        buffer_A[2]  = 0xCB;
        buffer_A[3]  = 0xC8;
        buffer_A[4]  = IDCast[0];
        buffer_A[5]  = IDCast[1];
        buffer_A[6]  = side.a.dir;
        buffer_A[7]  = 0xA4;
        buffer_A[8]  = RF_CASHSALEREPORT;
        buffer_A[9]  = side.a.activeHose - 1;
        
        for(x = side.a.ppuSale[0]; x > 0 ; x--)
        {						   							
    		tempPPU[side.a.ppuSale[0] - x] = side.a.ppuSale[x];
    	}
        
        for(x = 10; x <= 14; x++)
        {
            buffer_A[x] = tempPPU[x - 10]; 
            if(buffer_A[x] == 0x00)
                buffer_A[x] = 0x30;
        } 
        if(digits == 5 || digits == 6)
        {
            for(x = 1; x <= side.a.volumeSale[0]; x++)
            {						   							
                buffer_A[x + 14] = side.a.volumeSale[7 - x];                
        	}
        }else
        {
            for(x = 1; x <= side.a.volumeSale[0]; x++)
            {						   							
                buffer_A[x + 14] = side.a.volumeSale[9 - x];                
        	}
        }        
        if(buffer_A[21] == 0x00)
        {
            buffer_A[21] = 0x30;
            buffer_A[22] = 0x30;
        }
        if(digits == 5 || digits == 6)
        {
            for(x = 1; x <= side.a.moneySale[0]; x++)
            {						   							
        		buffer_A[x + 22] = side.a.moneySale[7 - x];                
        	} 
        }else
        {
            for(x = 1; x <= side.a.moneySale[0]; x++)
            {						   							
        		buffer_A[x + 22] = side.a.moneySale[9 - x];                
        	}            
        }
        if(buffer_A[29] == 0x00)
        {
            buffer_A[29] = 0x30;
            buffer_A[30] = 0x30;
        }
        buffer_A[31]                    = verificar_check(buffer_A,32);                          
        side.a.pumpState                = PUMP_IDLE;
        //side.a.rfState                  = RF_IDLE;        
        bufferDisplay1.flagEndSale      = false;
        side.a.RFstateReport            = 0;
        pollTotals                      = 1;
        bufferAready                    = 1;
        FlagTotal                       = 0;
        if(bufferDisplay1.flagPrint == 1)
        {
            bufferDisplay1.PrintFlagEOT     = 1;
        }else
        {
            bufferDisplay1.PrintFlagEOT     = 0;
            bufferDisplay1.flagActiveSale   = false;
            flowDisplay1 = 0;
        }
        side.a.BusyChange = 0;
    }   
    
    ////////////// SHIFT ////////////////////////////////////
    if(ShiftState == 1  && side.a.RFstateReport == 1){   
        
        for(x = 0; x < 100; x++)
        {
            buffer_A[x] = 0x00;
        }        
        buffer_A[0]  = 35;
        buffer_A[1]  = 0xBC;
        buffer_A[2]  = 0xCB;
        buffer_A[3]  = 0xC8;
        buffer_A[4]  = IDCast[0];
        buffer_A[5]  = IDCast[1];
        buffer_A[6]  = side.a.dir;
        buffer_A[7]  = 0xE3;
        buffer_A[8]  = RF_WORKSHIFTREQ;
        
        for(x = bufferDisplay1.shiftId[0]; x >= 1; x--)
        {						   							
    		buffer_A[x + 8]= bufferDisplay1.shiftId[x];            
    	}

        for(x = 1; x <= bufferDisplay1.shiftPassword[0] ;x++)
        {						   							
    		buffer_A[x + 19] = bufferDisplay1.shiftPassword[(bufferDisplay1.shiftPassword[0] + 1) - x];            
    	}

        buffer_A[33] = verificar_check(buffer_A, 34);
        
        side.a.RFstateReport = 0;
        ShiftState = 0;
        bufferAready = 1;
        ShiftDone = 0;
    }

    ////////////// AUTHORIZATION REQUEST ////////////////////////
    if(side.a.pumpState == PUMP_CALLING && side.a.RFstateReport == 1 && CreditAuth == RF_CREDITSALEAUTH && bufferDisplay1.saleType == 2)
    {
        for(x = 0; x < 100; x++)
        {
            buffer_A[x] = 0x00;
        }
        
        uint8 decimal,DecimalFaltante;
		buffer_A[0]  = 0xBC;
        buffer_A[1]  = 0xCB;
        buffer_A[2]  = 0xC8;
        buffer_A[3]  = IDCast[0];
        buffer_A[4]  = IDCast[1];
        buffer_A[5]  = side.a.dir;
        buffer_A[6]  = 0xA2;
        buffer_A[7]  = RF_CREDITSALEAUTH;
        buffer_A[8]  = side.a.hose - 1;
                                
        //iButton id
        for(y = 1; y <= 16; y++)
        {           
            if(bufferDisplay1.idSerial[y] < 0x3A)
            {
                Temp[y] = bufferDisplay1.idSerial[y] - 48;
            }
            else
            {
                Temp[y] = bufferDisplay1.idSerial[y] - 55;
            }
                                   
        }
        x = 0;      
        for(y = 1; y < 17; y += 2)
        {
            buffer_A[9 + x] =  ((Temp[y] & 0x0F) << 4) | (Temp[y + 1] & 0x0F);
            x++;
        }
       
        
        //Km (10 bytes)
        for(y = 0; y < 10; y++)
        {
            buffer_A[17 + y] = 0x00;
        }
        
        x = 0;
        
        for(y = bufferDisplay1.mileageSale[0]; y >= 1; y--)
        {           
            buffer_A[17 + x] = bufferDisplay1.mileageSale[y]; 
            x++;
        }
        
        // Preset Type
        buffer_A[27] =  bufferDisplay1.presetType[0];         
       
        //Preset (8 bytes)    
        for(y = 0; y < 8; y++)
        {
            buffer_A[28 + y] = 0x00;
        }

        x = 0;

        if(bufferDisplay1.presetType[0] == 1)
        {
            for(x=0; x<8;x++)
            {
                tempPreset[x] = 0x30;
            }

        for(x = bufferDisplay1.presetValue[0][0] ; x > 0; x--)
        {
            tempPreset[bufferDisplay1.presetValue[0][0] - x] = (bufferDisplay1.presetValue[0][x]); 
        } 
        
        decimal = 0;
        
        for(x = 0; x < 8; x++)
        {
            tempPreset2[x] = 0x30;
        }
        
        for(decimal = 0; decimal <= 7; decimal++)
        {
            tempPreset2[x] = 0x30;
            if (tempPreset[decimal] == ',')
            {
                break;
            }
        }
        if(decimal >= 7)
        {
           for(x = 0; x < 3; x++)
           {
            tempPreset2[x] = 0x30;
           }
           for(x = 3; x < 8; x++)
           {
            tempPreset2[x] = tempPreset[x - 3];
           }
        
        }
        else{
            DecimalFaltante = 3 - decimal;
            for(x = 0; x < DecimalFaltante; x++)
            {
                tempPreset2[x] = 0x30;
            }
            for(x = 0; x < decimal; x++)
            {
                tempPreset2[x + DecimalFaltante] = tempPreset[x];
            }
            for(x = 3; x < 8; x++)
            {
                
                tempPreset2[x] = tempPreset[x - DecimalFaltante + 1];
            
            }
        }

            for(x = 28; x <= 35; x++)
            {
                buffer_A[x] = tempPreset2[x - 28];
                
                if(buffer_A[x]== 0x00)
                {
                    buffer_A[x] = 0x30;
                }
            }
        }

        if(bufferDisplay1.presetType[0] == 2)
        {
            for(x = 0; x < 8; x++)
            {
                tempPreset[x] = 0x30;
            }
            
            for(x = bufferDisplay1.presetValue[0][0]; x > 0; x--)
            {
                tempPreset[bufferDisplay1.presetValue[0][0] - x] = (bufferDisplay1.presetValue[0][x]); 
            }
            for(x = 28; x <= 35; x++)
            {
                buffer_A[x] = tempPreset[x - 28];
                
                if(buffer_A[x]== 0x00)
                {
                    buffer_A[x] = 0x30;
                }
            }
        }

        // CRC
        buffer_A[36] = verificar_check(buffer_A,37);    
        side.a.RFstateReport = 0;
        bufferAready = 2;
        FlagTotal = 0;        
        CreditAuth = 0;
        AckFlag = 0;
    }
     
}

void pollingRFB_Tx(){   
    uint16 x,y;      
    /////////////// COPIA DE RECIBO //////////////////
    if(side.b.rfStateCopy == RF_COPY_RECEIPT && side.b.RFstateReport == 1){ 
        buffer_B[100]   = 10;
		buffer_B[0]   = 0xBC;                                 // Encabezado byte 1
        buffer_B[1]   = 0xCB;                                 // Encabezado byte 2
        buffer_B[2]   = 0xC8;                                 // Encabezado byte 3
        buffer_B[3]   = IDCast[0];                            // ID estacion byte 1
        buffer_B[4]   = IDCast[1];                            // ID estacion byte 2
        buffer_B[5]   = side.b.dir;                           // ID posicion 
        buffer_B[6]   = 0xE6;
        buffer_B[7]   = RF_COPY_RECEIPT;
        buffer_B[8]   = verificar_check(buffer_B,9);        
		side.b.RFstateReport = 0;
        side.b.rfState = RF_IDLE;
        bufferAreadyB = 1;
        if(PrinterType[1] == 1)
        {
            printLogoP(printPortB,11);    
        }       
        write_psoc1(printPortB,10);
        
        side.b.rfStateCopy = 0;
    }    
    ////////////// PRESET - DISPENSANDO ////////////////////////////////////
    if(side.b.pumpState == PUMP_BUSY && side.b.RFstateReport == 1 && bufferDisplay2.saleType == 1)
    {
            buffer_B[100]   = 40;
            buffer_B[0]     = 0xBC;
            buffer_B[1]     = 0xCB;
            buffer_B[2]     = 0xC8;
            buffer_B[3]     = IDCast[0];
            buffer_B[4]     = IDCast[1];
            buffer_B[5]     = side.b.dir;
            buffer_B[6]     = 0xAA;
            buffer_B[7]     = RF_DELIVERING;
            buffer_B[8]     = side.b.activeHose;
            buffer_B[9]     = bufferDisplay2.presetType[0] & 0x03;
            
            for(x = bufferDisplay2.presetValue[0][0] ; x > 0; x--)
            {
                tempPreset[bufferDisplay2.presetValue[0][0] - x] = (bufferDisplay2.presetValue[0][x]); 
            }
            for(x = 10; x <= 17; x++)
            {
                buffer_B[x] = tempPreset[x - 10]; 
                if(buffer_B[x]== 0x00)
                    buffer_B[x] = 0x30;
            }        
            buffer_B[18]  = 0x00;
            for(x = 0; x <8 ; x++)
            {
                buffer_B[19+x]=bufferDisplay2.licenceSale[x+1];
                tempPreset[x] = 0x00;
            }            
            for(x=27; x<=37;x++)
            {
                buffer_B[x]= 0x30;
            }
            
            buffer_B[38] = verificar_check(buffer_B,39);            
            //for (x = 0; x < 40; x++){
            //    RF_Connection_PutChar(buffer_B[x]);
            //}            
            side.b.rfState       = RF_DELIVERING;
            side.b.RFstateReport = 0;
            bufferAreadyB        = 1;
            FlagTotalB           = 0;
                      
    }      
    ////////////// END SALE ////////////////////////////////////
 
   if (bufferDisplay2.flagEndSale && side.b.RFstateReport == 1)    
    {
        for(x = 0; x < 255; x++)
        {
            buffer_B[x] = 0x00;
        }
        
        buffer_B[100] = 31;
        buffer_B[0]  = 0xBC;
        buffer_B[1]  = 0xCB;
        buffer_B[2]  = 0xC8;
        buffer_B[3]  = IDCast[0];
        buffer_B[4]  = IDCast[1];
        buffer_B[5]  = side.b.dir;
        buffer_B[6]  = 0xA4;
        buffer_B[7]  = RF_CASHSALEREPORT;
        buffer_B[8]  = side.b.activeHose - 1;
        
        for(x = side.b.ppuSale[0]; x > 0 ; x--)
        {						   							
    		tempPPU[side.b.ppuSale[0] - x] = side.b.ppuSale[x];
    	}
        
        for(x = 9; x <= 13; x++)
        {
            buffer_B[x] = tempPPU[x - 9]; 
            if(buffer_B[x] == 0x00)
                buffer_B[x] = 0x30;
        } 
        
        if(digits == 5 || digits == 6)
        {
            for(x = 1; x <= side.b.volumeSale[0]; x++)
            {						   							
                buffer_B[x + 13] = side.b.volumeSale[7 - x];                
        	}
        }else
        {
            for(x = 1; x <= side.b.volumeSale[0]; x++)
            {						   							
                buffer_B[x + 13] = side.b.volumeSale[9 - x];                
        	}
        }  
        
        if(buffer_B[20] == 0x00)
        {
            buffer_B[20] = 0x30;
            buffer_B[21] = 0x30;
        }
        
        if(digits == 5 || digits == 6)
        {
            for(x = 1; x <= side.b.moneySale[0]; x++)
            {						   							
        		buffer_B[x + 21] = side.b.moneySale[7 - x];                
        	} 
        }else
        {
            for(x = 1; x <= side.b.moneySale[0]; x++)
            {						   							
        		buffer_B[x + 21] = side.b.moneySale[9 - x];                
        	}            
        }
        
        if(buffer_B[28] == 0x00)
        {
            buffer_B[28] = 0x30;
            buffer_B[29] = 0x30;
        }
        
        buffer_B[30]              = verificar_check(buffer_B, 31);        
        side.b.pumpState              = PUMP_IDLE;
        //side.b.rfState                = RF_IDLE;        
        bufferDisplay2.flagEndSale    = false;
        side.b.RFstateReport          = 0;
        pollTotals                    = 2;        
        bufferAreadyB                 = 1;
        FlagTotalB                    = 0;    
        if(bufferDisplay2.flagPrint == 1)
        {
            bufferDisplay2.PrintFlagEOT     = 1;
        }else
        {
            bufferDisplay2.PrintFlagEOT     = 0;
            bufferDisplay2.flagActiveSale = false;
            flowDisplay2 = 0;
        }
        side.b.BusyChange = 0;
    }                                               
    ////////////// SHIFT ////////////////////////////////////
    if(ShiftState == 1  && side.b.RFstateReport == 1){                                            
        for(x = 0; x < 100; x++)
        {
            buffer_B[x] = 0x00;
        }        
        buffer_B[100]  = 35;
        buffer_B[0]  = 0xBC;
        buffer_B[1]  = 0xCB;
        buffer_B[2]  = 0xC8;
        buffer_B[3]  = IDCast[0];
        buffer_B[4]  = IDCast[1];
        buffer_B[5]  = side.b.dir;
        buffer_B[6]  = 0xE3;
        buffer_B[7]  = RF_WORKSHIFTREQ;
        
        for(x = bufferDisplay2.shiftId[0]; x >= 1; x--)
        {						   							
    		buffer_B[x + 7] = bufferDisplay2.shiftId[x];            
    	}
        
        for(x = 1; x <= bufferDisplay2.shiftPassword[0] ;x++)
        {						   							
    		buffer_B[x + 18] = bufferDisplay2.shiftPassword[(bufferDisplay2.shiftPassword[0] + 1) - x];            
    	}
        
         buffer_B[32] = verificar_check(buffer_B,32);
      
        side.b.RFstateReport = 0;
        ShiftState = 0;
        bufferAreadyB = 1;
        ShiftDone = 0;
    }
    
    ////////////// AUTHORIZATION REQUEST ////////////////////////
    if(side.b.pumpState == PUMP_CALLING && side.b.RFstateReport == 1 && CreditAuth2 == RF_CREDITSALEAUTH && bufferDisplay2.saleType == 2)
    {
        for(x = 0; x < 100; x++)
        {
            buffer_B[x] = 0x00;
        } 
        uint8 decimal, DecimalFaltante;
        buffer_B[0]  = 0xBC;
        buffer_B[1]  = 0xCB;
        buffer_B[2]  = 0xC8;
        buffer_B[3]  = IDCast[0];
        buffer_B[4]  = IDCast[1];
        buffer_B[5]  = side.b.dir;
        buffer_B[6]  = 0xA2;
        buffer_B[7]  = RF_CREDITSALEAUTH;
        buffer_B[8]  = side.b.hose - 1;
                             
        //iButton id
        for(y = 1; y <= 16; y++)
        {           
            if(bufferDisplay2.idSerial[y] < 0x3A)
            {
                Temp[y] = bufferDisplay2.idSerial[y] - 48;
            }
            else
            {
                Temp[y] = bufferDisplay2.idSerial[y] - 55;
            }                                
        }
        
        x = 0;
        
        for(y = 1; y < 17; y+=2)
        {
            buffer_B[9 + x] =  ((Temp[y] & 0x0F) << 4) | (Temp[y + 1] & 0x0F);
            x++;
        }
        
        //Km
        for(y = 0; y < 10; y++)
        {
            buffer_B[17 + y] = 0x00;
        }
        
        x = 0;
        
        for(y = bufferDisplay2.mileageSale[0]; y >= 1; y--)
        {           
            buffer_B[17 + x] = bufferDisplay2.mileageSale[y]; 
            x++;
        }
        
        // Preset Type
        buffer_B[27] =  bufferDisplay2.presetType[0];         
       
        //Preset (8 bytes)       
        for(y = 0; y < 8; y++)
        {
            buffer_B[28 + y] = 0x00;
        }
        x = 0;
        if(bufferDisplay2.presetType[0] == 1)
        {
            for(x=0; x<8;x++){
                tempPreset[x] = 0x30;
            }

        for(x = bufferDisplay2.presetValue[0][0] ; x > 0; x--)
        {
            tempPreset[bufferDisplay2.presetValue[0][0] - x] = (bufferDisplay2.presetValue[0][x]); 
        } 
        
        decimal = 0;
        
        for(x=0; x<8;x++){
            tempPreset2[x] = 0x30;
        }
        
        for(decimal =0; decimal <= 7; decimal++)
        {
            tempPreset2[x] = 0x30;
            if (tempPreset[decimal]== ',')
            {
                break;
            }
        }
        if(decimal >= 7)
        {
           for(x=0; x<3;x++){
            tempPreset2[x]=0x30;
           }
           for(x=3; x<8;x++){
            tempPreset2[x]=tempPreset[x-3];
           }
        
        }
        else{
            DecimalFaltante=3-decimal;
            for(x=0; x<DecimalFaltante;x++){
                tempPreset2[x]=0x30;
            }
            for(x=0; x<decimal;x++){
                tempPreset2[x+DecimalFaltante]=tempPreset[x];
            }
            for(x=3; x<8;x++){
                
                tempPreset2[x]=tempPreset[x-DecimalFaltante+1];
            
            }
        }

            for(x = 28; x <= 35; x++)
            {
                buffer_B[x] = tempPreset2[x - 28];
                
                if(buffer_B[x]== 0x00)
                {
                    buffer_B[x] = 0x30;
                }
            }
        }
        if(bufferDisplay2.presetType[0] == 2)
        {
            for(x = 0; x<8; x++)
            {
                tempPreset[x] = 0x30;
            }
            
            for(x = bufferDisplay2.presetValue[0][0] ; x > 0; x--)
            {
                tempPreset[bufferDisplay2.presetValue[0][0] - x] = (bufferDisplay2.presetValue[0][x]); 
            }
            for(x = 28; x <= 35; x++)
            {
                buffer_B[x] = tempPreset[x - 28];
                
                if(buffer_B[x]== 0x00)
                {
                    buffer_B[x] = 0x30;
                }
            }
        }    
 
        // CRC
        buffer_B[36] = verificar_check(buffer_B,37);
               
        side.b.RFstateReport = 0;
        bufferAreadyB = 2;
        FlagTotalB = 0;        
        CreditAuth2 = 0;
        AckFlag2 = 0;
    }
  
 }

void pollingRFC_Tx(){   
    uint16 x,y;
    
    /////////////// TICKET COPY //////////////////
    if(side.c.rfStateCopy == RF_COPY_RECEIPT && side.c.RFstateReport == 1){ 
        buffer_C[0]   = 10;
		buffer_C[1]   = 0xBC;                                 // Encabezado byte 1
        buffer_C[2]   = 0xCB;                                 // Encabezado byte 2
        buffer_C[3]   = 0xC8;                                 // Encabezado byte 3
        buffer_C[4]   = IDCast[0];                            // ID estacion byte 1
        buffer_C[5]   = IDCast[1];                            // ID estacion byte 2
        buffer_C[6]   = side.c.dir;                           // ID posicion 
        buffer_C[7]   = 0xE6;
        buffer_C[8]   = RF_COPY_RECEIPT;
        buffer_C[9]   = verificar_check(buffer_C,10);        
		side.c.RFstateReport = 0;
        side.c.rfState = RF_IDLE;
        bufferAreadyC = 1;
        if(PrinterType[1] == 1)
        {
            printLogoP(printPortA,11);    
        }       
        write_psoc1(printPortA,10);
        
        side.c.rfStateCopy = 0;
    }
    ////////////// PRESET - BUSY ////////////////////////////////////
    if(side.c.pumpState == PUMP_BUSY && side.c.RFstateReport == 1 && bufferDisplay3.saleType == 1)
    {
        buffer_C[0]   = 40;
		buffer_C[1]   = 0xBC;                                 // Encabezado byte 1
        buffer_C[2]   = 0xCB;                                 // Encabezado byte 2
        buffer_C[3]   = 0xC8;                                 // Encabezado byte 3
        buffer_C[4]   = IDCast[0];                            // ID estacion byte 1
        buffer_C[5]   = IDCast[1];                            // ID estacion byte 2
        buffer_C[6]   = side.c.dir;                           // ID posicion 
        buffer_C[7]   = 0xAA;                                 // Comando   
        buffer_C[8]   = RF_DELIVERING;                        // Estado de la posicion
        buffer_C[9]   = side.c.activeHose;                    
        buffer_C[10]  = bufferDisplay3.presetType[0] & 0x03; 
                
        for(x = bufferDisplay3.presetValue[0][0] ; x > 0; x--)
        {
            tempPreset[bufferDisplay3.presetValue[0][0] - x] = (bufferDisplay3.presetValue[0][x]); 
        }
        
        for(x = 11; x <= 18; x++)
        {
            buffer_C[x] = tempPreset[x - 11];
            
            if(buffer_C[x]== 0x00)
            {
                buffer_C[x] = 0x30;
            }
        }        
        buffer_C[19]  = 0x00;
        for(x = 0; x < 8 ; x++)
        {
            buffer_C[20 + x] = bufferDisplay3.licenceSale[x + 1];
            tempPreset[x] = 0x00;
        }
        //}
        for(x = 28; x <= 38; x++)
        {
            buffer_C[x] = 0x30;
        }
        buffer_C[39] = verificar_check(buffer_C, 40);                                
        side.c.rfState = RF_DELIVERING;     
        side.c.RFstateReport = 0;
        bufferAreadyC     = 1;
        FlagTotalC        = 0;
      
    }            
    ////////////// END SALE - CASH ////////////////////////////////////
    if(bufferDisplay3.flagEndSale && side.c.RFstateReport == 1) //if((side.a.pumpState == PUMP_PEOT || side.a.pumpState == PUMP_FEOT) && side.a.RFstateReport == 1)
    {        
        for(x = 0; x < 255; x++)
        {
            buffer_C[x] = 0x00;
        }
        
        buffer_C[0]  = 32;
		buffer_C[1]  = 0xBC;
        buffer_C[2]  = 0xCB;
        buffer_C[3]  = 0xC8;
        buffer_C[4]  = IDCast[0];
        buffer_C[5]  = IDCast[1];
        buffer_C[6]  = side.c.dir;
        buffer_C[7]  = 0xA4;
        buffer_C[8]  = RF_CASHSALEREPORT;
        buffer_C[9]  = side.c.activeHose - 1;
        
        for(x = side.c.ppuSale[0]; x > 0 ; x--)
        {						   							
    		tempPPU[side.c.ppuSale[0] - x] = side.c.ppuSale[x];
    	}
        
        for(x = 10; x <= 14; x++)
        {
            buffer_C[x] = tempPPU[x - 10]; 
            if(buffer_C[x] == 0x00)
                buffer_C[x] = 0x30;
        } 
        if(digits == 5 || digits == 6)
        {
            for(x = 1; x <= side.c.volumeSale[0]; x++)
            {						   							
                buffer_C[x + 14] = side.c.volumeSale[7 - x];                
        	}
        }else
        {
            for(x = 1; x <= side.c.volumeSale[0]; x++)
            {						   							
                buffer_C[x + 14] = side.c.volumeSale[9 - x];                
        	}
        }        
        if(buffer_C[21] == 0x00)
        {
            buffer_C[21] = 0x30;
            buffer_C[22] = 0x30;
        }
        if(digits == 5 || digits == 6)
        {
            for(x = 1; x <= side.c.moneySale[0]; x++)
            {						   							
        		buffer_C[x + 22] = side.c.moneySale[7 - x];                
        	} 
        }else
        {
            for(x = 1; x <= side.c.moneySale[0]; x++)
            {						   							
        		buffer_C[x + 22] = side.c.moneySale[9 - x];                
        	}            
        }
        if(buffer_C[29] == 0x00)
        {
            buffer_C[29] = 0x30;
            buffer_C[30] = 0x30;
        }
        buffer_C[31]                    = verificar_check(buffer_C,32);                          
        side.c.pumpState                = PUMP_IDLE;
        //side.a.rfState                  = RF_IDLE;        
        bufferDisplay3.flagEndSale      = false;
        side.c.RFstateReport            = 0;
        pollTotals                      = 3;
        bufferAreadyC                   = 1;
        FlagTotalC                      = 0;
        if(bufferDisplay3.flagPrint == 1)
        {
            bufferDisplay3.PrintFlagEOT     = 1;
        }else
        {
            bufferDisplay3.PrintFlagEOT     = 0;
            bufferDisplay3.flagActiveSale   = false;
            flowDisplay3 = 0;
        }
        side.c.BusyChange = 0;
    }   
    
    ////////////// SHIFT ////////////////////////////////////
    if(ShiftState == 1  && side.c.RFstateReport == 1){           
        for(x = 0; x < 100; x++)
        {
            buffer_C[x] = 0x00;
        }        
        buffer_C[0]  = 35;
        buffer_C[1]  = 0xBC;
        buffer_C[2]  = 0xCB;
        buffer_C[3]  = 0xC8;
        buffer_C[4]  = IDCast[0];
        buffer_C[5]  = IDCast[1];
        buffer_C[6]  = side.c.dir;
        buffer_C[7]  = 0xE3;
        buffer_C[8]  = RF_WORKSHIFTREQ;
        

        for(x = bufferDisplay3.shiftId[0]; x >= 1; x--)
        {						   							
    		buffer_C[x + 8]= bufferDisplay3.shiftId[x];            
    	}

        for(x = 1; x <= bufferDisplay3.shiftPassword[0] ;x++)
        {						   							
    		buffer_C[x + 19] = bufferDisplay3.shiftPassword[(bufferDisplay3.shiftPassword[0] + 1) - x];            
    	}

        buffer_C[33] = verificar_check(buffer_C, 34);
        

        side.c.RFstateReport = 0;
        ShiftState = 0;
        bufferAreadyC = 1;
        ShiftDone = 0;
    }

    ////////////// AUTHORIZATION REQUEST ////////////////////////
    if(side.c.pumpState == PUMP_CALLING && side.c.RFstateReport == 1 && CreditAuth3 == RF_CREDITSALEAUTH && bufferDisplay3.saleType == 2)
    {  
        for(x = 0; x < 100; x++)
        {
            buffer_C[x] = 0x00;
        }
        uint8 decimal,DecimalFaltante;
		buffer_C[0]  = 0xBC;
        buffer_C[1]  = 0xCB;
        buffer_C[2]  = 0xC8;
        buffer_C[3]  = IDCast[0];
        buffer_C[4]  = IDCast[1];
        buffer_C[5]  = side.c.dir;
        buffer_C[6]  = 0xA2;
        buffer_C[7]  = RF_CREDITSALEAUTH;
        buffer_C[8]  = side.c.hose - 1;
                                
        //iButton id
        for(y = 1; y <= 16; y++)
        {           
            if(bufferDisplay3.idSerial[y] < 0x3A)
            {
                Temp[y] = bufferDisplay3.idSerial[y] - 48;
            }
            else
            {
                Temp[y] = bufferDisplay3.idSerial[y] - 55;
            }
                                   
        }
        x = 0;      
        for(y = 1; y < 17; y += 2)
        {
            buffer_C[9 + x] =  ((Temp[y] & 0x0F) << 4) | (Temp[y + 1] & 0x0F);
            x++;
        }
       
        
        //Km (10 bytes)
        for(y = 0; y < 10; y++)
        {
            buffer_C[17 + y] = 0x00;
        }
        
        x = 0;
        
        for(y = bufferDisplay3.mileageSale[0]; y >= 1; y--)
        {           
            buffer_C[17 + x] = bufferDisplay3.mileageSale[y]; 
            x++;
        }
        
        // Preset Type
        buffer_C[27] =  bufferDisplay3.presetType[0];         
       
        //Preset (8 bytes)    
        for(y = 0; y < 8; y++)
        {
            buffer_C[28 + y] = 0x00;
        }

        x = 0;

        if(bufferDisplay3.presetType[0] == 1)
        {
            for(x=0; x<8;x++)
            {
                tempPreset[x] = 0x30;
            }

        for(x = bufferDisplay3.presetValue[0][0] ; x > 0; x--)
        {
            tempPreset[bufferDisplay3.presetValue[0][0] - x] = (bufferDisplay3.presetValue[0][x]); 
        } 
        
        decimal = 0;
        
        for(x = 0; x < 8; x++)
        {
            tempPreset2[x] = 0x30;
        }
        
        for(decimal = 0; decimal <= 7; decimal++)
        {
            tempPreset2[x] = 0x30;
            if (tempPreset[decimal] == ',')
            {
                break;
            }
        }
        if(decimal >= 7)
        {
           for(x = 0; x < 3; x++)
           {
            tempPreset2[x] = 0x30;
           }
           for(x = 3; x < 8; x++)
           {
            tempPreset2[x] = tempPreset[x - 3];
           }
        
        }
        else{
            DecimalFaltante = 3 - decimal;
            for(x = 0; x < DecimalFaltante; x++)
            {
                tempPreset2[x] = 0x30;
            }
            for(x = 0; x < decimal; x++)
            {
                tempPreset2[x + DecimalFaltante] = tempPreset[x];
            }
            for(x = 3; x < 8; x++)
            {
                
                tempPreset2[x] = tempPreset[x - DecimalFaltante + 1];
            
            }
        }

            for(x = 28; x <= 35; x++)
            {
                buffer_C[x] = tempPreset2[x - 28];
                
                if(buffer_C[x]== 0x00)
                {
                    buffer_C[x] = 0x30;
                }
            }
        }

        if(bufferDisplay3.presetType[0] == 2)
        {
            for(x = 0; x < 8; x++)
            {
                tempPreset[x] = 0x30;
            }
            
            for(x = bufferDisplay3.presetValue[0][0]; x > 0; x--)
            {
                tempPreset[bufferDisplay3.presetValue[0][0] - x] = (bufferDisplay3.presetValue[0][x]); 
            }
            for(x = 28; x <= 35; x++)
            {
                buffer_C[x] = tempPreset[x - 28];
                
                if(buffer_C[x]== 0x00)
                {
                    buffer_C[x] = 0x30;
                }
            }
        }

        // CRC
        buffer_C[36] = verificar_check(buffer_C,37);    
        side.c.RFstateReport = 0;
        bufferAreadyC = 2;
        FlagTotalC = 0;        
        CreditAuth3 = 0;
        AckFlag = 0;
    }
     
}

void pollingRFD_Tx(){   
    uint16 x,y;
    
    /////////////// TICKET COPY //////////////////
    if(side.d.rfStateCopy == RF_COPY_RECEIPT && side.d.RFstateReport == 1){ 
        buffer_A[0]   = 10;
		buffer_D[1]   = 0xBC;                                 // Encabezado byte 1
        buffer_D[2]   = 0xCB;                                 // Encabezado byte 2
        buffer_D[3]   = 0xC8;                                 // Encabezado byte 3
        buffer_D[4]   = IDCast[0];                            // ID estacion byte 1
        buffer_D[5]   = IDCast[1];                            // ID estacion byte 2
        buffer_D[6]   = side.d.dir;                           // ID posicion 
        buffer_D[7]   = 0xE6;
        buffer_D[8]   = RF_COPY_RECEIPT;
        buffer_D[9]   = verificar_check(buffer_D,10);        
		side.d.RFstateReport = 0;
        side.d.rfState = RF_IDLE;
        bufferAreadyD = 1;
        if(PrinterType[1] == 1)
        {
            printLogoP(printPortB,11);    
        }       
        write_psoc1(printPortB,10);
        
        side.d.rfStateCopy = 0;
    }
    ////////////// PRESET - BUSY ////////////////////////////////////
    if(side.d.pumpState == PUMP_BUSY && side.d.RFstateReport == 1 && bufferDisplay4.saleType == 1)
    {
        buffer_D[0]   = 40;
		buffer_D[1]   = 0xBC;                                 // Encabezado byte 1
        buffer_D[2]   = 0xCB;                                 // Encabezado byte 2
        buffer_D[3]   = 0xC8;                                 // Encabezado byte 3
        buffer_D[4]   = IDCast[0];                            // ID estacion byte 1
        buffer_D[5]   = IDCast[1];                            // ID estacion byte 2
        buffer_D[6]   = side.d.dir;                           // ID posicion 
        buffer_D[7]   = 0xAA;                                 // Comando   
        buffer_D[8]   = RF_DELIVERING;                        // Estado de la posicion
        buffer_D[9]   = side.d.activeHose;                    
        buffer_D[10]  = bufferDisplay4.presetType[0] & 0x03; 
                
        for(x = bufferDisplay4.presetValue[0][0] ; x > 0; x--)
        {
            tempPreset[bufferDisplay4.presetValue[0][0] - x] = (bufferDisplay4.presetValue[0][x]); 
        }
        
        for(x = 11; x <= 18; x++)
        {
            buffer_D[x] = tempPreset[x - 11];
            
            if(buffer_D[x]== 0x00)
            {
                buffer_D[x] = 0x30;
            }
        }        
        buffer_D[19]  = 0x00;
        for(x = 0; x < 8 ; x++)
        {
            buffer_D[20 + x] = bufferDisplay4.licenceSale[x + 1];
            tempPreset[x] = 0x00;
        }
        for(x = 28; x <= 38; x++)
        {
            buffer_D[x] = 0x30;
        }
        buffer_D[39] = verificar_check(buffer_D, 40);                                
        side.d.rfState = RF_DELIVERING;     
        side.d.RFstateReport = 0;
        bufferAreadyD     = 1;
        FlagTotalD        = 0;
      
    }            
    ////////////// END SALE - CASH ////////////////////////////////////
    if(bufferDisplay4.flagEndSale && side.d.RFstateReport == 1) //if((side.a.pumpState == PUMP_PEOT || side.a.pumpState == PUMP_FEOT) && side.a.RFstateReport == 1)
    {        
        for(x = 0; x < 255; x++)
        {
            buffer_D[x] = 0x00;
        }
        
        buffer_D[0]  = 32;
		buffer_D[1]  = 0xBC;
        buffer_D[2]  = 0xCB;
        buffer_D[3]  = 0xC8;
        buffer_D[4]  = IDCast[0];
        buffer_D[5]  = IDCast[1];
        buffer_D[6]  = side.d.dir;
        buffer_D[7]  = 0xA4;
        buffer_D[8]  = RF_CASHSALEREPORT;
        buffer_D[9]  = side.d.activeHose - 1;
        
        for(x = side.d.ppuSale[0]; x > 0 ; x--)
        {						   							
    		tempPPU[side.d.ppuSale[0] - x] = side.d.ppuSale[x];
    	}
        
        for(x = 10; x <= 14; x++)
        {
            buffer_D[x] = tempPPU[x - 10]; 
            if(buffer_D[x] == 0x00)
                buffer_D[x] = 0x30;
        } 
        if(digits == 5 || digits == 6)
        {
            for(x = 1; x <= side.d.volumeSale[0]; x++)
            {						   							
                buffer_D[x + 14] = side.d.volumeSale[7 - x];                
        	}
        }else
        {
            for(x = 1; x <= side.d.volumeSale[0]; x++)
            {						   							
                buffer_D[x + 14] = side.d.volumeSale[9 - x];                
        	}
        }        
        if(buffer_D[21] == 0x00)
        {
            buffer_D[21] = 0x30;
            buffer_D[22] = 0x30;
        }
        if(digits == 5 || digits == 6)
        {
            for(x = 1; x <= side.d.moneySale[0]; x++)
            {						   							
        		buffer_D[x + 22] = side.d.moneySale[7 - x];                
        	} 
        }else
        {
            for(x = 1; x <= side.d.moneySale[0]; x++)
            {						   							
        		buffer_D[x + 22] = side.d.moneySale[9 - x];                
        	}            
        }
        if(buffer_D[29] == 0x00)
        {
            buffer_D[29] = 0x30;
            buffer_D[30] = 0x30;
        }
        buffer_D[31]                    = verificar_check(buffer_D,32);                          
        side.d.pumpState                = PUMP_IDLE;
        //side.a.rfState                  = RF_IDLE;        
        bufferDisplay4.flagEndSale      = false;
        side.d.RFstateReport            = 0;
        pollTotals                      = 4;
        bufferAreadyD                   = 1;
        FlagTotalD                      = 0;        
        if(bufferDisplay4.flagPrint == 1)
        {
            bufferDisplay4.PrintFlagEOT     = 1;
        }else
        {
            bufferDisplay4.PrintFlagEOT     = 0;
            bufferDisplay4.flagActiveSale   = false;
            flowDisplay4 = 0;
        }
        side.d.BusyChange = 0;
    }   
    
    ////////////// SHIFT ////////////////////////////////////
    if(ShiftState == 1  && side.d.RFstateReport == 1){           
        for(x = 0; x < 100; x++)
        {
            buffer_D[x] = 0x00;
        }        
        buffer_D[0]  = 35;
        buffer_D[1]  = 0xBC;
        buffer_D[2]  = 0xCB;
        buffer_D[3]  = 0xC8;
        buffer_D[4]  = IDCast[0];
        buffer_D[5]  = IDCast[1];
        buffer_D[6]  = side.d.dir;
        buffer_D[7]  = 0xE3;
        buffer_D[8]  = RF_WORKSHIFTREQ;
        

        for(x = bufferDisplay4.shiftId[0]; x >= 1; x--)
        {						   							
    		buffer_D[x + 8]= bufferDisplay4.shiftId[x];            
    	}

        for(x = 1; x <= bufferDisplay4.shiftPassword[0] ;x++)
        {						   							
    		buffer_D[x + 19] = bufferDisplay4.shiftPassword[(bufferDisplay4.shiftPassword[0] + 1) - x];            
    	}

        buffer_D[33] = verificar_check(buffer_D, 34);
        

        side.d.RFstateReport = 0;
        ShiftState = 0;
        bufferAreadyC = 1;
        ShiftDone = 0;
    }

    ////////////// AUTHORIZATION REQUEST ////////////////////////
    if(side.d.pumpState == PUMP_CALLING && side.d.RFstateReport == 1 && CreditAuth4 == RF_CREDITSALEAUTH && bufferDisplay4.saleType == 2)
    { 
        for(x = 0; x < 100; x++)
        {
            buffer_D[x] = 0x00;
        }
        uint8 decimal,DecimalFaltante;
		buffer_D[0]  = 0xBC;
        buffer_D[1]  = 0xCB;
        buffer_D[2]  = 0xC8;
        buffer_D[3]  = IDCast[0];
        buffer_D[4]  = IDCast[1];
        buffer_D[5]  = side.d.dir;
        buffer_D[6]  = 0xA2;
        buffer_D[7]  = RF_CREDITSALEAUTH;
        buffer_D[8]  = side.d.hose - 1;
                                
        //iButton id
        for(y = 1; y <= 16; y++)
        {           
            if(bufferDisplay4.idSerial[y] < 0x3A)
            {
                Temp[y] = bufferDisplay4.idSerial[y] - 48;
            }
            else
            {
                Temp[y] = bufferDisplay4.idSerial[y] - 55;
            }                                   
        }
        x = 0;      
        for(y = 1; y < 17; y += 2)
        {
            buffer_D[9 + x] =  ((Temp[y] & 0x0F) << 4) | (Temp[y + 1] & 0x0F);
            x++;
        }               
        //Km (10 bytes)
        for(y = 0; y < 10; y++)
        {
            buffer_D[17 + y] = 0x00;
        }
        
        x = 0;
        
        for(y = bufferDisplay4.mileageSale[0]; y >= 1; y--)
        {           
            buffer_D[17 + x] = bufferDisplay4.mileageSale[y]; 
            x++;
        }
        
        // Preset Type
        buffer_D[27] =  bufferDisplay4.presetType[0];         
       
        //Preset (8 bytes)    
        for(y = 0; y < 8; y++)
        {
            buffer_D[28 + y] = 0x00;
        }

        x = 0;

        if(bufferDisplay4.presetType[0] == 1)
        {
            for(x=0; x<8;x++)
            {
                tempPreset[x] = 0x30;
            }

        for(x = bufferDisplay4.presetValue[0][0] ; x > 0; x--)
        {
            tempPreset[bufferDisplay4.presetValue[0][0] - x] = (bufferDisplay4.presetValue[0][x]); 
        } 
        
        decimal = 0;
        
        for(x = 0; x < 8; x++)
        {
            tempPreset2[x] = 0x30;
        }
        
        for(decimal = 0; decimal <= 7; decimal++)
        {
            tempPreset2[x] = 0x30;
            if (tempPreset[decimal] == ',')
            {
                break;
            }
        }
        if(decimal >= 7)
        {
           for(x = 0; x < 3; x++)
           {
            tempPreset2[x] = 0x30;
           }
           for(x = 3; x < 8; x++)
           {
            tempPreset2[x] = tempPreset[x - 3];
           }
        
        }
        else{
            DecimalFaltante = 3 - decimal;
            for(x = 0; x < DecimalFaltante; x++)
            {
                tempPreset2[x] = 0x30;
            }
            for(x = 0; x < decimal; x++)
            {
                tempPreset2[x + DecimalFaltante] = tempPreset[x];
            }
            for(x = 3; x < 8; x++)
            {
                
                tempPreset2[x] = tempPreset[x - DecimalFaltante + 1];
            
            }
        }

            for(x = 28; x <= 35; x++)
            {
                buffer_D[x] = tempPreset2[x - 28];
                
                if(buffer_D[x]== 0x00)
                {
                    buffer_D[x] = 0x30;
                }
            }
        }

        if(bufferDisplay4.presetType[0] == 2)
        {
            for(x = 0; x < 8; x++)
            {
                tempPreset[x] = 0x30;
            }
            
            for(x = bufferDisplay4.presetValue[0][0]; x > 0; x--)
            {
                tempPreset[bufferDisplay4.presetValue[0][0] - x] = (bufferDisplay4.presetValue[0][x]); 
            }
            for(x = 28; x <= 35; x++)
            {
                buffer_D[x] = tempPreset[x - 28];
                
                if(buffer_D[x]== 0x00)
                {
                    buffer_D[x] = 0x30;
                }
            }
        }

        // CRC
        buffer_D[36] = verificar_check(buffer_D,37);    
        side.d.RFstateReport = 0;
        bufferAreadyD = 2;
        FlagTotal = 0;        
        CreditAuth4 = 0;
        AckFlag = 0;
    }
     
}


