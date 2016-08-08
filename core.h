/**
    File: core.h
    Description: 程序核心文件
    Updated: Jul 10 2016
    Author : lxj

*/

#include "project.h"

#ifndef _CORE_H
#define _CORE_H

    #ifdef __cplusplus
    extern "C" {
    #endif // defined
    /**
    *   程序初始化
    */
    _EXT void init();

    /**
     * 程序退出操作
     */
    _EXT void Exit();

    /**
     *  添加联系人
     */
    _EXT void coreAddNewContact();

    /**
     * 搜索并操作联系人
     *
     */
     _EXT void coreSearchContact();

    /**
     * 删除联系人
     */
    _EXT void coreDeleteContact(pUSER obj);

    /**
     * 修改联系人
     */
     _EXT void coreChangeContact(pUSER obj);
    /**
     * 添加新群组
     */
     _EXT void coreAddNewGroup();
     /**
      * 查询群组
      */
     _EXT void coreSearchGroup();

    /**
     * 修改群组
     */
     _EXT void coreChangeGroup(pGroup obj);

     /**
     * 群组删除
     */
     _EXT void coreDeleteGroup(pGroup obj);

     /**
       * 主页菜单
       */
     _EXT void coreMenuInit();

     /**
     * 导出链表到文件
     * @param int type
     *            type = 1 csv  导出
     *            type = 2 html 导出
     *            type = 3 text 导出
     */
     _EXT void coreStoreToFile(int type);

    /**
     * 密码逻辑
     */
     _EXT void coreKeySecret();
    /**
     * 密码登陆
     */
     _EXT void coreKeyCheck();

    #ifdef __cplusplus
    }
    #endif // defined


#endif // _CORE_H
