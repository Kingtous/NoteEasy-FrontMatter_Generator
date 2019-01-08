#include "parser.h"
#include <QStringList>
#include <QFile>
#include <QTime>
#include <fstream>
using namespace std;
/*
 *
    ---
    layout:     post
    title:      "2018-12-26 智能交通讨论会"
    subtitle:   " \"确定项目主题\""
    date:       2018-12-26 17:27:00
    author:     "Kingtous"
    header-img: "img/post-bg-2015.jpg"
    catalog: true
    tags:
    - 智能交通
    ---
 *
 */

parser::parser()
{
    this->outputHead="";
}

void parser::parseLayout(QLineEdit * line)
{
    this->Layout=line->text();
    this->outputHead.append("layout: "+line->text()+'\n');
}

void parser::parseAuthor(QLineEdit * line)
{
    this->Layout=line->text();
    this->outputHead.append("author: "+line->text()+'\n');
}

void parser::parseTitle(QLineEdit *line)
{
    this->Title=line->text();
    this->FileName=line->text();
    int pos=0;
    while(Title.indexOf("\"",pos)!=-1)
    {
        int index=Title.indexOf("\"",pos);
        Title.insert(index,'\\');
        pos=index+2;
    }
    this->outputHead.append("title: "+this->Title+'\n');
}

void parser::parseBlogPosition(QLineEdit *line)
{
    this->BlogPosition=line->text()+'/';

    fstream Blog_write_position;
    Blog_write_position.open("BlogPosition.txt",ios::out);
    if(Blog_write_position)
    {
        Blog_write_position<<line->text().toStdString();
    }
    Blog_write_position.close();

    return;
}

void parser::parseSubTitle(QLineEdit* line)
{
    this->SubTitle=line->text();
    int pos=0;
    while(SubTitle.indexOf("\"",pos)!=-1)
    {
        int index=this->SubTitle.indexOf("\"",pos);
        this->SubTitle.insert(index,'\\');
        pos=index+2;
    }
    this->outputHead.append("subtitle: "+this->SubTitle+'\n');
}

void parser::parseHeaderImg(QLineEdit* line)
{
    this->HeaderImg=line->text();
    if(!this->HeaderImg.size()==0)
    {
    //判断是否在position下
    QStringList list=this->HeaderImg.split('/');
    QString FileName=list[list.size()-1];
    if(!this->HeaderImg.startsWith(this->BlogPosition))
    {
        //拷贝到目录下
            QFile::copy(this->HeaderImg,this->BlogPosition+"img/unsorted/"+
                        FileName);

    }
    //
    this->outputHead.append("header-img: img/unsorted/"+FileName+'\n');
    }
}

void parser::parseCatalog(QLineEdit *line)
{
    this->Catalog=line->text();
    this->outputHead.append("catalog: "+this->Catalog+'\n');
}

void parser::parsetags(QLineEdit* line)
{

    this->tags=line->text();
    if(this->tags.size()!=0)
    {
        this->outputHead.append("tags:\n");
        QStringList list=this->tags.split(' ');
        for (int point=0;point<list.size();++point) {
            this->outputHead.append("- "+list[point]+'\n');
        }
    }
}

void parser::parsetime()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    this->outputHead.append("date: "+current_date+'\n');
}

void parser::FinalParse()
{
    this->outputHead="---\n"+this->outputHead+"---\n";
}

void parser::output()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd");
    string storePos=this->BlogPosition.toStdString()+
            "_posts/"+current_date.toStdString()+'-'+this->FileName.toStdString()+".md";
    ofstream output(storePos);
    output<<this->outputHead.toStdString();
    output.close();
}
