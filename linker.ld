 ENTRY(start)
 SECTIONS
     {
       . = 0x10000;
       .text : {
		   *(.text.start)
		   *(.text.payload_start)
		   *(.text.payload)
		   *(.text.get_rel_addr)
		   *(.text.syscall1)
		   *(.text.syscall2)
		   *(.text.syscall3)
		   *(.text.finder)
		   *(.text.get_infos)
		   *(.text.ft_strlen)
		   *(.text.ft_memcmp)
		   *(.text.ft_memcpy)
		   *(.text.ft_putnbr)
		   *(.text.ft_putchar)
		   *(.text.ft_putul)
		   *(.text.debug_u64)
		   *(.text.inject)
		   *(.text.payload_end)
	   }
       . = 0x8000000;
       .data : { *(.data) }
       .bss : { *(.bss) }
     }
