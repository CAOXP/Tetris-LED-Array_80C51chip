/***********************************************************************/
/*                                                                     */
/*                       Uart Drive Code File                          */
/*                                                                     */
/* C FileName : Uart.c     Uart.h                                      */
/* Written by : Xiangpeng Cao,xpstudio2008                             */
/***********************************************************************/

#include "MCUREG.H"
#include "SYSCONFIG.H"

//����1���ֽ�����
void SendComm(INT8U dat)
{
	TI=0;
	SBUF=dat;
	while(!TI)
    {
        //Ӧ�ü��볬ʱ����.!!!
    }
	TI=0;
}
//�������ɸ��ֽڵ�������UART
void Prints(INT8U str[])
{
    INT8U   i=0;
    while(1)
    {
        SendComm(str[i]);
        i++;
        if(str[i] == 0)break;
    }
}

//����ͨѶ��ʼ��
void InitUART(void)
{
    SCON |= 0x50;   //0101 0000 uart ������ʽ1,
    TMOD &= 0x0f;   //Timer1,WorkMode 1
    TMOD |= 0x20;
    TH1   = 0xfd;   //0xfd
    TL1   = 0xfd;
    TR1   = TRUE;
    ES    = FALSE;   //init Interrupts
    
    Prints("Ready...");
}
