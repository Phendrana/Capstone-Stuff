
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

//info defining single guesture
struct action {
   int * high;
   int * low;
   int name;
};

//LLNode for action
struct actionNode {
   struct action * action;
   struct actionNode  *next;
};

struct actionNode * peter; 

int b1=7;//mux digital pin #1
int b0=8;//mux digital pin #2
int* p;//recognize() data
int readings[11];//data from sensors

//@inputs starting ptr and current guesture
//@output name of action if it exists NULL otherwise
//checks the created actions for one that matches the given guesture
int isAction(struct actionNode *ptr, int a[11])
{
	int i;
	int outside;
        struct actionNode *ptr2=ptr;//for priority
        int h=0;
        //while there are still things in the LL
	while(ptr!=NULL)
	{
		outside=0;
		for(i=0;i<11;i++)//for each dimention
		{
                 //check to see if the guesture matches the current action in the current dimention     
			if((ptr->action->high[i]<a[i])||(ptr->action->low[i]>a[i]))
			{
                                //if it is mark guesture wrong and move on
				outside=1;
				break;
			}
		}
                //if guesture is never marked wrong
		if(!outside)
		{
                        //do action (light up light for now)
                        digitalWrite(*ptr->action->name,HIGH);
                        //if chosen action is not already in first
                        if(ptr2!=ptr)
                        {
                          //switch the chosen 
                          struct action *temp=ptr->action;
                          ptr->action=ptr2->action;
                          ptr2->action=temp;
                        }
			return ptr2->action->name;
		}
                ptr2=ptr;
		ptr=ptr->next;
	}
	return NULL;
}

struct actionNode * addAction(struct actionNode * ptr, int a[11], int name)
{
	struct actionNode * rtn=ptr;
	int i;
	if(ptr==NULL)
	{
		ptr=(struct actionNode *)malloc(sizeof(struct actionNode *));
		ptr->action=(struct action *)malloc(sizeof(struct action *));
		ptr->next=NULL;
		ptr->action->high=(int*)malloc(22*sizeof(int));
		ptr->action->low=&(ptr->action->high[11]);
		for(i=0;i<11;i++)
		{
			ptr->action->low[i]=a[i]-1;
			ptr->action->high[i]=a[i]+1;	
		}
		ptr->action->name=name;

		return ptr;
	}
	struct actionNode * ptr2;
	while(ptr!=NULL)
	{
		ptr2=ptr;
		if(ptr->action->name==name)
		{
                  Serial.println(name);
			for(i=0;i<11;i++)
			{
				ptr->action->low[i]=min(ptr->action->low[i],a[i]-1);
				ptr->action->high[i]=max(ptr->action->high[i],a[i]+1);
			}

			return rtn;
		}
		ptr=ptr->next;
	}
	ptr=(struct actionNode *)malloc(sizeof(struct actionNode *));
	ptr->action=(struct action *)malloc(sizeof(struct action *));
	ptr->next=NULL;
	ptr->action->high=(int*)malloc(22*sizeof(int));
	ptr->action->low=&(ptr->action->high[11]);
	for(i=0;i<11;i++)
	{
		ptr->action->low[i]=a[i]-1;
		ptr->action->high[i]=a[i]+1;	
	}
	ptr->action->name=name;
	ptr2->next=ptr;
	return rtn;
}

int* recognize(int *array, int* avg) {
//	int j,k;
//        int hold[11]; 
//	for (j=0;j<11;j++) {
//		array[j] += hold[j]; 
//	}
//	for (k=0;k<11;k++) {
//		avg[k] = (5*avg[k] + array[k])/6;
//	}
//
//	for(k=0;k<11;k++)
//	{
//		if(abs(avg[k]-array[k])>3)
//		{
//
//			return avg;
//		}
//
//	}
//int i;
//for(i=0;i<11;i++)
//{
//Serial.print(array[i]);
//Serial.print(", ");
//}
//Serial.println();
//delay(500);
	isAction(peter,array);
	return avg;
}


void setup() {
  p=(int*)malloc(11*sizeof(int));
  Serial.begin(9600);
  pinMode(11, 'output');
  pinMode(12, 'output');
  pinMode(10, 'output');
  pinMode(b1, 'output');
  pinMode(b0, 'output');
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  digitalWrite(12,LOW);
  pinMode(b1, 'output');
  pinMode(b0, 'output');
  digitalWrite(b1, LOW);
  int a[]={680, 680, 680, 680, 800, 680, 680, 680, 680,800,680};
  peter=addAction(peter, a,10);
  int b[]={760, 760, 760, 760, 850, 760, 760, 760, 760,850,760};
  peter=addAction(peter, b,10);

}


void loop() {
  
  digitalWrite(b0, LOW);
  readings[0]=analogRead(1);
  readings[1]=analogRead(2);
  readings[2]=analogRead(3);
  readings[3]=analogRead(4);
  readings[4]=analogRead(5);
    
  digitalWrite(b0, HIGH);
  readings[5]=analogRead(1);
  readings[6]=analogRead(2);
  readings[7]=analogRead(3);
  readings[8]=analogRead(4);
  readings[9]=analogRead(5);
    
  readings[10]=analogRead(0);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  p=recognize(readings, p);
}
