cmake_minimum_required(VERSION 2.6)



#Déclaration du projet

project(World_Of_Colonies)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

#---------------------------------------------------------------------------------------------


#Inclusion des bibliotheques irrlicht, Qt et cppconn

#irrlicht, cppconn
include_directories(

	${irrlicht_include_dir}

	${cppconn_include_dir}
)

link_directories(

	${irrlicht_lib_dir}

	${cppconn_lib_dir}
)


#Qt
file(

        GLOB_RECURSE

        MOC_HEADERS

        src/*.h

)

file(

        GLOB_RECURSE

        UIS

        src/*.ui

)


# Next lines needed for building all Qt projects : WTFFFFF je ne comprend ps Qt complique
set ( CMAKE_AUTOMOC ON )
set ( CMAKE_INCLUDE_CURRENT_DIR ON )
find_package( Qt4 REQUIRED QtCore QtGui)
include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )
include_directories( ${CMAKE_BINARY_DIR} )

# using Qt meta-system (precompiler) : WTFFFFF je ne comprend pas Qt complique
QT4_WRAP_UI( UI_HEADERS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${MOC_HEADERS} )


#----------------------------------------------------------------------------------------------------


#Configuration de l'executable

file(

        GLOB_RECURSE

        source_files

        src/*.cpp
)

add_executable(

        World_Of_Colonies

        ${source_files}

	${MOC_HEADERS}

	${UIS}

)


#---------------------------------------------------------------------------------------------------


#Configuration de l'édition de liens

target_link_libraries(

        World_Of_Colonies

        ${irrlicht_lib_name}

	${cppconn_lib_name}

	Qt4::QtCore

	Qt4::QtGui
)
