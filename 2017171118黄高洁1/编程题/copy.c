#include<windows.h>
#include<stdio.h>
#define BUF_SIZE 1000

int main(int argc,LPTSTR argv [])
{
    //LPTSTR类型 与char*等价，表示普通字符/字符串变量，指向字符/字符串的指针。

    HANDLE handleIn, handleOut;//句柄（HANDLE)是资源的标识,操作系统要管理和操作这些资源，都是通过句柄来找到对应的资源
    //HANDLE 是一个32位的无符号整数,是一个对象的句柄,可以认为存放的是一个对象的地址
    //  printf("%d", handleIn);
    DWORD readsizeIn, readsizeOut;
    //#define DWORD unsigned long 所以比较方便移植用的 ，Windows下经常用来保存地址(或者存放指针) 

    CHAR Buffer [BUF_SIZE]; //大写的CHAR也表示 CHAR为单字节字符 Windows为了消除各编译器的差别，重新定义了一些数据类型

    //argc,argv 用命令行编译程序时有用
    //argc: 整数,用来统计你运行程序时送给main函数的命令行参数的个数
    //* argv[ ]: 指针数组，用来存放指向你的字符串参数的指针，每一个元素指向一个参数

    //如果传入的参数不等于3的话 说明用户没有输入正常的参数（参数多了或者少了）
    //此时提示用户正确的输入参数方法，并且退出程序
    if (argc != 3) {  
        printf ("正确使用方法: copyfile 文件名1 文件名2\n");
        return 1;
    }

    //如果通过上面判断语句的话说明参数输入符合形式 则进行下一个判断

    //（1）判断文件1是否能打开， 创建一个句柄来标识输入文件
    //CreateFile 这是一个多功能的函数，可打开或创建以下对象，并返回可访问的句柄：控制台，通信资源，目录（只读打开），磁盘驱动器，文件，邮槽，管道。
    handleIn = CreateFile (argv [1], GENERIC_READ,
        FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    //      printf("%ld", handleIn);    
    //如果文件打开失败 提示用户 并且调用GetLastError()函数取得上一个函数（也就是CreateFile函数）操作时所产生的错误代码
    if (handleIn == INVALID_HANDLE_VALUE) {
        printf ("不能打开被复制文件（文件1）. 错误代码: %x\n",
            GetLastError ());
        return 2;
    }
    //同上 这次是判断是否能打开文件2， 解释如上
    handleOut = CreateFile (argv [2], GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (handleOut == INVALID_HANDLE_VALUE) {
        printf ("不能打开目标文件（文件2）. 错误代码: %x\n",
            GetLastError ());
        return 3;
    }
    //下面进行文件复制的操作 调用ReadFile和WriteFile函数 每次读入字节数为BUF_SIZE
    //readsizeIn指向实际读取字节数的指针  而且ReadFile调用成功,返回非0，readsizeIn也要是大于0才表示可以继续读  

    while (ReadFile (handleIn, Buffer, BUF_SIZE, &readsizeIn, NULL) && readsizeIn > 0) {
        WriteFile (handleOut, Buffer, readsizeIn, &readsizeOut, NULL);
        if (readsizeIn != readsizeOut) {
            printf ("文件复制时出现错误。 错误代码: %x\n", GetLastError ());
            return 4;
        }
    }
    //提示复制成功！
    printf ("文件复制时成功\n");
    //关闭句柄 
    CloseHandle (handleIn);
    CloseHandle (handleOut);
    return 0;

}
