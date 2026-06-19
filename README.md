# AutoPainter

This repository contains a small C++ implementation for the Auto Painter course
assignment. The program reads the JPG images in `test_dataset/`, classifies
pixels to the seven supported pen colors, plans simple scanline strokes, and
writes the required `submission.json` file.

## Build

OpenCV was built from the official OpenCV 4.12.0 source package with
`BUILD_EXAMPLES=ON`. On this machine the local install prefix is:

```bash
/Users/hanliangzhaoxuan/Developer/opencv-builds/opencv-4.12.0-install
```

Configure this project with:

```bash
cmake -S . -B build -DOpenCV_DIR=/Users/hanliangzhaoxuan/Developer/opencv-builds/opencv-4.12.0-install/lib/cmake/opencv4
cmake --build build
```

Generate the JSON submission:

```bash
./build/autopainter test_dataset submission.json
```

Recompute checkpoint two:

```bash
./build/checkpoint_distance
```
