#ifndef PARSER_H
#define PARSER_H

#include <QLineEdit>
#include <QString>


class parser
{
public:
    parser();
    void parseLayout(QLineEdit* line);
    void parseBlogPosition(QLineEdit *line);
    void parseTitle(QLineEdit *line);
    void parseSubTitle(QLineEdit* line);
    void parseHeaderImg(QLineEdit* line);
    void parseCatalog(QLineEdit *line);
    void parsetags(QLineEdit* line);
    void parsetime();
    void parseAuthor(QLineEdit * line);
    void FinalParse();
    void output();
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
