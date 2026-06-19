# AutoPainter

这是 Auto Painter 大作业的一版 C++ 基线程序。现在的做法比较直接：
先把输入图片里的颜色归到题目给出的 7 支笔，再按颜色做横向扫描线，
最后把轨迹编码成网站要求的 `submission.json`。

这版不是最终优化算法，主要目标是先把工程结构、OpenCV 读取图片、
指令编码和 JSON 输出都打通。后面如果继续提分，重点应该改
`src/planner.cpp` 里的路径规划逻辑。

## 目录

- `include/autopainter/`：几个小模块的头文件。
- `src/`：颜色分类、路径规划、指令编码、JSON 输出。
- `tools/checkpoint_distance.cpp`：用来复算题目给的指令距离。
- `test_dataset/`：助教给的测试图片。

## 编译

本机的 OpenCV 是从官方 4.12.0 源码编译的，编译 examples 时开了
`BUILD_EXAMPLES=ON`。安装位置在：

```bash
/Users/hanliangzhaoxuan/Developer/opencv-builds/opencv-4.12.0-install
```

配置和编译本项目：

```bash
cmake -S . -B build -DOpenCV_DIR=/Users/hanliangzhaoxuan/Developer/opencv-builds/opencv-4.12.0-install/lib/cmake/opencv4
cmake --build build
```

## 生成提交文件

```bash
./build/autopainter test_dataset submission.json
```

运行后会在仓库根目录生成 `submission.json`，这个文件就是网站最终任务要上传的 JSON。

## 诚信记录

诚信证明不用另外写作文档，按作业文档给的命令导出 Git 历史即可：

```bash
git log --patch --pretty=format:"%h - %an, %ad : %s" --date=iso > log.txt
```

导出的 `log.txt` 用来上传到诚信审查页面。
