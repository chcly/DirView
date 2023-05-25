import sys, os, datetime

templatename = input("Template name:")
templatename = templatename.replace(" ", "")


def genTemplates():
    global templatename

    files = [
        "README.md",
        "CMakeLists.txt",
        "CMake/CMakeLists.txt",
        "CMake/Configure.cmake",
        "Source/Application/CMakeLists.txt",
        "Source/Application/Application.h",
        "Source/Application/Application.cpp",
        "Source/Content/MainWindow.h",
        "Source/Content/MainWindow.cpp",
        "Source/Content/CMakeLists.txt",
        "Test/CMakeLists.txt",
        ".github/workflows/build-linux.yml",
        ".github/workflows/build-windows.yml",
    ]
    
    patterns = [".yml", ".txt", ".cmake", ".md", ".cpp", ".h"]
    root = os.getcwd()

    for file in files:
        full_path = root + os.sep + file
        full_path = full_path.replace("\\", os.sep)

        if os.path.isfile(full_path):

            found = False
            for pat in patterns:
                if full_path.find(pat) != -1:
                    found = True
                    break
            if found:
                print("Found", full_path)
                fp = open(full_path, "r")
                buf = fp.read()
                fp.close()
                buf = buf.replace("QtTemplate", templatename)
                fp = open(full_path, "w")
                fp.write(buf)
                fp.close()


genTemplates()
