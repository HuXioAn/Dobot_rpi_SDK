#include <iostream>

#pragma pack(push)
#pragma pack(8)
// data: 8 bytes and 48 bytes aligned.
// size: 30 * 8 * 6 = 30 *6*sizeof(double) = 30 * sizeof(double)
typedef struct RealTimeData_t {
    // 
    uint64_t len;                        // 0000 ~ 0000  string length
    uint64_t digital_input_bits;         // 0008 ~ 0015  DI 
    uint64_t digital_outputs;            // 0016 ~ 0023  DO
    uint64_t robot_mode;                 // 0024 ~ 0031  
    uint64_t controller_timer;           // 0032 ~ 0039                    
    uint64_t run_time;                   // 0040 ~ 0047                      
    // 0048 ~ 0095                       //                
    uint64_t test_value;                 // 0048 ~ 0055  
    double safety_mode;                  // 0056 ~ 0063  
    double speed_scaling;                // 0064 ~ 0071                      
    double linear_momentum_norm;         // 0072 ~ 0079 
    double v_main;                       // 0080 ~ 0087 
    double v_robot;                      // 0088 ~ 0095 
    // 0096 ~ 0143                       // 
    double i_robot;                      // 0096 ~ 0103 
    double program_state;                // 0104 ~ 0111 
    double safety_status;                // 0112 ~ 0119 
    double tool_accelerometer_values[3]; // 0120 ~ 0143 
    // 0144 ~ 0191                       // 
    double elbow_position[3];            // 0144 ~ 0167 
    double elbow_velocity[3];            // 0168 ~ 0191 
    // 0192 ~ ...                        // 
    double q_target[6];                  // 0192 ~ 0239  //   
    double qd_target[6];                 // 0240 ~ 0287  // 
    double qdd_target[6];                // 0288 ~ 0335  // 
    double i_target[6];                  // 0336 ~ 0383  // 
    double m_target[6];                  // 0384 ~ 0431  // 
    double q_actual[6];                  // 0432 ~ 0479  // 
    double qd_actual[6];                 // 0480 ~ 0527  // 
    double i_actual[6];                  // 0528 ~ 0575  // 
    double i_control[6];                 // 0576 ~ 0623  // 
    double tool_vector_actual[6];        // 0624 ~ 0671  // 
    double TCP_speed_actual[6];          // 0672 ~ 0719  // 
    double TCP_force[6];                 // 0720 ~ 0767  // 
    double Tool_vector_target[6];        // 0768 ~ 0815  // 
    double TCP_speed_target[6];          // 0816 ~ 0863  // 
    double motor_temperatures[6];        // 0864 ~ 0911  // 
    double joint_modes[6];               // 0912 ~ 0959  // 
    double v_actual[6];                  // 960  ~ 1007  // 
    double dummy[9][6]; //               // 1008 ~ 1439  // 
}RealTimeData_t;
#pragma pack(pop)


#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
void dump_hex(uint8_t *buf, uint32_t size);

void print_params(RealTimeData_t *pRtData);