# DirView

Sample directory viewer.

Provides a different type of graphical view of the file system. 

+ [ScreenShot](Extras/SS01.png) - Shows a screen capture. 

## Testing

The testing directory is setup to work with [googletest](https://github.com/google/googletest).

## Building

![A1](https://github.com/chcly/DirView/actions/workflows/build-linux.yml/badge.svg)
![A2](https://github.com/chcly/DirView/actions/workflows/build-windows.yml/badge.svg)

```sh
mkdir Build
cmake -S . -B Build -DDirView_BUILD_TEST=ON -DDirView_AUTO_RUN_TEST=ON
cmake --build Build
```

Optional defines.

| Option                | Description                         | Default |
| :-------------------- | :---------------------------------- | :-----: |
| DirView_BUILD_TEST    | Build the unit test program.        |   ON    |
| DirView_AUTO_RUN_TEST | Automatically run the test program. |   OFF   |

### Dependencies

Local and external dependencies.

```mermaid
graph BT;
      DirView-->Utils;
      DirView-->View;
      DirView-->Math;
      DirView-->Thread;

      Thread-->TBB;
      Thread-->Utils;

      Math-->Utils;

      View-->Qt;
      View-->Utils;

      Qt-->Core;
      Qt-->Gui;
      Qt-->Widgets;
      
```
