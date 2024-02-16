#include "hash_tables.h"

/**
 * hash_table_delete - Deletes a hash table.
 * @ht: A pointer to a hash table.
 *
 * Description: Frees all memory allocated for the hash table.
 */
void hash_table_delete(hash_table_t *ht)
{
	hash_node_t *node, *tmp_node;
	unsigned long int i;

	/*Check if the hash table is NULL*/
	if (ht == NULL)
		return;

	/*Iterate through each index of the hash table array*/
	for (i = 0; i < ht->size; i++)
	{
		/*Check if the current index is not empty*/
		if (ht->array[i] != NULL)
		{
			node = ht->array[i];
			/*Traverse the linked list at the current index*/
			while (node != NULL)
			{
				tmp_node = node->next;
				/*Free the key, value, and node itself*/
				free(node->key);
				free(node->value);
				free(node);
				node = tmp_node;
			}
		}
	}
	/*Free the array and the hash table itself*/
	free(ht->array);
	free(ht);
}
