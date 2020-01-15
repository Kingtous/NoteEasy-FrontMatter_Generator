#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>

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
    QMessageBox box;
    // 获取引用的配置路径，写在Home目录下，.为隐藏文件
    QString str=QDir::homePath();
    qDebug() << str;
    QFile* configFile = new QFile();
    configFile->setFileName(str+"/.blogPosition.cfg");
    // 读取配置
    bool openFlag = configFile->open(QIODevice::ReadOnly | QIODevice::Text);
    if (!openFlag){
        return;
    } else {
        QTextStream textStream(configFile);
        QString leastFolder = textStream.readLine();
        ui->BlogPositionEdit->setText(leastFolder);
    }
    configFile->close();
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
    QString storeFullPath = par.output();
    //open Directory
    // 判断操作系统
    if (QSysInfo::kernelType()[0] == 'w'){
        // Windows System，直接当前文件
        QProcess::startDetached(storeFullPath);
    } else {
        // Unix Or Linux System, 使用open函数打开文件
        QProcess::startDetached("open "+storeFullPath);
    }

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
