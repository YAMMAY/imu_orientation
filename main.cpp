//Added by siyuan.yu
#include "MadgwickAHRS.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#define FMT_0 std::setw(16)<<std::fixed<<std::setprecision(6)
#define FMT_1 std::setw(12)<<std::fixed<<std::setprecision(6)
#define FMT_2 std::setw(7)<<std::fixed<<std::setprecision(3)
int main(int argc, char **argv)
{
    if(argc<3) 
    {
        std::cout<<"usage:./main  imu_input.txt imu_output.txt\n";
        return 0;
    }
    std::ifstream ifs(argv[1]);
    std::ofstream ofs(argv[2]);
    std::string ts,vels,accs;
    double times;
    float gx, gy,  gz, ax, ay, az;
    while(ifs>>ts>>times>>vels>>gx>>gy>>gz>>accs>>ax>>ay>>az)
    {
        MadgwickAHRSupdateIMU(gx,gy,gz,ax,ay,az);
        ofs<<ts<<" "<<FMT_0<<times<<"\t"
        <<vels<<" "<<FMT_1<<gx<<" "<<FMT_1<<gy<<" "<<FMT_1<<gz<<"\t"
        <<accs<<" "<<FMT_1<<ax<<" "<<FMT_1<<ay<<" "<<FMT_1<<az<<"\t"
        "orientation(w,x,y,z): "<<FMT_2<<q0<<" "<<FMT_2<<q1<<" "<<FMT_2<<q2<<" "<<FMT_2<<q3<<std::endl;
    }
    ifs.close();
    ofs.close();
    return 0;
}
