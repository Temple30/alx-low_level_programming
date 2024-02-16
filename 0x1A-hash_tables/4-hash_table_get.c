#include "hash_tables.h"

/**
 * hash_table_get - Retrieves an item from the hash table.
 * @ht: A pointer to the hash table.
 * @key: The key to retrieve the item.
 *
 * Return: The value associated with the key, or NULL if not found.
 */
char *hash_table_get(const hash_table_t *ht, const char *key)
{
	hash_node_t *node;
	unsigned long int index;

	/*Check for invalid parameters*/
	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	/*Calculate the index for the given key*/
	index = key_index((const unsigned char *)key, ht->size);

	/*Check if the calculated index is within the valid range*/
	if (index >= ht->size)
		return (NULL);

	/*Traverse the linked list at the calculated index to find the key*/
	node = ht->array[index];
	while (node != NULL && strcmp(node->key, key) != 0)
		node = node->next;

	/*Return the value associated with the key, or NULL if key not found*/
	return (node != NULL ? node->value : NULL);
}

