include(GroupSet)
set(TargetName DirView)

set_group(
    TargetName_SRC 
    Source:*.cpp
    #Source/Builder:Builder/*.cpp
    Header:*.h
    #Header/Builder:Builder/*.h
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
