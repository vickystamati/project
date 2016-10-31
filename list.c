#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"hash.h"
#include"list.h"

void search(struct list *lista,unsigned long long find,unsigned long idfind,struct distlist * dilist,int length,double radius,int L)
{
	struct distnode * new;
	char * chbin,* incur;//binary ws simvoloseira
	chbin=malloc(length+1);
	turnintobinary(find,length,chbin);
	int i,loop=0;
	double d;
	struct node *current = lista->head;
	if(radius==0)
	{
		new = malloc(sizeof(struct distnode));
		new->distance=length+1;//paradoxi, max+1 diaforetika
		new->next=NULL;
		while (current!= NULL && loop!=3*L) //isws thelei current->next
		{
			if(current->id==idfind) 
			{
				current = current->next;
				continue;
			}
			incur=malloc(length+1);
			turnintobinary(current->key,length,incur);
			//printf("incur %s",incur);
			d=0;
			for(i=0;i<length;i++)
			{
				//printf("---paei na sighrinei %c me %c\n",incur[i],chbin[i]);
				if(incur[i]!=chbin[i])
				{
					d++;
				}
			}
			if(d<new->distance)//einai i mikroteri ekeini ti stigmi
			{
				new->nearid=current->id;
				new->nearkey=current->key;
				new->distance=d;
			}
			current = current->next;
			free(incur);
		}
		free(chbin);
		//printf("THA MPEI STO DILIST1: item%lu with id :%llu  d=%f\n",new->nearid,new->nearkey,new->distance);
		if(new->distance!=length+1)
			insertnear(dilist,new);
	}
	else
	{
		while (current!= NULL && loop!=3*L) //isws thelei current->next
		{
			if(current->id==idfind) 
			{
				current = current->next;
				continue;
			}
			incur=malloc(length+1);
			turnintobinary(current->key,length,incur);
			//printf("incur %s",incur);
			d=0;
			for(i=0;i<length;i++)
			{
				if(incur[i]!=chbin[i])
				{
					d++;
				}
			}
			//printf("ekana sigkrisi kai to d einai= %f\n",d);
			if(d<=radius)
			{
				new = malloc(sizeof(struct distnode));
				//new->distance=length+1;//paradoxi, max+1 diaforetika
				new->next=NULL;
				new->nearid=current->id;
				new->nearkey=current->key;
				new->distance=d;
				//printf("THA MPEI STO DILIST2: item%lu with id :%llu  d=%f\n",new->nearid,new->nearkey,new->distance);
				insertnear(dilist,new);
			}
			current = current->next;
			free(incur);
		}
		free(chbin);		
	}	
}

double findmin(struct distlist * dilist)
{
	struct distnode *new=malloc(sizeof(struct distnode));
	struct distnode *current = dilist->head;
	int min;
	if(current!=NULL)
	{
		min=current->distance+1;
		while (current!= NULL) //isws thelei current->next
		{
			if(min>current->distance)//einai i mikroteri ekeini ti stigmi
			{
				new->nearid=current->nearid;
				new->nearkey=current->nearkey;
				new->distance=current->distance;
				min=current->distance;
			}
			current = current->next;
		}
		return new->distance;
		//printf("distanceTrue: %f\n",new->distance);
		free(new);
	}
	else
		printf("Empty list at findmin\n");
}

void printlist(struct list * lista)
{
	struct node* temp;
	temp = lista->head;
	if(lista->head==NULL)
	{
		printf("Empty List\n");
	}
	while(temp!=NULL)
	{
		temp = temp->next;
	}
}

void printdistancelist(struct distlist * lista,int length)
{
	struct distnode* temp;
	char *token;
	temp = lista->head;
	if(temp==NULL)
	{
		printf("Empty List\n");
	}
	else
	{	printf("R-near neighbors: \n");
		while(temp!=NULL)
		{
			
			token=malloc(length+1);
			turnintobinary(temp->nearkey,length,token);
			printf("item%lu\n",temp->nearid);
			free(token);
			temp = temp->next;
		}
	}
}



void insertnear(struct distlist * dlist,struct distnode * new)
{
	
	if (dlist->head == NULL)
	{
		dlist->head = malloc(sizeof(struct distnode));
		dlist->head=new;
		dlist->head->next=NULL;	
		//printf("mpika head minimm einai: %lu %f\n",dlist->head->nearid,dlist->head->distance);		
	}
	else
	{
		struct distnode *current = dlist->head;
		while (current->next != NULL) 
		{
			current = current->next;
		}
		//current->next = malloc(sizeof(struct distnode));
		current->next = new;
		current->next->next=NULL;
		//printf("mpika body minimm einai: %lu %f\n",current->nearid,current->distance);		
	}
}

void insert(struct list * lista,unsigned long long binary,unsigned long itemid)
{
	struct node * new;
	new = malloc(sizeof(struct node));
	if(new == NULL)
	{
		printf("Failed to allocate memory!\n");
	}
	new -> id=itemid;
	new -> key =binary;
	new -> next = NULL;
	if (lista->head == NULL)
	{
		lista->head = malloc(sizeof(struct node));
		lista->head=new;
		lista->head->next=NULL;	
	}
	else
	{
		struct node *current = lista->head;
		while (current->next != NULL) 
		{
			current = current->next;
		}
		current->next = new;
	}	
}

void turnintobinary(unsigned long long dn,int length,char* token)
{
	int i,k,count=0;
	char binarray[length+1];
	for (i = length-1; i >= 0; i--)
	{
		k = dn >> i;
 
		if (k & 1)
			binarray[count]='1';
		else
			binarray[count]='0';
		count++;
	}
	binarray[length]='\0';
	strcpy(token,binarray);
}

void insertcosine(struct list *lista,double * vector,unsigned long itemid,int counter)
{
	int i;
	struct node * new;
	new = malloc(sizeof(struct node));
	if(new == NULL)
	{
		printf("Failed to allocate memory!\n");
	}
	new -> id=itemid;
	//printf("inserted id: %lu\n",new->id);
	new -> key1 =malloc(counter*sizeof(double));
	for(i=0;i<counter;i++)
	{	
		new->key1[i]=vector[i];
		//printf("inserted: %f\n",vector[i]);
	}
	new -> next = NULL;
	if (lista->head == NULL)
	{
		lista->head = malloc(sizeof(struct node));
		lista->head=new;
		lista->head->next=NULL;	
	}
	else
	{
		struct node *current = lista->head;
		while (current->next != NULL) 
		{
			current = current->next;
		}
		current->next = new;
	}	
}

void searchcosine(struct list *lista,double* find,unsigned long idfind,struct distlist * dilist,int counter,double radius,int L)
{
	struct distnode * new;
	int i;
	double d,sum,sum1,sum2;
	int loop=0;
	struct node *current = lista->head;
	if(radius==0)
	{
		new = malloc(sizeof(struct distnode));
		new->distance=counter+1;//paradoxi, max+1 diaforetika
		new->next=NULL;
		while (current!= NULL && loop!=3*L) //isws thelei current->next
		{
			if(current->id==idfind) 
			{
				current = current->next;
				continue;
			}
			sum=0,sum1=0,sum2=0;
			for(i=0;i<counter;i++)
			{
				sum+=current->key1[i] * find[i];
				sum1+=current->key1[i] * current->key1[i];
				sum2+=find[i] * find[i];
			}
			
			loop++;
			if(sum1!=0 && sum2!=0)
			{
				d=1-(sum/sqrt(sum1 * sum2));
				if(d<new->distance)//einai i mikroteri ekeini ti stigmi
				{
					new->nearid=current->id;
					new->distance=d;
				}
			}
			current = current->next;
		}
		if(new->distance!=counter+1)
			insertnear(dilist,new);
	}
	else
	{
		while (current!= NULL && loop!=3*L) //isws thelei current->next
		{
			if(current->id==idfind) 
			{
				current = current->next;
				continue;
			}
			sum=0,sum1=0,sum2=0;
			for(i=0;i<counter;i++)
			{
				sum+=current->key1[i] * find[i];
				sum1+=current->key1[i] * current->key1[i];
				sum2+=find[i] * find[i];
			}
			loop++;
			//printf("%.10f %.10f %.10f\n",sum,sum1,sum2);
			if(sum1!=0 && sum2!=0)
			{
				//printf("%.10f %.10f %.10f\n",sum,sum1,sum2);
				
				d=1-(sum/sqrt(sum1 * sum2));
				if(d<=radius)//einai i mikroteri ekeini ti stigmi
				{
					new = malloc(sizeof(struct distnode));
					//new->distance=length+1;//paradoxi, max+1 diaforetika
					new->next=NULL;
					new->nearid=current->id;
					new->distance=d;
					//printf("THA MPEI STO DILIST2: item%lu d=%f\n",new->nearid,new->distance);
					//sleep(2);
					insertnear(dilist,new);
				}
			}
			current = current->next;
		}		
	}
}
void printdistancelistcosine(struct distlist * lista)
{
	struct distnode* temp;
	temp = lista->head;
	if(temp==NULL)
	{
		printf("Empty List\n");
	}
	else
	{
		while(temp!=NULL)
		{
			printf("item %lu minD= %f\n",temp->nearid,temp->distance);
			temp = temp->next;
		}
	}
}

void inserteuclidian(struct list * lista,double *vector, long itemid,long id,int counter)
{
	int i;
	struct node * new;
	new = malloc(sizeof(struct node));
	if(new == NULL)
	{
		printf("Failed to allocate memory!\n");
	}
	new -> id=itemid;
	new -> key1 =malloc(counter*sizeof(double));
	new -> findid=id;
	for(i=0;i<counter;i++)
	{	
		new->key1[i]=vector[i];
	}
	new -> next = NULL;
	if (lista->head == NULL)
	{
		lista->head = malloc(sizeof(struct node));
		lista->head=new;
		lista->head->next=NULL;	
	}
	else
	{
		struct node *current = lista->head;
		while (current->next != NULL) 
		{
			current = current->next;
		}
		current->next = new;
	}	
	//printf("mpike mesa id %ld findid %ld\n",new->id,new->findid);
}

void searcheuclidian(struct list *lista,double* find,long id,long idfind,struct distlist * dilist,int counter,double radius,int L)
{
	struct distnode * new;
	int i;
	double d,sum,sum2;
	int loop=0;
	struct node *current = lista->head;
	if(current->findid==idfind || L<0)
	{
		if(radius==0)
		{	
			new = malloc(sizeof(struct distnode));
			new->distance=100000000;//paradoxi
			new->next=NULL;
			while (current!= NULL && loop!=3*L) //isws thelei current->next
			{
				if(current->id==id) 
				{
					current = current->next;
					continue;
				}
				//printf("%ld %ld\n",current->id,idfind);
				sum=0;
				sum2=0;
				for(i=0;i<counter;i++)
				{
					//printf("currnet id %ld\n",current->id);
					sum=current->key1[i] - find[i];
					//printf("sum%f curr%f find%f\n",sum,current->key1[i],find[i]);
					sum=sum*sum;
					sum2+=sum;
					sum=0;
					//printf("sum sto tetra %f\n",sum2);
			
				}
				d=sqrt(sum2);
				loop++;
				//printf("d=%f\n",d);
				//sleep(2);
				if(d<new->distance)//einai i mikroteri ekeini ti stigmi
				{
					new->nearid=current->id;
					new->distance=d;
				}
				current = current->next;
			}
			if(new->distance!=100000000)
				insertnear(dilist,new);
			//printf("minimum apostasi %f\n",d);
		}
		else
		{
			while (current!= NULL && loop!=3*L) //isws thelei current->next
			{
				if(current->id==id) 
				{
					current = current->next;
					continue;
				}
				sum=0;
				sum2=0;
				for(i=0;i<counter;i++)
				{
					sum+=current->key1[i] - find[i];
					sum=sum*sum;
					sum2+=sum;
					sum=0;
				}
				d=sqrt(sum2);
				loop++;
				if(d<=radius)//einai i mikroteri ekeini ti stigmi
				{
					new = malloc(sizeof(struct distnode));
					new->next=NULL;
					new->nearid=current->id;
					new->distance=d;
					insertnear(dilist,new);
				}
				current = current->next;
			}		
		}
	}
}
void printdistancelisteuclidian(struct distlist * lista)
{
	struct distnode* temp;
	temp = lista->head;
	if(temp==NULL)
	{
		printf("Empty List\n");
	}
	else
	{
		while(temp!=NULL)
		{
			printf("item%lu\n",temp->nearid);
			temp = temp->next;
		}
	}
}
void searchmatrix(struct list*lista,double ** find,long itemid,struct  distlist * dilist, int counter,double radius,int L)
{
	struct distnode * new;
	int i;
	double d;
	int loop=0;
	struct node *current = lista->head;
	if(radius==0)
	{
		new = malloc(sizeof(struct distnode));
		new->distance=counter+1;//paradoxi, max+1 diaforetika
		new->next=NULL;
		while (current!= NULL && loop!=3*L) //isws thelei current->next
		{
			if(current->id==itemid) 
			{
				current = current->next;
				continue;
			}
			loop++;
			d=find[itemid-1][current->id-1];
			if(d<new->distance && d!=0)//einai i mikroteri ekeini ti stigmi
			{
				new->nearid=current->id;
				new->distance=d;
			}
			current = current->next;
			//sleep(2);
		}
		if(new->distance!=counter+1)
			insertnear(dilist,new);
	}
	else
	{
		while (current!= NULL && loop!=3*L) //isws thelei current->next
		{
			if(current->id==itemid) 
			{
				current = current->next;
				continue;
			}
			loop++;
			d=find[itemid-1][current->id-1];
			if(d<=radius && d!=0)//einai i mikroteri ekeini ti stigmi
			{
				new = malloc(sizeof(struct distnode));
				//new->distance=length+1;//paradoxi, max+1 diaforetika
				new->next=NULL;
				new->nearid=current->id;
				new->distance=d;
				//printf("THA MPEI STO DILIST2: item%lu d=%f\n",new->nearid,new->distance);
				//sleep(2);
				insertnear(dilist,new);
			}
			current = current->next;
		}		
	}
}
