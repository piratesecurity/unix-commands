#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
void main(int argc,char *argv[])
	{
	int f_num=1,fd,num;
	char *buff,*f_name;
	if (argc<2)
		{
		printf("Usage: cat [FILE] [FILE]...\n");
		}
	while (f_num<argc)
		{	
		f_name=argv[f_num];
		f_num++;	
		fd=open(f_name,O_RDONLY);	
		if (fd<0)	
			{
			printf("cat: %s: No such file or directory\n",f_name);
			continue;
			}
		else 
			{				
			while(read(fd,buff,1)>0)
				{
				printf("%c",buff[0]);	
				}			
			}		
		}
	}
