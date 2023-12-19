
#include "mainwindow.h"
#include "ui_mainwindow.h"

double hueToRgb(double p, double q, double t)
{
    if (t < 0)
    {
        t += 1;
    }
    if (t > 1)
    {
        t -= 1;
    }
    if (t < 1./6)
    {
        return p + (q - p) * 6 * t;
    }
    if (t < 0.5)
    {
        return q;
    }
    if (t < 2./3)
    {
        return p + (q - p) * (2./3 - t) * 6;
    }
    return p;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), rgb(0, 0, 0), cmyk(0, 0, 0, 255), hls(0, 0, 0),
    canChangeRgb(true), canChangeCmyk(true), canChangeHls(true)
{
    ui->setupUi(this);
    selectedColor.setRgb(rgb.r, rgb.g, rgb.b);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setAutoFillBackground(true);
    ui->widget->setPalette(pal);
    ui->spinBox->setValue(0);
    ui->spinBox_2->setValue(0);
    ui->spinBox_3->setValue(0);
    ui->spinBox_4->setValue(0);
    ui->spinBox_5->setValue(0);
    ui->spinBox_6->setValue(0);
    ui->spinBox_7->setValue(255);
    ui->horizontalSlider_7->setValue(255);
    ui->spinBox_8->setValue(0);
    ui->spinBox_9->setValue(0);
    ui->spinBox_10->setValue(0);
    ui->widget->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::on_spinBox_valueChanged(int arg1)
{
    rgb.r = arg1;
    selectedColor.setRgb(rgb.r, rgb.g, rgb.b);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider->setValue(arg1);

    cmyk.k = qMin(qMin(255 - rgb.r, 255 - rgb.g), 255 - rgb.b);
    if(cmyk.k == 255)
    {
        cmyk.c = 0;
        cmyk.m = 0;
        cmyk.y = 0;
    }
    else
    {
        cmyk.c = (int)((255 - rgb.r - cmyk.k) / (1. - (cmyk.k / 255.)));
        cmyk.m = (int)((255 - rgb.g - cmyk.k) / (1. - (cmyk.k / 255.)));
        cmyk.y = (int)((255 - rgb.b - cmyk.k) / (1. - (cmyk.k / 255.)));
    }
    ui->spinBox_4->setValue(cmyk.c);
    ui->spinBox_5->setValue(cmyk.m);
    ui->spinBox_6->setValue(cmyk.y);
    ui->spinBox_7->setValue(cmyk.k);

    int cMax = qMax(qMax(rgb.r, rgb.g), rgb.b);
    int cMin = qMax(qMax(rgb.r, rgb.g), rgb.b);
    int delta = cMax - cMin;
    if(delta == 0)
    {
        hls.h = 0;
    }
    else if(cMax == rgb.r)
    {
        double q = (rgb.g - rgb.b) / (double)(delta);
        int roundQ = (int)q;
        if(roundQ > q)
        {
            roundQ -= 6;
        }
        hls.h = 60 * (q - (double)roundQ);
    }
    else if(cMax == rgb.g)
    {
        hls.h = 60 * ((rgb.b - rgb.r) / (double)(delta) + 2);
    }
    else
    {
        hls.h = 60 * ((rgb.r - rgb.g) / (double)(delta) + 4);
    }

    hls.l = (cMax + cMin) / 2;

    if(delta == 0)
    {
        hls.s = 0;
    }
    else
    {
        hls.s = 255 * ((delta / 255.) / (1. - qAbs(2. * hls.l / 255 - 1)));
    }

    ui->spinBox_8->setValue(hls.h);
    ui->spinBox_9->setValue(hls.l);
    ui->spinBox_10->setValue(hls.s);
}


void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    rgb.g = arg1;
    selectedColor.setRgb(rgb.r, rgb.g, rgb.b);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_2->setValue(arg1);
    cmyk.k = qMin(qMin(255 - rgb.r, 255 - rgb.g), 255 - rgb.b);
    if(cmyk.k == 255)
    {
        cmyk.c = 0;
        cmyk.m = 0;
        cmyk.y = 0;
    }
    else
    {
        cmyk.c = (int)((255 - rgb.r - cmyk.k) / (1. - (cmyk.k / 255.)));
        cmyk.m = (int)((255 - rgb.g - cmyk.k) / (1. - (cmyk.k / 255.)));
        cmyk.y = (int)((255 - rgb.b - cmyk.k) / (1. - (cmyk.k / 255.)));
    }
    ui->spinBox_4->setValue(cmyk.c);
    ui->spinBox_5->setValue(cmyk.m);
    ui->spinBox_6->setValue(cmyk.y);
    ui->spinBox_7->setValue(cmyk.k);

    int cMax = qMax(qMax(rgb.r, rgb.g), rgb.b);
    int cMin = qMax(qMax(rgb.r, rgb.g), rgb.b);
    int delta = cMax - cMin;
    if(delta == 0)
    {
        hls.h = 0;
    }
    else if(cMax == rgb.r)
    {
        double q = (rgb.g - rgb.b) / (double)(delta);
        int roundQ = (int)q;
        if(roundQ > q)
        {
            roundQ -= 6;
        }
        hls.h = 60 * (q - (double)roundQ);
    }
    else if(cMax == rgb.g)
    {
        hls.h = 60 * ((rgb.b - rgb.r) / (double)(delta) + 2);
    }
    else
    {
        hls.h = 60 * ((rgb.r - rgb.g) / (double)(delta) + 4);
    }

    hls.l = (cMax + cMin) / 2;

    if(delta == 0)
    {
        hls.s = 0;
    }
    else
    {
        hls.s = 255 * ((delta / 255.) / (1. - qAbs(2. * hls.l / 255 - 1)));
    }

    ui->spinBox_8->setValue(hls.h);
    ui->spinBox_9->setValue(hls.l);
    ui->spinBox_10->setValue(hls.s);
}


void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    rgb.b = arg1;
    selectedColor.setRgb(rgb.r, rgb.g, rgb.b);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_3->setValue(arg1);
    cmyk.k = qMin(qMin(255 - rgb.r, 255 - rgb.g), 255 - rgb.b);
    if(cmyk.k == 255)
    {
        cmyk.c = 0;
        cmyk.m = 0;
        cmyk.y = 0;
    }
    else
    {
        cmyk.c = (int)((255 - rgb.r - cmyk.k) / (1. - (cmyk.k / 255.)));
        cmyk.m = (int)((255 - rgb.g - cmyk.k) / (1. - (cmyk.k / 255.)));
        cmyk.y = (int)((255 - rgb.b - cmyk.k) / (1. - (cmyk.k / 255.)));
    }
    ui->spinBox_4->setValue(cmyk.c);
    ui->spinBox_5->setValue(cmyk.m);
    ui->spinBox_6->setValue(cmyk.y);
    ui->spinBox_7->setValue(cmyk.k);

    int cMax = qMax(qMax(rgb.r, rgb.g), rgb.b);
    int cMin = qMax(qMax(rgb.r, rgb.g), rgb.b);
    int delta = cMax - cMin;
    if(delta == 0)
    {
        hls.h = 0;
    }
    else if(cMax == rgb.r)
    {
        double q = (rgb.g - rgb.b) / (double)(delta);
        int roundQ = (int)q;
        if(roundQ > q)
        {
            roundQ -= 6;
        }
        hls.h = 60 * (q - (double)roundQ);
    }
    else if(cMax == rgb.g)
    {
        hls.h = 60 * ((rgb.b - rgb.r) / (double)(delta) + 2);
    }
    else
    {
        hls.h = 60 * ((rgb.r - rgb.g) / (double)(delta) + 4);
    }

    hls.l = (cMax + cMin) / 2;

    if(delta == 0)
    {
        hls.s = 0;
    }
    else
    {
        hls.s = 255 * ((delta / 255.) / (1. - qAbs(2. * hls.l / 255 - 1)));
    }

    ui->spinBox_8->setValue(hls.h);
    ui->spinBox_9->setValue(hls.l);
    ui->spinBox_10->setValue(hls.s);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    rgb.r = value;
    ui->spinBox->setValue(value);
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    rgb.g = value;
    ui->spinBox_2->setValue(value);
}


void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    rgb.b = value;
    ui->spinBox_3->setValue(value);
}

//cmyk


void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    cmyk.c = arg1;
    selectedColor.setCmyk(cmyk.c, cmyk.m, cmyk.y, cmyk.k);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_4->setValue(arg1);
    rgb.r = (int)((255 - cmyk.c) * (1. - (cmyk.k / 255.)));
    rgb.g = (int)((255 - cmyk.m) * (1. - (cmyk.k / 255.)));
    rgb.b = (int)((255 - cmyk.y) * (1. - (cmyk.k / 255.)));
    ui->spinBox->setValue(rgb.r);
    ui->spinBox_2->setValue(rgb.g);
    ui->spinBox_3->setValue(rgb.b);
}


void MainWindow::on_spinBox_5_valueChanged(int arg1)
{
    cmyk.m = arg1;
    selectedColor.setCmyk(cmyk.c, cmyk.m, cmyk.y, cmyk.k);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_5->setValue(arg1);
    rgb.r = (int)((255 - cmyk.c) * (1. - (cmyk.k / 255.)));
    rgb.g = (int)((255 - cmyk.m) * (1. - (cmyk.k / 255.)));
    rgb.b = (int)((255 - cmyk.y) * (1. - (cmyk.k / 255.)));
    ui->spinBox->setValue(rgb.r);
    ui->spinBox_2->setValue(rgb.g);
    ui->spinBox_3->setValue(rgb.b);
}


void MainWindow::on_spinBox_6_valueChanged(int arg1)
{
    cmyk.y = arg1;
    selectedColor.setCmyk(cmyk.c, cmyk.m, cmyk.y, cmyk.k);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_6->setValue(arg1);
    rgb.r = (int)((255 - cmyk.c) * (1. - (cmyk.k / 255.)));
    rgb.g = (int)((255 - cmyk.m) * (1. - (cmyk.k / 255.)));
    rgb.b = (int)((255 - cmyk.y) * (1. - (cmyk.k / 255.)));
    ui->spinBox->setValue(rgb.r);
    ui->spinBox_2->setValue(rgb.g);
    ui->spinBox_3->setValue(rgb.b);
}


void MainWindow::on_spinBox_7_valueChanged(int arg1)
{
    cmyk.k = arg1;
    selectedColor.setCmyk(cmyk.c, cmyk.m, cmyk.y, cmyk.k);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_7->setValue(arg1);
    rgb.r = (int)((255 - cmyk.c) * (1. - (cmyk.k / 255.)));
    rgb.g = (int)((255 - cmyk.m) * (1. - (cmyk.k / 255.)));
    rgb.b = (int)((255 - cmyk.y) * (1. - (cmyk.k / 255.)));
    ui->spinBox->setValue(rgb.r);
    ui->spinBox_2->setValue(rgb.g);
    ui->spinBox_3->setValue(rgb.b);
}


void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    cmyk.c = value;
    ui->spinBox_4->setValue(value);
}


void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    cmyk.m = value;
    ui->spinBox_5->setValue(value);
}


void MainWindow::on_horizontalSlider_6_valueChanged(int value)
{
    cmyk.y = value;
    ui->spinBox_6->setValue(value);
}


void MainWindow::on_horizontalSlider_7_valueChanged(int value)
{
    cmyk.k = value;
    ui->spinBox_7->setValue(value);
}


void MainWindow::on_spinBox_8_valueChanged(int arg1)
{
    hls.h = arg1;
    selectedColor.setHsl(hls.h, hls.s, hls.l);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_8->setValue(arg1);

    double c = (1. - qAbs(2 * hls.l / 255. - 1)) * hls.s;
    double x = c * (1 - qAbs((hls.h / 60) % 2 - 1));
    double m = hls.l - c / 2;
    double r, g, b;

    if(hls.h < 60)
    {
        r = c;
        g = x;
        b = 0;
    }
    else if(hls.h < 120)
    {
        r = x;
        g = c;
        b = 0;
    }
    else if(hls.h < 180)
    {
        r = 0;
        g = c;
        b = x;
    }
    else if(hls.h < 240)
    {
        r = 0;
        g = x;
        b = c;
    }
    else if(hls.h < 300)
    {
        r = x;
        g = 0;
        b = c;
    }
    else
    {
        r = c;
        g = 0;
        b = x;
    }

    rgb.r = 255 * (r + m);
    rgb.g = 255 * (g + m);
    rgb.b = 255 * (b + m);

    ui->spinBox->setValue(rgb.r);
    ui->spinBox_2->setValue(rgb.g);
    ui->spinBox_3->setValue(rgb.b);
}


void MainWindow::on_spinBox_9_valueChanged(int arg1)
{
    hls.l = arg1;
    selectedColor.setHsl(hls.h, hls.s, hls.l);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_9->setValue(arg1);

    double c = (1. - qAbs(2 * hls.l / 255. - 1)) * hls.s;
    double x = c * (1 - qAbs((hls.h / 60) % 2 - 1));
    double m = hls.l - c / 2;
    double r, g, b;

    if(hls.h < 60)
    {
        r = c;
        g = x;
        b = 0;
    }
    else if(hls.h < 120)
    {
        r = x;
        g = c;
        b = 0;
    }
    else if(hls.h < 180)
    {
        r = 0;
        g = c;
        b = x;
    }
    else if(hls.h < 240)
    {
        r = 0;
        g = x;
        b = c;
    }
    else if(hls.h < 300)
    {
        r = x;
        g = 0;
        b = c;
    }
    else
    {
        r = c;
        g = 0;
        b = x;
    }

    rgb.r = 255 * (r + m);
    rgb.g = 255 * (g + m);
    rgb.b = 255 * (b + m);

    ui->spinBox->setValue(rgb.r);
    ui->spinBox_2->setValue(rgb.g);
    ui->spinBox_3->setValue(rgb.b);
}


void MainWindow::on_spinBox_10_valueChanged(int arg1)
{
    hls.s = arg1;
    selectedColor.setHsl(hls.h, hls.s, hls.l);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_10->setValue(arg1);

    double c = (1. - qAbs(2 * hls.l / 255. - 1)) * hls.s;
    double x = c * (1 - qAbs((hls.h / 60) % 2 - 1));
    double m = hls.l - c / 2;
    double r, g, b;

    if(hls.h < 60)
    {
        r = c;
        g = x;
        b = 0;
    }
    else if(hls.h < 120)
    {
        r = x;
        g = c;
        b = 0;
    }
    else if(hls.h < 180)
    {
        r = 0;
        g = c;
        b = x;
    }
    else if(hls.h < 240)
    {
        r = 0;
        g = x;
        b = c;
    }
    else if(hls.h < 300)
    {
        r = x;
        g = 0;
        b = c;
    }
    else
    {
        r = c;
        g = 0;
        b = x;
    }

    rgb.r = 255 * (r + m);
    rgb.g = 255 * (g + m);
    rgb.b = 255 * (b + m);

    ui->spinBox->setValue(rgb.r);
    ui->spinBox_2->setValue(rgb.g);
    ui->spinBox_3->setValue(rgb.b);
}


void MainWindow::on_horizontalSlider_8_valueChanged(int value)
{
    hls.h = value;
    ui->spinBox_8->setValue(value);
}


void MainWindow::on_horizontalSlider_9_valueChanged(int value)
{
    hls.l = value;
    ui->spinBox_9->setValue(value);
}


void MainWindow::on_horizontalSlider_10_valueChanged(int value)
{
    hls.s = value;
    ui->spinBox_10->setValue(value);
}*/


void MainWindow::on_pushButton_clicked()
{
    QColor col = QColorDialog::getColor();
    if(col.isValid())
    {
        selectedColor = col;
        rgb.r = selectedColor.red();
        rgb.g = selectedColor.green();
        rgb.b = selectedColor.blue();
        ui->spinBox->setValue(rgb.r);
        ui->horizontalSlider->setValue(rgb.r);
        ui->spinBox_2->setValue(rgb.g);
        ui->horizontalSlider_2->setValue(rgb.g);
        ui->spinBox_3->setValue(rgb.b);
        ui->horizontalSlider_3->setValue(rgb.b);

        rgbToCmyk();
        rgbToHls();
    }
}

//methods

void MainWindow::rgbToCmyk()
{
    cmyk.k = qMin(qMin(255 - rgb.r, 255 - rgb.g), 255 - rgb.b);
    if(cmyk.k == 255)
    {
        cmyk.c = 0;
        cmyk.m = 0;
        cmyk.y = 0;
    }
    else
    {
        cmyk.c = (int)((255 - rgb.r - cmyk.k) / (1. - (cmyk.k / 255.)));
        cmyk.m = (int)((255 - rgb.g - cmyk.k) / (1. - (cmyk.k / 255.)));
        cmyk.y = (int)((255 - rgb.b - cmyk.k) / (1. - (cmyk.k / 255.)));
    }
    ui->spinBox_4->setValue(cmyk.c);
    ui->horizontalSlider_4->setValue(cmyk.c);
    ui->spinBox_5->setValue(cmyk.m);
    ui->horizontalSlider_5->setValue(cmyk.m);
    ui->spinBox_6->setValue(cmyk.y);
    ui->horizontalSlider_6->setValue(cmyk.y);
    ui->spinBox_7->setValue(cmyk.k);
    ui->horizontalSlider_7->setValue(cmyk.k);

    selectedColor.setRgb(rgb.r, rgb.g, rgb.b);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
}

void MainWindow::cmykToRgb()
{
    rgb.r = (int)((255 - cmyk.c) * (1. - (cmyk.k / 255.)));
    rgb.g = (int)((255 - cmyk.m) * (1. - (cmyk.k / 255.)));
    rgb.b = (int)((255 - cmyk.y) * (1. - (cmyk.k / 255.)));

    ui->spinBox->setValue(rgb.r);
    ui->horizontalSlider->setValue(rgb.r);
    ui->spinBox_2->setValue(rgb.g);
    ui->horizontalSlider_2->setValue(rgb.g);
    ui->spinBox_3->setValue(rgb.b);
    ui->horizontalSlider_3->setValue(rgb.b);

    selectedColor.setRgb(rgb.r, rgb.g, rgb.b);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
}

void MainWindow::rgbToHls()
{
    /*double r = rgb.r / 255.;
    int cMax = qMax(qMax(rgb.r, rgb.g), rgb.b);
    int cMin = qMax(qMax(rgb.r, rgb.g), rgb.b);
    int delta = cMax - cMin;
    if(delta == 0)
    {
        hls.h = 0;
    }
    else if(cMax == rgb.r)
    {
        double q = (rgb.g - rgb.b) / (double)(delta);
        int roundQ = (int)q;
        if(roundQ > q)
        {
            roundQ -= 6;
        }
        hls.h = 60 * (q - (double)roundQ);
    }
    else if(cMax == rgb.g)
    {
        hls.h = 60 * ((rgb.b - rgb.r) / (double)(delta) + 2);
    }
    else
    {
        hls.h = 60 * ((rgb.r - rgb.g) / (double)(delta) + 4);
    }

    hls.l = (cMax + cMin) / 2;

    if(delta == 0)
    {
        hls.s = 0;
    }
    else
    {
        hls.s = 255 * ((delta / 255.) / (1. - qAbs(2. * hls.l / 255 - 1)));
    }*/

    ///

    double r, g, b;
    r = (double)rgb.r / 255;
    g = (double)rgb.g / 255;
    b = (double)rgb.b / 255;
    const double vmax = qMax(qMax(r, g), b);
    const double vmin = qMin(qMax(r, g), b);
    double h = (vmax + vmin) / 2;
    double s = (vmax + vmin) / 2;
    double l = (vmax + vmin) / 2;

    if (vmax - vmin < 0.01)
    {
        hls.h = 0;
        hls.s = 0;
        hls.l = (int)(l * 255);
    }
    else
    {
        const double d = vmax - vmin;
        s = l > 0.5 ? d / (2 - vmax - vmin) : d / (vmax + vmin);
        if (vmax - r < 0.01)
        {
            h = (g - b) / d + (g < b ? 6 : 0);
        }
        if (vmax - g < 0.01)
        {
            h = (b - r) / d + 2;
        }
        if (vmax - b < 0.01)
        {
            h = (r - g) / d + 4;
        }
        h /= 6;
        hls.h = (int)(h * 359);
        hls.l = (int)(l * 255);
        hls.s = (int)(s * 255);
    }



    ui->spinBox_8->setValue(hls.h);
    ui->horizontalSlider_8->setValue(hls.h);
    ui->spinBox_9->setValue(hls.l);
    ui->horizontalSlider_9->setValue(hls.l);
    ui->spinBox_10->setValue(hls.s);
    ui->horizontalSlider_10->setValue(hls.s);

    selectedColor.setRgb(rgb.r, rgb.g, rgb.b);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
}

void MainWindow::hlsToRgb()
{
    /*double c = (1. - qAbs(2 * hls.l / 255. - 1)) * hls.s;
    double x = c * (1 - qAbs((hls.h / 60) % 2 - 1));
    double m = hls.l - c / 2;
    double r, g, b;

    if(hls.h < 60)
    {
        r = c;
        g = x;
        b = 0;
    }
    else if(hls.h < 120)
    {
        r = x;
        g = c;
        b = 0;
    }
    else if(hls.h < 180)
    {
        r = 0;
        g = c;
        b = x;
    }
    else if(hls.h < 240)
    {
        r = 0;
        g = x;
        b = c;
    }
    else if(hls.h < 300)
    {
        r = x;
        g = 0;
        b = c;
    }
    else
    {
        r = c;
        g = 0;
        b = x;
    }

    rgb.r = 255 * (r + m);
    rgb.g = 255 * (g + m);
    rgb.b = 255 * (b + m);*/

    if (hls.s == 0)
    {
        rgb.r = hls.l;
        rgb.g = hls.l;
        rgb.b = hls.l;
    }
    else
    {

        double h = (double)hls.h / 360.; //???
        double l = hls.l / 255.;
        double s = hls.s / 255.;
        const double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        const double p = 2 * l - q;
        double r = hueToRgb(p, q, h + 1./3);
        double g = hueToRgb(p, q, h);
        double b = hueToRgb(p, q, h - 1./3);
        rgb.r = (int)(r * 255);
        rgb.g = (int)(g * 255);
        rgb.b = (int)(b * 255);
    }


    ui->spinBox->setValue(rgb.r);
    ui->horizontalSlider->setValue(rgb.r);
    ui->spinBox_2->setValue(rgb.g);
    ui->horizontalSlider_2->setValue(rgb.g);
    ui->spinBox_3->setValue(rgb.b);
    ui->horizontalSlider_3->setValue(rgb.b);

    selectedColor.setRgb(rgb.r, rgb.g, rgb.b);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
}

////////////


void MainWindow::on_spinBox_editingFinished()
{
    rgb.r = ui->spinBox->value();
    selectedColor.setRgb(rgb.r, rgb.g, rgb.b);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider->setValue(ui->spinBox->value());

    rgbToCmyk();
    rgbToHls();
}


void MainWindow::on_spinBox_2_editingFinished()
{
    rgb.g = ui->spinBox_2->value();
    selectedColor.setRgb(rgb.r, rgb.g, rgb.b);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_2->setValue(ui->spinBox_2->value());

    rgbToCmyk();
    rgbToHls();
}


void MainWindow::on_spinBox_3_editingFinished()
{
    rgb.b = ui->spinBox_3->value();
    selectedColor.setRgb(rgb.r, rgb.g, rgb.b);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_3->setValue(ui->spinBox_3->value());

    rgbToCmyk();
    rgbToHls();
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    rgb.r = ui->horizontalSlider->value();
    ui->spinBox->setValue(rgb.r);

    rgbToCmyk();
    rgbToHls();
}


void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    rgb.g = ui->horizontalSlider_2->value();
    ui->spinBox_2->setValue(rgb.g);

    rgbToCmyk();
    rgbToHls();
}


void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
{
    rgb.b = ui->horizontalSlider_3->value();
    ui->spinBox_3->setValue(rgb.b);

    rgbToCmyk();
    rgbToHls();
}


void MainWindow::on_spinBox_4_editingFinished()
{
    cmyk.c = ui->spinBox_4->value();
    selectedColor.setCmyk(cmyk.c, cmyk.m, cmyk.y, cmyk.k);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_4->setValue(cmyk.c);

    cmykToRgb();
    rgbToHls();
}


void MainWindow::on_spinBox_5_editingFinished()
{
    cmyk.m = ui->spinBox_5->value();
    selectedColor.setCmyk(cmyk.c, cmyk.m, cmyk.y, cmyk.k);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_5->setValue(cmyk.m);

    cmykToRgb();
    rgbToHls();
}


void MainWindow::on_spinBox_6_editingFinished()
{
    cmyk.y = ui->spinBox_6->value();
    selectedColor.setCmyk(cmyk.c, cmyk.m, cmyk.y, cmyk.k);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_6->setValue(cmyk.y);

    cmykToRgb();
    rgbToHls();
}


void MainWindow::on_spinBox_7_editingFinished()
{
    cmyk.k = ui->spinBox_7->value();
    selectedColor.setCmyk(cmyk.c, cmyk.m, cmyk.y, cmyk.k);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_7->setValue(cmyk.k);

    cmykToRgb();
    rgbToHls();
}


void MainWindow::on_horizontalSlider_4_sliderMoved(int position)
{
    cmyk.c = ui->horizontalSlider_4->value();
    ui->spinBox_4->setValue(cmyk.c);

    cmykToRgb();
    rgbToHls();
}


void MainWindow::on_horizontalSlider_5_sliderMoved(int position)
{
    cmyk.m = ui->horizontalSlider_5->value();
    ui->spinBox_5->setValue(cmyk.m);

    cmykToRgb();
    rgbToHls();
}


void MainWindow::on_horizontalSlider_6_sliderMoved(int position)
{
    cmyk.y = ui->horizontalSlider_6->value();
    ui->spinBox_6->setValue(cmyk.y);

    cmykToRgb();
    rgbToHls();
}


void MainWindow::on_horizontalSlider_7_sliderMoved(int position)
{
    cmyk.k = ui->horizontalSlider_7->value();
    ui->spinBox_7->setValue(cmyk.k);

    cmykToRgb();
    rgbToHls();
}


void MainWindow::on_spinBox_8_editingFinished()
{
    hls.h = ui->spinBox_8->value();
    selectedColor.setHsl(hls.h, hls.s, hls.l);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_8->setValue(hls.h);

    hlsToRgb();
    rgbToCmyk();
}


void MainWindow::on_spinBox_9_editingFinished()
{
    hls.l = ui->spinBox_9->value();
    selectedColor.setHsl(hls.h, hls.s, hls.l);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_9->setValue(hls.l);

    hlsToRgb();
    rgbToCmyk();
}


void MainWindow::on_spinBox_10_editingFinished()
{
    hls.s = ui->spinBox_10->value();
    selectedColor.setHsl(hls.h, hls.s, hls.l);
    pal.setColor(QPalette::Background, selectedColor);
    ui->widget->setPalette(pal);
    ui->horizontalSlider_10->setValue(hls.s);

    hlsToRgb();
    rgbToCmyk();
}


void MainWindow::on_horizontalSlider_8_sliderMoved(int position)
{
    hls.h = ui->horizontalSlider_8->value();
    ui->spinBox_8->setValue(hls.h);

    hlsToRgb();
    rgbToCmyk();
}


void MainWindow::on_horizontalSlider_9_sliderMoved(int position)
{
    hls.l = ui->horizontalSlider_9->value();
    ui->spinBox_9->setValue(hls.l);

    hlsToRgb();
    rgbToCmyk();
}


void MainWindow::on_horizontalSlider_10_sliderMoved(int position)
{
    hls.s = ui->horizontalSlider_10->value();
    ui->spinBox_10->setValue(hls.s);

    hlsToRgb();
    rgbToCmyk();
}

