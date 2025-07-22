# Ad-hoc CMake module exposing all libogg and libvorbis sources & headers from in-tree libogg and libvorbis
# This is the only bundled library where its .vcxproj exists in its own directory, and we will match

project(pxtone-vorbis LANGUAGES C)

function(external_sources dst prefix)
   set(lv "")
   foreach(f ${ARGN})
      list(APPEND lv "${prefix}/${f}")
   endforeach(f)
   set(${dst} "${lv}" PARENT_SCOPE)
endfunction()

set(OGG_SOURCE_DIR "${CMAKE_SOURCE_DIR}/libogg")
set(VORBIS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/libvorbis")

external_sources(OGG_SOURCES "${OGG_SOURCE_DIR}/src"
	bitwise.c
	framing.c
)

external_sources(VORBIS_SOURCES "${VORBIS_SOURCE_DIR}/lib"
	analysis.c
	bitrate.c
	block.c
	codebook.c
	envelope.c
	floor0.c
	floor1.c
	info.c
	lookup.c
	lpc.c
	lsp.c
	mapping0.c
	mdct.c
	psy.c
	registry.c
	res0.c
	sharedbook.c
	smallft.c
	synthesis.c
	vorbisenc.c
	vorbisfile.c
	window.c
)

list(APPEND LIBRARY_SOURCES ${OGG_SOURCES})
list(APPEND LIBRARY_SOURCES ${VORBIS_SOURCES})

list(APPEND LIBRARY_DIRS "${VORBIS_SOURCE_DIR}/lib")
list(APPEND LIBRARY_DIRS "${VORBIS_SOURCE_DIR}/include")

add_bundled_library(${PROJECT_NAME} SHARED "${LIBRARY_SOURCES}" "${LIBRARY_DIRS}")

# Export
# ---------------

add_library(pxtone::vorbis ALIAS ${PROJECT_NAME})
