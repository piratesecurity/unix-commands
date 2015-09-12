#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
void find_mode(int,char **,char *);
int prompt_flag=0;

void main(int argc,char **argv)
	{
	char *options="i",buff[100];
	int file_num=1;
	if (argc<2) 
		{
		printf("rm: missing operand\n");
		}
	else
		{
		find_mode(argc,argv,options);
		while (file_num<argc)
			{
			if (*argv[file_num]!='-')
				{
				int del=0;
				if (prompt_flag==1)
					{
					printf("rm: remove regular file'%s'? ",argv[file_num]) ;
					scanf("%s",buff);
					if (buff[0]=='y')
						{del=1;}				
					}
				if (prompt_flag==0 || del==1)
					{
					int status=remove(argv[file_num]);
					if (status!=0)
						{
						printf("rm: cannot remove ‘count’: No such file or directory\n");
						}
					}
				}
			file_num++;
			}
		}
	
	}

void find_mode(int argc,char **argv,char *options )
	{
	char option;	
	while ((option=getopt(argc,argv,options))!=-1)
		{		
		if (option=='i') prompt_flag=1;

		else
			{
			printf("rm: invalid option -- %c\n",option);
			exit(1);
			}
		}
	}
