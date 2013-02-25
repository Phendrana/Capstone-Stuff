#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif
#ifndef nullchk
	#define nullchk(a) ((a==NULL) ? "NULL" : (a) )
#endif

struct action {
   int * high;
   int * low;
   char* name;
};
typedef struct action *actionP;

typedef struct actionNode *actionPtr;

struct actionNode {
   actionP action;
   actionPtr next;
};

int overlapSub(actionP a, actionP b)
{
	int i;
	for(i=0;i<11;i++)
	{
		if((a->high[i]<b->low[i])||(b->high[i]<a->low[i]))
		{		
			return 0;
		}
	}
	printf("intersect detected\n");
	return 1;
}

int overlap(actionPtr start, actionP b)
{
	int i;
	while(start!=NULL)
	{
		if(strcmp(start->action->name,b->name)||strcmp(b->name,start->action->name))
		{
			if(overlapSub(start->action,b))
			{
				return 1;
			}
			
		}
		start=start->next;
	}
	return 0;
}

char* isAction(actionPtr ptr, int a[11])
{
	int i;
	int outside;
	while(ptr!=NULL)
	{
		outside=0;
		for(i=0;i<11;i++)
		{
			if((ptr->action->high[i]<a[i])||(ptr->action->low[i]>a[i]))
			{
				outside=1;
				break;
			}
		}
		if(!outside)
		{
			return ptr->action->name;
		}
		ptr=ptr->next;
	}
	return NULL;
}

actionPtr addAction(actionPtr ptr, int a[11], char* name)
{
	actionPtr rtn=ptr;
	int i;
	if(ptr==NULL)
	{
		ptr=malloc(sizeof(actionPtr));
		ptr->action=malloc(sizeof(actionP));
		ptr->next=NULL;
		ptr->action->high=malloc(22*sizeof(int));
		ptr->action->low=&(ptr->action->high[11]);
		for(i=0;i<11;i++)
		{
			ptr->action->low[i]=a[i]-1;
			ptr->action->high[i]=a[i]+1;	
		}
		ptr->action->name=malloc(strlen(name)*sizeof(char));
		strcpy(ptr->action->name,name);
		
		return ptr;
	}
	actionPtr ptr2;
	while(ptr!=NULL)
	{
		ptr2=ptr;
		if(~strcmp(ptr->action->name,name)&&~strcmp(name,ptr->action->name))
		{
			for(i=0;i<11;i++)
			{
				ptr->action->low[i]=min(ptr->action->low[i],a[i]-1);
				ptr->action->high[i]=max(ptr->action->high[i],a[i]+1);
			}
			overlap(rtn,ptr->action);
			return rtn;
		}
		ptr=ptr->next;
	}
	ptr=malloc(sizeof(actionPtr));
	ptr->action=malloc(sizeof(actionP));
	ptr->next=NULL;
	ptr->action->high=malloc(22*sizeof(int));
	ptr->action->low=&(ptr->action->high[11]);
	for(i=0;i<11;i++)
	{
		ptr->action->low[i]=a[i]-1;
		ptr->action->high[i]=a[i]+1;	
	}
	ptr->action->name=malloc(strlen(name)*sizeof(char));
	strcpy(ptr->action->name,name);
	ptr2->next=ptr;
	overlap(rtn,ptr->action);
	return rtn;
}


int main( int argc, const char* argv[] )
{
	int b[11]={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; 
	int c[11]={5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}; 
	int d[11]={10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; 
	actionPtr ptr=addAction(NULL,b,"penis");
	printf("a\n");
	ptr=addAction(ptr,c,"penis2");
	printf("%s\n",nullchk(isAction(ptr,b)));
	printf("%s\n",nullchk(isAction(ptr,c)));
	printf("%s\n",nullchk(isAction(ptr,d)));
	ptr=addAction(ptr,d,"penis");
	printf("%s\n",nullchk(isAction(ptr,d)));
	ptr=addAction(ptr,d,"penis3");
}