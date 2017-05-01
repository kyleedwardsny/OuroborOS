include(OuCommon)

add_sources(ldinitrd.elf
	early_data.c
	head.S
)

set_link_script(ldinitrd.elf ldinitrd.ld)
