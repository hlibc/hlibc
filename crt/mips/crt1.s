.set noreorder
.global __start
.global _start
__start:
_start:
	subu    $fp, $fp, $fp            # Zero the frame pointer.
	lui     $gp, %hi(_gp)
	addi    $gp, %lo(_gp)
	#la      $gp, _gp
	lw      $4, %call16(main)($gp)   # Get main() ...
	lw      $5, ($sp)                # Get argc...
	addu    $6, $sp, 4               # and argv ... 
	addi    $sp, $sp, -4*6           # Leave space for arguments 0..3, arg4, and arg5. 
	sw      $12, 4*4($sp)            # Save arg4. 
	lw      $25, %call16(__libc_start_main)($gp)
	jalr    $25                      # Let's go!
	nop
	b       .                        # Never gets here.
	nop
