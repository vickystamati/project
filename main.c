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

void bubble_sort(double* matr, int counter)
{
	double t;
	int i,j;
	for (i=0;i<(counter-1);i++)
	{
		for (j=0;j<counter-i-1;j++)
		{
			if (matr[j] > matr[j+1])
			{
				t = matr[j];
				matr[j] = matr[j+1];
				matr[j+1] = t;
			}
		}
	}
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

int main(int argc, char *argv[])
{
	FILE* fp;
	FILE* fpw;
	struct hashtable ** hasht;
	struct distlist * dilist;
	char baflen[bafSize];
	char * tok;
	char newfilename[30];
	int readcount=0,columns=0;
	int idcounter;
	long * matrid;
	double **summid;
	double ** matrix,** querymatr;
	int ** hmat,**gfun;
	double * tmat;
	const char s[2] = ",";
	double sum=0;
	double *** htable;
	double ** hfix;
	double w=4.0;
	double *tfix,**vfix,*vector;
	int *rfix;
	int fsum;
	long modnum=1,itemcounter=0,idfind;
	int length,counter=0;
	char bufinteger[bufSize],buflen[bufSize],buf[bufSize],bufint[bufSize];
	char *token;	
	char *dfile;
	char *qfile;
	char *ofile;
	int k=4;//megethos hastable 2^k 
	int L=5;//arithmos hashtable
	long hashsize=2;
	int i,j,z,check,random;
	char token3[k],token4[k];
	unsigned long long binarynum,decimalnum,number;
	unsigned long itemid;
	char * pitemid;
	double temp,ran,y1,y2,radius;
	double time_spentbr,time_spentlsh,time_spent;
	clock_t beginlsh,endlsh,beginbr,endbr,end,begin;
	srand(time(NULL));


	if(argc==11)
	{
		if(strcmp(argv[1],"-d")==0)
		{
			dfile=(argv[2]);
			if ((fp = fopen((dfile), "r")) != NULL)
			{
				fscanf(fp, "%s", buflen);
				fscanf(fp, "%s", buflen);
				if((strcmp(buflen,"vector")==0) || strcmp(buflen,"euclidean")==0)
				{
					fscanf(fp, "%s", buflen);
					fscanf(fp, "%s", buflen);
					if((strcmp(buflen,"cosine")==0))
						check=1;
					else
						check=2;
					
				}
				else if(strcmp(buflen,"hamming")==0)
					check=0;
				else if(strcmp(buflen,"matrix")==0)
					check=3;
				else
				{
					printf("Wrong file structure!\n");
					return 0;
				}						
			}
			else
				return 0;
			fclose(fp);
		}
		else
		{
			printf("Wrong argument!\n");
			return 0;
		}
		if(strcmp(argv[3],"-q")==0)
		{
			qfile=argv[4];
		}
		else
		{
			printf("Wrong argument!\n");
			return 0;
		}
		if(strcmp(argv[5],"-k")==0)
		{
			k=atoi(argv[6]);
		}
		else
		{
			printf("Wrong argument!\n");
			return 0;
		}
		if(strcmp(argv[7],"-L")==0)
		{
			L=atoi(argv[8]);
		}
		else
		{
			printf("Wrong argument!\n");
			return 0;
		}
		if(strcmp(argv[9],"-o")==0)
		{
			ofile=argv[10];
			fpw=fopen(ofile, "w");
		}
		else
		{
			printf("Wrong argument!\n");
			return 0;
		}
	}
	else if(argc==9)
	{
		if(strcmp(argv[1],"-d")==0)
		{
			dfile=(argv[2]);
			if ((fp = fopen((dfile), "r")) != NULL)
			{
				fscanf(fp, "%s", buflen);
				fscanf(fp, "%s", buflen);
				if((strcmp(buflen,"vector")==0) || strcmp(buflen,"euclidean")==0)
				{
					fscanf(fp, "%s", buflen);
					fscanf(fp, "%s", buflen);
					if((strcmp(buflen,"cosine")==0))
						check=1;
					else
						check=2;
					
				}
				else if(strcmp(buflen,"hamming")==0)
					check=0;
				else if(strcmp(buflen,"matrix")==0)
					check=3;
				else
				{
					printf("Wrong file structure!\n");
					return 0;
				}						
			}
			else
				return 0;
		fclose(fp);
		}
		else
		{
			printf("Wrong argument!\n");
			return 0;
		}
		if(strcmp(argv[3],"-q")==0)
		{
			qfile=(argv[4]);
		}
		else
		{
			printf("Wrong argument!\n");
			return 0;
		}
		if(strcmp(argv[5],"-k")==0)
		{
			k=atoi(argv[6]);		
		}
		else if(strcmp(argv[5],"-L")==0)
		{
			L=atoi(argv[6]);		
		}
		else
		{
			printf("Wrong argument!\n");
			return 0;
		}
		if(strcmp(argv[7],"-o")==0)
		{
			ofile=argv[8];
			fpw=fopen(ofile, "w");
		}
		else
		{
			printf("Wrong argument!\n");
			return 0;
		}
	}
	else if(argc==7)
	{
		if(strcmp(argv[1],"-d")==0)
		{
			dfile=(argv[2]);
			if ((fp = fopen((dfile), "r")) != NULL)
			{
				fscanf(fp, "%s", buflen);
				fscanf(fp, "%s", buflen);
				if((strcmp(buflen,"vector")==0) || strcmp(buflen,"euclidean")==0)
				{
					fscanf(fp, "%s", buflen);
					fscanf(fp, "%s", buflen);
					if((strcmp(buflen,"cosine")==0))
						check=1;
					else
						check=2;
					
				}
				else if(strcmp(buflen,"hamming")==0)
					check=0;
				else if(strcmp(buflen,"matrix")==0)
					check=3;
				else
				{
					printf("Wrong file structure!\n");
					return 0;
				}						
			}
			else
				return 0;
		fclose(fp);
		}
		else
		{
			printf("Wrong argument!\n");
			return 0;
		}
		if(strcmp(argv[3],"-q")==0)
		{
			qfile=(argv[4]);
		}
		else
		{
			printf("Wrong argument!\n");
			return 0;
		}
		if(strcmp(argv[5],"-o")==0)
		{
			ofile=argv[6];
			fpw=fopen(ofile, "w");
		}
		else
		{
			printf("Wrong argument!\n");
			return 0;
		}

	}
	else
	{
		printf("Wrong arguments!\n");
		return 0;	
	}
	for(i=1;i<k;i++)
	{
		hashsize*=2;
	}
	//hamming
	if(check==0)
	{
		fprintf(fpw,"Hamming\n");
		begin=clock();
		if ((fp = fopen((dfile), "r")) == NULL)
		{
			printf("Empty file!\n");
			return 0;
		}
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
		if ((fp = fopen((dfile), "r")) == NULL)
		{
			printf("Empty file!\n");
			return 0;
		}
		while (fscanf(fp, "%s", buflen) != EOF)
		{
			token=buflen; 
			if(token[0]=='i' && token[1]=='t'&& token[2]=='e'&& token[3]=='m')
			{
				readcount++;
			}
		}
		fclose(fp);
		if(k>log(readcount))
		{
			printf("Wrong k value! GOODBYE!\n");
			return 0;
		}
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
		
		hasht = malloc(L * sizeof(struct hashtable*));
		createhash(hasht,L,hashsize);
		if ((fp = fopen((dfile), "r")) == NULL)
		{
			printf("Empty file!\n");
			return 0;
		}
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
		end=clock();
		time_spent=(double)(end - begin) / CLOCKS_PER_SEC;
		do
		{	
			if ((fp = fopen(qfile, "r")) == NULL)
			{
				printf("Empty file!\n");
				return 0;
			}
			fscanf(fp, "%s", buflen);
			fscanf(fp, "%s", buflen);
			radius=strtol(buflen,&pitemid,10);
			while (fscanf(fp, "%s %s", buf,buflen) != EOF)
			{
				beginlsh=clock();
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
				fprintf(fpw, "Query: item%lu\n",itemid);			
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
				endlsh=clock();
				time_spentlsh=(double)(endlsh - beginlsh) / CLOCKS_PER_SEC;
				time_spentlsh+=time_spent;
				printdistancelist(dilist,length,fpw);
				findmin(dilist,0,fpw);
				free(dilist);
				freedlist(dilist);
				beginbr=clock();
				dilist =malloc(sizeof(struct distlist));//lista me apostaseis
				dilist->head=NULL;
				for(j=0;j<hashsize;j++)
				{
					search(hasht[0][j].lista,number,itemid,dilist,length,radius,L);//L=-1 wste na min stamatisei i while sto search
				}
				endbr=clock();
				time_spentbr=(double)(endbr - beginbr) / CLOCKS_PER_SEC;
				time_spentbr+=time_spent;
				findmin(dilist,1,fpw);
				freedlist(dilist);
				free(dilist);
				fprintf(fpw, "tLSH: %f\n",time_spentlsh);
				fprintf(fpw, "tTrue: %f\n\n",time_spentbr);
			}
			fclose(fp);	
			printf("Give the new query file name, or type END to terminate program!\n");
			memset(newfilename,0,sizeof(newfilename));
			memset(buflen,0,sizeof(buflen));
			memset(bufint,0,sizeof(bufint));
			scanf("%s",newfilename);
			qfile=newfilename;
		}while((strcmp(qfile,"END")!=0));
		freegf(gfun,L);
		free(gfun);
		freehasht(hasht,L,hashsize);
		free(hasht);
		
	}
//Cosine
	else if(check==1)
	{	
		fprintf(fpw,"Cosine\n");
		begin=clock();
		hasht = malloc(L * sizeof(struct hashtable*));
		createhash(hasht,L,hashsize);
		if ((fp = fopen((dfile), "r")) == NULL)
		{
			printf("Empty file!\n");
			return 0;
		}
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
		if ((fp = fopen((dfile), "r")) == NULL)
		{
			printf("Empty file!\n");
			return 0;
		}
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
		end=clock();
		time_spent=(double)(end - begin) / CLOCKS_PER_SEC;
		do{
			if ((fp = fopen((qfile), "r")) == NULL)
			{
				printf("Empty file!\n");
				return 0;
			}
			fscanf(fp, "%s", buflen);
			fscanf(fp, "%s", buflen);
			radius=strtol(buflen,&pitemid,10);

			while (fscanf(fp, "%s", buflen) != EOF)//vazei sto length ton stoixion tou arxeiou
			{
				beginlsh=clock();
				i=0;
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
					if(hasht[i][decimalnum].lista->head!=NULL) 
						searchcosine(hasht[i][decimalnum].lista,vector,itemid,dilist,counter,radius,L);
				}
				endlsh=clock();
				time_spentlsh=(double)(endlsh - beginlsh) / CLOCKS_PER_SEC;
				time_spentlsh+=time_spent;
				fprintf(fpw,"Query: item%lu\n",itemid);
				printdistancelistcosine(dilist,fpw);
				findmin(dilist,0,fpw);
				freedlist(dilist);
				free(dilist);
				beginbr=clock();
				dilist =malloc(sizeof(struct distlist));//lista me apostaseis
				dilist->head=NULL;
				for(j=0;j<hashsize;j++)
				{
					searchcosine(hasht[0][j].lista,vector,itemid,dilist,counter,0,-1);//L=-1 wste na min stamatisei i while sto search
				}
				endbr=clock();	
				time_spentbr=(double)(endbr - beginbr) / CLOCKS_PER_SEC;
				time_spentbr+=time_spent;
				findmin(dilist,1,fpw);		
				freedlist(dilist);
				free(dilist);
				free(vector);
				fprintf(fpw,"tLSH: %f\n",time_spentlsh);
				fprintf(fpw,"tTrue: %f\n",time_spentbr);
				fprintf(fpw,"\n");
			}
			fclose(fp);	
			printf("Give the new query file name, or type END to terminate program!\n");
			memset(newfilename,0,sizeof(newfilename));
			memset(buflen,0,sizeof(buflen));
			memset(bufint,0,sizeof(bufint));
			memset(bufinteger,0,sizeof(bufinteger));
			scanf("%s",newfilename);
			qfile=newfilename;
		}while((strcmp(qfile,"END")!=0));
		freegf(gfun,L);
		free(gfun);
		freefix(hfix,k,L);
		free(hfix);
		freehtable(htable,L,k);
		free(htable);
		freehasht(hasht,L,hashsize);
		free(hasht);
	
	}
	//EUCLIDEAN
	else if(check==2)
	{	
		fprintf(fpw,"Euclidean\n");
		begin=clock();
		if(k>10 && L>30)
		{
			printf("Wrong values for k,L! GOODBYE!\n");
			return 0;
		}
		for(i=0;i<32;i++)
			modnum*=2;
		modnum=modnum-5;
		if ((fp = fopen((dfile), "r")) == NULL)
		{
			printf("Empty file!\n");
			return 0;
		}
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
		if ((fp = fopen((dfile), "r")) == NULL)
		{
			printf("Empty file!\n");
			return 0;
		}
		while (fgets(buflen, sizeof(buflen), fp) != NULL)
		{
			if(buflen[0]=='i' && buflen[1]=='t' && buflen[2]=='e' && buflen[3]=='m')
				itemcounter++;
				
		}
		fclose(fp);
		hashsize=itemcounter/16;
		hasht = malloc(L * sizeof(struct hashtable*));
		createhash(hasht,L,hashsize);
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
		if ((fp = fopen((dfile), "r")) == NULL)
		{
			printf("Empty file!\n");
			return 0;
		}
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
		end=clock();
		time_spent=(double)(end - begin) / CLOCKS_PER_SEC;
		do
		{
			if ((fp = fopen((qfile), "r")) == NULL)
			{
				printf("Empty file!\n");
				return 0;
			}
			fscanf(fp, "%s", buflen);
			fscanf(fp, "%s", buflen);
			radius=strtol(buflen,&pitemid,10);
			
		
			while (fscanf(fp, "%s", buflen) != EOF)//vazei sto length ton stoixion tou arxeiou
			{
				beginlsh=clock();
				i=0;
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
					//printf("%f\n",radius);
					searcheuclidian(hasht[i][mod(idfind,hashsize)].lista,vector,itemid,idfind,dilist,counter,radius,L);
				}
				endlsh=clock();
				time_spentlsh=(double)(endlsh - beginlsh) / CLOCKS_PER_SEC;
				time_spentlsh+=time_spent;
				fprintf(fpw,"Query: item%lu\n",itemid);
				printdistancelisteuclidian(dilist,fpw);
				findmin(dilist,0,fpw);
				freedlist(dilist);
				free(dilist);
				beginbr=clock();
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
				{
					if(hasht[0][i].lista->head!=NULL)
						searcheuclidian(hasht[0][i].lista,vector,itemid,idfind,dilist,counter,0,-1);
				}
				endbr=clock();	
				time_spentbr=(double)(endbr - beginbr) / CLOCKS_PER_SEC;	
				time_spentbr+=time_spent;	
				findmin(dilist,1,fpw);
				freedlist(dilist);
				free(dilist);
				free(vector);
				fprintf(fpw,"tLSH: %f\n",time_spentlsh);
				fprintf(fpw,"tTrue: %f\n",time_spentbr);
				fprintf(fpw,"\n");
			}
			fclose(fp);	
			printf("Give the new query file name, or type END to terminate program!\n");
			memset(newfilename,0,sizeof(newfilename));
			memset(buflen,0,sizeof(buflen));
			memset(bufint,0,sizeof(bufint));
			memset(bufinteger,0,sizeof(bufinteger));
			scanf("%s",newfilename);
			qfile=newfilename;
		}while((strcmp(qfile,"END")!=0));
		freegf(gfun,L);
		free(gfun);
		freefix(vfix,k,L);
		free(vfix);
		free(tfix);
		free(rfix);
		freehasht(hasht,L,hashsize);
		free(hasht);

	}
	else if(check==3)
	{
		fprintf(fpw,"Matrix\n");
		begin=clock();
		hasht = malloc(L * sizeof(struct hashtable*));
		createhash(hasht,L,hashsize);
		begin=clock();
		if ((fp = fopen((dfile), "r")) == NULL)
		{
			printf("Empty file!\n");
			return 0;
		}
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
		if ((fp = fopen((dfile), "r")) == NULL)
		{
			printf("Empty file!\n");
			return 0;
		}
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
		
		summid=malloc(k*L*(sizeof(double*)));
		for(i=0;i<k*L;i++)
		{
			summid[i]=malloc(counter*sizeof(double));
			for(j=0;j<counter;j++)
			{
				summid[i][j]=0;
				summid[i][j]+=matrix[j][hmat[i][0]]*matrix[j][hmat[i][0]];
				summid[i][j]+=matrix[j][hmat[i][1]]*matrix[j][hmat[i][1]];
				summid[i][j]-=matrix[hmat[i][0]][hmat[i][1]]*matrix[hmat[i][0]][hmat[i][1]];
				summid[i][j]=summid[i][j]/(2*matrix[hmat[i][0]][hmat[i][1]]);
			}
		}
		for(i=0;i<k*L;i++)
		{
			bubble_sort(summid[i],counter);
			tmat[i]=summid[i][counter/2];
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
		fclose(fp);
		end=clock();
		time_spent=(double)(end - begin) / CLOCKS_PER_SEC;
		do{
			if ((fp = fopen((qfile), "r")) == NULL)
			{
				printf("Empty file!\n");
				return 0;
			}
			columns=-1;
			beginlsh=clock();
	 		while (fgets(baflen, sizeof(baflen), fp) != NULL)
				columns++;
			fclose(fp);
			matrid=malloc(columns*sizeof(long));
			querymatr=malloc(columns*sizeof(double*));
			for(i=0;i<columns;i++)
			{
				querymatr[i]=malloc(counter*sizeof(double));		
			}	
			if ((fp = fopen((qfile), "r")) == NULL)
			{
				printf("Empty file!\n");
				return 0;
			}
			fscanf(fp, "%s", baflen);
			fscanf(fp, "%s", baflen);
			radius=strtol(baflen,&pitemid,10);
			readcount=0;
			idcounter=0;
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
				itemid=strtol(bufinteger,&pitemid,10);
				matrid[idcounter]=itemid;
				idcounter++;
				for(i=0;i<counter;i++)
				{
					fscanf(fp, "%s", baflen);
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
					searchmatrix(hasht[z][decimalnum].lista,querymatr,matrid[j],dilist,counter,radius,-1);
			
				}	
				endlsh=clock();
				time_spentlsh=(double)(endlsh - beginlsh) / CLOCKS_PER_SEC;
				time_spentlsh+=time_spent;
				fprintf(fpw,"Query: item%lu\n",matrid[j]);
				printdistancelisteuclidian(dilist,fpw);
				findmin(dilist,0,fpw);
				free(dilist);
				beginbr=clock();
				dilist =malloc(sizeof(struct distlist));//lista me apostaseis
				dilist->head=NULL;

				for(i=0;i<hashsize;i++)
				{
					searchmatrix(hasht[0][i].lista,querymatr,matrid[j],dilist,counter,0,-1);
				}
				endbr=clock();
				time_spentbr=(double)(endbr - beginbr) / CLOCKS_PER_SEC;
				time_spentbr+=time_spent;
				findmin(dilist,1,fpw);			
				free(dilist);
				fprintf(fpw,"tLSH: %f\n",time_spentlsh);
				fprintf(fpw,"tTrue: %f\n",time_spentbr);
				fprintf(fpw,"\n");
			}
			fclose(fp);	
			printf("Give the new query file name, or type END to terminate program!\n");
			memset(newfilename,0,sizeof(newfilename));
			memset(baflen,0,sizeof(baflen));
			memset(bufint,0,sizeof(bufint));
			memset(bufinteger,0,sizeof(bufinteger));
			scanf("%s",newfilename);
			qfile=newfilename;
		}while((strcmp(qfile,"END")!=0));
		fclose(fp);	
		freefix(querymatr ,columns,1);
		free(querymatr);
		free(matrid);
		freefix(summid,k*L,1);
		free(summid);
		freegf(gfun,L);
		free(gfun);
		free(tmat);
		freegf(hmat,k*L);
		free(hmat);
		freefix(matrix,counter,1);
		free(matrix);
		freehasht(hasht,L,hashsize);
		free(hasht);
	}
	fclose(fpw);
}
