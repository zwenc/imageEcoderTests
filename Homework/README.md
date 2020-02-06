### 使用方法

安装opencv库，注意把dll放到对应位置（项目太久了，忘记要放到哪里了，百度可以解决）



命令：

```
 .\Homework.exe image.png quantizationLevel DeliveryMode Latency 
```

* quantizationLevel：量化水平，写1吧
* DeliveryMode：模式，分为3中，
  * 1：显示iDCT
  * 2：逐步选取频率分量编码
  * 3：按高低位编码
* Latency  ：延时，显示动图的时候，两帧图片的间隔


