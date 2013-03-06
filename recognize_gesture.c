#include <stdio.h>
#include <stdlib.h>



int* recognize(int *array, int* avg) {
	int j,k,l;

	for (k=0;k<11;k++) {
		avg[k] = (5*avg[k] + array[k])/6;
		//printf("%i\n",avg[k]);
		}

	for(k=0;k<11;k++)
	{
		if(abs(avg[k]-array[k])>3)
		{
			return avg;
		}
		
	}
	//isAction(peter,avg);
	return avg;
}

int* print_array(int* somearray) {
	int j;
	for (j=0;j<11;j++) {
		printf("%d\n", somearray[j]);
	} 
}

int main(int argc, char const *argv[])
{
	int p=11; int q;
	int* avg = calloc(p,sizeof(int));
	int a1[11] = {6,6,6,6,6,6,6,6,6,6,6};
	int a2[11] = {11,11,11,11,11,11,11,11,11,11,11};
	int a3[11] = {6,6,6,6,6,6,6,6,6,6,6};
	int a4[11] = {6,6,6,6,6,6,6,6,6,6,6};

	recognize(a1,avg);
	recognize(a2,avg);

	for (q=0;q<11;q++) {
		printf("%i\n",avg[q]);
	}

	return 0;
}