/**'/
    File: datastruct.c
    Description: ���ݽṹ����Դ��
    Updated: Jul 10 2016
    Author : Hafrans Newton

*/
#include "datastruct.h"

/**
 *  �԰�ȫ�ķ�ʽ����һ����������Ԫ��
 * @param char *name Ⱥ������
 * @param char *color ���Ի���ɫ
 * @return int ���ִ��󷵻�0 �ɹ����뷵��Ⱥ��ID ����ظ��򷵻�-1
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
 *  �԰�ȫ�ķ�ʽ����һ���û�����Ԫ��
 * @param char *name ��ϵ������
 * @param char *address ��ϵ�˹�����λסַ
 * @param char *homeaddress ��ϵ�˼�ͥסַ
 * @param char *email �����ʼ���ַ
 * @param char *telphone �绰
 * @param uint groupID Ⱥ����
 * @return int  ���ִ��󷵻�0 , �ɹ����� �û�ID ��������ظ��򷵻�-1
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
  * ���һ��Ⱥ���Ƿ����[�߼�]
  * @param int type ���Է�ʽ
  *        type = 1 ��ID����        ����  findGroup(1,20);
  *        type = 2 ��Ⱥ�����Ʋ���  ���� findGroup(2,"����");
  * @return unsigned int ��ѯ�ɹ��󷵻ص�ǰȺ��ID�����򷵻�0
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
 *  ��ȡһ��Ⱥ��ʵ�塾�߼���
  * @param int type ���Է�ʽ
  *        type = 1 ��ID����        ����  getGroup(1,20);
  *        type = 2 ��Ⱥ�����Ʋ���  ����  getGroup(2,"����");
  * @return pGroup �ɹ�����һ�����Բ�����Ⱥ��ʵ�壬���򷵻�һ��NULL
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
   * [�߼�] ͨ��ID��ȡһ���û�ʵ��
   * @param int type ��ȡ��ʽ
   *        type = 1 ͨ��ID��ʽ��ȡ�û�ʵ��
   *        type = 2 ͨ����ϵ��������ʽ��ȡΨһ�û�ʵ��
   * @return pUSER �û�ʵ�塾�ṹ��ָ�롿
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
  * ���涨���û�ʵ�����һ��Ⱥ��
  * @param pUSER obj �û�ʵ��
  * @param unsigned int groupID
  * @return int ����״̬ 0 ʧ�� 1 �ɹ�  -1 Ⱥ����������

  PS: �ú������û�����Ⱥ�飬
  ���GroupID����Ϊ0���û��������κ�Ⱥ��

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
        addUSERToGroup(obj,0);//�������
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
 *  �԰�ȫ�ķ�ʽ�޸�һ���û�����Ԫ��
 * @param char *name ��ϵ������
 * @param char *address ��ϵ�˹�����λסַ
 * @param char *homeaddress ��ϵ�˼�ͥסַ
 * @param char *email �����ʼ���ַ
 * @param char *telphone ��Ҫ�绰
 * @param uint groupID Ⱥ����
 * @return int  ���ִ��󷵻�0 , �ɹ����� 1
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
 *  ���߼����޸�һ����������Ԫ��
 * @param pGroup obj ��ȡ��Ⱥ��ʵ��
 * @param char *name Ⱥ������
 * @param char *color ���Ի���ɫ
 * @return BOOLEAN True ��ȷ False ����
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
 * ���߼���ͨ��ID �� ��ϵ������ ɾ���û�����
 * @param int type ����
 *            type = 1 ����IDɾ��
 *            type = 2 ������ϵ������ɾ��
 * @param mixed ����
 * @return BOOLEAN True - �ɹ� False - ʧ��
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
 * ���߼���ͨ��ID �� Ⱥ������ ɾ��Ⱥ������
 * @param int type ����
 *            type = 1 ����IDɾ��
 *            type = 2 ����Ⱥ������ɾ��
 * @param mixed ����
 * @return BOOLEAN True - �ɹ� False - ʧ��
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
 * �޸��û�����ϵ��ʽ�绰����
 * @param pUSER obj �û�ʵ��
 * @param int type �޸ķ�ʽ
 *            type = 0 ���   changeUserTel(obj,0,"13800138000");
 *            type = 1 �޸�   changeUserTel(obj,1,"13800138000","13863350001");
 *            type = 2 ɾ��   changeUserTel(obj,2,"13800000000");
 * @param mixed ����
 * @return  1 ��ӳɹ�
 *          0 ���ʧ��
 *         -1 �û�����������ֻ�����
 *         -2 ��ѯ����Ҫ�޸ĵĺ���
 *         -3 ɾ��ʱ��ѯ����Ҫɾ�����ֻ�����
 *         -4 ������û��ṹ��ָ�����
 *         -5 ��ӵ�ʱ�������ظ�
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
 * ͨ������pUserָ������û�������������
 * @author Hafrans
 * @date 07/09/2016
 * @param pUSER data ������û�������
 * @return BOOLEAN True �ɹ� False ʧ��
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
 * ɾ�������û����ݲ������û�����Ϊ��
 * @author Hafrans
 * @date   July 10 2016
 * @return BOOLEAN True �ɹ� False ʧ��
 */
 BOOLEAN removeAllUserAndSetuHEADNULL(){
    if(uHEAD == NULL)
        return True;
    puFile tmp = uHEAD; //���Ƹ�ѭ������
         uHEAD = NULL;  //����ͷ���
    while(tmp != NULL)  //��ʼ����
    {
         puFile trash = tmp;
         tmp = tmp->next;
         free(trash);   //��������
    }
    return True;
 }

 /**
 * ͨ������pGroupָ������û�������������
 * @author Hafrans
 * @date 07/10/2016
 * @param pGroup data ������û�������
 * @return BOOLEAN True �ɹ� False ʧ��
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
 * ɾ������Ⱥ�����ݲ�����Ⱥ������Ϊ��
 * @author Hafrans
 * @date   July 11 2016
 * @return BOOLEAN True �ɹ� False ʧ��
 */
 BOOLEAN removeAllGroupAndSetgHEADNULL(){
    if(gHEAD == NULL)
        return True;
    pgFile tmp = gHEAD; //���Ƹ�ѭ������
         gHEAD = NULL;  //����ͷ���
    while(tmp != NULL)  //��ʼ����
    {
         pgFile trash = tmp;
         tmp = tmp->next;
         free(trash);   //��������
    }
    return True;
 }
/**
 * ����IDɾ���û������е�Ԫ�ء��ײ㡿
 * @author Hafrans
 * @date July 11 2016
 * @param unsigned int ID ��Ҫɾ����ID
 * @return BOOLEAN True �ɹ��� False ʧ��
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
  * ���ײ㡿ͨ��ID��ȡȺ��ʵ��
  * @param unsigned int ID ID
  * @return pGroup Ⱥ��ʵ�壬���û�м�⵽�򷵻�0
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
  * ���ײ㡿ͨ�����ƻ�ȡȺ��ʵ��
  * @param char *text Ⱥ������
  * @return pGroup Ⱥ��ʵ�壬���û�м�⵽�򷵻�0(NULL)
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
 * ͨ��ID��ȡ�û�ʵ�塾�ײ㡿
 * @param unsigned int ID Ҫ���ҵ��û�ID
 * @return pUSER �û�ʵ�壬���û�м�⵽�򷵻�0(NULL)
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
 * ͨ����ȷ�û�����ȡ�û�ʵ�塾�ײ㡿
 * @param unsigned int ID Ҫ���ҵ��û�ID
 * @return pUSER �û�ʵ�壬���û�м�⵽�򷵻�0(NULL)
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
 * ͨ��ģ���û�����ȡ�û�ʵ�塾�ײ㡿
 * @param  char *text �����ֶ�
 * @return pUSER *�û�ʵ���飬���û�м�⵽�򷵻�data[0] = (NULL)
 * @author Hafrans Newton
 */
 pUSER *getUSERByUsingUSERName(char *text)
 {
    int count = 1; //�ڴ����
    size_t pUSERSize  = sizeof(pUSER);//�����ڴ�ָ���С
    pUSER *data = (pUSER *)malloc(pUSERSize*count); //����ڴ��������ڴ�
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
            data = (pUSER *)realloc(data,pUSERSize*(++count)); //����ڴ��������ڴ�
        }
        tmp = tmp->next;
    }
    data[count-1] = 0;
    return data;
 }

 /**
 * ͨ��ģ��������Ϣ��ȡ�û�ʵ�塾�ײ㡿
 * @param char *text �����ֶ�   0Ϊ����ȫ��
 * @return pUSER *�û�ʵ���飬���û�м�⵽�򷵻�data[0] = (NULL)
 * @author Hafrans Newton
 */
 pUSER *getUSERByUsingAll(char *text)
 {
    int count = 1; //�ڴ����
    size_t pUSERSize  = sizeof(pUSER);//�����ڴ�ָ���С
    pUSER *data = (pUSER *)malloc(pUSERSize*count); //����ڴ��������ڴ�
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
            data = (pUSER *)realloc(data,pUSERSize*(++count)); //����ڴ��������ڴ�
        }
        tmp = tmp->next;
    }
    data[count-1] = 0;
    return data;
 }

/**
 * ����IDɾ��Ⱥ�������е�Ԫ�ء��ײ㡿
 * @author Hafrans
 * @date July 11 2016
 * @param unsigned int ID ��Ҫɾ����ID
 * @return BOOLEAN True �ɹ��� False ʧ��
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
 * [�ײ�] ��ȡ����Ⱥ��ID
 * @return unsigned int * ������0Ϊ��β
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
    //��ʱ�������ڴ�й©
    return data;
}

/**
 * [�ײ�] ��ȡ�����û�ID
 * @author Hafrans Newton
 * @return unsigned int * ������0Ϊ��β
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
    //��ʱ�������ڴ�й©
    return data;
}

#ifdef DEBUG

 /**
  * [����]�������������Ⱥ������
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
  * [����]��������������û�����
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
                text = "��Ⱥ��";
            }else{
                text = temp->name;
            }
            printf("%u | %s | %s | %s | %s \n",tmp->data.ID,tmp->data.username,tmp->data.address,tmp->data.telphones[0],text);
            tmp = tmp->next;
        }
  }
#endif // DEBUG
 /**
  * ���pUSER����ĸ���
  * @param pUSER *arr pUSER ��
  * @return int ��Ա����
  * @author Hafrans Newton
  */

int sizeofpUSER(pUSER *arr)
{
    return sizeof(arr)/sizeof(pUSER);
}

 /**
  * ���pGroup����ĸ���
  * @param pGroup *arr pGroup ��
  * @return int ��Ա����
  * @author Hafrans Newton
  */

int sizeofpGroup(pGroup *arr)
{
    return sizeof(arr)/sizeof(Group);
}



