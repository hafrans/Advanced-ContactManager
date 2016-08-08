/*
    File: datastruct.h
    Description: 数据结构定义头文件
    Updated: Jul 10 2016
*/

#include "project.h"

#ifndef _DATASTRUCT_H
#define _DATASTRUCT_H
    #ifndef _DATASTRUCT_DEFINE
    #define _DATASTRUCT_DEFINE
    #endif // _DATASTRUCT_DEFINE
//    #define STORE  GROUP
//    #define pSTORE pGROUP
    #ifndef BOOLEAN
        #define BOOLEAN int
        #define True    1
        #define False   0
    #endif // BOOLEAN

    /**
        群组结构类型
    */
    typedef struct group_field{
        unsigned int ID;            //群组的ID
        char         name[BUFFSIZE];//群组的名称
        unsigned int USERID[128];  //本群组所含的人员ID
        char         Color[5];      //本群组设置的高亮颜色
    } Group ,*pGroup;
    /**
        群组存储类型
    */
    typedef struct linked{
        Group data;
        struct linked *next;
    } gFile,*pgFile;

    /**
        用户数据类型
    */
    typedef struct user_field{
        unsigned int    ID;                //用户ID
        char            username[BUFFSIZE];//用户名
        char            address[BUFFSIZE]; //地址
        char            homeaddress[BUFFSIZE];//工作单位住址
        char            email[BUFFSIZE];   //唯一电子邮件
        char            telphones[8][20];  //电话号码
        unsigned int    groupID;           //所归属的群组
    } USER,*pUSER;
    /**
        用户存储类型
    */
    typedef struct linked_user{
        USER data;
        struct linked_user *next;
    } uFile,*puFile;
    /**
     * 密钥链
     */
    typedef struct systemKey{
        int status;
        char key[BUFFSIZE];
    } Key,*pKey;
    //数据声明
    _EXT unsigned int maxRegistedUSERID;    //当前已注册的用户最大ID
    _EXT unsigned int maxRegistedGROUPID;   //当前已注册的群组最大ID
    _EXT pgFile gHEAD;          //群组链表表头
    _EXT puFile uHEAD;          //用户链表表头
    _EXT pKey   key;            //用户锁


    #ifdef __cplusplus
    extern "C" {
    #endif // defined

    /*********************************************************

        底层函数仅供核心层使用，请谨慎使用
                PS：高级函数更简单，更安全

    *********************************************************/

    /**
     * 通过模糊所有信息获取用户实体【底层】
     * @param char *text 查找字段   0为查找全部
     * @return pUSER *用户实体组，如果没有检测到则返回data[0] = (NULL)
     * @author Hafrans Newton

                        PS pUSER 指针用法在下面
     */
     _EXT pUSER *getUSERByUsingAll(char *text);

    /**
     * 通过精确用户名获取用户实体【底层】
     * @param unsigned int ID 要查找的用户ID
     * @return pUSER 用户实体，如果没有检测到则返回0(NULL)
     * @author Hafrans Newton
     */
    _EXT pUSER getAUSERByUsingUSERNameOnce(char *text);

    /**
     * 通过ID获取用户实体【底层】
     * @param unsigned int ID 要查找的用户ID
     * @return pUSER 用户实体，如果没有检测到则返回0(NULL)
     * @author Hafrans Newton
     */
    _EXT pUSER getUSERByUsingUSERID(unsigned int ID);

    /**
     * 通过模糊用户名获取用户实体【底层】
     * @param unsigned int ID 要查找的用户ID
     * @return pUSER 用户实体，如果没有检测到则返回0(NULL)
     * @author Hafrans Newton
     *

     PS:
        pUSER * 使用的方法如下：
            pUSER是一个数组但是无法正常检测其数组长度
            函数内置数组结束符为NULL
            你可以按照以下方法遍历整组变量
            pUSER *tmp = getUSERByUsingUSERName("Lari");
            int i = 0;
            for(i = 0; tmp[i] != NULL ; ++i)
            {
                //do something interesting.
            }

     **/
     _EXT pUSER *getUSERByUsingUSERName(char *text);

     /**
      * 【底层】通过ID获取群组实体
      * @param unsigned int ID ID
      * @return pGroup 群组实体，如果没有检测到则返回0
      * @author Hafrans Newton
      */
     _EXT pGroup getGroupByUsingGroupID(unsigned int ID);

    /**
      * 【底层】通过名称获取群组实体
      * @param char *text 群组名称
      * @return pGroup 群组实体，如果没有检测到则返回0(NULL)
      * @author Hafrans Newton
      */
      _EXT pGroup getGroupByUsingGroupName(char *text);

    /**
     * 通过生成pUser指针插入用户数据链表[底层]
     * @author Hafrans
     * @date 07/09/2016
     * @param pUSER data 插入的用户数据体
     * @return BOOLEAN True 成功 False 失败
     */
    _EXT BOOLEAN addUSERByInsertpUSERDATA(pUSER data);

    /**
     * 删除所有用户数据并设置用户链表为空[底层]
     * @author Hafrans
     * @date 07/09/2016
     * @return BOOLEAN True 成功 False 失败
     */
    _EXT BOOLEAN removeAllUserAndSetuHEADNULL();

     /**
      * 通过生成pGroup指针插入用户数据升序链表[底层]
      * @author Hafrans
      * @date 07/10/2016
      * @param pGroup data 插入的用户数据体
      * @return BOOLEAN True 成功 False 失败
      */
    _EXT BOOLEAN addGroupByInsertpGroupDATA(pGroup data);

    /**
     * 删除所有群组数据并设置群组链表为空【底层】
     * @author Hafrans
     * @date   July 10 2016
     * @return BOOLEAN True 成功 False 失败
     */
    _EXT BOOLEAN removeAllGroupAndSetgHEADNULL();

    /**
     * 根据ID删除用户链表中的元素【底层】
     * @author Hafrans
     * @date July 11 2016
     * @param unsigned int ID 将要删除的ID
     * @return BOOLEAN True 成功， False 失败
     */
     _EXT BOOLEAN removeUSERByUsingUSERID(unsigned int ID);

    /**
     * 根据ID删除群组链表中的元素【底层】
     * @author Hafrans
     * @date July 11 2016
     * @param unsigned int ID 将要删除的ID
     * @return BOOLEAN True 成功， False 失败
     */
     _EXT BOOLEAN removeGroupByUsingGroupID(unsigned int ID);

    /**
     * [底层] 获取所有群组ID
     * @return unsigned int * 数组以0为结尾
     * @author Hafrans Newton
     */
    _EXT unsigned int *getAllGroupID();

    /**
     * [底层] 获取所有用户ID
     * @author Hafrans Newton
     * @return unsigned int * 数组以0为结尾
     */
    _EXT unsigned int *getAllUSERID();



     /*********************************************************

                        高级层函数
                        安全更好用

    *********************************************************/
    /**
     *  以安全的方式加入一个数组链表元素
     * @param char *name 群组名称
     * @param char *color 个性化颜色
     * @return int 出现错误返回0 成功插入返回群组ID 如果重复，则返回-1
     *
     */
     _EXT int addGroup(char *name,char *color);


    /**
     *  以安全的方式加入一个用户链表元素
     * @param char *name 联系人姓名
     * @param char *address 联系人工作单位住址
     * @param char *homeaddress 联系人家庭住址
     * @param char *email 电子邮件地址
     * @param char *telphone 电话
     * @param uint groupID 群组名
     * @return int  出现错误返回0 , 成功返回 用户ID 如果重复则返回-1;
     *
     */
     _EXT int addUser(char        *name,
                      char        *address,
                      char        *homeaddress,
                      char        *email,
                      char        *telphone,
                      unsigned int groupID
                      );

    /**
     *  以安全的方式修改一个用户链表元素
     * @param pUSER obj 传入的用户实体
     * @param char *name 联系人姓名
     * @param char *address 联系人工作单位住址
     * @param char *homeaddress 联系人家庭住址
     * @param char *email 电子邮件地址
     * @param char *telphone 主要电话
     * @param uint  groupID 群组名
     * @return int  出现错误返回0 , 成功返回 1
     *
     */
     _EXT BOOLEAN modifyUser(pUSER         obj,
                             char         *name,
                             char         *address,
                             char         *homeaddress,
                             char         *email,
                             char         *telphone,
                             unsigned int  groupID
                            );
    /**
     *  【高级】修改一个数组链表元素
     * @param pGroup obj 获取的群组实体
     * @param char *name 群组名称
     * @param char *color 个性化颜色
     * @return BOOLEAN True 正确 False 错误
     *
     */
     _EXT int modifyGroup(pGroup obj,
                          char  *name,
                          char  *color);

    /**
      * 检测一个群组是否存在[高级]
      * @param int type 测试方式
      *        type = 1 用ID测试        例如  findGroup(1,20);
      *        type = 2 用群组名称测试  例如 findGroup(2,"亲友");
      * @return unsigned int 查询成功后返回当前群组ID，否则返回0
      * @author Hafrans Newton
      */
      _EXT int findGroup(int type,...);

     /**
      *  获取一个群组实体【高级】
      * @param int type 测试方式
      *        type = 1 用ID测试        例如  getGroup(1,20);
      *        type = 2 用群组名称测试  例如  getGroup(2,"亲友");
      * @return pGroup 成功返回一个可以操作的群组实体，负责返回一个NULL
      * @author Hafrans Newton
      */
      _EXT pGroup getGroup(int type,...);


     /**
       * [高级] 通过ID获取一个用户实体
       * @param int type 获取方式
       *        type = 1 通过ID形式获取用户实体
       *        type = 2 通过联系人姓名方式获取唯一用户实体
       * @return pUSER 用户实体【结构体指针】否则返回0（NULL）
       * @author Hafrans Newton
       */
      _EXT pUSER getAUSER(int type,...);

    /**
      * 将规定的用户实体加入一个群组
      * @param pUSER obj 用户实体
      * @param unsigned int groupID
      * @return int 返回状态 0 失败 1 成功  -1 群组人数过多

      PS: 该函数给用户设置群组，
      如果GroupID设置为0则用户不属于任何群组

      */
     _EXT int addUSERToGroup(pUSER obj,unsigned int groupID);

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
    _EXT BOOLEAN removeUser(int type,...);

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
    _EXT BOOLEAN removeGroup(int type,...);

    /**
     * 修改用户的联系方式电话号码[高级]
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
     int changeUserTel(pUSER obj,int type,...);







    #ifdef DEBUG

    /*********************************************************

        调试用

    *********************************************************/

     /**
      * [调试]输出链表中所有群组数据
      *
      */
      void debugPrintAllGroups();

    /**
      * [调试]输出链表中所有用户数据
      *
      */
      void debugPrintAllUsers();

     #endif // DEBUG

     /*****************************************************

                工具函数

     ******************************************************/
    /**
      * 输出pGroup数组的个数
      * @param pGroup *arr pGroup 组
      * @return int 成员个数
      * @author Hafrans Newton
      */

    _EXT int sizeofpGroup(pGroup *arr);

     /**
      * 输出pUSER数组的个数
      * @param pUSER *arr pUSER 组
      * @return int 成员个数
      * @author Hafrans Newton
      */

    _EXT int sizeofpUSER(pUSER *arr);





    #ifdef __cplusplus
    }
    #endif // defined




#endif // _DATASTRUCT_H
