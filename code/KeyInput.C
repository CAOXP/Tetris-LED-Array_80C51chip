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
/*                         KeyInput.C                                  */
/*                                                                     */
/*                       All rights reserved                           */
/*                                                                     */
/* Project : xp-Tetris Program Project                                 */
/* IDE     : Keil uV2                                                  */
/*                                                                     */
/* Instruction: 1.Basic Key input functions,                           */
/*              2.User can change this file to anthor Key-Driver-Prog. */
/*                                                                     */
/* Date   : 13,Aug,2008                                                */
/* Author : CaoXiangpeng xpstudio2008                                  */
/*                                                                     */
/*          latest modified: 13,Aug,2008 ,23:30                        */
/***********************************************************************/


#include "MCUREG.H"
#include "SYSCONFIG.H"



sbit KEY1=P0^0;//后面的键
sbit KEY2=P0^1;//
sbit KEY3=P0^2;//前面的键

INT16U DelayTime=0;


//键盘函数
INT8U keyget()
{
    KEY1=1;KEY2=1;KEY3=1;
    if(KEY1==0) return 1;
    if(KEY2==0) return 2;
    if(KEY3==0) return 3;
    return 0;
}

bit bKey=0;
INT8U Getkey()
{
    INT8U keytemp;
    DelayTime=0;
    keytemp=keyget();
    if(keytemp==0)return 0;

    while(1)
    {
        Delay(2);DelayTime++;
        if(keyget() == 0)//去抖,按键松开,返回键值
        {
            bKey=0;
            return keytemp;
        }
        
        if(bKey)
        {
            if(DelayTime==4)return keytemp; 
        }
    
        if(DelayTime>25)//不能超过这个时间长度吧
        {   
            bKey=1;
            return keytemp;
        }
    }//while(1)
}


//-----------------------------End of File-----------------------------//
