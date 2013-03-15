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
   char* name;
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
int * crosses;//ordered list of crosses in given dimension
int holding;



//@inputs action that was just added and weight to be given to it(mostly -1/1)
//finds the number of crosses created by a specific action adds them to crosses
//and sorts dims based on crosses
void dimShift(struct actionNode * ptr,int weight)
{
	struct actionNode *head=peter;
  	int i,j,m,minat,temp;
	if(dims==NULL)
	{
		dims=(int*)malloc(sizeof(int)*11);
		for(i=0;i<11;i++)
		{
			dims[i]=i;
		}
		crosses=(int*)calloc(11,sizeof(int));
	}
	while(head!=NULL)
	{
		if(head==ptr)
		{
			head=head->next;
			continue;
		}
		for(i=0;i<11;i++)
		{
			if((head->action->high[i]<ptr->action->low[i])||(head->action->low[i]>ptr->action->high[i]))
			{
				crosses[dims[i]]=crosses[dims[i]]+weight;
			}
		}
		head=head->next;
	}
	for(i=0;i<11;i++)
	{
		m=crosses[i];
		minat=i;
		for(j=(i+1);j<11;j++)
		{
			if(m>crosses[j])
			{
				m=crosses[j];
				minat=j;
			}
		}
		temp=dims[i];
		dims[i]=minat;
		dims[minat]=temp;
		crosses[minat]=crosses[i];
		crosses[i]=m;
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
                        //if chosen action is not already in first
                        if(!holding)
                        {
                          Serial.println(*ptr->action->name);
                          holding=1;
                        }
                        if(ptr2!=ptr)
                        {
                          //switch the chosen 
                          struct action *temp=ptr->action;
                          ptr->action=ptr2->action;
                          ptr2->action=temp;
                        }
			return *ptr2->action->name;
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

struct actionNode * addAction(struct actionNode * ptr, int a[11], char name)
{
	struct actionNode * rtn=ptr;
	struct actionNode * ptr2;
	int i;
	//while pointer has data in it, update it
	while(ptr!=NULL)
	{
		//checks if the name of the action is the same
		if(*ptr->action->name==name)
		{
  
			dimShift(ptr,-1);
		  // goes through and sets the new max and min values
		  for(i=0;i<11;i++)
		  {

		  	ptr->action->low[i]=min(ptr->action->low[i],a[i]-15);
			ptr->action->high[i]=max(ptr->action->high[i],a[i]+15);


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
	ptr->action->high=(int*)malloc(12*sizeof(int));
        ptr->action->high=ptr->action->high+1;
	ptr->action->low=(int*)malloc(11*sizeof(int));
	for(i=0;i<11;i++)
	{
		ptr->action->low[i]=a[i]-15;
		ptr->action->high[i]=a[i]+15;	
	}
        ptr->action->name=(char*)malloc(sizeof(char));
	*ptr->action->name=name;
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
		if(abs(avg[k]-array[k])>8)
		{
			digitalWrite(10,LOW);
  			digitalWrite(11,LOW);
  			digitalWrite(12,LOW);
                        holding=0;
			return avg;
		}

	}
int i;
	isAction(peter,array);
	return avg;
}


void removeAction(char name) {
	struct actionNode * point = peter;
	struct actionNode * point2;
        if(*point->action->name==name)
        {
           peter=point->next;
            free(point->action->high-1);
            free(point->action->low);
           free(point->action);
          free(point);
       return; 
        }
	while(point->next != NULL) {
		if (*point->next->action->name == name)
		{
			point2 = point;
			point->next = point2->next->next;
			free(point2->action->high);
			free(point2->action);
			free(point2);
			return;
		}
		point = point->next;
	}


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
  holding=0;
  pinMode(b0, 'output');
}


void loop() {
    
  digitalWrite(b1, LOW);
  digitalWrite(b0, LOW);
  readings[0]=analogRead(1);
  readings[1]=analogRead(2);
  readings[2]=analogRead(3);
  readings[3]=analogRead(4);
  
  digitalWrite(b0, HIGH);
  readings[4]=analogRead(1);
  readings[5]=analogRead(2);
  readings[6]=analogRead(3);
  readings[7]=analogRead(4);
  
  digitalWrite(b1, HIGH);
  digitalWrite(b0, LOW);
  readings[8]=analogRead(1);
  readings[9]=analogRead(2);
  readings[10]=analogRead(3);
  

  
  if(Serial.available()) {
    
    char ch = Serial.read();
    
    if (ch >='a') {
      peter=addAction(peter, readings, ch);
      int i;
      for(i=0;i<11;i++)
      {
        Serial.println(peter->action->high[i]);
      }
    }
    else {
      ch = ch + 32;
      removeAction(ch);
    }
    
  }
  
  p=recognize(readings, p);
}
