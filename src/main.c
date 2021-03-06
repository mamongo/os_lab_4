#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#include "itoa.h"

//////////////////Sum func
char* sum(char* map){
    int a = atoi(map);
    if(a!=1){
        pid_t pid;
        int res, buff_a = a - 1;
        char *buff_map = map;
        int len = itoa(buff_a, buff_map); 
        pid = fork();
        if(pid > 0){    //Родитель
            wait(0);
            res = atoi(map) + a;
            itoa(res, map);
            return map;
        }
        else if(pid < 0){
        	write(STDERR_FILENO, "ERROR: fork\n", sizeof "ERROR: fork\n" - 1);
        	exit(EXIT_FAILURE);
        }
        else{   //Ребенок
            map = sum(map);
            exit(0);
        }
    }
    else
        return map;
}

int main()
{
    char *map;
    map = mmap(0, 17, PROT_READ | PROT_WRITE, MAP_SHARED |  MAP_ANONYMOUS, -1, 0);
    int n = 0;
    printf("Enter a sequence number: ");
    scanf("%d", &n);
    if(n<0 || n == 0)
        printf("You should give the number, which is more than zero and zero\n");
    else{
        printf("there\n");
        int len = itoa(n, map);
        printf("there\n");
        printf("%d\n", atoi(sum(map)));
    }
    return 0;
}
