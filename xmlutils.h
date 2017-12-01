/******************************************************************************************
 * c++写的一个xml处理类
 * 读取xml信息，树结构保存
 * 返回根节点
 * author:fflyingfree
 * date:2017/12/01
*******************************************************************************************/

#ifndef XMLUTILS_H
#define XMLUTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

//标签节点数据结构
typedef struct confNode{
    std::string nodeName;
    std::string nodeValue;
    std::vector<confNode> vChildNode;
}ST_CONF_NODE;

class CXmlUtils{
public:
    //加载配置文件信息
    static int loadXmlConf(const char* confURL,ST_CONF_NODE* rootNode);
private:
    static int trim(std::string &str);  //去空格
    //去掉无效信息，例如注释，游离标签外的信息等
    static int delUnuseInfo(std::string &preRet);
    //纠错，如 <b<a> , 去掉b和a之间的<
    static int mvErr(std::string &str);
    //xml配置文件预处理
    static int preDealXml(std::string &preRet, std::ifstream &ifs);
    //获取标签节点，树状结构存储
    static int getNodes(ST_CONF_NODE *rootNode, std::string &confInfo,int &itr);
    static int getNode(ST_CONF_NODE *pNode, std::string &confInfo,int &itr);
};

#endif // XMLUTILS_H
