/*
    File: functions.c
    Description: ���򹫹�����Դ����
    Updated: Jul 10 2016
    Author : Hafrans Newton

*/
#include "functions.h"

/**
 * �����׼���뻺����
 * @author Hafrans
 */
 void stdinClear()
 {
    int c = 0;
    while((c = getchar())!= EOF || c != '\n');
 }


/**
 * ȥ���ַ������˵Ŀհ��ַ�
 * @param char text[] �ַ���
 * @return char * ��������ַ���
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
 * ��ȡ��ǰʱ����ַ���
 * @param int TYPE ��������
 * type = 1 ʱ 2016-07-10
 * type = 2 ʱ 11:52:20
 * type = 3 ʱ 2016-07-10 11:52:20
 * @return char * ������ַ���
 * @author Hafrans
 * ע�⣺�����һЩ�ڴ�й©������ʹ��free()���ܽ����ͷš�
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
 *  ����ַ������Ƿ�������
 * @param char *telphone ����ַ�
 * @return BOOLEAN True - 1 ���� False - 0����
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
     ��������������
     @author Hafrans Newton
     @date 12 Jul 2016
  ***/
/**
  * ����������������ʼ��
  * @return C_UINT ������Դ����
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
    *   ��������������Ԫ������
    *   @param C_UINT cdata ������Դ
    *   @param unsigned int E ����Ԫ��
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
   *   ��������������
   *   @param C_UINT cdata ������Դ
   *   @param unsigned int unsigned int ��Դֵ
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
   *   ����������������Դ�ͷ�
   *   @param C_UINT data ������Դ
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
 * ������ ������򷵻ؽ��
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
