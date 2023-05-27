cmake_minimum_required(VERSION 3.22)
project(DirView)

# Use C++-17 by default.
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the module path to include scripts
# CMake - Contains project local modules.
#
# CMake/Modules - Contains project independent modules.
#   GitUpdate.cmake invokes python ${DirView_SOURCE_DIR}/gitupdate.py
#   to pull all submodules and update to head.
#   If this fails, it will attempt to invoke git directly to pull 
#   submodules. 
list(APPEND CMAKE_MODULE_PATH 
  ${DirView_SOURCE_DIR}/CMake 
  ${DirView_SOURCE_DIR}/CMake/Modules
)
include(Configure)
if (NOT Configure_SUCCEEDED)
   return()
endif()



if (DirView_ExternalTarget)
    set(TargetFolders ${DirView_TargetFolders})
    set(TargetName    ${DirView_TargetName})
    set(TargetGroup   ${DirView_TargetGroup})
else()
    add_subdirectory(CMake)
    add_subdirectory(Internal/Utils)
    include(${Utils_SOURCE_DIR}/CMake/Locals.cmake)
    add_subdirectory(Internal/Thread)
    set(View_BUILD_SAMPLES OFF)
    set(View_BUILD_TEST OFF)
    add_subdirectory(Internal/View)
    add_subdirectory(Internal/Math)

    set(TargetFolders TRUE)
    set(TargetName DirView)
    set(TargetGroup )
    
   set(DirView_DEP_INCLUDE  
        ${Utils_INCLUDE} 
        ${View_INCLUDE} 
        ${Thread_INCLUDE}
        ${Math_INCLUDE}
    )
    
   set(DirView_DEP_LIBRARY  
        ${Utils_LIBRARY} 
        ${View_LIBRARY} 
        ${Thread_LIBRARY}
        ${Math_LIBRARY}
        Qt6::Widgets 
        Qt6::Core 
        Qt6::Gui 
    )

    set(DirView_INCLUDE  
        ${DirView_SOURCE_DIR}
        ${DirView_DEP_INCLUDE}
    )

    set(DirView_LIBRARY  
        ${TargetName}
        ${DirView_DEP_LIBRARY}
    )
endif()

add_subdirectory(DirView)

if (DirView_BUILD_TEST)
    if (NOT DirView_ExternalTarget)
        add_gtest_source(Extern/ThirdParty)
    endif()

    set(TargetGroup Units)
    add_subdirectory(Test)
endif()
