#ifndef OUROBOROS_ARCH_MIPS_CP0_H
#define OUROBOROS_ARCH_MIPS_CP0_H

/* Cache coherency attributes */
#define MIPS_CP0_CACHE_ATTR			(0x7)
#define MIPS_CP0_CACHE_ATTR_ATTR(attr)		((attr) & MIPS_CP0_CACHE_ATTR)

/* Cacheable, noncoherent, write-through, no write allocate */
#define MIPS_CP0_CACHE_ATTR_CNWTNA		(0x0)
/* Uncached */
#define MIPS_CP0_CACHE_ATTR_U			(0x2)
/* Cacheable, noncoherent, write-back, write allocate */
#define MIPS_CP0_CACHE_ATTR_CNWBA		(0x3)
/* Uncached accelerated */
#define MIPS_CP0_CACHE_ATTR_UA			(0x7)

/* TLB array index */
#define MIPS_CP0_INDEX				$0, 0

/* Probe Failure */
#define MIPS_CP0_INDEX_P			(0x80000000)
/* Index to the entry */
#define MIPS_CP0_INDEX_INDEX			(0x0000003F)
#define MIPS_CP0_INDEX_INDEX_INDEX(n)		((n) & MIPS_CP0_INDEX_INDEX)

/* TLB array random index */
#define MIPS_CP0_RANDOM				$1, 0

/* Index to the entry */
#define MIPS_CP0_RANDOM_RANDOM			(0x0000003F)

/* TLB entry low-order word (even-numbered pages) */
#define MIPS_CP0_ENTRY_LO0			$2, 0
/* TLB entry low-order word (odd-numbered pages) */
#define MIPS_CP0_ENTRY_LO1			$3, 0

/* Page Frame Number */
#define MIPS_CP0_ENTRY_LO_PFN			(0x03FFFFC0)
#define MIPS_CP0_ENTRY_LO_PFN_PFN(a)		(((a) >> 6) & MIPS_CP0_ENTRY_LO_PFN)
/* Coherency */
#define MIPS_CP0_ENTRY_LO_C			(0x00000038)
#define MIPS_CP0_ENTRY_LO_C_C(attr)		(MIPS_CP0_CACHE_ATTR_ATTR(attr) << 3)
/* Dirty */
#define MIPS_CP0_ENTRY_LO_D			(0x00000004)
/* Valid */
#define MIPS_CP0_ENTRY_LO_V			(0x00000002)
/* Global */
#define MIPS_CP0_ENTRY_LO_G			(0x00000001)

/* Page table entry */
#define MIPS_CP0_CONTEXT			$4, 0

/* PTE base */
#define MIPS_CP0_CONTEXT_PTEBASE		(0xFF800000)
/* Missed virtual address */
#define MIPS_CP0_CONTEXT_BADVPN2		(0x007FFFF0)

/* User information */
#define MIPS_CP0_USER_LOCAL			$4, 2

/* Control for variable page sizes in TLB entries */
#define MIPS_CP0_PAGE_MASK			$5, 0

/* Mask */
#define MIPS_CP0_PAGE_MASK_MASK			(0x1FFFE000)
#define MIPS_CP0_PAGE_MASK_MASK_4K		(0x00000000)
#define MIPS_CP0_PAGE_MASK_MASK_16K		(0x00006000)
#define MIPS_CP0_PAGE_MASK_MASK_64K		(0x0001E000)
#define MIPS_CP0_PAGE_MASK_MASK_256K		(0x0007E000)
#define MIPS_CP0_PAGE_MASK_MASK_1M		(0x001FE000)
#define MIPS_CP0_PAGE_MASK_MASK_4M		(0x007FE000)
#define MIPS_CP0_PAGE_MASK_MASK_16M		(0x01FFE000)
#define MIPS_CP0_PAGE_MASK_MASK_64M		(0x07FFE000)
#define MIPS_CP0_PAGE_MASK_MASK_256M		(0x1FFFE000)

/* Wired Register */
#define MIPS_CP0_WIRED				$6, 0

/* Wired */
#define MIPS_CP0_WIRED_WIRED			(0x0000003F)

/* HWREna Register */
#define MIPS_CP0_HWRENA				$7, 0

/* Mask */
#define MIPS_CP0_HWRENA_MASK			(0x3FFFFFFF)

/* BadVAddr Register */
#define MIPS_CP0_BADVADDR			$8, 0

/* BadInstr Register */
#define MIPS_CP0_BADINSTR			$8, 1

/* BadInstrP Register */
#define MIPS_CP0_BADINSTRP			$8, 2

/* Count Register */
#define MIPS_CP0_COUNT				$9, 0

/* TLB entry high-order word */
#define MIPS_CP0_ENTRY_HO			$10, 0

/* VPN2 */
#define MIPS_CP0_ENTRY_HO_VPN2			(0xFFFFE000)
#define MIPS_CP0_ENTRY_HO_VPN2_VPN2(a)		((a) & MIPS_CP0_ENTRY_HO_VPN2)

/* ASID */
#define MIPS_CP0_ENTRY_HO_ASID			(0x000000FF)
#define MIPS_CP0_ENTRY_HO_ASID_ASID(i)		((i) & MIPS_CP0_ENTRY_HO_ASID)

/* Compare Register */
#define MIPS_CP0_COMPARE			$11, 0

/* Status Register */
#define MIPS_CP0_STATUS				$12, 0

/* Coprocessor 2 */
#define MIPS_CP0_STATUS_CU2			(0x40000000)
/* Coprocessor 1 */
#define MIPS_CP0_STATUS_CU1			(0x20000000)
/* Coprocessor 0 */
#define MIPS_CP0_STATUS_CU0			(0x10000000)
/* Reduced power */
#define MIPS_CP0_STATUS_RP			(0x08000000)
/* Floating point register mode */
#define MIPS_CP0_STATUS_FR			(0x04000000)
/* Reverse-endian memory references */
#define MIPS_CP0_STATUS_RE			(0x02000000)
/* Access to DSP ASE resources */
#define MIPS_CP0_STATUS_MX			(0x01000000)
/* Location of exception vectors */
#define MIPS_CP0_STATUS_BEV			(0x00400000)
/* TLB shutdown */
#define MIPS_CP0_STATUS_TS			(0x00200000)
/* Soft reset */
#define MIPS_CP0_STATUS_SR			(0x00100000)
/* Entry was due to NMI */
#define MIPS_CP0_STATUS_NMI			(0x00080000)
/* CorExtend Enable */
#define MIPS_CP0_STATUS_CEE			(0x00020000)
/* Interrupt Mask */
#define MIPS_CP0_STATUS_IM7			(0x00008000)
#define MIPS_CP0_STATUS_IM6			(0x00004000)
#define MIPS_CP0_STATUS_IM5			(0x00002000)
#define MIPS_CP0_STATUS_IM4			(0x00001000)
#define MIPS_CP0_STATUS_IM3			(0x00000800)
#define MIPS_CP0_STATUS_IM2			(0x00000400)
/* Interrupt Priority Level */
#define MIPS_CP0_STATUS_IPL			(0x00007C00)
/* Interrupt Mask */
#define MIPS_CP0_STATUS_IM1			(0x00000200)
#define MIPS_CP0_STATUS_IM0			(0x00000100)
/* Kernel/Supervisor/User Mode */
#define MIPS_CP0_STATUS_KSU			(0x00000018)
#define MIPS_CP0_STATUS_KSU_K			(0x00000000)
#define MIPS_CP0_STATUS_KSU_S			(0x00000008)
#define MIPS_CP0_STATUS_KSU_U			(0x00000010)
/* Error Level */
#define MIPS_CP0_STATUS_ERL			(0x00000004)
/* Exception Level */
#define MIPS_CP0_STATUS_EXL			(0x00000002)
/* Interrupts Enabled */
#define MIPS_CP0_STATUS_IE			(0x00000001)

/* IntCtl Register */
#define MIPS_CP0_INTCTL				$12, 1

/* IP number for timer interrupt */
#define MIPS_CP0_INTCTL_IPTI			(0xE0000000)
#define MIPS_CP0_INTCTL_IPTI_HW0		(0x40000000)
#define MIPS_CP0_INTCTL_IPTI_HW1		(0x60000000)
#define MIPS_CP0_INTCTL_IPTI_HW2		(0x80000000)
#define MIPS_CP0_INTCTL_IPTI_HW3		(0xA0000000)
#define MIPS_CP0_INTCTL_IPTI_HW4		(0xC0000000)
#define MIPS_CP0_INTCTL_IPTI_HW5		(0xE0000000)
/* IP number for performance counter interrupt */
#define MIPS_CP0_INTCTL_IPPCI			(0x1C000000)
#define MIPS_CP0_INTCTL_IPPCI_HW0		(0x08000000)
#define MIPS_CP0_INTCTL_IPPCI_HW1		(0x0C000000)
#define MIPS_CP0_INTCTL_IPPCI_HW2		(0x10000000)
#define MIPS_CP0_INTCTL_IPPCI_HW3		(0x14000000)
#define MIPS_CP0_INTCTL_IPPCI_HW4		(0x18000000)
#define MIPS_CP0_INTCTL_IPPCI_HW5		(0x1C000000)
/* Vector Spacing */
#define MIPS_CP0_INTCTL_VS			(0x000003E0)
#define MIPS_CP0_INTCTL_VS_000			(0x00000000)
#define MIPS_CP0_INTCTL_VS_020			(0x00000020)
#define MIPS_CP0_INTCTL_VS_040			(0x00000040)
#define MIPS_CP0_INTCTL_VS_060			(0x00000060)
#define MIPS_CP0_INTCTL_VS_080			(0x00000080)
#define MIPS_CP0_INTCTL_VS_100			(0x00000100)
#define MIPS_CP0_INTCTL_VS_200			(0x00000200)

/* SRSCtl Register */
#define MIPS_CP0_SRSCTL				$12, 2

/* Highest Shadow Set */
#define MIPS_CP0_SRSCTL_HSS			(0x3C000000)
#define MIPS_CP0_SRSCTL_HSS_1			(0x00000000)
#define MIPS_CP0_SRSCTL_HSS_2			(0x04000000)
#define MIPS_CP0_SRSCTL_HSS_4			(0x0C000000)
/* EIC interrupt mode shadow set */
#define MIPS_CP0_SRSCTL_EICSS			(0x003C0000)
/* Exception Shadow Set */
#define MIPS_CP0_SRSCTL_ESS			(0x0000F000)
/* Previous Shadow Set */
#define MIPS_CP0_SRSCTL_PSS			(0x000003C0)
/* Current Shadow Set */
#define MIPS_CP0_SRSCTL_CSS			(0x0000000F)

/* SRSMap Register */
#define MIPS_CP0_SRSMAP				$12, 3

/* Vector 7 */
#define MIPS_CP0_SRSMAP_SSV7			(0xF0000000)
/* Vector 6 */
#define MIPS_CP0_SRSMAP_SSV6			(0x0F000000)
/* Vector 5 */
#define MIPS_CP0_SRSMAP_SSV5			(0x00F00000)
/* Vector 4 */
#define MIPS_CP0_SRSMAP_SSV4			(0x000F0000)
/* Vector 3 */
#define MIPS_CP0_SRSMAP_SSV3			(0x0000F000)
/* Vector 2 */
#define MIPS_CP0_SRSMAP_SSV2			(0x00000F00)
/* Vector 1 */
#define MIPS_CP0_SRSMAP_SSV1			(0x000000F0)
/* Vector 0 */
#define MIPS_CP0_SRSMAP_SSV0			(0x0000000F)

/* Cause Register */
#define MIPS_CP0_CAUSE				$13, 0

/* Branch delay */
#define MIPS_CP0_CAUSE_BD			(0x80000000)
/* Timer interrupt */
#define MIPS_CP0_CAUSE_TI			(0x40000000)
/* Coprocessor unit unusable */
#define MIPS_CP0_CAUSE_CE			(0x30000000)
/* Disable Count register */
#define MIPS_CP0_CAUSE_DC			(0x08000000)
/* Performance Counter Interrupt */
#define MIPS_CP0_CAUSE_PCI			(0x04000000)
/* General exception vector or special interrupt vector */
#define MIPS_CP0_CAUSE_IV			(0x00800000)
/* Watch exception deferred */
#define MIPS_CP0_CAUSE_WP			(0x00400000)
/* Interrupt pending */
#define MIPS_CP0_CAUSE_IP7			(0x00008000)
#define MIPS_CP0_CAUSE_IP6			(0x00004000)
#define MIPS_CP0_CAUSE_IP5			(0x00002000)
#define MIPS_CP0_CAUSE_IP4			(0x00001000)
#define MIPS_CP0_CAUSE_IP3			(0x00000800)
#define MIPS_CP0_CAUSE_IP2			(0x00000400)
/* Requested Interrupt Priority Level */
#define MIPS_CP0_CAUSE_RIPL			(0x0000FC00)
/* Interrupt pending */
#define MIPS_CP0_CAUSE_IP1			(0x00000200)
#define MIPS_CP0_CAUSE_IP0			(0x00000100)

/* Exception code */
#define MIPS_CP0_CAUSE_EXC			(0x0000007C)

/* Interrupt */
#define MIPS_CP0_CAUSE_EXC_INT			(0x00 << 2)
/* TLB modification exception */
#define MIPS_CP0_CAUSE_EXC_MOD			(0x01 << 2)
/* TLB exception (load or instruction fetch) */
#define MIPS_CP0_CAUSE_EXC_TLBL			(0x02 << 2)
/* TLB exception (store) */
#define MIPS_CP0_CAUSE_EXC_TLBS			(0x03 << 2)
/* Address error exception (load or instruction fetch) */
#define MIPS_CP0_CAUSE_EXC_ADEL			(0x04 << 2)
/* Address error exception (store) */
#define MIPS_CP0_CAUSE_EXC_ADES			(0x05 << 2)
/* Bus error exception (instruction fetch) */
#define MIPS_CP0_CAUSE_EXC_IBE			(0x06 << 2)
/* Bus error exception (data load or store) */
#define MIPS_CP0_CAUSE_EXC_DBE			(0x07 << 2)
/* Syscall exception */
#define MIPS_CP0_CAUSE_EXC_SYS			(0x08 << 2)
/* Breakpoint exception */
#define MIPS_CP0_CAUSE_EXC_BP			(0x09 << 2)
/* Reserved instruction exception */
#define MIPS_CP0_CAUSE_EXC_RI			(0x0A << 2)
/* Coprocessor unusable exception */
#define MIPS_CP0_CAUSE_EXC_CPU			(0x0B << 2)
/* Arithmetic overflow exception */
#define MIPS_CP0_CAUSE_EXC_OV			(0x0C << 2)
/* Trap exception */
#define MIPS_CP0_CAUSE_EXC_TR			(0x0D << 2)
/* MSA floating point exception */
#define MIPS_CP0_CAUSE_EXC_MSAFPE		(0x0E << 2)
/* Floating point exception */
#define MIPS_CP0_CAUSE_EXC_FPE			(0x0F << 2)
/* Coprocessor 2 exception */
#define MIPS_CP0_CAUSE_EXC_C2E			(0x12 << 2)
/* TLB read-inhibit exception */
#define MIPS_CP0_CAUSE_EXC_TLBRI		(0x13 << 2)
/* TLB execution-inhibit exception */
#define MIPS_CP0_CAUSE_EXC_TLBXI		(0x14 << 2)
/* MSA disabled exception */
#define MIPS_CP0_CAUSE_EXC_MSADIS		(0x15 << 2)
/* MDMX unusable exception */
#define MIPS_CP0_CAUSE_EXC_MDMX			(0x16 << 2)
/* Reference to WatchHi/WatchLo address */
#define MIPS_CP0_CAUSE_EXC_WATCH		(0x17 << 2)
/* Machine check */
#define MIPS_CP0_CAUSE_EXC_MCHECK		(0x18 << 2)
/* Thread allocation, deallocation, or scheduling exceptions */
#define MIPS_CP0_CAUSE_EXC_THREAD		(0x19 << 2)
/* DSP module state disabled exception */
#define MIPS_CP0_CAUSE_EXC_DSPDIS		(0x1A << 2)
/* Virtualized guest exception */
#define MIPS_CP0_CAUSE_EXC_GE			(0x1B << 2)
/* Cache error */
#define MIPS_CP0_CAUSE_EXC_CACHEERR		(0x1E << 2)

/* Exception Program Counter */
#define MIPS_CP0_EPC				$14, 0

/* Processor Identification */
#define MIPS_CP0_PRID				$15, 0

/* Company Option */
#define MIPS_CP0_PRID_CO			(0xFF000000)
/* Company ID */
#define MIPS_CP0_PRID_CI			(0x00FF0000)
/* Processor ID */
#define MIPS_CP0_PRID_PI			(0x0000FF00)
/* Revision */
#define MIPS_CP0_PRID_REV			(0x000000FF)
/* Major Revision */
#define MIPS_CP0_PRID_REV_MJR			(0x000000E0)
/* Minor Revision */
#define MIPS_CP0_PRID_REV_MNR			(0x0000001C)
/* Patch Level */
#define MIPS_CP0_PRID_REV_PL			(0x00000003)

/* EBase Register */
#define MIPS_CP0_EBASE				$15, 1

/* Exception Base */
#define MIPS_CP0_EBASE_EB			(0x3FFFF000)
#define MIPS_CP0_EBASE_EB_EB(a)			((a) & MIPS_CP0_EBASE_EB)
/* CPU Number */
#define MIPS_CP0_EBASE_CPUNUM			(0x000003FF)

/* Config Register */
#define MIPS_CP0_CONFIG				$16, 0

/* Presence of register */
#define MIPS_CP0_CONFIG_M			(0x80000000)
/* Cacheability of kseg2 and kseg3 in FM */
#define MIPS_CP0_CONFIG_K23			(0x70000000)
#define MIPS_CP0_CONFIG_K23_K23(attr)		(MIPS_CP0_CACHE_ATTR_ATTR(attr) << 28)
/* Cacheability of kuseg and useg in FM */
#define MIPS_CP0_CONFIG_KU			(0x0E000000)
#define MIPS_CP0_CONFIG_KU_KU(attr)		(MIPS_CP0_CACHE_ATTR_ATTR(attr) << 25)
/* I-side ScratchPad RAM present */
#define MIPS_CP0_CONFIG_ISP			(0x01000000)
/* D-side ScratchPad RAM present */
#define MIPS_CP0_CONFIG_DSP			(0x00800000)
/* CorExtend User Defined Instructions */
#define MIPS_CP0_CONFIG_UDI			(0x00400000)
/* SimpleBE bus mode enabled */
#define MIPS_CP0_CONFIG_SB			(0x00200000)
/* Write-through merging in 32-byte collapsing write buffer */
#define MIPS_CP0_CONFIG_MM			(0x00040000)
/* Burst order */
#define MIPS_CP0_CONFIG_BM			(0x00010000)
/* Little/big endian */
#define MIPS_CP0_CONFIG_BE			(0x00008000)
/* Architecture type */
#define MIPS_CP0_CONFIG_AT			(0x00006000)
/* Architecture revision level */
#define MIPS_CP0_CONFIG_AR			(0x00001C00)
/* MMU type */
#define MIPS_CP0_CONFIG_MT			(0x00000380)
#define MIPS_CP0_CONFIG_MT_TLB			(0x00000080)
#define MIPS_CP0_CONFIG_MT_FM			(0x00000180)
/* Kseg0 coherency algorithm */
#define MIPS_CP0_CONFIG_K0			(0x00000007)
#define MIPS_CP0_CONFIG_K0_K0(attr)		(MIPS_CP0_CACHE_ATTR_ATTR(attr) << 0)

/* Config1 Register */
#define MIPS_CP0_CONFIG1			$16, 1

/* Presence of register */
#define MIPS_CP0_CONFIG1_M			(0x80000000)
/* MMU size */
#define MIPS_CP0_CONFIG1_MMUSIZE		(0x7E000000)
/* Instruction cache sets per way */
#define MIPS_CP0_CONFIG1_IS			(0x01C00000)
/* Instruction cache line size */
#define MIPS_CP0_CONFIG1_IL			(0x00380000)
#define MIPS_CP0_CONFIG1_IL_NOIC		(0x00000000)
#define MIPS_CP0_CONFIG1_IL_32			(0x00200000)
/* Instruction cache associativity */
#define MIPS_CP0_CONFIG1_IA			(0x00070000)
#define MIPS_CP0_CONFIG1_IA_4			(0x00030000)
/* Data cache sets per way */
#define MIPS_CP0_CONFIG1_DS			(0x0000E000)
#define MIPS_CP0_CONFIG1_DS_64			(0x00000000)
#define MIPS_CP0_CONFIG1_DS_128			(0x00002000)
#define MIPS_CP0_CONFIG1_DS_256			(0x00004000)
#define MIPS_CP0_CONFIG1_DS_512			(0x00006000)
/* Data cache line size */
#define MIPS_CP0_CONFIG1_DL			(0x00001C00)
#define MIPS_CP0_CONFIG1_DL_NODC		(0x00000000)
#define MIPS_CP0_CONFIG1_DL_32			(0x00001000)
/* Data cache associativity */
#define MIPS_CP0_CONFIG1_DA			(0x00000380)
#define MIPS_CP0_CONFIG1_DA_4			(0x00000180)
/* Coprocessor 2 present */
#define MIPS_CP0_CONFIG1_C2			(0x00000040)
/* MDMX implemented */
#define MIPS_CP0_CONFIG1_MD			(0x00000020)
/* Performance Counter registers implemented */
#define MIPS_CP0_CONFIG1_PC			(0x00000010)
/* Watch registers implemented */
#define MIPS_CP0_CONFIG1_WR			(0x00000008)
/* Code compression (MIPS16) implemented */
#define MIPS_CP0_CONFIG1_CA			(0x00000004)
/* EJTAG present */
#define MIPS_CP0_CONFIG1_EP			(0x00000002)
/* FPU implemented */
#define MIPS_CP0_CONFIG1_FP			(0x00000001)

/* Config2 Register */
#define MIPS_CP0_CONFIG2			$16, 2

/* Presence of register */
#define MIPS_CP0_CONFIG2_M			(0x80000000)
/* Tertiary cache control */
#define MIPS_CP0_CONFIG2_TU			(0x70000000)
/* Tertiary cache sets per way */
#define MIPS_CP0_CONFIG2_TS			(0x0F000000)
/* Tertiary cache line size */
#define MIPS_CP0_CONFIG2_TL			(0x00F00000)
/* Tertiary cache associativity */
#define MIPS_CP0_CONFIG2_TA			(0x000F0000)
/* L2 Bypass */
#define MIPS_CP0_CONFIG2_L2B			(0x00001000)
/* Secondary cache sets per way */
#define MIPS_CP0_CONFIG2_SS			(0x00000F00)
#define MIPS_CP0_CONFIG2_SS_64			(0x00000000)
#define MIPS_CP0_CONFIG2_SS_128			(0x00000100)
#define MIPS_CP0_CONFIG2_SS_256			(0x00000200)
#define MIPS_CP0_CONFIG2_SS_512			(0x00000300)
#define MIPS_CP0_CONFIG2_SS_1024		(0x00000400)
#define MIPS_CP0_CONFIG2_SS_2048		(0x00000500)
#define MIPS_CP0_CONFIG2_SS_4096		(0x00000600)
#define MIPS_CP0_CONFIG2_SS_8192		(0x00000700)
/* Secondary cache line size */
#define MIPS_CP0_CONFIG2_SL			(0x000000F0)
#define MIPS_CP0_CONFIG2_SL_NOC			(0x00000000)
#define MIPS_CP0_CONFIG2_SL_4			(0x00000010)
#define MIPS_CP0_CONFIG2_SL_8			(0x00000020)
#define MIPS_CP0_CONFIG2_SL_16			(0x00000030)
#define MIPS_CP0_CONFIG2_SL_32			(0x00000040)
#define MIPS_CP0_CONFIG2_SL_64			(0x00000050)
#define MIPS_CP0_CONFIG2_SL_128			(0x00000060)
#define MIPS_CP0_CONFIG2_SL_256			(0x00000070)
/* Secondary cache associativity */
#define MIPS_CP0_CONFIG2_SA			(0x0000000F)
#define MIPS_CP0_CONFIG2_SA_DM			(0x00000000)
#define MIPS_CP0_CONFIG2_SA_2			(0x00000001)
#define MIPS_CP0_CONFIG2_SA_3			(0x00000002)
#define MIPS_CP0_CONFIG2_SA_4			(0x00000003)
#define MIPS_CP0_CONFIG2_SA_5			(0x00000004)
#define MIPS_CP0_CONFIG2_SA_6			(0x00000005)
#define MIPS_CP0_CONFIG2_SA_7			(0x00000006)
#define MIPS_CP0_CONFIG2_SA_8			(0x00000007)

/* Config3 Register */
#define MIPS_CP0_CONFIG3			$16, 3

/* Config4 register present */
#define MIPS_CP0_CONFIG3_M			(0x80000000)
/* User Local register implemented */
#define MIPS_CP0_CONFIG3_ULRI			(0x00002000)
/* DSP ASE implemented */
#define MIPS_CP0_CONFIG3_DSPP			(0x00000400)
/* External interrupt control implemented */
#define MIPS_CP0_CONFIG3_VEIC			(0x00000040)
/* Vectored interrupts implemented */
#define MIPS_CP0_CONFIG3_VINT			(0x00000020)
/* Small (1kb) page support */
#define MIPS_CP0_CONFIG3_SP			(0x00000010)
/* MIPS multi-threading ASE */
#define MIPS_CP0_CONFIG3_MT			(0x00000004)
/* SmartMIPS ASE */
#define MIPS_CP0_CONFIG3_SM			(0x00000002)
/* Trace Logic implemented */
#define MIPS_CP0_CONFIG3_TL			(0x00000001)

/* Config4 Register */
#define MIPS_CP0_CONFIG4			$16, 4

/* Config5 present */
#define MIPS_CP0_CONFIG4_M			(0x80000000)
/* TLB invalidate instruction support */
#define MIPS_CP0_CONFIG4_IE			(0x60000000)
#define MIPS_CP0_CONFIG4_IE_NONE		(0x00000000)
#define MIPS_CP0_CONFIG4_IE_SINGLE_ENTRY	(0x40000000)
#define MIPS_CP0_CONFIG4_IE_ALL_ENTRIES		(0x60000000)
/* EntryHI(ASID) extended to 10 bits */
#define MIPS_CP0_CONFIG4_AE			(0x10000000)
/* VTLB size extension */
#define MIPS_CP0_CONFIG4_VTLB_SIZEEXT		(0x0F000000)
/* KScratch(n) register exists */
#define MIPS_CP0_CONFIG4_KSCREXIST(n)		(0x00010000 << (n))
/* MMU extension definition */
#define MIPS_CP0_CONFIG4_MMU_EXT_DEF		(0x0000C000)

/* Config7 Register */
#define MIPS_CP0_CONFIG7			$16, 7

/* Wait IE Ignore */
#define MIPS_CP0_CONFIG7_WII			(0x80000000)
/* Hardware Cache Initialization */
#define MIPS_CP0_CONFIG7_HCI			(0x00040000)
/* Floating Point Ratio */
#define MIPS_CP0_CONFIG7_FPR			(0x00020000)
/* Alias removed */
#define MIPS_CP0_CONFIG7_AR			(0x00010000)
/* Instruction alias removed */
#define MIPS_CP0_CONFIG7_IAR			(0x00000400)
/* Instruction virtual aliasing fix disable */
#define MIPS_CP0_CONFIG7_IVA			(0x00000200)
/* Externalize sync */
#define MIPS_CP0_CONFIG7_ES			(0x00000100)
/* Out-of-order data return */
#define MIPS_CP0_CONFIG7_CPOOO			(0x00000040)
/* Non-blocking LSU */
#define MIPS_CP0_CONFIG7_NBLSU			(0x00000020)
/* Uncached loads blocking */
#define MIPS_CP0_CONFIG7_ULB			(0x00000010)
/* Branch prediction */
#define MIPS_CP0_CONFIG7_BP			(0x00000008)
/* Return prediction stack */
#define MIPS_CP0_CONFIG7_RPS			(0x00000004)
/* Branch history table */
#define MIPS_CP0_CONFIG7_BHT			(0x00000002)
/* Scheduled loads */
#define MIPS_CP0_CONFIG7_SL			(0x00000001)

/* WatchLo Register */
#define MIPS_CP0_WATCHLO(i)			$18, (i)

/* Virtual address to match */
#define MIPS_CP0_WATCHLO_VADDR			(0xFFFFFFF8)
/* Enabled for instruction fetches */
#define MIPS_CP0_WATCHLO_I			(0x00000004)
/* Enabled for loads */
#define MIPS_CP0_WATCHLO_R			(0x00000002)
/* Enabled for stores */
#define MIPS_CP0_WATCHLO_W			(0x00000001)

/* WatchHi Register */
#define MIPS_CP0_WATCHHI(i)			$19, (i)

/* Presence of additional Watch registers */
#define MIPS_CP0_WATCHHI_M			(0x80000000)
/* Match any address or ASID */
#define MIPS_CP0_WATCHHI_G			(0x40000000)
/* ASID value to match */
#define MIPS_CP0_WATCHHI_ASID			(0x00FF0000)
/* Bit mask for WatchLo register */
#define MIPS_CP0_WATCHHI_MASK			(0x00000FF8)
/* Instruction fetch condition match */
#define MIPS_CP0_WATCHHI_I			(0x00000004)
/* Load condition match */
#define MIPS_CP0_WATCHHI_R			(0x00000002)
/* Store condition match */
#define MIPS_CP0_WATCHHI_W			(0x00000001)

/* Debug Register */
#define MIPS_CP0_DEBUG				$23, 0

/* Branch delay slot */
#define MIPS_CP0_DEBUG_DBD			(0x80000000)
/* In debug mode */
#define MIPS_CP0_DEBUG_DM			(0x40000000)
/* Dseg segment is present */
#define MIPS_CP0_DEBUG_NODCR			(0x20000000)
/* Access of load/store between dseg and main memory */
#define MIPS_CP0_DEBUG_LSNM			(0x10000000)
/* Low power when exception occurred */
#define MIPS_CP0_DEBUG_DOZE			(0x08000000)
/* System clock stopped when exception occurred */
#define MIPS_CP0_DEBUG_HALT			(0x04000000)
/* Count register behavior */
#define MIPS_CP0_DEBUG_COUNTDM			(0x02000000)
/* Imprecise instruction fetch bus error exception */
#define MIPS_CP0_DEBUG_IBUSEP			(0x01000000)
/* Imprecise machine check exception */
#define MIPS_CP0_DEBUG_MCHECKP			(0x00800000)
/* Imprecise cache error */
#define MIPS_CP0_DEBUG_CACHEEP			(0x00400000)
/* Data access bus error exception */
#define MIPS_CP0_DEBUG_DBUSEP			(0x00200000)
/* Imprecise error exception inhibit */
#define MIPS_CP0_DEBUG_IEXI			(0x00100000)
/* Imprecise debug data break store exception */
#define MIPS_CP0_DEBUG_DDBSIMPR			(0x00080000)
/* Imprecise debug data break load exception */
#define MIPS_CP0_DEBUG_DDBLIMPR			(0x00040000)
/* EJTAG version */
#define MIPS_CP0_DEBUG_EJTAGVER			(0x00038000)
/* Cause of latest exception */
#define MIPS_CP0_DEBUG_DEXCCODE			(0x00007C00)
/* Single-step feature available */
#define MIPS_CP0_DEBUG_NOSTT			(0x00000200)
/* Debug single step execution enabled */
#define MIPS_CP0_DEBUG_SST			(0x00000100)
/* Debug interrupt exception occurred */
#define MIPS_CP0_DEBUG_DINT			(0x00000020)
/* Debug instruction break exception occurred */
#define MIPS_CP0_DEBUG_DIB			(0x00000010)
/* Debug data store break exception occurred */
#define MIPS_CP0_DEBUG_DDBS			(0x00000008)
/* Debug data load break exception occurred */
#define MIPS_CP0_DEBUG_DDBL			(0x00000004)
/* Debug software breakpoint exception occurred */
#define MIPS_CP0_DEBUG_DBP			(0x00000002)
/* Debug single-step exception occurred */
#define MIPS_CP0_DEBUG_DSS			(0x00000001)

/* Trace Control Register */
#define MIPS_CP0_TRACECONTROL			$23, 1

/* Trace select */
#define MIPS_CP0_TRACECONTROL_TS		(0x80000000)
/* Type of user-triggered trace record */
#define MIPS_CP0_TRACECONTROL_UT		(0x40000000)
/* Trace all branch */
#define MIPS_CP0_TRACECONTROL_TB		(0x08000000)
/* Inhibit overflow */
#define MIPS_CP0_TRACECONTROL_IO		(0x04000000)
/* Enable tracing in Debug Mode */
#define MIPS_CP0_TRACECONTROL_D			(0x02000000)
/* Enable tracing in Exception Mode */
#define MIPS_CP0_TRACECONTROL_E			(0x01000000)
/* Enable tracing in Kernel Mode */
#define MIPS_CP0_TRACECONTROL_K			(0x00800000)
/* Enable tracing in Supervisor Mode */
#define MIPS_CP0_TRACECONTROL_S			(0x00400000)
/* Enable tracing in User Mode */
#define MIPS_CP0_TRACECONTROL_U			(0x00200000)
/* ASID comparison mask */
#define MIPS_CP0_TRACECONTROL_ASID_M		(0x001FE000)
/* ASID to match */
#define MIPS_CP0_TRACECONTROL_ASID		(0x00001FE0)
/* Tracing enabled for all processes */
#define MIPS_CP0_TRACECONTROL_G			(0x00000010)
/* Trace function call and return instructions with full PC values */
#define MIPS_CP0_TRACECONTROL_TFCR		(0x00000008)
/* Trace data cache load and store misses with full PC values */
#define MIPS_CP0_TRACECONTROL_TLSM		(0x00000004)
/* Trace instruction miss with full PC values */
#define MIPS_CP0_TRACECONTROL_TIM		(0x00000002)
/* Master trace enable switch */
#define MIPS_CP0_TRACECONTROL_ON		(0x00000001)

/* Trace Control2 Register */
#define MIPS_CP0_TRACECONTROL2			$23, 2

/* Information to be traced when tracing is on */
#define MIPS_CP0_TRACECONTROL2_MODE		(0x00000F80)
#define MIPS_CP0_TRACECONTROL2_MODE_SD		(0x00000800)
#define MIPS_CP0_TRACECONTROL2_MODE_LD		(0x00000400)
#define MIPS_CP0_TRACECONTROL2_MODE_SA		(0x00000200)
#define MIPS_CP0_TRACECONTROL2_MODE_LA		(0x00000100)
#define MIPS_CP0_TRACECONTROL2_MODE_PC		(0x00000080)
/* Valid modes */
#define MIPS_CP0_TRACECONTROL2_VM		(0x00000060)
#define MIPS_CP0_TRACECONTROL2_VM_PC		(0x00000000)
#define MIPS_CP0_TRACECONTROL2_VM_PCA		(0x00000020)
#define MIPS_CP0_TRACECONTROL2_VM_PCAD		(0x00000040)
/* Trace buffers implemented by TCB */
#define MIPS_CP0_TRACECONTROL2_TBI		(0x00000010)
/* Trace buffer currently being written */
#define MIPS_CP0_TRACECONTROL2_TBU		(0x00000008)
/* Internal synchronization counter reset period */
#define MIPS_CP0_TRACECONTROL2_SYP		(0x00000007)
#define MIPS_CP0_TRACECONTORL2_SYP_2_5		(0x00000000)
#define MIPS_CP0_TRACECONTORL2_SYP_2_6		(0x00000001)
#define MIPS_CP0_TRACECONTORL2_SYP_2_7		(0x00000002)
#define MIPS_CP0_TRACECONTORL2_SYP_2_8		(0x00000003)
#define MIPS_CP0_TRACECONTORL2_SYP_2_9		(0x00000004)
#define MIPS_CP0_TRACECONTORL2_SYP_2_10		(0x00000005)
#define MIPS_CP0_TRACECONTORL2_SYP_2_11		(0x00000006)
#define MIPS_CP0_TRACECONTORL2_SYP_2_12		(0x00000007)

/* User Trace Data Register */
#define MIPS_CP0_USERTRACEDATA			$23, 3

/* TraceIBPC */
#define MIPS_CP0_TRACEIBPC			$23, 4

/* Trigger signals from instruction breakpoints */
#define MIPS_CP0_TRACEIBPC_IE			(0x10000000)
/* Tracing mode */
#define MIPS_CP0_TRACEIBPC_IPBC3		(0x00000E00)
#define MIPS_CP0_TRACEIBPC_IPBC2		(0x000001C0)
#define MIPS_CP0_TRACEIBPC_IBPC1		(0x00000038)
#define MIPS_CP0_TRACEIBPC_IBPC0		(0x00000007)
#define MIPS_CP0_TRACEIBPC_IBPC_STOP(i)		(0x0 << ((i) * 3))
#define MIPS_CP0_TRACEIBPC_IBPC_START(i)	(0x1 << ((i) * 3))

/* TraceDBPC */
#define MIPS_CP0_TRACEDBPC			$23, 5

/* Trigger signals from data breakpoints */
#define MIPS_CP0_TRACEDBPC_DE			(0x10000000)
/* Tracing mode */
#define MIPS_CP0_TRACEDBPC_DPBC1		(0x00000038)
#define MIPS_CP0_TRACEDBPC_DBBC0		(0x00000007)
#define MIPS_CP0_TRACEIBPC_DBPC_STOP(i)		(0x0 << ((i) * 3))
#define MIPS_CP0_TRACEIBPC_DBPC_START(i)	(0x1 << ((i) * 3))

/* Debug Exception Program Counter Register */
#define MIPS_CP0_DEPC				$24, 0

/* Performance Counter Control Register */
#define MIPS_CP0_PCCTL(i)			$25, (2 * (i))

/* Additional pair of control/counter registers */
#define MIPS_CP0_PCCTL_M			(0x80000000)
/* Counter event for this counter */
#define MIPS_CP0_PCCTL_EVENT			(0x00000FE0)
/* Counter Interrupt Enable */
#define MIPS_CP0_PCCTL_IE			(0x00000010)
/* Count in User Mode */
#define MIPS_CP0_PCCTL_U			(0x00000008)
/* Count in Supervisor Mode */
#define MIPS_CP0_PCCTL_S			(0x00000004)
/* Count in Kernel Mode */
#define MIPS_CP0_PCCTL_K			(0x00000002)
/* Count when EXL */
#define MIPS_CP0_PCCTL_EXL			(0x00000001)

/* Performance Counter Count Register */
#define MIPS_CP0_PCCNT(i)			$25, (2 * (i) + 1)

/* ErrCtl Register */
#define MIPS_CP0_ERRCTL				$26, 0

/* Parity Enable */
#define MIPS_CP0_ERRCTL_PE			(0x80000000)
/* Parity Overwrite */
#define MIPS_CP0_ERRCTL_PO			(0x40000000)
/* Way Selection Test */
#define MIPS_CP0_ERRCTL_WST			(0x20000000)
/* ScratchPadRAM Test */
#define MIPS_CP0_ERRCTL_SPR			(0x10000000)
/* Precode override */
#define MIPS_CP0_ERRCTL_PCO			(0x08000000)
/* InterThread Communication */
#define MIPS_CP0_ERRCTL_ITC			(0x04000000)
/* Most recent Data Bus Error involved load instruction */
#define MIPS_CP0_ERRCTL_LBE			(0x02000000)
/* Most recent Data Bus Error was due to write allocate, store data lost */
#define MIPS_CP0_ERRCTL_WABE			(0x01000000)
/* L2 ECC Enable */
#define MIPS_CP0_ERRCTL_L2P			(0x00800000)
/* Second cache error detected before first error processed */
#define MIPS_CP0_ERRCTL_SE			(0x00100000)
/* First cache error */
#define MIPS_CP0_ERRCTL_FE			(0x00080000)
/* Instruction precode bits read from or written to instruction cache data RAM */
#define MIPS_CP0_ERRCTL_PCI			(0x0007E000)
/* Parity bit read from or written to instruction cache data RAM */
#define MIPS_CP0_ERRCTL_PI			(0x00001FF0)
/* Parity bits read from or written to data cache data RAM */
#define MIPS_CP0_ERRCTL_PD			(0x0000000F)

/* CacheErr Register */
#define MIPS_CP0_CACHEERR			$27, 0

/* Error Reference */
#define MIPS_CP0_CACHEERR_ER			(0x80000000)
/* Cache level */
#define MIPS_CP0_CACHEERR_EC			(0x40000000)
/* Error Data */
#define MIPS_CP0_CACHEERR_ED			(0x20000000)
/* Error Tag */
#define MIPS_CP0_CACHEERR_ET			(0x10000000)
/* Error source */
#define MIPS_CP0_CACHEERR_ES			(0x08000000)
/* Error external */
#define MIPS_CP0_CACHEERR_EE			(0x04000000)
/* Error Both */
#define MIPS_CP0_CACHEERR_EB			(0x02000000)
/* Error Fatal */
#define MIPS_CP0_CACHEERR_EF			(0x01000000)
/* Scratchpad RAM parity error */
#define MIPS_CP0_CACHEERR_SP			(0x00800000)
/* Error Way */
#define MIPS_CP0_CACHEERR_EW			(0x00400000)
/* Way */
#define MIPS_CP0_CACHEERR_WAY			(0x00300000)
/* Index */
#define MIPS_CP0_CACHEERR_INDEX			(0x000FFFFF)

/* CacheErr Register (Secondary Cache) */
#define MIPS_CP0_CACHEERR_S			$27, 0

/* Cache level */
#define MIPS_CP0_CACHEERR_S_EC			(0x40000000)
/* Error Data */
#define MIPS_CP0_CACHEERR_S_ED			(0x20000000)
/* Error Tag */
#define MIPS_CP0_CACHEERR_S_ET			(0x10000000)
/* Error Multi */
#define MIPS_CP0_CACHEERR_S_EM			(0x02000000)
/* Error Fatal */
#define MIPS_CP0_CACHEERR_S_EF			(0x01000000)
/* Error Way */
#define MIPS_CP0_CACHEERR_S_EW			(0x00400000)
/* Way */
#define MIPS_CP0_CACHEERR_S_WAY			(0x00380000)
/* Index */
#define MIPS_CP0_CACHEERR_S_INDEX		(0x0007FFFF)

/* ITagLo Register */
#define MIPS_CP0_ITAGLO				$28, 0

/* PTagLo */
#define MIPS_CP0_ITAGLO_PTAGLO			(0xFFFFF800)
/* Cache line valid */
#define MIPS_CP0_ITAGLO_V			(0x00000080)
/* Lock bit for cache tag */
#define MIPS_CP0_ITAGLO_L			(0x00000020)
/* Parity bit for cache tag */
#define MIPS_CP0_ITAGLO_P			(0x00000001)
/* LRU bits */
#define MIPS_CP0_ITAGLO_WSLRU			(0x0000FC00)
/* BasePA */
#define MIPS_CP0_ITAGLO_BASEPA			(0xFFFFF000)
/* Scratchpad enabled */
#define MIPS_CP0_ITAGLO_E			(0x00000080)
/* Size of scratchpad array */
#define MIPS_CP0_ITAGLO_SIZE			(0x000FF000)

/* DTagLo Register */
#define MIPS_CP0_DTAGLO				$28, 2

/* PTagLo */
#define MIPS_CP0_DTAGLO_PTAGLO			(0xFFFFF800)
/* Cache line valid */
#define MIPS_CP0_DTAGLO_V			(0x00000080)
/* Cache line dirty */
#define MIPS_CP0_DTAGLO_D			(0x00000040)
/* Lock bit for cache tag */
#define MIPS_CP0_DTAGLO_L			(0x00000020)
/* Parity bit for cache tag */
#define MIPS_CP0_DTAGLO_P			(0x00000001)
/* Dirty Parity */
#define MIPS_CP0_DTAGLO_WSDP			(0x00F00000)
/* Dirty bits */
#define MIPS_CP0_DTAGLO_WSD			(0x000F0000)
/* LRU bits */
#define MIPS_CP0_DTAGLO_WSLRU			(0x0000FC00)
/* BasePA */
#define MIPS_CP0_DTAGLO_BASEPA			(0xFFFFF000)
/* Scratchpad enabled */
#define MIPS_CP0_DTAGLO_E			(0x00000080)
/* Size of scratchpad array */
#define MIPS_CP0_DTAGLO_SIZE			(0x000FF000)

/* L23TagLo Register */
#define MIPS_CP0_L23TAGLO			$28, 4

/* IDataLo Register */
#define MIPS_CP0_IDATALO			$28, 1

/* DDataLo Register */
#define MIPS_CP0_DDATALO			$28, 3

/* L23DataLo Register */
#define MIPS_CP0_L23DATALO			$28, 5

/* IDataHi Register */
#define MIPS_CP0_IDATAHI			$29, 1

/* L23DataHi Register */
#define MIPS_CP0_L23DATAHI			$29, 5

/* Error EPC */
#define MIPS_CP0_ERROR_EPC			$30, 0

/* DeSave Register */
#define MIPS_CP0_DESAVE				$31, 0

/* KScratch(n) Registers */
#define MIPS_CP0_KSCRATCH(n)			$31, (n)

#endif /* OUROBOROS_ARCH_MIPS_CP0_H */
