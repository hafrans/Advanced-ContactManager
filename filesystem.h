/*
    File: filesystem.h
    Description: 文件操作函数库头文件
    Updated: Jul 10 2016
    Author : Hafrans Newton

*/
#include "project.h"
#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

    #ifndef _FILENAME_DEFINE_
    #define _FILENAME_DEFINE_
        #define STORE_USER_MODULE  "./bin/user.dat"
        #define STORE_GROUP_MODULE "./bin/group.dat"
        #define STORE_KEY_MODULE   "./bin/private.key"
        #define STORE_FILE_NAME    "./output."
    #endif // _FILENAME_DEFINE_
    #ifdef __cplusplus
    extern "C" {
    #endif // defined

    /**
     * 存储群组数据链表
     * @author Hafrans Newton
     * @return BOOLEAN True - 成功 False - 失败
     */
    _EXT BOOLEAN storeUSERField();

    /**
     * 存储群组数据链表
     * @author Hafrans Newton
     * @return BOOLEAN True - 成功 False - 失败
     */
    _EXT BOOLEAN storeGROUPField();

    /**
     * 从文件里提取出用户链表
     * @author Hafrans
     * @return BOOLEAN True - 成功 False - 失败
     */
    _EXT BOOLEAN loadUSERField();

    /**
     * 从文件里提取出群组链表
     * @return BOOLEAN True - 成功 False - 失败
     * @author Hafrans
     */
    _EXT BOOLEAN loadGROUPField();

    /**
     * 将用户导出至HTML
     * @return BOOLEAN True - 成功 False - 失败
     * @author Hafrans
     */
    _EXT BOOLEAN outputHTML();

    /**
     * 将用户导出至CSV
     * @return BOOLEAN True - 成功 False - 失败
     * @author Hafrans
     */
    _EXT BOOLEAN outputCSV();

    /**
     * 将用户导出至TXT
     * @return BOOLEAN True - 成功 False - 失败
     * @author Hafrans
     */
    _EXT BOOLEAN outputTXT();

    /**
     * 导入用户密码表
     * @return BOOLEAN True - 成功 False - 失败
     * @author Hafrans Newton
     */
     _EXT BOOLEAN loadKey();

     /**
     * 存储用户密码表
     * @return BOOLEAN True - 成功 False - 失败
     * @author Hafrans Newton
     */
    _EXT BOOLEAN storeKey();

    #ifdef __cplusplus
    }
    #endif // defined

#endif // _FILESYSTEM_H
