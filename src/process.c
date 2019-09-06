#include "ft_virus.h"

#define BUF_SIZE 1024

int FORCE_INLINE is_the_one(char *file_name)
{
	char buf[BUF_SIZE];
	size_t name_size;
	char proc_dir[] = "/proc/";
	char exe_file[] = "/exe";
	int fd;

	name_size = ft_strlen(file_name);
	if (name_size + sizeof(proc_dir) - 1 + sizeof(exe_file) > BUF_SIZE)
		return (0);
	ft_memcpy(buf, proc_dir, sizeof(proc_dir) - 1);
	ft_memcpy(buf + sizeof(proc_dir) - 1, file_name, name_size);
	ft_memcpy(buf + sizeof(proc_dir) - 1 + name_size, exe_file, sizeof(exe_file));

	return (0);
}

int is_proc_actif(void)
{
    int						dir_fd;
    int						nread;
	int						bpos;
	struct linux_dirent64	*d;
	char					buf[BUF_SIZE];
	char					proc_dir = "/proc/";

    dir_fd = OPEN(proc_dir, O_RDONLY);
    if (dir_fd < 0)
        return (0); // hmmmm
    while (1)
    {
		nread = GETDENTS64(dir_fd, buf, BUF_SIZE);
		if (nread < 1)
			return (0); // hmmm
		bpos = 0;
		while (bpos < nread)
		{
			d = (struct linux_dirent64*)(buf + bpos);
			if (is_the_one(d->d_name))
				return (1);
			bpos += d->d_reclen;
		}
    }
	return (0);
}