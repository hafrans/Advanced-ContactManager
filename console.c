/*
    File: console.c
    Description: ����̨����Դ��
    Updated: Jul 10 2016
    Author : wx

*/
#include "console.h"

void clear()
{
    system("cls");
}

void menuNoResult()
{
             puts("\t    --------------------------------------------------------------   ");
             puts("\t    |               ��ǸŶ�����Ҳ�������Ҫ����Ϣ��               |   ");
             puts("\t    --------------------------------------------------------------   ");
}

void menuMain()
{
     puts("\t    -------------------------------------------------------------    ");
     puts("\t    *                                                           *    ");
     puts("\t   * *               === ��ӭʹ��ͨѶ¼ϵͳ ===                 *   ");
     puts("\t  * * *                                                       * * *  ");
     puts("\t *  *  *  ------------------------------------------------   *  *  * ");
     puts("\t  * * *   |     1.������ϵ��     |     2.��ѯ��ϵ��      |    * * *  ");
     puts("\t   * *    ------------------------------------------------     * *   ");
     puts("\t    *     |     3.ɾ����ϵ��     |     4.�޸���ϵ��      |      *    ");
     puts("\t   * *    ------------------------------------------------     * *   ");
     puts("\t  * * *   |     5.����Ⱥ��       |     6.��ѯȺ��        |    * * *  ");
     puts("\t *  *  *  ------------------------------------------------   *  *  * ");
     puts("\t  * * *   |     7.ɾ��Ⱥ��       |     8.�޸�Ⱥ��        |    * * *  ");
     puts("\t   * *    ------------------------------------------------     * *   ");
     puts("\t    *     |     9.���ݹ���       |    10.���뱣��        |      *    ");
     puts("\t   * *    ------------------------------------------------     * *   ");
     puts("\t  * * *   |                   0.�˳�                     |    * * *  ");
     puts("\t *  *  *  ------------------------------------------------   *  *  * ");
     puts("\t  * * *                                                       * * *  ");
     puts("\t    *              �����빦�ܺ���������ز���^_^                *    ");
     puts("\t    *-----------------------------------------------------------*    ");
   printf("\t    |                Time: %-15s                  |\n"   ,getNowTime(3));
     puts("\t    -------------------------------------------------------------    ");
}

void menuExit()
{
    system("cls");
    puts("\n");
    puts("\t    -------------------------------------------------------------    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                 �����˳������Ժ󡭡�                    --    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                 +--��  Ц(Display)                      --    ");
    puts("\t    --                 |                                       --    ");
    puts("\t    --            By:--+--���л�(Kernel)                       --    ");
    puts("\t    --                 |                                       --    ");
    puts("\t    --                 +--�����(Logic)                        --    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                                                         --    ");
    puts("\t    -------------------------------------------------------------    ");
    return ;
}

/**
  * �����û�ID��ʾһ����ϵ����Ϣ
  * @param unsigned int ID �û�ID
  * @author wx
  * @date 2016 07 12
  */
void menuShowDetailsByID(unsigned int ID)
{
    int i = 0;//ѭ����
    pUSER obj = getAUSER(1,ID);
    char *group = NULL;
    pGroup tmp;
    if(obj == NULL) //��ָ�����
    {
        puts("����δ֪�������ڷ��ء���");
        Sleep(500);
        return ;
    }
    tmp = getGroup(1,obj->groupID);
    group  = (tmp == NULL) ? "��Ⱥ��" : tmp->name;


    clear();
    puts("\t                                                            ");
    puts("\t                                                            ++++++++ ");
    puts("\t    --------------------------------------------------------++++++++ ");
    puts("\t    -- --                                                   ++++++++ ");
    puts("\t    -- --                 ��ϵ����Ϣ����                    ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
    puts("\t    -- --                                                      --    ");
  printf("\t    -- --    ��    ����%-38s  --    \n"                 ,obj->username);
  printf("\t    -- --    ������λ��%-38s  --    \n"                  ,obj->address);
  printf("\t    -- --    ��ͥסַ��%-38s  --    \n"              ,obj->homeaddress);
  printf("\t    -- --    ��������: %-38s  --    \n"                    ,obj->email);
  printf("\t    -- ---   ����Ⱥ�飺%-15s                         --    \n",  group);
    puts("\t    -- ----- ��ϵ��ʽ��                                        --    ");
  //puts("\t    -- --                                                      --    ");
    for(i = 0;i<8;i++)
    {
        if(strcmp(obj->telphones[i],"") != 0 &&
           obj->telphones[i][0]         != 0  )
  printf("\t    -- --              %d. %-15s                      --    \n"        ,i+1,obj->telphones[i]);
    }

    puts("\t    -- --                                                      --    ");
    puts("\t    -- ---                                          @          --    ");
    puts("\t    -- -----                                     @@@@@@@@      --    ");
    puts("\t    -- ----------------------                     @@@@@@     ----    ");
    puts("\t    -- -------------------------------------     @@@@@@@@  ------    ");
    puts("\t    --------------------------------------------------------------   ");



}

/**
  * �����û�ʵ����ʾһ����ϵ����Ϣ
  * @param pUSER obj �û�ʵ��
  * @author wx
  * @date 2016 07 12
  */

void menuShowDetailsBypUSER(pUSER obj)
{
    int i = 0;//ѭ����
    char *group = NULL;
    pGroup tmp;
    if(obj == NULL) //��ָ�����
    {
        puts("����δ֪�������ڷ��ء���");
        Sleep(500);
        return ;
    }
    tmp = getGroup(1,obj->groupID);
    group  = (tmp == NULL) ? "��Ⱥ��" : tmp->name;


    clear();
    puts("\t                                                            ");
    puts("\t                                                            ++++++++ ");
    puts("\t    --------------------------------------------------------++++++++ ");
    puts("\t    -- --                                                   ++++++++ ");
    puts("\t    -- --                 ��ϵ����Ϣ����                    ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
    puts("\t    -- --                                                      --    ");
  printf("\t    -- --    ��    ����%-38s  --    \n"                 ,obj->username);
  printf("\t    -- --    ������λ��%-38s  --    \n"                  ,obj->address);
  printf("\t    -- --    ��ͥסַ��%-38s  --    \n"              ,obj->homeaddress);
  printf("\t    -- --    ��������: %-38s  --    \n"                    ,obj->email);
  printf("\t    -- ---   ����Ⱥ�飺%-15s                         --    \n"  ,group);
    puts("\t    -- ----- ��ϵ��ʽ��                                        --    ");
  //puts("\t    -- --                                                      --    ");
    for(i = 0;i<8;i++)
    {
        if(strcmp(obj->telphones[i],"") != 0 &&
           obj->telphones[i][0]         != 0  )
  printf("\t    -- --              %d. %-15s                      --    \n"        ,i+1,obj->telphones[i]);
    }

    puts("\t    -- --                                                      --    ");
    puts("\t    -- ---                                          @          --    ");
    puts("\t    -- -----                                     @@@@@@@@      --    ");
    puts("\t    -- ----------------------                     @@@@@@     ----    ");
    puts("\t    -- -------------------------------------     @@@@@@@@  ------    ");
    puts("\t    --------------------------------------------------------------   ");



}


/**
 *  ������Ϣ��ʾһ����ʱ�û�����������ӻ��޸�֮ǰȷ�ϣ�
 * @param char *name ��ϵ������
 * @param char *address ��ϵaddUSERToGroup�˹�����λסַ
 * @param char *homeaddress ��ϵ�˼�ͥסַ
 * @param char *email �����ʼ���ַ
 * @param char *telphone ��Ҫ�绰
 * @param uint  groupID Ⱥ����
 * @return int  ���ִ��󷵻�0 , �ɹ����� 1
 * @author wx
 *
 */

void menuShowDetailsByDetails(char        *name,
                              char        *address,
                              char        *homeaddress,
                              char        *email,
                              char        *telphone,
                              unsigned int groupID
                             )
{
    char *group = NULL;
    pGroup tmp = NULL;
    if(name        == NULL ||
       address     == NULL ||
       homeaddress == NULL ||
       email       == NULL ||
       telphone    == NULL
       ) //��ָ�����
    {
        puts("����δ֪�������ڷ��ء���");
        Sleep(500);
        return ;
    }
    tmp = getGroup(1,groupID);
    group  = (tmp == NULL) ? "��Ⱥ��" : tmp->name;


    clear();
    puts("\t                                                            ");
    puts("\t                                                            ++++++++ ");
    puts("\t    --------------------------------------------------------++++++++ ");
    puts("\t    -- --                                                   ++++++++ ");
    puts("\t    -- --                 ��ϵ����Ϣ����                    ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
    puts("\t    -- --                                                      --    ");
  printf("\t    -- --    ��    ����%-38s  --    \n"                          ,name);
  printf("\t    -- --    ������λ��%-38s  --    \n"                       ,address);
  printf("\t    -- --    ��ͥסַ��%-38s  --    \n"                   ,homeaddress);
  printf("\t    -- --    ��������: %-38s  --    \n"                         ,email);
  printf("\t    -- ---   ����Ⱥ�飺%-15s                         --    \n"  ,group);
    puts("\t    -- ----- ��ϵ��ʽ��                                        --    ");
  //puts("\t    -- --                                                      --    ");
  printf("\t    -- --              %d. %-15s                      --    \n"       ,1,telphone);
    puts("\t    -- --                                                      --    ");
    puts("\t    -- ---                                          @          --    ");
    puts("\t    -- -----                                     @@@@@@@@      --    ");
    puts("\t    -- ----------------------                     @@@@@@     ----    ");
    puts("\t    -- -------------------------------------     @@@@@@@@  ------    ");
    puts("\t    --------------------------------------------------------------   ");



}

/**
 *  ͨ��unsigned int ������ʾ�û��б�
 *  @param unsigned int ID[] �û�����
 *  @author wx & hafrans
 **/
void menuShowUserList(unsigned int ID[])
{
    pUSER obj  = NULL;
    pGroup grp = NULL;
    char *text = NULL;
    int i   = 0;//ѭ������
    if(ID[0] == 0)
    {
        menuNoResult();
        Sleep(1000);
        return ;
    }
        puts("  +----------------------------------------------------------------------------+");
        puts("  | I D |   ����   |    ��Ҫ��ϵ�绰  |    ������λ              |  ����Ⱥ��   |");
        puts("  +----------------------------------------------------------------------------+");
    for(i = 0;ID[i] != 0;i++)
    {
        obj = getAUSER(1,ID[i]);
        if(obj == NULL)
            continue;
        grp = getGroup(1,obj->groupID);
        if(grp == NULL)
            text = "��Ⱥ��";
        else
            text = grp->name;
      //puts("  | I D |  ����  |  ��Ҫ��ϵ�绰  |    ������λ              |   ����Ⱥ��  |");
      printf("  | %-4u| %-8s | %-16s |  %-22s  |  %-9s  |\n",obj->ID,obj->username,obj->telphones[0],obj->address,text);
        puts("  +----------------------------------------------------------------------------+");
    }


}
/**
 *  ͨ��unsigned int ������ʾȺ���б�
 *  @param unsigned int ID[] Ⱥ��ID����
 *  @author wx & hafrans
 **/
 void menuShowGroupList(unsigned int ID[])
 {
         pGroup tmp = NULL;
         int i   = 0,k=0;//ѭ������
         int count = 0;//����
         if(ID[0] == 0)
         {
             menuNoResult();
             Sleep(1000);
             return ;
         }
        puts("\t  +----------------------------------------+");
        puts("\t  |   I D  |       Ⱥ����     |    ����    |");//8,18,12
        puts("\t  +----------------------------------------+");
        for(i = 0;ID[i] != 0 ;++i)
        {
            tmp = getGroup(1,ID[i]);
            if(tmp == NULL)
                continue;
            for(k = 0;k<128;k++)
            {
                if(tmp->USERID[k]!=0)
                    count++;
            }

      printf("\t  | %-6u | %-16s | %-10d |\n",tmp->ID,tmp->name,count);
      printf("\t  +----------------------------------------+\n");
            count = 0;
        }

 }


 /**
  * ͨ��ID��ʾȺ������
  * @param unsigned int ID Ⱥ��ID
  */
void menuShowGroupByID(unsigned int ID)
{
    C_UINT data = NULL;//����
    int i = 0;
    pGroup grp = getGroup(1,ID);
    unsigned int *tt = NULL;
    if(grp == NULL)
    {
        puts("��ѯ�������Ⱥ�飡");
        return ;
    }


    clear();
    data = containerInitUint();
    for(i = 0;i<128;i++)
    {
        if(grp->USERID[i] != 0 )
        containerPushBackUint(data,grp->USERID[i]);
    }
    tt = containerGetDataUint(data);
    puts("\t                                                            ");
    puts("\t                                                            ++++++++ ");
    puts("\t    --------------------------------------------------------++++++++ ");
    puts("\t    -- --                                                   ++++++++ ");
    puts("\t    -- --                  Ⱥ����Ϣ����                     ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
    puts("\t    -- --                                                      --    ");
  printf("\t    -- --    Ⱥ�����ƣ�%-38s  --    \n"                          ,grp->name);
  printf("\t    -- --    Ⱥ��  ID��%-38u  --    \n"                       ,grp->ID);
    puts("\t    --------------------------------------------------------------   ");
    puts("\t    -- --                    Ⱥ���Ա                          --    ");
    puts("\t    --------------------------------------------------------------   ");
    menuShowUserList(tt);

}

void menuOutputLayout()
{
    puts("\t                                                            ");
    puts("\t                                                            ++++++++ ");
    puts("\t    --------------------------------------------------------++++++++ ");
    puts("\t    -- --                                                   ++++++++ ");
    puts("\t    -- --               ���ݹ�������                        ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
    puts("\t    -- --    1.���ݵ�����CSV                                   --    ");
  printf("\t    -- --    2.���ݵ�����HTML                                  --    \n");
  printf("\t    -- --    3.���ݵ�����TXT                                   --    \n");
    puts("\t    -- --    4.������CSV����                                   --    ");
    puts("\t    -- ---   0.����                                 @          --    ");
    puts("\t    -- -----                                     @@@@@@@@      --    ");
    puts("\t    -- ----------------------                     @@@@@@     ----    ");
    puts("\t    -- -------------------------------------     @@@@@@@@  ------    ");
    puts("\t    --------------------------------------------------------------   ");

}


void menuKeySecret()
{
        puts("\t                                                            ");
    puts("\t                                                            ++++++++ ");
    puts("\t    --------------------------------------------------------++++++++ ");
    puts("\t    -- --                                                   ++++++++ ");
    puts("\t    -- --               �����������                        ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
  printf("\t    -- --    |    ���뱣��״̬��%4s                 |         --    \n",key->status?"��":"��");
    puts("\t    -- --    ----------------------------------------          --    ");
  printf("\t    -- --    1.%-15s                                 --    \n",key->status?"�ر����뱣��":"�������뱣��");
  printf("\t    -- --    2.%-15s                                 --    \n",strcmp(key->key,"")?"�޸�����":"��������");
    puts("\t    -- ---   0.����                                            --    ");
    puts("\t    -- -----                                                   --    ");
    puts("\t    -- ----------------------                                ----    ");
    puts("\t    -- -------------------------------------               ------    ");
    puts("\t    --------------------------------------------------------------   ");

}

void menuErrorKey()
{
             puts("");
             puts("");
             puts("\t    --------------------------------------------------------------   ");
             puts("\t    |             �����ļ����ƻ��������޷�����                   |   ");
             puts("\t    --------------------------------------------------------------   ");
}

void menuLogin(int type)
{
    switch(type)
    {
        case 1:
                puts("\t                                                            ");
                puts("\t                                                            ++++++++ ");
                puts("\t    --------------------------------------------------------++++++++ ");
                puts("\t    -- --                                                   ++++++++ ");
                puts("\t    -- --             ��ӭʹ�ñ�ͨѶ¼ϵͳ                  ++++++++ ");
                puts("\t    -- --    ----------------------------------------          --    ");
                puts("\t    -- --              ���˿��������뱣��                      --    ");
                puts("\t    -- --         ����������ȷ������ſ��Խ���Ŷ               --    ");
                puts("\t    =============================================================  ");
//              printf("\t           ����������:");

    }
}
