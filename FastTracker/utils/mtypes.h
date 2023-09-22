#ifndef MTYPES_H
#define MTYPES_H

class VideoPos
{

public:
    int frame();
    double time();
    int step();

    void setFrame(int frame);
    void setTime(double time);
    void setStep(int step);
    void setIntervalStep(int step);
    void setZeroFrame(int frame);
    void setFps(double fps);
    void setCurrentFrame2ZeroTime();

private:
    int         _frame{0};
    double      _time{0};
    int         _step{0};
    int         _intervalStep{1};
    double      _fps{1};
    int         _zeroFrame{0};

};



#endif // MTYPES_H
