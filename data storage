#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"gesture.h"    // This header file is copied to,  and commented out at the bottom of this .c file



int Gwrite(FILE * fg, struct gesture *object)
{
  int i;
	fprintf(fg,"%s ", object->name);                 //now the format is name followed by the array of ints seperated by spaces. formatting changes and additonal information to be saved is a trivial change
	for(i = 0; i < 11; i++)
	{
		fprintf(fg, " %i", object->data[i]);
	}
	fprintf(fg, "%\n");
	return 1;
	
}

int Gnew(char*name, int data[11])            //it is currently implimented such that Gnew will always save the struct to disk by calling Gwrite, however I implimented Gwrite and Gnew sepertly in the event we do not always want to write directly to memory
{
	int i;

struct gesture * ngest;

	FILE * fp;
	fp = fopen("C:\\Users\\Austin\\Desktop\\data.txt", "a");                // for now the file must be declared inadvance, we can change this to be an arrgument of the function Gnew and Gload if desired
	if(fp == NULL)
		return 0;

		ngest = (struct gesture*)malloc(sizeof(struct gesture));

		ngest->name = name;
		for(i = 0; i < 11; i++)
		{
		ngest->data[i] = data[i];
		}


	Gwrite(fp, ngest);
	


	return 1;
}

void Gload(void)
{

	char line[80];
	int arr[11];
	int i;
	int y;
	char *name;
	FILE * fp;
	fp = fopen("C:\\Users\\Austin\\Desktop\\data.txt", "r");    // for now the file must be declared inadvance, we can change this to be an arrgument of the function Gnew and Gload if desired
	
	while(fgets(line, 80, fp) != NULL)
	{
		

		
	 name = strtok(line, " ");
	 arr[0] = atoi(strtok(NULL, " "));            // should turn this into a while loop but done this way for trouble shooting
	 arr[1] = atoi(strtok(NULL, " "));            //also, must deal with special case of first number being a '0' as atoi does not save it
	 arr[2] = atoi(strtok(NULL, " "));
	 arr[3] = atoi(strtok(NULL, " "));
	 arr[4] = atoi(strtok(NULL, " "));
	 arr[5] = atoi(strtok(NULL, " "));
	 arr[6] = atoi(strtok(NULL, " "));
	 arr[7] = atoi(strtok(NULL, " "));
	 arr[8] = atoi(strtok(NULL, " "));
	 arr[9] = atoi(strtok(NULL, " "));
	 arr[10] = atoi(strtok(NULL, " "));



	}
	Gnew(name, arr);                       //for now load only prints back to the .txt. this is for proof of concept, returning a pointer to a linked list will be trivial




	
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
