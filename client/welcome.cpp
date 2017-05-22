﻿#include "welcome.h"
#include "mainwindow.h"

#include <QtWidgets>
#include <QSplitter>
#include <QRegularExpressionValidator>
#include "inputbox.h"

Welcome::Welcome(MainWindow *parent)
  : QWidget(parent), mainWin(parent), welcomeWidget(this)
{
  portInputBox = new InputBox(tr("Input the port."), this);
  QRegExp rx("^[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]{1}|6553[0-5]$");
  QRegExpValidator *portValidator = new QRegExpValidator(rx, portInputBox);
  portInputBox->setValidator(portValidator);
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

void Welcome::begin(){
  welcomeWidget->show();
}

void Welcome::clear(){
  welcomeWidget->hide();
}

void Welcome::gotPort(){
  qDebug() << "gotPort";
  mainWin->setPort(portInputBox->text().toInt());
  mainWin->WtoC();
}