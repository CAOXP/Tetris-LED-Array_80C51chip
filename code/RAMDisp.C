/* Copyright (c) 2008 xpstudio, CaoXiangpeng
 * <xpstudio2003@yahoo.com.cn>
 * <http://xpstudio2003.blog.163.com>
 * <http://blog.ednchina.com/xpstudio2003>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 */
 
/***********************************************************************/
/*                                                                     */
/*                           RAMdisp.C                                 */
/*                                                                     */
/*                       All rights reserved                           */
/*                                                                     */
/* Project : xp-Tetris Program Project                                 */
/* IDE     : Keil uV2                                                  */
/*                                                                     */
/* Instruction: 1.the basic drive to Flash Data to the LED-Screen      */
/*                user can change the TH0 TL0 of timer0                */
/*                to change the freqence.                              */
/*                In file RAMdisp.H                                    */
/*                                                                     */
/* Date   : 13,Aug,2008                                                */
/* Author : CaoXiangpeng xpstudio2008                                  */
/*                                                                     */
/*          latest modified: 13,Aug,2008 ,23:30                        */
/***********************************************************************/

#include "MCUREG.H"
#include "SYSCONFIG.H"
#include "RAMDisp.h" 

/***********************************************************************
* 名称: INT8U   GrayScale;
* 功能: 亮度控制变量,指示显示屏的亮度,共10个级别
*
* 作者: 曹香鹏,XPSTUDIO2008,0808
***********************************************************************/
INT8U   GrayScale;


/***********************************************************************
* 名称: INT8U idata DisRAM[ROW_NUM][ROW_NUM]
* 功能: 显存,,,对应于显示屏
*			行数:LINE_NUM
*			列数:ROW_NUM
* 作者: 曹香鹏,XPSTUDIO2008,0808
***********************************************************************/
INT8U idata DisRAM[LINE_NUM][ROW_NUM]=
{/*--  当前宽度x高度=32x16  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x66,0x7C,0x00,0x32,0x66,0x66,0x00,
0x30,0x3C,0x66,0x18,0x30,0x18,0x66,0x0C,0x30,0x3C,0x66,0x06,0x32,0x66,0x66,0xF3,
0x1E,0x66,0x7C,0x06,0x00,0x00,0x60,0x0C,0x00,0x00,0x60,0x18,0x00,0x00,0x60,0x00,
0x55,0x55,0x55,0x55,0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,0xAA,0xAA,0xAA,0xAA,
};

/**********************************************************************
* 名称: SendSrlDt8(INT8U sData)
* 功能: 通过6B595输出数据, 一个字节.
*
* 作者: 曹香鹏,XPSTUDIO2008,0808
***********************************************************************/
void SendSrlDt8(INT8U sData)
{
    INT8U i;
    set595_SRCLR();      //移位寄存器使能
    clr595_RCK();
    for(i=8; i>0; i--)
    {
        clr595_SRCK();
        if( sData&0x80 ) set595_SERIN();
        else             clr595_SERIN();
        sData<<=1;
        set595_SRCK();   //上升沿移入数据
    }
    set595_RCK();        //上升沿输出数据
}



/********************************************************************** 
* 名称: RAMDispInit()
* 功能: 显示的初始化程序,初始化定时器0,亮度级别
*
* 作者: 曹香鹏,XPSTUDIO2008,0808
***********************************************************************/
void RAMDispInit()
{
	TMOD &=  0xF0;		//定时器0,工作方式 1
	TMOD |=  0x01;

    TH0  = T0INIT_H;    //定时初值
    TL0  = T0INIT_L;

    ET0  = TRUE;        //开定时器0 中断
    TR0  = TRUE;        //定时器0运行

    GrayScale = GRAY_DEFAULT;    //亮度初值
}



/********************************************************************** 
* 名称: void Timer0_INT(void) interrupt 1
* 功能: 将显存里的内容显示出来,利用定时器0
*
* 作者: 曹香鹏,XPSTUDIO2008,0808
***********************************************************************/
void Timer0_INT(void) interrupt 1
{
    static INT8U 	T0intCnt	= 0;    //用来记录进入中断的次数
	static INT8U	LineScanCnt = 0;	//用来记录扫描到哪一行

    TH0  = T0INIT_H;   					//重新加载初值
    TL0  = T0INIT_L;

    T0intCnt ++ ;

	if(T0intCnt == GrayScale)CloseOut();//亮度控制


	if(T0intCnt < 10) return;			//定时器中断次数
	T0intCnt = 0;

	LineScanCnt ++;
	if(LineScanCnt == LINE_NUM)			//一共LINE_NUM行数据
		LineScanCnt = 0;	

	CloseOut();							//1.关闭输出,防止拖影
	SendSrlDt8(DisRAM[LineScanCnt][0]);	//2.输出数据
	SendSrlDt8(DisRAM[LineScanCnt][1]);
	SendSrlDt8(DisRAM[LineScanCnt][2]);
	SendSrlDt8(DisRAM[LineScanCnt][3]);
	ScanIO = LineScanCnt|(ScanIO&0XF0);	//3.确定扫描第LineScanCnt行
	OpenOut();							//4.打开输出,显示内容
}

#define     dlydly  delayms(10)
/********************************************************************** 
* 名称: void SetPix(INT8U x, INT8U y) 
* 功能: 将坐标x,y点的点置1
*
* 作者: 曹香鹏,XPSTUDIO2008,0813
***********************************************************************/
void SetPix(INT8U x, INT8U y) 
{
    DisRAM[y][x>>3] |=  0x80 >>(x&0x07);
    dlydly;
}
/********************************************************************** 
* 名称: void ClearPix(INT8U x, INT8U y) 
* 功能: 将坐标x,y点的点清0
*
* 作者: 曹香鹏,XPSTUDIO2008,0813
***********************************************************************/
void ClearPix(INT8U x, INT8U y) 
{
    DisRAM[y][x>>3] &= ~(0x80>>(x&0x07));
    dlydly;
}

/********************************************************************** 
* 名称: void AntiPix(INT8U x, INT8U y) 
* 功能: 将坐标x,y点的点取反
*
* 作者: 曹香鹏,XPSTUDIO2008,0813
***********************************************************************/
void AntiPix(INT8U x, INT8U y) 
{
    DisRAM[y][x>>3] ^=  0x80 >>(x&0x07);
    dlydly;
}

//-----------------------------End of File-----------------------------//
