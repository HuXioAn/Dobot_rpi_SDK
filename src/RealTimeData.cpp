#include "RealTimeData.h"

void dump_hex(uint8_t *buf, uint32_t size)
{
    int i, j;

    for (i = 0; i < size; i += 16)
    {
        printf("%08X: ", i);

        for (j = 0; j < 16; j++)
        {
            if (i + j < size)
            {
                printf("%02X ", buf[i + j]);
            }
            else
            {
                printf("   ");
            }
        }
        printf(" ");

        for (j = 0; j < 16; j++)
        {
            if (i + j < size)
            {
                printf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
            }
        }
        printf("\n");
    }
}

void   print_params(RealTimeData_t *pRtData)
{
    printf("q   : %f,%f,%f,%f,%f,%f\n",
        pRtData->q_target[0],pRtData->q_target[1],pRtData->q_target[2],
        pRtData->q_target[3],pRtData->q_target[4],pRtData->q_target[5]);
    printf("qd  : %f,%f,%f,%f,%f,%f\n",
        pRtData->qd_target[0],pRtData->qd_target[1],pRtData->qd_target[2],
        pRtData->qd_target[3],pRtData->qd_target[4],pRtData->qd_target[5]);
    printf("qdd : %f,%f,%f,%f,%f,%f\n",
        pRtData->qdd_target[0],pRtData->qdd_target[1],pRtData->qdd_target[2],
        pRtData->qdd_target[3],pRtData->qdd_target[4],pRtData->qdd_target[5]);
    printf("i   : %f,%f,%f,%f,%f,%f\n",
        pRtData->i_target[0],pRtData->i_target[1],pRtData->i_target[2],
        pRtData->i_target[3],pRtData->i_target[4],pRtData->i_target[5]);
    printf("m   : %f,%f,%f,%f,%f,%f\n",
        pRtData->m_target[0],pRtData->m_target[1],pRtData->m_target[2],
        pRtData->m_target[3],pRtData->m_target[4],pRtData->m_target[5]);
    printf("qact: %f,%f,%f,%f,%f,%f\n",
        pRtData->q_actual[0],pRtData->q_actual[1],pRtData->q_actual[2],
        pRtData->q_actual[3],pRtData->q_actual[4],pRtData->q_actual[5]);
    printf("qdact: %f,%f,%f,%f,%f,%f\n",
        pRtData->qd_actual[0],pRtData->qd_actual[1],pRtData->qd_actual[2],
        pRtData->qd_actual[3],pRtData->qd_actual[4],pRtData->qd_actual[5]);
    printf("iact: %f,%f,%f,%f,%f,%f\n",
        pRtData->i_actual[0],pRtData->i_actual[1],pRtData->i_actual[2],
        pRtData->i_actual[3],pRtData->i_actual[4],pRtData->i_actual[5]);
    printf("ictl: %f,%f,%f,%f,%f,%f\n",
        pRtData->i_control[0],pRtData->i_control[1],pRtData->i_control[2],
        pRtData->i_control[3],pRtData->i_control[4],pRtData->i_control[5]);
    printf("vact: %f,%f,%f,%f,%f,%f\n",
        pRtData->v_actual[0],pRtData->v_actual[1],pRtData->v_actual[2],
        pRtData->v_actual[3],pRtData->v_actual[4],pRtData->v_actual[5]);
    printf("toolv: %f,%f,%f,%f,%f,%f\n",
        pRtData->tool_vector_actual[0],pRtData->tool_vector_actual[1],pRtData->tool_vector_actual[2],
        pRtData->tool_vector_actual[3],pRtData->tool_vector_actual[4],pRtData->tool_vector_actual[5]);
    printf("tempM: %f,%f,%f,%f,%f,%f\n",
        pRtData->motor_temperatures[0],pRtData->motor_temperatures[1],pRtData->motor_temperatures[2],
        pRtData->motor_temperatures[3],pRtData->motor_temperatures[4],pRtData->motor_temperatures[5]);
    // for (int i = 0;i < 6;i++) {
    //     printf("pRtData->q_target[%d]     = %8.3f\n",i,pRtData->q_target[i]  );
    //     printf("pRtData->qd_target[%d]    = %8.3f\n",i,pRtData->qd_target[i] );
    //     printf("pRtData->qdd_target[%d]   = %8.3f\n",i,pRtData->qdd_target[i]);
    //     printf("pRtData->i_target[%d]     = %8.3f\n",i,pRtData->i_target[i]  );
    //     printf("pRtData->m_target[%d]     = %8.3f\n",i,pRtData->m_target[i]  );
    //     printf("pRtData->q_actual[%d]     = %8.3f\n",i,pRtData->q_actual[i]    );   
    //     printf("pRtData->qd_actual[%d]    = %8.3f\n",i,pRtData->qd_actual[i]   );   
    //     printf("pRtData->i_actual[%d]     = %8.3f\n",i,pRtData->i_actual[i]    );   
    //     printf("pRtData->i_control[%d]    = %8.3f\n",i,pRtData->i_control[i]   );   
    //     printf("pRtData->v_actual[%d]     = %8.3f\n",i,pRtData->v_actual[i]   );   
    //     printf("pRtData->tool_vector_actual[%d]    = %8.3f\n",i,pRtData->tool_vector_actual[i]   );   
    //     printf("pRtData->motor_temperatures[%d]    = %8.3f\n",i,pRtData->motor_temperatures[i]   );
    // }
    printf("pRtData->linear_momentum_norm   = %8.3f\n", pRtData->linear_momentum_norm);
    printf("pRtData->v_robot                = %8.3f\n", pRtData->v_robot);
    printf("pRtData->i_robot                = %8.3f\n", pRtData->i_robot);
    printf("pRtData->digital_input_bits     = %016llx\n", pRtData->digital_input_bits);
    printf("pRtData->digital_outputs        = %016llx\n", pRtData->digital_outputs);
    printf("pRtData->robot_mode             = %016llx\n", pRtData->robot_mode);
    printf("pRtData->controller_timer       = %016llx\n", pRtData->controller_timer);
    printf("test = %d \n", *(uint16_t*)&(pRtData->len));
}

