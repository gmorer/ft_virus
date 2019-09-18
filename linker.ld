 ENTRY(start)
 SECTIONS
     {
       . = 0x10000;
       .text : {
			*(.text.start)
			*(.text.payload_start)
			*(.text.decrypt)
			*(.text.syscall0)
			*(.text.syscall1)
			*(.text.syscall2)
			*(.text.syscall3)
			*(.text.syscall4)
			*(.text.get_rel_addr)
			*(.text.is_proc_actif)
			*(.text.ft_strlen)
			*(.text.ft_memcmp)
			*(.text.ft_memcpy)
			*(.text.payload)
			*(.text.encrypt)
			*(.text.finder)
			*(.text.get_infos)
			*(.text.inject)
			*(.text.payload_end)
	   }
       . = 0x8000000;
       .data : { *(.data) }
       .bss : { *(.bss) }
     }
