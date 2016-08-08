/*
    File: functions.c
    Description: 程序公共函数源代码
    Updated: Jul 10 2016
    Author : Hafrans Newton

*/
#include "functions.h"

/**
 * 清除标准输入缓冲区
 * @author Hafrans
 */
 void stdinClear()
 {
    int c = 0;
    while((c = getchar())!= EOF || c != '\n');
 }


/**
 * 去掉字符串两端的空白字符
 * @param char text[] 字符串
 * @return char * 处理过的字符串
 * @author Hafrans
 */
char *trim(char text[]){
    if(text){
        char *bottom = text+strlen(text)-1;
        while(text < bottom && isspace(*text))text++;
        while(text < bottom && isspace(*bottom))*bottom-- = '\0';
    }
    return text;
}

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
char *getNowTime(int type){
    char *text = (char *)calloc(256,sizeof(char));
    char *format = NULL;
    struct tm  *ptr;
    time_t nowTime = time(NULL);
    ptr = localtime(&nowTime);
    switch(type){
        case 1:
            format = "%Y/%m/%d";
            break;
        case 2:
            format = "%H:%M:%S";
            break;
        default:
            format = "%Y/%m/%d %H:%M:%S";
            break;
    }
    strftime(text,sizeof(char)*256,format,ptr);
    return text;
}

/**
 *  检测字符串里是否是数字
 * @param char *telphone 检测字符
 * @return BOOLEAN True - 1 正常 False - 0错误
 * @author Hafrans
 * @date 07 / 11 /2016
 */
 BOOLEAN testNumber(const char *telphone)
 {
     int i = 0;
     if(telphone == NULL)
        return False;
     size_t len = strlen(telphone);
     for(i = 0;i<len;i++)
     {
        if(!isdigit(telphone[i]))
            return False;
     }
     return True;
 }



  #ifndef C_UINT
  #define C_UINT unsigned int **
  #endif // C_UINT
  /***
     正整数线性容器
     @author Hafrans Newton
     @date 12 Jul 2016
  ***/
/**
  * 正整数线性容器初始化
  * @return C_UINT 容器资源类型
  */
  C_UINT containerInitUint()
  {
      C_UINT cdata = (C_UINT)malloc(sizeof(unsigned int *));
      unsigned int *data = (unsigned int *)malloc(sizeof(unsigned int));
                   *data = 0;
                   *cdata = data;
      return cdata;
  }

  /**
    *   正整数线性容器元素新增
    *   @param C_UINT cdata 容器资源
    *   @param unsigned int E 新增元素
    *   @return
    *
    */
  BOOLEAN containerPushBackUint(C_UINT cdata,unsigned int E)
  {
      unsigned int *data = *cdata;
      if(data == NULL)
        return False;
      unsigned int *tmpdata = data;
      data = (unsigned int *)realloc(data,sizeof(unsigned int)*(++(*data)+1));
      if(data == NULL){
        data = tmpdata;
        (*data)--;
        *cdata = data;
        return False;
      }else{
        data[(*data)] = E;
      }
      *cdata = data;
      return True;
  }

  /**
   *   正整数线性容器
   *   @param C_UINT cdata 容器资源
   *   @param unsigned int unsigned int 资源值
   *
   */
  unsigned int *containerGetDataUint(C_UINT cdata)
  {
     unsigned int *data = *cdata;
     if(data == NULL)
        return NULL;
      unsigned int *tmpdata = data;
      data = (unsigned int *)realloc(data,sizeof(unsigned int)*(++(*data)+1));
      if(data == NULL){
        data = tmpdata;
        return NULL;
      }else{
        data[*data] = 0;
      }
      return ++data;
  }

   /**
   *   正整数线性容器资源释放
   *   @param C_UINT data 容器资源
   *   @return BOOLEAN
   */
   BOOLEAN containerFreeUint(C_UINT data)
   {
       if(data == NULL)
            return True;
       else
            free(*data);
            data = NULL;
        return True;
   }

/**
 * 调试用 输出程序返回结果
 * @author Hafrans Newton
 *
 */
 void dump(int temp){
    if(temp == True)
        puts("True");
    else if(temp == False)
        puts("False");
    else
        printf("%d\n",temp);
    return ;
 }
