#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i = 0;
	int N;
	printf("N : ");
	scanf("%d", &N);
	while(i!=N)
	{
		system("./q_update_bot.sh");
		printf("Game Over\n");
		sleep(1);
		system("clear");
		i++;	
	}
	return 0;
}


