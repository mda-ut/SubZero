/*
This file was mostly copied from a DE0-Nano CD example and is used to read
accelerometer data from the FPGA. This is not really used anymore.

Victor - Sept 2013
*/

#include "terasic_includes.h"
#include "accelerometer_adxl345_spi.h"
#include "terasic_spi.h"


#define DATA_READY_TIMEOUT  (alt_ticks_per_second()/3)



bool ADXL345_SPI_Init(alt_u32 device_base){
    bool bSuccess;
    
    // clear fifo
    SPI_Init(device_base);
   
    // 3-wire spi
    bSuccess = SPI_Write(device_base, ADXL345_REG_DATA_FORMAT, XL345_SPI3WIRE);
 
    // clear fifo   
    SPI_Init(device_base);
        
    //Output Data Rate: 40Hz
    if (bSuccess){
        bSuccess = SPI_Write(device_base, ADXL345_REG_BW_RATE, XL345_RATE_400); // 400 MHZ
    }
    
            
        
    //INT_Enable: Data Ready
    if (bSuccess){   
        bSuccess = SPI_Write(device_base, ADXL345_REG_INT_ENALBE, XL345_DATAREADY);
    }
    
    // stop measure
    if (bSuccess){
        bSuccess = SPI_Write(device_base, ADXL345_REG_POWER_CTL, XL345_STANDBY);
    }

    // start measure
    if (bSuccess){
        bSuccess = SPI_Write(device_base, ADXL345_REG_POWER_CTL, XL345_MEASURE);
        
    }
    
            
    return bSuccess;    
        
}


    
bool ADXL345_SPI_WaitDataReady(alt_u32 device_base){
    bool bDataReady;
    alt_u32 TimeStart;
    
    TimeStart = alt_nticks();
    do{
        bDataReady = ADXL345_SPI_IsDataReady(device_base);
        if (!bDataReady)
            usleep(500); 
    }while (!bDataReady && ( (alt_nticks() - TimeStart) < DATA_READY_TIMEOUT) );
    
    return bDataReady;
        
}    

bool ADXL345_SPI_IsDataReady(alt_u32 device_base){
    bool bReady = FALSE;
    alt_u8 data8;
    
    if (SPI_Read(device_base, ADXL345_REG_INT_SOURCE,&data8)){
        if (data8 & XL345_DATAREADY)
            bReady = TRUE;
    }            
    
    return bReady;
}



bool ADXL345_SPI_XYZ_Read(alt_u32 device_base, struct t_accel_data *szData16){
    bool bPass;
    alt_u8 szData8[6];
    bPass = SPI_MultipleRead(device_base, 0x32, (alt_u8 *)&szData8, sizeof(szData8));
    if (bPass){
        szData16->x = (szData8[1] << 8) | szData8[0]; 
        szData16->y = (szData8[3] << 8) | szData8[2];
        szData16->z = (szData8[5] << 8) | szData8[4];
    }        
    
    return bPass;
}

bool ADXL345_SPI_IdRead(alt_u32 device_base, alt_u8 *pId){
    bool bPass;
    bPass = SPI_Read(device_base, ADXL345_REG_DEVID, pId);
    
    return bPass;
}
