	.file	"makeoffset.c"
	.section .text
.Ltext0:
	.align 1
	.global _makeoffset
	.type	_makeoffset, @function
_makeoffset:
.LFB58:
	.file 1 "../../../../mros/asp-athrill-mbed/asp-athrill/arch/v850_gcc/makeoffset.c"
	.loc 1 61 0
	.loc 1 62 0
#APP
# 62 "../../../../mros/asp-athrill-mbed/asp-athrill/arch/v850_gcc/makeoffset.c" 1
	OFFSET_DEF TCB_p_tinib = 8
# 0 "" 2
	.loc 1 63 0
# 63 "../../../../mros/asp-athrill-mbed/asp-athrill/arch/v850_gcc/makeoffset.c" 1
	OFFSET_DEF TCB_texptn = 16
# 0 "" 2
	.loc 1 64 0
# 64 "../../../../mros/asp-athrill-mbed/asp-athrill/arch/v850_gcc/makeoffset.c" 1
	OFFSET_DEF TCB_sp = 24
# 0 "" 2
	.loc 1 65 0
# 65 "../../../../mros/asp-athrill-mbed/asp-athrill/arch/v850_gcc/makeoffset.c" 1
	OFFSET_DEF TCB_pc = 28
# 0 "" 2
	.loc 1 67 0
# 67 "../../../../mros/asp-athrill-mbed/asp-athrill/arch/v850_gcc/makeoffset.c" 1
	OFFSET_DEF TINIB_exinf = 4
# 0 "" 2
	.loc 1 68 0
# 68 "../../../../mros/asp-athrill-mbed/asp-athrill/arch/v850_gcc/makeoffset.c" 1
	OFFSET_DEF TINIB_task = 8
# 0 "" 2
	.loc 1 69 0
#NO_APP
	jmp [r31]
.LFE58:
	.size	_makeoffset, .-_makeoffset
	.align 1
	.global _sil_endian
	.type	_sil_endian, @function
_sil_endian:
.LFB59:
	.loc 1 73 0
	.loc 1 78 0
#APP
# 78 "../../../../mros/asp-athrill-mbed/asp-athrill/arch/v850_gcc/makeoffset.c" 1
	SIL_ENDIAN = LITTLE
# 0 "" 2
	.loc 1 81 0
#NO_APP
	jmp [r31]
.LFE59:
	.size	_sil_endian, .-_sil_endian
	.global _BIT_LB_TCB_enatex
	.section .data
	.align 2
	.type	_BIT_LB_TCB_enatex, @object
	.size	_BIT_LB_TCB_enatex, 32
_BIT_LB_TCB_enatex:
	.long	0
	.long	0
	.long	0
	.byte	0
	.byte	0
	.byte	4
	.zero	1
	.long	0
	.long	0
	.long	0
	.long	0
	.global _BIT_REF_1
	.type	_BIT_REF_1, @object
	.size	_BIT_REF_1, 1
_BIT_REF_1:
	.byte	18
	.global _BIT_REF_2
	.align 1
	.type	_BIT_REF_2, @object
	.size	_BIT_REF_2, 2
_BIT_REF_2:
	.hword	4660
	.global _BIT_REF_4
	.align 2
	.type	_BIT_REF_4, @object
	.size	_BIT_REF_4, 4
_BIT_REF_4:
	.long	305419896
	.section	.debug_frame,"",@progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x3
	.string	""
	.uleb128 0x1
	.sleb128 -4
	.uleb128 0x1f
	.byte	0xc
	.uleb128 0x3
	.uleb128 0
	.align 2
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB58
	.4byte	.LFE58-.LFB58
	.align 2
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB59
	.4byte	.LFE59-.LFB59
	.align 2
.LEFDE2:
	.section .text
.Letext0:
	.file 2 "../../../../mros/asp-athrill-mbed/asp-athrill/arch/gcc/tool_stddef.h"
	.file 3 "../../../../mros/asp-athrill-mbed/asp-athrill/include/t_stddef.h"
	.file 4 "../../../../mros/asp-athrill-mbed/asp-athrill/include/kernel.h"
	.file 5 "../../../../mros/asp-athrill-mbed/asp-athrill/arch/v850_gcc/prc_config.h"
	.file 6 "../../../../mros/asp-athrill-mbed/asp-athrill/include/queue.h"
	.file 7 "../../../../mros/asp-athrill-mbed/asp-athrill/kernel/time_event.h"
	.file 8 "../../../../mros/asp-athrill-mbed/asp-athrill/kernel/task.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x45b
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x1
	.4byte	.LASF76
	.4byte	.LASF77
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF0
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	.LASF1
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF2
	.uleb128 0x4
	.4byte	.LASF5
	.byte	0x2
	.byte	0x67
	.4byte	0x4c
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF3
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x4
	.4byte	.LASF6
	.byte	0x2
	.byte	0x6a
	.4byte	0x65
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x4
	.4byte	.LASF8
	.byte	0x2
	.byte	0x6d
	.4byte	0x2c
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF9
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x4
	.4byte	.LASF11
	.byte	0x2
	.byte	0x75
	.4byte	0x33
	.uleb128 0x4
	.4byte	.LASF12
	.byte	0x2
	.byte	0x76
	.4byte	0x9b
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF13
	.uleb128 0x3
	.byte	0x4
	.byte	0x4
	.4byte	.LASF14
	.uleb128 0x3
	.byte	0x8
	.byte	0x4
	.4byte	.LASF15
	.uleb128 0x5
	.4byte	.LASF26
	.byte	0x4
	.byte	0x3
	.byte	0x5b
	.4byte	0xc9
	.uleb128 0x6
	.4byte	.LASF28
	.byte	0x3
	.byte	0x5b
	.4byte	0x25
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF16
	.byte	0x3
	.byte	0x5c
	.4byte	0xd4
	.uleb128 0x7
	.byte	0x4
	.4byte	0xda
	.uleb128 0x8
	.4byte	0xe5
	.uleb128 0x9
	.4byte	0xb0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF17
	.byte	0x3
	.byte	0x63
	.4byte	0x25
	.uleb128 0x4
	.4byte	.LASF18
	.byte	0x3
	.byte	0x65
	.4byte	0x25
	.uleb128 0x4
	.4byte	.LASF19
	.byte	0x3
	.byte	0x66
	.4byte	0x2c
	.uleb128 0x4
	.4byte	.LASF20
	.byte	0x3
	.byte	0x69
	.4byte	0x9b
	.uleb128 0xa
	.string	"ER"
	.byte	0x3
	.byte	0x6c
	.4byte	0xf0
	.uleb128 0xa
	.string	"ATR"
	.byte	0x3
	.byte	0x6e
	.4byte	0xfb
	.uleb128 0x4
	.4byte	.LASF21
	.byte	0x3
	.byte	0x72
	.4byte	0x90
	.uleb128 0xa
	.string	"FP"
	.byte	0x3
	.byte	0x79
	.4byte	0xc9
	.uleb128 0x4
	.4byte	.LASF22
	.byte	0x4
	.byte	0x53
	.4byte	0xfb
	.uleb128 0x4
	.4byte	.LASF23
	.byte	0x4
	.byte	0x5c
	.4byte	0x151
	.uleb128 0x7
	.byte	0x4
	.4byte	0x157
	.uleb128 0x8
	.4byte	0x162
	.uleb128 0x9
	.4byte	0x85
	.byte	0
	.uleb128 0x4
	.4byte	.LASF24
	.byte	0x4
	.byte	0x5d
	.4byte	0x16d
	.uleb128 0x7
	.byte	0x4
	.4byte	0x173
	.uleb128 0x8
	.4byte	0x183
	.uleb128 0x9
	.4byte	0x13b
	.uleb128 0x9
	.4byte	0x85
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x189
	.uleb128 0x8
	.4byte	0x194
	.uleb128 0x9
	.4byte	0x194
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF25
	.uleb128 0x5
	.4byte	.LASF27
	.byte	0x8
	.byte	0x5
	.byte	0x45
	.4byte	0x1c0
	.uleb128 0xc
	.string	"sp"
	.byte	0x5
	.byte	0x46
	.4byte	0x194
	.byte	0
	.uleb128 0xc
	.string	"pc"
	.byte	0x5
	.byte	0x47
	.4byte	0x131
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF29
	.byte	0x5
	.byte	0x48
	.4byte	0x19d
	.uleb128 0x5
	.4byte	.LASF30
	.byte	0x8
	.byte	0x6
	.byte	0x3f
	.4byte	0x1f0
	.uleb128 0x6
	.4byte	.LASF31
	.byte	0x6
	.byte	0x40
	.4byte	0x1f0
	.byte	0
	.uleb128 0x6
	.4byte	.LASF32
	.byte	0x6
	.byte	0x41
	.4byte	0x1f0
	.byte	0x4
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x1cb
	.uleb128 0x4
	.4byte	.LASF33
	.byte	0x6
	.byte	0x42
	.4byte	0x1cb
	.uleb128 0x4
	.4byte	.LASF34
	.byte	0x7
	.byte	0x3b
	.4byte	0x106
	.uleb128 0x4
	.4byte	.LASF35
	.byte	0x7
	.byte	0x40
	.4byte	0x183
	.uleb128 0x5
	.4byte	.LASF36
	.byte	0xc
	.byte	0x7
	.byte	0x42
	.4byte	0x248
	.uleb128 0x6
	.4byte	.LASF37
	.byte	0x7
	.byte	0x43
	.4byte	0xfb
	.byte	0
	.uleb128 0x6
	.4byte	.LASF38
	.byte	0x7
	.byte	0x44
	.4byte	0x20c
	.byte	0x4
	.uleb128 0xc
	.string	"arg"
	.byte	0x7
	.byte	0x45
	.4byte	0x194
	.byte	0x8
	.byte	0
	.uleb128 0x4
	.4byte	.LASF39
	.byte	0x7
	.byte	0x46
	.4byte	0x217
	.uleb128 0x7
	.byte	0x4
	.4byte	0x248
	.uleb128 0xd
	.4byte	.LASF78
	.byte	0x4
	.byte	0x8
	.byte	0xa4
	.4byte	0x27c
	.uleb128 0xe
	.4byte	.LASF40
	.byte	0x8
	.byte	0xa5
	.4byte	0x111
	.uleb128 0xe
	.4byte	.LASF41
	.byte	0x8
	.byte	0xa6
	.4byte	0x253
	.byte	0
	.uleb128 0x4
	.4byte	.LASF42
	.byte	0x8
	.byte	0xa7
	.4byte	0x259
	.uleb128 0x5
	.4byte	.LASF43
	.byte	0x20
	.byte	0x8
	.byte	0xb7
	.4byte	0x2f4
	.uleb128 0x6
	.4byte	.LASF44
	.byte	0x8
	.byte	0xb8
	.4byte	0x11b
	.byte	0
	.uleb128 0x6
	.4byte	.LASF45
	.byte	0x8
	.byte	0xb9
	.4byte	0x85
	.byte	0x4
	.uleb128 0x6
	.4byte	.LASF46
	.byte	0x8
	.byte	0xba
	.4byte	0x146
	.byte	0x8
	.uleb128 0x6
	.4byte	.LASF47
	.byte	0x8
	.byte	0xbb
	.4byte	0xfb
	.byte	0xc
	.uleb128 0x6
	.4byte	.LASF48
	.byte	0x8
	.byte	0xc0
	.4byte	0x126
	.byte	0x10
	.uleb128 0xc
	.string	"stk"
	.byte	0x8
	.byte	0xc1
	.4byte	0x194
	.byte	0x14
	.uleb128 0x6
	.4byte	.LASF49
	.byte	0x8
	.byte	0xc4
	.4byte	0x11b
	.byte	0x18
	.uleb128 0x6
	.4byte	.LASF50
	.byte	0x8
	.byte	0xc5
	.4byte	0x162
	.byte	0x1c
	.byte	0
	.uleb128 0x4
	.4byte	.LASF51
	.byte	0x8
	.byte	0xc6
	.4byte	0x287
	.uleb128 0x5
	.4byte	.LASF52
	.byte	0x20
	.byte	0x8
	.byte	0xeb
	.4byte	0x38e
	.uleb128 0x6
	.4byte	.LASF53
	.byte	0x8
	.byte	0xec
	.4byte	0x1f6
	.byte	0
	.uleb128 0x6
	.4byte	.LASF54
	.byte	0x8
	.byte	0xed
	.4byte	0x38e
	.byte	0x8
	.uleb128 0x6
	.4byte	.LASF55
	.byte	0x8
	.byte	0xf0
	.4byte	0x41
	.byte	0xc
	.uleb128 0x6
	.4byte	.LASF56
	.byte	0x8
	.byte	0xf5
	.4byte	0x41
	.byte	0xd
	.uleb128 0xf
	.4byte	.LASF57
	.byte	0x8
	.byte	0xfa
	.4byte	0x2c
	.byte	0x4
	.byte	0x1
	.byte	0xf
	.byte	0xc
	.uleb128 0xf
	.4byte	.LASF58
	.byte	0x8
	.byte	0xfb
	.4byte	0x2c
	.byte	0x4
	.byte	0x1
	.byte	0xe
	.byte	0xc
	.uleb128 0xf
	.4byte	.LASF59
	.byte	0x8
	.byte	0xfc
	.4byte	0x2c
	.byte	0x4
	.byte	0x1
	.byte	0xd
	.byte	0xc
	.uleb128 0x6
	.4byte	.LASF60
	.byte	0x8
	.byte	0xfe
	.4byte	0x13b
	.byte	0x10
	.uleb128 0x6
	.4byte	.LASF61
	.byte	0x8
	.byte	0xff
	.4byte	0x399
	.byte	0x14
	.uleb128 0x10
	.4byte	.LASF62
	.byte	0x8
	.2byte	0x100
	.4byte	0x1c0
	.byte	0x18
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x394
	.uleb128 0x11
	.4byte	0x2f4
	.uleb128 0x7
	.byte	0x4
	.4byte	0x27c
	.uleb128 0x12
	.string	"TCB"
	.byte	0x8
	.2byte	0x101
	.4byte	0x2ff
	.uleb128 0x13
	.4byte	.LASF63
	.byte	0x1
	.byte	0x3c
	.4byte	.LFB58
	.4byte	.LFE58-.LFB58
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x13
	.4byte	.LASF64
	.byte	0x1
	.byte	0x48
	.4byte	.LFB59
	.4byte	.LFE59-.LFB59
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x14
	.4byte	.LASF65
	.byte	0x5
	.byte	0x61
	.4byte	0x41
	.uleb128 0x14
	.4byte	.LASF66
	.byte	0x5
	.byte	0x63
	.4byte	0xe5
	.uleb128 0x15
	.4byte	0x5a
	.4byte	0x3ee
	.uleb128 0x16
	.byte	0
	.uleb128 0x14
	.4byte	.LASF67
	.byte	0x5
	.byte	0x65
	.4byte	0x3e3
	.uleb128 0x14
	.4byte	.LASF68
	.byte	0x5
	.byte	0x67
	.4byte	0x3e3
	.uleb128 0x14
	.4byte	.LASF69
	.byte	0x5
	.byte	0x69
	.4byte	0x41
	.uleb128 0x14
	.4byte	.LASF70
	.byte	0x7
	.byte	0x65
	.4byte	0x201
	.uleb128 0x17
	.4byte	.LASF71
	.byte	0x1
	.byte	0x53
	.4byte	0x6c
	.uleb128 0x5
	.byte	0x3
	.4byte	_BIT_REF_4
	.uleb128 0x17
	.4byte	.LASF72
	.byte	0x1
	.byte	0x54
	.4byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	_BIT_REF_2
	.uleb128 0x17
	.4byte	.LASF73
	.byte	0x1
	.byte	0x55
	.4byte	0x41
	.uleb128 0x5
	.byte	0x3
	.4byte	_BIT_REF_1
	.uleb128 0x17
	.4byte	.LASF74
	.byte	0x1
	.byte	0x57
	.4byte	0x39f
	.uleb128 0x5
	.byte	0x3
	.4byte	_BIT_LB_TCB_enatex
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x17
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0xc
	.uleb128 0xb
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF75:
	.string	"GNU C 4.9-GNUV850_v14.01 -mv850e2v3 -mdisable-callt -g -O2"
.LASF35:
	.string	"CBACK"
.LASF55:
	.string	"tstat"
.LASF12:
	.string	"uintptr_t"
.LASF40:
	.string	"wercd"
.LASF60:
	.string	"texptn"
.LASF77:
	.string	"/mnt/c/project/esm/mros-v1_1_refactoring/mROS_athrill/mros_ws/app"
.LASF10:
	.string	"long long unsigned int"
.LASF18:
	.string	"int_t"
.LASF59:
	.string	"enatex"
.LASF21:
	.string	"SIZE"
.LASF9:
	.string	"long long int"
.LASF2:
	.string	"signed char"
.LASF58:
	.string	"wupque"
.LASF17:
	.string	"bool_t"
.LASF67:
	.string	"saved_imr"
.LASF19:
	.string	"uint_t"
.LASF1:
	.string	"long int"
.LASF61:
	.string	"p_winfo"
.LASF47:
	.string	"ipriority"
.LASF6:
	.string	"uint16_t"
.LASF15:
	.string	"double"
.LASF72:
	.string	"BIT_REF_2"
.LASF24:
	.string	"TEXRTN"
.LASF71:
	.string	"BIT_REF_4"
.LASF50:
	.string	"texrtn"
.LASF48:
	.string	"stksz"
.LASF0:
	.string	"unsigned int"
.LASF49:
	.string	"texatr"
.LASF13:
	.string	"long unsigned int"
.LASF70:
	.string	"_kernel_next_time"
.LASF20:
	.string	"ulong_t"
.LASF41:
	.string	"p_tmevtb"
.LASF30:
	.string	"queue"
.LASF66:
	.string	"lock_flag"
.LASF7:
	.string	"short unsigned int"
.LASF45:
	.string	"exinf"
.LASF38:
	.string	"callback"
.LASF56:
	.string	"priority"
.LASF11:
	.string	"intptr_t"
.LASF25:
	.string	"sizetype"
.LASF34:
	.string	"EVTTIM"
.LASF23:
	.string	"TASK"
.LASF28:
	.string	"TOPPERS_dummy_field"
.LASF69:
	.string	"intnest"
.LASF44:
	.string	"tskatr"
.LASF14:
	.string	"float"
.LASF68:
	.string	"disint_table"
.LASF57:
	.string	"actque"
.LASF22:
	.string	"TEXPTN"
.LASF36:
	.string	"time_event_block"
.LASF32:
	.string	"p_prev"
.LASF39:
	.string	"TMEVTB"
.LASF3:
	.string	"unsigned char"
.LASF26:
	.string	"TOPPERS_dummy_t"
.LASF73:
	.string	"BIT_REF_1"
.LASF64:
	.string	"sil_endian"
.LASF4:
	.string	"short int"
.LASF31:
	.string	"p_next"
.LASF54:
	.string	"p_tinib"
.LASF8:
	.string	"uint32_t"
.LASF63:
	.string	"makeoffset"
.LASF16:
	.string	"TOPPERS_fp_t"
.LASF37:
	.string	"index"
.LASF46:
	.string	"task"
.LASF29:
	.string	"TSKCTXB"
.LASF51:
	.string	"TINIB"
.LASF33:
	.string	"QUEUE"
.LASF52:
	.string	"task_control_block"
.LASF53:
	.string	"task_queue"
.LASF74:
	.string	"BIT_LB_TCB_enatex"
.LASF78:
	.string	"waiting_information"
.LASF5:
	.string	"uint8_t"
.LASF27:
	.string	"task_context_block"
.LASF42:
	.string	"WINFO"
.LASF62:
	.string	"tskctxb"
.LASF43:
	.string	"task_initialization_block"
.LASF76:
	.string	"../../../../mros/asp-athrill-mbed/asp-athrill/arch/v850_gcc/makeoffset.c"
.LASF65:
	.string	"current_intpri"
	.ident	"GCC: (GNU) 4.9-GNUV850_v14.01"
