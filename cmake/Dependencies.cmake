#
#	NFX_APP_VISION
#
#	Dependencies
#
#	nfx Marine © 2024 <ronan.fesselier@nfxMarine.com>
#

add_dependencies(${PROJECT_NAME} "copy_resources_folder_${PROJECT_NAME}")

find_package( OpenCV CONFIG REQUIRED )
target_link_libraries( ${PROJECT_NAME} PRIVATE ${OpenCV_LIBS} )

target_link_libraries( ${PROJECT_NAME} PUBLIC
											nfxCore
											nfxApplication
											#nfxUtils
											#nfxImage
											nfxGraphicsCore
											nfxGraphicsGL
											nfxWindow
											nfxGUI
											#nfxVideoCaptureDevice
											nfxVideoCaptureDeviceInfo
											#nfxTensorRTYoloV8Engine
											#nfxCudaDevice
)
