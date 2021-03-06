#ifndef PARSER_H
#define PARSER_H

#include <QLineEdit>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTime>
#include <fstream>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>

class parser
{
public:
    parser();
    int parseLayout(QLineEdit* line);
    int parseBlogPosition(QLineEdit *line);
    void parseTitle(QLineEdit *line);
    void parseSubTitle(QLineEdit* line);
    void parseHeaderImg(QLineEdit* line);
    void parseCatalog(QLineEdit *line);
    void parsetags(QLineEdit* line);
    void parsetime();
    void parseAuthor(QLineEdit * line);
    void FinalParse();
    QString output();
    //
    QString Layout;
    QString BlogPosition;
    QString Title;
    QString SubTitle;
    QString HeaderImg;
    QString Catalog;
    QString tags;
    QString FileName;
    //

    QString outputHead;
};

#endif // PARSER_H
