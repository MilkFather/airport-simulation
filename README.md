# Airport Simulation

**这个项目已经完成并归档，不再积极开发。**

*欢迎提Issue，也欢迎开pull request*

## 目前状态

已完成。


## 如何编译

推荐使用Linux(Ubuntu)以获得最好的编译体验，macOS也可以，Windows需要特别进行配置。

* 仅需在代码所在的工作目录下(命令行)输入```make```或```make build```即可自动完成编译。在文件夹```bin```当中寻找编译出的程序；
* 输入```make flush```可以清除中间生成的```.o```文件；
* 输入```make clean```可以清除所有生成文件，包括```.o```文件和编译出的程序；
* 输入```make cleanbuild```将会先执行```clean```，然后执行```build```，最后执行```flush```，以全新状态执行编译，只留下最后产物。
