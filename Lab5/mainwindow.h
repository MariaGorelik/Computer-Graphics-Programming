
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QFile>
#include <QTextStream>

struct Segment
{
    int x1;
    int y1;
    int x2;
    int y2;
};

struct MyRectangle
{
    int xMin;
    int xMax;
    int yMin;
    int yMax;
};

enum Status
{
    notSelected,
    MP,
    KB
};

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap *pix;
    QPainter *painter;
    Segment seg;
    MyRectangle rec;
    QVector<QPoint> pol; // polygon for Cyrus-Beck
    int maxX; // для масштаба
    int minX;
    int maxY;
    int minY;
    double scaleX;
    double scaleY;
    int originX;
    int originY;
    int code(double x, double y);
    Status status;
    void midpointAlgorithm(double x1, double y1, double x2, double y2);
    void CyrusBeckAlgorithm();
    void paintEvent(QPaintEvent *event);
    void drawSegment(double x1, double y1, double x2, double y2);
};

#endif // MAINWINDOW_H
