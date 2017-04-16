set(OU_IKERNEL_LOAD_ADDR 0xA0010000 CACHE STRING "Sets the physical address where the inner kernel is loaded")
set(OU_IKERNEL_ENTRY_ADDR "${OU_IKERNEL_LOAD_ADDR}" CACHE STRING "Sets the physical address where the inner kernel is entered")
set(OU_IKERNEL_LINK_ADDR 0x80010000 CACHE STRING "Sets the physical address where the inner kernel is linked")
