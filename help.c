/*
    ������
    ���򿪵���ģʽ��ʱ��
    ����ͻ�������
    ����main.c��Ϊ�������ļ�

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
