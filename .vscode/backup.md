Backup Code for tasks.json
{
    "comment1": "// See https://go.microsoft.com/fwlink/?LinkId=733558",
    "comment2": "// for the documentation about the tasks.json format",
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build project",
            "type": "shell",
            "command": "C:/mingw-w64/mingw64/bin/g++.exe",
            "args": [
                "-o",
                "\"${workspaceFolder}\"/bin/main.exe",
                "-I",
                "\"${workspaceFolder}\"/headers",
                "-ggdb",
                "\"${workspaceFolder}\"/source/*.cpp",
                "\"${workspaceFolder}\"/source/SDL2/*.cpp",
                "\"${workspaceFolder}\"/source/games/*.cpp",
                "-L\"${workspaceFolder}\"/SDL2/include/SDL2",
                "-L\"${workspaceFolder}\"/SDL2/lib",
                "-Wall",
                "-lmingw32",
                "-lSDL2main",
                "-lSDL2",
                "-lSDL2_image",
                "-lSDL2_ttf",
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": [],
            "options": {
                "cwd": "C:/mingw-w64/mingw64/bin/"
            }
        },
        {
            "label": "build test project",
            "type": "shell",
            "command": "C:/mingw-w64/mingw64/bin/g++.exe",
            "args": [
                "-std=c++11",
                "-o",
                "\"${workspaceFolder}\"/bin/testmain.exe",
                "-I",
                "\"${workspaceFolder}\"/headers",
                "-I",
                "C:/googletest/googletest/include",
                "-I",
                "C:/googletest/googletest",
                "-ggdb",
                "\"${workspaceFolder}\"/tests/*.cpp",
                "\"${workspaceFolder}\"/source/*.cpp",
                "C:/googletest/googletest/src/gtest-all.cc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": [],
            "options": {
                "cwd": "C:/mingw-w64/mingw64/bin/"
            }
        },
        {
            "label": "run",
            "type": "shell",
            "command": "./bin/main.exe",
            "problemMatcher": []
        },
        {
            "label": "run tests",
            "type": "shell",
            "command": "./bin/testmain.exe",
            "problemMatcher": []
        },
        {
            "label": "run on windows cmd shell ",
            "type": "shell",
            "command": "\"${workspaceFolder}/bin/main.exe\"",
            "options": {
                "cwd": "bin"
            },
            "problemMatcher": []
        },
        {
            "label": "run tests on windows cmd shell ",
            "type": "shell",
            "command": "\"${workspaceFolder}/bin/testmain.exe\"",
            "options": {
                "cwd": "bin"
            },
            "problemMatcher": []
        }
    ]
}