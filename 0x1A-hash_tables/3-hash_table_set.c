#include "hash_tables.h"

/**
 * hash_table_set - Adds an item to the Hash table.
 * @ht: A pointer to the hash table.
 * @key: The key of the item to be added.
 * @value: The value associated with the key.
 *
 * Return: Upon failure - 0.
 * Otherwise - 1.
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	hash_node_t *new_node;
	char *value_copy;
	unsigned long int index, i;

	/*Check for invalid parameters*/
	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	/*Duplicate the value string to store in the hash table*/
	value_copy = strdup(value);
	if (value_copy == NULL)
		return (0);

	/*Calculate the index for the given key*/
	index = key_index((const unsigned char *)key, ht->size);

	/*Check if the key already exists in the hash table*/
	for (i = index; ht->array[i]; i++)
	{
		if (strcmp(ht->array[i]->key, key) == 0)
		{
			/*Update the value if the key already exists*/
			free(ht->array[i]->value);
			ht->array[i]->value = value_copy;
			return (1);
		}
	}

	/*Create a new node for the key-value pair*/
	new_node = malloc(sizeof(hash_node_t));
	if (new_node == NULL)
	{
		free(value_copy);
		return (0);
	}

	/*Duplicate the key string to store in the new node*/
	new_node->key = strdup(key);
	if (new_node->key == NULL)
	{
		free(new_node);
		free(value_copy);
		return (0);
	}

	/*Assign the value and next pointer for the new node*/
	new_node->value = value_copy;
	new_node->next = ht->array[index];

	/*Update the array with the new node*/
	ht->array[index] = new_node;

	return (1);
}
