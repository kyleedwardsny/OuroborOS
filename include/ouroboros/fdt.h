#ifndef OUROBOROS_FDT_H
#define OUROBOROS_FDT_H

#include <ouroboros/common.h>

#include <stdint.h>

PACKED_STRUCT_BEGIN(ou_fdt_header) {
	uint32_t magic;
	uint32_t totalsize;
	uint32_t off_dt_struct;
	uint32_t off_dt_strings;
	uint32_t off_mem_rsvmap;
	uint32_t version;
	uint32_t last_comp_verison;
	uint32_t boot_cpuid_phys;
	uint32_t size_dt_strings;
	uint32_t size_dt_structs;
} PACKED_STRUCT_END;

int ou_fdt_check_header(const struct ou_fdt_header *header);

#endif /* OUROBOROS_FDT_H */
