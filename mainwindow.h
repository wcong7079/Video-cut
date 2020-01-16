#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QFileDialog>
#include <QLabel>
#include <QMouseEvent>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
struct Coordinate
{
    int x;
    int y;
};
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString fileName;
    String fileNameS;
    Coordinate top;
    Coordinate down;
    int mouseEventL=0;
    int mouseEventR=0;
    //int mouseSign=0;
    int mark=0;
    int frameNow=0;
    int frameStart;
    char outname[100];
    int sign=0;
    Size size;
    VideoCapture cap;
    Mat frame;
    Mat pic;
    Mat picCut;
    QPoint start;
    QPoint end;
    MainWindow(QWidget *parent = nullptr);
    QImage cvMat_to_QImage(const cv::Mat &mat );
    void mousePressEvent(QMouseEvent *event);
    ~MainWindow();
private slots:

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
