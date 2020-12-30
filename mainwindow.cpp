#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QPushButton"
#include"QMessageBox"
#include"QKeyEvent"
#include"QDebug"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置参与矩阵运算的数量
    connect(ui->MatNumSet,&QPushButton::clicked,[=](){
        if(ui->MatNumText->text()==""){
            QMessageBox::information(this,"error","MatNum cannot be empty");
        }
        else
        {
            MatNum=ui->MatNumText->text().toInt();
            if(MatNum<=1)
            {
                QMessageBox::information(this,"error","MatNum cannot be 1 or 0!");
            }
            else
            {
                ui->MatNumReset->setEnabled(true);
                QString TextString;
                TextString=ui->MatNumText->text();
                ui->textBrowser->setText("MatNum is "+TextString);
             }
         }
    });
    connect(ui->MatNumReset,&QPushButton::clicked,[=](){
        MatNum=0;
        ui->MatNumReset->setEnabled(false);
        ui->MatNumText->setText("");
        ui->textBrowser->setText("");
        ui->SetColText->clear();
        ui->SetRowText->clear();
        i=1;
    });

    connect(ui->MatSizeSet,&QPushButton::clicked,[=](){
        if(MatNum<=1||ui->MatNumText->text()==" ")
        {
            QMessageBox::information(this,"error","Please set MatNumber");
        }
        else
        {
            if(MatNum<i)
            {
                QMessageBox::information(this,"error","You have exceed the maximum number");
            }
            else
            {
                row[i-1]=ui->SetRowText->text().toInt();
                col[i-1]=ui->SetColText->text().toInt();
                if((row[i-1])!=0&&(col[i-1])!=0)
                {
                    QMessageBox::information(this,"success","Mat "+QString::number(i)+" size set successfully");
                    ui->SetRowSize->setText("Mat "+QString::number(i+1)+" RowSize");
                    ui->SetColSize->setText("Mat "+QString::number(i+1)+" ColSize");
                    ui->textBrowser->append("Mat "+QString::number(i)+" size is "+QString::number(row[i-1])+"x"+QString::number(col[i-1]));
                    ui->SetColText->clear();
                    ui->SetRowText->clear();
                    ui->MatSizeReset->setEnabled(true);
                    if(i==MatNum&&row[i-1]>0&&col[i-1]>0)
                    {
                        ui->input->setEnabled(true);
                        ui->textBrowser->append("Mat "+QString::number(j)+" is");
                    }
                    i++;

                }
                else
                {
                    QMessageBox::information(this,"error","Size cannot be 0 ");
                    ui->SetColText->clear();
                    ui->SetRowText->clear();
                }
            }
        }

    });
    connect(ui->MatSizeReset,&QPushButton::clicked,[=](){
        i=1;
        ui->SetColText->clear();
        ui->SetRowText->clear();
        ui->SetRowSize->setText("Mat "+QString::number(i)+" RowSize");
        ui->SetColSize->setText("Mat "+QString::number(i)+" ColSize");
        QString str=QString::number(MatNum);
        ui->textBrowser->setText("MatNum is "+str);
    });


}
void MainWindow::keyPressEvent(QKeyEvent *ev){
    if(ev->key()==Qt::Key_Return)
    {
            QString strNum=ui->input->text();
            QStringList sl=strNum.split(" ");

            n=(row[j-1])*(col[j-1]);
            for(int m=0;m<col[j-1];m++)
            {
              input[m+inputStates]=sl.at(m).toInt();
            }
            inputStates+=col[j-1];
            ui->input->clear();
            ui->textBrowser->append(strNum);
            if(inputStates==n)
            {
                QMessageBox::information(this,"over","Mat "+QString::number(j)+" has input over");
                j++;
            }
            return;
            this->grabKeyboard();
   }
}
MainWindow::~MainWindow()
{
    delete [] row;
    delete [] col;
    delete [] input;
    delete ui;

}
