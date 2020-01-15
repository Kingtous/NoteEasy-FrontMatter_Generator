#include "parser.h"

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

int parser::parseLayout(QLineEdit * line)
{
    this->Layout=line->text();
    if(this->Layout.size()!=0)
    {
        this->outputHead.append("layout: "+line->text()+'\n');
        return 0;
    }
    return -1;
}

void parser::parseAuthor(QLineEdit * line)
{
    this->Layout=line->text();
    if(this->Layout.size()!=0)
    {
        this->outputHead.append("author: "+line->text()+'\n');
    }
}

void parser::parseTitle(QLineEdit *line)
{
    this->Title=line->text();
    this->FileName=line->text();
    if(this->Title.size()!=0)
    {
        int pos=0;
        while(Title.indexOf("\"",pos)!=-1)
        {
            int index=Title.indexOf("\"",pos);
            Title.insert(index,'\\');
            pos=index+2;
        }
        this->outputHead.append("title: "+this->Title+'\n');
    }

}

int parser::parseBlogPosition(QLineEdit *line)
{

    this->BlogPosition=line->text();
    if(this->BlogPosition!=0)
    {
        QString pos = this->BlogPosition;
        this->BlogPosition=this->BlogPosition+'/';

        QString str=QDir::homePath();
        QFile* configFile = new QFile();
        configFile->setFileName(str+"/.blogPosition.cfg");
        // 写入配置
        bool openFlag = configFile->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
        if (!openFlag){
            return -1;
        } else {
            QTextStream textStream(configFile);
            textStream << pos;
        }
        configFile->close();
        return 0;
    }
    return -1;
}

void parser::parseSubTitle(QLineEdit* line)
{
    this->SubTitle=line->text();
    if(this->SubTitle!=0)
    {
        int pos=0;
        while(SubTitle.indexOf("\"",pos)!=-1)
        {
            int index=this->SubTitle.indexOf("\"",pos);
            this->SubTitle.insert(index,'\\');
            pos=index+2;
        }
        this->outputHead.append("subtitle: "+this->SubTitle+'\n');
    }
}

void parser::parseHeaderImg(QLineEdit* line)
{
    this->HeaderImg=line->text();
    if(this->HeaderImg.size()!=0)
    {
        //判断是否在position下
        QStringList list=this->HeaderImg.split('/');
        QString FileName=list[list.size()-1];
        if(!this->HeaderImg.startsWith(this->BlogPosition))
        {
            //拷贝到目录下
                QFile::copy(this->HeaderImg,this->BlogPosition+"img/unsorted/"+
                            FileName);
                this->outputHead.append("header-img: img/unsorted/"+FileName+'\n');
        }
        //
        else {

            int pos=this->BlogPosition.size();
            QString abspath=this->HeaderImg.mid(pos);
            this->outputHead.append("header-img: "+
                                    abspath
                                    +"\n");
        }
    }
}

void parser::parseCatalog(QLineEdit *line)
{
    this->Catalog=line->text();
    if(this->Catalog.size()!=0)
    {
        this->outputHead.append("catalog: "+this->Catalog+'\n');
    }
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

QString parser::output()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd");
    string storePos=this->BlogPosition.toStdString()+
            "_posts/"+current_date.toStdString()+'-'+this->FileName.toStdString()+".md";
    ofstream output(storePos);
    output<<this->outputHead.toStdString();
    output.close();

    return QString::fromStdString(storePos);
}
