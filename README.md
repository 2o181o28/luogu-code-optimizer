# luogu-code-optimizer

使用base64编码和[无文件ELF执行](https://blog.spoock.com/2019/08/27/elf-in-memory-execution/)绕过洛谷对于文件访问的限制，完成的C++的Babel.js类似品。

## 构建

```bash
g++ optimizer.cpp -o optimizer -std=c++11 -O2 
```

## 使用方法

`input.cpp`是你想要优化，或者需要奇怪编译选项的代码。自带的例子是我紫荆花之恋的代码，这个程序不开`-Ofast`不可能在洛谷上获得AC。

```bash
g++ input.cpp -o input -Ofast -march=native -std=c++20 # 或者任意其它你喜欢的开关
strip input
./optimizer
```

然后使用最普通的C++98、不开O2编译`output.cpp`，也可得到与你用任意你喜欢的编译开关编译`input.cpp`一样的结果。此`output.cpp`可用于洛谷提交等。例子：[使用output.cpp AC的紫荆花之恋 洛谷提交](https://www.luogu.com.cn/record/40135048)。

不保证可以在非Ubuntu 20.04的操作系统上正常运行。
