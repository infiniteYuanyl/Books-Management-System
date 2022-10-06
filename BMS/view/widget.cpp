#include "widget.h"
#include "MainWindow.h"
#include "ui_widget.h"
#include <QFile>
#include <QTextStream>
#include <string>
#include "../backend/Utils.h"
#include "../backend/MD5.h"
#include "../backend/User.h"
#include <QDir>
#include <QString>

extern User now_user ;
extern Utils now_utils;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置窗口名
    this->setWindowTitle("登录");
    ui->label_user_name->setScaledContents(true);   //图片自适应label大小
    ui->label_pwd->setScaledContents(true);         //图片自适应label大小

    ui->lineE_pwd->setEchoMode(QLineEdit::Password);//设置为小黑点

    connect(ui->btn_1,SIGNAL(clicked(bool)),this,SLOT(set_style()));
    connect(ui->btn_2,SIGNAL(clicked(bool)),this,SLOT(set_style()));
    connect(ui->btn_3,SIGNAL(clicked(bool)),this,SLOT(set_style()));
    connect(ui->btn_4,SIGNAL(clicked(bool)),this,SLOT(set_style()));
}

/*
* 槽函数-皮肤设置
*/
QPushButton* btn;
void Widget::set_style()
{
    btn = qobject_cast<QPushButton*>(sender());//获取发射信号的对象
    QString filePath;
    if("btn_1" == btn->objectName())        //粉色
    {
        filePath = ":/qss/login/style-1.qss";
    }else if("btn_2" == btn->objectName())  //黄蓝
    {
        filePath = ":/qss/login/style-2.qss";
    }else if("btn_3" == btn->objectName())  //浅紫
    {
        filePath = ":/qss/login/style-3.qss";
    }else if("btn_4" == btn->objectName())  //青绿
    {
        filePath = ":/qss/login/style-4.qss";
    }

    /*皮肤设置*/
    QFile file(filePath);/*QSS文件所在的路径*/
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    file.close();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_login_clicked()
{

    QString account=ui->lineE_user_name->text();
    QString pwd=ui->lineE_pwd->text();

    MD5 md5;
    string b= md5.read(pwd.toStdString());//加密

    int flag;
    string t=account.toStdString();
    char* account2=const_cast<char*>(t.c_str());
    char* pwd2=const_cast<char*>(b.c_str());

//登陆
    flag=now_utils.Login(account2,pwd2);
    if(flag==0){
        //账户不存在
        ui->label->setText("账户不存在");
    }else if(flag==1){
        //密码错误
        ui->label->setText("密码错误");
        ui->lineE_pwd->setText("");
    }else{
        //登陆成功
        ui->label->setText("登陆成功");
        this->hide();
        now_user=now_utils.GetUserByAccount(account2);
        MainWindow *personal_homepage = new MainWindow;
        personal_homepage->show();
    }

}


void Widget::on_btn_register_clicked()
{

    QString account=ui->lineE_user_name->text();
    QString pwd=ui->lineE_pwd->text();

    MD5 md5;
    string b= md5.read(pwd.toStdString());//加密

    int flag;
    string t=account.toStdString();
    char* account2=const_cast<char*>(t.c_str());
    char* pwd2=const_cast<char*>(b.c_str());

    now_user.setAccount(account2);
    now_user.setPassword(pwd2);

    now_user.setSex(1);
    string s="LiHua";
    char* ss=const_cast<char*>(s.c_str());
    now_user.setName(ss);
    now_user.setDebet(10);
    s="CS";
    ss=const_cast<char*>(s.c_str());
    now_user.setMajor(ss);

    flag=now_utils.Register(now_user);
    if(flag==0){
        //账户已存在
        ui->label->setText("账户已存在");
    }else if(flag==-1){
        //注册失败
        ui->label->setText("注册错误");
    }else if(flag==1){
        //注册成功
        ui->label->setText("注册成功");
    }

}
