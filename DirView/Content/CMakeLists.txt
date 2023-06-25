include(GroupSet)
set(TargetName DirView)

set_group(
    TargetName_SRC 
    Source:*.cpp
    Source/Builder:Builder/*.cpp
    Source/Cache:Cache/*.cpp
    Header:*.h
    Header/Builder:Builder/*.h
    Header/Cache:Cache/*.h
)

include_directories(
    ${DirView_INCLUDE} 
)


add_library(
    ${TargetName} 
    ${TargetName_SRC}
)

target_link_libraries(
    ${TargetName} 
    ${DirView_DEP_LIBRARY}
)

set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)
qt_auto_resource(${TargetName})
