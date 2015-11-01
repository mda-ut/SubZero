#ifndef TERASIC_SPI_H_
#define TERASIC_SPI_H_

void SPI_Init(alt_u32 spi_base);
bool SPI_MultipleWrite(alt_u32 spi_base, alt_u8 RegIndex, alt_u8 szData[], alt_u8 nByteNum);
bool SPI_Write(alt_u32 spi_base, alt_u8 RegIndex, alt_u8 Value);
bool SPI_MultipleRead(alt_u32 spi_base, alt_u8 RegIndex, alt_u8 szBuf[], alt_u8 nByteNum);
bool SPI_Read(alt_u32 spi_base, alt_u8 RegIndex, alt_u8 *pBuf);

#endif /*TERASIC_SPI_H_*/
