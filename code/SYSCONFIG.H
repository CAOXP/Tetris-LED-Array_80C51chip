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
/*                           sysConfig.H                               */
/*                       All rights reserved                           */
/* Project : xp-Tetris Program Project                                 */
/* IDE     : Keil uV2                                                  */
/* Date   : 13,Aug,2008                                                */
/* Author : fpdz                                  */
/*                                                                     */
/*          latest modified: 13,Aug,2008 ,23:30                        */
/***********************************************************************/


#ifndef __SYSCONFIG_H__
#define __SYSCONFIG_H__

	typedef     unsigned char       BOOL    ; 
	typedef     unsigned char       INT8U   ;
	typedef     unsigned int        INT16U  ;  
	typedef     unsigned long       INT32U  ;
	typedef     float               FLOAT   ;

	
	#define     TRUE                1
	#define     FALSE               0
    #define     NULL                0
	#define		BIT(x)				(1<<(x))

    #define     FAILURE             0
    #define     SUCCESS             1

	#define		INT_ON()			(EA = TRUE)


    extern void Delay(INT8U ii);
    extern void delayms(INT8U i);


#endif
