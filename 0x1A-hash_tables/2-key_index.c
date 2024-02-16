#include "hash_tables.h"

/**
 * key_index - Calculates the index of a key in the hash table array.
 * @key: The key to get the index of.
 * @size: The size of the array item of the hash table.
 *
 * Return: The index of the key.
 *
 * Description: Uses the djb2 algorithm.
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	/*Calculate the hash value using the djb2 algorithm*/
	unsigned long int hash_value = hash_djb2(key);

	/*Calculate the index by taking the modulo with the size of the array*/
	unsigned long int index = hash_value % size;

	return (index);
}
