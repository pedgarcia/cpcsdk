# In this directory we build the executable with wxWidgets gui
cmake_minimum_required(VERSION 2.8)
project(ReloadedGUI)

# wxWidgets
set(wxWidgets_CONFIGURATION 'wxmsw')
find_package(wxWidgets COMPONENTS aui adv core base REQUIRED)
include( "${wxWidgets_USE_FILE}" )

include_directories(..)

add_executable(reloaded WIN32 
	CapriceAboutImpl.cpp
	CapriceApp.cpp
	CapriceInputSettingsImpl.cpp
	CapriceRegistersDialogImpl.cpp
	CapriceUIWrapper.cpp
	CapriceWindowImpl.cpp
	MemoryImpl.cpp
	../aop/portAudioAudioPlugin.cpp
	WXEmulator.cpp
	../misc/Desass.cpp
)

add_dependencies(reloaded ReloadedCore)
target_link_libraries(reloaded ReloadedCore)

target_link_libraries(reloaded ${wxWidgets_LIBRARIES})

target_link_libraries(reloaded ${CMAKE_THREAD_LIB_INIT})

if (WIN32)
	target_link_libraries(reloaded portaudio_x86)
else (WIN32)
	target_link_libraries(reloaded portaudio)
endif (WIN32)
