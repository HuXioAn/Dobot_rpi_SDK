#include "SocketUtils.h"
#include <sstream>
using std::stringstream;

#define isSocketUtilDebug 1

TCPClient::TCPClient()
{
    this->isConnected = false;
    this->sockfd      = 0;    
}

TCPClient::~TCPClient()
{
    if(this->sockfd){
        close(this->sockfd);
        this->sockfd = 0;
    }
        
}

int TCPClient::TCPClientStart(uint16_t port,std::string remoteip,uint32_t blockTimeMs)
{
    int ret;
    this->reConnectBlockTimeMs = blockTimeMs;
    this->remoteIP             = remoteip;
    this->remotePort           = port;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(blockTimeMs < 1){
        blockTimeMs = 0xffffffff;
    }
    struct timeval timev;
    timev.tv_sec   = blockTimeMs/1000;
    timev.tv_usec  =(blockTimeMs%1000) * 1000;
    if (setsockopt(this->sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timev, sizeof(struct timeval)) != 0){
        perror("[TCPClient::TCPClientStart] :");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(remoteip.c_str());
    socklen_t addr_len = sizeof(addr);
    if((ret = connect(this->sockfd, (struct sockaddr*)&addr, addr_len)) < 0){
        printf("[TCPClient::TCPClientStart] connect faild !!! errcode = %d\n",ret);
        perror("[TCPClient::TCPClientStart] connect ");
        return ret;
    }
    if(this->sockfd && !ret ) this->isConnected = true;
    printf("connect to host:%s port:%d success!!! \n",this->remoteIP.c_str(),this->remotePort);   
    return 0;
}

int TCPClient::RecvData(char* buf,uint32_t bufSize , uint32_t timeOutMs)
{    
    int ret = -1;    
    timeval timev = {timeOutMs/1000,(timeOutMs%1000) * 1000};        
    if (setsockopt(this->sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timev, sizeof(struct timeval)) != 0){
        printf("[TCPClient::Recvdata] set time out faild!!!!!  \n");
        return -2;
    }      
  
    ret = recv(this->sockfd,buf,bufSize,0);     
    return ret;   
}

int TCPClient::SendData(const char* buf,uint32_t bufSize)
{
    if(isSocketUtilDebug) printf("[TCPClient::SendData]:buf=%s,bufSize=%d\n",buf,bufSize);        
    if(this->isConnected == false){ 
        return -1;
    }
    if(bufSize) bufSize = strlen(buf);
    // if(send(this->sockfd, buf, bufSize, 0) < 0){
    //     shutdown(this->sockfd,SHUT_RDWR);
    //     close(this->sockfd);
    //     this->sockfd = 0;
    //     this->isConnected = false;
    //     return -2;
    // }
    return send(this->sockfd, buf, bufSize, 0);
}

int TCPClient::SendAndRecvData(const char *bufSend, char * bufRev, uint32_t bufSize, uint32_t revTimeOutMs)
{
    int sendRet = SendData(bufSend);
    if(sendRet < 0){
        perror("sendAndRecv failed1:\n");
        return -2;
    }
    sleep(0.5);
    int recvRet = RecvData(bufRev, bufSize, revTimeOutMs);
    if(recvRet < 0){
        perror("sendAndRecv failed2:\n");
        return -1;
    }
    return recvRet;
}

int TCPClient::Close(){
    if(this->sockfd){
        close(this->sockfd);
        this->sockfd = 0;
    }    
    return 0;
}

int TCPClient::ConnectServer(void)
{   
    int ret = -1;
    if(this->isConnected == false){
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(this->remotePort);
        addr.sin_addr.s_addr = inet_addr(this->remoteIP.c_str());
        socklen_t addr_len = sizeof(addr);
        if((ret = connect(this->sockfd, (struct sockaddr*)&addr, addr_len)) < 0){
            printf("[TCPClient::connectServer] connect faild !!! errcode = %d\n",ret);
            perror("[TCPClient::connectServer] connect ");
            return ret;
        }
        if(this->sockfd && !ret ) this->isConnected = true;
        printf("connect to host:%s port:%d success!!! \n",this->remoteIP.c_str(),this->remotePort);
    }
    return 0;
}

void * TCPClient::ReConnectSubProcess(void * __this)
{
    TCPClient* temp = (TCPClient *) __this;
    int ret;
    while(1){
        ret = temp->ConnectServer();
        if(!ret){ // 
            usleep(temp->netTimeOutMs + 1000); 
            //printf("[TCPClient::ReConnectSubProcess] ...\n");
        }
    }
    return nullptr;
}

int TCPClient::EnableRobot(){
    const char* t = "EnableRobot()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::DisableRobot(){
    const char* t = "DisableRobot()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::ClearError(){
    const char* t = "ClearError()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::ResetRobot(){
    const  char* t = "ResetRobot()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::SpeedFactor(int speed){
    stringstream fmt;                       
    fmt << "SpeedFactor(" << speed << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::User(int index){
    stringstream fmt;                       
    fmt << "User(" << index << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::Tool(int index){
    stringstream fmt;                       
    fmt << "Tool(" << index << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::RobotMode(){
    const char* t = "RobotMode()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::PayLoad(float weight, float inertia){
    stringstream fmt;                       
    fmt << "PayLoad(" << weight << "," << inertia << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::DO(int index, int val){
    stringstream fmt;                       
    fmt << "DO(" << index << "," << val << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::DOExecute(int index, int val){
    stringstream fmt;                       
    fmt << "DOExecute(" << index << "," << val << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::ToolDO(int index, int val){
    stringstream fmt;                       
    fmt << "ToolDO(" << index << "," << val << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::ToolDOExecute(int index, int val){
    stringstream fmt;                       
    fmt << "ToolDOExecute(" << index << "," << val << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::AO(int index, int val){
    stringstream fmt;                       
    fmt << "AO(" << index << "," << val << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::AOExecute(int index, int val){
    stringstream fmt;                       
    fmt << "AOExecute(" << index << "," << val << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::AccJ(int speed){
    stringstream fmt;                       
    fmt << "AccJ(" << speed << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::AccL(int speed){
    stringstream fmt;                       
    fmt << "AccL(" << speed << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::SpeedJ(int speed){
    stringstream fmt;                       
    fmt << "SpeedJ(" << speed << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::SpeedL(int speed){
    stringstream fmt;                       
    fmt << "SpeedL(" << speed << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::Arch(int index){
    stringstream fmt;                       
    fmt << "Arch(" << index << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::CP(int ratio){
    stringstream fmt;                       
    fmt << "CP(" << ratio << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::LimZ(int value){
    stringstream fmt;                       
    fmt << "LimZ(" << value << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::SetArmOrientation(int r, int d, int n, int cfg){
    stringstream fmt;                       
    fmt << "SetArmOrientation(" << r << "," << d << "," << n << "," << cfg << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::PowerOn(){
    const char* t = "PowerOn()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::RunScript(char *project_name){
    printf("%s\n", project_name);
    char bufRev[1024] = {0};
    return SendAndRecvData(project_name, bufRev);
}

int TCPClient::StopScript(){
    const char* t = "StopScript()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::PauseScript(){
    const char* t = "PauseScript()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::ContinueScript(){
    const char* t = "ContinueScript()";
    printf("%s\n", t);
    char bufRev[1024] = {0};
    return SendAndRecvData(t, bufRev);
}

int TCPClient::GetHoldRegs(int id, int addr, int count, int type){
    stringstream fmt;                       
    fmt << "GetHoldRegs(" << id << "," << addr << "," << count << "," << type << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}

int TCPClient::SetHoldRegs(int id, int addr, int count, int table, int type){
    stringstream fmt;                       
    fmt << "SetHoldRegs(" << id << "," << addr << "," << count << "," << table << "," << type << ")";
    printf("%s\n", fmt.str().c_str());
    char bufRev[1024] = {0};
    return SendAndRecvData(fmt.str().c_str(), bufRev);
}


int TCPClient::MovJ(float j1, float j2, float j3, float j4, float j5, float j6){
    stringstream fmt;                       
    fmt << "MovJ(" << j1 << "," << j2 << "," << j3 << "," << j4 << "," << j5 << "," << j6 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::MovL(float x, float y, int z, float a, float  b, float c){
    stringstream fmt;                       
    fmt << "MovL(" << x << "," << y << "," << z << "," << a << "," << b << "," << c << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::JointMovJ(float j1, float j2, float j3, float  j4, float j5, float j6){
    stringstream fmt;                       
    fmt << "JointMovJ(" << j1 << "," << j2 << "," << j3 << "," << j4 << "," << j5 << "," << j6 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::Jump(){
    stringstream fmt;                       
    fmt << "Jump(" << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::RelMovJ(float offset1, float offset2, float offset3, float offset4, float offset5, float offset6){
    stringstream fmt;                       
    fmt << "RelMovJ(" << offset1 << "," << offset2 << "," << offset3 << "," << offset4 << "," << offset5 << "," << offset6 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::RelMovL(float offsetX, float offsetY, float offsetZ){
    stringstream fmt;                       
    fmt << "RelMovL(" << offsetX << "," << offsetY << "," << offsetZ << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::MovLIO(float x, float y, float z, float a, float b, float c, int dynArrayIO[][4], int rowSize){
    stringstream fmt;                       
    fmt << "MovLIO(" << x << "," << y << "," << z << "," << a << "," << b << "," << c;
    for(int i=0; i< rowSize; i++) {
        fmt << ",{" << dynArrayIO[i][0] << "," << dynArrayIO[i][1] << "," << dynArrayIO[i][2] << "," << dynArrayIO[i][3] << "}";
    }
    fmt << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::MovJIO(float x, float y, float z, float a, float b, float c, int dynArrayIO[][4], int rowSize){
    stringstream fmt;                       
    fmt << "MovJIO(" << x << "," << y << "," << z << "," << a << "," << b << "," << c;
     for(int i=0; i< rowSize; i++) {
        fmt << ",{" << dynArrayIO[i][0] << "," << dynArrayIO[i][1] << "," << dynArrayIO[i][2] << "," << dynArrayIO[i][3] << "}";
    }
    fmt << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::Arc(float x1, float y1, float z1, float a1, float b1, float c1, float x2, float y2, float z2, float a2, float b2, float c2){
    stringstream fmt;                       
    fmt << "Arc(" << x1 << "," << y1 << "," << z1 << "," << a1 << "," << b1 << "," << c1
                    << x2 << "," << y2 << "," << z2 << "," << a2 << "," << b2 << "," << c2 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::Circle(int count, float x1, float y1, float z1, float a1, float b1, float c1, float x2, float y2, float z2, float a2, float b2, float c2){
    stringstream fmt;                       
    fmt << "Circle(" << count << x1 << "," << y1 << "," << z1 << "," << a1 << "," << b1 << "," << c1
                            << x2 << "," << y2 << "," << z2 << "," << a2 << "," << b2 << "," << c2 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::ServoJ(float j1, float j2, float j3, float j4, float j5, float j6){
    stringstream fmt;                       
    fmt << "ServoJ(" << j1 << "," << j2 << "," << j3 << "," << j4 << "," << j5 << "," << j6 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}

int TCPClient::ServoP(float j1, float j2, float j3, float j4, float j5, float j6){
    stringstream fmt;                       
    fmt << "ServoP(" << j1 << "," << j2 << "," << j3 << "," << j4 << "," << j5 << "," << j6 << ")";
    printf("%s\n", fmt.str().c_str());
    return SendData(fmt.str().c_str());
}