/*
    File: console.c
    Description: 控制台操作源码
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
             puts("\t    |               抱歉哦，查找不到您需要的信息！               |   ");
             puts("\t    --------------------------------------------------------------   ");
}

void menuMain()
{
     puts("\t    -------------------------------------------------------------    ");
     puts("\t    *                                                           *    ");
     puts("\t   * *               === 欢迎使用通讯录系统 ===                 *   ");
     puts("\t  * * *                                                       * * *  ");
     puts("\t *  *  *  ------------------------------------------------   *  *  * ");
     puts("\t  * * *   |     1.新增联系人     |     2.查询联系人      |    * * *  ");
     puts("\t   * *    ------------------------------------------------     * *   ");
     puts("\t    *     |     3.删除联系人     |     4.修改联系人      |      *    ");
     puts("\t   * *    ------------------------------------------------     * *   ");
     puts("\t  * * *   |     5.新增群组       |     6.查询群组        |    * * *  ");
     puts("\t *  *  *  ------------------------------------------------   *  *  * ");
     puts("\t  * * *   |     7.删除群组       |     8.修改群组        |    * * *  ");
     puts("\t   * *    ------------------------------------------------     * *   ");
     puts("\t    *     |     9.数据管理       |    10.密码保护        |      *    ");
     puts("\t   * *    ------------------------------------------------     * *   ");
     puts("\t  * * *   |                   0.退出                     |    * * *  ");
     puts("\t *  *  *  ------------------------------------------------   *  *  * ");
     puts("\t  * * *                                                       * * *  ");
     puts("\t    *              请输入功能号来进行相关操作^_^                *    ");
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
    puts("\t    --                 正在退出，请稍后……                    --    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                 +--王  笑(Display)                      --    ");
    puts("\t    --                 |                                       --    ");
    puts("\t    --            By:--+--吕中华(Kernel)                       --    ");
    puts("\t    --                 |                                       --    ");
    puts("\t    --                 +--郎需捷(Logic)                        --    ");
    puts("\t    --                                                         --    ");
    puts("\t    --                                                         --    ");
    puts("\t    -------------------------------------------------------------    ");
    return ;
}

/**
  * 根据用户ID显示一个联系人信息
  * @param unsigned int ID 用户ID
  * @author wx
  * @date 2016 07 12
  */
void menuShowDetailsByID(unsigned int ID)
{
    int i = 0;//循环体
    pUSER obj = getAUSER(1,ID);
    char *group = NULL;
    pGroup tmp;
    if(obj == NULL) //空指针错误
    {
        puts("出现未知错误，正在返回……");
        Sleep(500);
        return ;
    }
    tmp = getGroup(1,obj->groupID);
    group  = (tmp == NULL) ? "无群组" : tmp->name;


    clear();
    puts("\t                                                            ");
    puts("\t                                                            ++++++++ ");
    puts("\t    --------------------------------------------------------++++++++ ");
    puts("\t    -- --                                                   ++++++++ ");
    puts("\t    -- --                 联系人信息详情                    ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
    puts("\t    -- --                                                      --    ");
  printf("\t    -- --    姓    名：%-38s  --    \n"                 ,obj->username);
  printf("\t    -- --    工作单位：%-38s  --    \n"                  ,obj->address);
  printf("\t    -- --    家庭住址：%-38s  --    \n"              ,obj->homeaddress);
  printf("\t    -- --    电子邮箱: %-38s  --    \n"                    ,obj->email);
  printf("\t    -- ---   所在群组：%-15s                         --    \n",  group);
    puts("\t    -- ----- 联系方式：                                        --    ");
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
  * 根据用户实体显示一个联系人信息
  * @param pUSER obj 用户实体
  * @author wx
  * @date 2016 07 12
  */

void menuShowDetailsBypUSER(pUSER obj)
{
    int i = 0;//循环体
    char *group = NULL;
    pGroup tmp;
    if(obj == NULL) //空指针错误
    {
        puts("出现未知错误，正在返回……");
        Sleep(500);
        return ;
    }
    tmp = getGroup(1,obj->groupID);
    group  = (tmp == NULL) ? "无群组" : tmp->name;


    clear();
    puts("\t                                                            ");
    puts("\t                                                            ++++++++ ");
    puts("\t    --------------------------------------------------------++++++++ ");
    puts("\t    -- --                                                   ++++++++ ");
    puts("\t    -- --                 联系人信息详情                    ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
    puts("\t    -- --                                                      --    ");
  printf("\t    -- --    姓    名：%-38s  --    \n"                 ,obj->username);
  printf("\t    -- --    工作单位：%-38s  --    \n"                  ,obj->address);
  printf("\t    -- --    家庭住址：%-38s  --    \n"              ,obj->homeaddress);
  printf("\t    -- --    电子邮箱: %-38s  --    \n"                    ,obj->email);
  printf("\t    -- ---   所在群组：%-15s                         --    \n"  ,group);
    puts("\t    -- ----- 联系方式：                                        --    ");
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
 *  根据信息显示一个临时用户名（用于添加或修改之前确认）
 * @param char *name 联系人姓名
 * @param char *address 联系addUSERToGroup人工作单位住址
 * @param char *homeaddress 联系人家庭住址
 * @param char *email 电子邮件地址
 * @param char *telphone 主要电话
 * @param uint  groupID 群组名
 * @return int  出现错误返回0 , 成功返回 1
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
       ) //空指针错误
    {
        puts("出现未知错误，正在返回……");
        Sleep(500);
        return ;
    }
    tmp = getGroup(1,groupID);
    group  = (tmp == NULL) ? "无群组" : tmp->name;


    clear();
    puts("\t                                                            ");
    puts("\t                                                            ++++++++ ");
    puts("\t    --------------------------------------------------------++++++++ ");
    puts("\t    -- --                                                   ++++++++ ");
    puts("\t    -- --                 联系人信息详情                    ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
    puts("\t    -- --                                                      --    ");
  printf("\t    -- --    姓    名：%-38s  --    \n"                          ,name);
  printf("\t    -- --    工作单位：%-38s  --    \n"                       ,address);
  printf("\t    -- --    家庭住址：%-38s  --    \n"                   ,homeaddress);
  printf("\t    -- --    电子邮箱: %-38s  --    \n"                         ,email);
  printf("\t    -- ---   所在群组：%-15s                         --    \n"  ,group);
    puts("\t    -- ----- 联系方式：                                        --    ");
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
 *  通过unsigned int 数组显示用户列表
 *  @param unsigned int ID[] 用户数组
 *  @author wx & hafrans
 **/
void menuShowUserList(unsigned int ID[])
{
    pUSER obj  = NULL;
    pGroup grp = NULL;
    char *text = NULL;
    int i   = 0;//循环变量
    if(ID[0] == 0)
    {
        menuNoResult();
        Sleep(1000);
        return ;
    }
        puts("  +----------------------------------------------------------------------------+");
        puts("  | I D |   姓名   |    主要联系电话  |    工作单位              |  所在群组   |");
        puts("  +----------------------------------------------------------------------------+");
    for(i = 0;ID[i] != 0;i++)
    {
        obj = getAUSER(1,ID[i]);
        if(obj == NULL)
            continue;
        grp = getGroup(1,obj->groupID);
        if(grp == NULL)
            text = "无群组";
        else
            text = grp->name;
      //puts("  | I D |  姓名  |  主要联系电话  |    工作单位              |   所在群组  |");
      printf("  | %-4u| %-8s | %-16s |  %-22s  |  %-9s  |\n",obj->ID,obj->username,obj->telphones[0],obj->address,text);
        puts("  +----------------------------------------------------------------------------+");
    }


}
/**
 *  通过unsigned int 数组显示群组列表
 *  @param unsigned int ID[] 群组ID数组
 *  @author wx & hafrans
 **/
 void menuShowGroupList(unsigned int ID[])
 {
         pGroup tmp = NULL;
         int i   = 0,k=0;//循环变量
         int count = 0;//人数
         if(ID[0] == 0)
         {
             menuNoResult();
             Sleep(1000);
             return ;
         }
        puts("\t  +----------------------------------------+");
        puts("\t  |   I D  |       群组名     |    人数    |");//8,18,12
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
  * 通过ID显示群组详情
  * @param unsigned int ID 群组ID
  */
void menuShowGroupByID(unsigned int ID)
{
    C_UINT data = NULL;//容器
    int i = 0;
    pGroup grp = getGroup(1,ID);
    unsigned int *tt = NULL;
    if(grp == NULL)
    {
        puts("查询不到这个群组！");
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
    puts("\t    -- --                  群组信息详情                     ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
    puts("\t    -- --                                                      --    ");
  printf("\t    -- --    群组名称：%-38s  --    \n"                          ,grp->name);
  printf("\t    -- --    群组  ID：%-38u  --    \n"                       ,grp->ID);
    puts("\t    --------------------------------------------------------------   ");
    puts("\t    -- --                    群组成员                          --    ");
    puts("\t    --------------------------------------------------------------   ");
    menuShowUserList(tt);

}

void menuOutputLayout()
{
    puts("\t                                                            ");
    puts("\t                                                            ++++++++ ");
    puts("\t    --------------------------------------------------------++++++++ ");
    puts("\t    -- --                                                   ++++++++ ");
    puts("\t    -- --               数据管理中心                        ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
    puts("\t    -- --    1.数据导出至CSV                                   --    ");
  printf("\t    -- --    2.数据导出至HTML                                  --    \n");
  printf("\t    -- --    3.数据导出至TXT                                   --    \n");
    puts("\t    -- --    4.数据由CSV导入                                   --    ");
    puts("\t    -- ---   0.返回                                 @          --    ");
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
    puts("\t    -- --               密码管理中心                        ++++++++ ");
    puts("\t    -- --    ----------------------------------------          --    ");
  printf("\t    -- --    |    密码保护状态：%4s                 |         --    \n",key->status?"开":"关");
    puts("\t    -- --    ----------------------------------------          --    ");
  printf("\t    -- --    1.%-15s                                 --    \n",key->status?"关闭密码保护":"开启密码保护");
  printf("\t    -- --    2.%-15s                                 --    \n",strcmp(key->key,"")?"修改密码":"新增密码");
    puts("\t    -- ---   0.返回                                            --    ");
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
             puts("\t    |             密码文件被破坏！程序无法启动                   |   ");
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
                puts("\t    -- --             欢迎使用本通讯录系统                  ++++++++ ");
                puts("\t    -- --    ----------------------------------------          --    ");
                puts("\t    -- --              主人开启了密码保护                      --    ");
                puts("\t    -- --         必须输入正确的密码才可以进入哦               --    ");
                puts("\t    =============================================================  ");
//              printf("\t           请输入密码:");

    }
}
