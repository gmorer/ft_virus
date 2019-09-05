#ifndef STRUCT_H
# define STRUCT_H

typedef unsigned long long	u64;
typedef long long			s64;
typedef unsigned int		size_t;
typedef signed long			off_t;
typedef unsigned int		dev_t;
typedef unsigned long		ino_t;
typedef unsigned int		mode_t;
typedef   signed int		pid_t;
typedef unsigned int		uid_t;
typedef unsigned int		gid_t;
typedef unsigned long		nlink_t;
typedef   signed long		off_t;
typedef   signed long		blksize_t;
typedef   signed long		blkcnt_t;
typedef   signed long		time_t;

struct stat {
    dev_t     st_dev;
    ino_t     st_ino;
    mode_t    st_mode;
    nlink_t   st_nlink;
    uid_t     st_uid;
    gid_t     st_gid;
    dev_t     st_rdev;
    off_t     st_size;
    blksize_t st_blksize;
    blkcnt_t  st_blocks;
    time_t    st_atime;
    time_t    st_mtime;
    time_t    st_ctime;
};

struct linux_dirent64 {
	u64        d_ino;    // 64-bit inode number
	s64        d_off;    // 64-bit offset to next structure
	unsigned short d_reclen; // Size of this dirent
	unsigned char  d_type;   // File type
	char           d_name[]; // Filename (null-terminated)
};

#endif
