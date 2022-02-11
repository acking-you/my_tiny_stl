//
// Created by Alone on 2021/10/23.
//

#ifndef HAFUMAN_HAFUMANZIP_H
#define HAFUMAN_HAFUMANZIP_H

#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>

typedef unsigned char uchar;

struct TreeNode {//哈夫曼树的结点结构
    uchar *data;
    int cnt;//出现的次数(权值
    TreeNode *left;
    TreeNode *right;

    TreeNode(uchar *data, int cnt) : data(data), cnt(cnt), left(nullptr), right(nullptr) {}

    ~TreeNode() {
        delete data;
        data = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

class HafumanZip {
    /*存储编码表和解码表等相关数据长度信息*/
public:
    int oriLen;     //原数据长度
    int lastSize;   //压缩后最后一个字节的长度
    int decodeSize; //解码后的数据长度
    int encodeSize; //编码后的数据长度
private:
    std::unordered_map<uchar, std::string> encodeTable;
    std::unordered_map<std::string, uchar> decodeTable;
public:
    HafumanZip() : oriLen(0), lastSize(0), decodeSize(0) {}

private:/*静态成员函数实现*/
    static const uchar *HafumanEncode(const uchar *, int, int *, int *, std::unordered_map<uchar, std::string> *,
                                      std::unordered_map<std::string, uchar> *);

    /*实现编码过程需要的一些函数*/
    static std::vector<TreeNode *> *countByte(const uchar *, int);//用于得到哈夫曼数的结点
    static TreeNode *creatTree(std::vector<TreeNode *> &);

    static void deleteTree(TreeNode *);

    static void
    creatMap(std::unordered_map<uchar, std::string> *encode, std::unordered_map<std::string, uchar> *decode, TreeNode *,
             std::string *);

    static const uchar *toZip(const uchar *, int, int *, int *, std::unordered_map<uchar, std::string> *);

    /*解码过程*/
    static const uchar *HafumanDecode(const uchar *, int, int, int, int *, std::unordered_map<std::string, uchar> &);

public:
    const uchar *encode(uchar *src, int len) {
        oriLen = len;
        return HafumanEncode(src, len, &lastSize, &encodeSize, &encodeTable, &decodeTable);
    }

    const uchar *decode(const uchar *src, int len) {
        return HafumanDecode(src, len, lastSize, oriLen, &decodeSize, decodeTable);
    }
};


#endif //HAFUMAN_HAFUMANZIP_H
