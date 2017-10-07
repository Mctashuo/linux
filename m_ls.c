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

SList SL_Create();

int l = 0,R=0,a=0,i=0,d=0;

SList SL_Insert(SList,char * file_path);

SList do_ls(SList,char * dirname);


void mode_to_letters(int mode, char * str);

char *uid_to_name(uid_t uid);

char *gid_to_name(gid_t gid);

void set_filepath(SList ,char * filepath);

void printf_dir(SList);

void isR(char *);

void del_list(SList);
int main(int argc,char **argv)
{

	SList head,cur;	//定义一个头指针和当前尾指针
	head = SL_Create();
	cur = head;
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

	if (argc == 1)
	{

		if(l==0 && R ==0 && a==0 && i==0 && d==0){
			char *temp = malloc(strlen(argv[optind]));
/*		for(;optind<argc;optind++)

		{
			printf("%d",(int)strlen(argv[optind]));
			printf("%s\n",argv[optind]);
		}
*/
	//	memcpy(temp,argv+optind,(argc-optind)*sizeof(char));
			strncpy(temp,argv[optind],strlen(argv[optind]));	
			chdir(temp);
			head->file_path  = temp;
			cur = do_ls(cur,temp);
		}
		else
		{
			head->file_path = ".";
			cur = do_ls(cur,".");
		
		}
	}

	else if(argc >2)
	{
		char *temp = malloc(strlen(argv[optind]));
		strncpy(temp,argv[optind],strlen(argv[optind]));	
		chdir(temp);
		head->file_path  = temp;
		cur = do_ls(cur,temp);
		
	}
	else 
	{
		head->file_path = ".";
		cur = do_ls(cur,".");
	}

	if(R==1)
	{
		isR(head->file_path);
	}
	else{
		printf_dir(head);
	}
	chdir("");
	return 0;
}


SList do_ls(SList cur, char * dirname )

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
		//	set_filepath(cur,direntp->d_name);
			cur = SL_Insert(cur,direntp->d_name);
		}

		closedir(dir_ptr);

		return cur;
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

void set_filepath(SList lcur ,char *filepath)
{
	//	struct file_info *f;
	//	f->next = NULL;
	lcur = SL_Insert(lcur,filepath);

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
void printf_dir(SList list)
{
	list=list->next;

	do
	{
		if(a==0 && list->file_path[0] == 46)
		{
			list=list->next;
			continue;
		}
		struct stat info,*info_p;
		if(stat(list->file_path,&info) == -1)
		{
			perror(list->file_path);
		}

		else
		{
			info_p = &info;
		}
		if(i==1)
		{
			printf("%8d  ",(int) info_p->st_ino); 
		}
		if(l==1)
		{
			char modestr[11];
			mode_to_letters(info_p->st_mode,modestr);
			
			printf("%s",modestr);
			printf("%-8s ",uid_to_name(info_p->st_uid));
			printf("%-8s ",gid_to_name(info_p->st_gid));
			printf("%4d ",(int)info_p->st_nlink);
			printf("%8ld ",(long)info_p->st_size);
			printf("%.12s ",4 + ctime(&info_p->st_mtime));
		}

		printf("%s  ",list->file_path);
		list=list->next;
		if(l==1)
		{
			printf("\n");
		}
	}while(list->next!=NULL);   //46 为.的ascll码
}


void isR(char *dir)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	SList head,cur;
	
	
	cur = head = SL_Create();

	if((dp = opendir(dir)) == NULL)
	{
		return;
	}


	chdir(dir);
	SList shead,scur;
	scur = shead = SL_Create();
	shead->file_path = dir;
	while((entry = readdir(dp)) !=NULL) 
	{
		lstat(entry->d_name,&statbuf);
	//	set_filepath(cur,entry->d_name);
		cur = SL_Insert(cur,entry->d_name);
		
		if(S_ISDIR(statbuf.st_mode)) 
		{
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;

			scur = SL_Insert(scur,entry->d_name);
			
		}
		
	}
	printf("\n%s:\n",getcwd(NULL,0));
	printf_dir(head);
	
	SList list = shead;

	while(list->next != NULL)
	{
		list = list->next;
		isR(list->file_path);
	}
	chdir("..");

	closedir(dp);
}


void del_list(SList head)
{

	SList p,q;
	p=head;
	while(p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	p=NULL;
	q=NULL;
}
