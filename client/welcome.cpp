﻿/*************************************************
名称：welcome.cpp
作者：叶梓杰 计65 2016011380
时间：2017/05/22
内容：客户端欢迎界面类
版权：完全自行完成
*************************************************/

#include "welcome.h"
#include "mainwindow.h"

#include <QtWidgets>
#include <QSplitter>
#include <QRegularExpressionValidator>
#include "inputbox.h"

Welcome::Welcome(MainWindow *parent)
  : QWidget(parent), mainWin(parent), welcomeWidget(this)
{
  portInputBox = new InputBox(tr("Input the port."), this);
  QPushButton *beginBtn = new QPushButton(tr("Begin"), this);
  connect(portInputBox, &QLineEdit::editingFinished, this, &Welcome::gotPort);
  connect(beginBtn, &QPushButton::clicked, this, &Welcome::gotPort);
  QHBoxLayout *welcomeLayout = new QHBoxLayout(this);
  welcomeLayout->addWidget(portInputBox);
  welcomeLayout->addWidget(beginBtn);
  welcomeWidget->setLayout(welcomeLayout);

  parent->splitter()->addWidget(welcomeWidget);
  welcomeWidget->hide();
}

Welcome::~Welcome(){}

//功能：展示欢迎界面
void Welcome::begin(){
  welcomeWidget->show();
}

//功能：隐藏欢迎界面
void Welcome::clear(){
  welcomeWidget->hide();
}

//功能：从端口输入框读取数据并用正则表达式检查，若不符合要求则弹窗提示
void Welcome::gotPort(){
  qDebug() << "gotPort";
  QRegExp rx("^[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]{1}|6553[0-5]$");
  QRegExpValidator validator(rx, this);
  int pos = 0;
  QString text = portInputBox->text();


  if(validator.validate(text, pos) == QValidator::Acceptable){
    mainWin->setPort(portInputBox->text().toInt());
    mainWin->WtoC();
    }
  else{
      QMessageBox::information(this, tr("Wrong Port"), tr("You've entered a wrong port. Please check."));
    }
}
