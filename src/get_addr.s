global get_rel_addr

; return the rel addr of the function
section .text.get_rel_addr
get_rel_addr:
	lea rax, [rel get_rel_addr]
	ret
