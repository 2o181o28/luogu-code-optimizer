# luogu-code-optimizer

使用base64编码和[无文件ELF执行](https://blog.spoock.com/2019/08/27/elf-in-memory-execution/)绕过洛谷对于文件访问的限制，完成的C++的Babel.js类似品。更多细节详见[我的博客](https://2o181o28.github.io/2020/10/20/%E6%97%A0%E6%96%87%E4%BB%B6ELF%E6%89%A7%E8%A1%8C%E4%BB%A5%E5%8F%8A%E6%B4%9B%E8%B0%B7%E6%89%8B%E5%8A%A8O2/)。

## 使用方法

```bash
./optimize.sh input.cpp output.cpp # 将input.cpp优化为output.cpp
./optimize.sh input.cpp # 优化input.cpp并覆盖input.cpp，将引发警告
./optimize.sh input output.cpp # 将任意的可执行文件input转化为output.cpp
```

此`output.cpp`可用于洛谷提交等。例子：[使用output.cpp AC的紫荆花之恋 洛谷提交](https://www.luogu.com.cn/record/46375489)。

脚本返回值`0`代表执行成功；`1`代表文件操作失败了；`2`代表编译错误。

比如说你想要提交一个开了最高编译优化，使用C++20标准，Clang++编译器，链接pthread库的代码`1.cpp`（显然洛谷不支持这些功能），将其变成可以使用C++98标准，古董g++编译器，不带任何编译开关编译的代码`2.cpp`：
```bash
clang++ 1.cpp -o 1 -Ofast -march=native -std=c++20 -lpthread && strip 1
./optimize.sh 1 2.cpp
```

不保证可以在非Ubuntu 20.04的操作系统上正常运行。
