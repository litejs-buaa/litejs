### String 字符串

#### 简介

字符串字面量的存储形式与其他token的存储形式不太一样，因为需要实现Unicode支持，字符串使用了`char_16t`数组作为内部存储形式。使用的是token结构体中的`content_16`数组。在存储时，所有的字符均按16位存储，如果是ASCII字符则高八位均为0。

#### 实现

字符串的解析最重要的工作是对于转义字符的处理，在我们的实现中，我们编写了一个转义字符处理函数`parse_escape`，当状态机读取到`\`时，就会进入转义处理部分，除了单双引号和换行连接的情况，其他所有情况均有上述函数处理。

#### 现存缺陷

* 用于将token输出的调试功能还无法输出除ASCII以外的字符，具体的Unicode解析还需要由虚拟机来完成。
* 目前还不支持源码级的UTF-8输入，字符串中使用Unicode仅能通过转义字符输入。
* 字符串变量的值单独开了一个数组，增大的内存占用，最好在之后将所有token值统一为`char_16t`存储。
* 没有实现JS严格模式