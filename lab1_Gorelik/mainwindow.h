
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QColor>
#include <QPalette>
#include <QColorDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Rgb
{
    int r;
    int g;
    int b;
    Rgb(int R, int G, int B): r(R), g(G), b(B) {}
};

struct Cmyk
{
    int c;
    int m;
    int y;
    int k;
    Cmyk(int C, int M, int Y, int K): c(C), m(M), y(Y), k(K) {}
};

struct Hls
{
    int h;
    int l;
    int s;
    Hls(int H, int L, int S): h(H), l(L), s(S) {}
};

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    /*void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_spinBox_4_valueChanged(int arg1);

    void on_spinBox_5_valueChanged(int arg1);

    void on_spinBox_6_valueChanged(int arg1);

    void on_spinBox_7_valueChanged(int arg1);

    void on_horizontalSlider_4_valueChanged(int value);

    void on_horizontalSlider_5_valueChanged(int value);

    void on_horizontalSlider_6_valueChanged(int value);

    void on_horizontalSlider_7_valueChanged(int value);



    void on_spinBox_8_valueChanged(int arg1);

    void on_spinBox_9_valueChanged(int arg1);

    void on_spinBox_10_valueChanged(int arg1);

    void on_horizontalSlider_8_valueChanged(int value);

    void on_horizontalSlider_9_valueChanged(int value);

    void on_horizontalSlider_10_valueChanged(int value);*/

    void on_pushButton_clicked();

    void on_spinBox_editingFinished();

    void on_spinBox_2_editingFinished();

    void on_spinBox_3_editingFinished();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_horizontalSlider_3_sliderMoved(int position);

    void on_spinBox_4_editingFinished();

    void on_spinBox_5_editingFinished();

    void on_spinBox_6_editingFinished();

    void on_spinBox_7_editingFinished();

    void on_horizontalSlider_4_sliderMoved(int position);

    void on_horizontalSlider_5_sliderMoved(int position);

    void on_horizontalSlider_6_sliderMoved(int position);

    void on_horizontalSlider_7_sliderMoved(int position);

    void on_spinBox_8_editingFinished();

    void on_spinBox_9_editingFinished();

    void on_spinBox_10_editingFinished();

    void on_horizontalSlider_8_sliderMoved(int position);

    void on_horizontalSlider_9_sliderMoved(int position);

    void on_horizontalSlider_10_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QColor selectedColor;
    QPalette pal;
    Rgb rgb;
    Cmyk cmyk;
    Hls hls;

    void rgbToCmyk();
    void cmykToRgb();
    void rgbToHls();
    void hlsToRgb();

    bool canChangeRgb;
    bool canChangeCmyk;
    bool canChangeHls;
};

#endif // MAINWINDOW_H
