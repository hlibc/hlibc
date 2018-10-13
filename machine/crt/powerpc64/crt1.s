.text
.global _start
.type    _start, %function
_start :
        addis  2, 12, .TOC.- _start @ha
        addi   2,  2, .TOC.- _start @l
        lwz    4, 1f- _start (12)
        add    4, 4, 12
        mr     3, 1
        clrrdi 1, 1, 4
        li     0, 0
        stdu   0, -32(1)
        mtlr   0
        bl  __load_main
.weak   _DYNAMIC
.hidden _DYNAMIC
1:      .long _DYNAMIC- _start

