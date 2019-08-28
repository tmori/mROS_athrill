/* kernel_cfg.c */
#include "kernel/kernel_int.h"
#include "kernel_cfg.h"

#if TKERNEL_PRID != 0x07u
#error The kernel does not match this configuration file.
#endif

/*
 *  Include Directives (#include)
 */

#include "target_timer.h"
#include "syssvc/syslog.h"
#include "syssvc/banner.h"
#include "target_syssvc.h"
#include "target_serial.h"
#include "syssvc/serial.h"
#include "syssvc/logtask.h"
#include "../../../../fork/mROS/mros-lib/mros-src/config/os/target/os_asp/mros_os_config.h"
#include "app.h"

/*
 *  Default Definitions of Trace Log Macros
 */

#ifndef LOG_ISR_ENTER
#define LOG_ISR_ENTER(intno)
#endif /* LOG_ISR_ENTER */

#ifndef LOG_ISR_LEAVE
#define LOG_ISR_LEAVE(intno)
#endif /* LOG_ISR_LEAVE */

/*
 *  Task Management Functions
 */

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

static STK_T _kernel_stack_LOGTASK[COUNT_STK_T(LOGTASK_STACK_SIZE)]  __attribute__ ((section(".bss_noclr")));
static STK_T _kernel_stack_MAIN_TASK[COUNT_STK_T(MROS_TASK_STACK_SIZE)]  __attribute__ ((section(".bss_noclr")));
static STK_T _kernel_stack_PUB_TASK[COUNT_STK_T(MROS_TASK_STACK_SIZE)]  __attribute__ ((section(".bss_noclr")));
static STK_T _kernel_stack_SUB_TASK[COUNT_STK_T(MROS_TASK_STACK_SIZE)]  __attribute__ ((section(".bss_noclr")));
static STK_T _kernel_stack_XML_SLV_TASK[COUNT_STK_T(MROS_TASK_STACK_SIZE)]  __attribute__ ((section(".bss_noclr")));
static STK_T _kernel_stack_XML_MAS_TASK[COUNT_STK_T(MROS_TASK_STACK_SIZE)]  __attribute__ ((section(".bss_noclr")));
static STK_T _kernel_stack_USR_TASK1[COUNT_STK_T(MROS_USR1_STACK_SIZE)]  __attribute__ ((section(".bss_noclr")));
static STK_T _kernel_stack_USR_TASK2[COUNT_STK_T(MROS_USR2_STACK_SIZE)]  __attribute__ ((section(".bss_noclr")));

const TINIB _kernel_tinib_table[TNUM_TSKID] = {
	{ (TA_ACT), (intptr_t)(LOGTASK_PORTID), ((TASK)(logtask_main)), INT_PRIORITY(LOGTASK_PRIORITY), ROUND_STK_T(LOGTASK_STACK_SIZE), _kernel_stack_LOGTASK, (TA_NULL), (NULL) },
	{ (TA_ACT), (intptr_t)(0), ((TASK)(main_task)), INT_PRIORITY(MAIN_TASK_PRI), ROUND_STK_T(MROS_TASK_STACK_SIZE), _kernel_stack_MAIN_TASK, (TA_NULL), (NULL) },
	{ (TA_NULL), (intptr_t)(0), ((TASK)(pub_task)), INT_PRIORITY(MROS_TASK_PRI), ROUND_STK_T(MROS_TASK_STACK_SIZE), _kernel_stack_PUB_TASK, (TA_NULL), (NULL) },
	{ (TA_NULL), (intptr_t)(0), ((TASK)(sub_task)), INT_PRIORITY(MROS_TASK_PRI), ROUND_STK_T(MROS_TASK_STACK_SIZE), _kernel_stack_SUB_TASK, (TA_NULL), (NULL) },
	{ (TA_NULL), (intptr_t)(0), ((TASK)(xml_slv_task)), INT_PRIORITY(MROS_TASK_PRI), ROUND_STK_T(MROS_TASK_STACK_SIZE), _kernel_stack_XML_SLV_TASK, (TA_NULL), (NULL) },
	{ (TA_NULL), (intptr_t)(0), ((TASK)(xml_mas_task)), INT_PRIORITY(MROS_TASK_PRI), ROUND_STK_T(MROS_TASK_STACK_SIZE), _kernel_stack_XML_MAS_TASK, (TA_NULL), (NULL) },
	{ (TA_NULL), (intptr_t)(0), ((TASK)(usr_task1)), INT_PRIORITY(MROS_USR_TASK1_PRI), ROUND_STK_T(MROS_USR1_STACK_SIZE), _kernel_stack_USR_TASK1, (TA_NULL), (NULL) },
	{ (TA_NULL), (intptr_t)(0), ((TASK)(usr_task2)), INT_PRIORITY(MROS_USR_TASK2_PRI), ROUND_STK_T(MROS_USR2_STACK_SIZE), _kernel_stack_USR_TASK2, (TA_NULL), (NULL) }
};

TCB _kernel_tcb_table[TNUM_TSKID];

const ID _kernel_torder_table[TNUM_TSKID] = {
	LOGTASK, MAIN_TASK, PUB_TASK, SUB_TASK, XML_SLV_TASK, XML_MAS_TASK, USR_TASK1, USR_TASK2
};

/*
 *  Semaphore Functions
 */

const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);

const SEMINIB _kernel_seminib_table[TNUM_SEMID] = {
	{ (TA_TPRI), (0), (1) },
	{ (TA_TPRI), (1), (1) },
	{ (TA_TPRI), (0), (1) },
	{ (TA_TPRI), (1), (1) },
	{ (TA_TPRI), (0), (1) },
	{ (TA_TPRI), (1), (1) },
	{ (TA_TPRI), (0), (1) },
	{ (TA_TPRI), (1), (1) }
};

SEMCB _kernel_semcb_table[TNUM_SEMID];

/*
 *  Eventflag Functions
 */

const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);

TOPPERS_EMPTY_LABEL(const FLGINIB, _kernel_flginib_table);
TOPPERS_EMPTY_LABEL(FLGCB, _kernel_flgcb_table);

/*
 *  Dataqueue Functions
 */

const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);

TOPPERS_EMPTY_LABEL(const DTQINIB, _kernel_dtqinib_table);
TOPPERS_EMPTY_LABEL(DTQCB, _kernel_dtqcb_table);

/*
 *  Priority Dataqueue Functions
 */

const ID _kernel_tmax_pdqid = (TMIN_PDQID + TNUM_PDQID - 1);

TOPPERS_EMPTY_LABEL(const PDQINIB, _kernel_pdqinib_table);
TOPPERS_EMPTY_LABEL(PDQCB, _kernel_pdqcb_table);

/*
 *  Mailbox Functions
 */

const ID _kernel_tmax_mbxid = (TMIN_MBXID + TNUM_MBXID - 1);

TOPPERS_EMPTY_LABEL(const MBXINIB, _kernel_mbxinib_table);
TOPPERS_EMPTY_LABEL(MBXCB, _kernel_mbxcb_table);

/*
 *  Fixed-sized Memorypool Functions
 */

const ID _kernel_tmax_mpfid = (TMIN_MPFID + TNUM_MPFID - 1);

TOPPERS_EMPTY_LABEL(const MPFINIB, _kernel_mpfinib_table);
TOPPERS_EMPTY_LABEL(MPFCB, _kernel_mpfcb_table);

/*
 *  Cyclic Handler Functions
 */

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);

const CYCINIB _kernel_cycinib_table[TNUM_CYCID] = {
	{ (TA_STA), (intptr_t)(0), (cyclic_handler), (MROS_LOOP_RATE), (1) }
};

CYCCB _kernel_cyccb_table[TNUM_CYCID];

/*
 *  Alarm Handler Functions
 */

const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);

TOPPERS_EMPTY_LABEL(const ALMINIB, _kernel_alminib_table);
TOPPERS_EMPTY_LABEL(ALMCB, _kernel_almcb_table);

/*
 *  Interrupt Management Functions
 */

void
_kernel_inthdr_44(void)
{
	i_begin_int(44);
	LOG_ISR_ENTER(44);
	((ISR)(sio_rx_isr))((intptr_t)(SIO_PORTID));
	LOG_ISR_LEAVE(44);
	i_end_int(44);
}
void
_kernel_inthdr_45(void)
{
	i_begin_int(45);
	LOG_ISR_ENTER(45);
	((ISR)(sio_tx_isr))((intptr_t)(SIO_PORTID));
	LOG_ISR_LEAVE(45);
	i_end_int(45);
}

#define TNUM_INHNO	3
const uint_t _kernel_tnum_inhno = TNUM_INHNO;

INTHDR_ENTRY(INHNO_TIMER, 22, target_timer_handler)
INTHDR_ENTRY(44, 44, _kernel_inthdr_44)
INTHDR_ENTRY(45, 45, _kernel_inthdr_45)

const INHINIB _kernel_inhinib_table[TNUM_INHNO] = {
	{ (INHNO_TIMER), (TA_NULL), (FP)(INT_ENTRY(INHNO_TIMER, target_timer_handler)) },
	{ (44), (TA_NULL), (FP)(INT_ENTRY(44, _kernel_inthdr_44)) },
	{ (45), (TA_NULL), (FP)(INT_ENTRY(45, _kernel_inthdr_45)) }
};

#define TNUM_INTNO	3
const uint_t _kernel_tnum_intno = TNUM_INTNO;

const INTINIB _kernel_intinib_table[TNUM_INTNO] = {
	{ (INTNO_TIMER), (TA_ENAINT | INTATR_TIMER), (INTPRI_TIMER) },
	{ (INTNO_SIO_TX), (INTATR_SIO), (INTPRI_SIO) },
	{ (INTNO_SIO_RX), (INTATR_SIO), (INTPRI_SIO) }
};

/*
 *  CPU Exception Management Functions
 */

/*
 *  Stack Area for Non-task Context
 */

#ifdef DEFAULT_ISTK

#define TOPPERS_ISTKSZ		DEFAULT_ISTKSZ
#define TOPPERS_ISTK		DEFAULT_ISTK

#else /* DEAULT_ISTK */

static STK_T				_kernel_istack[COUNT_STK_T(DEFAULT_ISTKSZ)]  __attribute__ ((section(".bss_noclr")));
#define TOPPERS_ISTKSZ		ROUND_STK_T(DEFAULT_ISTKSZ)
#define TOPPERS_ISTK		_kernel_istack

#endif /* DEAULT_ISTK */

const SIZE		_kernel_istksz = TOPPERS_ISTKSZ;
STK_T *const	_kernel_istk = TOPPERS_ISTK;

#ifdef TOPPERS_ISTKPT
STK_T *const	_kernel_istkpt = TOPPERS_ISTKPT(TOPPERS_ISTK, TOPPERS_ISTKSZ);
#endif /* TOPPERS_ISTKPT */

/*
 *  Time Event Management
 */

TMEVTN   _kernel_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID];

/*
 *  Module Initialization Function
 */

void
_kernel_initialize_object(void)
{
	_kernel_initialize_task();
	_kernel_initialize_semaphore();
	_kernel_initialize_cyclic();
	_kernel_initialize_interrupt();
	_kernel_initialize_exception();
}

/*
 *  Initialization Routine
 */

void
_kernel_call_inirtn(void)
{
	((INIRTN)(target_timer_initialize))((intptr_t)(0));
	((INIRTN)(syslog_initialize))((intptr_t)(0));
	((INIRTN)(print_banner))((intptr_t)(0));
	((INIRTN)(sio_initialize))((intptr_t)(0));
	((INIRTN)(serial_initialize))((intptr_t)(0));
}

/*
 *  Termination Routine
 */

void
_kernel_call_terrtn(void)
{
	((TERRTN)(logtask_terminate))((intptr_t)(0));
	((TERRTN)(target_timer_terminate))((intptr_t)(0));
}

const uint16_t imr_table[][IMR_SIZE] = 
{
	{ 0xffff , 0xffbf , 0xcfff , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff } , 
	{ 0xffff , 0xffbf , 0xcfff , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff } , 
	{ 0xffff , 0xffbf , 0xcfff , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff } , 
	{ 0xffff , 0xffbf , 0xcfff , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff } , 
	{ 0xffff , 0xffbf , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff } , 
	{ 0xffff , 0xffbf , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff } , 
	{ 0xffff , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff } , 
	{ 0xffff , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff , 0xffff }
};

