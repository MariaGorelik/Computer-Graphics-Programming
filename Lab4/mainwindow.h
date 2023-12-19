
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_radioButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_4_valueChanged(int arg1);

    void on_radioButton_2_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QButtonGroup *group;
    QPixmap *pix;
    QPainter *painter;
    void paintEvent(QPaintEvent *event);
    void setPixmapSize();
    double scaleX;
    double scaleY;
    double originX;
    double originY;
    void stepByStep();
    void DDA();
    void BresenhamLine();
    void BresenhamCircle();
};

#endif // MAINWINDOW_H
