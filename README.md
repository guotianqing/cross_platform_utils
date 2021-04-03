# cross_platform_utils
cross platform linux &amp; windows c++ utils class

# 说明
---

旨在构建一个跨平台的c++实用类。

# changelist
---

- 增加了获取线程id的接口，该id为Linux下top命令第一列所显示的id
- 增加了检测进程是否正在运行的接口
- 增加了字符串分割接口
- 增加了生成随机数接口
- 增加cmake构建，同时生成动态库和静态库
- 增加了unittest，使用gtest
