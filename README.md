# C语言程序设计课程期中作业—人人对战五子棋

## TO-DO List
- [x] 棋盘显示
- [x] 人机交互（下棋）
- [ ] 胜负判定
- [ ] 禁手规则

## 项目简介

## 编译与运行方法

- 使用CMake和MinGW编译，仅支持**windows**环境
- 请先检查环境是否安装好，输入下列指令后若能输出对应版本号，则环境配置完成
```bash
gcc -v
cmake --version
mingw32-make -v
```
- 编译方法1：先进入项目根目录，输入下列指令：
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```
- 编译方法2：使用写好的批处理脚本，在根目录中输入下列指令`./cmake_build.bat`
- 运行方法：双击build/中的P2PChessGame.exe或者在根目录中`./build/P2PChessGame.exe`
## 文件结构

本项目包含多个文件，在此节中说明文件组织结构
```
2024K8009929011/      # 根目录
├── src/              # 源代码目录
│   ├── board/      
│   │   ├── board.h   # 棋盘相关的头文件
│   │   └── board.c   # 棋盘相关函数的实现(初始化、落子等)
│   ├── display/   
│   │   ├── display.h # 显示相关的头文件
│   │   └── display.c # 显示相关函数的实现(棋盘绘制、清屏等)
│   ├── rule/  
│   │   ├── rule.h    # 规则相关的头文件
│   │   └── rule.c    # 规则相关函数的实现(胜负判定、禁手等)
│   └── main.c        # 主程序
├── test/             # 测试用例
│   └── test_rule.c   # 禁手规则测试文件
├── .gitignore        # Git忽略配置
├── CMakeLists.txt    # Cmake文件
├── cmake_build.bat   # Cmake编译批处理脚本
└── README.md         # 说明文档
```
## 操作说明
- 所有输入均在stdin，所有输出均在stdout
- 输入时有明确文字提示，用键盘输入坐标即可，若输入不合法会有提示并需要重新输入
- 坐标输入结束后需要按回车才能将输入提交，程序可以即时反应并将结果打印

## 功能列表

## 已知问题

- 棋盘显示时部分字符编码有问题，仅支持UTF-8，调试时无法支持GBK编码
- 棋盘边框仅支持圆角边框，使用直角边框会出现乱码

## 其他