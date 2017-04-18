include("config.cmake")
include("postconfig.cmake")

add_sources(kernel.elf
	config.c
	entry.S
	head.S
	hang.c
	mmu.c
	shadow.c
)

set_link_script(kernel.elf kernel.ld)

configure_file(config.ld.in config.ld)
configure_file(genconfig.h.in genconfig.h)
