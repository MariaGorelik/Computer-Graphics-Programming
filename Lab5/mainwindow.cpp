
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Алгоритмы отсечения отрезков и многоугольников");
    pix = new QPixmap(451, 451);
    painter = new QPainter(pix);
    painter->setRenderHint(QPainter::Antialiasing); // Сглаживание*/
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    status = notSelected;

    maxX = 10;
    minX = -10;
    maxY = 10;
    minY = -10;
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::code(double x, double y)
{
    int c = 0;
    if (y > rec.yMax)
        c += 8;
    if (x > rec.xMax)
        c += 4;
    if (y < rec.yMin)
        c += 2;
    if (x < rec.xMin)
        c += 1;
    return c;
}

void MainWindow::midpointAlgorithm(double x1, double y1, double x2, double y2)
{
    int code1 = code(x1, y1); // коды как в алгоритме Сазерленда-Коэна
    int code2 = code(x2, y2);
    if ((code1 & code2) != 0) // вне
        return;
    if (code1 == 0 && code2 == 0)
        drawSegment(x1, y1, x2, y2);
    if (qAbs(y1 - y2) > 1 || qAbs(x1 - x2) > 1)
    {
        midpointAlgorithm(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2);
        midpointAlgorithm((x1 + x2) / 2, (y1 + y2) / 2, x2, y2);
    }
}

void MainWindow::CyrusBeckAlgorithm()
{
    double t_start = 0;
    double t_end = 1;
    for (int i = 0; i < pol.size() - 1; i++)
    {
        int v1 = (pol[i + 1].x() - pol[i].x()) * (seg.y2 - seg.y1) - (pol[i + 1].y() - pol[i].y()) * (seg.x2 - seg.x1);
        int v2 = (pol[i + 1].x() - pol[i].x()) * (seg.y1 - pol[i].y()) - (pol[i + 1].y() - pol[i].y()) * (seg.x1 - pol[i].x());
        if (v1 == 0 && v2 < 0)
        {
            return;
        }
        if (v1 > 0)
        {
            double t = -1 * v2 / (double)v1;
            if (t > t_start)
            {
                t_start = t;
            }
        }
        if (v1 < 0)
        {
            double t = -1 * v2 / (double)v1;
            if (t < t_end)
            {
                t_end = t;
            }
        }
        if (t_end < t_start)
        {
            return;
        }
    }
    double x_start = seg.x1 + (seg.x2 - seg.x1) * t_start;
    double x_end = seg.x1 + (seg.x2 - seg.x1) * t_end;
    double y_start = seg.y1 + (seg.y2 - seg.y1) * t_start;
    double y_end = seg.y1 + (seg.y2 - seg.y1) * t_end;
    drawSegment(x_start, y_start, x_end, y_end);
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    int pixmapWidth = pix->width();
    int pixmapHeight = pix->height();

    pix->fill(Qt::white);

    // Определение размеров системы координат
    double coordinateWidth = maxX - minX;
    double coordinateHeight = maxY - minY;

    // Определение масштаба для преобразования координат в пиксели
    scaleX = pixmapWidth / coordinateWidth;
    scaleY = pixmapHeight / coordinateHeight;

    // Перемещение начала координат в середину pixmap
    originX = -minX;
    originY = -minY;

    // Нарисовать сетку и деления на осях
    painter->setPen(QPen(Qt::lightGray, 1));
    painter->setFont(QFont("Arial", 8));

    // Расстояние между делениями на осях
    double tickSpacing = 1.0;

    // Нарисовать вертикальные линии сетки и цифры на осях x
    for (double x = originX + tickSpacing; x < coordinateWidth; x += tickSpacing) {
    int pixelX = x * scaleX;
    painter->drawLine(pixelX, 0, pixelX, pixmapHeight);
    }
    for (double x = originX - tickSpacing; x > 0; x -= tickSpacing) {
    int pixelX = x * scaleX;
    painter->drawLine(pixelX, 0, pixelX, pixmapHeight);
    }

    // Нарисовать горизонтальные линии сетки и цифры на осях y
    for (double y = originY + tickSpacing; y < coordinateHeight; y += tickSpacing) {
    int pixelY = y * scaleY;
    painter->drawLine(0, pixelY, pixmapWidth, pixelY);
    }
    for (double y = originY - tickSpacing; y > 0; y -= tickSpacing) {
    int pixelY = y * scaleY;
    painter->drawLine(0, pixelY, pixmapWidth, pixelY);
    }

    painter->setPen(Qt::black);

    for (double y = originY + tickSpacing; y < coordinateHeight; y += tickSpacing) {
    int pixelY = y * scaleY;
    painter->drawText(originX * scaleX + 5, pixelY + 5, QString::number(-1 * y + maxY));
    }
    for (double y = originY - tickSpacing; y > 0; y -= tickSpacing) {
    int pixelY = y * scaleY;
    painter->drawText(originX * scaleX + 5, pixelY + 5, QString::number(-1 * y + maxY));
    }

    for (double x = originX + tickSpacing; x < coordinateWidth; x += tickSpacing) {
    int pixelX = x * scaleX;
    painter->drawText(pixelX - 5, originY * scaleY + 15, QString::number(x - maxX));
    }
    for (double x = originX - tickSpacing; x > 0; x -= tickSpacing) {
    int pixelX = x * scaleX;
    painter->drawText(pixelX - 5, originY * scaleY + 15, QString::number(x - maxX));
    }

    // Нарисовать оси x и y
    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(0, originY * scaleY, pixmapWidth, originY * scaleY); // Ось x
    painter->drawLine(originX * scaleX, 0, originX * scaleX, pixmapHeight); // Ось y

    if (status == MP)
    {
        painter->setPen(QPen(Qt::red, 3));
        drawSegment(rec.xMin, rec.yMin, rec.xMin, rec.yMax);
        drawSegment(rec.xMin, rec.yMax, rec.xMax, rec.yMax);
        drawSegment(rec.xMax, rec.yMax, rec.xMax, rec.yMin);
        drawSegment(rec.xMax, rec.yMin, rec.xMin, rec.yMin);
        painter->setPen(QPen(Qt::black, 2));
        drawSegment(seg.x1, seg.y1, seg.x2, seg.y2);
        painter->setPen(QPen(Qt::blue, 3));
        midpointAlgorithm(seg.x1, seg.y1, seg.x2, seg.y2);
    }
    else if (status == KB)
    {
        painter->setPen(QPen(Qt::black, 2));
        drawSegment(seg.x1, seg.y1, seg.x2, seg.y2);
        painter->setPen(QPen(Qt::red, 3));
        for (int i = 0; i < pol.size() - 1; i++)
        {
            drawSegment(pol[i].x(), pol[i].y(), pol[i + 1].x(), pol[i + 1].y());
        }
        drawSegment(pol[0].x(), pol[0].y(), pol[pol.size() - 1].x(), pol[pol.size() - 1].y());
        painter->setPen(QPen(Qt::blue, 3));
        CyrusBeckAlgorithm();
    }

    ui->label->setPixmap(*pix);
}

void MainWindow::drawSegment(double x1, double y1, double x2, double y2)
{
    painter->drawLine((x1 + originX) * scaleX, pix->height() - ((y1 + originY) * scaleY), (x2 + originX) * scaleX, pix->height() - ((y2 + originY) * scaleY));
}

void MainWindow::on_pushButton_clicked()
{
    status = MP;
    QFile file(":resource/midpointAlgorithm.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;
        in >> seg.x1;
        in >> seg.y1;
        in >> seg.x2;
        in >> seg.y2;
        in >> rec.xMin;
        in >> rec.yMin;
        in >> rec.xMax;
        in >> rec.yMax;
        file.close();
        maxX = qMax(qAbs(seg.x1), qAbs(seg.y1));
        maxX = qMax(maxX, qAbs(seg.x2));
        maxX = qMax(maxX, qAbs(seg.y2));
        maxX = qMax(maxX, qAbs(rec.xMin));
        maxX = qMax(maxX, qAbs(rec.yMin));
        maxX = qMax(maxX, qAbs(rec.xMax));
        maxX = qMax(maxX, qAbs(rec.yMax));
        maxX++;
        minX = -maxX;
        maxY = maxX;
        minY = minX;
    }
    update();
}


void MainWindow::on_pushButton_2_clicked()
{
    status = KB;
    QFile file(":resource/CyrusBeckAlgorithm.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;
        in >> seg.x1;
        in >> seg.y1;
        in >> seg.x2;
        in >> seg.y2;
        int n;
        in >> n;
        pol.resize(n);
        for (int i = 0; i < n; i++)
        {
            int x, y;
            in >> x >> y;
            pol[i] = QPoint(x, y);
        }
        file.close();
        maxX = qMax(qAbs(seg.x1), qAbs(seg.y1));
        maxX = qMax(maxX, qAbs(seg.x2));
        maxX = qMax(maxX, qAbs(seg.y2));
        for (int i = 0; i < n; i++)
        {
            int m = qMax(qAbs(pol[i].x()), qAbs(pol[i].y()));
            maxX = qMax(maxX, m);
        }
        maxX++;
        minX = -maxX;
        maxY = maxX;
        minY = minX;
    }
    update();
}

