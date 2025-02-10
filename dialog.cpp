#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
    // Connect OK button click signal to slot
    connect(ui->pushButtonOK, &QPushButton::clicked, this, &Dialog::onOKButtonClicked);
}
Dialog::~Dialog() {
    delete ui;
}

void Dialog::showDialog(const QString &message) {
    ui->_dialog->setText(message);
    this->setWindowModality(Qt::ApplicationModal);
    this->exec();  // Show the dialog and block until closed
}

void Dialog::onOKButtonClicked() {
    this->accept();  // Close the dialog
}
