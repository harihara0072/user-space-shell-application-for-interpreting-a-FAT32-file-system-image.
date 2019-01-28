/*
 
 Name: Nakshatrala Hari Hara Kumar
 ID: 1001102740 
 
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 10   // Mav shell only supports five argument


//This will hold the pid of last child process created
int pid_of_child;

//This will hold the pids of last 10 child process created
int child_pids[10];
int cpid_count = 0;
int temp;

//Signal handling method for SIGINT and SIGTSTP
static void signal_handler(int signal)
{
	switch(signal)
	{
	case SIGTSTP:
		kill(child_pids[cpid_count-1], SIGTSTP) ;
		fflush(stdout);
	case SIGINT:
		kill(child_pids[cpid_count-1], SIGINT) ;
		fflush(stdout);
	}
}
int main()
{
	//this will store the last 15 commands user enterd
	char *hist[15];
	int hist_count = 0;
	char cmd_str[100], *ptr;
	ptr = cmd_str;
	FILE *fp;
	char buff[255];
	
	//This will catch the signal and handle them with the defined
	//signal handling functions
	struct sigaction sig_act;
	sig_act.sa_handler = signal_handler;
	sigaction(SIGTSTP, &sig_act, NULL);
	sigaction(SIGINT, &sig_act, NULL);
	while(1)
	{
		// Print out the msh prompt
		printf ("mfs> ");
		
		// Read the command from the commandline.  The
		// maximum command that will be read is MAX_COMMAND_SIZE
		// This while command will wait here until the user
		// inputs something since fgets returns NULL when there
		// is no input
		while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );
		
		/* Parse input */
		//This will contain the command entered by the user which is seperated
		char *argarry[MAX_NUM_ARGUMENTS];
		int arg_counter = 0;
		
		// Pointer to point to the token
		// parsed by strsep
		char *arg;
		
		// we are going to move the pointer so
		// keep track of its original value so we can deallocate
		// the correct amount at the end
		ptr = cmd_str;
		argarry[0]= '\0';
		
		// Tokenize the input stringswith whitespace used as the delimiter
		while(((arg = strsep(&ptr, WHITESPACE))!= NULL) && arg_counter<MAX_NUM_ARGUMENTS)
		{
			argarry[arg_counter] = strndup(arg, MAX_COMMAND_SIZE);
			argarry[arg_counter+1]=(char *)0;
			if( strlen( argarry[arg_counter] ) == 0 )
			{
				argarry[arg_counter] = NULL;
			}
			arg_counter++;
		}
		
		//Checking if there is no input enterd
		//If nothing entered then it again continue from While(1) loop
		if(argarry[0] == '\0')
		{
			continue;
		}
		
		//Checking if the user entered "cd" command.
		//This will change the directory as per the command user entered
		else if(strcmp(argarry[0], "cd")==0)
		{
			chdir(argarry[1]);	
		}
		
		//Checking if the user entered "bg" to move a process to background
		//This will check the pid of the last child process which is suspended
		//and send a signal SIGCONT to that process to switch it to running state
		else if(strcmp(argarry[0], "open")==0)
		{
			
			fp = fopen(argarry[1], "r");
					
		}
		
		else if(strcmp(argarry[0], "root")==0)
			{
			
			int BPB_Fz32;
			short BPB_BPS;
			short BPB_RSC;
			signed char BPB_SPC,BPB_NumF;
			fseek(fp,11, SEEK_SET);
			fread(&BPB_BPS,2,1,fp);
			fseek(fp,13, SEEK_SET);
			fread(&BPB_SPC,1,1,fp);
			fseek(fp,14, SEEK_SET);
			fread(&BPB_RSC,2,1,fp);
			fseek(fp,16, SEEK_SET);
			fread(&BPB_NumF,1,1,fp);
			fseek(fp,36, SEEK_SET);
			fread(&BPB_Fz32,4,1,fp);
			struct __attribute__((__packed__)) DirectoryEntry {
				char DIR_Name[11];
				char DIR_Attr;
				char Unused1[8];
				unsigned short DIR_FirstClusterHigh;
				char Unused2[4];
				unsigned short DIR_FirstClusterLow;
				int DIR_FileSize;	
			};
			
			struct DirectoryEntry dir[17];
			int root_offset = (BPB_NumF * BPB_Fz32 * BPB_BPS) +(BPB_RSC * BPB_BPS);
			
			fseek(fp, root_offset, SEEK_SET);
			int i = 0;
			for(i = 0; i < 16; i++)
			{
				memset(&dir[i].DIR_Name, 0 , 11);
				fread(&dir[i], 32, 1, fp);
			}
			for(i = 0; i < 16; i++)
			{
				char name[12];
				memset(name, 0, 12);
				strncpy(&name[0], dir[i].DIR_Name, 11);
				if(dir[i].DIR_Attr == 0x10 || dir[i].DIR_Attr == 0x20 ||dir[i].DIR_Attr == 0x1)
				{
					printf("Filename:%s\n", name);
				}
			}
					
					
							
			}
				
		else if(strcmp(argarry[0], "show")==0)
		{
			
			//fp = fopen("/tmp/test.txt", "r");
			   fscanf(fp, "%s", buff);
			   printf("1 : %s\n", buff );

			   fgets(buff, 255, (FILE*)fp);
			   printf("2: %s\n", buff );
			   
			   fgets(buff, 255, (FILE*)fp);
			   printf("3: %s\n", buff );
		}
		else if(strcmp(argarry[0], "info")==0)
		{
			int BPB_Fz32;
			short BPB_BPS;
			short BPB_RSC;
			signed char BPB_SPC,BPB_NumF;
			fseek(fp,11, SEEK_SET);
			fread(&BPB_BPS,2,1,fp);
			fseek(fp,13, SEEK_SET);
			fread(&BPB_SPC,1,1,fp);
			fseek(fp,14, SEEK_SET);
			fread(&BPB_RSC,2,1,fp);
			fseek(fp,16, SEEK_SET);
			fread(&BPB_NumF,1,1,fp);
			fseek(fp,36, SEEK_SET);
			fread(&BPB_Fz32,4,1,fp);
			fprintf(stdout, "BPB_BytesPerSec-%d\n", BPB_BPS);
			fprintf(stdout, "BPB_BytesPerSec-%x\n", BPB_BPS);
			fprintf(stdout, "BPB_SecPerClus-%d\n", BPB_SPC);
			fprintf(stdout, "BPB_SecPerClus-%x\n", BPB_SPC);
			fprintf(stdout, "BPB_RsvdSecCnt-%d\n", BPB_RSC);
			fprintf(stdout, "BPB_RsvdSecCnt-%x\n", BPB_RSC);
			fprintf(stdout, "BPB_NumFATS-%d\n", BPB_NumF);
			fprintf(stdout, "BPB_NumFATS-%x\n", BPB_NumF);
			fprintf(stdout, "BPB_FATSz32-%d\n", BPB_Fz32);
			fprintf(stdout, "BPB_FATSz32-%x\n", BPB_Fz32);
					
		}
		
		//Checking if the user enterd "showpids"
		//this will display all the pids of last 10 process which is 
		//stored in an array
		else if(strcmp(argarry[0], "showpids")==0)
		{
			int s;
			for(s=0;s<cpid_count;s++)
			{
				printf("%d: %d\n",s+1,child_pids[s]);
			}
		}
		
		//Checking if user entered "history"
		//this will display last 15 commands entered by the user
		//which is stored in an array
		else if (strcmp(argarry[0],"history")== 0)
		{
			int j;
			for(j=0;j<hist_count;j++)
			{
				printf("%d: %s\n",j+1,hist[j]);					
			}
		}
		
		//if the input is not null,bg,shoupids,history then
		//this is executed
		else
		{
			pid_t child;
			int status;
			int temp;
			
			//if there are less that 15 commands entered then the array
			//will be filled with that command entered
			if(hist_count<15)
			{
				hist[hist_count] = argarry[0];
				hist_count = hist_count+1;
			}
			
			//if there are more that 15 commands entered then 
			//each element in array is moved towards left by one 
			//and the latest command will be entered at the last position
			else
			{
				hist[0] = hist[1];
				hist[1] = hist[2];
				hist[2] = hist[3];
				hist[3] = hist[4];
				hist[4] = hist[5];
				hist[5] = hist[6];
				hist[6] = hist[7];
				hist[7] = hist[8];
				hist[8] = hist[9];
				hist[9] = hist[10];
				hist[10] = hist[11];
				hist[11] = hist[12];
				hist[12] = hist[13];
				hist[13] = hist[14];
				hist[14] = argarry[0];
				hist_count = 15;
			}
			
			//If the user enters"exit" or "quit" it will exit the program
			if(strcmp(argarry[0],"exit") == 0 || strcmp(argarry[0],"quit") == 0)	
			{
				exit(0);
			}
			else
			{
				child = fork();
				
				//Checking if it is a parent or child
				if (child==0)
				{
					//replacing the child process with the process user entered
					temp = execvp(argarry[0], argarry);
					
					//if the command execution failes
					if (temp== -1)
					{
						printf("Command not found.\n");
					}
				}
				
				//if it is parent
				else if(child!=0)
				{
					//storing the pids of last 10 child process in an array
					if(cpid_count<10)
					{
						child_pids[cpid_count] = child;
						cpid_count = cpid_count +1;
					}
					
					//if there are more than 10 process then each pid will
					//move left by one element and the latest pid saved
					//at last position
					else
					{
						child_pids[0] = child_pids[1];
						child_pids[1] = child_pids[2];
						child_pids[2] = child_pids[3];
						child_pids[3] = child_pids[4];
						child_pids[4] = child_pids[5];
						child_pids[5] = child_pids[6];
						child_pids[7] = child_pids[8];
						child_pids[8] = child_pids[9];
						child_pids[9] = child;
						cpid_count = 10;
					}				
					pid_of_child = child;
					waitpid(child, &status, 0);
				}
			 }
		 }
	
	memset(cmd_str,0, strlen(cmd_str));
	memset(buff,0, strlen(buff));
	}
}
	

