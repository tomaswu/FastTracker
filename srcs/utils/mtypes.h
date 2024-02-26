#ifndef MTYPES_H
#define MTYPES_H

namespace mtypes {


enum POS_TYPE
{
    frame,
    time,
    step
};

class VideoPos
{

public:
    int frame();
    double time();
    int step();
    double getTypePos();
    POS_TYPE posType();
    int maxFrame();

    void setFrame(int frame);
    void setTime(double time);
    void setStep(int step);
    void setIntervalStep(int step);
    void setZeroFrame(int frame);
    void setFps(double fps);
    void setCurrentFrame2ZeroTime();
    void setPosType(POS_TYPE pt);
    void setMaxFrame(int mf);
    void setInfo(int mf,double fps);

private:
    int         _frame{0};
    double      _time{0};
    int         _step{0};
    int         _intervalStep{1};
    double      _fps{1};
    int         _zeroFrame{0};
    int         _maxFrame{0};
    POS_TYPE    _pos_type{POS_TYPE::frame};
};

}
#endif // MTYPES_H
