#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
void main(int argc,char *argv[])
	{
	int i=1,sig_d=15,status;
	if (argc>=2)
		{
		if (atoi(argv[1])<0)
			{
			i=2;
			sig_d=atoi(argv[1])*-1;	
			}
		for (;i<argc;i++)
			{
			status=kill(atoi(argv[i]),sig_d);
			if (status!=0) printf("Failed to kill process PID :%d",atoi(argv[i]));
			else printf("Operation success id:%s\n",argv[i]);
			}
		
		}		
	}


