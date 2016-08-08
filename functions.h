/*

    File: functions.h
    Description: 程序公共函数头文件
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
     *  检测字符串里是否都是数字
     * @param char *telphone 检测字符
     * @return BOOLEAN True - 1 正常 False - 0错误
     * @author Hafrans
     * @date 07 / 11 /2016
     */
     _EXT BOOLEAN testNumber(const char *telphone);

    /**
     * 清除标准输入缓冲区
     * @author Hafrans
     */
     _EXT void stdinClear();


    /**
     *  去除字符串两端空白
     * @param char text[] 输入的字符串
     * @return char * 输出的字符串
     * @author Hafrans
     */
    _EXT char *trim(char text[]);

    /**
     * 获取当前时间的字符串
     * @param int TYPE 日期类型
     * type = 1 时 2016-07-10
     * type = 2 时 11:52:20
     * type = 3 时 2016-07-10 11:52:20
     * @return char * 输出的字符串
     * @author Hafrans
     * 注意：会造成一些内存泄漏，建议使用free()功能进行释放。
     */
    _EXT char *getNowTime(int type);

    /**
     * 调试用 输出程序返回结果
     * @author Hafrans Newton
     *
     */
     _EXT void dump(int temp);

    /*****************************************************
        Uint 简单容器

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
          * Unsigned int 线性容器初始化
          * @return C_UINT 容器资源类型
          */
         _EXT C_UINT containerInitUint();

           /**
            *   Unsigned int 线性容器元素添加
            *   @param C_UINT data 容器资源
            *   @param unsigned int E 新增元素
            *   @return
            *
            */
         _EXT BOOLEAN containerPushBackUint(C_UINT data,unsigned int E);

        /**
          *    Unsigned int 线性容器获取实际值
          *   @param C_UINT data 容器资源
          *   @param unsigned int unsigned int 资源值
          *
          */
        _EXT unsigned int *containerGetDataUint(C_UINT data);

         /**
           *    Unsigned int 线性容器释放资源
           *   @param C_UINT data 容器资源
           *   @return BOOLEAN
           */
        _EXT BOOLEAN containerFreeUint(C_UINT data);




    #ifdef __cplusplus
    }
    #endif // defined


#endif // _FUNCTIONS_H
