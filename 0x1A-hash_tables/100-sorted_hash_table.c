#include "hash_tables.h"

/**
 * shash_table_create - Creates a sorted hash table.
 * @size: The size of the new sorted hash table.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new sorted hash table.
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;
	unsigned long int i;

	/*Allocate memory for the sorted hash table*/
	ht = malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);

	/*Initialize the hash table attributes*/
	ht->size = size;
	ht->array = malloc(sizeof(shash_node_t *) * size);
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}
	for (i = 0; i < size; i++)
		ht->array[i] = NULL;
	ht->shead = NULL;
	ht->stail = NULL;

	return (ht);
}

/**
 * shash_table_set - Adds an element to a sorted hash table.
 * @ht: A pointer to the sorted hash table.
 * @key: The key to add - cannot be an empty string.
 * @value: The value associated with the key.
 *
 * Return: Upon failure - 0.
 *         Otherwise - 1.
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *new, *tmp;
	char *value_copy;
	unsigned long int index;

	/*Check for NULL pointers or empty key*/
	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	/*Duplicate the value string to store in the hash table*/
	value_copy = strdup(value);
	if (value_copy == NULL)
		return (0);

	/*Calculate the index for the given key*/
	index = key_index((const unsigned char *)key, ht->size);

	/*Search for existing key in the sorted list*/
	tmp = ht->shead;
	while (tmp != NULL)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			/*Update the value if the key already exists*/
			free(tmp->value);
			tmp->value = value_copy;
			return (1);
		}
		tmp = tmp->snext;
	}

	/*Create a new node for the key-value pair*/
	new = malloc(sizeof(shash_node_t));
	if (new == NULL)
	{
		free(value_copy);
		return (0);
	}
	new->key = strdup(key);
	if (new->key == NULL)
	{
		free(value_copy);
		free(new);
		return (0);
	}
	new->value = value_copy;

	/*Insert the new node into the hash table array*/
	new->next = ht->array[index];
	ht->array[index] = new;

	/*Insert the new node into the sorted list*/
	if (ht->shead == NULL || strcmp(ht->shead->key, key) > 0)
	{
		new->snext = ht->shead;
		new->sprev = NULL;
		if (ht->shead != NULL)
			ht->shead->sprev = new;
		ht->shead = new;
		if (ht->stail == NULL)
			ht->stail = new;
	}
	else
	{
		tmp = ht->shead;
		while (tmp->snext != NULL && strcmp(tmp->snext->key, key) < 0)
			tmp = tmp->snext;
		new->sprev = tmp;
		new->snext = tmp->snext;
		if (tmp->snext != NULL)
			tmp->snext->sprev = new;
		tmp->snext = new;
		if (tmp == ht->stail)
			ht->stail = new;
	}

	return (1);
}

/**
 * shash_table_get - Retrieve the value associated with a key in a sorted hash table.
 * @ht: A pointer to the sorted hash table.
 * @key: The key to get the value of.
 *
 * Return: If the key cannot be matched - NULL.
 *         Otherwise - the value associated with the key in ht.
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *node;
	unsigned long int index;

	/*Check for NULL pointers or empty key*/
	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	/*Calculate the index for the given key*/
	index = key_index((const unsigned char *)key, ht->size);
	if (index >= ht->size)
		return (NULL);

	/*Search for the key in the sorted list*/
	node = ht->shead;
	while (node != NULL && strcmp(node->key, key) != 0)
		node = node->snext;

	return (node != NULL ? node->value : NULL);
}

/**
 * shash_table_print - Prints a sorted hash table in order.
 * @ht: A pointer to the sorted hash table.
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;

	/*Check for NULL hash table*/
	if (ht == NULL)
		return;

	printf("{");
	/*Traverse the sorted list and print key-value pairs*/
	for (node = ht->shead; node != NULL; node = node->snext)
	{
		printf("'%s': '%s'", node->key, node->value);
		if (node->snext != NULL)
			printf(", ");
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - Prints a sorted hash table in reverse order.
 * @ht: A pointer to the sorted hash table.
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;

	/*Check for NULL hash table*/
	if (ht == NULL)
		return;

	printf("{");
	/*Traverse the sorted list in reverse order and print key-value pairs*/
	for (node = ht->stail; node != NULL; node = node->sprev)
	{
		printf("'%s': '%s'", node->key, node->value);
		if (node->sprev != NULL)
			printf(", ");
	}
	printf("}\n");
}

/**
 * shash_table_delete - Deletes a sorted hash table.
 * @ht: A pointer to the sorted hash table.
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *node, *next;

	/*Check for NULL hash table*/
	if (ht == NULL)
		return;

	/*Free the memory allocated for each node in the sorted list*/
	for (node = ht->shead; node != NULL; node = next)
	{
		next = node->snext;
		free(node->key);
		free(node->value);
		free(node);
	}

	/*Free the memory allocated for the hash table array*/
	free(ht->array);

	/*Free the memory allocated for the hash table itself*/
	free(ht);
}
