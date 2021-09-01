# Makefile 使用说明

### Makefile开头的可选项
* `CONFIG_LTO`  
    是否使用LTO优化编译，默认为是
    一般情况下不会出什么问题，不过如果出了请注释掉此行。
* `CFLAGS_CUSTOM`  
    在此加入你需要的gcc命令，默认值为-O2优化
    如果需要其他优化方式或Werror报错信息等选项请在此添加。
* `prefix`  
    QuickJS所在的源码目录，默认值为空。
* `CONFIG_BIGNUM`  
    编译时是否开启QuickJS的大数处理部分，默认值为是，若关闭请注释掉此行。
* `BUILD_EXAMPLES`  
    编译后是否同时生成自带的静态js编译展示文件，默认值为否。  
    选择是后会在QuickJS根目录生成./example文件夹里的js文件自动转换而来的c文件。
* `BUILD_TESTS`  
    编译后是否立即进行自带的功能测试，默认值为否。
---
### Makefile可用命令
* 编译相关
    >* `make`  
    只编译QuickJS本体相关文件
    >* `make install`  
    将qjs和qjsc作为命令安装到./bin目录里
    >* `make clean`  
    清除make命令产生的文件
* qjs测试相关
    >* `make test`  
    用tests目录下的js依次测试qjs命令的基本功能有无报错
    >* `make microbench`  
    测试qjs能否跑完自带的microbench  
    >* `make testall`  
    test+microbench+test2+test2o（见下）
* 其他测试模块的编译
    >* `make run-test262`  
    编译test262测试命令，可用来进行测试目录中的test262,test262bn（bignum）,test262o三个测试。以test262为例：  
    `time ./run-test262 -m -c test262.conf -a`
    >* `make unicode_gen`  
    编译unicode生成命令
    >* `make regexp_test`  
    编译正则表达式测试命令
---
### 做出的改动
* 在默认运行及调试环境为Linux系统的前提下，删去了Darwin/win32相关的判断项和一些不必要的Debug条目
* 将调试选项、tests、examples的编译独立了出来
* 整理了多余的变量