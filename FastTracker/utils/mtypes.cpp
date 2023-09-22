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
    int df = frame-_frame;
    _frame=frame;
    _time+=df/_fps;
    int dstep = df/_intervalStep;
    _step+=dstep;
}

void VideoPos::setTime(double time)
{
    double dt = time-_time;
    _time=time;
    _frame+=dt*_fps;
    _step+=dt*_fps/_intervalStep;
    if(_frame<0)setFrame(0);
}

void VideoPos::setStep(int step)
{
    int ds=step-_step;
    int f=_frame+ds*_intervalStep;
    setFrame(f);
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

void VideoPos::setCurrentFrame2ZeroTime()
{
    _time=0;
    _zeroFrame=_frame;
}
