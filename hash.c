#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hash.h"
#include"list.h"


void createhash(struct hashtable**hasht, int L,int hashsize)
{
	int i,j;
	for(i=0;i<L;i++)
	{
		hasht[i] = malloc(hashsize*sizeof(struct hashtable));
		for(j=0;j<hashsize;j++)
		{
			hasht[i][j].lista=malloc(sizeof(struct list));
			hasht[i][j].lista->head=NULL;
		}
	}
}


