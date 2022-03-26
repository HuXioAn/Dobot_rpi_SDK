#include <iostream>
#include <thread>
#include <string.h>
#include <mutex>
#include <chrono>
#include <memory>
#include "SocketUtils.h"
#include "RealTimeData.h"

using namespace std;

volatile bool flag = true;
mutex mtx;

uint64_t getNowMilliseconds()
{
    auto now = std::chrono::system_clock::now().time_since_epoch();
    auto ts = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
    return ts;
}

void dashboard(TCPClient *clientDashboard, TCPClient *clientFeedback){
    clientDashboard->ClearError();
    clientDashboard->EnableRobot();
    sleep(6);
    clientDashboard->User(0);
    clientDashboard->Tool(0);
    clientDashboard->SpeedFactor(10);
    clientFeedback->JointMovJ(0, 60, 0, 0, 0, 0);
    sleep(8);
    clientFeedback->JointMovJ(0, 30, 0, 0, 0, 0);
    sleep(8);

    std::lock_guard<std::mutex> guard(mtx);
    flag = false;
    printf("end!!!");
}

void feedback(TCPClient *clientFeedback){
    char *buf = (char*)malloc(2048*sizeof(char));
    RealTimeData_t pack;
    int ret;
    uint64_t temp;
    uint8_t *p_temp = (uint8_t*)(&temp);
    uint16_t lengthSize;

    uint64_t beginTime = getNowMilliseconds();
    int hasRead = 0;
    while(true){
        std::lock_guard<std::mutex> guard(mtx);
        if (flag){
            while (hasRead < 1440)
            {
                ret = clientFeedback->RecvData(buf + hasRead, 1440 - hasRead);
                if (ret>0)
                    hasRead += ret;
            }
            hasRead = 0;

            memcpy(&pack,buf,sizeof(pack));
            memcpy(&lengthSize,buf,sizeof(uint16_t));
            memcpy(&temp,buf+48,sizeof(uint64_t));
            printf("ret = %d\n",ret);
            if(ret > 0 ){      
                auto nowTime = getNowMilliseconds();
                if (nowTime - beginTime >= 100)
                {
                    beginTime = nowTime;
                    //dump_hex(buf,sizeof(RealTimeData_t));     
                    printf("0x%016llx\n", temp);
                    if (temp != 0x123456789abcdef || lengthSize != 1440) {
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~parse pack err" << endl;
                        continue;
                    }
                    // printf("0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n",
                    //     buf[48],buf[49],buf[50],buf[51],
                    //     buf[52],buf[53],buf[54],buf[55]);                        
                    printf("%02x %02x %2x %02x %02x %02x %02x %02x\n",
                        p_temp[0],p_temp[1],p_temp[2],p_temp[3],
                        p_temp[4],p_temp[5],p_temp[6],p_temp[7]);
                    print_params(&pack);
                }
            } else {
                perror("recv err");
            }
        } else {
            break;            
        }
    }
}

int main(int argc, char* argv[])
{
    TCPClient *tcpDashboard = new TCPClient();
    TCPClient *tcpFeedback = new TCPClient();
    if(tcpDashboard->TCPClientStart(29999, "192.168.5.1", 1000) < 0){
        return -1;
    }
    if(tcpFeedback->TCPClientStart(30003, "192.168.5.1", 1000) < 0){
        return -2;
    }

    thread thread1(feedback, tcpFeedback);
    thread thread2(dashboard, tcpDashboard, tcpFeedback);
    thread1.join();
    thread2.join();
    tcpDashboard->Close();
    tcpFeedback->Close();
    return 0;
}
