/* Copyright (c) fpdz
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
/*                           RAMDisp.H                                 */
/*                       All rights reserved                           */
/* Project : xp-Tetris Program Project                                 */
/* IDE     : Keil uV2                                                  */
/* Date   : 13,Aug,2008                                                */
/* Author : fpdz                                  */
/*                                                                     */
/*          latest modified: 13,Aug,2008 ,23:30                        */
/***********************************************************************/

#ifndef    __RAMDISP_H__
#define    __RAMDISP_H__
/*--------------------------------------------------
			    GND |
			    VCC |
				0	|
				.	|
				3	|
----------------------------------------------------
  数据输入   SerIn  |  /SRCLR  输入移位寄存器清零
                NC  |  SRCK    移位寄存器时钟
　    　地     GND  |  RCK     输出寄存器时钟
      电源     VCC  |  /G      输出使能
--------------------------------------------------*/

	#define		T0INIT_H		0xFF	//定时器初值,决定定时时间
	#define		T0INIT_L		0xF0	
	#define		LINE_NUM		0x10	//16行
	#define		ROW_NUM			0x04	//4*8列
	#define		GRAY_DEFAULT	1		//默认亮度
	#define		GRAY_NUM		10		//亮度总级数

	sbit        B595_SRCLR       = P1^3;
	sbit        B595_SRCK        = P1^2;
	sbit        B595_RCK         = P1^1;
	sbit        B595_G           = P1^0;
	sbit        B595_SERIN       = P1^4;
	#define		ScanIO			   P2		//扫描IO口

	#define     set595_SRCLR()   (B595_SRCLR    = 1)
	#define     set595_SRCK()    (B595_SRCK     = 1)
	#define     set595_RCK()     (B595_RCK      = 1)
	#define     set595_G()       (B595_G        = 1)
	#define     set595_SERIN()   (B595_SERIN    = 1)
	#define     clr595_SRCLR()   (B595_SRCLR    = 0)
	#define     clr595_SRCK()    (B595_SRCK     = 0)
	#define     clr595_RCK()     (B595_RCK      = 0)
	#define     clr595_G()       (B595_G        = 0)
	#define     clr595_SERIN()   (B595_SERIN    = 0)


	#define     CloseOut()      set595_G()        //关闭输出
	#define     OpenOut()       clr595_G()        //打开输出
	#define     ClearReg()      clr595_SRCLR()    //清除寄存器内数据
	#define     HoldReg()       set595_SRCLR()    //保持寄存器内数据


	extern INT8U idata DisRAM[16][4];	//显存
	extern INT8U GrayScale; 			//亮度
	extern void SendSrlDt8(INT8U sData);
	extern void RAMDispInit();

    extern void SetPix(INT8U x, INT8U y) ;
    extern void ClearPix(INT8U x, INT8U y) ;
    extern void AntiPix(INT8U x, INT8U y) ;

#endif
