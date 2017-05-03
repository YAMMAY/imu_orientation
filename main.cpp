//Added by siyuan.yu
#include "MadgwickAHRS.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#define FMT_0 std::setw(16)<<std::fixed<<std::setprecision(6)
#define FMT_1 std::setw(12)<<std::fixed<<std::setprecision(6)
#define FMT_2 std::setw(7)<<std::fixed<<std::setprecision(3)
inline void toEulerianAngle(double& roll, double& pitch, double& yaw)
{
	double ysqr = q2 * q2;

	// roll (x-axis rotation)
	double t0 = +2.0 * (q0 * q1 + q2 * q3);
	double t1 = +1.0 - 2.0 * (q1 * q1 + ysqr);
	roll = atan2(t0, t1);

	// pitch (y-axis rotation)
	double t2 = +2.0 * (q0 * q2 - q3 * q1);
	t2 = t2 > 1.0 ? 1.0 : t2;
	t2 = t2 < -1.0 ? -1.0 : t2;
	pitch = asin(t2);

	// yaw (z-axis rotation)
	double t3 = +2.0 * (q0 * q3 + q1 * q2);
	double t4 = +1.0 - 2.0 * (ysqr + q3 * q3);  
	yaw = atan2(t3, t4);
}
void printUsage()
{
        std::cout<<"Calculate quaternion  usage:./main  imu_input.txt imu_output.txt\n";
        std::cout<<"Calculate euler angle usage:./main  imu_input.txt imu_output.txt euler\n";
}
int main(int argc, char **argv)
{
    if(argc<3) 
    {
	printUsage();
        return 0;
    }
    std::ifstream ifs(argv[1]);
    std::ofstream ofs(argv[2]);
    std::string ts,vels,accs;
    double times,roll,pitch,yaw;
    float gx, gy,  gz, ax, ay, az;
    while(ifs>>ts>>times>>vels>>gx>>gy>>gz>>accs>>ax>>ay>>az)
    {
        MadgwickAHRSupdateIMU(gx,gy,gz,ax,ay,az);
        ofs<<ts<<" "<<FMT_0<<times<<"\t"
        <<vels<<" "<<FMT_1<<gx<<" "<<FMT_1<<gy<<" "<<FMT_1<<gz<<"\t"
        <<accs<<" "<<FMT_1<<ax<<" "<<FMT_1<<ay<<" "<<FMT_1<<az<<"\t";
	if(argc==4&&strcmp(argv[3],"euler")==0)
	{
		toEulerianAngle(roll,pitch,yaw);
		ofs<<"orientation(roll,pitch,yaw): "<<FMT_2<<roll<<" "<<FMT_2<<pitch<<" "<<FMT_2<<yaw<<std::endl;
	}
        else if(argc==3) ofs<<"orientation(w,x,y,z): "<<FMT_2<<q0<<" "<<FMT_2<<q1<<" "<<FMT_2<<q2<<" "<<FMT_2<<q3<<std::endl;
	else
	{
		printUsage();
		break;
	}
    }
    ifs.close();
    ofs.close();
    return 0;
}
