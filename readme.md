## <2>解压 进入该目录后执行
##./configure 
## b目录下 cd lib       执行 make
## 此时会在上层目录（就是刚才有configure那个目录）生成libunp.a文件
## <3>复制libunp.a到 /usr/lib下  （以后gcc编译就可以用 -lunp来调用该库文件）
## <4>最后在configure目录下找到config.h  在lib目录下找到unp.h 复制到你写代码的某个文件下即可
## 把unp.h中 #include "../config.h"改成#include "config.h"include    "print.c"
