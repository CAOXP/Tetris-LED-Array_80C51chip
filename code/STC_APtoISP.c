/************************************************************
**
**                       STC AP to ISP File 
**
** Written by : fpdz
**
** Note:你只需要把STC_APtoISP.H文件包含到你的工程中
        并在你的系统初始化文件里添加Init_APtoISP_byUart()即可
**
*************************************************************/

#define SYS_AP2ISP          0x22
#define SYS_AP2AP           0x11

#include "SYSCONFIG.H"

sfr ISP_CONTR = 0xe7;
sfr PCON = 0x87;
sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL1  = 0x8B;
sfr TH1  = 0x8D;
sfr SCON = 0x98;
sfr SBUF = 0x99;
sfr IE   = 0xA8;
sfr IP   = 0xB8;
sbit TR1  = TCON^6;
sbit TI   = SCON^1;
sbit RI   = SCON^0;
sbit ES   = IE^4;
sbit EA   = IE^7;
sbit PS   = IP^4;

//********************************************************
//   发送一个1个字节命令
//********************************************************
void SendComm(INT8U dat)
{
    ES  = FALSE;
	TI  = FALSE;
	SBUF= dat;
	while(!TI);
	TI  = FALSE;
    ES  = TRUE;
}
//********************************************************
//   UART中断程序
//********************************************************
void UartService()  interrupt 4
{
    INT8U i;
    if( RI == TRUE )
    {
        RI = FALSE;
        i  = SBUF;

        if(i == SYS_AP2ISP)
        {
            ISP_CONTR = 0x60;//软复位AP->ISP,可下程序
        }
        else if(i == SYS_AP2AP)
        {
            ISP_CONTR = 0x20;//软复位AP->AP
        }
        else
            SendComm(i);

    }
    else
        TI  =   FALSE;

}

//********************************************************
//   UART  初始化程序
//********************************************************
void UartInit()
{
    SCON &= 0x0F;   //0101 0000 uart 工作方式1,
    SCON |= 0x50;
    TMOD &= 0x0F;   //Timer1,WorkMode 1
    TMOD |= 0x20;

    TH1   = 0xfd;   //0xfd
    TL1   = 0xfd;

    TR1   = TRUE;
    ES    = TRUE;   //init Interrupts

    SendComm('R');
    SendComm('d');
    SendComm('y');
}
