#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //tab order
    QWidget::setTabOrder(ui->AuthorEdit,ui->layoutEdit);
    QWidget::setTabOrder(ui->layoutEdit,ui->titleEdit);
    QWidget::setTabOrder(ui->titleEdit,ui->subtitleEdit);
    QWidget::setTabOrder(ui->subtitleEdit,ui->catalogEdit);
    QWidget::setTabOrder(ui->catalogEdit,ui->tagsEdit);

    //read content
    fstream Blog_read_position;
    Blog_read_position.open("BlogPosition.txt",ios::in);
    if(Blog_read_position)
    {
        string str;
        Blog_read_position>>str;
        ui->BlogPositionEdit->setText(QString::fromStdString(str));
    }
    Blog_read_position.close();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Start_clicked()
{
    parser par;
    //parse head
    par.parseBlogPosition(ui->BlogPositionEdit);
    par.parseLayout(ui->layoutEdit);
    par.parseTitle(ui->titleEdit);
    par.parseSubTitle(ui->subtitleEdit);
    par.parseAuthor(ui->AuthorEdit);
    par.parsetime();
    par.parseHeaderImg(ui->imgEdit);
    par.parseCatalog(ui->catalogEdit);
    par.parsetags(ui->tagsEdit);
    par.FinalParse();
    //parse store file
    par.output();
    //open Directory
    QProcess::startDetached("open "+par.BlogPosition+"_posts/");
}

void MainWindow::on_BlogPositionBrowser_clicked()
{
    QString Dir=QFileDialog::getExistingDirectory(this);
    ui->BlogPositionEdit->setText(Dir);
}

void MainWindow::on_imgBrowser_clicked()
{
    QString Dir=QFileDialog::getOpenFileName(this);
    ui->imgEdit->setText(Dir);
}


void MainWindow::on_tagsEdit_cursorPositionChanged(int arg1, int arg2)
{
    QPoint point=ui->tagsEdit->pos();
    QToolTip::showText(point,"Split tags by space.");
}

void MainWindow::on_pushButton_clicked()
{
    QString pos=ui->BlogPositionEdit->text();
    if(pos.size()!=0)
    {
        QProcess::startDetached("open "+ui->BlogPositionEdit->text()+"/_posts");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString pos=ui->BlogPositionEdit->text();
    if(pos.size()!=0)
    {
        QProcess::startDetached("open "+ui->BlogPositionEdit->text());
    }
}
