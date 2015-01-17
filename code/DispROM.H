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
/*                           DispROM.H                                 */
/*                       All rights reserved                           */
/* Project : xp-Tetris Program Project                                 */
/* IDE     : Keil uV2                                                  */
/* Date   : 13,Aug,2008                                                */
/* Author : fpdz                             */
/*                                                                     */
/*          latest modified: 13,Aug,2008 ,23:30                        */
/***********************************************************************/



#include "MCUREG.H"
#include "SYSCONFIG.H"


//俄罗斯方块的图形范围
#define     TRS_Y_MIN           0   //y方向
#define     TRS_Y_MAX           15  //Y方向

#define     TRS_X_MIN           8   //X方向不包括此点
#define     TRS_X_MAX           23  //X方向不包括此点

//----------------------------------------------------------------------//
//             以下宏定义为自动生成,不用修改                            //
//----------------------------------------------------------------------//


#define     XBYTES_HEAD_NUM     (TRS_X_MIN % 8)
#define     XBYTES_END_NUM      (TRS_X_MAX % 8)

INT8U code  XBytesHead[] = {0x7f,0x3f,0x1f,0x0f,0x07,0x03,0x01,0xff};
INT8U code  XBytesEnd[]  = {0xff,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe};

#define     XBYTES_HEAD         XBytesHead[XBYTES_HEAD_NUM]
#define     XBYTES_END          XBytesEnd[XBYTES_END_NUM]



            //在RAM中占的第一个字节序号
#define     TRS_X_BYTE_MIN      ( (TRS_X_MIN+1) >> 3 )
            //在RAM中占的最后个字节序号
#define     TRS_X_BYTE_MAX      ( (TRS_X_MAX-1) >> 3 )
            //X方向所占字节数
#define     TRS_X_BYTES         ( TRS_X_BYTE_MAX - TRS_X_BYTE_MIN + 1)




/********************************************************************** 

    1.方块图标坐标举例:

                 7高位4   3低位0
              ┌─────────┐
              │□□□□  ○■□□│
              │□□□□  ■■■□│
              │□□□□  □□□□│
              │□□□□  □□□□│
              └─────────┘
        对于上幅方块图像,,,○所示处为(0,0)点,,,


    2.RAM坐标举例 32X16(x,y):
           ┌──────────────┐
           │(0, 0)  (1,0)  ...  (32, 0) │  
           │(0, 1)                      │
           │ .                          │
           │ .                          │
           │ .                          │
           │(0,16)     ...      (32,16) │  
           └──────────────┘
***********************************************************************/


/********************************************************************** 
* 名称: INT8U code TtrsBlck[]
* 功能: 方块的图形代码,,每四个字节表示一个图形
*       每行表示一个内容,,只表示了第一个状态的样子
*       其它按顺时针转图形可得      
*
* 作者: fpdz,12,Aug,2008
***********************************************************************/
INT8U code TtrsBlck[]={ //
/*  ■
  ■■■        Middle      0   0
*/
0x04,0x0E,0x00,0x00,0x08,0x0C,0x08,0x00,0x0E,0x04,0x00,0x00,0x04,0x0C,0x04,0x00,
/*■
  ■■■        Left        16  1
*/
0x08,0x0E,0x00,0x00,0x0C,0x08,0x08,0x00,0x0E,0x02,0x00,0x00,0x04,0x04,0x0C,0x00,
/*■■■
  ■            Right       32  2
*/
0x02,0x0E,0x00,0x00,0x08,0x08,0x0C,0x00,0x0E,0x08,0x00,0x00,0x0C,0x04,0x04,0x00,
/*■■
    ■■        Z           48  3
*/
0x0C,0x06,0x00,0x00,0x04,0x0C,0x08,0x00,
/*  ■■
  ■■          Z_Reversal  56  4
*/
0x06,0x0C,0x00,0x00,0x08,0x0C,0x04,0x00,


/*■■■■      Line        64  5
*/
0x0F,0x00,0x00,0x00,0x08,0x08,0x08,0x08,

/*■■
  ■■          Stone       72  6
*/
0x0C,0x0C,0x00,0x00
};


/******************************************************************** 
* 名称: INT8U code TtrsBlckPoint[]
* 功能: 图形指针数组
*       指示了各种方块在图形代码里的最初指针
*
* 作者: fpdz,12,Aug,2008
***********************************************************************/
INT8U code TtrsBlckPoint[ ]={    0, //Middle
                                16, //Left
                                32, //Right
                                48, //Z
                                56, //Z-twist
                                64, //Line
                                72  //Stone
                                };


/******************************************************************** 
* 名称: INT8U code TtrsBlckStsNum[]
* 功能: 方块状态个数
*       表示每种方块的状态的个数       
*
* 作者: fpdz,12,Aug,2008
***********************************************************************/
INT8U code TtrsBlckStsNum[ ]={  4,  //Middle
                                4,  //Left
                                4,  //Right 
                                2,  //Z
                                2,  //Z-twist
                                2,  //Line
                                1   //Stone
                                };




//-----------------------------End of File-----------------------------//
