typedef struct list {
	int value;
	struct list *next;
} list_t;

int list_search (list_t *list, int key)
{
	list_t *current = list;
	
	while (current != NULL)
	{
		if (current->value == key)
			return 1;
		
		current = current->next;
	}
	
	return 0;
}

list_t* list_add (list_t *list, int key)
{
	list_t *new = malloc(sizeof(list_t));
	
	new->value = key;
	new->next = list;
	
	return new;
}

list_t* list_delete (list_t *list, int key)
{
	list_t *current = list, *pred;
	
	while (current != NULL)
	{
		if (current->value == key)
		{
			if (current == list)
				list = current->next;
			else
				pred->next = current->next;
			
			free(current);
			return list;
		}
		else
		{
			pred = current;
			current = current->next;
		}
	}
	
	return list;
}

void list_display (list_t *list)
{
	list_t *current = list;
	
	while (current != NULL)
	{
		printf("%d\n", current->value);
		current = current->next;
	}
}
