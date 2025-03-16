#------------------------------------------------------------------------------
# NFX_APP_VISION
#
# Copyright © 2025 nfx Marine <ronan.fesselier@nfxMarine.com>
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Platform and Compiler Detection
#------------------------------------------------------------------------------
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(ARCHITECTURE "x64")
else()
	set(ARCHITECTURE "x86")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT MATCHES "MSVC")
		set(COMPILER_VARIANT "clang-cl")
	else()
		set(COMPILER_VARIANT "clang")
	endif()
	set(COMPILER_FULL_NAME "${COMPILER_VARIANT}_${CMAKE_CXX_COMPILER_VERSION}")
else()
	set(COMPILER_FULL_NAME "${CMAKE_CXX_COMPILER_ID}_${CMAKE_CXX_COMPILER_VERSION}")
endif()

if(NOT CMAKE_CXX_COMPILER)
	message(WARNING "No C++ compiler path was found!")
endif()

if(NOT CMAKE_C_COMPILER)
	message(WARNING "No C compiler path was found!")
endif()

#------------------------------------------------------------------------------
# Compiler flags
#------------------------------------------------------------------------------
if( WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
	set( NFX_CXX_COMPILE_FLAGS
# ------------------------------------ Compiler flags ----------------------------------------------- #
		/std:c++20
		/MP
		/EHsc
#		/EHa
		/utf-8
		/arch:AVX
		/arch:AVX2
		/W4						# warning level: /W0, /W1, /W2, /W3, /W4
#		/Wall
		/WX-					# treat linker warnings as errors
		/permissive-
#		/fp:except
#		/fp:fast
#		/fp:strict
		/fp:precise
		/Zc:__cplusplus
		/Zc:inline
#		/Zc:preprocessor		# Preprocessor conformance with c++>=11
#		/Qspectre				# Spectre/Meltdown mitigations. Need specific msvc installation.

# ------------------------------------ External libraries ------------------------------------------- #
		/external:anglebrackets # External libraries recognized by angle brackets <>
		/external:W0			# Disable warnings for external libraries

# ------------------------------------ Code analysis (slow compilation) ----------------------------- #
		/analyze:WX- /analyze:external- /analyze

# ------------------------------------ Warning suppressions ----------------------------------------- #
#		/wd4061					# switch not handled
#		/wd4062					# switch not handled
#		/wd4244					# possible loss of data
		/wd4251					# 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
#		/wd4464					# relative include path contains '..'
		/wd4371					# better packing of class member than previous version of the compiler
#		/wd4505					# unreferenced function
#		/wd4514					# unreferenced inline function has been removed
		/wd4599					# precompiled headers
		/wd4605					# precompiled headers
#		/wd4625					# copy constructor was implicitly defined as deleted
#		/wd4626					# assignement operator was implicitly defined as deleted
#		/wd4623					# default constructor was implicitly defined as deleted
		/wd4651					# Definition set for pch but not for current compile
		/wd4710					# function not inlined
		/wd4711					# function inlined
#		/wd4715					# return value
#		/wd4723					# divide operation evaluated to zero
		/wd4820					# padding
#		/wd4866					# compiler may not enforce left-to-right evaluation order for call
		/wd4868					# left-to-right evaluation order in braced initializer list
#		/wd5027					# move assignement operator was implicitly defined as deleted
		/wd5045					# Qspectre
#		/wd5219					# implicit conversion
#		/wd5267					# definition of implicit copy constructor/assignment operator is deprecated because it has a user-provided assignment operator/copy constructor
	)

	set( CMAKE_SHARED_LINKER_FLAGS
		/manifestuac:no
	)
endif()

if( WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_CXX_COMPILER_FRONTEND_VARIANT MATCHES "MSVC" )
	set( NFX_CXX_COMPILE_FLAGS
		/std:c++20
		/EHsc
		/utf-8
		/arch:AVX
		/arch:AVX2
		/W4
		/WX-
		/permissive-
		/fp:precise
		/Zc:__cplusplus
		/Zc:inline
		/external:W0
		
		/wd4251
		/wd4371
		/wd4599
		/wd4605
		/wd4651
		/wd4710
		/wd4711
		/wd4820
		/wd4868
		/wd5045
	)
	
	set( CMAKE_SHARED_LINKER_FLAGS
		/manifestuac:no
	)
endif()


if( WIN32 AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR MINGW) )
	set( NFX_CXX_COMPILE_FLAGS
		-std=gnu++20
		-fPIC
		-g1
		-msse
		-msse2
		-msse3
		-msse4.1
		-pthread
		-DNDEBUG
		-O3
		-fdiagnostics-color=always
		-fdiagnostics-show-option
		-ffunction-sections
		-fomit-frame-pointer
		-fsigned-char
		-W
		-Wall
		-Wextra
		-Wpedantic
		-Wno-invalid-pch
		-Wno-unused-parameter
		-Wno-missing-declarations
	)
endif()

if( UNIX AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
	set( NFX_CXX_COMPILE_FLAGS
		-std=c++20
		-no-pie
		-fno-pie
		-fPIC
		-fdata-sections
		-g1
		-msse
		-msse2
		-msse3
		-msse4.1
		-pthread
		-DNDEBUG
		-O3
		-fdiagnostics-color=always
		-fdiagnostics-show-option
		-ffunction-sections
		-fomit-frame-pointer
		-fsigned-char
		-W
		-Waddress
		-Wall
		-Walloca
		-Wcast-align
		-Wcast-qual
		-Wconversion
#		-Wctor-dtor-privacy
		-Wdisabled-optimization
		-Wdouble-promotion
		-Werror
		-Wextra
		-Wformat
		-Wformat-security
		-Wformat=2
		-Wimplicit-fallthrough=3
		-Winit-self
		-Wmissing-declarations
		-Wmissing-field-initializers
#		-Wno-comment
#		-Wno-delete-non-virtual-dtor
#		-Wno-deprecated-copy
#		-Wno-dev
#		-Wno-long-long
#		-Wno-strict-overflow
#		-Wno-unused
#		-Wno-unused-parameter
#		-Wnon-virtual-dtor
#		-Wold-style-cast
		-Woverloaded-virtual
		-Wpedantic
		-Wpointer-arith
		-Wredundant-decls
		-Wreorder
		-Wreturn-type
		-Wsequence-point
		-Wshadow
		-Wsign-conversion
		-Wsuggest-override
		-Wswitch-default
		-Wswitch-enum
		-Wtautological-compare
		-Wtype-limits
		-Wundef
		-Wuninitialized
		-Wunknown-pragmas
		-Wunreachable-code
		-Wunused
		-Wunused-but-set-variable
		-Wunused-parameter
		-Wunused-result
		-Wunused-variable
		-Wno-invalid-pch
		-Wno-missing-declarations
	)	
endif()

if( UNIX AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
	set( NFX_CXX_COMPILE_FLAGS
		-std=c++20
		-fno-pie
		-fPIC
		-fdata-sections
		-g1
		-msse
		-msse2
		-msse3
		-msse4.1
		-pthread
		-DNDEBUG
		-O3
		-fdiagnostics-color=always
		-fdiagnostics-show-option
		-ffunction-sections
		-fomit-frame-pointer
		-fsigned-char
		-W
		-Waddress
		-Wall
		-Walloca
		-Wcast-align
		-Wcast-qual
		-Wconversion
#		-Wctor-dtor-privacy
		-Wdisabled-optimization
		-Wdouble-promotion
		-Werror
		-Wextra
		-Wformat
		-Wno-format-security
#		-Wformat-security
		-Wformat=2
#		-Wimplicit-fallthrough
		-Winit-self
		-Wmissing-declarations
		-Wmissing-field-initializers
#		-Wno-comment
#		-Wno-delete-non-virtual-dtor
#		-Wno-deprecated-copy
#		-Wno-dev
#		-Wno-long-long
#		-Wno-strict-overflow
		-Wno-unused
		-Wno-unused-parameter
		-Wno-invalid-pch
#		-Wnon-virtual-dtor
#		-Wold-style-cast
		-Woverloaded-virtual
		-Wpedantic
		-Wpointer-arith
		-Wredundant-decls
		-Wreorder
		-Wreturn-type
		-Wsequence-point
		-Wshadow
		-Wsign-conversion
		-Wsuggest-override
		-Wswitch-default
		-Wswitch-enum
		-Wtautological-compare
		-Wtype-limits
		-Wundef
		-Wuninitialized
		-Wunknown-pragmas
		-Wunreachable-code
#		-Wunused
#		-Wunused-but-set-variable
#		-Wunused-parameter
#		-Wunused-result
#		-Wunused-variable
		-Wno-unreachable-code

	)
endif()

if(NFX_CXX_COMPILE_FLAGS)
	# Convert the list to a space-separated string
	string(REPLACE ";" " " CXX_FLAGS_STR "${NFX_CXX_COMPILE_FLAGS}")
	
	# First unset the cache variable to ensure we start fresh
	unset(CMAKE_CXX_FLAGS CACHE)
	
	# Append our flags
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS_STR}" 
		CACHE STRING "C++ Compiler Flags" FORCE)
	
	# Handle configuration specific flags
	foreach(CONFIG_TYPE ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER ${CONFIG_TYPE} CONFIG_TYPE_UPPER)
		# Clear the cache for configuration specific flags
		unset(CMAKE_CXX_FLAGS_${CONFIG_TYPE_UPPER} CACHE)
		
		# Get default flags for this configuration
		get_property(DEFAULT_CONFIG_FLAGS 
			CACHE CMAKE_CXX_FLAGS_${CONFIG_TYPE_UPPER} 
			PROPERTY VALUE)
		
		# Set configuration specific flags
		set(CMAKE_CXX_FLAGS_${CONFIG_TYPE_UPPER} 
			"${DEFAULT_CONFIG_FLAGS} ${CXX_FLAGS_STR}"
			CACHE STRING "C++ Compiler Flags for ${CONFIG_TYPE}" FORCE)
	endforeach()
endif()



# Apply linker flags if any
if(CMAKE_SHARED_LINKER_FLAGS)
	string(REPLACE ";" " " SHARED_LINKER_FLAGS_STR "${CMAKE_SHARED_LINKER_FLAGS}")
	set(CMAKE_SHARED_LINKER_FLAGS "${SHARED_LINKER_FLAGS_STR}" 
		CACHE STRING "Shared Library Linker Flags" FORCE)
endif()

nfx_Print_Section("Platform and Compiler Detection")
nfx_Print_Item("Detected architecture    " ${ARCHITECTURE})
nfx_Print_Item("Detected compiler        " ${COMPILER_FULL_NAME})
nfx_Print_Item("CMAKE_C_COMPILER         " "${CMAKE_C_COMPILER}")
nfx_Print_Item("CMAKE_CXX_COMPILER       " "${CMAKE_CXX_COMPILER}")
nfx_Print_Item("NFX_CXX_COMPILE_FLAGS    " "${NFX_CXX_COMPILE_FLAGS}")
nfx_Print_Item("CMAKE_CXX_FLAGS          " "${CMAKE_CXX_FLAGS}")
nfx_Print_Item("CMAKE_SHARED_LINKER_FLAGS" "${CMAKE_SHARED_LINKER_FLAGS}")
