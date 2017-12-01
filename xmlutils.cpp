#include "xmlutils.h"


//加载配置文件信息  返回标签根节点
int CXmlUtils::loadXmlConf(const char *confURL, ST_CONF_NODE *rootNode){
    std::ifstream ifs;
    ifs.open(confURL,std::ios::in);
    std::string preRet="";
    preDealXml(preRet,ifs);

    int itr=0;
    getNodes(rootNode,preRet,itr);
    return 0;
}

int CXmlUtils::getNodes(ST_CONF_NODE *rootNode, std::string &confInfo, int &itr){
    while(itr < confInfo.length()){
        getNode(rootNode,confInfo,itr);
        ++itr;
    }
    return 0;
}

int CXmlUtils::getNode(ST_CONF_NODE *pNode, std::string &confInfo,int &itr){
    ST_CONF_NODE node;
    int iStart,iEnd;
    int leafFlg=0;  //叶子节点标志
    int returnFlag=0;  //递归出口
    for(;itr < confInfo.length();++itr){
        if(returnFlag){
            if(confInfo.substr(itr,1)==">"){
                return 1;
            }
            continue;
        }
        if(confInfo.substr(itr,2)=="</"){
            if(leafFlg){
                iEnd=itr;
                node.nodeValue=confInfo.substr(iStart,iEnd-iStart);
            }
            leafFlg=0;
            pNode->vChildNode.push_back(node);
            returnFlag=1;
            continue;
        }
        if(confInfo.substr(itr,1)==">"){
            iEnd=itr;
            node.nodeName=confInfo.substr(iStart,iEnd-iStart);
            iStart=++itr;
            if(confInfo.substr(iStart,1)=="<" && confInfo.substr(iStart,2)!="</"){
                while(confInfo.substr(iStart,1)=="<" && confInfo.substr(iStart,2)!="</"){
                    getNode(&node,confInfo,itr);
                    iStart=++itr;
                }
            }else{
                leafFlg=1;
            }
            --itr;
            continue;
        }
        if(confInfo.substr(itr,1)=="<" && confInfo.substr(itr,2)!="</"){
            iStart=itr+1;
            continue;
        }
    }

    return 0;
}

int CXmlUtils::preDealXml(std::string &preRet, std::ifstream &ifs){
    preRet.clear();
    char buf[1024];
    std::string strLine;  //去空格后的一行
    while(!ifs.eof()){
        ifs.getline(buf,1024);
        strLine=buf;
        //去空格
        trim(strLine);
        preRet+=strLine;
    }
    delUnuseInfo(preRet);
    mvErr(preRet);
    trim(preRet);
    return 0;
}

//纠错，如 <b<a> , 去掉b和a之间的<
int CXmlUtils::mvErr(std::string &str){
    int errChkFlg=0;  //纠错标志
    for(int i=0;i<str.length();++i){
       if(str.substr(i,1) == ">"){
            errChkFlg=0;
            continue;
        }
        if(errChkFlg){
            if(str.substr(i,1)=="<"){
                str.at(i)=' ';
                continue;
            }
        }
        if(str.substr(i,1) == "<"){
            errChkFlg=1;
        }
    }
    return 0;
}

//去掉无效信息，例如注释，游离标签外的信息等
int CXmlUtils::delUnuseInfo(std::string &preRet){
    int flag=0; //无效信息标志
    std::string type="";  //无效信息结束类型
    std::string subTemp;
    for(int i=0;i<preRet.length();++i){
        if(((subTemp=preRet.substr(i,2)) == "?>"
            || (subTemp=preRet.substr(i,3)) == "-->"
            || ((subTemp=preRet.substr(i,1)) == "<" && preRet.substr(i,4)!="<!--" ) )
                && type==subTemp){
            if(subTemp!="<"){
                for(int j=0;j<subTemp.length();++j){
                    preRet.at(i+j)=' ';
                }
            }
            i+=(subTemp.length()-1);
            flag=0;  //一个无效信息结束
            continue;
        }
        if(flag){  //无效信息
            preRet.at(i)=' ';
            continue;
        }
        if((subTemp=preRet.substr(i,2)) == "<?"
                || (subTemp=preRet.substr(i,4)) == "<!--"
                || (subTemp=preRet.substr(i,1)) == ">"){
            if(subTemp!=">"){
                for(int j=0;j<subTemp.length();++j){
                    preRet.at(i+j)=' ';
                }
            }
            i+=(subTemp.length()-1);
            flag=1;  //一个无效信息开始
            if(subTemp==">"){
                int j=i+1;
                for(;j<preRet.length();++j){
                    if(preRet.substr(j,1)=="<"){
                        break;
                    }
                }
                if(preRet.substr(j,2)=="</"){
                    flag=0;
                }
            }

            if(subTemp=="<?"){
                type="?>";  //这个无效信息的结束类型
            }
            if(subTemp=="<!--"){
                type="-->";
            }
            if(subTemp==">"){
                type="<";
            }
            continue;
        }
    }
    return 0;
}

//去空格
int CXmlUtils::trim(std::string &str){
    std::string strBuf=str;
    std::string chStr;
    str.clear();
    for(int i=0;i<strBuf.length();++i){
        if((chStr=strBuf.substr(i,1)) != " " && chStr != "\t"
                && chStr != "\n" && chStr != "\r"){
            str+=chStr;
        }
    }
    return 0;
}


















