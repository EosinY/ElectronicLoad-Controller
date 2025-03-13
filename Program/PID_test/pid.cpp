#include <cstdio>
#include <iostream>
#include <string>

#define DEBUG

int main(void)
{
    std::string foo;
    printf("string > ");
    scanf("%s", &foo);
    printf("Input: %s\n", foo);
#ifdef DEBUG
    system("pause");
#endif
    return 0;
}

class PID
{
private:
    const double _dx, _kp, _ki, _kd;
    double _intg(double xmin, double xmax);
    double _diff();
    double _prop();
    double _err(double x1, double x2, bool isAbs);

public:
    PID(double dx, double kp, double ki, double kd) : dx_(dx), _kp(kp), _ki(ki), _kd(kd){};
    double PID_main(double x, double tg);
};