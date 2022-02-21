#ifndef DIALOGCOLORS_H
#define DIALOGCOLORS_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class DialogColors;
}

class DialogColors : public QDialog
{
    Q_OBJECT

public:
    explicit DialogColors(QList<QColor> colors, QWidget *parent = nullptr);
    ~DialogColors();

    QList<QColor> getColors();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::DialogColors *ui;
};

#endif // DIALOGCOLORS_H
