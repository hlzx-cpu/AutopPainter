# Checkpoints

## Checkpoint 1

OpenCV 4.12.0 was downloaded from the official OpenCV release source link,
configured with `BUILD_EXAMPLES=ON`, and built with Ninja. The required sample
binary is:

```bash
/Users/hanliangzhaoxuan/Developer/opencv-builds/opencv-4.12.0-build/bin/example_cpp_squares
```

The six sample images are `pic1.png` through `pic6.png`. They contain four
visible triangles in total.

Answer: `4`

## Checkpoint 2

For:

```text
8FF5 0000 0102 0304 8FDD 0000 0045 00AE 8FEE 0000
```

The pen is up from `(0,0)` to `(258,772)`, then down from `(258,772)` to
`(69,174)`.

Answer: `1441.1`

## Checkpoint 3

Generate the integrity log after the final commit:

```bash
git log --patch --pretty=format:"%h - %an, %ad : %s" --date=iso > log.txt
```

