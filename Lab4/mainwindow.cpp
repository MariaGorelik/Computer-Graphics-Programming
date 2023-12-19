
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Basic raster algorithms");
    group = new QButtonGroup(this);
    group->addButton(ui->radioButton, 1);
    group->addButton(ui->radioButton_2, 2);
    group->addButton(ui->radioButton_3, 3);
    group->addButton(ui->radioButton_4, 4);
    setPixmapSize();
    painter = new QPainter(pix);
    painter->setRenderHint(QPainter::Antialiasing); // Сглаживание*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPixmapSize()
{
    pix = new QPixmap(631, 631);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    int pixmapWidth = pix->width();
    int pixmapHeight = pix->height();

    pix->fill(Qt::white);

    int selectedId = group->checkedId();

    double maxX;
    double minX;
    double maxY;
    double minY;

    if (selectedId != 4)
    {
        maxX = qMax(qMax(qAbs(ui->spinBox->value()), qAbs(ui->spinBox_2->value())), qMax(qAbs(ui->spinBox_3->value()), qAbs(ui->spinBox_4->value())));
        maxX++;
        minX = -1 * maxX;
        maxY = maxX;
        minY = -1 * maxY;
    }
    else
    {
        maxX = ui->spinBox_2->value() + qMax(qAbs(ui->spinBox->value()) + 1, qAbs(ui->spinBox_3->value()) + 1);
        maxX++;
        minX = -1 * maxX;
        maxY = maxX;
        minY = -1 * maxY;
    }

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
    painter->setPen(QPen(Qt::black, 2)); // Толстая линия для осей
    painter->drawLine(0, originY * scaleY, pixmapWidth, originY * scaleY); // Ось x
    painter->drawLine(originX * scaleX, 0, originX * scaleX, pixmapHeight); // Ось y


    if (selectedId == 1)
    {
        stepByStep();
    }
    else if (selectedId == 2)
    {
        DDA();
    }
    else if (selectedId == 3)
    {
        BresenhamLine();
    }
    else if (selectedId == 4)
    {
        BresenhamCircle();
    }
    ui->label->setPixmap(*pix);
}

void MainWindow::stepByStep()
{
    int x1 = ui->spinBox->value();
    int x2 = ui->spinBox_2->value();
    int y1 = ui->spinBox_3->value();
    int y2 = ui->spinBox_4->value();
    painter->setPen(QPen(Qt::blue, 2));
    if (qAbs(x1 - x2) >= qAbs(y1 - y2))
    {
        if (x1 > x2)
        {
            qSwap(x1, x2);
            qSwap(y1, y2);
        }
        int x_start = x1;
        double y_start = y1;
        int x_end = x1;
        double y_end = y1;
        double k = (y2 - y1) / (double)(x2 - x1);
        while (x_end < x2)
        {
            x_end = x_start + 1;
            y_end = y_start + k;
            painter->drawLine((x_start + originX) * scaleX, pix->height() - (((int)y_start + originY) * scaleY), (x_end + originX) * scaleX, pix->height() - (((int)y_end + originY) * scaleY));
            x_start = x_end;
            y_start = y_end;
        }
    }
    else
    {
        if (y1 > y2)
        {
            qSwap(x1, x2);
            qSwap(y1, y2);
        }
        double x_start = x1;
        int y_start = y1;
        double x_end = x1;
        int y_end = y1;
        double k = (x2 - x1) / (double)(y2 - y1);
        while (y_end < y2)
        {
            y_end = y_start + 1;
            x_end = x_start + k;
            painter->drawLine(((int)x_start + originX) * scaleX, pix->height() - (y_start + originY) * scaleY, ((int)x_end + originX) * scaleX, pix->height() - (y_end+ originY) * scaleY);
            x_start = x_end;
            y_start = y_end;
        }
    }
}

void MainWindow::DDA() // симметричный алгоритм
{
    int x1 = ui->spinBox->value();
    int x2 = ui->spinBox_2->value();
    int y1 = ui->spinBox_3->value();
    int y2 = ui->spinBox_4->value();
    painter->setPen(QPen(Qt::blue, 2));
    int Dx = x2 - x1;
    int Dy = y2 - y1;
    double L = qMax(qAbs(Dx), qAbs(Dy));
    double k1 = Dy / L;
    double k2 = Dx / L;
    double x_start = x1;
    double y_start = y1;
    double x_end = x1;
    double y_end = y1;
    int i = 0;
    while (i < L)
    {
        y_end = y_start + k1;
        x_end = x_start + k2;
        painter->drawLine(((int)x_start + originX) * scaleX, pix->height() - ((int)y_start + originY) * scaleY, ((int)x_end + originX) * scaleX, pix->height() - ((int)y_end + originY) * scaleY);
        x_start = x_end;
        y_start = y_end;
        i++;
    }
}

void MainWindow::BresenhamLine()
{
    int x1 = ui->spinBox->value();
    int x2 = ui->spinBox_2->value();
    int y1 = ui->spinBox_3->value();
    int y2 = ui->spinBox_4->value();
    painter->setPen(QPen(Qt::blue, 2));
    bool steep = qAbs(y2-y1)>qAbs(x2-x1);
    if(steep)
    {
        qSwap(x1,y1);
        qSwap(x2,y2);
    }

    if(x1>x2)
    {
        qSwap(x1,x2);
        qSwap(y1,y2);
    }

    int dx = x2-x1;
    int dy = qAbs(y2-y1);
    int error = dx/2;
    int ystep = (y1<y2) ? 1:-1;
    int y = y1;
    QVector<QPoint> line;
    for(int x = x1; x<= x2; x++)
    {
        line.push_back(steep?QPoint(y,x):QPoint(x,y));
        error -= dy;
        if(error<0)
        {
            y+=ystep;
            error+=dx;
        }
    }
    for (int i = 1; i < line.size(); i++)
    {
        painter->drawLine((line[i - 1].x() + originX) * scaleX, pix->height() - (line[i - 1].y() + originY) * scaleY, (line[i].x() + originX) * scaleX, pix->height() - (line[i].y() + originY) * scaleY);
    }
}

void MainWindow::BresenhamCircle()
{
    painter->setPen(QPen(Qt::blue, 2));
    int x1 = ui->spinBox->value();
    int y1 = ui->spinBox_3->value();
    int r = ui->spinBox_2->value();
    QVector<QVector<QPoint>> points(8);
    int x = 0;
    int y = r;
    int e = 3 - 2 * r;
    points[0].push_back(QPoint(x + x1, y + y1));
    points[1].push_back(QPoint(x + x1, -y + y1));
    points[2].push_back(QPoint(-x + x1, y + y1));
    points[3].push_back(QPoint(-x + x1, -y + y1));
    points[4].push_back(QPoint(y + x1, x + y1));
    points[5].push_back(QPoint(y + x1, -x + y1));
    points[6].push_back(QPoint(-y + x1, x + y1));
    points[7].push_back(QPoint(-y + x1, -x + y1));
    while (x < y)
    {
        if (e >= 0)
        {
            e += (4 * (x - y) + 10);
            x++;
            y--;
        }
        else
        {
            e += 4 * x + 6;
            x++;
        }
        points[0].push_back(QPoint(x + x1, y + y1));
        points[1].push_back(QPoint(x + x1, -y + y1));
        points[2].push_back(QPoint(-x + x1, y + y1));
        points[3].push_back(QPoint(-x + x1, -y + y1));
        points[4].push_back(QPoint(y + x1, x + y1));
        points[5].push_back(QPoint(y + x1, -x + y1));
        points[6].push_back(QPoint(-y + x1, x + y1));
        points[7].push_back(QPoint(-y + x1, -x + y1));
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 1; j < points[i].size(); j++)
        {
            painter->drawLine((points[i][j].x() + originX) * scaleX, pix->height() - (points[i][j].y() + originY) * scaleY, (points[i][j - 1].x() + originX) * scaleX, pix->height() - (points[i][j - 1].y() + originY) * scaleY);
        }
    }
}

void MainWindow::on_radioButton_clicked()
{
    ui->spinBox_4->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setText("x2:");
    ui->spinBox_2->setMinimum(-20);
    ui->spinBox_2->setMaximum(20);
    update();
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    update();
}


void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    update();
}


void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    update();
}


void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    update();
}


void MainWindow::on_radioButton_2_clicked()
{
    ui->spinBox_4->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setText("x2:");
    ui->spinBox_2->setMinimum(-20);
    ui->spinBox_2->setMaximum(20);
    update();
}


void MainWindow::on_radioButton_4_clicked()
{
    ui->spinBox_4->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setText("R:");
    ui->spinBox_2->setMinimum(0);
    ui->spinBox_2->setMaximum(20);
    update();
}


void MainWindow::on_radioButton_3_clicked()
{
    ui->spinBox_4->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setText("x2:");
    ui->spinBox_2->setMinimum(-20);
    ui->spinBox_2->setMaximum(20);
    update();
}

