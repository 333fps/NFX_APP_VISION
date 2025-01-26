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

  find_package(imgui CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)

	  find_package(magic_enum CONFIG REQUIRED)
	target_link_libraries(${PROJECT_NAME} PRIVATE magic_enum::magic_enum)

		find_package(GLEW REQUIRED)
	target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)

target_link_libraries( ${PROJECT_NAME} PUBLIC
											nfxApplication
											nfxGraphicsCore
											nfxGraphicsGL
											nfxWindow2
											nfxGUI
											nfxVideoCapture
)
