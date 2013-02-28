#include <stdio.h>
#include <stdlib.h>

int* recognize(int *array, int* avg) {
	int j,k;
	for (j=0;j<11;j++) {
		array[j] += hold[j]; 
	}

		for (k=0;k<11;k++) {
			avg[k] = (5*avg[k] + array[k])/6;
		}
	}
	for(k=0;k<11;k++)
	{
		if(abs(avg[k]-array[k])>3)
		{
			
			return avg;
		}
		
	}
	isAction(peter,avg);
	return avg;
}
