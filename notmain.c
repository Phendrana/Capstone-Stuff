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
int * dims;//ordered list of dimentions
int * crosses;//ordered list of crosses in given dimention



//@inputs action that was just added and weight to be given to it(mostly -1/1)
//finds the number of crosses created by a specific action adds them to crosses
//and sorts dims based on crosses
void dimShift(struct actionNode * new,int weight)
{
	struct actionNode *head=peter;
  	int i,j,min,minat,temp;
	if(dims==NULL)
	{
		dims=malloc(sizeof(int)*11);
		for(i=0;i<11;i++)
		{
			dims[i]=i;
		}
		crosses=calloc(11,sizeof(int));
	}
	while(head!=NULL)
	{
		if(head==new)
		{
			head=head->next;
			continue;
		}
		for(i=0;i<11;i++)
		{
			if((head->action->high[i]<new->action->low[i])||((head->action->low[i]>new->action->high[i]))
			{
				crosses[dims[i]]=crosses[dims[i]]+weight;
			}
		}
		head=head->next;
	}
	for(i=0;i<11;i++)
	{
		min=crosses[i];
		minat=i;
		for(j=(i+1);j<11;j++)
		{
			if(min>crosses[j])
			{
				min=crosses[j];
				minat=j;
			}
		}
		temp=dims[i];
		dims[i]=minat;
		dims[minat]=temp;
		crosses[minat]=crosses[i];
		crosses[i]=min;
	}
}

//@inputs starting ptr and current guesture
//@output name of action if it exists NULL otherwise
//checks the created actions for one that matches the given guesture
int isAction(struct actionNode *ptr, int a[11])
{
	int i,j;
	int outside;
        struct actionNode *ptr2=ptr;//for priority
        int h=0;
        //while there are still things in the LL
	while(ptr!=NULL)
	{
		outside=0;
		for(i=0;i<11;i++)//for each dimention
		{
			j=dims[i];
                 //check to see if the guesture matches the current action in the current dimention     
			if((ptr->action->high[j]<a[j])||(ptr->action->low[j]>a[j]))
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

/*
  @inputs LL node, 11 data points, name of gesture
  @outputs returns a pointer witht the new action
  adds a new action 
*/

struct actionNode * addAction(struct actionNode * ptr, int a[11], int name)
{
	struct actionNode * rtn=ptr;
	struct actionNode * ptr2;
	int i;
	//while pointer has data in it, update it
	while(ptr!=NULL)
	{
		//checks if the name of the action is the same
		if(ptr->action->name==name)
		{
			dimShift(ptr,-1);
		  // goes through and sets the new max and min values
		  for(i=0;i<11;i++)
		  {
		  	ptr->action->low[i]=min(ptr->action->low[i],a[i]-1);
			ptr->action->high[i]=max(ptr->action->high[i],a[i]+1);
		  }
			dimShift(ptr,1);
		  return rtn;
		}
		ptr2=ptr;
		ptr=ptr->next;
	}
	// if there is no data instantiate the highs and lows  
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
	if(rtn==NULL)
	{
		rtn=ptr;
	}
	else
	{
		ptr2->next=ptr;	
	}
	dimShift(ptr,1);
	return rtn;
}

//@inputs: array of sensor readings, current average
//@outputs: new average
//Is used to have a moving average, based on the current data input and previous average  
int* recognize(int *array, int* avg) {
	int j,k,l;

	for (k=0;k<11;k++) {
		avg[k] = (5*avg[k] + array[k])/6; //Puts more weighting on the previous average 
	}

	for(k=0;k<11;k++)
	{
		//If the difference is more than 3, break out of the method and take another input
		if(abs(avg[k]-array[k])>3)
		{
			digitalWrite(10,LOW);
  			digitalWrite(11,LOW);
  			digitalWrite(12,LOW);
			return avg;
		}
		
	}
	isAction(peter,avg);
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
  p=recognize(readings, p);
}
