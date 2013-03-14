void rmgesture(char* name) {
	struct actionNode * point = peter;
	struct actionNode * point2;
	while(point != null || point->next->name != name) {
		if (point->next->name == name)
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
