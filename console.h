/*
    File: console.h
    Description: 控制台操作头文件
    Updated: Jul 10 2016
    Author : wx

*/

#include "project.h"
#ifndef _CONSOLE_H
#define _CONSOLE_H

    #ifdef __cplusplus
    extern "C" {
    #endif // defined

    /**
     * 主菜单界面
     */
    _EXT void menuMain();

    /**
     * 退出界面
     */
    _EXT void menuExit();

    /**
     * 清空屏幕
     */
    _EXT void clear();


    /**
      * 根据用户ID显示一个联系人信息界面
      * @param unsigned int ID 用户ID
      * @author wx
      * @date 2016 07 12
      */
    _EXT void menuShowDetailsByID(unsigned int ID);

    /**
      * 根据用户实体显示一个联系人信息界面
      * @param pUSER obj 用户实体
      * @author wx
      * @date 2016 07 12
      */
    _EXT void menuShowDetailsBypUSER(pUSER obj);

    /**
     *  根据信息显示一个临时用户名（用于添加或修改之前确认）界面
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
    _EXT void menuShowDetailsByDetails(char        *name,
                                       char        *address,
                                       char        *homeaddress,
                                       char        *email,
                                       char        *telphone,
                                       unsigned int groupID
                                       );



    /**
     *  通过unsigned int 数组显示用户列表
     *  @param unsigned int ID[] 用户数组
     *  @author wx & hafrans
     **/
    _EXT void menuShowUserList(unsigned int ID[]);

    /**
     *  通过unsigned int 数组显示群组列表
     *  @param unsigned int ID[] 群组ID数组
     *  @author wx & hafrans
     **/
     _EXT void menuShowGroupList(unsigned int ID[]);

    /**
      * 通过ID显示群组详情
      * @param unsigned int ID 群组ID
      */
    _EXT void menuShowGroupByID(unsigned int ID);

    /**
     * 导出菜单选项
     */
    _EXT void menuOutputLayout();

    /**
     * 密码登陆项
     */
    _EXT void menuKeySecret();

    /**
     * 密码错误提示
     */
    _EXT void menuErrorKey();
    /**
       登陆提示
     */
    _EXT void menuLogin(int type);


    #ifdef __cplusplus
    }
    #endif // defined


#endif // _CORE_H
