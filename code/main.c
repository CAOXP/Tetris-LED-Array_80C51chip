/* Copyright (c) fpdz
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
 * 
 *
 *
 * # Version 1.0.3 CaoXiangpeng 20081029 #
 */

/***********************************************************************/
/*                                                                     */
/*                xp-Tetris Program  based on LED_Screen               */
/*                                                                     */
/*                     All Rights Reserved                             */
/*                                                                     */
/* IDE     : KEIL UV2                                                  */
/* Language: C51 (in all project files)                                */
/* Hardware: STC89C52RC 11.092Mhz                                      */
/*                                                                     */
/* Instruction: 1.this project is for a Simple xp-Tetris Game          */
/*                base on a 32*16 LED-Screen                           */
/*              2.User can set the values of x and y what you want     */
/*                to make a Game Screen.                               */
/*                In DispROM.H file.                                   */
/*                                                                     */
/* Author  : fpdz                          */
/* Date    : 13,Aug,2008                                               */
/*                                                                     */
/* Note    : project created:  5,Aug,2008,                             */
/*           latest modified: 13,Aug,2008 ,23:30                       */
/***********************************************************************/


#include "MCUREG.H"
#include "SYSCONFIG.H"

#include "RAMDisp.h"
//#include "UART.H"
#include "KeyInput.h"

#include "Block.h"


main()
{
    INT8U keytime;
	RAMDispInit();
	INT_ON();  

    while(Getkey()==0);

TETRIS:
    ClearTetrisScreen();    //清理屏幕
	
	while(1)
    {

        if(BlockGenerate()==FAILURE)    //生成一个方块
        {
            while(Getkey()==0);
            goto TETRIS;
        }


        while(1)            //操作这个方块
        {
            keytime = 5;
            while(keytime--)
            {
                Delay(3);
                switch( Getkey() )
                {
                    case 1:  MoveLeft();    break;
                    case 2:  TurnStatus();  break;
                    case 3:  MoveRight();   break;
                }
            }

            if(MoveDown() == FAILURE)
            {
                ClearAreaFull();
                break;
            }

        }
    }

}


//-----------------------------End of File-----------------------------//
