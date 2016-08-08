/*
    File: project.h
    Description: 工程头文件
    Updated: Jul 10 2016
    Author : Hafrans Newton

*/
#ifndef _PROJECT_H
#define _PROJECT_H
    //引入系统库
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
    //引入全局常量
    /***调试开始键***/
    /**调试模式下main函数文件在help.c下*/
    //#define DEBUG
    ///////////////////
    #define _EXT extern
    #define BUFFSIZE 4096 //默认缓冲区大小
    //Boolean hack
    #define BOOLEAN int
    #define True    1
    #define False   0
    //引入系统文件
    #include "functions.h"
    #include "datastruct.h"
    #include "filesystem.h"
    #include "console.h"
    #include "core.h"

#endif // _PROJECT_H
