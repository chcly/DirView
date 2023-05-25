include(GroupSet)
set(TargetName DirViewContent)

set_group(
    TargetName_SRC 
    Source:*.cpp
    Header:*.h
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
