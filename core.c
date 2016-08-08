/**
    File: core.c
    Description:��������߼�Դ��
    Updated: Jul 10 2016
    Author : lxj

*/
#include "core.h"

     unsigned int maxRegistedUSERID = 0;   //��ǰ��ע����û����ID NULL == 0
     unsigned int maxRegistedGROUPID= 0;   //��ǰ��ע���Ⱥ�����ID
     pgFile gHEAD = NULL;                  //Ⱥ�������ͷ
     puFile uHEAD = NULL;                  //�û������ͷ
     pKey   key   = NULL;                  //�û���������


void init()
{
    system("mode con cols=85 lines=28");
    loadGROUPField();
    loadUSERField();
    loadKey();
    Sleep(100);
    coreKeyCheck();
    system("color 2f");
    #ifdef DEBUG
        puts("*****IN DEBUG MODE*****");
        system("color f0");
    #endif // DEBUG
    return ;
}
void Exit()
{

    storeGROUPField();
    storeUSERField();
    storeKey();
    menuExit();
    Sleep(1500);
    return ;
}

void coreAddNewContact()
{
    int count = 0;
    char            username[BUFFSIZE];//�û���
    char            address[BUFFSIZE]; //��ַ
    char            homeaddress[BUFFSIZE];//������λסַ
    char            email[BUFFSIZE];   //Ψһ�����ʼ�
    char            telphone[20];  //�绰����
    unsigned int    groupID;           //��������Ⱥ��
    char            buf[BUFFSIZE] = {0};
    puts("\t\t\t�����ϵ��");
segment:
    puts("\t      [����Ļ��Ͷ�δ������봥������]");
    puts("========================================================");
    printf("����������:");
    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
    {
        if(count == 3)
        {
            puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
            Sleep(1500);
            return ;
        }
        printf("û����ȷ���룬����������:");
        count ++;
    }
    strcpy(username,trim(buf));
    count = 0;
    printf("�����빤����λ:");
    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
    {
        if(count == 3)
        {
            puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
            Sleep(1500);
            return ;
        }
        printf("û����ȷ���룬����������:");
        count ++;
    }
    strcpy(address,trim(buf));
    count = 0;

    printf("�������ͥסַ:");
    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
    {
        if(count == 3)
        {
            puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
            Sleep(1500);
            return ;
        }
        printf("û����ȷ���룬����������:");
        count ++;
    }
    strcpy(homeaddress,trim(buf));
    count = 0;
    printf("������E-mail:");
    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
    {
        if(count == 3)
        {
            puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
            Sleep(1500);
            return ;
        }
        printf("û����ȷ���룬����������:");
        count ++;
    }
    strcpy(email,trim(buf));
    count = 0;

    while(1)
    {
        printf("��������Ҫ�绰����[19λ����]:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("û����ȷ���룬:");
                count ++;
            }
            if(!testNumber(trim(buf)))
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("���Ǵ�����Ŷ��");
                count ++;
                continue;
            }
            else if(strlen(trim(buf)) > 19)
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("���ȹ�����");
                count ++;
                continue;
            }else{
                break;
            }
    }
    strcpy(telphone,trim(buf));
    count = 0;
    puts("���������������û���һ��Ⱥ���С�");
    puts("��ͨѶ¼��������Ⱥ�鹩����ѡ");
    menuShowGroupList(getAllGroupID());
    while(1)
    {
        printf("������Ҫ����Ⱥ��ID[��������0]:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("û����ȷ���룬:");
                count ++;
            }
            if(!testNumber(trim(buf)))
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("���Ǵ�����Ŷ��");
                count ++;
                continue;
            }
            else if(strlen(trim(buf)) > 8)
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("���ȹ�����");
                count ++;
                continue;
            }else{
                break;
            }
    }
    groupID = atoi(trim(buf));
    count = 0;

    menuShowDetailsByDetails(username,address,homeaddress,email,telphone,groupID);
     printf("���Ƿ�Ҫ���\"%s\"����û���(y/N):",username);
     while(1)
     {
         while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
         {
            if(count == 3)
            {
                puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                Sleep(1500);
                return ;
            }
                printf("û����ȷ���룬:");
                count ++;
         }
         if(strcmp(trim(buf),"y") == 0 || strcmp(trim(buf),"Y") == 0)
         {
            puts("��ȴ�����");
            BOOLEAN result = addUser(username,address,homeaddress,email,telphone,groupID);
            if(result > 0)
            {
                puts("��ϲ������ӳɹ���");
                printf("���Ƿ�Ҫ������ӣ�(y/N)");
                    gets(buf);
                    if(strcmp(trim(buf),"Y") == 0 ||
                       strcmp(trim(buf),"y") == 0 )
                       {
                           clear();
                           goto segment;
                       }
            }
            else if(result == -1)
                puts("��Ǹ����ϵ���ظ����볢���޸���ϵ�˲�����");
            else
                puts("��Ǹ�����ʧ�ܣ�����ϵ����Ա");
            puts("���ڷ������˵�����");
            Sleep(1500);
            return;
         }else{
                puts("���Ѿ�ȡ��������������ڷ������˵�����");
                Sleep(1500);
                return ;
         }
     }



    //stdinClear();
    //getchar();
}

void coreSearchContact()
{
    int count = 0; //�������
    pUSER *tmp = NULL;
    pUSER user = NULL;//�û�ʵ��
    C_UINT container = NULL;//ID����
    unsigned int *IDs = NULL;//IDʵ������
    int type = 0; //���ҷ�ʽ
    int i = 0;
    char buf[BUFFSIZE] = {0};
    puts("\t\t\t��ѯ��ϵ��");
segment:
    puts("\t      [����Ļ��Ͷ�δ������봥������]");
    puts("========================================================");
    puts("�����ṩ�����²�ѯ��ʽ��");
    puts("========================================================");
    puts("| 1.ID��ȷ���� | 2.����ģ������ |  3.������ģ������    |");
    puts("========================================================");

    while(1){
        printf("������һ�����ҷ�ʽ(1,2,3):");
        while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
         {
            if(count == 3)
            {
                puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                Sleep(1500);
                return ;
            }
         }
         if(strcmp(trim(buf),"1") != 0 &&
            strcmp(trim(buf),"2") != 0 &&
            strcmp(trim(buf),"3") != 0 )
         {
            if(count == 3)
            {
                puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                Sleep(1500);
                return ;
            }
            printf("��ʽ����");
            count ++;
            continue;
         }else{
            break;
         }
    }

    type = atoi(trim(buf));

    switch(type)
    {
        case 1:
    ID_SEGMENT:
            printf("������Ҫ��ѯ���û�ID[ȫ����������0]:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ѯ�����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("û����ȷ���룬:");
                count ++;
            }
            if(strcmp(trim(buf),"0") == 0)
            {
                menuShowUserList(getAllUSERID());
            }else{
                pUSER tmp = getAUSER(1,atoi(trim(buf)));
                if(tmp == NULL)
                {
                    puts("��Ǹ�������ڸ��û���");
                }else{
                    menuShowDetailsBypUSER(tmp);
                    user = tmp;
                }
            }
            break;
        case 2:
            printf("������Ҫ����ģ����ѯ���û���:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ѯ�����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("û����ȷ���룬:");
                count ++;
            }
            tmp = getUSERByUsingUSERName(trim(buf));
            container = containerInitUint();
            for(i = 0;tmp[i]!=NULL;++i)
            {
                containerPushBackUint(container,tmp[i]->ID);
            }
            IDs = containerGetDataUint(container);
            menuShowUserList(IDs);
            if(IDs[0] != 0)
            {
                containerFreeUint(container);
                goto ID_SEGMENT;
            }else{
                containerFreeUint(container);
            }
            break;


        case 3:
             printf("������Ҫ����ģ����ѯ����:");
             while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
               {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ѯ�����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("û����ȷ���룬:");
                count ++;
               }
            tmp = getUSERByUsingAll(trim(buf));
            container = containerInitUint();
            for(i = 0;tmp[i]!=NULL;++i)
            {
                containerPushBackUint(container,tmp[i]->ID);
            }
            IDs = containerGetDataUint(container);
            menuShowUserList(IDs);
            if(IDs[0] != 0)
            {
                containerFreeUint(container);
                goto ID_SEGMENT;
            }else{
                containerFreeUint(container);
            }
            break;
    }

    if(user != NULL)
    {
            puts("\t\t\t   �����ṩ�����²�����ʽ��");
            puts("\t   ========================================================");
            puts("\t   | 1.�޸���ϵ�� | 2.ɾ����ϵ�� |  3.������ѯ | 0.������  |");
            puts("\t   ========================================================");

                while(1){
                    printf("�������㽫Ҫ���еĲ���(0,1,2,3):");
                    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                     {
                        if(count == 3)
                        {
                            puts("����������࣬������ֹ�����ڷ������˵���");
                            Sleep(1500);
                            return ;
                        }
                            printf("û����ȷ���룬:");
                            Sleep(1500);
                            return ;
                    }
                     if(strcmp(trim(buf),"1") != 0 &&
                        strcmp(trim(buf),"2") != 0 &&
                        strcmp(trim(buf),"3") != 0 &&
                        strcmp(trim(buf),"0") != 0 )
                     {
                        if(count == 3)
                        {
                            puts("����������࣬������ֹ�����ڷ������˵���");
                            Sleep(1500);
                            return ;
                        }
                        printf("��ʽ����");
                        count ++;
                        continue;
                     }else{
                        break;
                     }
                }
                type = atoi(trim(buf));
                switch(type)
                {
                    case 1:
                        coreChangeContact(user);
                        goto  end_segment;
                        break;
                    case 2:
                        coreDeleteContact(user);
                        goto  end_segment;
                        break;
                    case 3:
                        clear();
                        goto segment;
                        break;
                    default:
                        puts("���ڷ������˵�����");
                        Sleep(1500);
                        return ;
                        break;
                }


    }
    printf("���Ƿ�Ҫ������ѯ��(y/N)");
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        clear();
        goto segment;
    }
    puts("���ڷ������˵�����");
    Sleep(1500);
end_segment:
      return ;
}
void coreDeleteContact(pUSER obj)
{
    int count = 0; //�������
    pUSER tmp = NULL;
    char buf[BUFFSIZE] = {0};
    if(obj == NULL)
    {
        puts("\t\t\tɾ����ϵ��");
    segment:
        puts("\t      [����Ļ��Ͷ�δ������봥������]");
        puts("========================================================");
        puts("Ϊ�˰�ȫ�ԣ�����ֻ�ṩ��ID����ɾ����");
      printf("������Ҫɾ�����û�ID:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ѯ�����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("û����ȷ���룬:");
                count ++;
            }
        tmp = getAUSER(1,atoi(trim(buf)));
        count = 0;
        if(tmp == NULL)
        {
            puts("��Ǹ�����Ҳ������û�,���ڷ������˵�");
            Sleep(1500);
            return;
        }
    }else{
        tmp = obj;
    }
    if(tmp == NULL)
    {
        puts("λ��ָ����������˳�����");
        exit(255);
        return ;
    }
    printf("���Ƿ�Ҫɾ�� ID: %u ������%s ����û�(y/N)��",tmp->ID,tmp->username);
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        if(removeUser(1,tmp->ID))
        {
            puts("��ϲ����ɾ���ɹ�");
        }else{
            puts("��Ǹ��ɾ��ʧ�ܣ�����ϵ����Ա���");
        }
            if(obj != NULL)
            {
               puts("���ڷ������˵�����");
                Sleep(1500);
                return ;
            }

    }else{
        puts("���Ѿ�ȡ����ɾ��������");
    }
    printf("�Ƿ�Ҫ����ɾ��(y/N)��");
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        tmp = NULL;
        count = 0;
        clear();
        goto segment;
    }
    puts("���ڷ������˵�����");
    Sleep(1500);
    return;


}

void coreChangeContact(pUSER obj)
{
    int count = 0; //�������
    pUSER           tmp = NULL;
    char            username[BUFFSIZE];//�û���
    char            address[BUFFSIZE]; //��ַ
    char            homeaddress[BUFFSIZE];//������λסַ
    char            email[BUFFSIZE];   //Ψһ�����ʼ�
    char            telphone[20];  //�绰����
    unsigned int    groupID;           //��������Ⱥ��
    char            buf[BUFFSIZE] = {0};

    if(obj == NULL)
    {
        puts("\t\t\t�޸���ϵ��");
    segment:
        puts("\t      [����Ļ��Ͷ�δ������봥������]");
        puts("========================================================");
        puts("Ϊ�˰�ȫ�ԣ�����ֻ�ṩ��ID���ң�");
      printf("������Ҫ�޸ĵ��û�ID:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ѯ�����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("û����ȷ���룬:");
                count ++;
            }
        tmp = getAUSER(1,atoi(trim(buf)));
        count = 0;
        if(tmp == NULL)
        {
            puts("��Ǹ�����Ҳ������û�,���ڷ������˵�");
            Sleep(1500);
            return;
        }
    }else{
        tmp = obj;
    }
    if(tmp == NULL)
    {
        puts("λ��ָ����������˳�����");
        exit(255);
        return ;
    }
    printf("���Ƿ�Ҫ�޸� ID: %u ������%s ����û�(y/N)��",tmp->ID,tmp->username);
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
                printf("������������(�س���ʾ������):");
                    if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        strcpy(buf,tmp->username);
                    }
                    strcpy(username,trim(buf));
                    count = 0;
                    printf("�����빤����λ(�س���ʾ������):");
                    if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        strcpy(buf,tmp->address);
                    }
                    strcpy(address,trim(buf));
                    count = 0;

                    printf("�������ͥסַ(�س���ʾ������):");
                    if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        strcpy(buf,tmp->homeaddress);
                    }
                    strcpy(homeaddress,trim(buf));
                    count = 0;
                    printf("������E-mail(�س���ʾ������):");
                    if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        strcpy(buf,tmp->email);
                    }
                    strcpy(email,trim(buf));
                    count = 0;
                    while(1)
                    {
                        printf("��������Ҫ�绰����[19λ����](�س���ʾ������):");
                            if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                            {
                                 strcpy(buf,tmp->telphones[0]);
                                 goto telfinish;
                            }
                            if(!testNumber(trim(buf)))
                            {
                                if(count == 3)
                                {
                                    puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                                    Sleep(1500);
                                    return ;
                                }
                                printf("���Ǵ�����Ŷ��");
                                count ++;
                                continue;
                            }
                            else if(strlen(trim(buf)) > 19)
                            {
                                if(count == 3)
                                {
                                    puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                                    Sleep(1500);
                                    return ;
                                }
                                printf("���ȹ�����");
                                count ++;
                                continue;
                            }else{
                                break;
                            }
                    }
          telfinish:strcpy(telphone,trim(buf));
                    count = 0;
                    puts("���������������û���һ��Ⱥ���С�");
                    puts("��ͨѶ¼��������Ⱥ�鹩����ѡ");
                    menuShowGroupList(getAllGroupID());
                    while(1)
                    {
                        printf("������Ҫ����Ⱥ��ID[��������0](������ֱ�ӻس�):");
                            if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                            {
                                groupID = tmp->groupID;
                                goto grpfinish;
                            }
                            if(!testNumber(trim(buf)))
                            {
                                if(count == 3)
                                {
                                    puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                                    Sleep(1500);
                                    return ;
                                }
                                printf("���Ǵ�����Ŷ��");
                                count ++;
                                continue;
                            }
                            else if(strlen(trim(buf)) > 8)
                            {
                                if(count == 3)
                                {
                                    puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                                    Sleep(1500);
                                    return ;
                                }
                                printf("���ȹ�����");
                                count ++;
                                continue;
                            }else{
                                break;
                            }
                    }
                    groupID = atoi(trim(buf));
           grpfinish:count = 0;
                    menuShowDetailsByDetails(username,address,homeaddress,email,telphone,groupID);
                printf("��ȷ��(y/N)��");
                gets(buf);
            if(strcmp(trim(buf),"Y") == 0 ||
               strcmp(trim(buf),"y") == 0  )
            {
                if(modifyUser(tmp,username,address,homeaddress,email,telphone,groupID) == True)
                {
                    puts("�޸ĳɹ���");
                }else{
                    puts("�޸�ʧ�ܣ�");
                }
            }else
            {
                puts("���Ѿ�ȡ�����޸�");
            }
            if(obj != NULL)
            {
                puts("���ڷ������˵�����");
                Sleep(1500);
                return ;
            }

    }else{
        puts("���Ѿ�ȡ�����޸Ĳ�����");
        puts("���ڷ������˵�����");
        Sleep(1500);
    return;
    }
    printf("�Ƿ�Ҫ�����޸�(y/N)��");
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        tmp = NULL;
        count = 0;
        clear();
        goto segment;
    }
    puts("���ڷ������˵�����");
    Sleep(1500);
    return;
}
//////////////////////////////////////
void coreAddNewGroup()
{
    int count = 0;
    char buf[BUFFSIZE] = {0};
    char name[BUFFSIZE];
    char *color = "3c";//�ݲ���ӱ�����
    puts("\t\t\t�����ϵ��Ⱥ��");
segment:
    puts("\t      [����Ļ��Ͷ�δ������봥������]");
    puts("========================================================");
    printf("������Ⱥ����:");
    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
    {
        if(count == 3)
        {
            puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
            Sleep(1500);
            return ;
        }
        printf("û����ȷ���룬����������:");
        count ++;
    }
    strcpy(name,trim(buf));
    count = 0;
    puts("\t    --------------------------------------------------------++++++++ ");
    puts("\t    -- --                                                   ++++++++ ");
    puts("\t    -- --                  Ⱥ����Ϣ����                     ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
    puts("\t    -- --                                                      --    ");
  printf("\t    -- --    Ⱥ�����ƣ�%-38s  --    \n"                          ,name);
  printf("\t    -- --    Ⱥ��  ID��%-38s  --    \n"                       ,"��Ӻ��ƶ�");
    puts("\t    --------------------------------------------------------------   ");
     printf("���Ƿ�Ҫ���\"%s\"���Ⱥ�飿(y/N):",name);
     while(1)
     {
         while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
         {
            if(count == 3)
            {
                puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                Sleep(1500);
                return ;
            }
                printf("û����ȷ���룬:");
                count ++;
         }
         if(strcmp(trim(buf),"y") == 0 || strcmp(trim(buf),"Y") == 0)
         {
            puts("��ȴ�����");
            BOOLEAN result = addGroup(name,color);
            if(result > 0)
            {
                puts("��ϲ������ӳɹ���");
                printf("���Ƿ�Ҫ������ӣ�(y/N)");
                    gets(buf);
                    if(strcmp(trim(buf),"Y") == 0 ||
                       strcmp(trim(buf),"y") == 0 )
                       {
                           clear();
                           goto segment;
                       }
            }
            else if(result == -1)
                puts("��Ǹ��Ⱥ���ظ����볢���޸���ϵ�˲�����");
            else
                puts("��Ǹ�����ʧ�ܣ�����ϵ����Ա");
            puts("���ڷ������˵�����");
            Sleep(1500);
            return;
         }else{
                puts("���Ѿ�ȡ��������������ڷ������˵�����");
                Sleep(1500);
                return ;
         }
     }
}

void coreSearchGroup()
{
    int count = 0; //�������
    pGroup tmp = NULL;
    pGroup user = NULL;//�û�ʵ��
    //C_UINT container = NULL;//ID����
    //unsigned int *IDs = NULL;//IDʵ������
    int type = 0; //���ҷ�ʽ
    char buf[BUFFSIZE] = {0};
    puts("\t\t\t��ѯȺ��");
segment:
    puts("\t      [����Ļ��Ͷ�δ������봥������]");
    puts("========================================================");
    puts("�����ṩ�����²�ѯ��ʽ��");
    puts("========================================================");
    puts("| 1.ID��ȷ���� | 2.Ⱥ�����ƾ�ȷ���� |                  |");
    puts("========================================================");

    while(1){
        printf("������һ�����ҷ�ʽ(1,2):");
        while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
         {
            if(count == 3)
            {
                puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                Sleep(1500);
                return ;
            }
         }
         if(strcmp(trim(buf),"1") != 0 &&
            strcmp(trim(buf),"2") != 0  )
         {
            if(count == 3)
            {
                puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                Sleep(1500);
                return ;
            }
            printf("��ʽ����");
            count ++;
            continue;
         }else{
            break;
         }
    }

    type = atoi(trim(buf));

    switch(type)
    {
        case 1:
    ID_SEGMENT:
            printf("������Ҫ��ѯ��Ⱥ��ID[ȫ����������0]:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ѯ�����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("û����ȷ���룬:");
                count ++;
            }
            if(strcmp(trim(buf),"0") == 0)
            {
                clear();
                menuShowGroupList(getAllGroupID());
            }else{
                tmp = getGroup(1,atoi(trim(buf)));
                if(tmp == NULL)
                {
                    puts("��Ǹ�������ڸ�Ⱥ�飡");
                }else{
                    menuShowGroupByID(tmp->ID);
                    user = tmp;
                }
            }
            break;
        case 2:
            printf("������Ҫ��ѯ��Ⱥ����:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ѯ�����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("û����ȷ���룬:");
                count ++;
            }
            tmp = getGroup(2,trim(buf));
            if(tmp == NULL)
            {
                puts("��Ǹ�������ڸ�Ⱥ�飡");
            }else{
                clear();
                menuShowGroupByID(tmp->ID);
                user = tmp;
            }
            break;
    }

    if(user != NULL)
    {
            puts("\t\t\t      �����ṩ�����²�����ʽ��");
            puts("\t    ==============================================================");
            puts("\t    |  1.�޸�Ⱥ��  |  2.ɾ��Ⱥ��  |  3.������ѯ   |   0.������   |");
            puts("\t    ==============================================================");

                while(1){
                    printf("�������㽫Ҫ���еĲ���(0,1,2,3):");
                    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                     {
                        if(count == 3)
                        {
                            puts("����������࣬������ֹ�����ڷ������˵���");
                            Sleep(1500);
                            return ;
                        }
                            printf("û����ȷ���룬:");
                            Sleep(1500);
                            return ;
                    }
                     if(strcmp(trim(buf),"1") != 0 &&
                        strcmp(trim(buf),"2") != 0 &&
                        strcmp(trim(buf),"3") != 0 &&
                        strcmp(trim(buf),"0") != 0 )
                     {
                        if(count == 3)
                        {
                            puts("����������࣬������ֹ�����ڷ������˵���");
                            Sleep(1500);
                            return ;
                        }
                        printf("��ʽ����");
                        count ++;
                        continue;
                     }else{
                        break;
                     }
                }
                type = atoi(trim(buf));
                switch(type)
                {
                    case 1:
                        coreChangeGroup(user);
                        goto  end_segment;
                        break;
                    case 2:
                        coreDeleteGroup(user);
                        goto  end_segment;
                        break;
                    case 3:
                        clear();
                        goto segment;
                        break;
                    default:
                        puts("���ڷ������˵�����");
                        Sleep(1500);
                        return ;
                        break;
                }


    }
    printf("���Ƿ�Ҫ������ѯ��(y/N)");
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        clear();
        goto ID_SEGMENT;
    }
    puts("���ڷ������˵�����");
    Sleep(1500);
end_segment:
      return ;
}

/**
 * �޸�Ⱥ��
 */
void coreChangeGroup(pGroup obj){
    int count = 0; //�������
    pGroup          tmp = NULL;
    char            name[BUFFSIZE];//Ⱥ����
    char            buf[BUFFSIZE];
    if(obj == NULL)
    {
        puts("\t\t\t�޸�Ⱥ��");
    segment:
        puts("\t      [����Ļ��Ͷ�δ������봥������]");
        puts("========================================================");
        puts("Ϊ�˰�ȫ�ԣ�����ֻ�ṩ��ID���ң�");
      printf("������Ҫ�޸ĵ�Ⱥ��ID:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ѯ�����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("û����ȷ���룬:");
                count ++;
            }
        tmp = getGroup(1,atoi(trim(buf)));
        count = 0;
        if(tmp == NULL)
        {
            puts("��Ǹ�����Ҳ�����Ⱥ��,���ڷ������˵�");
            Sleep(1500);
            return;
        }
    }else{
        tmp = obj;
    }
    if(tmp == NULL)
    {
        puts("λ��ָ����������˳�����");
        exit(255);
        return ;
    }
    printf("���Ƿ�Ҫ�޸� %s ���Ⱥ��(y/N)��",tmp->name);
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
       {
                printf("������Ⱥ����:");
                while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                {
                    if(count == 3)
                    {
                        puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                        Sleep(1500);
                        return ;
                    }
                    printf("û����ȷ���룬����������:");
                    count ++;
                }
                strcpy(name,trim(buf));
                count = 0;

                puts("\t    --------------------------------------------------------++++++++ ");
                puts("\t    -- --                                                   ++++++++ ");
                puts("\t    -- --                ��Ⱥ����Ϣ����                     ++++++++ ");
                puts("\t    -- --    ----------------------------------------          --    ");
                puts("\t    -- --                                                      --    ");
              printf("\t    -- --    Ⱥ�����ƣ�%-38s  --    \n"                          ,name);
              printf("\t    -- --    Ⱥ��  ID��%-38u  --    \n"                       ,tmp->ID);
                puts("\t    --------------------------------------------------------------   ");
                 printf("���Ƿ�Ҫ�޸�ԭ����Ϊ\"%s\"��������Ϊ\"%s\"���Ⱥ�飿(y/N):",tmp->name,name);
                     while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                     {
                        if(count == 3)
                        {
                            puts("����������ֹ࣬ͣ��ӣ����ڷ������˵���");
                            Sleep(1500);
                            return ;
                        }
                            printf("û����ȷ���룬:");
                            count ++;
                     }
                     count = 0;
                     if(strcmp(trim(buf),"Y") == 0 ||
                        strcmp(trim(buf),"y") == 0  )
                     {
                        if(modifyGroup(tmp,name,tmp->Color))
                        {
                            puts("�޸ĳɹ���");
                        }else{
                            puts("�޸�ʧ�ܣ�");
                        }
                        if(obj != NULL)
                        {
                            Sleep(1500);
                            return;
                        }
                     }else{
                        puts("��ȡ���˸ò��������ڷ������˵�����");
                        Sleep(1500);
                        return ;
                     }

       }else{
               puts("��ȡ���˸ò��������ڷ������˵�����");
               Sleep(1500);
               return ;
    }
    printf("�Ƿ�Ҫ�����޸�(y/N)��");
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        tmp = NULL;
        count = 0;
        clear();
        goto segment;
    }
    puts("���ڷ������˵�����");
    Sleep(1500);
    return;

}
/**
 * Ⱥ��ɾ��
 */
 void coreDeleteGroup(pGroup obj)
 {
    int count = 0; //�������
    pGroup tmp = NULL;
    char buf[BUFFSIZE] = {0};
    if(obj == NULL)
    {
        puts("\t\t\tɾ��Ⱥ��");
    segment:
        puts("\t      [����Ļ��Ͷ�δ������봥������]");
        puts("========================================================");
        puts("Ϊ�˰�ȫ�ԣ�����ֻ�ṩ��ID����ɾ����");
      printf("������Ҫɾ����Ⱥ��ID:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("����������ֹ࣬ͣ��ѯ�����ڷ������˵���");
                    Sleep(1500);
                    return ;
                }
                printf("û����ȷ���룬:");
                count ++;
            }
        tmp = getGroup(1,atoi(trim(buf)));
        count = 0;
        if(tmp == NULL)
        {
            puts("��Ǹ�����Ҳ�����Ⱥ��,���ڷ������˵�");
            Sleep(1500);
            return;
        }
    }else{
        tmp = obj;
    }
    if(tmp == NULL)
    {
        puts("λ��ָ����������˳�����");
        exit(255);
        return ;
    }
    puts("=================================================");
    puts("|                  **ע������**                 |");
    puts("|   �����ɾ���˸�Ⱥ��󣬸�Ⱥ���ڳ�Ա�Զ���ɢ��|");
    puts("|ֱ�������¶���������顣                       |");
    puts("=================================================");
    printf("���Ƿ�Ҫɾ�� ID: %u ���ƣ�%s ���Ⱥ��(y/N)��",tmp->ID,tmp->name);
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        if(removeGroup(1,tmp->ID))
        {
            puts("��ϲ����ɾ���ɹ�");
        }else{
            puts("��Ǹ��ɾ��ʧ�ܣ�����ϵ����Ա���");
        }
            if(obj != NULL)
            {
               puts("���ڷ������˵�����");
                Sleep(1500);
                return ;
            }

    }else{
        puts("���Ѿ�ȡ����ɾ��������");
    }
    printf("�Ƿ�Ҫ����ɾ��(y/N)��");
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        tmp = NULL;
        count = 0;
        clear();
        goto segment;
    }
    puts("���ڷ������˵�����");
    Sleep(1500);
    return;
}

/**
 * ����
 */
void coreOutputManager()
{
     int cmd = 0;
     char buf[BUFFSIZE] = {0};
    menu:
        clear();
        menuOutputLayout();
          while(True)
         {
            printf("[user@Contact]#");
            if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                continue;
            }
            if(strcmp("clear",buf) == 0 || strcmp("help",buf) == 0 || strcmp("?",buf) == 0)
            {
                goto menu;
            }
            if(!testNumber(trim(buf)))
            {
                printf("-daras: %s: δ�ҵ�����\n",buf);
                continue;
            }
            cmd = atoi(trim(buf));
            switch(cmd)
            {
                case 0:
                    return ;
                case 1:
                case 2:
                case 3:
                    clear();
                    coreStoreToFile(cmd);
                    goto menu;
                    break;
                case 4:
                    puts("-plop: 4: �ù�����δʵ��");
                    break;
                default:
                    printf("-plop: %s: δ�ҵ�����\n",buf);
                    break;
            }
         }

}
void keyManager()
{

}
void coreMenuInit()
{
    int cmd = 0;
    char buf[BUFFSIZE] = {0};
    menu:
     clear();

     menuMain();
     while(True)
     {
        printf("[user@Contact]#");
        if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
        {
            continue;
        }
        if(strcmp("clear",buf) == 0 || strcmp("help",buf) == 0 || strcmp("?",buf) == 0)
        {
            goto menu;
        }
        if(!testNumber(trim(buf)))
        {
            printf("-daras: %s: δ�ҵ�����\n",buf);
            continue;
        }
        cmd = atoi(trim(buf));
        switch(cmd)
        {
            case 0:
                return ;
            case 1:
                clear();
                coreAddNewContact();
                storeUSERField();
                goto menu;
                break;
            case 2:
                clear();
                coreSearchContact();
                storeUSERField();
                goto menu;
                break;
            case 3:
                clear();
                coreDeleteContact(NULL);
                storeUSERField();
                goto menu;
                break;
            case 4:
                clear();
                coreChangeContact(NULL);
                storeUSERField();
                goto menu;
                break;
            case 5:
                clear();
                coreAddNewGroup();
                storeGROUPField();
                goto menu;
            case 6:
                clear();
                coreSearchGroup();
                storeGROUPField();
                goto menu;
            case 7:
                clear();
                coreDeleteGroup(NULL);
                storeGROUPField();
                goto menu;
            case 8:
                clear();
                coreChangeGroup(NULL);
                storeGROUPField();
                goto menu;
            case 9:
                clear();
                coreOutputManager();
                goto menu;
            case 10:
                clear();
                coreKeySecret();
                storeKey();
            case 11:
                goto menu;
                break;
            default:
                printf("-plop: %s: δ�ҵ�����\n",buf);
                break;
        }
     }
}

/**
 * ���������ļ�
 * @param int type
 *            type = 1 csv  ����
 *            type = 2 html ����
 *            type = 3 text ����
 */
void coreStoreToFile(int type)
{
    int result = 0;
    char myDir[BUFFSIZE];
    char buf[BUFFSIZE] = {0};
    strcpy(myDir,"explorer.exe ");
    char *cmd = NULL;
    puts(buf);
    dump(type);
     switch(type)
     {
        case 1:
            puts("�ļ��������������ļ�ͬ��Ŀ¼������Ϊoutput.csv");
            break;
        case 2:
            puts("�ļ��������������ļ�ͬ��Ŀ¼������Ϊoutput.html");
            break;
        case 3:
            puts("�ļ��������������ļ�ͬ��Ŀ¼������Ϊoutput.txt");
            break;
     }
     puts("ע�⣬�ļ���ԭ�ȴ��ڵĻ��ͻᱻ���ǣ���ע�����ݰ�ȫ������");
     printf("���������е�������,��ȷ��(y/N)��");
     gets(buf);
     if(strcmp(trim(buf),"Y") == 0 ||
        strcmp(trim(buf),"y") == 0  )
     {
         switch(type)
         {
            case 1:
                result = outputCSV();
                break;
            case 2:
                result = outputHTML();
                break;
            case 3:
                result = outputTXT();
                break;
         }
         if(result == True)
         {
             puts("�����ɹ���,���ڵ�������");
             _getcwd(buf,BUFFSIZE);
             cmd = strcat(myDir,buf);
             system(cmd);

         }else{
            puts("����ʧ�ܣ�������Ȩ�޻���Ŀ���ļ��Ƿ�ռ�ã�");
         }
            Sleep(1500);
            return ;
     }else{
        puts("��ȡ���˱��β�����");
        Sleep(1500);
        return ;
     }



}


void coreKeySecret()
{
    int cmd = 0;
    int count = 0;
    char buf[BUFFSIZE] = {0};
    char newPassword[BUFFSIZE] = {0};
    menu:
        clear();
        menuKeySecret();
          while(True)
         {
            printf("[user@Contact]#");
            if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                continue;
            }
            if(strcmp("clear",buf) == 0 || strcmp("help",buf) == 0 || strcmp("?",buf) == 0)
            {
                goto menu;
            }
            if(!testNumber(trim(buf)))
            {
                printf("-daras: %s: δ�ҵ�����\n",buf);
                continue;
            }
            cmd = atoi(trim(buf));
            switch(cmd)
            {
                case 0:
                    return ;
                case 1:
                    if(strcmp("",key->key) == 0  ||
                       key->key[0] == 0          )
                       {
                           puts("δ�������룬��������������ԣ�");
                           Sleep(1500);
                           goto menu;
                       }else{
                                if(key->status == 0)
                                {
                                    key->status = 1;
                                    puts("��������뱣����");
                                }else{
                                    key->status = 0;
                                    puts("��ȡ�����뱣����");
                                }

                                    Sleep(1000);
                                    clear();
                                    goto menu;

                       }
                       break;
                case 2:
                    if(strcmp(key->key,"") == 0)
                    {
                        goto input_pwd;
                    }
                    count = 0;
                    printf("����������룺");
                    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        if(count == 3)
                        {
                            puts("����������ֹ࣬ͣ��ѯ�����ڷ������˵���");
                            Sleep(1500);
                            goto menu;
                        }
                        printf("û����ȷ���룬:");
                        count ++;
                    }
                    if(strcmp(trim(buf),key->key) != 0)
                    {
                        puts("������Ч��");
                        Sleep(1500);
                        goto menu;
                    }
                    input_pwd:
                    count = 0;
                    printf("�����������룺");
                    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        if(count == 3)
                        {
                            puts("����������ֹ࣬ͣ��ѯ�����ڷ������˵���");
                            Sleep(1500);
                            goto menu;
                        }
                        printf("û����ȷ���룬");
                        count ++;
                    }
                    strcpy(newPassword,trim(buf));
                    count = 0;
                    printf("���������������룺");
                    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        if(count == 3)
                        {
                            puts("����������ֹ࣬ͣ��ѯ�����ڷ������˵���");
                            Sleep(1500);
                            goto menu;
                        }
                        printf("û����ȷ���룬");
                        count ++;
                    }
                    if(strcmp(newPassword,trim(buf)) == 0 )
                    {
                        strcpy(key->key,newPassword);
                        puts("�޸ĳɹ�");
                        Sleep(1500);
                        goto menu;
                    }else{
                        puts("�����������벻ͬ��");
                        Sleep(500);
                        goto input_pwd;
                    }
                    break;
                default:
                    printf("-plop: %s: δ�ҵ�����\n",buf);
                    break;
            }
         }

}

void coreKeyCheck()
{
    char buf[BUFFSIZE] = {0};
    int offset = 0;
    char ch = 0;
    int count = 0;
    #ifdef DEBUG
    if(key == NULL)
    {
        puts("���ڳ�ʼ�����ܹ��ܡ���");
        key  =  (pKey) calloc(1,sizeof(Key));
        Sleep(1500);
        clear();
    }
    #endif // DEBUG
    if(key == NULL)
    {
        menuErrorKey();
        Sleep(5000);
        exit(-1);
    }
    if(key->status)
    {

        menuLogin(1);
        input_pwd:
        if(count >= 3)
        {
             printf("\t       �������������࣬ϵͳ�ܾ����ٴ����룡\n");
             Sleep(3000);
             exit(-2);
        }
        if(count)
        {
             printf("\t       ���ٴ���������:");
        }else{
             printf("\t           ����������:");
        }
        offset = 0;
            while((ch =_getch())!=-1 && ch != 13)
            {
                buf[offset++] = ch;
                printf("*");
            }
            buf[offset] = '\0';
            puts("");
        if(strcmp(trim(buf),key->key)!=0)
        {
            printf("\t           ���벻��ȷ,������\n");
            Sleep(1000);
            count ++;
            goto input_pwd;
        }


    }
}








