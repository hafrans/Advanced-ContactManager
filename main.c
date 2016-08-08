/*
    File: main.c
    Description: 程序运行入口
    Updated: Jul 10 2016
    Author : Hafrans Newton

*/
#include "project.h"

#ifndef DEBUG
int main()
{
    init();
    coreMenuInit();
    Exit();
    return 0;
}
#endif // DEBUG

