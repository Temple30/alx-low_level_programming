#include "hash_tables.h"

/**
 * hash_djb2 - Hash function implementing the djb2 algorithm.
 * @str: The string to hash.
 *
 * Return: The calculated hash.
 */
unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash;
	int c;

	hash = 5381; /*Initial hash value*/
	while ((c = *str++)) /*Iterate over each character of the string*/
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		/*The above line applies the djb2 algorithm to calculate the hash*/
	}

	return (hash);
}
