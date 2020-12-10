//HL-1无线开发板配套NRF24L01使用说明
//接入模块之前请看图片，不能接错模块，否则会烧坏模块
//模块共有2排，10个焊针，HL-1开发板模块接口有14个，接入之前请一定要看清楚
//你的模块需要接到哪个位置上，正确的方法是接入右边10个座子上，同时焊好24L01位置
//上的三个焊点（连起来）。出货如果配套24L01的模块，出厂已焊接好。
//下载同一个程序到开发板芯片上，按下左下角第一个按钮，二个开发板会发出声音。
//按下左下角第二个按钮，D1流水灯发光管会点亮。
//程序不提供源码分析，如果把本源码用于项目开发，毕业设计，请自己修改程序。
// nRF24L01.h
#ifndef _NRF_24L01_
#define _NRF_24L01_



#define TX_ADR_WIDTH    5   // 5 bytes TX address width
#define RX_ADR_WIDTH    5   // 5 bytes RX address width
#define TX_PLOAD_WIDTH  20  // 20 bytes TX payload
#define RX_PLOAD_WIDTH  20  // 20 bytes TX payload

typedef unsigned char BYTE;
typedef unsigned char uchar;
//****************************************************************//
// SPI(nRF24L01) commands
#define READ_REG        0x00  // Define read command to register
#define WRITE_REG       0x20  // Define write command to register
#define RD_RX_PLOAD     0x61  // Define RX payload register address
#define WR_TX_PLOAD     0xA0  // Define TX payload register address
#define FLUSH_TX        0xE1  // Define flush TX register command
#define FLUSH_RX        0xE2  // Define flush RX register command
#define REUSE_TX_PL     0xE3  // Define reuse TX payload register command
#define NOP             0xFF  // Define No Operation, might be used to read status register


//***************************************************//
// SPI(nRF24L01) registers(addresses)
#define CONFIG          0x00  // 'Config' register address
#define EN_AA           0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR       0x02  // 'Enabled RX addresses' register address
#define SETUP_AW        0x03  // 'Setup address width' register address
#define SETUP_RETR      0x04  // 'Setup Auto. Retrans' register address
#define RF_CH           0x05  // 'RF channel' register address
#define RF_SETUP        0x06  // 'RF setup' register address
#define STATUS          0x07  // 'Status' register address
#define OBSERVE_TX      0x08  // 'Observe TX' register address
#define CD              0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0      0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1      0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2      0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3      0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4      0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5      0x0F  // 'RX address pipe5' register address
#define TX_ADDR         0x10  // 'TX address' register address
#define RX_PW_P0        0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1        0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2        0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3        0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4        0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5        0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS     0x17  // 'FIFO Status Register' register address

//***************************************************************//
//                   FUNCTION's PROTOTYPES  //
/****************************************************************/
// void SPI_Init(BYTE Mode);     // Init HW or SW SPI
 BYTE SPI_RW(BYTE byte);                                // Single SPI read/write
 BYTE SPI_Read(BYTE reg);                               // Read one byte from nRF24L01
 BYTE SPI_RW_Reg(BYTE reg, BYTE byte);                  // Write one byte to register 'reg'
 BYTE SPI_Write_Buf(BYTE reg, BYTE *pBuf, BYTE bytes);  // Writes multiply bytes to one register
 BYTE SPI_Read_Buf(BYTE reg, BYTE *pBuf, BYTE bytes);   // Read multiply bytes from one register
//*****************************************************************/

void inerDelay_us(unsigned char n);

void init_io(void) ;

void SetRX_Mode(void);
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf);
void nRF24L01_TxPacket(unsigned char * tx_buf);


extern uchar const TX_ADDRESS[TX_ADR_WIDTH];//TX address
extern uchar const RX_ADDRESS[RX_ADR_WIDTH];//;RX address


#endif   //_NRF_24L01_
