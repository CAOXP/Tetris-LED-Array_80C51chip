
#include "MCUREG.H"
#include "SYSCONFIG.H"
#include "RAMDisp.h" 


//INT8U idata DisRAM[LINE_NUM][ROW_NUM]

void dly(INT16U I)
{
    while(I--);
}





/******************************************************************** 
* 名称: void SetPic()
* 功能: 在指定坐标放置图片
*
* 作者: fpdz,0808
***********************************************************************/
void SetPic()
{}














void ShowChara(INT8U Chara[16][2])  //向左
{
    INT8U row,line;
    INT8U temp;

    for (temp=0; temp<16; temp++)
    {
        for (line=0; line<16; line++)   //一行一行处理
        {
            for (row=0; row<3; row++)
            {
                DisRAM[line][row]<<=1;
                if(DisRAM[line][row+1] & 0x80)
                    DisRAM[line][row] |=1;
            }
            DisRAM[line][row]<<=1;    

            if(  Chara[line][temp>>3]  & ( 0x80>>(temp&0x07) ) )
                DisRAM[line][row] |=1;
        }
        //dly(50);

    }
}


void ShowChara2(INT8U Chara[16][2]) //向上
{
    INT8U line;
    INT8U temp;
    for (temp=0; temp<16; temp++)
    {
        for (line=0; line<15; line++)   //一行一行处理
        {
            DisRAM[line][0] = DisRAM[line+1][0];
            DisRAM[line][1] = DisRAM[line+1][1];            
        }

        DisRAM[line][0] = Chara[temp][0];
        DisRAM[line][1] = Chara[temp][1];  

        dly(200);
    }

}

void ShowChara3(INT8U Chara[16][2]) //向下
{
    INT8U line;
    INT8U temp;
    for (temp=16; temp>0; temp--)
    {
        for (line=15; line>0; line--)   //一行一行处理
        {
            DisRAM[line][0] = DisRAM[line-1][0];
            DisRAM[line][1] = DisRAM[line-1][1];            
        }

        DisRAM[line][0] = Chara[temp-1][0];
        DisRAM[line][1] = Chara[temp-1][1];  

        dly(200);
    }

}
