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
    dev_t     st_dev;      /* ID du périphérique contenant le fichier */
    ino_t     st_ino;      /* Numéro inœud */
    mode_t    st_mode;     /* Protection */
    nlink_t   st_nlink;    /* Nb liens matériels */
    uid_t     st_uid;      /* UID propriétaire */
    gid_t     st_gid;      /* GID propriétaire */
    dev_t     st_rdev;     /* ID périphérique (si fichier spécial) */
    off_t     st_size;     /* Taille totale en octets */
    blksize_t st_blksize;  /* Taille de bloc pour E/S */
    blkcnt_t  st_blocks;   /* Nombre de blocs alloués */
    time_t    st_atime;    /* Heure dernier accès */
    time_t    st_mtime;    /* Heure dernière modification */
    time_t    st_ctime;    /* Heure dernier changement état */
};

struct linux_dirent64 {
	u64        d_ino;    // 64-bit inode number
	s64        d_off;    // 64-bit offset to next structure
	unsigned short d_reclen; // Size of this dirent
	unsigned char  d_type;   // File type
	char           d_name[]; // Filename (null-terminated)
};

#endif
