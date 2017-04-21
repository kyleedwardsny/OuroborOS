include(OuCommon)

add_sources(ikernel.elf
	config.c
	context.c
	entry.S
	head.S
	hang.c
	main.c
	mmu.c
	shadow.c
)

set_link_script(ikernel.elf kernel.ld)

configure_file(config.ld.in config.ld)
