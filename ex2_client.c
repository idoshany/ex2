/**
 Ido Shany - 207689746
 Omer Lindner - 313532574
**/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <math.h>

int random_number(int min_num, int max_num);
void sighandler(int sig);
int main(int argc, char** argv){
	pid_t P1=0; //its the Process Id of the server
	int P2 = 0, P3 = 0, P4 = 0; // The argv values
	int to_srv, to_client; // to_srv.txt fd, to_client.txt fd
	int i; //loop index
	char pid[100]= ""; //Buffer to keep the value of to_srv.txt pre writing to the file
	char to_Client[100] = "";//buffer to keep the name of the to_client file name
	char print[100]= "";//buffer to keep the value of the to_client file, then printing it
	signal(SIGCONT, sighandler);
	if(argc != 5){
		printf("<Usage> ./ex2_client.out P1 P2 P3 P4\n");
		exit(1);
	}
	printf("%s %s %d %d\n",argv[3], argv[4], strcmp(argv[4],"0"), strcmp(argv[3],"4"));
	if((strcmp(argv[4],"0") == 0) && (strcmp(argv[3],"4") == 0)){
		fprintf(stderr,"Can't Divide with 0\n");
		exit(1);
	}
	sprintf(pid, "%d %s %s %s\n", getpid(), argv[2], argv[3], argv[4]);
	for(i =0 ; i < 10; i++){
		to_srv = open("to_srv.txt", O_RDWR | O_CREAT| O_EXCL, 0777);
		if(to_srv == -1)
			sleep(random_number(1,5));
		else
			break;
	}
	if(i == 10){
		printf("Tried too many Times, Bye\n");
		exit(1);
	}
	write(to_srv, pid, strlen(pid));
	for(i=0; i < strlen(argv[1]); i++)
		P1 += pow(10,strlen(argv[1])-i-1) *(argv[1][i]-'0');
	kill(P1,SIGCONT);
	pause();
	sprintf(to_Client, "to_client_%d", getpid());
	fflush(stdout);
	to_client = open(to_Client, O_RDONLY);
      	read(to_client, print, 100);
	printf("The Result - %s", print);
	close(to_srv);
	close(to_client);
}



//Function to randomize a number between 1 and 5
int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

//Function for catching the SIGCONT signal
void sighandler(int sig){
	printf("Continuing the process\n");
	return;
}
