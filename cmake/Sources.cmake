#------------------------------------------------------------------------------
# NFX_APP_VISION
#
# Copyright © 2025 nfx Marine <ronan.fesselier@nfxMarine.com>
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Sources
#------------------------------------------------------------------------------

# Core application files
set(APP_CORE_FILES
	"main.cpp"
	"App/App.h"
	"App/App.cpp"
)

# UI component files
set(APP_UI_FILES
	# Main UI components
	"ui/MainWidget.h"
	"ui/MainWidget.cpp"
	
	# Navigation components
	"ui/MenuBar.h"
	"ui/MenuBar.cpp"
	"ui/StatusBar.h"
	"ui/StatusBar.cpp"
	
	# Camera-related UI components
	"ui/CameraController.h"
	"ui/CameraController.cpp"
	"ui/CameraViewport.h"
	"ui/CameraViewport.cpp"
)

# Combine all source files
set(sources_files
	${APP_CORE_FILES}
	${APP_UI_FILES}
)

# Create the executable target
add_executable(${PROJECT_NAME}
	${RC}
	${sources_files}
)

# Configure the target
target_precompile_headers(${PROJECT_NAME} REUSE_FROM nfxCore)
target_include_directories(${PROJECT_NAME} PRIVATE ".")
target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${CXX_COMPILE_FLAGS}>)

# Platform-specific properties
if(UNIX)
	set_target_properties(${PROJECT_NAME} PROPERTIES
		VERSION     ${PROJECT_VERSION}
		SOVERSION   ${PROJECT_VERSION_MAJOR}
	)
endif()
