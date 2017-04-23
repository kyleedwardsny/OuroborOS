include(OuCommon)

add_sources(ldinitrd.elf
	head.S
)

set_link_script(ldinitrd.elf ldinitrd.ld)
