#include "./hash_tables.h"

/**
 * hash_table_print - Prints the contents of a hash table.
 * @ht: A pointer to the hash table.
 *
 * Description: Prints the key-value pairs of the hash table.
 */
void hash_table_print(const hash_table_t *ht)
{
	hash_node_t *node;
	unsigned long int i;
	unsigned char comma_flag = 0;

	/*Check if the hash table is NULL*/
	if (ht == NULL)
		return;

	printf("{");
	/*Iterate through each index of the hash table array*/
	for (i = 0; i < ht->size; i++)
	{
		/*Check if the current index is not empty*/
		if (ht->array[i] != NULL)
		{
			/*Add a comma if it's not the first key-value pair*/
			if (comma_flag == 1)
				printf(", ");

			/*Traverse the linked list at the current index*/
			node = ht->array[i];
			while (node != NULL)
			{
				printf("'%s': '%s'", node->key, node->value);
				node = node->next;
				/*Add a comma if there are more key-value pairs*/
				if (node != NULL)
					printf(", ");
			}
			/*Set comma_flag to 1 after printing the first key-value pair*/
			comma_flag = 1;
		}
	}
	printf("}\n");
}
