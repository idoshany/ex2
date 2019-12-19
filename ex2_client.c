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

int main(int argc, char** argv){
	pid_t P1;
	int P2, P3, P4;
	int to_srv;
	int i;
	char pid[100];
	if(argc != 5){
		printf("<Usage> ./ex2_client.out P1 P2 P3 P4\n");
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
	printf("%d\n", P1);
	printf("%d\n", getpid());
	kill(P1,SIGCONT);
}


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
