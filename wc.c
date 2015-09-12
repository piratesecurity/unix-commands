#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int word_flag=0,all_flag=0,char_flag=0,line_flag=0;

int total_count=0,file_num=1,total_wcount=0,total_lcount=0,total_ccount=0;

void print_output(int,char *,int,int,int);
void find_mode(int argc,char **argv,char *);

void main(int argc,char **argv)
	{
	
	char *options="lwc",*buff,prev_char='\0';	
	find_mode(argc,argv,options);
	while (file_num<argc)
		{
		int line_count=0,word_count=0,char_count=0;
		if (*argv[file_num]!='-')
			{
			int fd=open(argv[file_num],O_RDONLY);
			if (fd<0)	
				{
				printf("wc: %s: No such file or directory\n",argv[file_num]);
				continue;
				}
			else 
				{				
				while(read(fd,buff,1)>0)
					{
					char_count++;
					if (*buff=='\n') {line_count++;word_count++;}
					else if (*buff==' ') word_count++;					
					prev_char=*buff;					
					}			
				}
			print_output(0,argv[file_num],line_count,word_count,char_count);			
			}
		file_num++;
		total_wcount+=word_count;
		total_ccount+=char_count;
		total_lcount+=line_count;
	
		}
		if (total_ccount)
			print_output(1,argv[file_num],total_ccount,total_wcount,total_ccount);	

	
	}

void print_output(int total,char *file_name,int line_count,int word_count,int char_count)
	{

	if (line_flag==1)
		printf("  %5d",line_count);
	if (word_flag==1)
		printf("  %5d",word_count);
	if (char_flag==1)
		printf("  %5d",line_count);
	if (total==1)
		printf("  total\n");
	else
		printf("  %s\n",file_name);
		
	}

void find_mode(int argc,char **argv,char *options )
	{
	char option;	
	while ((option=getopt(argc,argv,options))!=-1)
		{
		
		switch(option)
			{						
			case 'l':
				{
				line_flag=1;
				break;
				}
			case 'w':
				{
				word_flag=1;
				break;
				}

			case 'c':
				{
				char_flag=1;
				break;	
				}
			default:
				{
				printf("wc: invalid option -- %c",option);
				exit(1);
				}
				}
			}
	if (line_flag==0 && word_flag==0&& char_flag==0) {all_flag=1;line_flag=1;word_flag=1;char_flag=1;}
	}
