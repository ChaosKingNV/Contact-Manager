#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnCreate_clicked();

    void on_btnUpdate_clicked();

    void on_btnDelete_clicked();

    void on_btnSaveContact_clicked();

    void on_btnSaveContactCreate_clicked();

    void on_btnFind_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
