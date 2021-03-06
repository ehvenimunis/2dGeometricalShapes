#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>
#include <math.h>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor (0, 0, 250),
    mShapeColor (255, 255, 255),
    mShape(Astroid) // default
{
    on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(400, 400);
}

QSize RenderArea::sizeHint()  const
{
    return QSize(400, 400);
}

void RenderArea::on_shape_changed(){
    switch (mShape){
    case Astroid:
        mScale = 40;
        mIntervalLenght = 2 * M_PI;
        mStepCount = 256;
        break;
    case Cycloid:
        mScale = 4;
        mIntervalLenght = 6 * M_PI;
        mStepCount = 128;
        break;
    case HuygensCycloid:
        mScale = 4;
        mIntervalLenght = 2 * M_PI;
        mStepCount = 256;
        break;
    case Hypocycloid:
        mScale = 15;
        mIntervalLenght = 2 * M_PI;
        mStepCount = 256;
        break;
    case Line:
        mIntervalLenght = 1;
        mScale = 100;
        mStepCount = 128;
        break;
    default:
        //mBackgroundColor = Qt::black;
        break;
    }
}
QPointF RenderArea::compute(float t){
    switch (mShape){
    case Astroid:
        return compute_astroid(t);
        break;
    case Cycloid:
        return compute_cycloid(t);
        break;
    case HuygensCycloid:
        return compute_huygens(t);
        break;
    case Hypocycloid:
        return compute_hypo(t);
        break;
    case Line:
        return compute_line(t);
        break;
    default:
        //mBackgroundColor = Qt::black;
        break;
    }
    return QPointF(0, 0);
}
QPointF RenderArea::compute_astroid(float t){
    float cost_t = cos(t);
    float sin_t = sin(t);
    float x = 2 * cost_t * cost_t * cost_t;
    float y = 2 * sin_t * sin_t * sin_t;
    return QPointF(x,y);
}

QPointF RenderArea::compute_cycloid(float t){
    return QPointF (
                1.5 * (1 - cos (t)), // X
                1.5 * (t - sin (t)) // Y
    );
}

QPointF RenderArea::compute_huygens(float t){
    return QPointF (
                4 * (3 * cos(t) - cos (3 * t)), // X
                4 * (3 * sin(t) - sin (3 * t)) // Y
    );
}

QPointF RenderArea::compute_hypo(float t){
    return QPointF (
                1.5 * (2* cos(t) + cos(2 * t)), // X
                1.5 * (2* sin(t) - sin(2 * t))
    );
}
QPointF RenderArea::compute_line (float t){
    return QPointF (1 - t, 1 - t);
}
void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);



    painter.setBrush(mBackgroundColor);
    painter.setPen(mShapeColor);
    //drawing area
    painter.drawRect(this->rect());
    //painter.drawLine(this->rect().topLeft(), this->rect().bottomRight());

    QPoint center = this->rect().center();

    QPointF prevPoint = compute(0);
    QPoint prevPixel;
    prevPixel.setX((prevPoint.x() * mScale + center.x()));
    prevPixel.setY((prevPoint.y()) * mScale + center.y());


    float step = mIntervalLenght / mStepCount;
    for (float t = 0; t < mIntervalLenght; t+= step){
        QPointF point = compute (t);
        QPoint pixel;
        pixel.setX((point.x() * mScale + center.x()));
        pixel.setY((point.y()) * mScale + center.y());


        painter.drawLine(pixel, prevPixel);
        prevPixel = pixel;

    }
}
