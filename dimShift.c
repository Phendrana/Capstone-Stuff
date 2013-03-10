int * dims;
int * crosses;

void dimShift(actionPtr head, actionPtr new,int weight)
{
  int i,j,min,minat,temp;
	if(dims==NULL)
	{
		dims=malloc(sizeof(int)*11);
		for(i=0;i<11;i++)
		{
			dims[i]=i;
		}
		crosses=calloc(sizeof(int)*11);
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
