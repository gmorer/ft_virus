 ENTRY(start)
 SECTIONS
     {
       . = 0x10000;
       .text : {
		   *(.text.start)
		   *(.text.payload)
		   *(.text.syscall0)
		   *(.text.syscall1)
		   *(.text.syscall2)
		   *(.text.finder)
		   *(.text.ft_strlen)
		   *(.text.ft_memcmp)
		   *(.text.ft_memcpy)
		   *(.text.ft_putnbr)
		   *(.text.inject)
		   *(.text.payload_end)
	   }
       . = 0x8000000;
       .data : { *(.data) }
       .bss : { *(.bss) }
     }
