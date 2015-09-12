/*
Recursive ls command implementation
usage: ./a.out dir1 dir2

any doubts :mail:bharath.hussy@gmail.com
*/


#include<stdio.h>
#include<dirent.h>
#include<errno.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>



struct path
	{
	char name[5000];
	struct path *next;
	};

void ls(char *);

void main(int argc,char **argv)
{		
	char c[1000];
	int i=0;

	if (argc==1) 
		{
		strcpy(c,".");
		ls(c);
		}
    else 
		{
		for (i=1;i<argc;i++)
			{
			strcpy(c,argv[1]);
			ls(c);
			}
		
		}

}

void ls(char *name)
	{
	DIR *dir=opendir(name);
	struct dirent *dir_struct;
	struct path *first=NULL,*current;
	if (dir!=NULL)
		{
		int index=0,i;
		
		printf("\n\n %s \n",name);
		while (dir_struct=readdir(dir))
			{	
		  char mode[10]="---------";	  
          struct stat sbuf;
          stat (dir_struct->d_name,&sbuf);
          if(sbuf.st_mode & S_IRUSR)
            mode[0]='r';
          if(sbuf.st_mode & S_IWUSR)
            mode[1]='w';
          if(sbuf.st_mode & S_IXUSR)
            mode[2]='x';
          if(sbuf.st_mode & S_IRGRP)
            mode[3]='r';
          if(sbuf.st_mode & S_IWGRP)
            mode[4]='w';
          if(sbuf.st_mode & S_IXGRP)
            mode[5]='x';
          if(sbuf.st_mode & S_IROTH)
            mode[6]='r';
          if(sbuf.st_mode & S_IWOTH)
            mode[7]='w';
          if(sbuf.st_mode & S_IXOTH)
            mode[8]='x';

			printf("%s\t%s\t%s",mode,dir_struct->d_name,ctime(&sbuf.st_ctime));		

			if (dir_struct->d_type==8)
				{
					int ll;
				}
			else if (dir_struct->d_type==4) 
				{
				if (strcmp(dir_struct->d_name,".")!=0 && strcmp(dir_struct->d_name,"..")!=0)
				{		
					struct path * folder_node=(struct path *)malloc(sizeof(struct path ));
					strcpy(folder_node->name,dir_struct->d_name);
					folder_node->next=NULL;				
						
					if (first==NULL) {first=folder_node;}
					 else
						{
						current=first;
						while (current->next!=NULL){current=current->next;}
						current->next=folder_node;					
						}			
				}
					
				}		
			
			}
		//printf("\nFolders\n");
		
		current=first;
		while(current!=NULL) 
			{ 
			struct path * complete_path=(struct path *)malloc(sizeof(struct path ));				
			strcpy(complete_path->name,name);
			if (complete_path->name[strlen(complete_path->name)-1]!='/')
			strcat(complete_path->name,"/");
			strcat(complete_path->name,current->name);			
			//printf("\n folder send %s \n",complete_path->name);		
			ls(complete_path->name);	
			current=current->next;			
			}
		
		}
	else
		{
		
		printf("\n404: Folder Not found: %s \n",name);		
		}
	
	closedir(dir);	
	}
