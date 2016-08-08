/**
    File: core.c
    Description:程序核心逻辑源码
    Updated: Jul 10 2016
    Author : lxj

*/
#include "core.h"

     unsigned int maxRegistedUSERID = 0;   //当前已注册的用户最大ID NULL == 0
     unsigned int maxRegistedGROUPID= 0;   //当前已注册的群组最大ID
     pgFile gHEAD = NULL;                  //群组链表表头
     puFile uHEAD = NULL;                  //用户链表表头
     pKey   key   = NULL;                  //用户加密数据


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
    char            username[BUFFSIZE];//用户名
    char            address[BUFFSIZE]; //地址
    char            homeaddress[BUFFSIZE];//工作单位住址
    char            email[BUFFSIZE];   //唯一电子邮件
    char            telphone[20];  //电话号码
    unsigned int    groupID;           //所归属的群组
    char            buf[BUFFSIZE] = {0};
    puts("\t\t\t添加联系人");
segment:
    puts("\t      [误入的话就多次错误输入触发返回]");
    puts("========================================================");
    printf("请输入姓名:");
    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
    {
        if(count == 3)
        {
            puts("错误次数过多，停止添加！正在返回主菜单！");
            Sleep(1500);
            return ;
        }
        printf("没有正确输入，请重新输入:");
        count ++;
    }
    strcpy(username,trim(buf));
    count = 0;
    printf("请输入工作单位:");
    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
    {
        if(count == 3)
        {
            puts("错误次数过多，停止添加！正在返回主菜单！");
            Sleep(1500);
            return ;
        }
        printf("没有正确输入，请重新输入:");
        count ++;
    }
    strcpy(address,trim(buf));
    count = 0;

    printf("请输入家庭住址:");
    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
    {
        if(count == 3)
        {
            puts("错误次数过多，停止添加！正在返回主菜单！");
            Sleep(1500);
            return ;
        }
        printf("没有正确输入，请重新输入:");
        count ++;
    }
    strcpy(homeaddress,trim(buf));
    count = 0;
    printf("请输入E-mail:");
    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
    {
        if(count == 3)
        {
            puts("错误次数过多，停止添加！正在返回主菜单！");
            Sleep(1500);
            return ;
        }
        printf("没有正确输入，请重新输入:");
        count ++;
    }
    strcpy(email,trim(buf));
    count = 0;

    while(1)
    {
        printf("请输入主要电话号码[19位以内]:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止添加！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("没有正确输入，:");
                count ++;
            }
            if(!testNumber(trim(buf)))
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止添加！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("不是纯数字哦，");
                count ++;
                continue;
            }
            else if(strlen(trim(buf)) > 19)
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止添加！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("长度过长，");
                count ++;
                continue;
            }else{
                break;
            }
    }
    strcpy(telphone,trim(buf));
    count = 0;
    puts("最后，你可以添加这个用户到一个群组中。");
    puts("本通讯录中有以下群组供您挑选");
    menuShowGroupList(getAllGroupID());
    while(1)
    {
        printf("请输入要加入群组ID[不加入填0]:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止添加！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("没有正确输入，:");
                count ++;
            }
            if(!testNumber(trim(buf)))
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止添加！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("不是纯数字哦，");
                count ++;
                continue;
            }
            else if(strlen(trim(buf)) > 8)
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止添加！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("长度过长，");
                count ++;
                continue;
            }else{
                break;
            }
    }
    groupID = atoi(trim(buf));
    count = 0;

    menuShowDetailsByDetails(username,address,homeaddress,email,telphone,groupID);
     printf("您是否要添加\"%s\"这个用户？(y/N):",username);
     while(1)
     {
         while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
         {
            if(count == 3)
            {
                puts("错误次数过多，停止添加！正在返回主菜单！");
                Sleep(1500);
                return ;
            }
                printf("没有正确输入，:");
                count ++;
         }
         if(strcmp(trim(buf),"y") == 0 || strcmp(trim(buf),"Y") == 0)
         {
            puts("请等待……");
            BOOLEAN result = addUser(username,address,homeaddress,email,telphone,groupID);
            if(result > 0)
            {
                puts("恭喜您，添加成功！");
                printf("您是否要继续添加？(y/N)");
                    gets(buf);
                    if(strcmp(trim(buf),"Y") == 0 ||
                       strcmp(trim(buf),"y") == 0 )
                       {
                           clear();
                           goto segment;
                       }
            }
            else if(result == -1)
                puts("抱歉，联系人重复，请尝试修改联系人操作！");
            else
                puts("抱歉，添加失败！请联系管理员");
            puts("正在返回主菜单……");
            Sleep(1500);
            return;
         }else{
                puts("您已经取消插入操作，正在返回主菜单……");
                Sleep(1500);
                return ;
         }
     }



    //stdinClear();
    //getchar();
}

void coreSearchContact()
{
    int count = 0; //错误次数
    pUSER *tmp = NULL;
    pUSER user = NULL;//用户实体
    C_UINT container = NULL;//ID容器
    unsigned int *IDs = NULL;//ID实质容器
    int type = 0; //查找方式
    int i = 0;
    char buf[BUFFSIZE] = {0};
    puts("\t\t\t查询联系人");
segment:
    puts("\t      [误入的话就多次错误输入触发返回]");
    puts("========================================================");
    puts("我们提供了以下查询方式：");
    puts("========================================================");
    puts("| 1.ID精确查找 | 2.姓名模糊查找 |  3.所有项模糊查找    |");
    puts("========================================================");

    while(1){
        printf("请输入一个查找方式(1,2,3):");
        while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
         {
            if(count == 3)
            {
                puts("错误次数过多，停止添加！正在返回主菜单！");
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
                puts("错误次数过多，停止添加！正在返回主菜单！");
                Sleep(1500);
                return ;
            }
            printf("格式有误，");
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
            printf("请输入要查询的用户ID[全部查找输入0]:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止查询！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("没有正确输入，:");
                count ++;
            }
            if(strcmp(trim(buf),"0") == 0)
            {
                menuShowUserList(getAllUSERID());
            }else{
                pUSER tmp = getAUSER(1,atoi(trim(buf)));
                if(tmp == NULL)
                {
                    puts("抱歉，不存在该用户！");
                }else{
                    menuShowDetailsBypUSER(tmp);
                    user = tmp;
                }
            }
            break;
        case 2:
            printf("请输入要进行模糊查询的用户名:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止查询！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("没有正确输入，:");
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
             printf("请输入要进行模糊查询条件:");
             while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
               {
                if(count == 3)
                {
                    puts("错误次数过多，停止查询！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("没有正确输入，:");
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
            puts("\t\t\t   我们提供了以下操作方式：");
            puts("\t   ========================================================");
            puts("\t   | 1.修改联系人 | 2.删除联系人 |  3.继续查询 | 0.不操作  |");
            puts("\t   ========================================================");

                while(1){
                    printf("请输入你将要进行的操作(0,1,2,3):");
                    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                     {
                        if(count == 3)
                        {
                            puts("错误次数过多，程序终止！正在返回主菜单！");
                            Sleep(1500);
                            return ;
                        }
                            printf("没有正确输入，:");
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
                            puts("错误次数过多，程序终止！正在返回主菜单！");
                            Sleep(1500);
                            return ;
                        }
                        printf("格式有误，");
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
                        puts("正在返回主菜单……");
                        Sleep(1500);
                        return ;
                        break;
                }


    }
    printf("您是否要继续查询？(y/N)");
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        clear();
        goto segment;
    }
    puts("正在返回主菜单……");
    Sleep(1500);
end_segment:
      return ;
}
void coreDeleteContact(pUSER obj)
{
    int count = 0; //错误次数
    pUSER tmp = NULL;
    char buf[BUFFSIZE] = {0};
    if(obj == NULL)
    {
        puts("\t\t\t删除联系人");
    segment:
        puts("\t      [误入的话就多次错误输入触发返回]");
        puts("========================================================");
        puts("为了安全性，我们只提供了ID查找删除：");
      printf("请输入要删除的用户ID:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止查询！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("没有正确输入，:");
                count ++;
            }
        tmp = getAUSER(1,atoi(trim(buf)));
        count = 0;
        if(tmp == NULL)
        {
            puts("抱歉，查找不到此用户,正在返回主菜单");
            Sleep(1500);
            return;
        }
    }else{
        tmp = obj;
    }
    if(tmp == NULL)
    {
        puts("位置指针错误！正在退出程序！");
        exit(255);
        return ;
    }
    printf("您是否要删除 ID: %u 姓名：%s 这个用户(y/N)？",tmp->ID,tmp->username);
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        if(removeUser(1,tmp->ID))
        {
            puts("恭喜您，删除成功");
        }else{
            puts("抱歉，删除失败！请联系管理员解决");
        }
            if(obj != NULL)
            {
               puts("正在返回主菜单……");
                Sleep(1500);
                return ;
            }

    }else{
        puts("您已经取消了删除操作！");
    }
    printf("是否要继续删除(y/N)？");
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        tmp = NULL;
        count = 0;
        clear();
        goto segment;
    }
    puts("正在返回主菜单……");
    Sleep(1500);
    return;


}

void coreChangeContact(pUSER obj)
{
    int count = 0; //错误次数
    pUSER           tmp = NULL;
    char            username[BUFFSIZE];//用户名
    char            address[BUFFSIZE]; //地址
    char            homeaddress[BUFFSIZE];//工作单位住址
    char            email[BUFFSIZE];   //唯一电子邮件
    char            telphone[20];  //电话号码
    unsigned int    groupID;           //所归属的群组
    char            buf[BUFFSIZE] = {0};

    if(obj == NULL)
    {
        puts("\t\t\t修改联系人");
    segment:
        puts("\t      [误入的话就多次错误输入触发返回]");
        puts("========================================================");
        puts("为了安全性，我们只提供了ID查找：");
      printf("请输入要修改的用户ID:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止查询！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("没有正确输入，:");
                count ++;
            }
        tmp = getAUSER(1,atoi(trim(buf)));
        count = 0;
        if(tmp == NULL)
        {
            puts("抱歉，查找不到此用户,正在返回主菜单");
            Sleep(1500);
            return;
        }
    }else{
        tmp = obj;
    }
    if(tmp == NULL)
    {
        puts("位置指针错误！正在退出程序！");
        exit(255);
        return ;
    }
    printf("您是否要修改 ID: %u 姓名：%s 这个用户(y/N)？",tmp->ID,tmp->username);
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
                printf("请输入新姓名(回车表示不更改):");
                    if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        strcpy(buf,tmp->username);
                    }
                    strcpy(username,trim(buf));
                    count = 0;
                    printf("请输入工作单位(回车表示不更改):");
                    if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        strcpy(buf,tmp->address);
                    }
                    strcpy(address,trim(buf));
                    count = 0;

                    printf("请输入家庭住址(回车表示不更改):");
                    if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        strcpy(buf,tmp->homeaddress);
                    }
                    strcpy(homeaddress,trim(buf));
                    count = 0;
                    printf("请输入E-mail(回车表示不更改):");
                    if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        strcpy(buf,tmp->email);
                    }
                    strcpy(email,trim(buf));
                    count = 0;
                    while(1)
                    {
                        printf("请输入主要电话号码[19位以内](回车表示不更改):");
                            if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                            {
                                 strcpy(buf,tmp->telphones[0]);
                                 goto telfinish;
                            }
                            if(!testNumber(trim(buf)))
                            {
                                if(count == 3)
                                {
                                    puts("错误次数过多，停止添加！正在返回主菜单！");
                                    Sleep(1500);
                                    return ;
                                }
                                printf("不是纯数字哦，");
                                count ++;
                                continue;
                            }
                            else if(strlen(trim(buf)) > 19)
                            {
                                if(count == 3)
                                {
                                    puts("错误次数过多，停止添加！正在返回主菜单！");
                                    Sleep(1500);
                                    return ;
                                }
                                printf("长度过长，");
                                count ++;
                                continue;
                            }else{
                                break;
                            }
                    }
          telfinish:strcpy(telphone,trim(buf));
                    count = 0;
                    puts("最后，你可以添加这个用户到一个群组中。");
                    puts("本通讯录中有以下群组供您挑选");
                    menuShowGroupList(getAllGroupID());
                    while(1)
                    {
                        printf("请输入要加入群组ID[不加入填0](不更改直接回车):");
                            if(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                            {
                                groupID = tmp->groupID;
                                goto grpfinish;
                            }
                            if(!testNumber(trim(buf)))
                            {
                                if(count == 3)
                                {
                                    puts("错误次数过多，停止添加！正在返回主菜单！");
                                    Sleep(1500);
                                    return ;
                                }
                                printf("不是纯数字哦，");
                                count ++;
                                continue;
                            }
                            else if(strlen(trim(buf)) > 8)
                            {
                                if(count == 3)
                                {
                                    puts("错误次数过多，停止添加！正在返回主菜单！");
                                    Sleep(1500);
                                    return ;
                                }
                                printf("长度过长，");
                                count ++;
                                continue;
                            }else{
                                break;
                            }
                    }
                    groupID = atoi(trim(buf));
           grpfinish:count = 0;
                    menuShowDetailsByDetails(username,address,homeaddress,email,telphone,groupID);
                printf("您确定(y/N)？");
                gets(buf);
            if(strcmp(trim(buf),"Y") == 0 ||
               strcmp(trim(buf),"y") == 0  )
            {
                if(modifyUser(tmp,username,address,homeaddress,email,telphone,groupID) == True)
                {
                    puts("修改成功！");
                }else{
                    puts("修改失败！");
                }
            }else
            {
                puts("您已经取消了修改");
            }
            if(obj != NULL)
            {
                puts("正在返回主菜单……");
                Sleep(1500);
                return ;
            }

    }else{
        puts("您已经取消了修改操作！");
        puts("正在返回主菜单……");
        Sleep(1500);
    return;
    }
    printf("是否要继续修改(y/N)？");
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        tmp = NULL;
        count = 0;
        clear();
        goto segment;
    }
    puts("正在返回主菜单……");
    Sleep(1500);
    return;
}
//////////////////////////////////////
void coreAddNewGroup()
{
    int count = 0;
    char buf[BUFFSIZE] = {0};
    char name[BUFFSIZE];
    char *color = "3c";//暂不添加本功能
    puts("\t\t\t添加联系人群组");
segment:
    puts("\t      [误入的话就多次错误输入触发返回]");
    puts("========================================================");
    printf("请输入群组名:");
    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
    {
        if(count == 3)
        {
            puts("错误次数过多，停止添加！正在返回主菜单！");
            Sleep(1500);
            return ;
        }
        printf("没有正确输入，请重新输入:");
        count ++;
    }
    strcpy(name,trim(buf));
    count = 0;
    puts("\t    --------------------------------------------------------++++++++ ");
    puts("\t    -- --                                                   ++++++++ ");
    puts("\t    -- --                  群组信息详情                     ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
    puts("\t    -- --                                                      --    ");
  printf("\t    -- --    群组名称：%-38s  --    \n"                          ,name);
  printf("\t    -- --    群组  ID：%-38s  --    \n"                       ,"添加后将制定");
    puts("\t    --------------------------------------------------------------   ");
     printf("您是否要添加\"%s\"这个群组？(y/N):",name);
     while(1)
     {
         while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
         {
            if(count == 3)
            {
                puts("错误次数过多，停止添加！正在返回主菜单！");
                Sleep(1500);
                return ;
            }
                printf("没有正确输入，:");
                count ++;
         }
         if(strcmp(trim(buf),"y") == 0 || strcmp(trim(buf),"Y") == 0)
         {
            puts("请等待……");
            BOOLEAN result = addGroup(name,color);
            if(result > 0)
            {
                puts("恭喜您，添加成功！");
                printf("您是否要继续添加？(y/N)");
                    gets(buf);
                    if(strcmp(trim(buf),"Y") == 0 ||
                       strcmp(trim(buf),"y") == 0 )
                       {
                           clear();
                           goto segment;
                       }
            }
            else if(result == -1)
                puts("抱歉，群组重复，请尝试修改联系人操作！");
            else
                puts("抱歉，添加失败！请联系管理员");
            puts("正在返回主菜单……");
            Sleep(1500);
            return;
         }else{
                puts("您已经取消插入操作，正在返回主菜单……");
                Sleep(1500);
                return ;
         }
     }
}

void coreSearchGroup()
{
    int count = 0; //错误次数
    pGroup tmp = NULL;
    pGroup user = NULL;//用户实体
    //C_UINT container = NULL;//ID容器
    //unsigned int *IDs = NULL;//ID实质容器
    int type = 0; //查找方式
    char buf[BUFFSIZE] = {0};
    puts("\t\t\t查询群组");
segment:
    puts("\t      [误入的话就多次错误输入触发返回]");
    puts("========================================================");
    puts("我们提供了以下查询方式：");
    puts("========================================================");
    puts("| 1.ID精确查找 | 2.群组名称精确查找 |                  |");
    puts("========================================================");

    while(1){
        printf("请输入一个查找方式(1,2):");
        while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
         {
            if(count == 3)
            {
                puts("错误次数过多，停止添加！正在返回主菜单！");
                Sleep(1500);
                return ;
            }
         }
         if(strcmp(trim(buf),"1") != 0 &&
            strcmp(trim(buf),"2") != 0  )
         {
            if(count == 3)
            {
                puts("错误次数过多，停止添加！正在返回主菜单！");
                Sleep(1500);
                return ;
            }
            printf("格式有误，");
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
            printf("请输入要查询的群组ID[全部查找输入0]:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止查询！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("没有正确输入，:");
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
                    puts("抱歉，不存在该群组！");
                }else{
                    menuShowGroupByID(tmp->ID);
                    user = tmp;
                }
            }
            break;
        case 2:
            printf("请输入要查询的群组名:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止查询！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("没有正确输入，:");
                count ++;
            }
            tmp = getGroup(2,trim(buf));
            if(tmp == NULL)
            {
                puts("抱歉，不存在该群组！");
            }else{
                clear();
                menuShowGroupByID(tmp->ID);
                user = tmp;
            }
            break;
    }

    if(user != NULL)
    {
            puts("\t\t\t      我们提供了以下操作方式：");
            puts("\t    ==============================================================");
            puts("\t    |  1.修改群组  |  2.删除群组  |  3.继续查询   |   0.不操作   |");
            puts("\t    ==============================================================");

                while(1){
                    printf("请输入你将要进行的操作(0,1,2,3):");
                    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                     {
                        if(count == 3)
                        {
                            puts("错误次数过多，程序终止！正在返回主菜单！");
                            Sleep(1500);
                            return ;
                        }
                            printf("没有正确输入，:");
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
                            puts("错误次数过多，程序终止！正在返回主菜单！");
                            Sleep(1500);
                            return ;
                        }
                        printf("格式有误，");
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
                        puts("正在返回主菜单……");
                        Sleep(1500);
                        return ;
                        break;
                }


    }
    printf("您是否要继续查询？(y/N)");
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        clear();
        goto ID_SEGMENT;
    }
    puts("正在返回主菜单……");
    Sleep(1500);
end_segment:
      return ;
}

/**
 * 修改群组
 */
void coreChangeGroup(pGroup obj){
    int count = 0; //错误次数
    pGroup          tmp = NULL;
    char            name[BUFFSIZE];//群组名
    char            buf[BUFFSIZE];
    if(obj == NULL)
    {
        puts("\t\t\t修改群组");
    segment:
        puts("\t      [误入的话就多次错误输入触发返回]");
        puts("========================================================");
        puts("为了安全性，我们只提供了ID查找：");
      printf("请输入要修改的群组ID:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止查询！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("没有正确输入，:");
                count ++;
            }
        tmp = getGroup(1,atoi(trim(buf)));
        count = 0;
        if(tmp == NULL)
        {
            puts("抱歉，查找不到此群组,正在返回主菜单");
            Sleep(1500);
            return;
        }
    }else{
        tmp = obj;
    }
    if(tmp == NULL)
    {
        puts("位置指针错误！正在退出程序！");
        exit(255);
        return ;
    }
    printf("您是否要修改 %s 这个群组(y/N)？",tmp->name);
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
       {
                printf("请输入群组名:");
                while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                {
                    if(count == 3)
                    {
                        puts("错误次数过多，停止添加！正在返回主菜单！");
                        Sleep(1500);
                        return ;
                    }
                    printf("没有正确输入，请重新输入:");
                    count ++;
                }
                strcpy(name,trim(buf));
                count = 0;

                puts("\t    --------------------------------------------------------++++++++ ");
                puts("\t    -- --                                                   ++++++++ ");
                puts("\t    -- --                新群组信息详情                     ++++++++ ");
                puts("\t    -- --    ----------------------------------------          --    ");
                puts("\t    -- --                                                      --    ");
              printf("\t    -- --    群组名称：%-38s  --    \n"                          ,name);
              printf("\t    -- --    群组  ID：%-38u  --    \n"                       ,tmp->ID);
                puts("\t    --------------------------------------------------------------   ");
                 printf("您是否要修改原名称为\"%s\"，现名称为\"%s\"这个群组？(y/N):",tmp->name,name);
                     while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                     {
                        if(count == 3)
                        {
                            puts("错误次数过多，停止添加！正在返回主菜单！");
                            Sleep(1500);
                            return ;
                        }
                            printf("没有正确输入，:");
                            count ++;
                     }
                     count = 0;
                     if(strcmp(trim(buf),"Y") == 0 ||
                        strcmp(trim(buf),"y") == 0  )
                     {
                        if(modifyGroup(tmp,name,tmp->Color))
                        {
                            puts("修改成功！");
                        }else{
                            puts("修改失败！");
                        }
                        if(obj != NULL)
                        {
                            Sleep(1500);
                            return;
                        }
                     }else{
                        puts("您取消了该操作！正在返回主菜单……");
                        Sleep(1500);
                        return ;
                     }

       }else{
               puts("您取消了该操作！正在返回主菜单……");
               Sleep(1500);
               return ;
    }
    printf("是否要继续修改(y/N)？");
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        tmp = NULL;
        count = 0;
        clear();
        goto segment;
    }
    puts("正在返回主菜单……");
    Sleep(1500);
    return;

}
/**
 * 群组删除
 */
 void coreDeleteGroup(pGroup obj)
 {
    int count = 0; //错误次数
    pGroup tmp = NULL;
    char buf[BUFFSIZE] = {0};
    if(obj == NULL)
    {
        puts("\t\t\t删除群组");
    segment:
        puts("\t      [误入的话就多次错误输入触发返回]");
        puts("========================================================");
        puts("为了安全性，我们只提供了ID查找删除：");
      printf("请输入要删除的群组ID:");
            while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
            {
                if(count == 3)
                {
                    puts("错误次数过多，停止查询！正在返回主菜单！");
                    Sleep(1500);
                    return ;
                }
                printf("没有正确输入，:");
                count ++;
            }
        tmp = getGroup(1,atoi(trim(buf)));
        count = 0;
        if(tmp == NULL)
        {
            puts("抱歉，查找不到此群组,正在返回主菜单");
            Sleep(1500);
            return;
        }
    }else{
        tmp = obj;
    }
    if(tmp == NULL)
    {
        puts("位置指针错误！正在退出程序！");
        exit(255);
        return ;
    }
    puts("=================================================");
    puts("|                  **注意事项**                 |");
    puts("|   您如果删除了该群组后，该群组内成员自动解散，|");
    puts("|直到您重新对其分配新组。                       |");
    puts("=================================================");
    printf("您是否要删除 ID: %u 名称：%s 这个群组(y/N)？",tmp->ID,tmp->name);
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        if(removeGroup(1,tmp->ID))
        {
            puts("恭喜您，删除成功");
        }else{
            puts("抱歉，删除失败！请联系管理员解决");
        }
            if(obj != NULL)
            {
               puts("正在返回主菜单……");
                Sleep(1500);
                return ;
            }

    }else{
        puts("您已经取消了删除操作！");
    }
    printf("是否要继续删除(y/N)？");
    gets(buf);
    if(strcmp(trim(buf),"Y") == 0 ||
       strcmp(trim(buf),"y") == 0  )
    {
        tmp = NULL;
        count = 0;
        clear();
        goto segment;
    }
    puts("正在返回主菜单……");
    Sleep(1500);
    return;
}

/**
 * 导出
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
                printf("-daras: %s: 未找到命令\n",buf);
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
                    puts("-plop: 4: 该功能尚未实现");
                    break;
                default:
                    printf("-plop: %s: 未找到命令\n",buf);
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
            printf("-daras: %s: 未找到命令\n",buf);
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
                printf("-plop: %s: 未找到命令\n",buf);
                break;
        }
     }
}

/**
 * 导出链表到文件
 * @param int type
 *            type = 1 csv  导出
 *            type = 2 html 导出
 *            type = 3 text 导出
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
            puts("文件将保存至程序文件同级目录下命名为output.csv");
            break;
        case 2:
            puts("文件将保存至程序文件同级目录下命名为output.html");
            break;
        case 3:
            puts("文件将保存至程序文件同级目录下命名为output.txt");
            break;
     }
     puts("注意，文件若原先存在的话就会被覆盖，请注意数据安全！！！");
     printf("您即将进行导出操作,您确认(y/N)？");
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
             puts("导出成功！,正在调出界面");
             _getcwd(buf,BUFFSIZE);
             cmd = strcat(myDir,buf);
             system(cmd);

         }else{
            puts("导出失败！检查程序权限或者目标文件是否被占用！");
         }
            Sleep(1500);
            return ;
     }else{
        puts("您取消了本次操作！");
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
                printf("-daras: %s: 未找到命令\n",buf);
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
                           puts("未设置密码，请设置密码后重试！");
                           Sleep(1500);
                           goto menu;
                       }else{
                                if(key->status == 0)
                                {
                                    key->status = 1;
                                    puts("已添加密码保护！");
                                }else{
                                    key->status = 0;
                                    puts("已取消密码保护！");
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
                    printf("请输入旧密码：");
                    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        if(count == 3)
                        {
                            puts("错误次数过多，停止查询！正在返回主菜单！");
                            Sleep(1500);
                            goto menu;
                        }
                        printf("没有正确输入，:");
                        count ++;
                    }
                    if(strcmp(trim(buf),key->key) != 0)
                    {
                        puts("密码无效！");
                        Sleep(1500);
                        goto menu;
                    }
                    input_pwd:
                    count = 0;
                    printf("请输入新密码：");
                    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        if(count == 3)
                        {
                            puts("错误次数过多，停止查询！正在返回主菜单！");
                            Sleep(1500);
                            goto menu;
                        }
                        printf("没有正确输入，");
                        count ++;
                    }
                    strcpy(newPassword,trim(buf));
                    count = 0;
                    printf("请重新输入新密码：");
                    while(gets(buf) == NULL || strcmp(buf,"") == 0 || strcmp(trim(buf)," ") == 0)
                    {
                        if(count == 3)
                        {
                            puts("错误次数过多，停止查询！正在返回主菜单！");
                            Sleep(1500);
                            goto menu;
                        }
                        printf("没有正确输入，");
                        count ++;
                    }
                    if(strcmp(newPassword,trim(buf)) == 0 )
                    {
                        strcpy(key->key,newPassword);
                        puts("修改成功");
                        Sleep(1500);
                        goto menu;
                    }else{
                        puts("两次密码输入不同！");
                        Sleep(500);
                        goto input_pwd;
                    }
                    break;
                default:
                    printf("-plop: %s: 未找到命令\n",buf);
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
        puts("正在初始化加密功能……");
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
             printf("\t       密码错误次数过多，系统拒绝您再次输入！\n");
             Sleep(3000);
             exit(-2);
        }
        if(count)
        {
             printf("\t       请再次输入密码:");
        }else{
             printf("\t           请输入密码:");
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
            printf("\t           密码不正确,请重试\n");
            Sleep(1000);
            count ++;
            goto input_pwd;
        }


    }
}








