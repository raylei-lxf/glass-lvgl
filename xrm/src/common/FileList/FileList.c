/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system
*
* File		:	FileList
*                 ��������ṹ��Ϊ�����һ��ʼ�����ļ����ٶ�.
* By		:	Libaiao
* Func	:
* Version	:	v1.0
* ============================================================================================================
* 2010-6-5	15:24:52  Libaiao  create this file, implements the fundemental interface;
**************************************************************************************************************
*/
#include <stdlib.h>
#include <string.h>
#include "FileList.h"
//�ݹ麯���е��ã����ں����еĻ����������ջ���
//char            fullpath[RAT_MAX_FULL_PATH_LEN];
/*
************************************************************************************************************************
*Function	:
*
*Description	:
*
*Arguments	:
*
*Return		:
*
************************************************************************************************************************
*/
//�������������ļ���Ϣ, �½�һ���ļ���Ŀ,�洢�ļ����ļ�����ص���Ϣ
file_item_t* new_file_item(struct dirent   *pDirent)
{
	file_item_t *file_item = NULL;

	if (pDirent == NULL)
	{
		goto end;
	}

	file_item = (file_item_t *)malloc(sizeof(file_item_t));
	if(file_item  == NULL)
	{
		printf("memory is not enough for new a file list\n");
		goto end;
	}
	memset(file_item, 0, sizeof(file_item_t));

	file_item->name_len = strlen(pDirent->d_name);
	if (file_item->name_len != 0)
	{
		file_item->name_len += 5;		//�������һ��byte
		file_item->name = (char*)malloc(file_item->name_len);
		if (file_item->name == NULL) {
			printf("%s %d %s malloc fail\n", __FILE__, __LINE__, __func__);
			goto end;
		}
		memset(file_item->name, 0, file_item->name_len);
//		printf("%s %d %s pDirent->d_name:%s\n", __FILE__, __LINE__, __func__, pDirent->d_name);
		strcpy(file_item->name, pDirent->d_name);
	}

//	printf("%s %d %s pDirent->d_type:%d\n", __FILE__, __LINE__, __func__, pDirent->d_type);
	file_item->fatdirattr = pDirent->d_type;
	return file_item;

	end:
		if(file_item) {
			if(file_item->name) {
				free(file_item->name);
			}
			free(file_item);
		}

		return NULL;
}

//ɾ��һ���ļ���Ŀ,�ͷ���ص��ڴ�
__s32 delete_file_item(file_item_t* file_item)
{
	if (file_item == NULL) {
		return EPDK_FAIL;
	}

	if (file_item->name_len != 0) {
		if (file_item->name != NULL) {
			free(file_item->name);
			file_item->name = NULL;
		}
	}
	free(file_item);
	return EPDK_OK;
}

//-------------------------------------------------------------------------------
//function		:
//descriptions		: ����һ���µ��ļ��б��ú�������ָ��Ŀ¼�������ļ��к��ļ�
//				 �ú���ִ��ʱ�����ļ���������
//				 �ļ��е����γ�һ������
//				�ļ������γ�һ������
//				������������ϲ����ļ�����ǰ��
//arguments		:	ext_para, Ϊ��չ����
//return			: �����������ļ��ĸ���,
//-------------------------------------------------------------------------------
__s32  new_file_list(const char *path, file_item_t** pp_item_list, void *ext_para)
{
    DIR	*pDir = NULL;
	struct dirent *pDirent = NULL;
	file_item_t* list = NULL;
	file_item_t* first = NULL;
	file_item_t* next = NULL;

	file_item_t* folder_first = NULL;			//�ļ����б�
	file_item_t* folder_list = NULL;
	file_item_t* folder_next = NULL;

    __u32 count = 0, folder_count = 0;

    pDir = opendir(path);
    if (pDir == NULL) {
	     return 0;
    }
    rewinddir(pDir);

	while(1) {
	    pDirent = readdir(pDir);
		if(pDirent == NULL) {
			break;
		}
        /* skip "." and ".." sub directory */
        if ((0 == strcmp(".", pDirent->d_name)) || (0 == strcmp("..", pDirent->d_name))) {
               continue;
		}

		//�ļ��е����γ�һ������
		if (pDirent->d_type == FSYS_ATTR_DIRECTORY) {
			if (folder_first == NULL) {
				folder_first = new_file_item(pDirent);
				if (folder_first != NULL) {
					folder_first->fatdirattr = FSYS_ATTR_DIRECTORY;
					folder_list = folder_first;
					//count++;
					folder_count++;
				}
				else {
					break;
				}
			}
			else {
				folder_next = new_file_item(pDirent);
				if (folder_next != NULL) {
					folder_list->next = folder_next;
					folder_next->previous = folder_list;
					folder_list = folder_next;					//folder_list Ϊ��������һ����
					//count++;
					folder_count++;
				}
				else {
					break;
				}
			}
		}
		else {//�ļ������γ�һ������
			if (first == NULL) {
				first = new_file_item(pDirent);
				if (first == NULL) {
					break;
				}
				list = first;
				count++;
			}
			else {
				next = new_file_item(pDirent);

				if (next != NULL) {
					list->next = next;

					next->previous = list;
					list = next;								//list Ϊ��������һ����
					count++;
				}
				else
				{
					break;
				}
			}
		}
	}

//	printf("get %d folders & %d files totally\n", folder_count, count);

	//����������ϲ�����,�ļ���������ǰ
	if (folder_first != NULL)
	{
		if (first != NULL)
		{
			folder_list->next = first;						//�ļ������ļ���������
			first->previous = folder_list;					//�����ļ���
			list->next = folder_first;						//�ļ��б�Ľ�βָ���ļ����б�ʼ�ĵط�
			folder_first->previous = list;
		}
		else												//ֻ���ļ���
		{
			folder_list->next = folder_first;
			folder_first->previous = folder_list;
		}

		*pp_item_list = folder_first;						//�б��׵�ַ���ظ�������
	}
	else {
		if (first != NULL)									//ֻ���ļ�
		{
			list->next = first;
			first->previous = list;		//�γ�˫������
			*pp_item_list = first;						//�б��׵�ַ���ظ�������
		}
		else {
			printf("nothing in this folder\n");
		}
	}

    closedir(pDir);
	return count + folder_count;
}

//ɾ��һ���ļ��б�(ʹ������ɾ��)
//item_list = �б��׵�ַ
//total = ��������
__s32 delete_file_list(file_item_t  *item_list, __u32 total)
{
	__u32 i = 0;
	file_item_t* list = NULL;
	file_item_t* temp = NULL;

	if (item_list == NULL) {
		return EPDK_FAIL;
	}
	list = item_list;
	for (i = 0; i < total; i++) {
		if (list == NULL) {
			break;
		}

		if(list->next == NULL) {
			break;
		}
		temp = list->next;				//�ȱ�����һ����Ŀ��ַ
		if (temp!= NULL) {
			delete_file_item(list);
			list = temp;
		}
		else {
			break;
		}
	}
	return EPDK_OK;
}

//���б���ɾ��һ���ڵ�
__s32 delete_file_item_from_list(file_item_t* item, file_list_t* list)
{
	file_item_t* previous = NULL;
	file_item_t* next = NULL;
	__s32 ret = 0;

	if (item == NULL) {
		return EPDK_FAIL;
	}
	if (list == NULL) {
		return EPDK_FAIL;
	}
	if (list->item_list == item) {
		list->item_list = item->next;		//ɾ�����ǵ�һ��ͷ�ڵ�,��Ҫ�ı�item_list��ֵ
	}
	if (item->next == item)					//������ֻ��һ���ڵ�
	{
//		printf("=========================only one item\n");
		ret = delete_file_item(item);
		list->cur_item = NULL;
		list->item_list = NULL;
		return ret;
	}
	else {
		if (item->previous != NULL) {
			previous = item->previous;
		}
		if (item->next != NULL) {
			next = item->next;
		}
		if (previous == next) {							//��ȱ�ʾֻ��������Ŀ
//			printf("=========================there are two items \n");
			next->next = next;
			next->previous = next;
			ret = delete_file_item(item);
		}
		else						//��������
		{
//printf("=========================more than two items \n");
			previous->next = next;
			next->previous = previous;
			ret = delete_file_item(item);
		}
	}
	return ret;
}

//cur_itemΪ��ǰ��Ŀ
//itemΪҪ�������Ŀ,���뵽cur_item�ĺ���
__s32 insert_file_item_to_list(file_item_t* cur_item, file_item_t* item)
{
	file_item_t* next = NULL;

	if (cur_item == NULL)
	{
		return EPDK_FAIL;
	}
	if(item == NULL)
	{
		return EPDK_FAIL;
	}
	next = cur_item->next;
	cur_item->next = item;
	item->previous = cur_item;
	item->next = next;

	next->previous = item;

	return EPDK_OK;
}

//Ϊfilelist ��������һ���ڵ�
file_list_t* new_file_list_nod(const char *path, void* ext_para)
{
	file_list_t* nod = NULL;

	nod = (file_list_t*)malloc(sizeof(file_list_t));
	if(nod == NULL)
	{
		printf("malloc is not enough for file list\n");
	}
	memset((void *)nod, 0, sizeof(file_list_t));

	nod->total = new_file_list(path, &(nod->item_list), ext_para);
//	printf("%s %d path:%s total:%d\n", __FILE__, __LINE__, path, nod->total);
	if (nod->total == 0) {
		free(nod);
		nod = NULL;
		return NULL;
	}
	strcpy(nod->file_path, path);
	return nod;
}

//ɾ��һ���ڵ�,��ɾ���ڵ��µ�itemlist
__s32 delete_file_list_nod(file_list_t* nod)
{
	__s32 ret = 0;
	if(nod == NULL)
	{
		return EPDK_FAIL;
	}

	if(nod->item_list != NULL)
	{
		ret = delete_file_list(nod->item_list, nod->total);
	}
	memset(nod, 0x00, sizeof(file_list_t));
	free(nod);
	return ret;
}
int FileList_GetItemNum_ByMountPoint(file_list_t *root_nod, char *MountPoint) {
	int i = 0;
	file_item_t *temp = NULL;

	temp = root_nod->item_list;
	while (temp != NULL) {
		if (temp->name) {
			if (!strcmp(temp->name, MountPoint)) {
				 return i;
			}
		}
		temp = temp->next;
		i++;
	}
	return -1;
}
int FileList_AddFileNod_To_RootList(file_list_t *root_nod, DiskInfo_t *DiskInfo) {
	struct dirent dirent;
	file_item_t *item = NULL, *item_tmp = NULL, *tmp = NULL;

	memset(&dirent, 0, sizeof(struct dirent));
	strcpy(dirent.d_name, DiskInfo->MountPoint);
	switch (DiskInfo->MediaType) {
		case MEDIUM_USB_MASSSTORAGE:
			dirent.d_type = RAT_MEDIA_TYPE_USB_DEVICE;
			break;
		case MEDIUM_SD_CARD:
			dirent.d_type = RAT_MEDIA_TYPE_SD_DEVICE;
			break;
		default:
			dirent.d_type = RAT_MEDIA_TYPE_LOCAL_DEVICE;
			break;
	}

	item = new_file_item(&dirent);
	if(item == NULL) {
		return -1;
	}
	item_tmp = root_nod->item_list;
	while (item_tmp) {
		tmp = item_tmp;
		item_tmp = item_tmp->next;
	}
	tmp->next = item;
	item->previous = tmp;
	item->next = NULL;
	root_nod->total += 1;
	return 0;
}
int FileList_DelFileNod_To_RootList(file_list_t *root_nod, DiskInfo_t *DiskInfo) {
	file_item_t *item_tmp = NULL;

	item_tmp = root_nod->item_list;
	while (item_tmp) {
		if (item_tmp && item_tmp->name && !strncmp(item_tmp->name, DiskInfo->MountPoint, strlen(DiskInfo->MountPoint))) {
			if (item_tmp->previous != NULL) {
				item_tmp->previous->next = item_tmp->next;
			}
			if (item_tmp->next != NULL) {
				item_tmp->next = item_tmp->previous;
			}
			break;
		}
		item_tmp = item_tmp->next;
	}
	if (item_tmp == NULL) {
		//printf("%s %d %s not found %s item\n",__FILE__,__LINE__,__func__, DiskInfo->MountPoint);
		return -1;
	} else {
		delete_file_item(item_tmp);
		root_nod->total -= 1;
		return 0;
	}
}

file_list_t* new_file_root_list_nod(void* ext_para) {
	__u32 i = 0, count = 0;;
	struct dirent dirent;
	file_item_t *item = NULL;
	file_list_t *root_nod = NULL;
	DiskInfo_t *disk_tmp = NULL;

	count = DiskManager_GetDiskNum();
	root_nod = (file_list_t*)malloc(sizeof(file_list_t));
	if(root_nod == NULL)
	{
		printf("malloc is not enough for file list\n");
		return NULL;
	}
	memset((void *)root_nod, 0, sizeof(file_list_t));

	for (i = 0; i < count; i++) {
		memset(&dirent, 0, sizeof(struct dirent));
		disk_tmp = DiskManager_GetDiskInfoByIndex(i);
		if (disk_tmp == NULL) {
			printf("%s %d DiskManager_GetDiskInfoByIndex fail\n", __FILE__, __LINE__);
			continue;
		}
		strcpy(dirent.d_name, disk_tmp->MountPoint);
		switch (disk_tmp->MediaType) {
			case MEDIUM_USB_MASSSTORAGE:
				dirent.d_type = RAT_MEDIA_TYPE_USB_DEVICE;
				break;
			case MEDIUM_SD_CARD:
				dirent.d_type = RAT_MEDIA_TYPE_SD_DEVICE;
				break;
			default:
				dirent.d_type = RAT_MEDIA_TYPE_LOCAL_DEVICE;
				break;
		}

		if(item == NULL)
		{
			item = new_file_item(&dirent);
			if(item != NULL) {
				item->next = NULL;
				item->previous = NULL;
				root_nod->item_list = item;
			}
		}
		else {
			item->next = new_file_item(&dirent);
			if(item->next != NULL)
			{
				item->next->previous = item;
				item->next->next = NULL;
				item = item->next;
			}
		}
	}
	root_nod->total = count;
	item = root_nod->item_list;
	return root_nod;
}

//���������Ŵ�nod������
file_item_t* get_file_list_item(file_list_t* nod, __u32 index)
{
	__u32 i = 0;
	file_item_t *list = NULL, *temp = NULL;

	if (nod == NULL) {
		printf("%s %d %s\n", __FILE__, __LINE__, __func__);
		return NULL;
	}
	if (nod->item_list == NULL) {
printf("nod->item_list is null \n");
		return NULL;
	}
	if (index >= nod->total) {
		printf("index is bigger than total \n");
		return NULL;
	}
	list = nod->item_list;

	for (i = 0; (i <= index) && (list != NULL); i++) {
		temp =	list;
		list = list->next;
	}
	return temp;
}


char* get_file_list_item_name(file_list_t* nod, __u32 index)
{
	file_item_t* temp = NULL;

	temp = get_file_list_item(nod, index);
	if(temp == NULL)
	{
		return NULL;
	}
	return temp->name;
}

//����ļ���Ŀ�ļ�����
rat_media_type_t  get_file_list_item_file_type(file_item_t* item)
{
	rat_media_type_t media_type = RAT_MEDIA_TYPE_UNKNOWN;

	if (item == NULL) {
		return RAT_MEDIA_TYPE_UNKNOWN;
	}
	else if (item->fatdirattr == FSYS_ATTR_DIRECTORY)	{
		return RAT_MEDIA_TYPE_FOLDER;
	}
	else if (item->fatdirattr == RAT_MEDIA_TYPE_SD_DEVICE) {
		return RAT_MEDIA_TYPE_SD_DEVICE;
	}
	else if (item->fatdirattr == RAT_MEDIA_TYPE_LOCAL_DEVICE) {
		return RAT_MEDIA_TYPE_LOCAL_DEVICE;
	}
	else if (item->fatdirattr == RAT_MEDIA_TYPE_USB_DEVICE) {
		return RAT_MEDIA_TYPE_USB_DEVICE;
	}
//	printf("%s %d %s item->name:%s\n", __FILE__, __LINE__, __func__, item->name);
	media_type = rat_get_file_type(item->name);
	return media_type;

}

//���ݸ����Ķ����ڵ㣬ɾ������filelist ����
//ע��ֻ����ɾ������
__s32 delete_file_list_chain(file_list_t* top_nod)
{
	file_list_t* parent_nod = NULL;
	file_list_t* child_nod = NULL;
	if(top_nod == NULL)
	{
		return EPDK_FAIL;
	}
	parent_nod = top_nod;
	child_nod = parent_nod->child;				//�����ӽڵ��ַ
	if(child_nod == NULL)
	{
		delete_file_list_nod(parent_nod);		//ɾ�����ڵ�
		return EPDK_OK;
	}

	while(child_nod != NULL)
	{
		delete_file_list_nod(parent_nod);		//ɾ�����ڵ�
		parent_nod = child_nod;					//ָ����һ���ڵ�
		child_nod = parent_nod->child;			//�����ӽڵ��ַ
	}
	return EPDK_OK;
}

//char            sub_dir[RAT_MAX_FULL_PATH_LEN];				//���ں����У��������ջ���
//���һ���ļ���Ŀ¼���ļ���Ŀ�����������ļ���
__s32 get_item_num_in_dir(const char * dirpath, __u32 *total)
{
    DIR *dirp = NULL;
    static __s32 dir_level = 0;
    struct dirent *direntp = NULL;
    char sub_dir[RAT_MAX_FULL_PATH_LEN] = {0};

    if (dirpath == NULL) {
        return EPDK_FAIL;
    }
    else if(dir_level > C_MAX_DIR_SCAN_LEVEL) {
        return EPDK_FAIL;
    }
    else {
        dir_level++;
    }

    dirp = (DIR *)opendir(dirpath);
    if (dirp == NULL)
    {
        return EPDK_FAIL;
    }

    while ((direntp = (struct dirent *)readdir(dirp)) != NULL) {
        if (direntp->d_type == FSYS_ATTR_DIRECTORY) {
            /* skip "." and ".." sub directory */
            if ((0 == strcmp(".", direntp->d_name)) || (0 == strcmp("..", direntp->d_name))) {
                continue;
            }

			memset(sub_dir, 0, RAT_MAX_FULL_PATH_LEN);
            strcpy(sub_dir, dirpath);
            strcat(sub_dir, "\\");
            strcat(sub_dir, (const char *)direntp->d_name);
            if(get_item_num_in_dir(sub_dir, total) == EPDK_FAIL)
            {
                return EPDK_FAIL;
            }
			if(dir_level > 0)
			{
				dir_level--;
			}
        }
        else
        {
            (*total)++;
        }
    }

    if(closedir(dirp)== EPDK_FAIL)
    {
	return EPDK_FAIL;
    }
    (*total)++;
    return EPDK_OK;
}


//ɾ��һ���ļ���
__s32 delete_dir(char* dir_name, file_op_info_t *op_info)
{
    DIR *dir = NULL;
    __s32 ret = EPDK_OK;
    struct dirent *dirent = NULL;
    char fullpath[RAT_MAX_FULL_PATH_LEN] = {0};

    if(dir_name == NULL)
    {
        return EPDK_FAIL;
    }
    else if(op_info->dir_level > C_MAX_DIR_SCAN_LEVEL)
    {
	if(op_info != NULL)
	{
		op_info->percent = 100;
	}
    }
    else
    {
        op_info->dir_level++;
    }
    memset(fullpath, 0, RAT_MAX_FULL_PATH_LEN);

    /*open dir*/
    dir = opendir(dir_name);
    if (dir == NULL) {
        return EPDK_FAIL;
    }

    while(1) {
        /*read dir*/
        dirent = readdir(dir);
        if(dirent == NULL) {
            break;
        }

        memset(fullpath, 0, RAT_MAX_FULL_PATH_LEN);
        strcpy(fullpath, dir_name);
        strcat(fullpath, "\\");
        strcat(fullpath, (const char *)dirent->d_name);

        if (dirent->d_type == FSYS_ATTR_DIRECTORY) {
            if ((0 == strcmp(".", dirent->d_name)) || (0 == strcmp("..", dirent->d_name))) {
                continue;
            }

            ret = delete_dir(fullpath, op_info);
            if (ret == EPDK_FAIL) {
                ret = EPDK_FAIL;
                break;
            }

			if (op_info->dir_level > 0){
				op_info->dir_level--;
			}
        }
        else {
            if (remove(fullpath) == -1) {
                ret = EPDK_FAIL;
                break;
            }
            else {
		if (op_info != NULL) {
	                op_info->finish_num++;
	                op_info->percent = (op_info->finish_num * 100) / op_info->total_num;
					if (op_info->OnDraw != NULL) {
						op_info->OnDraw(op_info);
					}
		}
            }
        }
    }


	if (op_info != NULL) {
	    op_info->finish_num++;
	    op_info->percent = (op_info->finish_num * 100) / op_info->total_num;
		if(op_info->OnDraw != NULL)
		{
			op_info->OnDraw(op_info);
		}
	}
    closedir(dir);

    ret = rmdir(dir_name);
	if (ret == EPDK_FAIL){
		if (op_info != NULL) {
			op_info->percent = 101;
		}
	}
    return ret;
}
