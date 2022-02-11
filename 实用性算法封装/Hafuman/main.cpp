#include "HafumanZip.h"
#include <fstream>
#include <iostream>

using namespace std;

void ReadFile(const char *path, uchar *&buffer, int &len) {//读取数据操作，注意传出引用
    ifstream in(path, ios::in | ios::binary);
    in.seekg(0, ios::end);
    len = in.tellg();
    in.seekg(0, ios::beg);
    buffer = new uchar[len];
    in.read((char *) buffer, len);
    in.close();
}

void WriteFile(const char *path, const uchar *&buffer, int len) {//写入数据操作，同时释放内存空间
    ofstream out(path, ios::out | ios::binary);
    out.write((char *) buffer, len);
    delete buffer;
    buffer = nullptr;
    out.close();
}

int main() {
    HafumanZip t;
    uchar *src = nullptr;
    int len;
    auto inputPath = "C:\\Users\\Alone\\Desktop\\qt源码介绍.md";
    auto outputPath = R"(C:\Users\Alone\Desktop\qt源码介绍.md.L_B__)";
    /*编码过程*/
    ReadFile(inputPath, src, len);
    cout<<"压缩前的编码长度："<<len<<endl;
    const uchar *zip = t.encode(src, len);
    delete src;src = nullptr;
    WriteFile(R"(C:\Users\Alone\Desktop\qt源码介绍.md.L_B__)", zip, t.encodeSize);//注意zip的内存在这个函数里写入后就释放了
    auto encodelen = t.encodeSize;
    cout<<"压缩后的编码长度："<<encodelen;

    /*解码过程*/
    ReadFile(outputPath,src,len);
    const uchar *unzip = t.decode(src, len);
    WriteFile("C:\\Users\\Alone\\Desktop\\C.txt", unzip, t.decodeSize);
}
