cmake_minimum_required(VERSION 3.22)
project(QtTemplate)

# Use C++-17 by default.
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the module path to include scripts
# CMake - Contains project local modules.
#
# CMake/Modules - Contains project independent modules.
#   GitUpdate.cmake invokes python ${QtTemplate_SOURCE_DIR}/gitupdate.py
#   to pull all submodules and update to head.
#   If this fails, it will attempt to invoke git directly to pull 
#   submodules. 
list(APPEND CMAKE_MODULE_PATH 
  ${QtTemplate_SOURCE_DIR}/CMake 
  ${QtTemplate_SOURCE_DIR}/CMake/Modules
)
include(Configure)
if (NOT Configure_SUCCEEDED)
   return()
endif()



if (QtTemplate_ExternalTarget)
    set(TargetFolders ${QtTemplate_TargetFolders})
    set(TargetName    ${QtTemplate_TargetName})
    set(TargetGroup   ${QtTemplate_TargetGroup})
else()
    add_subdirectory(CMake)
    add_subdirectory(Internal/Utils)
    include(${Utils_SOURCE_DIR}/CMake/Locals.cmake)
    add_subdirectory(Internal/Thread)
    add_subdirectory(Internal/View)

    set(TargetFolders TRUE)
    set(TargetName QtTemplate)
    set(TargetGroup )
    
   set(QtTemplate_DEP_INCLUDE  
        ${Utils_INCLUDE} 
        ${View_INCLUDE} 
        ${Thread_INCLUDE}
    )
    
   set(QtTemplate_DEP_LIBRARY  
        ${Utils_LIBRARY} 
        ${View_LIBRARY} 
        ${Thread_LIBRARY}
        Qt6::Widgets 
        Qt6::Core 
        Qt6::Gui 
    )

    set(QtTemplate_INCLUDE  
        ${QtTemplate_SOURCE_DIR}
        ${QtTemplate_DEP_INCLUDE}
    )

    set(QtTemplate_LIBRARY  
        ${TargetName}
        ${QtTemplate_DEP_LIBRARY}
    )
endif()

add_subdirectory(Source)

if (QtTemplate_BUILD_TEST)
    if (NOT QtTemplate_ExternalTarget)
        add_gtest_source(Extern/ThirdParty)
    endif()

    set(TargetGroup Units)
    add_subdirectory(Test)
endif()
