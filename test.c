#include<stdio.h>

void doublicate(void ** a)
{
	a=2*(int)a;
}

int main(void)
{
	int k;
	double m;
	k=2;
	m=4.0;
	doublicate(&k);
	//doublicate(m);
	printf("%d\n",k);
	//printf("%f\n",&m);

}
