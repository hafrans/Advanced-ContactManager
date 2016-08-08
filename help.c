/*
    调试用
    当打开调试模式的时候
    这个就会起到作用
    代替main.c作为程序主文件

*/
#include "project.h"
#ifdef DEBUG
int main()
{

    init();
    loadKey();
//    coreKeyCheck();
//    puts("OK");
//    Sleep(1000);
    coreMenuInit();

    Exit();
    return 0;
}

#endif // DEBUG
