# Video-cut
Cut any part of the video at any time into a single video.

The environment used by this program is ubuntu18.04、QT、opencv4.2.0.

You can modify the input video format on line 18 of the mainwindow.cpp file, the default mp4 format; modify the save path and format on line 141.

Since this program has a Chinese interface, the following description will appear in Chinese.

1. Use process (English version):
After running the program, first click "Select File", click "Start Play" and the video will play in the window. When the video reaches the part to be intercepted first, click "Ready to mark", the video will stop and wait to select the interception area. Use Left mouse click on the upper left corner coordinates of the area to be intercepted on the image, right click on the lower right corner coordinates of the area to be intercepted on the image, a red box will appear in the image. For the selection area, if you want to reselect, click "Clear Mark ", click" Ready to mark ", select again, and click" Start saving ". After the video loads, start to play the selected region video, and save the video at the same time, click" Stop saving "to stop the video.

2. 使用流程（中文版）：
运行程序后，先点击“选择文件”，点击“开始播放”视频会在窗口中进行播放，当视频到达先要截取的部分时，点击“准备标记”，视频会停止，等待选择截取区域，使用鼠标左键点击图像上想要截取区域的左上角坐标，使用鼠标右键点击图像上想要截取区域的右下角坐标，图像会出现红色的框，为选择区域，如果想要重新选择，点击“清除标记”，点击“准备标记”，重新选择，点击“开始保存”，视频加载后，开始播放选择截取的区域视频，同时对视频进行保存，点击“停止保存”，视频停止。
