macro(get_source_path VAR FILENAME)
	if (IS_ABSOLUTE "${FILENAME}")
		set("${VAR}" "${FILENAME}")
	else()
		get_filename_component("${VAR}" "${FILENAME}" ABSOLUTE)
	endif()
endmacro()

macro(get_binary_path VAR FILENAME)
	if (IS_ABSOLUTE "${FILENAME}")
		set("${VAR}" "${FILENAME}")
	else()
		set("${VAR}" "${CMAKE_CURRENT_BINARY_DIR}/${FILENAME}")
	endif()
endmacro()

macro(add_sources TARGET)
	foreach (_source IN ITEMS ${ARGN})
		get_source_path(_source_abs "${_source}")
		set_property(GLOBAL APPEND PROPERTY "${TARGET}_SOURCES" "${_source_abs}")
	endforeach()
endmacro()

macro(get_sources VAR TARGET)
	get_property("${VAR}" GLOBAL PROPERTY "${TARGET}_SOURCES")
endmacro()

macro(set_link_script TARGET SCRIPT)
	get_source_path(_script_abs "${SCRIPT}")
	set_property(GLOBAL PROPERTY "${TARGET}_LINK_SCRIPT" "${_script_abs}")
endmacro()

macro(get_link_script VAR TARGET)
	get_property("${VAR}" GLOBAL PROPERTY "${TARGET}_LINK_SCRIPT")
endmacro()

macro(get_link_script_flags VAR TARGET)
	get_link_script(_link_script "${TARGET}")
	if ("${_link_script}" STREQUAL "")
		set("${VAR}" "")
	else()
		set("${VAR}" "-T \"${_link_script}\"")
	endif()
endmacro()

macro(finish_executable TARGET)
	get_sources(_sources "${TARGET}")
	get_link_script_flags(_ldflags "${TARGET}")
	get_link_script(_ldscript "${TARGET}")

	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${_ldflags}")
	add_executable("${TARGET}" ${_sources})
	set_property(TARGET "${TARGET}" APPEND PROPERTY LINK_DEPENDS ${_ldscript})
endmacro()

macro(finish_library TARGET)
	get_sources(_sources "${TARGET}")
	get_link_script_flags(_ldflags "${TARGET}")
	get_link_script(_ldscript "${TARGET}")

	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${_ldflags}")
	add_library("${TARGET}" ${_sources})
	set_property(TARGET "${TARGET}" APPEND PROPERTY LINK_DEPENDS ${_ldscript})
endmacro()

macro(add_itb TARGET SOURCE)
	get_source_path(_source "${SOURCE}")
	get_binary_path(_target "${TARGET}")
	add_custom_command(
		OUTPUT "${_target}"
		COMMAND "${MKIMAGE}"
			-f "${_source}"
			-D "-i ${CMAKE_BINARY_DIR} -O dtb"
			"${_target}"
		DEPENDS "${_source}"
	)
endmacro()

macro(add_dtb TARGET SOURCE)
	get_source_path(_source "${SOURCE}")
	get_binary_path(_target "${TARGET}")
	add_custom_command(
		OUTPUT "${_target}"
		COMMAND "${DTC}"
			-O dtb
			-o "${_target}"
			-i "${CMAKE_BINARY_DIR}"
			"${_source}"
		DEPENDS "${_source}"
	)
endmacro()
