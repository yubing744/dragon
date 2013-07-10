ChangeLog for Dragon
--------------------

Version 0.01 2013-06-19
--------------------------

1.  使用scons实现跨平台构建.

2.  使用Sublime Text 2 实现跨平台开发。

3.  使用SublimeGDB在Mac电脑上调试代码。

4.  实现 dragon::lang::String 类，该类内部使用 32bit字符，支持Unicode编码，
    使用到的库为 libunicode-0.4。

5.  实现工具包 dragon::util::regex，通过封装开源正则表达式引擎 pcre 实现，当前
    使用的pcre版本是 pcre-8.33。

6.  使用gtest来做单元测试，版本为 1.6.0。

7.  使用valgrind作为内存泄露检查工具。 


Version 0.02 2013-06-22
-----------------------------

1. Implements StringBuffer class


Version 0.03 2013-07-09
-----------------------------

1. Implements simple gc

2. Define class SmartPointer and SmartArrayPointer for count ref.