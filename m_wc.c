#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<unistd.h>
#include<stdlib.h>

#define IN 1    /*单词内*/
#define OUT 0	//单词外


int c,l,L,w;

int flag=0;
void m_wc(char * filename);

int main(int argc,char ** argv)
{
	int opt;
	while((opt = getopt(argc,argv,"clLw")) != -1)

	{
	
		switch(opt)
		{
			case 'c':
				c=1;
				break;
			case 'l':
				l=1;
				break;
			case 'L':
				L=1;
				break;
			case 'w':
				w=1;
				break;
			default:
				break;
		}
		
	}
	if(argc == 1)
	{

		return 0;
	}

	if(argc ==2)
	{
		m_wc(argv[1]);
	}
	if(argc > 2)
	{
		{
			
			char * temp = malloc(strlen(argv[optind]));
			strncpy(temp,argv[optind],strlen(argv[optind]));
			char * filename = temp;
			flag =1;
			m_wc(filename);
		}
	}
	return 0;
}
void m_wc(char * filename)
{
	int c1, n1,nw,nc,state,temp,lc;

	
	state  = OUT;
	//n1 行数 nw 单词数 nc 字符数 lc 最长行 
	n1 = nw = nc = lc =temp =0;

	FILE * f = fopen(filename,"r");
	while((c1 = fgetc(f)) != EOF)
	{
		++nc;
		if( c1 == '\n')
		{
			++n1;
			temp = 0;
		}
		else
		{
			if(c1 == '\t')
				temp += 8;
			else temp++;
		}

		if(temp > lc)
		{
			lc = temp;
		}
			
		if(c1 == ' ' || c1 == '\n' || c1 == '\t')
			state = OUT;
		
		else if (state == OUT) 
		{
			state = IN;
			++nw;
		}

		
	}
	if(flag ==1)
	{
		if(c==1)
		{
			printf("%d ",nc);
		}
		if(l==1)
		{
			printf("%d ",n1);	
		}
		if(L==1)
		{
			printf("%d ",lc);
		}

		if(w==1)
		{
			printf("%d ",nw);
		}
		printf("%s\n",filename);
	}
	else
		printf("%d %d %d %s\n",n1,nw,nc,filename);
}
