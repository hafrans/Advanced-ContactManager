/*
    File: project.h
    Description: ����ͷ�ļ�
    Updated: Jul 10 2016
    Author : Hafrans Newton

*/
#ifndef _PROJECT_H
#define _PROJECT_H
    //����ϵͳ��
    #include <stdio.h>
    #include <stdlib.h>
    #include <windows.h>
    #include <ctype.h>
    #include <math.h>
    #include <string.h>
    #include <assert.h>
    #include <conio.h>
    #include <time.h>
    #include <stdarg.h>
    #include <unistd.h>
    //����ȫ�ֳ���
    /***���Կ�ʼ��***/
    /**����ģʽ��main�����ļ���help.c��*/
    //#define DEBUG
    ///////////////////
    #define _EXT extern
    #define BUFFSIZE 4096 //Ĭ�ϻ�������С
    //Boolean hack
    #define BOOLEAN int
    #define True    1
    #define False   0
    //����ϵͳ�ļ�
    #include "functions.h"
    #include "datastruct.h"
    #include "filesystem.h"
    #include "console.h"
    #include "core.h"

#endif // _PROJECT_H
