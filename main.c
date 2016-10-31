#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include <inttypes.h>
#include"hash.h"
#include"list.h"
#define bufSize 2048
#define bafSize 8192


unsigned long long turnintodecimal(unsigned long long bn)
{
	unsigned long long binaryNumber,decimalNumber=0,j=1,remainder;
	binaryNumber=bn;
	while(binaryNumber!=0)
	{
		remainder=binaryNumber%10;
		decimalNumber=decimalNumber+remainder*j;
		j=j*2;
		binaryNumber=binaryNumber/10;
    }
	return decimalNumber;
}

long int mod (long int a, long int b)
{
	if(b < 0) //you can check for b == 0 separately and do what you want
		return mod(a, -b);   
	long int ret = a % b;
	if(ret < 0)
		ret+=b;
	return ret;
}

int main(void)
{
	FILE* fp;
	int length,counter=0;
	char bufinteger[bufSize],buflen[bufSize],buf[bufSize];
	char *token;
	char *token2;	
	int k=4;//megethos hastable 2^k 
	int L=9;//arithmos hashtable
	long hashsize=2;
	int i,j,z,check,random;
	char token3[k],token4[k];
	unsigned long long binarynum,decimalnum,find,number;
	int ** gfun;
	unsigned long itemid;
	char * pitemid;
	double temp,ran,y1,y2,radius,nn;
	srand(time(NULL));
	for(i=1;i<k;i++)
	{
		hashsize*=2;
	}
	scanf("%d",&check);
	//Hamming
	if(check==0)
	{
		fp=fopen("DataHamming.csv","r");
		while (fscanf(fp, "%s", buflen) != EOF)//vazei sto length ton stoixion tou arxeiou
		{
			token=buflen; 
			if(token[0]=='0' || token[0]=='1')
			{
				length=strlen(token);
				break;
			}
		}
		fclose(fp);
		gfun=malloc(L*sizeof(int*));	
		for(i=0;i<L;i++)//kataskevazoyme ti sinartisi g
		{
			gfun[i]=malloc(k*sizeof(int));
			for(j=0;j<k;j++)
			{
				random=1+ (rand() /( RAND_MAX + 1.0))*(length-1);
				gfun[i][j]=random;
			}
			
		}
		struct hashtable ** hasht;
		hasht = malloc(L * sizeof(struct hashtable*));
		createhash(hasht,L,hashsize);
		fp=fopen("DataHamming.csv","r");
		while (fscanf(fp, "%s %s", buf,buflen) != EOF)
		{
			if(counter>0)
			{
				i=0;
				z=0;
				while(i<strlen(buf))
				{
					if(buf[i]>='0' && buf[i]<='9')
					{
						bufinteger[z]=buf[i];
						z++;
					}
					i++;
				}
				itemid=strtol(bufinteger,&pitemid,10);//vazw sto itemid long tous to id tou item(krataw mono tous arithmous ap to string
				number=strtoull(buflen,&token,2);//vazw sto number to long long tis akolouthias 0,1
				//printf("itemid%lu kai number %llu\n",itemid,number);
				//sleep(1);
				j=0;
				while(j<L)
				{
					for(i=0;i<k;i++)
					{
						token3[i]=buflen[gfun[j][i]];
					}
					binarynum=atoll(token3);//pairnei tin duadiki simvoloseira kai tin kanei typo long long int
					decimalnum=turnintodecimal(binarynum);//meta trepei to diadiko se dekadiko wste na paei sto swsto bucket
					insert(hasht[j][decimalnum].lista,number,itemid);
					j++;
				}
			}
			counter++;
		}
		fclose(fp);
		fp=fopen("QueryHamming.csv","r");
		fscanf(fp, "%s", buflen);
		fscanf(fp, "%s", buflen);
		radius=strtol(buflen,&pitemid,10);
		//printf("radius %f\n",radius);
		char bufint[bufSize];
		while (fscanf(fp, "%s %s", buf,buflen) != EOF)
		{
			i=0;
			z=0;
			while(i<strlen(buf))
			{
				if(buf[i]>='0' && buf[i]<='9')
				{
					bufint[z]=buf[i];
					z++;
				}
				i++;
			}
			itemid=strtol(bufint,&pitemid,10);//vazw sto itemid long tous to id tou item(krataw mono tous arithmous ap to string
			number=strtoull(buflen,&token,2);//vazw sto number to long long tis akolouthias 0,1
			printf("Query: item%lu\n",itemid);
			struct distlist * dilist;
			dilist =malloc(sizeof(struct distlist));//lista me apostaseis
			j=0;
			while(j<L)
			{
				for(i=0;i<k;i++)
				{
					token4[i]=buflen[gfun[j][i]];
				}
				binarynum=atoll(token4);
				decimalnum=turnintodecimal(binarynum);
				search(hasht[j][decimalnum].lista,number,itemid,dilist,length,0,L);//an exei radius 0 vriskei ta geitonika mono
				j++;
			}	
			printdistancelist(dilist,length);
			printf("Nearest neighbor: item\n");
			nn=findmin(dilist);
			printf("distanceLSH: %f\n",nn);
			free(dilist);
			dilist =malloc(sizeof(struct distlist));//lista me apostaseis
			dilist->head=NULL;
			for(j=0;j<hashsize;j++)
			{
				search(hasht[0][j].lista,number,itemid,dilist,length,0,-1);//L=-1 wste na min stamatisei i while sto search
			}
			nn=findmin(dilist);
			printf("distanceTrue: %f\n",nn);
			free(dilist);
		}
	}
//Cosine
	else if(check==1)
	{	
		char bufint[bufSize];
		struct hashtable ** hasht;
		hasht = malloc(L * sizeof(struct hashtable*));
		createhash(hasht,L,hashsize);
		struct distlist * dilist;
		double sum=0;
		double *** htable;
		double ** hfix;
		double * vector;
		fp=fopen("DataEuclidean.csv","r");
		i=0;
		counter=0;
		while (fscanf(fp, "%s", buflen) != EOF)//vazei sto length ton stoixion tou arxeiou
		{
			if(buflen[0]=='i' && buflen[1]=='t' && buflen[2]=='e' && buflen[3]=='m')
			{
				if(i==1)
				{
					counter--;
					break;
				}
				i++;
			}
			if(i!=0)
				counter++;
		}
		fclose(fp);
		hfix=malloc((k*L)*sizeof(double*));//vazw ta k*L h
		for(i=0;i<k*L;i++)
			hfix[i]=malloc(counter*sizeof(double));
		for(i=0;i<(k*L);i++)
		{
			for(j=0;j<counter;j++)
			{
				ran=2;
				while(ran>=1)
				{
					y1=-1+(rand()/(RAND_MAX +1.0))*(1+1);	
					y2=-1+(rand()/(RAND_MAX +1.0))*(1+1);	
					ran=(y1*y1) + (y2*y2);	
				}
				hfix[i][j]=sqrt((-2*log10(ran))/(ran)) * y1;
			}
		}
		gfun=malloc(L*sizeof(int*));	
		for(i=0;i<L;i++)//kataskevazoyme ti sinartisi g pou periexei ton arithmo tou h poy tha mpei se kathe g(px h1 h2 h3 h5)
		{
			gfun[i]=malloc(k*sizeof(int));
			for(j=0;j<k;j++)
			{
				random=1+ (rand() /( RAND_MAX + 1.0))*(L*k-1);
				gfun[i][j]=random;
				//printf("%d\n",random);
			}
			
		}
		htable=malloc(L *sizeof(double**));
		for(i=0;i<L;i++)
		{
			htable[i]=malloc(k*sizeof(double*));
			for(j=0;j<k;j++)
			{
				htable[i][j]=malloc(counter*sizeof(double));
			}
		}
		for(i=0;i<L;i++)
		{
			for(j=0;j<k;j++)
			{			
				htable[i][j]=hfix[gfun[i][j]];

			}
		}
		fp=fopen("DataEuclidean.csv","r");
		while (fscanf(fp, "%s", buflen) != EOF)//vazei sto length ton stoixion tou arxeiou
		{
			if(buflen[0]=='i' && buflen[1]=='t' && buflen[2]=='e' && buflen[3]=='m')
			{
				vector=malloc(counter*sizeof(double));
				i=0;
				z=0;
				while(i<strlen(buflen))
				{
					if(buflen[i]>='0' && buflen[i]<='9')
					{
						bufint[z]=buflen[i];
						z++;
					}
					i++;
				}
				itemid=strtol(bufint,&pitemid,10);
				for(z=0;z<counter;z++)
				{
					fscanf(fp, "%s", buflen);
					temp=atof(buflen);
					vector[z]=temp;
				}
				for(i=0;i<L;i++)
				{
					for(j=0;j<k;j++)
					{
						for(z=0;z<counter;z++)
						{
							sum+=htable[i][j][z] * vector[z];
						}
						if(sum>=0)
							token3[j]='1';
						else 
							token3[j]='0';
						sum=0;
					}
					binarynum=atoll(token3);
					decimalnum=turnintodecimal(binarynum);//thesi sto hastable pou tha mpei
					insertcosine(hasht[i][decimalnum].lista,vector,itemid,counter);
				}
				free(vector);
			}
		}
		fclose(fp);
		fp=fopen("QueryEuclidean.csv","r");
		fscanf(fp, "%s", buflen);
		fscanf(fp, "%s", buflen);
		radius=strtol(buflen,&pitemid,10);
		while (fscanf(fp, "%s", buflen) != EOF)//vazei sto length ton stoixion tou arxeiou
		{
			z=0;
			while(i<strlen(buflen))
			{
				if(buflen[i]>='0' && buflen[i]<='9')
				{
					bufinteger[z]=buflen[i];
					z++;
				}
				i++;
			}
			itemid=strtol(bufinteger,&pitemid,10);
			vector=malloc(counter*sizeof(double));
			for(i=0;i<counter;i++)
			{
				fscanf(fp, "%s", buflen);
				temp=strtod(buflen,&token);
				vector[i]=temp;	
			}
			dilist =malloc(sizeof(struct distlist));//lista me apostaseis
			dilist->head=NULL;
			sum=0;
			for(i=0;i<L;i++)
			{
				for(j=0;j<k;j++)
				{
					for(z=0;z<counter;z++)
					{
						sum+=htable[i][j][z] * vector[z];
					}
					if(sum>=0)
						token4[j]='1';
					else 
						token4[j]='0';
					sum=0;
				}
				binarynum=atoll(token4);
				decimalnum=turnintodecimal(binarynum);//thesi sto hastable pou tha mpei
				//printf("paw sti thesi %llu\n",decimalnum);
				//sleep(2);
				if(hasht[i][decimalnum].lista->head==NULL) printf("adeia lista\n");
				else searchcosine(hasht[i][decimalnum].lista,vector,itemid,dilist,counter,0,L);
				//sleep(2);
			}
			free(vector);
			printf("Query: %lu\n",itemid);
			printdistancelistcosine(dilist);
			printf("Nearest neighbor: item\n");
			nn=findmin(dilist);
			printf("distanceLSH %f \n",nn);
			free(dilist);
			dilist =malloc(sizeof(struct distlist));//lista me apostaseis
			dilist->head=NULL;
			for(j=0;j<hashsize;j++)
			{
				searchcosine(hasht[0][j].lista,vector,itemid,dilist,counter,0,-1);//L=-1 wste na min stamatisei i while sto search
			}
			nn=findmin(dilist);
			printf("distanceTrue %f \n",nn);			
			free(dilist);
		}
	}
	//////////
	else if(check==2)
	{	
		char bufint[bufSize];
		double t,w=4.0,sum;
		double *tfix,**vfix,*vector;;
		int *rfix;
		int fsum,fid;
		long modnum=1,itemcounter=0,idfind;
		
		for(i=0;i<32;i++)
			modnum*=2;
		modnum=modnum-5;
		fp=fopen("DataEuclidean.csv","r");
		i=0;
		counter=0;
		while (fscanf(fp, "%s", buflen) != EOF)//vazei sto length ton stoixion tou arxeiou
		{
			if(buflen[0]=='i' && buflen[1]=='t' && buflen[2]=='e' && buflen[3]=='m')
			{
				if(i==1)
				{
					counter--;
					break;
				}
				i++;
			}
			if(i!=0)
				counter++;
		}
		fclose(fp);
		fp=fopen("DataEuclidean.csv","r");
		while (fgets(buflen, sizeof(buflen), fp) != NULL)
		{
			if(buflen[0]=='i' && buflen[1]=='t' && buflen[2]=='e' && buflen[3]=='m')
				itemcounter++;
					
		}
		fclose(fp);
		hashsize=itemcounter/16;
		struct hashtable ** hasht;
		hasht = malloc(L * sizeof(struct hashtable*));
		createhash(hasht,L,hashsize);
		struct distlist * dilist;
		gfun=malloc(L*sizeof(int*));	
		for(i=0;i<L;i++)//kataskevazoyme ti sinartisi g pou periexei ton arithmo tou h poy tha mpei se kathe g(px h1 h2 h3 h5)
		{
			gfun[i]=malloc(k*sizeof(int));
			for(j=0;j<k;j++)
			{
				random=(rand() /( RAND_MAX + 1.0))*(L*k);
				gfun[i][j]=random;
			}
			
		}
		vfix=malloc(k*L*sizeof(double*));
		tfix=malloc(k*L*sizeof(double));
		for(i=0;i<k*L;i++)
		{		
			vfix[i]=malloc(counter*sizeof(double));
		}
		for(i=0;i<k*L;i++)
		{
			tfix[i]=(rand() /( RAND_MAX + 1.0))*w;	//t tou kathe h
			//printf("%f\n",tfix[i]);
			for(j=0;j<counter;j++)
			{
				ran=2;
				while(ran>=1)
				{
					y1=-1+(rand()/(RAND_MAX +1.0))*(1+1);	
					y2=-1+(rand()/(RAND_MAX +1.0))*(1+1);	
					ran=(y1*y1) + (y2*y2);	
				}
				vfix[i][j]=sqrt((-2*log10(ran))/(ran)) * y1;//to v tou kathe h
			}
		}
		rfix=malloc(k*sizeof(int));// k*L isws
		for(i=0;i<k;i++)
		{
			rfix[i]=1+(rand() /( RAND_MAX + 1.0))*128;
		}
		fp=fopen("DataEuclidean.csv","r");
		while (fscanf(fp, "%s", buflen) != EOF)
		{
			if(buflen[0]=='i' && buflen[1]=='t' && buflen[2]=='e' && buflen[3]=='m')
			{
				vector=malloc(counter*sizeof(double));
				i=0;
				z=0;
				while(i<strlen(buflen))
				{
					if(buflen[i]>='0' && buflen[i]<='9')
						{
							bufint[z]=buflen[i];
							z++;
						}
					i++;
				}
				itemid=strtol(bufint,&pitemid,10);
				for(z=0;z<counter;z++)
				{
					fscanf(fp, "%s", buflen);
					temp=atof(buflen);
					vector[z]=temp;
				}
				for(i=0;i<L;i++)
				{
					fsum=0;
					for(j=0;j<k;j++)
					{
						sum=0;
						for(z=0;z<counter;z++)
						{
							
							sum=vector[z] * vfix[gfun[i][j]][z];
						}
						
						sum=(sum+tfix[gfun[i][j]])/w;
						sum=floor(sum);
						fsum+=rfix[j]*sum;
					}
					idfind=mod(fsum,modnum);
					inserteuclidian(hasht[i][mod(idfind,hashsize)].lista,vector,itemid,idfind,counter);
				}
				free(vector);
			}
		}
		fclose(fp);
		fp=fopen("QueryEuclidean.csv","r");
		fscanf(fp, "%s", buflen);
		fscanf(fp, "%s", buflen);
		radius=strtol(buflen,&pitemid,10);
		while (fscanf(fp, "%s", buflen) != EOF)//vazei sto length ton stoixion tou arxeiou
		{
			z=0;
			while(i<strlen(buflen))
			{
				if(buflen[i]>='0' && buflen[i]<='9')
				{
					bufinteger[z]=buflen[i];
					z++;
				}
				i++;
			}
			itemid=strtol(bufinteger,&pitemid,10);
			vector=malloc(counter*sizeof(double));
			for(i=0;i<counter;i++)
			{
				fscanf(fp, "%s", buflen);
				temp=strtod(buflen,&token);
				vector[i]=temp;	
			}	
			dilist =malloc(sizeof(struct distlist));//lista me apostaseis
			dilist->head=NULL;
			for(i=0;i<L;i++)
			{
				fsum=0;
				for(j=0;j<k;j++)
				{
					sum=0;
					for(z=0;z<counter;z++)
					{
				
						sum=vector[z] * vfix[gfun[i][j]][z];
					}
			
					sum=(sum+tfix[gfun[i][j]])/w;
					sum=floor(sum);
					fsum+=rfix[j]*sum;
				}
				idfind=mod(fsum,modnum);
				searcheuclidian(hasht[i][mod(idfind,hashsize)].lista,vector,itemid,idfind,dilist,counter,0,L);
			}
			free(vector);
			printf("Query: %lu\n",itemid);
			printdistancelisteuclidian(dilist);
			printf("Nearest neighbor: item\n");
			nn=findmin(dilist);
			printf("distanceLSH: %f \n",nn);
			//sleep(2);
			free(dilist);
			dilist =malloc(sizeof(struct distlist));//lista me apostaseis
			dilist->head=NULL;
			fsum=0;
			for(j=0;j<k;j++)
			{
				sum=0;
				for(z=0;z<counter;z++)
				{
			
					sum=vector[z] * vfix[gfun[0][j]][z];
				}
		
				sum=(sum+tfix[gfun[0][j]])/w;
				sum=floor(sum);
				fsum+=rfix[j]*sum;
			}
			idfind=mod(fsum,modnum);
			for(i=0;i<hashsize;i++)
				{if(hasht[0][i].lista->head!=NULL)
					searcheuclidian(hasht[0][i].lista,vector,itemid,idfind,dilist,counter,0,-1);}
			nn=findmin(dilist);
			printf("distanceTrue %f \n",nn);
			free(dilist);
		}
		fclose(fp);
	}
	else if(check==3)
	{
		char baflen[bafSize],bufint[bufSize];
		char * tok;
		int readcount=0,columns=0;
		double sum=0,summid=0;
		double ** matrix,** querymatr;
		int ** hmat,**gfun;
		double * tmat;
		struct hashtable ** hasht;
		hasht = malloc(L * sizeof(struct hashtable*));
		createhash(hasht,L,hashsize);
		struct distlist * dilist;
		const char s[2] = ",";
		
		fp=fopen("DistanceMatrix.csv","r");
		fscanf(fp, "%s", baflen);
		fscanf(fp, "%s", baflen);
		fscanf(fp, "%s", baflen);
		fscanf(fp, "%s", baflen);
		tok = strtok (baflen,s);
		//printf ("%s\n",tok);
		while (tok != NULL)
		{
			//printf ("%s\n",tok);
			tok = strtok (NULL, s);
			counter++;
  		}
		fclose(fp);	
		matrix=malloc(counter*sizeof(double*));
		for(i=0;i<counter;i++)
		{
			matrix[i]=malloc(counter*sizeof(double));		
		}
		fp=fopen("DistanceMatrix.csv","r");
		fscanf(fp, "%s", baflen);
		fscanf(fp, "%s", baflen);
		fscanf(fp, "%s", baflen);
		fscanf(fp, "%s", baflen);
		readcount=0;
		i=0;
		j=0;
		while(fscanf(fp, "%s", baflen)!=EOF)
		{
			matrix[i][j]=atof(baflen);
			readcount++;
			j++;
			if(readcount==counter)
			{
				readcount=0;
				i++;
				j=0;
			}
		}

		hmat=malloc(k*L*sizeof(int*));
		tmat=malloc(k*L*sizeof(double));
		for(i=0;i<k*L;i++)
		{
			hmat[i]=malloc(2*sizeof(int));		
		}
		gfun=malloc(L*sizeof(int*));
		for(i=0;i<L;i++)
		{
			gfun[i]=malloc(k*sizeof(int));
			for(j=0;j<k;j++)
			{
				gfun[i][j]=(rand() /( RAND_MAX + 1.0))*(L*k);
			}
		}
		for(i=0;i<k*L;i++)
		{
				hmat[i][0]=1+(rand() /( RAND_MAX + 1.0))*(counter);
				hmat[i][1]=1+(rand() /( RAND_MAX + 1.0))*(counter);
				while(hmat[i][0]==hmat[i][1])
				{
					hmat[i][1]=1+(rand() /( RAND_MAX + 1.0))*(counter);
				}
		}
		for(i=0;i<k*L;i++)
		{
			summid=0;
			for(j=0;j<counter;j++)
			{
				sum=0;
				sum+=matrix[j][hmat[i][0]]*matrix[j][hmat[i][0]];
				sum+=matrix[j][hmat[i][1]]*matrix[j][hmat[i][1]];
				sum-=matrix[hmat[i][0]][hmat[i][1]]*matrix[hmat[i][0]][hmat[i][1]];
				sum=sum/(2*matrix[hmat[i][0]][hmat[i][1]]);
				summid+=sum;
			}
			tmat[i]=summid/counter;
			//printf("skakrak %f\n",tmat[i]);
		}

		for(z=0;z<L;z++)
		{
			for(j=0;j<counter;j++)
			{
				for(i=0;i<k;i++)
				{
					sum=0;
					sum+=matrix[j][hmat[gfun[z][i]][0]]*matrix[j][hmat[gfun[z][i]][0]];
					sum+=matrix[j][hmat[gfun[z][i]][1]]*matrix[j][hmat[gfun[z][i]][1]];
					sum-=matrix[hmat[gfun[z][i]][0]][hmat[gfun[z][i]][1]]*matrix[hmat[i][0]][hmat[gfun[z][i]][1]];
					sum=sum/(2*matrix[hmat[gfun[z][i]][0]][hmat[gfun[z][i]][1]]);
					if(sum>=tmat[gfun[z][i]])
						token3[i]='1';
					else 
						token3[i]='0';				
				}
				binarynum=atoll(token3);//pairnei tin duadiki simvoloseira kai tin kanei typo long long int
				decimalnum=turnintodecimal(binarynum);//meta trepei to diadiko se dekadiko wste na paei sto swsto bucket
				itemid=j+1;
				insertcosine(hasht[z][decimalnum].lista,matrix[j],itemid,counter);
			}	
		}
		fp=fopen("QueryDistanceMatrix.csv","r");
		columns=-1;
 		while (fgets(baflen, sizeof(baflen), fp) != NULL)
			columns++;
		fclose(fp);
		querymatr=malloc(columns*sizeof(double*));
		for(i=0;i<counter;i++)
		{
			querymatr[i]=malloc(counter*sizeof(double));		
		}	
		fp=fopen("QueryDistanceMatrix.csv","r");
		fscanf(fp, "%s", baflen);
		fscanf(fp, "%s", baflen);
		radius=strtol(baflen,&pitemid,10);
		readcount=0;
		while (fscanf(fp, "%s", baflen) != EOF)
		{
			z=0;
			
			i=0;
			while(i<strlen(baflen))
			{
				if(baflen[i]>='0' && baflen[i]<='9')
				{
					bufinteger[z]=baflen[i];
					z++;
				}
				i++;
			}
			//printf("bufint %s  buflen %s z %d \n",bufint,buflen,z);
			itemid=strtol(bufinteger,&pitemid,10);
			//printf("buf  %s bufint  %s utem %lu\n",baflen,bufinteger,itemid);
			for(i=0;i<counter;i++)
			{
				fscanf(fp, "%s", baflen);
				//printf("%s\n",buflen);
				temp=strtod(baflen,&token);
				querymatr[readcount][i]=temp;
				//printf("%f\n",temp);	
			}
			readcount++;
			//printf("%d readcount\n",readcount);
		}		
		for(j=0;j<columns;j++)
		{
			dilist =malloc(sizeof(struct distlist));//lista me apostaseis
			dilist->head=NULL;
			for(z=0;z<L;z++)
			{
				for(i=0;i<k;i++)
				{
					sum=0;
					sum+=querymatr[j][hmat[gfun[z][i]][0]]*querymatr[j][hmat[gfun[z][i]][0]];
					sum+=querymatr[j][hmat[gfun[z][i]][1]]*querymatr[j][hmat[gfun[z][i]][1]];
					sum-=matrix[hmat[gfun[z][i]][0]][hmat[gfun[z][i]][1]]*matrix[hmat[i][0]][hmat[gfun[z][i]][1]];
					sum=sum/(2*matrix[hmat[gfun[z][i]][0]][hmat[gfun[z][i]][1]]);
					if(sum>=tmat[gfun[z][i]])
						token4[i]='1';
					else 
						token4[i]='0';				
				}
				binarynum=atoll(token4);//pairnei tin duadiki simvoloseira kai tin kanei typo long long int
				decimalnum=turnintodecimal(binarynum);//meta trepei to diadiko se dekadiko wste na paei sto swsto bucket
				itemid=j+1;
				searchmatrix(hasht[z][decimalnum].lista,querymatr,itemid,dilist,counter,0,-1);
				
			}	

			printf("Query: item%lu\n",itemid);
			printdistancelisteuclidian(dilist);
			printf("Nearest neighbor: item\n");
			nn=findmin(dilist);
			printf("distanceLSH: %f\n",nn);
			//sleep(2);
			free(dilist);

		}
		for(i=0;i<columns;i++)
		{
			dilist =malloc(sizeof(struct distlist));//lista me apostaseis
			dilist->head=NULL;
			for(j=0;j<hashsize;j++)
			{
				itemid=i+1;
				searchmatrix(hasht[0][j].lista,querymatr,itemid,dilist,counter,0,-1);
			}
			nn=findmin(dilist);
			printf("distanceTrue: %f\n",nn);			
			free(dilist);
		}
		fclose(fp);
	}
}
