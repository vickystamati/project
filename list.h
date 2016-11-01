struct distnode{
	unsigned long long nearkey;
	unsigned long nearid;
	double distance;
	struct distnode *next;
};

struct distlist{
	struct distnode * head;
};


struct node{
	unsigned long long key;//binary
	unsigned long  id;//itemid
	long findid;//ID P
	double * key1;
	struct node * next;
};

struct list{
	struct node * head;
};
void createdlist(struct distlist * );
void insert(struct list * ,unsigned long long ,unsigned long );
void insertnear(struct distlist * ,struct distnode * );
void findmin(struct distlist * ,int,FILE*);
void search(struct list * ,unsigned long long,unsigned long ,struct distlist * ,int,double,int);
void turnintobinary(unsigned long long ,int ,char* );
void printdistancelist(struct distlist * ,int,FILE*);
void insertcosine(struct list *,double * ,unsigned long,int);
void searchcosine(struct list *,double* ,unsigned long ,struct distlist * ,int,double,int);
void printdistancelistcosine(struct distlist *,FILE*);
void inserteuclidian(struct list *,double* , long ,long ,int);
void searcheuclidian(struct list *,double* ,long,long ,struct distlist * ,int,double,int);
void printdistancelisteuclidian(struct distlist *,FILE*);
void searchmatrix(struct list* ,double ** ,long ,struct  distlist * , int,double ,int);
void freehlist(struct list*);
void freedlist(struct distlist*);
