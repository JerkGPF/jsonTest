#include <iostream>
#include <vector>


#include "json.hpp"
#include <optional>



class TagListItem {
public:
    int id;
    std::string tagName;

    std::string createTime;

    std::string updateTime;
};

class ArticlesItem {
public:

    int id;

    std::string author;
    std::string title;

    int userId;

    int categoryId;

    std::string content;

    int views;

    int totalWords;

    std::string commentableId;

    int artStatus;

    std::string description;

    std::string imageUrl;

    std::string createTime;

    std::string updateTime;

    std::vector<TagListItem> tagList;

    std::string tagIdList;

    std::string categoryName;
};

class ResultItem {
public:

    std::string type;

    std::vector<ArticlesItem> articles;
};

class Data {
public:

    int pageNum;

    int pageSize;

    int totalSize;

    int totalPages;

    std::vector<ResultItem> result;

    void printf()
    {
        std::cout<<"pageNum:"<<pageNum<<",pageSize:"<<pageSize<<std::endl;
        for(auto res : result)
        {
            std::cout<<"type:"<<res.type<<std::endl;
            for(auto item:res.articles)
            {
                std::cout<<"title:"<<item.title<<std::endl;
            }
        }
    }
};

class Root {
public:
    int code;

    std::string msg;

    Data data;

};
namespace nlohmann {
    template <typename T>
    struct adl_serializer<std::optional<T>> {
        static void to_json(json& j, const std::optional<T>& opt) {
            if (opt == std::nullopt) {
                j = nullptr;
            } else {
                j = *opt; // this will call adl_serializer<T>::to_json which will
                // find the free function to_json in T's namespace!
            }
        }
        static void from_json(const json& j, std::optional<T>& opt) {
            if (j.is_null()) {
                opt = std::nullopt;
            } else {
                opt = j.get<T>(); // same as above, but with
                // adl_serializer<T>::from_json
            }
        }
    };
}


// 序列化struct,class
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TagListItem, id,tagName,createTime,updateTime)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ArticlesItem, id,author,title,userId,categoryId,content,
                                   views,totalWords,commentableId,artStatus,description,imageUrl,
                                   createTime,updateTime,tagList,tagIdList,categoryName)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ResultItem,type,articles)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Data, pageNum,pageSize,totalSize,totalPages,result)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Root,code,msg,data)