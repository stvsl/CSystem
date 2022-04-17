#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <QWidget>

namespace Ui
{
    class DataView;
}

class DataView : public QWidget
{
    Q_OBJECT

public:
    explicit DataView(QWidget *parent = nullptr);
    ~DataView();

private slots:
    void on_pushButton_8_clicked();

private:
    Ui::DataView *ui;
    void initTable();
};

#endif // DATAVIEW_H
