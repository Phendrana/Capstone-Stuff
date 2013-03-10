#include <stdio.h>
#include <stdlib.h>


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
			return avg;
		}
		
	}
	//isAction(peter,avg);
	return avg;
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
