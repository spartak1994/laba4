#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include "time.h"
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
void getTime(struct tm **time_f)
{
time_t sec;
time(&sec);
*time_f = localtime(&sec);
}

int main()
{
struct tm *time;
struct tm *new_time;
getTime(&time);
char* file_name[16]={"fifo.dat"};
int pid,is_open,died,status; 
int fifo=mknod(file_name, 0777,0);
if(fifo==0)printf("FIFO создан\n");
if(fifo<0)printf("Ошибка создания FIFO\n");
is_open=open(file_name, O_RDONLY,0004);
printf("is_open=%d\n",is_open);
if(is_open!=-1)
printf("Открыло на чтение в родительском процессе\n");
if(is_open==-1)printf("Ошибка открытия на чтение\n");
//wait(&status);
pid=fork();
wait(&status);
//в дочернем процессе
is_open=open(file_name, O_WRONLY,0002);
printf("Открыло на запись в дочернем процессе\n");
if(is_open==-1)printf("Ошибка открытия на запись\n");
write(is_open, time, sizeof(struct tm));
printf("Записало %d байт\n",is_open);
exit(0);
//Снова в родительском
read(is_open,new_time,sizeof(struct tm));
printf("Time from FIFO: %d:%d:%d\n",new_time->tm_hour, new_time->tm_min, new_time->tm_sec);
exit(0);
return 0;
}
