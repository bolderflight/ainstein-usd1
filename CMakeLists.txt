# v3.14 required for FetchContent_MakeAvailable
cmake_minimum_required(VERSION 3.14)
if (DEFINED MCU)
  include(FetchContent)
	FetchContent_Declare(
		mcu_support
		GIT_REPOSITORY https://github.com/bolderflight/mcu-support.git
		GIT_TAG v1.0.0
	)
	FetchContent_MakeAvailable(mcu_support)
  # Setting up the toolchain
  set(CMAKE_TOOLCHAIN_FILE "${mcu_support_SOURCE_DIR}/cmake/cortex.cmake")
	# Project information
	project(AinsteinUsd1
		VERSION 1.0.0
		DESCRIPTION "Ainstein US-D1 sensor driver"
		LANGUAGES CXX
	)
	# Grab the processor and set up definitions and compile options
	include(${mcu_support_SOURCE_DIR}/cmake/config_mcu.cmake)
	configMcu(${MCU} ${mcu_support_SOURCE_DIR})
	# Fetch core
	FetchContent_Declare(
		core
		GIT_REPOSITORY https://github.com/bolderflight/core.git
		GIT_TAG v3.0.2
	)
	FetchContent_MakeAvailable(core)
	# Add the library target
	add_library(ainstein_usd1
		src/ainstein_usd1.h
		src/ainstein_usd1.cpp
	)
	# Link libraries
	target_link_libraries(ainstein_usd1
		PUBLIC
			core
	)
	# Setup include directories 
	target_include_directories(ainstein_usd1 PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
		$<INSTALL_INTERFACE:include>
	)
	# Example and test if this project is built separately
	if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
		# Add the spi example target
		add_executable(usd1_example examples/cmake/usd1_example.cc)
		# Add the includes
		target_include_directories(usd1_example PUBLIC 
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
			$<INSTALL_INTERFACE:include>
		)
		# Link libraries to the example target
		target_link_libraries(usd1_example
			PRIVATE 
				ainstein_usd1
		)
		# Add hex and upload targets
		include(${mcu_support_SOURCE_DIR}/cmake/flash_mcu.cmake)
		FlashMcu(usd1_example ${MCU} ${mcu_support_SOURCE_DIR})
	endif()
endif()
