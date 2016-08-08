/*

    File: functions.h
    Description: ���򹫹�����ͷ�ļ�
    Updated: Jul 10 2016
    Author : Hafrans Newton

*/
#include "project.h"
#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

    #ifdef __cplusplus
    extern "C" {
    #endif // defined

    /**
     *  ����ַ������Ƿ�������
     * @param char *telphone ����ַ�
     * @return BOOLEAN True - 1 ���� False - 0����
     * @author Hafrans
     * @date 07 / 11 /2016
     */
     _EXT BOOLEAN testNumber(const char *telphone);

    /**
     * �����׼���뻺����
     * @author Hafrans
     */
     _EXT void stdinClear();


    /**
     *  ȥ���ַ������˿հ�
     * @param char text[] ������ַ���
     * @return char * ������ַ���
     * @author Hafrans
     */
    _EXT char *trim(char text[]);

    /**
     * ��ȡ��ǰʱ����ַ���
     * @param int TYPE ��������
     * type = 1 ʱ 2016-07-10
     * type = 2 ʱ 11:52:20
     * type = 3 ʱ 2016-07-10 11:52:20
     * @return char * ������ַ���
     * @author Hafrans
     * ע�⣺�����һЩ�ڴ�й©������ʹ��free()���ܽ����ͷš�
     */
    _EXT char *getNowTime(int type);

    /**
     * ������ ������򷵻ؽ��
     * @author Hafrans Newton
     *
     */
     _EXT void dump(int temp);

    /*****************************************************
        Uint ������

            C_UINT test = containerInitUint();
            dump(containerPushBackUint(test,1));
            dump(containerPushBackUint(test,2));
            dump(containerPushBackUint(test,5));
            dump(containerPushBackUint(test,8));
            dump(containerPushBackUint(test,4));
            unsigned int *data = containerGetDataUint(test);
            if(data != NULL)
                for(int i = 0;data[i] != 0;++i)
                {
                    printf("%d\n",data[i]);
                }
            containerFreeUint(test);

    ******************************************************/
      #ifndef C_UINT
      #define C_UINT unsigned int **
      #endif // C_UINT

         /**
          * Unsigned int ����������ʼ��
          * @return C_UINT ������Դ����
          */
         _EXT C_UINT containerInitUint();

           /**
            *   Unsigned int ��������Ԫ�����
            *   @param C_UINT data ������Դ
            *   @param unsigned int E ����Ԫ��
            *   @return
            *
            */
         _EXT BOOLEAN containerPushBackUint(C_UINT data,unsigned int E);

        /**
          *    Unsigned int ����������ȡʵ��ֵ
          *   @param C_UINT data ������Դ
          *   @param unsigned int unsigned int ��Դֵ
          *
          */
        _EXT unsigned int *containerGetDataUint(C_UINT data);

         /**
           *    Unsigned int ���������ͷ���Դ
           *   @param C_UINT data ������Դ
           *   @return BOOLEAN
           */
        _EXT BOOLEAN containerFreeUint(C_UINT data);




    #ifdef __cplusplus
    }
    #endif // defined


#endif // _FUNCTIONS_H
