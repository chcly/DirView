# DirView

Sample directory viewer.

![I0](Extras/SS01.png)

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

| Option                      | Description                                          | Default |
|:----------------------------|:-----------------------------------------------------|:-------:|
| DirView_BUILD_TEST         | Build the unit test program.                         |   ON    |
| DirView_AUTO_RUN_TEST      | Automatically run the test program.                  |   OFF   |



# Dependencies

```mermaid
graph BT;
      DirView-->Utils;
      DirView-->Math;
      DirView-->View;
      DirView-->Thread;
      Thread-->TBB;
      View-->Qt;
      
      Math-->Utils;
      View-->Utils;
      
      Thread-->Utils;
      
```
