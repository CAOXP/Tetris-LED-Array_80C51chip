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
 



����������ʱ����һ������˹�������Ϸ


˵��:�����޸��趨�������е�С��Ļ�Ĵ�С��λ��....���ڲ�˵��:
  


Ӳ��:   1. 8��8*8�ĵ������һ��32*16�ľ���
        2. 6B595  138�����· ���������·.
        3. ��Ƭ���õ���STC�꾧��STC89C52RC+,,��8K��Flash,512��RAM.
        4. �˿ڶ���Ͳ��ö�˵��,,�Լ������������������.

���:   1. ��ײ���ǵ���������ʾ����,,,����ʵ�������ļ�RAMDisp.C��.
           �����޸���Ӧ��ͷ�ļ��������������ʾƵ�ʺ�����.
        2. ������һ����Block.C�ļ���ʵ�ֵķ����������Ӻ���
           ���а���:���������(û������Ϊ�������)
                    ����д��RAM���һЩ����
                    ������ƶ�,����,����,����,
                    �������ת
                    ��Ϸ��������
                    ɾ��һ�к���
                    ɾ���������к���
                    �ȵ�...������Կ�����ͷ��˵��

        3.BLOCK.C�ļ��ﶨ���˽ṹ��TETRIS,��ʾһ������.ͬʱ����ĺ�������ʵ�ֺ���

          �����涨����һ�� TETRIS this, ��ʾ��ǰ�ķ���...2 ����˵�ĳ���󲿷��Ƕ�
          this����Ĳ���.

           �û������޸���Ϸ��������,��DispROM.h�ļ���.
        4. DispROM.h�ļ�˵��
           ����ļ�������Ҫ���ļ�,,,
           1).��������Ϸ���Ĵ�Сλ�����ú궨��.
              ֻ���޸� TRS_Y_MIN, TRS_Y_MAX, TRS_X_MIN, TRS_X_MAX ���ĸ��꼴��.
              �������ɱ������Լ����. ��Ҫ�޸�
           2).��������Ƿ���ͼ������,,,һ�㲻Ҫ�޸�,,,�����˵��.
           3).����������׼ȷ�ҵ�����ͼ�ε���������,��������������Ժܿ���ҵ�
              ��һ�������һ״̬��ͼ��.
             
        5. ����һ���ײ����������,,,KEYINPUT.C,����һ���������������,,
           ����֧�� �����ĳ���.
           ��Ȼ��Ҳ���Ի��������ĺ���,,,ֻҪ�ӿڶ�Ӧ�Ϳ�����,�ܼ�.

        6. �����������Ϸ��������...���˵ײ��һ�����ĺ���,,��Ϸ�ܺ�ʵ��

           ����һ������

           ��һ��ѭ������ݰ����������������
              ͬʱ�������½�,,
           ֱ�����鲻���½��������ѭ��.

           ���һ���Ƿ�������,,�о�ɾ��

           ������һ������...

        7. ������û�м����½��ٶȿ���,����Ϸ����,Ҫ����Ҳ�ܼ�...

        8. ����ĵײ㺯�������൱����,,����Ժ����׵���ֲ�����ϵͳ.

           ������õ�Ҳ�ǵ���,,,������ô��
           ������õ���Һ��,,,����ˢ�����������,,,��Ҫ��DisRAM�������Ĳ������ɺ���,
             ��װ����,,ֻ�����Ԫ�ص�ֵ������ȥˢ��Һ�����ֵ�Ϳ�����,,,

-------------------------------------------------------------------------------------------

2008,08,14 00:33
fpdz
