/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM mce

#if !defined(_TRACE_MCE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_MCE_H

#include <linux/ktime.h>
#include <linux/tracepoint.h>
#include <asm/mce.h>

TRACE_EVENT(mce_func,

	TP_PROTO(const char *func, int line),

	TP_ARGS(func, line),

	TP_STRUCT__entry(
		__string(	name,	func	)
		__field(	int,	line	)
	),

	TP_fast_assign(
		__entry->line = line;
		__assign_str(name, func);
	),

	TP_printk("%s:%d", __get_str(name), __entry->line)
);

TRACE_EVENT(mce_func_msrl,

	TP_PROTO(const char *func, int line, u32 msr),

	TP_ARGS(func, line, msr),

	TP_STRUCT__entry(
		__string(	name,	func	)
		__field(	int,	line	)
		__field(	u32,	msr	)
	),

	TP_fast_assign(
		__assign_str(name, func);
		__entry->line = line;
		__entry->msr = msr;
	),

	TP_printk("%s:%d msr:0x%x", __get_str(name), __entry->line, __entry->msr)
);

TRACE_EVENT(mce_func_msrl_ret,

	TP_PROTO(const char *func, int line, u32 msr, u64 val),

	TP_ARGS(func, line, msr, val),

	TP_STRUCT__entry(
		__string(	name,	func	)
		__field(	int,	line	)
		__field(	u32,	msr	)
		__field(	u64,	val	)
	),

	TP_fast_assign(
		__assign_str(name, func);
		__entry->line = line;
		__entry->msr = msr;
		__entry->val = val;
	),

	TP_printk("%s:%d msr:0x%x val:0x%llx", __get_str(name), __entry->line, __entry->msr, __entry->val)
);

TRACE_EVENT(mce_record,

	TP_PROTO(struct mce *m),

	TP_ARGS(m),

	TP_STRUCT__entry(
		__field(	u64,		mcgcap		)
		__field(	u64,		mcgstatus	)
		__field(	u64,		status		)
		__field(	u64,		addr		)
		__field(	u64,		misc		)
		__field(	u64,		synd		)
		__field(	u64,		ipid		)
		__field(	u64,		ip		)
		__field(	u64,		tsc		)
		__field(	u64,		walltime	)
		__field(	u32,		cpu		)
		__field(	u32,		cpuid		)
		__field(	u32,		apicid		)
		__field(	u32,		socketid	)
		__field(	u8,		cs		)
		__field(	u8,		bank		)
		__field(	u8,		cpuvendor	)
	),

	TP_fast_assign(
		__entry->mcgcap		= m->mcgcap;
		__entry->mcgstatus	= m->mcgstatus;
		__entry->status		= m->status;
		__entry->addr		= m->addr;
		__entry->misc		= m->misc;
		__entry->synd		= m->synd;
		__entry->ipid		= m->ipid;
		__entry->ip		= m->ip;
		__entry->tsc		= m->tsc;
		__entry->walltime	= m->time;
		__entry->cpu		= m->extcpu;
		__entry->cpuid		= m->cpuid;
		__entry->apicid		= m->apicid;
		__entry->socketid	= m->socketid;
		__entry->cs		= m->cs;
		__entry->bank		= m->bank;
		__entry->cpuvendor	= m->cpuvendor;
	),

	TP_printk("CPU: %d, MCGc/s: %llx/%llx, MC%d: %016Lx, IPID: %016Lx, ADDR/MISC/SYND: %016Lx/%016Lx/%016Lx, RIP: %02x:<%016Lx>, TSC: %llx, PROCESSOR: %u:%x, TIME: %llu, SOCKET: %u, APIC: %x",
		__entry->cpu,
		__entry->mcgcap, __entry->mcgstatus,
		__entry->bank, __entry->status,
		__entry->ipid,
		__entry->addr, __entry->misc, __entry->synd,
		__entry->cs, __entry->ip,
		__entry->tsc,
		__entry->cpuvendor, __entry->cpuid,
		__entry->walltime,
		__entry->socketid,
		__entry->apicid)
);

#endif /* _TRACE_MCE_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
