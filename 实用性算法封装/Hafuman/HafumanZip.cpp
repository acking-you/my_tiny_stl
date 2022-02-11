//
// Created by Alone on 2021/10/23.
//

#include "HafumanZip.h"

const uchar *
HafumanZip::HafumanEncode(const uchar *src, int len, int *lastSize, int *returnSize,
                          std::unordered_map<uchar, std::string> *encode,
                          std::unordered_map<std::string, uchar> *decode) {
    std::vector<TreeNode *> *treeNodes = countByte(src, len);
    TreeNode *tree = creatTree(*treeNodes);
    delete treeNodes;
    std::string *t = new std::string;
    creatMap(encode, decode, tree, t);
    delete t;
    deleteTree(tree);
    return toZip(src, len, lastSize, returnSize, encode);
}

//得到哈夫曼树的根结点
std::vector<TreeNode *> *HafumanZip::countByte(const uchar *src, int length) {
    std::unordered_map<uchar, int> cnt;
    std::vector<TreeNode *> *ret = new std::vector<TreeNode *>;
    for (int i = 0; i < length; i++) {
        cnt[src[i]]++;
    }
    for (auto[key, val]:cnt) {
        ret->push_back(new TreeNode(new uchar(key), val));
    }
    return ret;
}

TreeNode *HafumanZip::creatTree(std::vector<TreeNode *> &list) {
    while (list.size() > 1) {
        std::sort(list.begin(), list.end(), [](TreeNode *a, TreeNode *b) { return a->cnt > b->cnt; });
        TreeNode *a = list.back();
        list.pop_back();
        TreeNode *b = list.back();
        list.pop_back();
        TreeNode *c = new TreeNode(nullptr, a->cnt + b->cnt);
        c->left = a;
        c->right = b;
        list.push_back(c);
    }
    return list[0];
}


/*得到编码表和解码表*/
void
HafumanZip::creatMap(std::unordered_map<uchar, std::string> *encode, std::unordered_map<std::string, uchar> *decode,
                     TreeNode *root, std::string *sb) {
    if (root == nullptr)return;
    if (root->data == nullptr) {
        sb->push_back('0');
        creatMap(encode, decode, root->left, sb);
        sb->pop_back();
        sb->push_back('1');
        creatMap(encode, decode, root->right, sb);
        sb->pop_back();
    } else {
        (*encode)[*root->data] = *sb;
        (*decode)[*sb] = *root->data;
    }
}

/*开始编码*/
const uchar *HafumanZip::toZip(const uchar *src, int len, int *lastSize, int *returnSize,
                               std::unordered_map<uchar, std::string> *encode) {
    std::string str;
    for (int i = 0; i < len; i++) {
        str += (*encode)[src[i]];
    }
    int length, strlen = str.size();
    if (str.size() % 8 == 0) {
        length = strlen / 8;
        *lastSize = 0;
    } else {
        length = strlen / 8 + 1;
        *lastSize = strlen % 8;
    }
    *returnSize = length;
    uchar *res = new uchar[length];
    int index = 0;
    for (int i = 0; i < strlen; i += 8) {
        if (i + 8 > strlen) {
            std::bitset<8> tmp;
            int idx = 7;
            for (int j = i; j < strlen; j++) {
                if (str[j] == '1') {
                    tmp[idx--] = 1;
                } else tmp[idx--] = 0;
            }
            res[index++] = tmp.to_ulong();
            break;
        }
        std::bitset<8> t(str.substr(i, 8));
        res[index++] = t.to_ulong();
    }
    return res;
}

void HafumanZip::deleteTree(TreeNode *root) {
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = nullptr;
}

/*解码过程*/
const uchar *HafumanZip::HafumanDecode(const uchar *src, int len, int lastSize, int oriLen, int *returnSize,
                                       std::unordered_map<std::string, uchar> &decode) {
    std::string t;
    for (int i = 0; i < len; i++) {
        if (i == len - 1 && lastSize != 0) {//对最后的有效长度不为整8的特殊处理
            for (int j = 0; j < lastSize; j++) {
                if ((src[i] >> (7 - j)) & 1)
                    t.push_back('1');
                else
                    t.push_back('0');
            }
            break;
        }
        std::bitset<8> conv(src[i]);
        t += conv.to_string();
    }
    uchar *res = new uchar[oriLen + 1024];
    int index = 0;
    for (int i = 0; i < t.size();) {//由于是完全还原了原始的编码字符串，所以只需要一直往前读就行了
        int sz = 1;
        while (!decode.count(t.substr(i, sz)))sz++;
        if (decode.count(t.substr(i, sz)))
            res[index++] = decode[t.substr(i, sz)];
        i += sz;
    }
    *returnSize = index;
    return res;
}


