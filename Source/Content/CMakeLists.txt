include(GroupSet)
set(TargetName QtTemplateContent)

set_group(
    TargetName_SRC 
    Source:*.cpp
    Header:*.h
)

include_directories(
    ${QtTemplate_INCLUDE} 
)


add_library(
    ${TargetName} 
    ${TargetName_SRC}
)

target_link_libraries(
    ${TargetName} 
    ${QtTemplate_DEP_LIBRARY}
)

set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)
