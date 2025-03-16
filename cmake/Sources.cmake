#
#	NFX_APP_VISION
#
#	Source files
#
#	nfx Marine © 2024 <ronan.fesselier@nfxMarine.com>
#

set( sources_files
					"main.cpp"

					"App/App.h"
					"App/App.cpp"

					"ui/MainWidget.h"
					"ui/MainWidget.cpp"

					"ui/MenuBar.h"
					"ui/MenuBar.cpp"

					"ui/StatusBar.h"
					"ui/StatusBar.cpp"

					"ui/CameraController.h"
					"ui/CameraController.cpp"

					"ui/CameraViewport.h"
					"ui/CameraViewport.cpp"
)

add_executable( ${PROJECT_NAME}
							${RC}
							${sources_files}
)


target_precompile_headers( ${PROJECT_NAME} REUSE_FROM nfxCore )

target_include_directories( ${PROJECT_NAME} PRIVATE "." )

target_compile_options( ${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${CXX_COMPILE_FLAGS}> )


if( UNIX )
	set_target_properties( ${PROJECT_NAME} PROPERTIES
								VERSION		${PROJECT_VERSION}
								SOVERSION	${PROJECT_VERSION_MAJOR} )
endif()
