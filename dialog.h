#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void showDialog(const QString &message);

private slots:
    void onOKButtonClicked();

private:
    Ui::Dialog *ui;
};

#endif
