set(TestTargetName ${TargetName}Test)

include(TestDirectory)
include(GroupSet)

set_group(
    TestTarget_SRC
    Source:Test1.cpp
)

include_directories(
    ${QtTemplate_INCLUDE}
    ${GTEST_INCLUDE}
)

add_executable(
    ${TestTargetName}
    ${TestTarget_SRC}
)

target_link_libraries(
    ${TestTargetName} 
    ${GTEST_LIBRARY}
)

set_target_properties(
    ${TestTargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)


if (QtTemplate_AUTO_RUN_TEST)
    run_test(${TestTargetName})
endif()
