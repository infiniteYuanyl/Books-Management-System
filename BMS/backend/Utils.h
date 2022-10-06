#ifndef UTILS_H
#define UTILS_H
#include "all_head.h"
#include "myFileDB.h"

class Utils {
public:
    //登录
    myFileDB db;
    Utils(string path) : db(path) {}


    int Login(char* account, char* password); //参数1:账号，参数2:密码。   返回值：0:账户不存在； 2:登陆成功；1:密码错误

    //注册
    int Register(User user); //参数：用户对象。    返回值：0:账号已存在，1:注册成功, -1：注册失败

    //修改信息
    bool UpdateUser(User before, User after); //参数1为需要修改的User对象（只需要有学号），参数2为修改后的User对象，返回修改操作是否成功

    //由名字筛选用户
    bool GetUserByName(char* name, vector<User>&result);

    //由名字筛选用户
    bool GetUserByAccount(char* account,User& user0);

    //由id筛选用户,速度最快建议首选
    bool GetUserById(int id,User& user0);

    //由专业筛选用户
    bool GetUserByMajor(char* major, vector<User>&result);

    //删除学生
    bool DeleteUser(User user); //参数：User对象，返回是操作是否成功

    //还款
    bool Repayment(User user); //参数为用户对象，返回是否成功

    //添加学生
    bool InsertUser(User user); //参数：User对象，进行插入操作，返回是操作是否成功







    //管理员登录
    int AdminLogin(char* account, char* password);  //参数1:账号，参数2:密码。返回值：0:账户不存在；1:登陆成功；2:密码错误

    //由名字筛选管理员
    bool GetAdminByName(char* name, vector<Admin>&result);

    //由账号筛选管理员
    Admin GetAdminByAccount(char* account);

    //管理员注册
    int AdminRegister(Admin admin); //参数：管理员对象。返回值：0:账号已存在，1:注册成功, -1：注册失败

    //添加管理员
    bool InsertAdmin(Admin admin); //参数：管理员对象，进行插入操作，返回是操作是否成功








    //添加书的种类（！！注意！！增加书的数量请用UpdateBook）
    bool InsertBook(Book book); //参数：Book对象，进行插入操作，返回是操作是否成功

    //删除书
    bool DeleteBook(Book book); //参数：Book对象，只需要有isbn号，进行插入操作，返回是操作是否成功

    //修改图书信息
    bool UpdateBook(Book before, Book after); //参数1为需要修改的Book对象（只需要有isbn号），参数2为修改后的Book对象，返回修改操作是否成功

    //根据ISBN获取图书
    bool GetBookByIsbn(char* isbn,Book &book0); //参数为图书isbn，返回该isbn对应的图书对象

    //按书名找书
    bool GetBooksByBookName(char* name, vector<Book>&result); //参数1为图书名，参数2为存结果列表，操作为根据书名检索图书，返回操作是否成功

    //按作者找书
    bool GetBooksByAuthor(char* author, vector<Book>&result); //参数1为作者名，参数2为存结果列表，操作为根据作者名检索图书，返回操作是否成功

    //按分区找书
    bool GetBooksByClassification(char* classification, vector<Book>&result); //参数1为分区id，参数2为存结果列表，操作为根据分区id检索图书，返回操作是否成功的结果

    //查看该书余量
    int GetBookMargin(char* isbn);//参数1为图书isbn，返回该书还有多少没有被借走

    //由id筛选书,速度最快建议首选
    bool GetBookById(int id,Book &book0); //参数为图书id，返回该id对应的图书对象






    //添加借书关系
    bool InsertRecord(Record record); //参数：Record对象，进行插入操作，返回是操作是否成功

    //删除借书关系
    bool DeleteRecord(Record record); //参数：Record对象，返回是操作是否成功

    //返回关于这本书的借阅记录
    bool GetBookBorrowList(char* isbn,vector<Record>&result);

    //返回用户的借书记录
    bool GetUserBorrowList(char * account,vector<Record>&result);

    //查找借书
    bool GetRecord(char* account, char* isbn,Record &record0);//参数1学生账号，参数2图书isbn，返回唯一的Record对象

    //还书
    bool Return(char* account, char* isbn);

    //修改借书信息
    bool UpdateRecord(Record before, Record after);//参数1为需要修改的Record对象，参数2为修改后的Record对象，返回修改操作是否成功








    //(！！需要没人预约且无人预约,否则会返回失败!!)
    bool InsertReserve(Reserve reserve); //参数：Reserve对象，进行插入操作，返回是操作是否成功

    //删除预约关系
    bool DeleteReserve(Reserve reserve); //参数：Reserve对象(只需要account 和 ISBN)，返回是操作是否成功

    //取消预约
    bool PreAppoint(char* account, char* isbn); //参数1:取消预约者用户，参数2:所取消预约图书,返回操作是否成功

    //查找预约
    bool GetReserve(char* account, char* isbn,Reserve &reserve0);//参数1学生账号，参数2图书id，返回唯一的Reserve对象

    //修改预约信息
    bool UpdateReserve(Reserve before, Reserve after);//参数1为需要修改的Reserve对象，参数2为修改后的Reserve对象，返回修改操作是否成功

    //返回预约这本书的人，如果没有，返回FALSE
    bool GetReserveUser(char* isbn,Reserve &reserve0);

    //返回用户的所有预约记录
    bool GetUserReserveList(char * account,vector<Reserve>&result);



    //获取推荐列表
    bool GetRecommendList(User user, vector<Book>&result); //参数1为User对象,参数2为存结果列表，返回值为该用户的推荐书目列表

    //获取借书列表
    bool GetRecordList(User user, vector<Book>&result); //参数1为User对象，参数2为存结果列表，返回该用户的正在借书列表






    bool CheckUserExist(User user);//该对象只需要有只需填账号（学号）

    bool CheckAdminExist(Admin admin);//该对象只需要有只需填账号

    bool CheckBookExist(Book book);//该对象只需要有ISBN

    bool CheckRecordExist(Record record);//该对象只需要有学号和ISBN号

    bool CheckReserveExist(Reserve reserve); //该对象只需要有学号和ISBN号
};


#endif //UTILS_H
