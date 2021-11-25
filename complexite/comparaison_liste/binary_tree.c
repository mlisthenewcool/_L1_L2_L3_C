typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
} node_t;

node_t* new_node(int data) {
	node_t *new = malloc(sizeof(node_t));
	
	if (new == NULL) {
		perror("new_node failled to malloc");
		exit(1);
	}
	
	new->data = data;
	new->left = NULL;
	new->right = NULL;
	
	return new;
}


node_t* insert(node_t *tree, int data) {
	if(tree == NULL)
		return new_node(data);
	
	int left = 0;
	int exist = 0;
	node_t *cursor = tree;
	node_t *parent = NULL;
	
	while (cursor != NULL && exist == 0) {
		parent = cursor;
		
		if (data < cursor->data) {
			left = 1;
			cursor = cursor->left;
		}
		else if (data > cursor->data) {
			cursor = cursor->right;
		}
		else {
			exist = 1;
		}
	}
	
	if(left == 0)
		parent->left = new_node(data);
	else
		parent->right = new_node(data);
	
	return tree;
}


node_t* insert_bis(node_t *tree, int data) {
	if(tree == NULL)
		return new_node(data);

	node_t **current = &tree;
	while (*current)
	{
		if (data < (*current)->data)
		{
		   current = &(*current)->left;
		}
		else
		{
		   current = &(*current)->right;
		}
	}
	*current = new_node(data);
	return root;
}


void display(node_t *tree) {
	if (tree != NULL) {
		display(tree->left);
		printf("%d\n", tree->data);
		display(tree->right);
	}
}
