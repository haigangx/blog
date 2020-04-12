# 解决新版谷歌浏览器不能安装本地CRX插件文件

参考文档：[How to install Chrome extensions manually](https://www.cnet.com/how-to/how-to-install-chrome-extensions-manually/)

## 步骤：

- 谷歌浏览器中进入 **chrome://extensions** ，然后选中右上方的 **Developer mode** 开启开发者模式。
- 解压CRX插件文件，最简单的办法：将插件文件拓展名改为zip或者rar，然后解压即可，如果这种办法不行可以使用 [CRX Extractor](http://crxextractor.com/) 上传CRX文件得到相应的zip文件并且解压。
- 回到谷歌浏览器 **chrome://extensions** 窗口下，点击 **load unpacked** 然后选择插件解压的目录即可安装该插件。
