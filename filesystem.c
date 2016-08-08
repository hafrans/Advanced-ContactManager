/*
    File: filesystem.c
    Description: 文件操作函数库源码
    Updated: Jul 10 2016
    Author : Hafrans Newton

*/
#include "project.h"

/**
 * 存储用户数据链表
 * @return BOOLEAN True - 成功 False - 失败
 * @author Hafrans Newton
 */
BOOLEAN storeUSERField()
{
    FILE *handle = NULL;
    handle = fopen(STORE_USER_MODULE,"wb");
    if(handle == NULL)
        return False;
    puFile tmp = uHEAD;
    while(tmp != NULL)
    {
        fwrite(&tmp->data,sizeof(USER),1,handle);
        tmp = tmp->next;
    }
    fclose(handle);
    return True;
}

/**
 * 存储群组数据链表
 * @author Hafrans Newton
 * @return BOOLEAN True - 成功 False - 失败
 */
BOOLEAN storeGROUPField()
{
    FILE *handle = NULL;
    handle = fopen(STORE_GROUP_MODULE,"wb");
    if(handle == NULL)
        return False;
    pgFile tmp = gHEAD;
    while(tmp != NULL)
    {
        fwrite(&tmp->data,sizeof(Group),1,handle);
        tmp = tmp->next;
    }
    fclose(handle);
    return True;
}

/**
 * 从文件里提取出用户链表
 * @return BOOLEAN True - 成功 False - 失败
 * @author Hafrans
 */
BOOLEAN loadUSERField()
{
    FILE *handle = NULL;
    handle = fopen(STORE_USER_MODULE,"rb");
    if(handle == NULL)
        return False;
    while(True){
        pUSER tmp = (pUSER)calloc(1,sizeof(USER));

        if(!fread(tmp,sizeof(USER),1,handle))
            break;
        if(tmp->ID > maxRegistedUSERID)
            maxRegistedUSERID = tmp->ID;
        addUSERByInsertpUSERDATA(tmp);
    }
    fclose(handle);

    return True;

}

/**
 * 从文件里提取出群组链表
 * @return BOOLEAN True - 成功 False - 失败
 * @author Hafrans
 */
BOOLEAN loadGROUPField()
{
    FILE *handle = NULL;
    handle = fopen(STORE_GROUP_MODULE,"rb");
    if(handle == NULL)
        return False;
    while(True){
        pGroup tmp = (pGroup)calloc(1,sizeof(Group));

        if(!fread(tmp,sizeof(Group),1,handle))
            break;
        if(tmp->ID > maxRegistedGROUPID)
            maxRegistedGROUPID = tmp->ID;
        addGroupByInsertpGroupDATA(tmp);
    }
    fclose(handle);

    return True;

}

/**
 * 存储用户密码表
 * @return BOOLEAN True - 成功 False - 失败
 * @author Hafrans Newton
 */
BOOLEAN storeKey()
{
    FILE *handle = fopen(STORE_KEY_MODULE,"wb+");
    if(handle == NULL)
    {
        return False;
    }
    if(key != NULL)
    {
        fwrite(key,sizeof(Key),1,handle);
    }else{
        fclose(handle);
        return False;
    }
    fclose(handle);
    return True;
}
 /**
 * 导入用户密码表
 * @return BOOLEAN True - 成功 False - 失败
 * @author Hafrans Newton
 */
 BOOLEAN loadKey()
 {
   FILE *handle = fopen(STORE_KEY_MODULE,"rb+");
   if(handle == NULL)
        return False;
   if(key == NULL)
   {
        key = (pKey)malloc(sizeof(Key));
        if(!fread(key,sizeof(Key),1,handle))
        {
            free(key);
            key = NULL;
        }

   }else{
      fclose(handle);
      return False;
   }
   return True;
 }


/**
 * 将用户导出至HTML
 * @return BOOLEAN True - 成功 False - 失败
 * @author Hafrans
 */
BOOLEAN outputHTML()
{
    char *filename = "./output.html";
    pGroup tmpl = NULL;
    char *text = NULL;
    FILE *handle = fopen(filename,"w+");
    if(handle == NULL)
        return False;
    fprintf(handle,"<!DOCTYPE HTML>\n<!-- Generated By Hafrans dramas Engine -->\n<html>\n<body>\n<table border=\"2\">\n");
    fprintf(handle,"<caption>通讯录</caption>\n");
    fprintf(handle,"<tr><th> %-4s </th><th> %-10s </th><th> %s </th>\
<th> %s </th><th> %s </th><th> %s </th><th> %-8s </th></tr>\n","序号",
                                                               "姓名",
                                                               "工作单位",
                                                               "家庭住址",
                                                               "电子信箱",
                                                               "联系电话",
                                                               "所属群组");

    puFile tmp = uHEAD;
    while(tmp != NULL)
    {
        tmpl = getGroup(1,tmp->data.ID);
        if(tmpl == NULL)
        {
            text = "无群组";
        }else{
            text = tmpl->name;
        }
        fprintf(handle,"<tr><td> %u </td><td> %s </td><td> %s </td>\
<td> %s </td><td> %s </td><td> %s </td><td> %-12s </td></tr>\n",
                                                                tmp->data.ID,
                                                                tmp->data.username,
                                                                tmp->data.address,
                                                                tmp->data.homeaddress,
                                                                tmp->data.email,
                                                                tmp->data.telphones[0],
                                                                text
                                                                );
        tmp = tmp->next;
    }

    fprintf(handle,"</table></body></html>\n");
    fclose(handle);
    return True;
}

/**
 * 将用户导出至CSV
 * @return BOOLEAN True - 成功 False - 失败
 * @author Hafrans
 */
BOOLEAN outputCSV()
{
    char *filename = "./output.csv";
    pGroup tmpl = NULL;
    char *text = NULL;
    FILE *handle = fopen(filename,"w+");
    if(handle == NULL)
        return False;
    fprintf(handle,"通讯录\n %-6s , %-18s , %-35s , %-35s , %-35s , %-20s , %-12s \n","序号",
                                                                                      "姓名",
                                                                                      "工作单位",
                                                                                      "家庭住址",
                                                                                      "电子信箱",
                                                                                      "联系电话",
                                                                                      "所属群组");
    puFile tmp = uHEAD;
    while(tmp != NULL)
    {
        tmpl = getGroup(1,tmp->data.ID);
        if(tmpl == NULL)
        {
            text = "无群组";
        }else{
            text = tmpl->name;
        }
        fprintf(handle," %-6u , %-18s , %-35s , %-35s , %-35s , %-20s , %-12s \n",
                                                                                  tmp->data.ID,
                                                                                  tmp->data.username,
                                                                                  tmp->data.address,
                                                                                  tmp->data.homeaddress,
                                                                                  tmp->data.email,
                                                                                  tmp->data.telphones[0],
                                                                                  text
                                                                                  );
        tmp = tmp->next;
    }
    fclose(handle);
    return True;
}
/**
 * 将用户导出至TXT
 * @return BOOLEAN True - 成功 False - 失败
 * @author Hafrans
 */
BOOLEAN outputTXT()
{
    char *filename = "./output.txt";
    FILE *handle = fopen(filename,"w+");
    pGroup tmpl = NULL;
    char *text = NULL;
    if(handle == NULL)
        return False;
    fprintf(handle,"\t\t\t\t\t通讯录\n┌──────┬────────────┬──────────────────────────┬──────────────────\
────────┬──────────────────────────────┬─────────────┬──────────┐\n");
    fprintf(handle,"│ %-4s │ %-10s │ %-24s │ %-24s │ %-28s │ %-11s │ %-8s │\n","序号",
                                                                                      "姓名",
                                                                                      "工作单位",
                                                                                      "家庭住址",
                                                                                      "电子信箱",
                                                                                      "联系电话",
                                                                                      "所属群组");
    puFile tmp = uHEAD;
    while(tmp != NULL)
    {
        fprintf(handle,"├──────┼────────────┼──────────────────────────┼────────────\
──────────────┼──────────────────────────────┼─────────────┼──────────┤\n");
        tmpl = getGroup(1,tmp->data.ID);
        if(tmpl == NULL)
        {
            text = "无群组";
        }else{
            text = tmpl->name;
        }
        fprintf(handle,"│ %-4u │ %-10s │ %-24s │ %-24s │ %-28s │ %-11s │ %-8s │\n",
                                                                                  tmp->data.ID,
                                                                                  tmp->data.username,
                                                                                  tmp->data.address,
                                                                                  tmp->data.homeaddress,
                                                                                  tmp->data.email,
                                                                                  tmp->data.telphones[0],
                                                                                  text
                                                                                  );
        tmp = tmp->next;
    }
    fprintf(handle,"└──────┴────────────┴──────────────────────────┴──────────\
────────────────┴──────────────────────────────┴─────────────┴──────────┘");

    fclose(handle);
    return True;
}






