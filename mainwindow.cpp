#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/********************选择文件夹函数*********************/
void MainWindow::on_pushButton_5_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("file"),"/",tr("*.mp4"));
    fileNameS = fileName.toStdString();
    ui->label->setText(fileName);
}
/********************鼠标点击事件函数*********************/
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 如果是鼠标左键按下
    if(event->button() == Qt::LeftButton)
    {
        mouseEventL=1;
        this->start=event->pos();
    }
    //如果是鼠标右键按下
    else if(event->button() == Qt::RightButton)
    {
        mouseEventR=1;
        this->end=event->pos();
    }
}
/********************Mat转QImage函数*********************/
QImage MainWindow::cvMat_to_QImage(const cv::Mat &mat )
{
  switch ( mat.type() )
  {
     // 8-bit, 4 channel
     case CV_8UC4:
     {
        QImage image( mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32 );
        return image;
     }

     // 8-bit, 3 channel
     case CV_8UC3:
     {
        QImage image( mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888 );
        return image.rgbSwapped();
     }

     // 8-bit, 1 channel
     case CV_8UC1:
     {
        static QVector<QRgb>  sColorTable;
        // only create our color table once
        if ( sColorTable.isEmpty() )
        {
           for ( int i = 0; i < 256; ++i )
              sColorTable.push_back( qRgb( i, i, i ) );
        }
        QImage image( mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8 );
        image.setColorTable( sColorTable );
        return image;
     }

     default:
        qDebug("Image format is not supported: depth=%d and %d channels\n", mat.depth(), mat.channels());
        break;
  }
  return QImage();
}
/********************开始播放视频函数*********************/
void MainWindow::on_pushButton_clicked()
{
    cap.open(fileNameS);
    while(1)
    {
        cap >> frame;
        if(frame.empty())
        {
            break;
        }
        size.width = frame.cols;
        size.height = frame.rows;
        cv::resize(frame,pic,Size(920,480),0,0,INTER_LINEAR);
        ui->label_2->setPixmap(QPixmap::fromImage(cvMat_to_QImage(pic)));
        frameNow++;
        cv::waitKey(1);
        if(mark==1)
        {
            frameStart = frameNow;
            frameNow = 0;
            mark = 0;
            break;
        }
    }
}
/********************准备标记函数*********************/
void MainWindow::on_pushButton_2_clicked()
{
    mark = 1;
    while(1)
    {
        if(mouseEventL==1)
        {
            top.x = (start.x()-40)*size.width/920;
            top.y = (start.y()-90)*size.height/480;
        }
        if(mouseEventR==1)
        {
            down.x = (end.x()-40)*size.width/920;
            down.y = (end.y()-90)*size.height/480;
            break;
        }
        cv::waitKey(1);
    }

    pic = frame.clone();
    cv::rectangle(pic, Point(top.x, top.y), Point(down.x, down.y), cv::Scalar(0, 0, 255));
    cv::resize(pic,picCut,Size(920,480),0,0,INTER_LINEAR);
    ui->label_2->setPixmap(QPixmap::fromImage(cvMat_to_QImage(picCut)));
}
/********************清理标记函数*********************/
void MainWindow::on_pushButton_4_clicked()
{
        mouseEventL = 0;
        mouseEventR = 0;
        cv::resize(frame,pic,Size(920,480),0,0,INTER_LINEAR);
        ui->label_2->setPixmap(QPixmap::fromImage(cvMat_to_QImage(pic)));
}
/********************准备保存视频函数*********************/
void MainWindow::on_pushButton_3_clicked()
{
    cap.open(fileNameS);
    sprintf(outname,"/home/***/cut.avi");//修改保存路径与名称
    VideoWriter writer(outname, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), cap.get(CAP_PROP_FPS), Size(down.x-top.x,down.y-top.y));
    Rect rect(top.x, top.y, down.x-top.x, down.y-top.y);
    while(1)
    {
        cap >> frame;
        if(frame.empty())
        {
            break;
        }
        frameNow++;
        if(frameNow < frameStart)
        {
            ui->label_2->setText("正在加载");
        }
        else
        {
            picCut = Mat(frame, rect);
            cv::resize(picCut,pic,Size(920,480),0,0,INTER_LINEAR);
            ui->label_2->setPixmap(QPixmap::fromImage(cvMat_to_QImage(pic)));
            writer << picCut;
            if(sign==1)
            {
                break;
            }
        }
        cv::waitKey(1);

    }
}
/********************准备保存视频函数*********************/
void MainWindow::on_pushButton_6_clicked()
{
    sign=1;
    mouseEventL = 0;
    mouseEventR = 0;
}
