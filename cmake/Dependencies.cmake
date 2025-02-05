#
#	NFX_APP_VISION
#
#	Dependencies
#
#	nfx Marine © 2024 <ronan.fesselier@nfxMarine.com>
#

add_dependencies( ${PROJECT_NAME} "copy_resources_folder_${PROJECT_NAME}" )

get_target_property(nfxLIBS_COMPILE_DEFINITIONS nfxCore INTERFACE_COMPILE_DEFINITIONS)
message(STATUS "nfxLibs definitions: ${nfxLIBS_COMPILE_DEFINITIONS}")

target_link_libraries( ${PROJECT_NAME} PUBLIC
											nfxApplication
											nfxGraphicsCore
											nfxGraphicsGL
											nfxGraphicsVk
											nfxWindow
											nfxGUI
											nfxVideoCapture
)
