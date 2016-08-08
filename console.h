/*
    File: console.h
    Description: ����̨����ͷ�ļ�
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
     * ���˵�����
     */
    _EXT void menuMain();

    /**
     * �˳�����
     */
    _EXT void menuExit();

    /**
     * �����Ļ
     */
    _EXT void clear();


    /**
      * �����û�ID��ʾһ����ϵ����Ϣ����
      * @param unsigned int ID �û�ID
      * @author wx
      * @date 2016 07 12
      */
    _EXT void menuShowDetailsByID(unsigned int ID);

    /**
      * �����û�ʵ����ʾһ����ϵ����Ϣ����
      * @param pUSER obj �û�ʵ��
      * @author wx
      * @date 2016 07 12
      */
    _EXT void menuShowDetailsBypUSER(pUSER obj);

    /**
     *  ������Ϣ��ʾһ����ʱ�û�����������ӻ��޸�֮ǰȷ�ϣ�����
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
    _EXT void menuShowDetailsByDetails(char        *name,
                                       char        *address,
                                       char        *homeaddress,
                                       char        *email,
                                       char        *telphone,
                                       unsigned int groupID
                                       );



    /**
     *  ͨ��unsigned int ������ʾ�û��б�
     *  @param unsigned int ID[] �û�����
     *  @author wx & hafrans
     **/
    _EXT void menuShowUserList(unsigned int ID[]);

    /**
     *  ͨ��unsigned int ������ʾȺ���б�
     *  @param unsigned int ID[] Ⱥ��ID����
     *  @author wx & hafrans
     **/
     _EXT void menuShowGroupList(unsigned int ID[]);

    /**
      * ͨ��ID��ʾȺ������
      * @param unsigned int ID Ⱥ��ID
      */
    _EXT void menuShowGroupByID(unsigned int ID);

    /**
     * �����˵�ѡ��
     */
    _EXT void menuOutputLayout();

    /**
     * �����½��
     */
    _EXT void menuKeySecret();

    /**
     * ���������ʾ
     */
    _EXT void menuErrorKey();
    /**
       ��½��ʾ
     */
    _EXT void menuLogin(int type);


    #ifdef __cplusplus
    }
    #endif // defined


#endif // _CORE_H
