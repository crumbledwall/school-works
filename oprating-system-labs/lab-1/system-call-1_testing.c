#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#define __NR_MYSETNICE 335

int main()
{
	int flag1, flag2, flag3, nicevalue1, nicevalue2, nicevalue3;
	int nice, prio;
	pid_t id;

	printf("请输入进程号：\n");
	scanf("%d", &id);
	
	printf("输入flag值和nicevalue值：");
	scanf("%d %d", &flag1, &nicevalue1);


	syscall(__NR_MYSETNICE, id, flag1, nicevalue1, &prio, &nice);
	printf("prio:%d, nice:%d\n", prio, nice);

	
	return 0;
}
