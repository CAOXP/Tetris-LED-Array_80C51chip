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
/*                           Block.C                                   */
/*                                                                     */
/*                       All rights reserved                           */
/*                                                                     */
/* Project : xp-Tetris Program Project                                 */
/* IDE     : Keil uV2                                                  */
/*                                                                     */
/* Instruction: 1.some functions used when the Tetris is running       */
/*              2.Basic-Drive File                                     */
/*                                                                     */
/* Date   : 13,Aug,2008                                                */
/* Author : fpdz                            */
/*                                                                     */
/*          latest modified: 13,Aug,2008 ,23:30                        */
/***********************************************************************/

#include "MCUREG.H"
#include "SYSCONFIG.H"
#include "RAMDisp.h"
#include "DispROM.H"
//#include "UART.H"

typedef struct
{
    INT8U BlckIndex :4;     //对象序号0~6
    INT8U Status    :4;     //每个对象当前形状0~3
    INT8U code *  pPIC;     //对应于图形区的指针
    INT8U x,y;              //位置
}TETRIS;

TETRIS this;


INT8U data BufChng[4][2];   //转换过程中的临时变量区
INT8U TopLine = 1;          //保存整个区域最高的行(值最小)



#define     ShortDly()      delayms(6)
#define     LongDly()       Delay(20)

//--------------------------------------------------------------


/******************************************************************** 
* 名称: void GetPicPointer()
* 功能: 由对象 序号及状态 获得对象 图形区指针
*
* 作者: ,12,Aug,2008
***********************************************************************/
void GetPicPointer()
{
    this.pPIC   = TtrsBlck
                + TtrsBlckPoint[this.BlckIndex] 
                + (this.Status) * 4;
}
/******************************************************************** 
* 名称: INT8U ShowTetrisBlck()
* 功能: 将相应的方块的图形写进RAM里去
*       成功返回1,不成功返回0
*
* 作者: fpdz,12,Aug,2008
***********************************************************************/
INT8U ShowTetrisBlck()
{
    INT8U xtmp,Btmp;
    INT8U i;

    Btmp = this.x >> 3;     //取得图形对应的字节上..
    xtmp = this.x & 0x07;   //取得图形在对应字节上相对位置

    //修改RAM_BufChng
    for(i=0; i<4; i++)
    {
        if(xtmp <= 4)
        {
            BufChng[i][0] = this.pPIC[i] << (4 - xtmp);
            BufChng[i][1] = 0;
        }
        else// if(xtmp > 4)
        {
            BufChng[i][0] = this.pPIC[i] >> (xtmp - 4);
            BufChng[i][1] = this.pPIC[i] << (12 - xtmp);
        }        
    }

    //检查RAM相应位置是否有图像
    for(i=0; i<4; i++)
    {
        if( (DisRAM[this.y + i][Btmp])   & (BufChng[i][0]) )
            return FAILURE;
        if( (DisRAM[this.y + i][Btmp+1]) & (BufChng[i][1]) )
            return FAILURE;
    }

    //将RAM_BUFFER写进RAM里去
    for(i=0; i<4; i++)
    {
        DisRAM[this.y + i][Btmp]    |= BufChng[i][0];
        DisRAM[this.y + i][Btmp+1]  |= BufChng[i][1];
    }

    return SUCCESS;
}
/******************************************************************** 
* 名称: void ClearTetrisBlck()
* 功能: 清除原来位置上的方块
*           注意:没有去确认RAMBuff里的内容
*
* 作者: fpdz,12,Aug,2008
***********************************************************************/
void ClearTetrisBlck()
{
    INT8U Btmp;
    INT8U i;
    
    Btmp = this.x >> 3;     //取得图形对应的字节上..
    for(i=0; i<4; i++)
    {
        DisRAM[this.y + i][Btmp]    &= ~BufChng[i][0];
        DisRAM[this.y + i][Btmp+1]  &= ~BufChng[i][1];
    }
}
/******************************************************************** 
* 名称: void ClearLine(INT8U line)
* 功能: 清除一行
*       
*
* 作者: fpdz,13,Aug,2008
***********************************************************************/
void ClearLine(INT8U line)
{
    #if TRS_X_BYTES >2
    INT8U xtmp;
    #endif

    for(; line>TopLine; line--)
    {
        //先把第一个字节的一部分清0
        DisRAM[line][TRS_X_BYTE_MIN] &= ~XBYTES_HEAD;
        DisRAM[line][TRS_X_BYTE_MIN] |= DisRAM[line-1][TRS_X_BYTE_MIN]
                                        & XBYTES_HEAD;
        //中间的直接赋值 
        #if TRS_X_BYTES >2
        for(xtmp=TRS_X_BYTE_MIN+1 ; xtmp<TRS_X_BYTE_MAX;  xtmp++)
        {
            DisRAM[line][xtmp] = DisRAM[line-1][xtmp];
        }
        #endif

        #if TRS_X_BYTES > 1
        //再把最后一个字节的一部分清0
        DisRAM[line][TRS_X_BYTE_MAX] &= ~XBYTES_END;
        DisRAM[line][TRS_X_BYTE_MAX] |= DisRAM[line-1][TRS_X_BYTE_MAX] 
                                        & XBYTES_END;
        #endif

    }
}



//  以上部分为子函数
//--------------------------------------------------------------

/******************************************************************** 
* 名称: INT8U MoveLeft()
* 功能: 当前方块向左移动一格
*       成功返回SUCCESS,失败返回FAILURE
*
* 作者: fpdz,12,Aug,2008
***********************************************************************/
INT8U MoveLeft()
{
    #ifdef  CHECK_BOUND
    //先检查是否越界
    if(this.x - 1 <= TRS_X_MIN) return FAILURE;
    #endif

    //先清除原来的图像
    ClearTetrisBlck(); 

    this.x -- ;

    if( ShowTetrisBlck() == FAILURE)
    {
        this.x ++ ;     //不能移动,返回原值
        ShowTetrisBlck();
        return FAILURE;
    }
    
    return SUCCESS;
}


/******************************************************************** 
* 名称: INT8U MoveRight()
* 功能: 当前方块向右移动一格
*       成功返回SUCCESS,失败返回FAILURE
*
* 作者: fpdz,12,Aug,2008
***********************************************************************/
INT8U MoveRight()
{
    #ifdef  CHECK_BOUND
    //先检查是否越界
    if(this.x + 1 >= TRS_X_MAX) return FAILURE;    //test
    #endif

    //先清除原来的图像
    ClearTetrisBlck(); 

    this.x ++ ;

    if( ShowTetrisBlck() == FAILURE)
    {
        this.x -- ;     //不能移动,返回原值
        ShowTetrisBlck();
        return FAILURE;
    }
    
    return SUCCESS;
}


/******************************************************************** 
* 名称: INT8U MoveDown()
* 功能: 当前方块向下移动一格
*       成功返回SUCCESS,失败返回FAILURE
*
* 作者: fpdz,13,Aug,2008
***********************************************************************/
INT8U MoveDown()
{
    #ifdef  CHECK_BOUND
    //先检查是否越界
    if(this.x + 1 > TRS_Y_MAX) return FAILURE;
    #endif

    //先清除原来的图像
    ClearTetrisBlck(); 

    this.y ++ ;

    if( ShowTetrisBlck() == FAILURE)
    {
        this.y -- ;     //不能移动,返回原值
        ShowTetrisBlck();

        if(this.y < TopLine) TopLine = this.y;      //获得最高的点

        return FAILURE;
    }
    
    return SUCCESS;   
}
/******************************************************************** 
* 名称: INT8U TurnStatus()
* 功能: 方块转换状态
*       成功返回SUCCESS,失败返回FAILURE
*
* 作者: fpdz,13,Aug,2008
***********************************************************************/
INT8U TurnStatus()
{
    INT8U StatusPrev;

    #ifdef  CHECK_BOUND
    //先检查是否越界
    if(this.x + 1 > TRS_Y_MAX) return FAILURE;
    #endif

    StatusPrev = this.Status;

    //先清除原来的图像
    ClearTetrisBlck(); 

    //状态转变
    this.Status ++;
    if(this.Status >= TtrsBlckStsNum[this.BlckIndex])
        this.Status = 0;
    GetPicPointer();            //重新获得图形指针

    if( ShowTetrisBlck() == FAILURE)
    {
        this.Status = StatusPrev;   //恢复原来状态
        GetPicPointer();            //重新获得图形指针

        ShowTetrisBlck();
        return FAILURE;
    }
    
    return SUCCESS;    
}


/******************************************************************** 
* 名称: INT8U ClearAreaFull()
* 功能: 检查一个区域内是否有全1的行,并删除全1的行
*       返回删除的行数
*
* 作者: fpdz,13,Aug,2008
***********************************************************************/
INT8U ClearAreaFull()
{
    bit cFlag;
    INT8U ytmp;
    INT8U lines=0;        //保存一次清除的行数

    #if TRS_X_BYTES > 2
    INT8U xtmp,Flag;
    #endif

    for(ytmp = TRS_Y_MAX-1 ; ytmp>this.y; ytmp--)
    {
        cFlag = TRUE;
        //检查第一行是否全1
        if( (DisRAM[ytmp][TRS_X_BYTE_MIN] & XBYTES_HEAD) != XBYTES_HEAD ) cFlag = FALSE;

        //中间的直接检查    
        #if TRS_X_BYTES > 2
        Flag=FALSE;
        for(xtmp=TRS_X_BYTE_MIN+1 ; xtmp<TRS_X_BYTE_MAX;  xtmp++)
        {
            if( DisRAM[ytmp][xtmp] != 0xFF )
            {
                Flag=TRUE;
                break;
            }
        }
        if(Flag==TRUE)continue;
        #endif  
     
        #if TRS_X_BYTES > 1
        //检查最后一行是否全1
        if( (DisRAM[ytmp][TRS_X_BYTE_MAX] & XBYTES_END)  != XBYTES_END )  cFlag = FALSE;
        #endif

        //这一行满足条件
        if(cFlag == TRUE)
        {
            lines++;
            ClearLine(ytmp);
            ytmp ++;
            ShortDly();
        }    
    }
    return lines;
}


/******************************************************************** 
* 名称: INT8U BlockGenerate()
* 功能: 获得随机方块,及随机状态
*       成功返回SUCCESS,
* 注意: 这个函数应该使用随机数来生成方块,,这里没有使用,,,
*       而是使用了循环生成的方法
*
* 作者: fpdz,13,Aug,2008
***********************************************************************/
INT8U BlockGenerate()
{
    static INT8U   X=0;
    this.x = ( TRS_X_MIN + TRS_X_MAX )>>1;
    this.y = TRS_Y_MIN+1;
    this.BlckIndex = (X++)%7;
    this.Status = 0;

    GetPicPointer();
    return ShowTetrisBlck();
}


/******************************************************************** 
* 名称: void ClearTetrisScreen()
* 功能: 清方块屏,,以供游戏开始
*       
*
* 作者: fpdz,13,Aug,2008
***********************************************************************/
void ClearTetrisScreen()
{
    INT8U xtemp,ytemp;

    //取反
    for(ytemp = TRS_Y_MIN; ytemp <=TRS_Y_MAX; ytemp++)
    {
        for(xtemp = TRS_X_MIN; xtemp <=TRS_X_MAX; xtemp++)
        {
            AntiPix(xtemp, ytemp);
        }
    }
    LongDly();
    //置1
    for(ytemp = TRS_Y_MIN; ytemp <=TRS_Y_MAX; ytemp++)
    {
        for(xtemp = TRS_X_MIN; xtemp <=TRS_X_MAX; xtemp++)
        {
            SetPix(xtemp, ytemp);
        }
    }
    //清0
    for(ytemp = TRS_Y_MIN; ytemp <=TRS_Y_MAX; ytemp++)
    {
        for(xtemp = TRS_X_MIN; xtemp <=TRS_X_MAX; xtemp++)
        {
            ClearPix(xtemp, ytemp);
        }
    }
    LongDly();LongDly();
    //绘边框
    for(xtemp =TRS_X_MAX; xtemp >TRS_X_MIN; xtemp--)
    {
        SetPix(xtemp, TRS_Y_MIN);   
    }
    for(ytemp = TRS_Y_MIN; ytemp <=TRS_Y_MAX; ytemp++)
    {
        SetPix(TRS_X_MIN, ytemp);   
    }
    for(xtemp = TRS_X_MIN; xtemp <=TRS_X_MAX; xtemp++)
    {
        SetPix(xtemp, TRS_Y_MAX);   
    }
    for(ytemp = TRS_Y_MAX; ytemp >0; ytemp--)
    {
        SetPix(TRS_X_MAX, ytemp);   
    }
}


//-----------------------------End of File-----------------------------//
