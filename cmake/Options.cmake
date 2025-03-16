#------------------------------------------------------------------------------
# NFX_APP_VISION
#
# Copyright © 2025 nfx Marine <ronan.fesselier@nfxMarine.com>
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Build Options
#------------------------------------------------------------------------------

# Option to hide console window on Windows
option(NFX_HIDE_CONSOLE "Hide console window in release builds" FALSE)

#------------------------------------------------------------------------------
# Resource Files
#------------------------------------------------------------------------------

# Configure version resource for Windows
set(RC "")
if(WIN32)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
		${CMAKE_CURRENT_BINARY_DIR}/version.rc
		@ONLY
	)
	set(RC ${CMAKE_CURRENT_BINARY_DIR}/version.rc)
endif()

#------------------------------------------------------------------------------
# Resource Copying
#------------------------------------------------------------------------------
add_custom_target(
	"copy_resources_folder_${PROJECT_NAME}" ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/resources/" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/"
)
