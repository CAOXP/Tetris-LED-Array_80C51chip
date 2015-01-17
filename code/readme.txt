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
 



这是我闲着时候做一个俄罗斯方块的游戏


说明:可以修改设定方块运行的小屏幕的大小和位置....见内部说明:
  


硬件:   1. 8块8*8的点阵组成一个32*16的矩阵
        2. 6B595  138译码电路 组成驱动电路.
        3. 单片机用的是STC宏晶的STC89C52RC+,,有8K的Flash,512的RAM.
        4. 端口定义就不用多说了,,自己看看程序里面就有了.

软件:   1. 最底层的是点阵屏的显示程序,,,具体实现是在文件RAMDisp.C里.
           可以修改相应的头文件里的设置来改显示频率和亮度.
        2. 再上面一层是Block.C文件所实现的方块具体操作子函数
           其中包括:方块的生成(没有设置为随机生成)
                    方块写入RAM里的一些函数
                    方块的移动,向左,向右,向下,
                    方块的旋转
                    游戏屏的设置
                    删除一行函数
                    删除所有满行函数
                    等等...具体可以看函数头的说明

        3.BLOCK.C文件里定义了结构体TETRIS,表示一个方块.同时下面的函数就是实现函数

          再下面定义了一个 TETRIS this, 表示当前的方块...2 中所说的程序大部分是对
          this对象的操作.

           用户可以修改游戏屏的设置,在DispROM.h文件里.
        4. DispROM.h文件说明
           这个文件是最重要的文件,,,
           1).首先是游戏屏的大小位置设置宏定义.
              只须修改 TRS_Y_MIN, TRS_Y_MAX, TRS_X_MIN, TRS_X_MAX 这四个宏即可.
              其它的由编译器自己完成. 不要修改
           2).再下面就是方块图形数据,,,一般不要修改,,,具体见说明.
           3).最下面是用准确找到方块图形的两个数组,用这两个数组可以很快的找到
              任一方块的任一状态的图形.
             
        5. 还有一个底层的驱动程序,,,KEYINPUT.C,这是一个按键的输入程序,,
           函数支持 按键的长按.
           当然你也可以换成其它的函数,,,只要接口对应就可以了,很简单.

        6. 最上面就是游戏的总体了...有了底层的一个个的函数,,游戏很好实现

           生成一个方块

           在一个循环里根据按键来操作这个方块
              同时方块在下降,,
           直到方块不能下降跳出这个循环.

           检查一下是否有满行,,有就删除

           再生成一个方块...

        7. 程序里没有加上下降速度控制,和游戏积分,要加上也很简单...

        8. 方块的底层函数做的相当独立,,你可以很容易的移植到你的系统.

           如果你用的也是点阵,,,不用怎么改
           如果你用的是液晶,,,这样刷新起来会很慢,,,你要把DisRAM这个数组的操作做成函数,
             封装起来,,只有这个元素的值变了再去刷新液晶里的值就可以了,,,

-------------------------------------------------------------------------------------------

2008,08,14 00:33
fpdz
