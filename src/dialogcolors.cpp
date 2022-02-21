#include <QListWidgetItem>
#include <QColorDialog>
#include "dialogcolors.h"
#include "ui_dialogcolors.h"

DialogColors::DialogColors(QList<QColor> colors, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogColors)
{
    ui->setupUi(this);

    for( auto c : colors )
    {
        QListWidgetItem* lwi = new QListWidgetItem();
        lwi->setBackground(c);
        lwi->setSizeHint(QSize(100, 45));
        ui->listWidget->addItem(lwi);
    }
}

DialogColors::~DialogColors()
{
    delete ui;
}

QList<QColor> DialogColors::getColors()
{
    QList<QColor> colors;
    for( int i = 0; i < ui->listWidget->count(); i++ )
    {
        colors.append( ui->listWidget->item(i)->background().color() );
    }
    return colors;
}

void DialogColors::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QColorDialog cd(item->background().color());
    if( cd.exec() == QColorDialog::Accepted )
    {
        item->setBackground(cd.selectedColor());
    }
}

void DialogColors::on_pushButton_clicked()
{
    this->accept();
}
