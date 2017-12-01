/******************************************************************************************
 * c++д��һ��xml������
 * ��ȡxml��Ϣ�����ṹ����
 * ���ظ��ڵ�
 * author:fflyingfree
 * date:2017/12/01
*******************************************************************************************/

#ifndef XMLUTILS_H
#define XMLUTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

//��ǩ�ڵ����ݽṹ
typedef struct confNode{
    std::string nodeName;
    std::string nodeValue;
    std::vector<confNode> vChildNode;
}ST_CONF_NODE;

class CXmlUtils{
public:
    //���������ļ���Ϣ
    static int loadXmlConf(const char* confURL,ST_CONF_NODE* rootNode);
private:
    static int trim(std::string &str);  //ȥ�ո�
    //ȥ����Ч��Ϣ������ע�ͣ������ǩ�����Ϣ��
    static int delUnuseInfo(std::string &preRet);
    //������ <b<a> , ȥ��b��a֮���<
    static int mvErr(std::string &str);
    //xml�����ļ�Ԥ����
    static int preDealXml(std::string &preRet, std::ifstream &ifs);
    //��ȡ��ǩ�ڵ㣬��״�ṹ�洢
    static int getNodes(ST_CONF_NODE *rootNode, std::string &confInfo,int &itr);
    static int getNode(ST_CONF_NODE *pNode, std::string &confInfo,int &itr);
};

#endif // XMLUTILS_H
