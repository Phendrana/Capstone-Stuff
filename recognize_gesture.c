#include <stdio.h>
#include <stdlib.h>

struct arrays {
	int array[11];
}

typedef struct arrays *Thing;
typedef struct arrays *storing_thing;
int* recognize(Thing *somearray, int n) {
	int i,j,k;
	int avg[11];
	int *hold = calloc(sizeof(int)*11);
	for (i=0;i<n;i++) {
		for (j=0;j<11;j++) {
			somearray[i].array[j] += hold[j]; 
		}

		for (k=0;k<11;k++) {
			avg[k] = 5*hold[k] + somearray[i].array[k];
		}
	}
	return avg;
}



/*
int recognize(int** stored,int * input)
{
	if(stored==NULL)
	{
		stored=calloc(121*sizeof(int));
		int i;
		for(i=0;i<10;i++)
		{
			stored[i]=stored[(i+1)+11];
		}

	}


	return stored
}
*/