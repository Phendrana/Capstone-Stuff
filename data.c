#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"gesture.h"    // This header file is copied to,  and commented out at the bottom of this .c file

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

void Gwrite(FILE * fg)
{
  	int i;
	struct actionNode * ptr=peter;
	FILE * fg;
	fp = fopen("C:\\Users\\Austin\\Desktop\\data.txt", "w");    
	while(ptr!=NULL)
	{
		fprintf(fg,"%s", ptr->action->name);                 //now the format is name followed by the array of ints seperated by spaces. formatting changes and additonal information to be saved is a trivial change
		for(i = 0; i < 11; i++)
		{
			fprintf(fg, " %i %i", ptr->action->high[i],ptr->action->low[i]);
		}
		fprintf(fg, "%\n");
	ptr=ptr->next
	}
	
}

void Gload()
{

	char line[128];
	int i;
	struct actionNode * ptr=peter;
	char name[64];
	FILE * fp;
	fp = fopen("C:\\Users\\Austin\\Desktop\\data.txt", "r");    // for now the file must be declared inadvance, we can change this to be an arrgument of the function Gnew and Gload if desired
	
	while(fgets(line, 128, fp) != NULL)
	{
		if(peter==NULL)
		{
			peter=malloc(sizeof(struct actionNode *));
			peter->next=NULL;
			ptr=peter;
		}
		else
		{
			ptr->next=malloc(sizeof(struct actionNode *));
			ptr=ptr->next
			ptr->next=NULL;
		}
		ptr->action=malloc(sizeof(struct action*));
	 	name = strtok(line, " ");
		i=strlen(name)+1;
		ptr->action->name=malloc(sizeof(char)*i);
		strcpy(ptr->action->name,name,i);
		ptr->action->high=(int*)malloc(22*sizeof(int));
		ptr->action->low=&(ptr->action->high[11]);
		for(i=0;i<11;i++)
		{
		 	ptr->action->high[i] = atoi(strtok(NULL, " "));            // should turn this into a while loop but done this way for trouble shooting
		 	ptr->action->low[i = atoi(strtok(NULL, " "));  		//also, must deal with special case of first number being a '0' as atoi does not save it
		}
	}



	
}

int main()
{
	int i;

int arr[11];                     // used this for a test run

arr[0] = 123;
arr[1] = 345;
arr[2] = 678;
arr[3] = 263;
arr[4] = 856;
arr[5] = 375;
arr[6] = 387;
arr[7] = 642;
arr[8] = 678;
arr[9] = 345;
arr[10] = 261;



Gnew("test", arr);


Gload();

return 0;
}





// gesture.h     includes the struct gesture
/*           
struct gesture
{
	int data[11];
	char *name;

};
*/
