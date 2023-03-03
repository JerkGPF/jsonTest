#include <iostream>
#include "Data.hpp"
#include <fstream>

void readTest()
{
    Root root;
    std::ifstream ifs("test.json",std::ios::in);
    nlohmann::json j;
    if(ifs.is_open())
        ifs>>j;
    ifs.close();
    root = j;
    std::cout<<"code:"<<root.code<<std::endl;
    std::cout<<"msg:"<<root.msg<<std::endl;
    Data *data = new Data;
    *data = j.at("data");
    data->printf();
    delete data;
}
void writeTest()
{
    ArticlesItem articlesItem;
    articlesItem.title = "文章名字";
    std::vector<ArticlesItem> articles;
    articles.push_back(articlesItem);
    ResultItem resultItem = {"类别",articles};
    std::vector<ResultItem> results;
    results.push_back(resultItem);
    Data data = {1,1,1,1,results};
    Root root = {200,"成功",data};
    nlohmann::json  j = root;
    std::ofstream ofs("writeTest.json",std::ios::out);
    if (ofs.is_open())
        ofs<<j;
    else
        std::cout<<"文件打开失败";
    ofs.close();
}
int main() {
    readTest();
    writeTest();
    return 0;
}
