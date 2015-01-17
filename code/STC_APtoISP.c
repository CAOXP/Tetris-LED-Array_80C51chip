/************************************************************
**
**                       STC AP to ISP File 
**
** Written by : fpdz
**
** Note:��ֻ��Ҫ��STC_APtoISP.H�ļ���������Ĺ�����
        �������ϵͳ��ʼ���ļ������Init_APtoISP_byUart()����
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
//   ����һ��1���ֽ�����
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
//   UART�жϳ���
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
            ISP_CONTR = 0x60;//��λAP->ISP,���³���
        }
        else if(i == SYS_AP2AP)
        {
            ISP_CONTR = 0x20;//��λAP->AP
        }
        else
            SendComm(i);

    }
    else
        TI  =   FALSE;

}

//********************************************************
//   UART  ��ʼ������
//********************************************************
void UartInit()
{
    SCON &= 0x0F;   //0101 0000 uart ������ʽ1,
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
