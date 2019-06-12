# 系统使用书

## 开发环境
- 开发平台：windows 10

- 编程语言：C++

- 开发框架：Qt

## 编译方法
- 命令行方式：
命令行进入项目源代码文件夹，并输入：
```
qmake
nmake
```
- 使用Qt(项目路径中不能存在中文): 
    1. Qt打开 CGConsole.pro(命令行界面程序) 或 CGGUI.pro(图形用户界面程序)
    2. 构建->执行qmake
    ![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/1.png)
    3. 选择release，然后运行
    ![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/2.png)

## 系统简介
### 命令行界面程序
&emsp;&emsp;命令行界面程序(CGConsole.exe) 要求输入含有图元绘制指令序列的文本文件的保存路径和图像保存路径，然后它会读取含有图元绘制指令序列的文本文件，执行每条指令相对应的动作。
&emsp;&emsp;目前命令行界面程序实现的功能有：重置画布、保存画布、设置画笔颜色、绘制线段、绘制多边形、绘制椭圆、绘制曲线、图元平移、图元旋转、图元缩放、线段裁剪。

### 图形用户界面程序
&emsp;&emsp;图形用户界面程序(CGGUI.exe)目前实现的功能有：重置画布、保存画布、设置画笔颜色、绘制线段、绘制多边形、绘制椭圆、绘制曲线、图元平移、图元旋转、图元缩放、线段裁剪，该程序中图元的 id 是其被绘制的顺序（从 1 开始记录），重置画布后 id 会从 1 开始记录。
&emsp;&emsp;图形用户界面程序(CGGUI.exe) 主界面如图所示，蓝色区域的两个按钮分别是保存画布和重置画布功能按钮，红色区域的按钮是绘制按钮，可以绘制线段、绘制多边形、绘制椭圆、绘制曲线，黄色部分的按钮和输入框和图元平移、图元旋转、图元缩放、线段裁剪功能有关，黑色部分的滑动条和输入框可以用来改变画笔颜色。
![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/mainwindow.png "mainwindow.png")


## 系统使用方法

### 命令行界面程序

&emsp;&emsp;将想要执行的图元绘制指令序列存入某一文本文件中，双击CGConsole.exe文件，按提示输入含有图元绘制指令序列的文本文件的文件路径以及生成图像的保存路径，如图。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/cli.gif "cli.gif")

#### 绘制指令
- 重置画布，清空当前画布，并重新设置宽高：
`restCanvas width height`

- 保存画布，将当前画布保存为位图name.bmp：
`saveCanvas name`

- 设置画笔颜色，将当前画笔颜色设置为RGB颜色：
`setColor R G B`

- 绘制线段，使用算法绘制从$(x_1,y_1)$到$(x_2,y_2)$的线段：
`drawLine id x1 y1 x2 y2 algorithm`

- 绘制多边形，使用算法绘制以$(x_1,y_1)$...$(x_n,y_n)$为顶点的多边形：
```
drawPolygon id n algorithm
x_1 y_1 … x_n y_n
```

- 绘制椭圆，绘制以$(x,y)$为中心，$rx$为长轴长，$ry$为短轴长的椭圆：
`drawEllipse id x y rx ry`

- 绘制曲线，使用算法绘制以$(x_1,y_1)$...$(x_n,y_n)$为控制顶点的曲线：
```
drawCurve id n algorithm
x_1 y_1 … x_n y_n
```

- 图元平移，以$(dx,dy)$为平移向量，将id对应的图元进行平移：
`translate id dx dy`

- 图元旋转，以$(x,y)$为旋转中心，将id对应的图元旋转r角度：
`rotate id x y r`

- 图元缩放，以$(x,y)$为缩放中心，将id对应的图元进行缩放s倍：
`scale id x y s`

- 线段裁剪，使用算法将 id 对应的线段进行裁剪，裁剪窗口由($x_1$, $y_1$) 与($x_2$, $y_2$) 确定。
`clip id x1 y1 x2 y2 algorithm`

#### 样例
```
resetCanvas 100 100
setColor 255 0 0
drawLine 5 7 39 93 71 DDA
saveCanvas output_1
```
![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/output_1.bmp "output_1.bmp")
```
setColor 0 162 232
drawLine 233 96 35 15 58 DDA
saveCanvas output_2
```
![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/output_2.bmp "output_2.bmp")
```
clip 5 33 10 70 58 Liang-Barsky
saveCanvas output_3
```
![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/output_3.bmp "output_3.bmp")
```
rotate 5 33 49 -90
saveCanvas output_4
```
![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/output_4.bmp "output_4.bmp")
```
drawEllipse 123 31 49 8 18
setColor 0 0 0
drawPolygon 666 6 DDA
44 22 73 30 74 77 59 56 32 63 25 49
saveCanvas output_5
```
![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/output_5.bmp "output_5.bmp")
```
rotate 666 59 56 90
translate 666 -8 -18
saveCanvas output_6
```
![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/output_6.bmp "output_6.bmp")
```
resetCanvas 160 100
drawCurve 10 4 Bezier
28 34 9 86 61 4 129 42
setColor 0 255 0
drawCurve 11 4 Bezier
114 88 60 92 99 3 42 24
saveCanvas output_7
```
![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/output_7.bmp "output_7.bmp")

### 图形用户界面程序

#### 启动
&emsp;&emsp;双击CGGUI.exe启动程序。

#### 重置画布
&emsp;&emsp;点击按纽栏的第二个按钮即可清空画布，重置画布后新绘制的图元的 id 会从 1 开始记录。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/clean.gif "clean.gif")

#### 保存画布
&emsp;&emsp;点击按纽栏的第一个按钮后，选择路径并输入文件名，即可保存画布。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/save.gif "save.gif")

#### 设置画笔颜色
&emsp;&emsp;通过滑动右下方滑动条或者在输入框中输入数字或者点击箭头改变R、G、B 对应的值就可以设置画笔颜色。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/color.gif "color.gif")

#### 绘制线段
&emsp;&emsp;点击按纽栏的第三个（第四个）按钮即可进入用DDA 算法(Bresenham 算法) 绘制直线的模式。左键点击画布中任意一处，并按住左键移动即可绘制直线，松开左键代表绘制结束。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/line.gif "line.gif")

#### 绘制矩形
&emsp;&emsp;点击按纽栏的第五个按钮即可进入绘制矩形的模式。左键点击画布中任意一处，并按住左键移动即可绘制矩形，松开左键代表绘制结束。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/rect.gif "rect.gif")

#### 绘制多边形
&emsp;&emsp;点击按纽栏的第六个（第七个）按钮即可进入用DDA 算法(Bresenham 算法) 绘制多边形的模式。通过左键单击画布中的任意一处添加顶点，左键每点击一次就添加一个顶点，画布将显示所有顶点生成的多边形。再次点击按钮或者画布中单击右键表示目前多边形绘制结束，可开始新的多边形绘制。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/poly.gif "poly.gif")

#### 绘制椭圆
&emsp;&emsp;点击按纽栏的第八个按钮即可进入绘制椭圆的模式。左键点击画布中任意一处，并按住左键移动即可绘制椭圆，松开左键代表绘制结束。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/elli.gif "elli.gif")

#### 绘制曲线
&emsp;&emsp;点击按纽栏的第九个（第十个）按钮即可进入用绘制Bezier 曲线（B-spline 曲线）的模式。通过左键单击画布中的任意一处添加控制点，左键每点击一次就添加一个控制点，画布将显示所有控制点生成的曲线。再次点击按钮或者画布中单击右键表示目前曲线绘制结束，可开始新的曲线绘制。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/curve.gif "curve.gif")

#### 图元平移
&emsp;&emsp;在 tartget id 处输入被平移的图元 id，该程序中图元的 id 是其被绘制的顺序（从 1 开始记录），在 dx 和 dy 处输入平移向量后，点击 translate 按钮就可以完成对 target id 对应图元的平移操作。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/translate.gif "translate.gif")

#### 图元旋转
&emsp;&emsp;在 tartget id 处输入被旋转的图元 id，该程序中图元的 id 是其被绘制的顺序（从 1 开始记录）。其次选择旋转中心，两种方法：1、在 x 输入框处输入旋转中心的 x 坐标，在 y 输入框处输入旋转中心的 y 坐标；2、点击按纽栏的第十一个按钮进入选择选择中心的模式，单击画布中的任意一处即可将对应位置设置成旋转中心。然后选择旋转角度，通过拖动滑动条选择旋转角度，最后点击 rotate 按钮就可以完成对 target id 对应图元的旋转操作。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/rotate.gif "rotate.gif")

#### 图元缩放
&emsp;&emsp;在 tartget id 处输入被缩放的图元id，该程序中图元的 id 是其被绘制的顺序（从 1 开始记录）。其次选择缩放中心，两种方法：1、在 x 输入框处输入缩放中心的 x 坐标，在 y 输入框处输入缩放中心的 y 坐标；2、点击按纽栏的第十一个按钮进入选择缩放中心的模式，单击画布中的任意一处即可将对应位置设置成缩放中心。然后选择缩放倍数，通过拖动滑动条选择缩放倍数，最后点击 scale 按钮就可以完成对 target id 对应图元的缩放操作。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/scale.gif "scale.gif")

#### 线段裁剪
&emsp;&emsp;在  tartget id 处输入被缩放的图元 id，该程序中图元的 id 是其被绘制的顺序（从 1 开始记录）。其次选择裁剪窗口，两种方法：1、在 xmin 输入框处输入裁剪窗口左下顶点的 x 坐标，在 ymin 输入框处输入裁剪窗口左下顶点的 y 坐标，在 xmax 输入框处输入裁剪窗口右上顶点的 x 坐标，在 ymax 输入框处输入裁剪窗口右上顶点的 y 坐标；2、单击按纽栏的第十二个按钮进入选择裁剪窗口左下顶点的模式，单击画布中的任意一处即可将对应位置设置成裁剪窗口左下顶点，然后单击按纽栏的第十三个按钮进入选择裁剪窗口右上顶点的模式，单击画布中的任意一处即可将对应位置设置成裁剪窗口右上顶点（确保单击第十二个按钮后选择的点位于单击第十三个按钮后选择的点的左下方）。最后点击 Cohen-Sutherland（Liang-Barsky）按钮就可以使用 Cohen-Sutherland（Liang-Barsky）算法完成对 target id 对应线段的裁剪操作。

![](https://github.com/zhaoxxxxn/CG-HOMEWORK-A-CANVAS/tree/master/picture/clip.gif "clip.gif")
