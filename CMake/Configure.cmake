include(GitUpdate)
if (NOT GitUpdate_SUCCESS)
    return()
endif()

include(StaticRuntime)
include(GTestUtils)
include(ExternalTarget)
include(ConfigureQt)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY AUTOGEN_TARGETS_FOLDER "CMakePredefinedTargets/Qt")
set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP   "Generated/Qt")

option(QtTemplate_BUILD_TEST    "Build the unit test program." OFF)
option(QtTemplate_AUTO_RUN_TEST "Automatically run the test program." OFF)
option(QtTemplate_BUILD_SAMPLE  "Build the sample program" ON)

# can cause isuses with std::string, so you 
# have to force the dll dependency
# on the final executable
set_dynamic_runtime()

DefineExternalTargetEx(
    Utils Extern
    ${QtTemplate_SOURCE_DIR}/Internal/Utils 
    ${QtTemplate_SOURCE_DIR}/Internal/Utils
    ${QtTemplate_BUILD_TEST}
    ${QtTemplate_AUTO_RUN_TEST}
)

DefineExternalTargetEx(
    View Extern
    ${QtTemplate_SOURCE_DIR}/Internal/View 
    ${QtTemplate_SOURCE_DIR}/Internal/View
    ${QtTemplate_BUILD_TEST}
    ${QtTemplate_AUTO_RUN_TEST}
)

DefineExternalTargetEx(
    Thread Extern
    ${QtTemplate_SOURCE_DIR}/Internal/Thread 
    ${QtTemplate_SOURCE_DIR}/Internal/Thread
    ${QtTemplate_BUILD_TEST}
    ${QtTemplate_AUTO_RUN_TEST}
)

configure_gtest(${QtTemplate_SOURCE_DIR}/Test/googletest 
                ${QtTemplate_SOURCE_DIR}/Test/googletest/googletest/include)


if (WIN32)
    configure_qt_windows(Core Widgets Gui Test)
    qt_standard_project_setup()
else()
    configure_qt_linux(Core Widgets Gui Test)
endif()
                
set(Configure_SUCCEEDED TRUE)