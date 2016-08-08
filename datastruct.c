/**'/
    File: datastruct.c
    Description: 数据结构定义源码
    Updated: Jul 10 2016
    Author : Hafrans Newton

*/
#include "datastruct.h"

/**
 *  以安全的方式加入一个数组链表元素
 * @param char *name 群组名称
 * @param char *color 个性化颜色
 * @return int 出现错误返回0 成功插入返回群组ID 如果重复则返回-1
 *
 */
 int addGroup(char *name,
              char *color)
 {
     if(strcmp(name,"") == 0 || strcmp(color,"") == 0)
        return 0;
     if(findGroup(2,name) != 0)
     {
         return -1;
     }
     pGroup data = (pGroup)calloc(1,sizeof(Group));
     if(data == NULL)
        return False;

     data->ID = ++maxRegistedGROUPID;
//        if(getGroupByUsingGroupID(data->ID) != NULL)
//        {
//            return -1;
//        }
     strcpy(data->name,name);
     strcpy(data->Color,color);
     if(!addGroupByInsertpGroupDATA(data))
     {
         maxRegistedGROUPID -- ;
         return 0;
     }
     return data->ID;
 }

/**
 *  以安全的方式加入一个用户链表元素
 * @param char *name 联系人姓名
 * @param char *address 联系人工作单位住址
 * @param char *homeaddress 联系人家庭住址
 * @param char *email 电子邮件地址
 * @param char *telphone 电话
 * @param uint groupID 群组名
 * @return int  出现错误返回0 , 成功返回 用户ID 如果插入重复则返回-1
 *
 */
 int addUser(char *name,
             char *address,
             char *homeaddress,
             char *email,
             char *telphone,
             unsigned int groupID
             )
 {
    if(name        == NULL ||
       address     == NULL ||
       homeaddress == NULL ||
       email       == NULL ||
       telphone    == NULL ||
       groupID      < 0     )
        return 0;
    if(getAUSERByUsingUSERNameOnce(name) != NULL)
    {
        return -1;
    }
    pUSER data = (pUSER)calloc(1,sizeof(USER));
    if(data == NULL)
        return False;
     data->ID = ++maxRegistedUSERID;
//    if(getUSERByUsingUSERID(data->ID)!= NULL)
//    {
//            return -1;
//    }
     strcpy(data->username,name);
     strcpy(data->address,address);
     strcpy(data->homeaddress,homeaddress);
     strcpy(data->email,email);
     strcpy(data->telphones[0],telphone);
     //return addGroupByInsertpGroupDATA(data)*data->ID;
     if(addUSERToGroup(data,groupID) == True) //bug fix
        data->groupID = groupID;
     if(addUSERByInsertpUSERDATA(data) == False)
     {
         maxRegistedUSERID -- ;

         return 0;
     }

     return data->ID;
 }

 /**
  * 检测一个群组是否存在[高级]
  * @param int type 测试方式
  *        type = 1 用ID测试        例如  findGroup(1,20);
  *        type = 2 用群组名称测试  例如 findGroup(2,"亲友");
  * @return unsigned int 查询成功后返回当前群组ID，否则返回0
  * @author Hafrans Newton
  */
  int findGroup(int type,...)
  {
      int num = 0;
      char *text = NULL;
      pGroup tmp = NULL;
      va_list ap;
      va_start(ap,type);
      switch(type){
        case 1:
            num = va_arg(ap,int);
            va_end(ap);
            tmp = getGroupByUsingGroupID(num);
            if(tmp == NULL)
                return 0;
            else
                return tmp->ID;
            break;
        case 2:
            text = va_arg(ap,char *);
            va_end(ap);
            tmp = getGroupByUsingGroupName(text);
            if(tmp == NULL)
                return 0;
            else
                return tmp->ID;
            break;
      }
      return 0;
  }

/**
 *  获取一个群组实体【高级】
  * @param int type 测试方式
  *        type = 1 用ID测试        例如  getGroup(1,20);
  *        type = 2 用群组名称测试  例如  getGroup(2,"亲友");
  * @return pGroup 成功返回一个可以操作的群组实体，否则返回一个NULL
  * @author Hafrans Newton
  */
  pGroup getGroup(int type,...)
  {
      int num = 0;
      char *text = NULL;
      pGroup tmp = NULL;
      va_list ap;
      va_start(ap,type);
      switch(type){
        case 1:
            num = va_arg(ap,unsigned int);
            va_end(ap);
            tmp = getGroupByUsingGroupID(num);
            if(tmp == NULL)
                return 0;
            else
                return tmp;
            break;
        case 2:
            text = va_arg(ap,char *);
            va_end(ap);
            tmp = getGroupByUsingGroupName(text);
            if(tmp == NULL)
                return 0;
            else
                return tmp;
            break;
      }
      return 0;
  }

  /**
   * [高级] 通过ID获取一个用户实体
   * @param int type 获取方式
   *        type = 1 通过ID形式获取用户实体
   *        type = 2 通过联系人姓名方式获取唯一用户实体
   * @return pUSER 用户实体【结构体指针】
   * @author Hafrans Newton
   */
pUSER getAUSER(int type,...)
{
    int num = 0;
      char *text = NULL;
      pUSER tmp = NULL;
      va_list ap;
      va_start(ap,type);
      switch(type){
        case 1:
            num = va_arg(ap,unsigned int);
            va_end(ap);
            tmp = getUSERByUsingUSERID(num);
            if(tmp == NULL)
                return 0;
            else
                return tmp;
            break;
        case 2:
            text = va_arg(ap,char *);
            va_end(ap);
            tmp = getAUSERByUsingUSERNameOnce(text);
            if(tmp == NULL)
                return 0;
            else
                return tmp;
            break;
      }
      return 0;

}

/**
  * 将规定的用户实体加入一个群组
  * @param pUSER obj 用户实体
  * @param unsigned int groupID
  * @return int 返回状态 0 失败 1 成功  -1 群组人数过多

  PS: 该函数给用户设置群组，
  如果GroupID设置为0则用户不属于任何群组

  */
int addUSERToGroup(pUSER obj,unsigned int groupID)
{
    int i = 0;
    if(obj == NULL || groupID < 0 )
        return False;
    if(groupID == 0){
        if(obj->groupID == 0)
            return True;
        else{
            pGroup tmp = getGroup(1,obj->groupID);
            if(tmp != NULL)
            {
                for(i = 0;i<128;i++)
                {
                    if(tmp->USERID[i] == obj->ID)
                    {
                        tmp->USERID[i] = 0;
                        break;
                    }
                }
            }
            obj->groupID = 0;
            return True;
        }
    }else{
        addUSERToGroup(obj,0);//归零操作
        pGroup tmp = getGroup(1,groupID);
        if(tmp == NULL)
            return False;
        for(i = 0;i<128;++i)
        {
            if(tmp->USERID[i] == 0)
            {
                tmp->USERID[i] = obj->ID;
                obj->groupID = groupID;
                return True;
            }
        }
        return -1;
    }
    return False;
}

/**
 *  以安全的方式修改一个用户链表元素
 * @param char *name 联系人姓名
 * @param char *address 联系人工作单位住址
 * @param char *homeaddress 联系人家庭住址
 * @param char *email 电子邮件地址
 * @param char *telphone 主要电话
 * @param uint groupID 群组名
 * @return int  出现错误返回0 , 成功返回 1
 *
 */
BOOLEAN modifyUser(pUSER          obj,
                     char         *name,
                     char         *address,
                     char         *homeaddress,
                     char         *email,
                     char         *telphone,
                     unsigned int  groupID
                    )
{
    if(obj == NULL)
        return False;
    if(name         == NULL ||
       address      == NULL ||
       homeaddress  == NULL ||
       email        == NULL ||
       telphone     == NULL ||
       groupID      <  0     )
        return False;
    strcpy(obj->username,name);
    strcpy(obj->address,address);
    strcpy(obj->homeaddress,homeaddress);
    strcpy(obj->email,email);
    strcpy(obj->telphones[0],telphone);
    return addUSERToGroup(obj,groupID);
}

/**
 *  【高级】修改一个数组链表元素
 * @param pGroup obj 获取的群组实体
 * @param char *name 群组名称
 * @param char *color 个性化颜色
 * @return BOOLEAN True 正确 False 错误
 *
 */
 int modifyGroup(pGroup obj,
                 char  *name,
                 char  *color)
 {
     if(obj              == NULL ||
        name             == NULL ||
        color            == NULL ||
        strcmp(name,"")  == 0    ||
        strcmp(color,"") == 0     )
        return False;
        strcpy(obj->name,name);
        strcpy(obj->Color,color);
        return True;

 }

/**
 * 【高级】通过ID 或 联系人姓名 删除用户链表
 * @param int type 类型
 *            type = 1 按照ID删除
 *            type = 2 按照联系人姓名删除
 * @param mixed 条件
 * @return BOOLEAN True - 成功 False - 失败
 * @author Hafrans
 * @date 07 11 2016
 */
BOOLEAN removeUser(int type,...)
{
    int   num = 0;
    char *text= 0;
    pUSER tt = NULL;
    va_list ap;
    va_start(ap,type);
    switch(type){
        case 1:
            num = va_arg(ap,unsigned int);
            tt = getAUSER(1,num);
            break;
        case 2:
            text= va_arg(ap,char *);
            tt = getAUSER(2,text);
            if(tt == NULL)
                return False;
            else
                num = tt->ID;
            break;
        default:
            return False;
            break;
    }
    va_end(ap);
    addUSERToGroup(tt,0);
    return removeUSERByUsingUSERID(num);
}

/**
 * 【高级】通过ID 或 群组名称 删除群组链表
 * @param int type 类型
 *            type = 1 按照ID删除
 *            type = 2 按照群组名称删除
 * @param mixed 条件
 * @return BOOLEAN True - 成功 False - 失败
 * @author Hafrans
 * @date 07 11 2016
 */
BOOLEAN removeGroup(int type,...)
{
    int   num = 0;
    char *text= 0;
    va_list ap;
    va_start(ap,type);
    switch(type){
        case 1:
            num = va_arg(ap,unsigned int);
            break;
        case 2:
            text= va_arg(ap,char *);
            num = findGroup(2,text);
            break;
        default:
            return False;
            break;
    }
    va_end(ap);
    return removeGroupByUsingGroupID(num);
}

/**
 * 修改用户的联系方式电话号码
 * @param pUSER obj 用户实体
 * @param int type 修改方式
 *            type = 0 添加   changeUserTel(obj,0,"13800138000");
 *            type = 1 修改   changeUserTel(obj,1,"13800138000","13863350001");
 *            type = 2 删除   changeUserTel(obj,2,"13800000000");
 * @param mixed 条件
 * @return  1 添加成功
 *          0 添加失败
 *         -1 用户不能再添加手机号了
 *         -2 查询不到要修改的号码
 *         -3 删除时查询不到要删除的手机号码
 *         -4 传入的用户结构体指针错误
 *         -5 添加的时候发现了重复
 *
 */
 int changeUserTel(pUSER obj,int type,...)
 {
     char *textA = NULL;
     char *textB = NULL;
     int       i = NULL;
     va_list ap;
     if(obj == NULL)
        return -4;
     va_start(ap,type);
     textA = va_arg(ap,char *);
     if(strlen(textA)>=20)
        return 0;
     switch (type){
        case 0:
            va_end(ap);
            for(i = 0;i<8;++i)
            {
                if(strcmp(obj->telphones[i],textA) == 0)
                    return -5;
            }
            for(i = 0;i<8;++i)
            {
                if(strcmp(obj->telphones[i],"") == 0 ||
                   obj->telphones[i][0]         == 0  )
                {
                    strcpy(obj->telphones[i],textA);
                    return 1;
                }
            }
            break;
        case 1:
            textB = va_arg(ap,char *);
            if(strlen(textB)>=20)
                return 0;
            va_end(ap);
            for(i = 0;i<8;++i)
            {
                if(strcmp(obj->telphones[i],textA) == 0)
                    break;
            }
            if(i<8)
            {
                strcpy(obj->telphones[i],textB);
                return 1;
            }else{
                return -2;
            }
            break;
        case 2:
            va_end(ap);
            for(i = 0;i<8;++i)
            {
                if(strcmp(obj->telphones[i],textA) == 0)
                {
                    strcpy(obj->telphones[i],"");
                    return 1;
                }
            }
                    return -3;
            break;
        default:
            va_end(ap);
            return 0;
            break;
     }
     return 0;
 }

/**
 * 通过生成pUser指针插入用户数据升序链表
 * @author Hafrans
 * @date 07/09/2016
 * @param pUSER data 插入的用户数据体
 * @return BOOLEAN True 成功 False 失败
 */
BOOLEAN addUSERByInsertpUSERDATA(pUSER data)
{
    if(data == NULL)
        return False;
    puFile tmp = uHEAD;
    puFile parent = NULL;

    puFile newTmp = (puFile)malloc(sizeof(uFile));
    memcpy(&newTmp->data,data,sizeof(USER));
    newTmp->next = NULL;

    if(uHEAD == NULL)
    {
        uHEAD = newTmp;
        return True;
    }else{

        while(tmp != NULL)
        {
            if(tmp == uHEAD && tmp->data.ID > data->ID)
            {
                newTmp->next = uHEAD;
                uHEAD = newTmp;
                if(data->ID > maxRegistedUSERID)
                    maxRegistedUSERID = data->ID;
                return True;
            }else if(tmp->data.ID > data->ID){
                parent->next = newTmp;
                newTmp->next = tmp;
                if(data->ID > maxRegistedUSERID)
                    maxRegistedUSERID = data->ID;
                return True;
            }
            parent = tmp;
            tmp = parent->next;
        }
            parent->next = newTmp;
            if(data->ID > maxRegistedUSERID)
                    maxRegistedUSERID = data->ID;
            return True;
        return True;
    }
    return False;
}

/**
 * 删除所有用户数据并设置用户链表为空
 * @author Hafrans
 * @date   July 10 2016
 * @return BOOLEAN True 成功 False 失败
 */
 BOOLEAN removeAllUserAndSetuHEADNULL(){
    if(uHEAD == NULL)
        return True;
    puFile tmp = uHEAD; //复制给循环变量
         uHEAD = NULL;  //链表头清空
    while(tmp != NULL)  //开始清理
    {
         puFile trash = tmp;
         tmp = tmp->next;
         free(trash);   //垃圾回收
    }
    return True;
 }

 /**
 * 通过生成pGroup指针插入用户数据升序链表
 * @author Hafrans
 * @date 07/10/2016
 * @param pGroup data 插入的用户数据体
 * @return BOOLEAN True 成功 False 失败
 */
BOOLEAN addGroupByInsertpGroupDATA(pGroup data)
{
    //puts(data->name);
    if(data == NULL)
        return False;
    pgFile tmp = gHEAD;
    pgFile parent = NULL;
    pgFile newTmp = (pgFile)malloc(sizeof(gFile));
    memcpy(&newTmp->data,data,sizeof(Group));
    newTmp->next = NULL;

    if(gHEAD == NULL)
    {
        gHEAD = newTmp;
        return True;
    }else{

        while(tmp != NULL)
        {
            if(tmp == gHEAD && tmp->data.ID > data->ID)
            {
                newTmp->next = gHEAD;
                gHEAD = newTmp;
                if(data->ID > maxRegistedGROUPID)
                    maxRegistedGROUPID = data->ID;
                return True;
            }else if(tmp->data.ID > data->ID){
                parent->next = newTmp;
                newTmp->next = tmp;
                if(data->ID > maxRegistedGROUPID)
                    maxRegistedGROUPID = data->ID;
                return True;
            }
            parent = tmp;
            tmp = parent->next;
        }
            parent->next = newTmp;
            if(data->ID > maxRegistedGROUPID)
                    maxRegistedGROUPID = data->ID;
            return True;
    }
    return False;
}

/**
 * 删除所有群组数据并设置群组链表为空
 * @author Hafrans
 * @date   July 11 2016
 * @return BOOLEAN True 成功 False 失败
 */
 BOOLEAN removeAllGroupAndSetgHEADNULL(){
    if(gHEAD == NULL)
        return True;
    pgFile tmp = gHEAD; //复制给循环变量
         gHEAD = NULL;  //链表头清空
    while(tmp != NULL)  //开始清理
    {
         pgFile trash = tmp;
         tmp = tmp->next;
         free(trash);   //垃圾回收
    }
    return True;
 }
/**
 * 根据ID删除用户链表中的元素【底层】
 * @author Hafrans
 * @date July 11 2016
 * @param unsigned int ID 将要删除的ID
 * @return BOOLEAN True 成功， False 失败
 */
 BOOLEAN removeUSERByUsingUSERID(unsigned int ID)
 {
    if(ID > maxRegistedUSERID)
        return False;
    puFile tmp = uHEAD;
    puFile parent = NULL;
    if(uHEAD == NULL)
        return False;
    while(tmp != NULL)
    {
        if(tmp->data.ID == ID)
        {
            if(tmp == uHEAD)
            {
                uHEAD = uHEAD->next;
                free(tmp);
                return True;
            }else{
                parent->next = tmp->next;
                free(tmp);
                return True;
            }
        }
        parent = tmp;
        tmp = parent->next;
    }
    return False;
 }

 /**
  * 【底层】通过ID获取群组实体
  * @param unsigned int ID ID
  * @return pGroup 群组实体，如果没有检测到则返回0
  * @author Hafrans Newton
  */
  pGroup getGroupByUsingGroupID(unsigned int ID)
  {
        pgFile tmp = gHEAD;
        while(tmp != NULL)
        {
            if(tmp->data.ID == ID)
                return &tmp->data;
            if(ID < tmp->data.ID)
                return 0;
            tmp = tmp->next;
        }
        return 0;
  }

 /**
  * 【底层】通过名称获取群组实体
  * @param char *text 群组名称
  * @return pGroup 群组实体，如果没有检测到则返回0(NULL)
  * @author Hafrans Newton
  */
  pGroup getGroupByUsingGroupName(char *text)
  {
      if(text == NULL)
        return NULL;
      pgFile tmp = gHEAD;

        while(tmp != NULL)
        {
            if(strcmp(tmp->data.name,text) == 0)
                return &tmp->data;
            tmp = tmp->next;
        }
        return 0;
  }

/**
 * 通过ID获取用户实体【底层】
 * @param unsigned int ID 要查找的用户ID
 * @return pUSER 用户实体，如果没有检测到则返回0(NULL)
 * @author Hafrans Newton
 */
pUSER getUSERByUsingUSERID(unsigned int ID)
{
    puFile tmp = uHEAD;
    if(tmp == NULL)
        return 0;

        while(tmp != NULL)
        {
            if(tmp->data.ID == ID)
                return &tmp->data;
            if(ID < tmp->data.ID)
                return 0;
            tmp = tmp->next;
        }
        return 0;
}

/**
 * 通过精确用户名获取用户实体【底层】
 * @param unsigned int ID 要查找的用户ID
 * @return pUSER 用户实体，如果没有检测到则返回0(NULL)
 * @author Hafrans Newton
 */
pUSER getAUSERByUsingUSERNameOnce(char *text)
{
    puFile tmp = uHEAD;
    while(tmp != NULL)
    {
        if(strcmp(tmp->data.username,text) == 0)
        {
            return &tmp->data;
        }
        tmp = tmp->next;
    }
    return NULL;
}

/**
 * 通过模糊用户名获取用户实体【底层】
 * @param  char *text 查找字段
 * @return pUSER *用户实体组，如果没有检测到则返回data[0] = (NULL)
 * @author Hafrans Newton
 */
 pUSER *getUSERByUsingUSERName(char *text)
 {
    int count = 1; //内存计数
    size_t pUSERSize  = sizeof(pUSER);//单个内存指向大小
    pUSER *data = (pUSER *)malloc(pUSERSize*count); //向堆内存申请新内存
    if(text == NULL)
    {
        data[count - 1] = 0;
        return data;
    }
    puFile tmp = uHEAD;
    while(tmp != NULL)
    {
        if(strstr(tmp->data.username,text) != NULL)
        {
            data[count - 1] = &tmp->data;
            data = (pUSER *)realloc(data,pUSERSize*(++count)); //向堆内存申请新内存
        }
        tmp = tmp->next;
    }
    data[count-1] = 0;
    return data;
 }

 /**
 * 通过模糊所有信息获取用户实体【底层】
 * @param char *text 查找字段   0为查找全部
 * @return pUSER *用户实体组，如果没有检测到则返回data[0] = (NULL)
 * @author Hafrans Newton
 */
 pUSER *getUSERByUsingAll(char *text)
 {
    int count = 1; //内存计数
    size_t pUSERSize  = sizeof(pUSER);//单个内存指向大小
    pUSER *data = (pUSER *)malloc(pUSERSize*count); //向堆内存申请新内存
    if(text == NULL)
    {
        data[count - 1] = 0;
        return data;
    }
    puFile tmp = uHEAD;
    while(tmp != NULL)
    {
        if(strstr(tmp->data.username,text)     != NULL ||
           strstr(tmp->data.address,text)      != NULL ||
           strstr(tmp->data.homeaddress,text)  != NULL ||
           strstr(tmp->data.email,text)        != NULL ||
           strstr(tmp->data.telphones[0],text) != NULL ||
           strstr(tmp->data.telphones[1],text) != NULL ||
           strstr(tmp->data.telphones[2],text) != NULL ||
           strstr(tmp->data.telphones[3],text) != NULL ||
           strstr(tmp->data.telphones[4],text) != NULL ||
           strstr(tmp->data.telphones[5],text) != NULL ||
           strstr(tmp->data.telphones[6],text) != NULL ||
           strstr(tmp->data.telphones[7],text) != NULL
           )
        {
            data[count - 1] = &tmp->data;
            data = (pUSER *)realloc(data,pUSERSize*(++count)); //向堆内存申请新内存
        }
        tmp = tmp->next;
    }
    data[count-1] = 0;
    return data;
 }

/**
 * 根据ID删除群组链表中的元素【底层】
 * @author Hafrans
 * @date July 11 2016
 * @param unsigned int ID 将要删除的ID
 * @return BOOLEAN True 成功， False 失败
 */
BOOLEAN removeGroupByUsingGroupID(unsigned int ID)
{
    if(ID > maxRegistedGROUPID)
        return False;
    pgFile tmp = gHEAD;
    pgFile parent = NULL;
    if(gHEAD == NULL)
        return False;
    while(tmp != NULL)
    {
        if(tmp->data.ID == ID)
        {
            if(tmp == gHEAD)
            {
                gHEAD = gHEAD->next;
                free(tmp);
                return True;
            }else{
                parent->next = tmp->next;
                free(tmp);
                return True;
            }
        }
        parent = tmp;
        tmp = parent->next;
    }
    return False;

}

/**
 * [底层] 获取所有群组ID
 * @return unsigned int * 数组以0为结尾
 * @author Hafrans Newton
 */
unsigned int *getAllGroupID()
{
    pgFile tmp = gHEAD;
    unsigned int *data = NULL;
    C_UINT container = containerInitUint();
    while(tmp != NULL)
    {
        containerPushBackUint(container,tmp->data.ID);
        tmp = tmp->next;
    }
    data = containerGetDataUint(container);
    //此时或发生了内存泄漏
    return data;
}

/**
 * [底层] 获取所有用户ID
 * @author Hafrans Newton
 * @return unsigned int * 数组以0为结尾
 */
unsigned int *getAllUSERID()
{
    puFile tmp = uHEAD;
    unsigned int *data = NULL;
    C_UINT container = containerInitUint();
    while(tmp != NULL)
    {
        containerPushBackUint(container,tmp->data.ID);
        tmp = tmp->next;
    }
    data = containerGetDataUint(container);
    //此时或发生了内存泄漏
    return data;
}

#ifdef DEBUG

 /**
  * [调试]输出链表中所有群组数据
  *
  */
  void debugPrintAllGroups()
  {
          pgFile tmp = gHEAD;
          int i = 0;
        while(tmp != NULL)
        {
            puts("***************************");
            printf("%u | %s | %s\n",tmp->data.ID,tmp->data.name,tmp->data.Color);
            unsigned int *tt = tmp->data.USERID;
            for(i = 0;tt[i] != 0;i++)
            {
                printf("user: %d %u\n",i+1,tt[i]);
            }
            tmp = tmp->next;
        }
  }

/**
  * [调试]输出链表中所有用户数据
  *
  */
  void debugPrintAllUsers()
  {
        puFile tmp = uHEAD;
        char *text = NULL;
        while(tmp != NULL)
        {
            puts("***************************");
            printf("g:%u |",tmp->data.groupID);
            pGroup temp = getGroup(1,tmp->data.groupID);
            if(temp == NULL)
            {
                text = "无群组";
            }else{
                text = temp->name;
            }
            printf("%u | %s | %s | %s | %s \n",tmp->data.ID,tmp->data.username,tmp->data.address,tmp->data.telphones[0],text);
            tmp = tmp->next;
        }
  }
#endif // DEBUG
 /**
  * 输出pUSER数组的个数
  * @param pUSER *arr pUSER 组
  * @return int 成员个数
  * @author Hafrans Newton
  */

int sizeofpUSER(pUSER *arr)
{
    return sizeof(arr)/sizeof(pUSER);
}

 /**
  * 输出pGroup数组的个数
  * @param pGroup *arr pGroup 组
  * @return int 成员个数
  * @author Hafrans Newton
  */

int sizeofpGroup(pGroup *arr)
{
    return sizeof(arr)/sizeof(Group);
}



