### <center>RSA实验报告


#### 一、实验环境介绍

##### 1.1 电脑软硬件配置

- 软件平台：

  操作系统：Windows 10专业版，64位操作系统

  开发软件：Microsoft Visual Studio Premium 2012​	

- 硬件配置：

  CPU：Intel i7-9700

  内存：16GB

##### 1.2 编译环境

- 编程语言：C++，使用MFC框架

- 编译选项：本地Windows调试器

#### 二、程序使用说明

##### 2.1 程序初始化

![1572751944630](pic\1572751944630.png)

​		源代码编译完成后，运行RSA.exe可执行程序，初始化界面如图所示。

​		界面分为四个按钮，两个只读区（查看`p`, `q`），四个可写区（自定义公钥e、原文、密文和解密文本），计算的中间变量如`n = p * q`，密钥`d`等不可见。

<div style="page-break-after:always;"></div>
##### 2.2 程序执行顺序

​		执行顺序如下图，提供四个可选的加密方式：`RSA-512(not safe)`、`RAS-768`、`RAS-1024`和`RAS-2048`，密钥长度越长、执行时间越长、加密字符串长度的上限越高。

​		其中公钥`e`可由用户自定义输入，如果计算出的`e`和`d`不可逆，则会随机生成`e`，再次计算密钥`d`。

![1572752286945](pic\1572752286945.png)

##### 2.3 程序运行实例

![1572752699956](pic\1572752699956.png)

#### 三、代码架构

![1572753837339](pic\1572753837339.png)

1. LargeInt.h：大数运算库，在该文件中实现了大数的四则运算以及取模运算。

2. Generator.h：密钥运算库，包括利用millerRabin算法生成指定位数的大素数（该算法分别用自定义的大数运算库、gmp库实现一遍，并对两算法的执行时间进行了比较，见后文）

3. Crypt.h：封装了生成密钥、加密、解密等函数，为MFC提供对应的函数接口。

#### 四、RSA算法

##### 4.1 素数筛法

​		实现素数筛法`O(n)`复杂度，得到`n`以内的质数并保存为`vector`，将`vector`中的质数作为millerRabin检测的底，来验证大素数的正确性。

##### 4.2 快速幂模运算

​		在计算`a^b(mod n)`时，使用快速幂函数计算，将`b`改写为二进制字符串`str`，从前至后扫描`str`，遇`1`则乘`a`再平方，遇`0`则直接平方。在不考虑模运算复杂度的情况下，快速幂只需要`O(lg b)`的复杂度。

##### 4.3 大数除法运算

​		对于自定义的大数类`LargeInt`，在计算`a / b`时，用较少的时间预先对商进行估值，而后更新`a=a-q*b`。由于减法和乘法的运行效率高于除法，因此可以在一定程度上降低除法运行时间，具体实现见`LargeInt.cpp`的`296~334`行。虽然效率有一定优化，但实际测试时，其复杂度仍然较高，在大素数的生成过程中不可避免地使用了gmp.h库。

##### 4.4 大数运算细节

​		在大数类中定义`symbol`表示正负号，这样一来，虽然在四则运算中需要考虑符号细节。但是可以在利用Bezout定理求密钥`d`时减少工作量。

##### 4.5 CRT定理

​		使用了CRT中国剩余定理计算`x^d(mod n)`这类计算，有效的优化了计算时间。

##### 4.6 运行时间对比

​		做实验来验证不同算法和优化对于时间的影响，结果见下表。

1. 对于不同密钥长度，加密相同长度的文本，文本长度为22。
2. 对比在解密过程中，使用CRT定理和不使用定理的执行时间，CRT的速度有`2~3`的提升。
3. 在生成密钥时，分为两种实现方式：自定义四则运算生成密钥 **VS** 利用gmp库生成密钥。可知gmp库的效率确实很高。（整个程序只有在生成密钥和大数除法时借助了gmp库）

| 时间(s)  | 解密   | 解密（CRT） | 密钥生成 | 密钥生成(GMP) |
| -------- | ------ | ----------- | -------- | ------------- |
| RSA-768  | 2.451  | 1.072       | 33.667   | 0.032         |
| RSA-1024 | 4.855  | 2.049       | 182.219  | 0.102         |
| RSA-2048 | 30.863 | 11.503      | 336.188  | 1.064         |

##### 五、实验感想和收获

​		在完成应用密码学课程RSA大作业的过程中，加深了我对于欧几里得定理、Bezout定理、CRT定理等的理解和感悟。总的来说，代码的实现细节非常重要，例如大数类中以`1^28`为底(而非`10^9`)，可以在转换为16进制时减少复杂度；还有在代码中使用底层的位运算，而非四则运算，也可以极大的提高运行效率。

​		虽然个人在代码中加入了许多优化，但是在实际的生产生活中，最好还是直接使用gmp等大数库，避免"造轮子"这类工作，站在前人的肩膀上才能看得更远。gmp库将数据看作二进制流，大量使用了位运算，在除法、幂运算体现出了极大的优势。在测试2048位密钥时，自己写的(除法运算等)函数虽然测试完成，但其时间过长，因此不得不采用gmp库。

​		最后，在测试和调研过程中，发现密钥长度对于加密算法的安全性有直接关系，位数较少的密钥，虽然运行效率非常高，但是其并不能保证安全性，因为破解起来也更加的轻松。整体上感觉加密和破解是一对相互促进、螺旋上升的过程：好的加密方案会促进社会的发展和进步，也会激励更多的人来研究如何破解；不同破解密钥新思想、新方式的提出，又不断促进好的密码方案的进步，两者相辅相成。
