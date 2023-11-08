cmake_minimum_required(VERSION 3.10.0)

project(MySqlGUI
  VERSION
    1.0
  DESCRIPTION
    "MySql a GUI workbench"
  LANGUAGES
    CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(Qt5Core REQUIRED)

set(SRC_FILES
		main.cpp
		MysqlLogin.cpp
		DataQueryWindow.cpp
		DialogSelectDB.cpp
		DialogUploadSQL.cpp
		InsertValue.cpp
		InsertLineForm.cpp
		)

set(HEADER_FILES
		MysqlLogin.h
		DataQueryWindow.h
		DialogSelectDB.h
		DialogUploadSQL.h
		InsertValue.h
		InsertLineForm.h
		)
		
set(UI_FILES
		MysqlLogin.ui
		DataQueryWindow.ui
		DialogSelectDB.ui
		DialogUploadSQL.ui
		InsertValue.ui
		InsertLineForm.ui
		)
		
set(QRC_FILES
		icons.qrc
		)


add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES} ${UI_FILES} ${QRC_FILES})


add_definitions(-DQT_NO_VERSION_TAGGING)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

qt5_use_modules(${PROJECT_NAME} Core Sql Test)

include_directories(.)


