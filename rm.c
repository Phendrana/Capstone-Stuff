void rmgesture(char* name) {
	struct actionNode * point = peter;
	while(point != null || point->next->name != name) {
		if (point->next->name == name)
			point->next = point->next->next;

		point = point->next;
	}
}
