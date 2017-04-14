#ifndef OUROBOROS_FDT_H
#define OUROBOROS_FDT_H

#include <ouroboros/common.h>
#include <ouroboros/stdint.h>

PACKED_STRUCT_BEGIN(ou_fdt_header) {
	ou_uint32_t magic;
	ou_uint32_t totalsize;
	ou_uint32_t off_dt_struct;
	ou_uint32_t off_dt_strings;
	ou_uint32_t off_mem_rsvmap;
	ou_uint32_t version;
	ou_uint32_t last_comp_verison;
	ou_uint32_t boot_cpuid_phys;
	ou_uint32_t size_dt_strings;
	ou_uint32_t size_dt_structs;
} PACKED_STRUCT_END;

int ou_fdt_check_header(const struct ou_fdt_header *header);

#endif /* OUROBOROS_FDT_H */
