#include <stdio.h> 

#include <sys/types.h>

#include <dirent.h>

#include <sys/stat.h>

#include <string.h>

#include <unistd.h>

#include <pwd.h>

#include <grp.h>

#include <stdlib.h>

#include <time.h>

#include <malloc.h>

typedef struct node *PNode;
typedef struct node

{
	/*	char * mode;
		int nlink;
		char * u_name;
		char * g_name;
		long size;
		char * mtime;
		char * file_name;
	 */
	char *file_path;
	struct node *next;

}Node,*SList;

SList head,cur;	//定义一个头指针和当前尾指针
SList SL_Create();

int l = 0,R=0,a=0,i=0,d=0;

SList SL_Insert(SList,char * file_path);

void do_ls(char * dirname);


void mode_to_letters(int mode, char * str);

char *uid_to_name(uid_t uid);

char *gid_to_name(gid_t gid);

void set_filepath(char * filepath);

void printf_dir();

int main(int argc,char **argv)
{

	head = SL_Create();
	cur = head;
	if (argc <= 1)
	{
		head->file_path = ".";
		do_ls(".");
	}
	else
	{
		chdir(argv[1]);
		head->file_path  = *argv;
		do_ls(argv[1]);
		int opt;
		while((opt = getopt(argc,argv,"lRaid")) != -1)
		{
			switch(opt) 
			{
				case 'l':
					l=1;
					break;
				case 'R':
					R=1;
					break;
				case 'a':
					a=1;
					break;
				case 'i':
					i=1;
					break;
				case 'd':
					d = 1;
				case '?':
					printf("unknown option: %c\n",optopt);
					break;
				default:
					break;
			}
		}
		chdir("");
	}

	printf_dir();
	return 0;
}


void do_ls( char * dirname )

{

	DIR    *dir_ptr;

	struct dirent  *direntp;

	/*

	   struct dirent

	   {

	   ino_t d_nio;

	   ff_t d_off;

	   signed short int d_reclen;

	   unsigned char d_type;

	   har d_name[256];  

	   }

d_ino:目录进入点的inode

d_off:目录文件开头至此目录进入点的位移

d_reclen:d_name的长度，不包含NULL字符

d_type:d_ame所指文件类型

d_name:文件名

	 */

	/*

	   opendir函数用来打开参数name指定的目录，

	   并返回DIR *形态的目录流

	 */

	if ( ( dir_ptr = opendir( dirname ) ) == NULL ) 

	{

		fprintf(stderr,"ls1: cannot open %s, not a directory. treat as a file shown below:\n", dirname);

		//    dostat( dirname ); //如果不是目录就当作文件来显示其属性

	}

	else

	{

		/*

		   readdir返回参数dir目录流的下个目录进入点

		 */

		while ( ( direntp = readdir( dir_ptr ) ) != NULL )

		{ 

			//    dostat( direntp->d_name );/*逐个显示目录里文件信息*/
			set_filepath(direntp->d_name);
		}

		closedir(dir_ptr);

	}

}



void mode_to_letters(int mode, char * str)

{

	strcpy(str, "----------");           /* default=无参数 */



	if (S_ISDIR(mode))  

		str[0] = 'd';    /* 目录      */

	if (S_ISCHR(mode)) 

		str[0] = 'c';    /* 字符设备   */

	if (S_ISBLK(mode))  

		str[0] = 'b';    /* 块设备     */



	if (mode & S_IRUSR) 

		str[1] = 'r';    /* 用户权限  */

	if (mode & S_IWUSR) 

		str[2] = 'w';

	if (mode & S_IXUSR) 

		str[3] = 'x';



	if (mode & S_IRGRP) 

		str[4] = 'r';    /* 组权限 */

	if (mode & S_IWGRP) 

		str[5] = 'w';

	if (mode & S_IXGRP)

		str[6] = 'x';



	if (mode & S_IROTH) 

		str[7] = 'r';    /* 其人的权限 */

	if (mode & S_IWOTH) 

		str[8] = 'w';

	if (mode & S_IXOTH) 

		str[9] = 'x';

}



char *uid_to_name(uid_t uid)

{

	struct  passwd *pw_ptr;

	static  char numstr[10];

	//获取用户ID

	if ((pw_ptr = getpwuid(uid)) == NULL)

	{

		sprintf(numstr,"%d", uid);

		return numstr;

	}

	else

	{ 

		return pw_ptr->pw_name ;

	}

}



char *gid_to_name( gid_t gid )

{

	struct group *grp_ptr;

	static  char numstr[10];

	//获取组ID

	if ((grp_ptr = getgrgid(gid)) == NULL)

	{

		sprintf(numstr,"%d", gid);

		return numstr;

	}

	else

	{ 

		return grp_ptr->gr_name;

	}

}

void set_filepath(char *filepath)
{
	//	struct file_info *f;
	//	f->next = NULL;
	cur = SL_Insert(cur,filepath);

}


SList SL_Create()	//创建链表
{
	PNode List;
	PNode p_head = (SList) malloc(sizeof(Node));
	if(p_head == NULL)
	{
		exit(-1);
	}
	p_head->file_path="\n";
	p_head->next = NULL;
	return p_head;
}

SList SL_Insert(SList list,char * file_path)
{
	SList p,q;
	p = list;
	
	q = (SList) malloc(sizeof(Node));

	if(q!=NULL)
	{
		q->file_path = file_path;
		p->next = q;
		q->next = NULL;
		return q;
	}


	
}
void printf_dir()
{
	SList l = head;	
	do
	{
		if(l->file_path[0] != 46)
			printf("%s  ",l->file_path);
		l=l->next;
	}while(l->next!=NULL);   //46 为.的ascll码
}
