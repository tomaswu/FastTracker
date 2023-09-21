#include "utils/mtypes.h"


int VideoPos::frame()
{
    return _frame;
}

double VideoPos::time()
{
    return _time;
}

int VideoPos::step()
{
    return _step;
}

void VideoPos::setFrame(int frame)
{
    if(frame<0)frame=0;
    auto df = frame-_frame;
    _frame=frame;
    _time+=df/_fps;
    int dstep = df/_intervalStep;
    _step+=dstep;
}

void VideoPos::setTime(double time)
{

}

void VideoPos::setIntervalStep(int step)
{
    if(step<1)step=1;
    _intervalStep=step;
}

void VideoPos::setZeroFrame(int frame)
{
    if(frame<0)frame=0;
    _zeroFrame=frame;
}

void VideoPos::setFps(double fps)
{
    if(fps<0)return;
    _fps=fps;
}
