 ENTRY(start)
 SECTIONS
     {
       . = 0x10000;
       .text : {
		   start += .;
		   payload += . ;
		   *(.text)
		   payload_end = .;
	   }
       . = 0x8000000;
       .data : { *(.data) }
       .bss : { *(.bss) }
     }
