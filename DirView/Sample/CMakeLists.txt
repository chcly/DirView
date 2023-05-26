include(GroupSet)
set(TargetGroup Sample)
set(TargetName DirViewer)

set_group(
    TargetName_SRC 
    Source:*.cpp
    Header:*.h
)

include_directories(
    ${DirView_INCLUDE} 
)


add_executable(
    ${TargetName} 
    ${TargetName_SRC}
)

target_link_libraries(
    ${TargetName} 
    ${DirView_DEP_LIBRARY} 
    DirView 
)

set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)

copy_to_bin(${TargetName} ${CMAKE_SOURCE_DIR}/Bin)