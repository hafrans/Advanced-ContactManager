/*
    File: filesystem.h
    Description: �ļ�����������ͷ�ļ�
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
     * �洢Ⱥ����������
     * @author Hafrans Newton
     * @return BOOLEAN True - �ɹ� False - ʧ��
     */
    _EXT BOOLEAN storeUSERField();

    /**
     * �洢Ⱥ����������
     * @author Hafrans Newton
     * @return BOOLEAN True - �ɹ� False - ʧ��
     */
    _EXT BOOLEAN storeGROUPField();

    /**
     * ���ļ�����ȡ���û�����
     * @author Hafrans
     * @return BOOLEAN True - �ɹ� False - ʧ��
     */
    _EXT BOOLEAN loadUSERField();

    /**
     * ���ļ�����ȡ��Ⱥ������
     * @return BOOLEAN True - �ɹ� False - ʧ��
     * @author Hafrans
     */
    _EXT BOOLEAN loadGROUPField();

    /**
     * ���û�������HTML
     * @return BOOLEAN True - �ɹ� False - ʧ��
     * @author Hafrans
     */
    _EXT BOOLEAN outputHTML();

    /**
     * ���û�������CSV
     * @return BOOLEAN True - �ɹ� False - ʧ��
     * @author Hafrans
     */
    _EXT BOOLEAN outputCSV();

    /**
     * ���û�������TXT
     * @return BOOLEAN True - �ɹ� False - ʧ��
     * @author Hafrans
     */
    _EXT BOOLEAN outputTXT();

    /**
     * �����û������
     * @return BOOLEAN True - �ɹ� False - ʧ��
     * @author Hafrans Newton
     */
     _EXT BOOLEAN loadKey();

     /**
     * �洢�û������
     * @return BOOLEAN True - �ɹ� False - ʧ��
     * @author Hafrans Newton
     */
    _EXT BOOLEAN storeKey();

    #ifdef __cplusplus
    }
    #endif // defined

#endif // _FILESYSTEM_H
