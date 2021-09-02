## QuickJS GC 机制总结

1. 调用 js_trigger_gc：

- 新建对象（重新赋值）
  - 调用 gc，成功创建后将对象引用计数记 1 并加入 gc_obj_list 中

- 函数返回：
  - 先调用 JSFreeValue() 处理局部变量，再调用 gc 处理环引用
  - JS_FreeValue() --> __ JSFreeValue --> __ JSFreeValueRT --> free_zero_refcount
  - __ JSFreeValueRT 将对象引用计数减 1 且加入 gc_zero_ref_count_list 并调用函数 free_zero_refcount 释放，函数 free_zero_refcount 调用 free_gc_object 释放

2. 调用 js_RunGc：

- js_trigger_gc
- JS_FreeRuntime
- 组成：
  - gc_decref：遍历 gc_obj_list 中的对象，对每个对象调用 mark_children，将对象 mark 置 1 表示已检查，如果该对象引用计数为 0 将其加入 tmp_obj_list
    - mark_children：调用 mark_func (gc_decref_children)
    - gc_decref_children：将每个对象的属性引用计数减 1，减完之后如果计数为 0 且 mark 为 1，则存放到 tmp_obj_list中
  - gc_scan：再次遍历 gc_obj_list，将对象 mark 置回 0，对每个对象调用 mark_children（gc_scan_incref_child）；遍历 tmp_obj_list，对每个对象调用 mark_children（gc_scan_incref_child2）
    - gc_scan_incref_child：将每个对象的属性引用计数加 1，加完之后如果计数为 1，则放回 gc_obj_list中，并置 mark 回 0
    - gc_scan_incref_child2：将每个对象的属性引用计数加 1
  - gc_free_cycles：遍历 tmp_obj_list 调用 free_gc_object
    - free_gc_object：调用 free_object 和 free_function_bytecode
      - free_object：清空对象结构体的所有内容，放入 gc_zero_ref_count_list 或调用 js_free_rt 处理



## QuickJS 程序初始化所申请的变量

**JS_NewRuntime :**

- rt

- JS_InitAtoms :  predefined_atom

  JS_ResizeAtomHash

  JS_NewAtomInit :  js_alloc_string_rt,  JS_NewAtom

- JS_Class

  init_class_range :  JS_NewClass1

- rt->shape_hash

**JS_NewContext :**

- JS_NewContextRaw

  JS_AddIntrinsicBasicObjects

- JS : intrinsic object, method, function



## GC 内存管理机制调研

- 方舟编译器：内存随用随回收，回收时无需暂停应用，引用计数，没找到其堆内存分配相关文档
- malloc：块内存分裂，延迟合并（项目主要参考）
  - [自己动手实现一个malloc内存分配器](https://zhuanlan.zhihu.com/p/367060283)
  - [malloc 原理和内存分配](https://blog.csdn.net/zpznba/article/details/90445349)
- orp 初生代分配：指针标识即可，因为 GC 是按照分代移动设计的，不怕碎片
  - **ORP.pdf** & **ORP 调研.md**
- **Garbage Collector of XORP.ppt** & **Clean Version -- Design a High Performance JVM for Embedded Systems.ppt** & **内存垃圾收集器.ppt**

