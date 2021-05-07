因为``master``分支的``readme``与``tools``文件夹会经常更新，其中``readme``会有一些开发的建议，``tools``会包含一些小工具，不是某个系统专有的，自己写自己那部分有一些感觉可以作为全项目通用的``api``可以放进去,有时候需要某些通用功能时(比如需要获取时间)可以看看``tools``文件夹里的函数。

因此在每次开发前，建议在自己fork的仓库下先全部``pull``该项目，然后将``master``分支``merge``到自己分支上。当然在此之前，自己分支已有的工作要先进行``commit``保存。



即流程如下:

1. ``git pull -a``

看当前各个分支是否都是最新状态，如果某个分支有改动会将改动拉取下来，这个操作不会影响你自己分支的文件.

![image-20210404231603427](C:\Users\ELIO\AppData\Roaming\Typora\typora-user-images\image-20210404231603427.png)

2. ``git merge master``

   执行该操作时确保 

   1.在你自己的分支下进行 

   2.所有你自己的工作修改已经commit了。

   如果有未commit的，会报错。一般情况merge master 分支不会出现你自己分支的冲突，如果有冲突，如下

   ![image-20210404233023744](C:\Users\ELIO\AppData\Roaming\Typora\typora-user-images\image-20210404233023744.png)

   选择怎样在你的分支保留这个冲突部分即可，比如修改为

   ![image-20210404233317723](C:\Users\ELIO\AppData\Roaming\Typora\typora-user-images\image-20210404233317723.png)

   之后在当前分支commit该修改，然后再git merge master即可。

   ![image-20210404233759193](C:\Users\ELIO\AppData\Roaming\Typora\typora-user-images\image-20210404233759193.png)

   一般出问题的时候命令行都会提示怎样修改，按着指示做即可。

   

   master 有主要更新时会发提醒，那时候就merge master分支到自己分支即可。

   