//---------------------------------------------------------------------------

#ifndef GlobalDefH
#define GlobalDefH
#include <math.h>
#ifndef M_PI
#define M_PI   3.141592654
#endif
//---------------------------------------------------------------------------
// �����˽ṹ�ߴ�
//         UpperArmLength     |  UpperBaseLength
//                            |  (ע�⣺�̱۳���ָ�����ܻ����ߴ��1/2)
//     -----------------------|
//                            |
//                            |

// �ŷ���ײ���
//#define ROBOT_2
//#define ROBOT_1
//#define JUNE_BUG1
#define ROBOT_3

#ifdef ROBOT_1       // �칫�ҵĻ�����
   #define ROBOT_UPPER_ARM_LENGTH     0.375           // ��������ƽ̨���۳���
   #define ROBOT_UPPER_BASE_LENGTH    0.036           // ��������ƽ̨�̱۳���
   #define ROBOT_LOWER_ARM_LENGTH     0.675           // ��������ƽ̨���۳���
   #define ROBOT_LOWER_BASE_LENGTH    0.036           // ��������ƽ̨�̱۳���

   #define ACTIVE_SERVO_CNT           6
   #define SERVO_PULSE_ROUND          10000          // �ŷ�ת��һ�ܶ�Ӧ������(ÿ����������������������65535��
                                                     //   ÿ����������������6553500��ÿ�����50ת�����ÿתһ��������������131,070��
																										 //   �趨Ϊ10,000��̨���ŷ�B2������1ת����Ϊ160,000�������ӳ��ַ���(P1-44)��Ϊ160����ĸ(P1-45)Ϊ10��
   #define SERVO_ROUND_MM             5.0            // �ŷ�ת��һ�ܵ��ֱ���˶����룬��λ mm
   #define SERVO_RPM_MIN              5              // �ŷ���Сת�٣���λRPM
   #define SERVO_RPM_MAX              3000           // �ŷ����ת�٣���λRPM

   #define JACK_FIXED_LENGTH          1.134          // �ŷ���׹̶����ֳ���(�ó���ָ�����ɻ�������λ���ص�λ�ã���Ҫ׼ȷ����)
   #define JACK_SERVO_LENGTH          0.2            // �ŷ��˶��������г�(m)��ͨ��ָ������λ����֮��ĳ���
   #define JACK_SERVO_DEC             0.05           // �ŷ����˼���������(m)

   #define INIT_Z_POSITION            1.140
#endif

#ifdef ROBOT_2
   #define ROBOT_UPPER_ARM_LENGTH     1.1           // ��������ƽ̨���۳���
   #define ROBOT_UPPER_BASE_LENGTH    0.06          // ��������ƽ̨�̱۳���
   #define ROBOT_LOWER_ARM_LENGTH     1.25           // ��������ƽ̨���۳���
   #define ROBOT_LOWER_BASE_LENGTH    0.06          // ��������ƽ̨�̱۳���
	 
   #define ACTIVE_SERVO_CNT           6
   #define SERVO_PULSE_ROUND          10000          // �ŷ�ת��һ�ܶ�Ӧ������(ÿ����������������������65535��
                                                     //   ÿ����������������6553500��ÿ�����50ת�����ÿתһ��������������131,070��
																										 //   �趨Ϊ10,000��̨���ŷ�B2������1ת����Ϊ160,000�������ӳ��ַ���(P1-44)��Ϊ160����ĸ(P1-45)Ϊ10��
   #define SERVO_ROUND_MM             5.0            // �ŷ�ת��һ�ܵ��ֱ���˶����룬��λ mm
   #define SERVO_RPM_MIN              5              // �ŷ���Сת�٣���λRPM
   #define SERVO_RPM_MAX              3000           // �ŷ����ת�٣���λRPM

   #define JACK_FIXED_LENGTH          1.15          // �ŷ���׹̶����ֳ���(�ó���ָ�����ɻ�������λ���ص�λ�ã���Ҫ׼ȷ����)
   #define JACK_SERVO_LENGTH          0.4           // �ŷ������С�˶��г̣���λm(�����˶��У��ŷ�Ҫ����λ���ر���һ���������)
   #define JACK_SERVO_DEC             0.05           // �ŷ��������˶��г̣���λm
#endif

#ifdef ROBOT_3
   #define ROBOT_UPPER_ARM_LENGTH     1.5           // ��������ƽ̨���۳���
   #define ROBOT_UPPER_BASE_LENGTH    0.2          // ��������ƽ̨�̱۳���
   #define ROBOT_LOWER_ARM_LENGTH     3.0           // ��������ƽ̨���۳���
   #define ROBOT_LOWER_BASE_LENGTH    0.2          // ��������ƽ̨�̱۳���

   #define ACTIVE_SERVO_CNT           6
   #define SERVO_PULSE_ROUND          10000          // �ŷ�ת��һ�ܶ�Ӧ������(ÿ����������������������65535��
                                                     //   ÿ����������������6553500��ÿ�����50ת�����ÿתһ��������������131,070��
																										 //   �趨Ϊ10,000��̨���ŷ�B2������1ת����Ϊ160,000�������ӳ��ַ���(P1-44)��Ϊ160����ĸ(P1-45)Ϊ10��
   #define SERVO_ROUND_MM             5.0            // �ŷ�ת��һ�ܵ��ֱ���˶����룬��λ mm
   #define SERVO_RPM_MIN              5              // �ŷ���Сת�٣���λRPM
   #define SERVO_RPM_MAX              3000           // �ŷ����ת�٣���λRPM

   #define JACK_FIXED_LENGTH          3.0          // �ŷ���׹̶����ֳ���(�ó���ָ�����ɻ�������λ���ص�λ�ã���Ҫ׼ȷ����)
   #define JACK_SERVO_LENGTH          2.0           // �ŷ������С�˶��г̣���λm(�����˶��У��ŷ�Ҫ����λ���ر���һ���������)
   #define JACK_SERVO_DEC             0.05           // �ŷ��������˶��г̣���λm

   #define DEFAULT_Z_OFFSET           0.0
   #define XYPLANE_HEIGHT             0.01
#endif




#ifdef JUNE_BUG       // �������л�����
   #define ROBOT_UPPER_ARM_LENGTH     0.555          // ��������ƽ̨���۳���
   #define ROBOT_UPPER_BASE_LENGTH    0.045          // ��������ƽ̨�̱۳���
   #define ROBOT_LOWER_ARM_LENGTH     0.399          // ��������ƽ̨���۳���
   #define ROBOT_LOWER_BASE_LENGTH    0.045          // ��������ƽ̨�̱۳���

   #define ACTIVE_SERVO_CNT           6
   #define SERVO_PULSE_ROUND          10000          // �ŷ�ת��һ�ܶ�Ӧ������(ÿ����������������������65535��
                                                     //   ÿ����������������6553500��ÿ�����50ת�����ÿתһ��������������131,070��
																										 //   �趨Ϊ10,000��̨���ŷ�B2������1ת����Ϊ160,000�������ӳ��ַ���(P1-44)��Ϊ160����ĸ(P1-45)Ϊ10��
   #define SERVO_ROUND_MM             5.0            // �ŷ�ת��һ�ܵ��ֱ���˶����룬��λ mm
   #define SERVO_RPM_MIN              5              // �ŷ���Сת�٣���λRPM
   #define SERVO_RPM_MAX              3000           // �ŷ����ת�٣���λRPM

   #define JACK_FIXED_LENGTH          0.506          // �ŷ���׹̶����ֳ���(�ó���ָ�����ɻ�������λ���ص�λ�ã���Ҫ׼ȷ����)
   #define JACK_SERVO_LENGTH          0.300          // �ŷ��˶��������г�(m)��ͨ��ָ������λ����֮��ĳ���
   #define JACK_SERVO_DEC             0.005          // �ŷ����˼���������(m)

   #define INIT_Z_POSITION            1.140
#endif

#ifdef JUNE_BUG1       // �������л�����
   #define ROBOT_UPPER_ARM_LENGTH     0.448          // ��������ƽ̨���۳���
   #define ROBOT_UPPER_BASE_LENGTH    0.050          // ��������ƽ̨�̱۳���
   #define ROBOT_LOWER_ARM_LENGTH     0.448          // ��������ƽ̨���۳���
   #define ROBOT_LOWER_BASE_LENGTH    0.050          // ��������ƽ̨�̱۳���

   #define ACTIVE_SERVO_CNT           6
   #define SERVO_PULSE_ROUND          2000           // �ŷ�ת��һ�ܶ�Ӧ������(ÿ����������������������65535��
                                                     // ÿ����������������6553500��ÿ�����50ת�����ÿתһ��������������131,070��
																										 //   �趨Ϊ10,000��̨���ŷ�B2������1ת����Ϊ160,000�������ӳ��ַ���(P1-44)��Ϊ160����ĸ(P1-45)Ϊ10��
   #define SERVO_ROUND_MM             5.0            // �ŷ�ת��һ�ܵ��ֱ���˶����룬��λ mm
   #define SERVO_RPM_MIN              20             // �ŷ���Сת�٣���λRPM
   #define SERVO_RPM_MAX              3000           // �ŷ����ת�٣���λRPM

   #define JACK_FIXED_LENGTH          0.54           // �ŷ���׹̶����ֳ���(�ó���ָ�����ɻ�������λ���ص�λ�ã���Ҫ׼ȷ����)
   #define JACK_SERVO_LENGTH          0.25           // �ŷ��˶��������г�(m)��ͨ��ָ������λ����֮��ĳ���
   #define JACK_SERVO_DEC             0.005          // �ŷ����˼���������(m)

   #define INIT_Z_POSITION            1.3
   #define DEFAULT_Z_OFFSET           0.0

   #define XYPLANE_HEIGHT             0.01
#endif

// �˶�ģ�����
#define MAX_LINEAR_ACC  0.5      // ���ֱ�߼��ٶ�(m/s^2)

#define MAX_SPEED_X     0.3    // x���������ٶ�
#define MAX_RANGE_X     0.038   // x�������˶�����(�����ĵ�Ϊԭ��)

#define MAX_SPEED_Y     0.3    // y���������ٶ�
#define MAX_RANGE_Y     0.078   // y�������˶�����(�����ĵ�Ϊԭ��)

#define MAX_SPEED_Z     0.3    // z���������ٶ�
#define MAX_RANGE_Z     0.038   // z�������˶�����(�����ĵ�Ϊԭ��)

#define MAX_ROTARY_SPD  20     // �����ٶ�(deg/s)
#define MAX_YAW         5
#define MAX_PITCH       10
#define MAX_ROLL        10

// ���ڿ���
// ���ڼ��ڿ�����Ҫʹ��UART2��UART3����˼��ڿ���ʱ���޷�������������λ��ͨ�ſ���
//#define SYS_STABLE_CTRL   


//---------------------------------------------------------------------------
// ���²��������̶�
//---------------------------------------------------------------------------
// ������ˢ������
#ifdef __BORLANDC__
   #define  CTRL_INTERVAL  0.02
#else
   #define  CTRL_INTERVAL  0.01
#endif

// �����������ٶ�(m/s)�������ٶ�(m/s^2)
#define JACK_MAX_SPEED  0.25
#define JACK_MAX_ACC    0.5

// �����������ٶ�
#define GO_ZERO_RPM          100     // ����ת��
#define ZERO_2_CENTER_SPD    0.01    // ����������ĵ��ƶ��ٶ�(m/s)

// �ŷ����ת�ٱ仯(0RPM��SERVO_RPM_MAX)����Ҫ�ļ���ʱ��
// ͨ����ʱ��������������ٶȣ��Ӷ������ŷ�����������
#define SERVO_FULL_SPD_ACC_TIME   0.4

#define JACK_SERVO_DEC_RANGE       0.05           // �ŷ���׼����г�(m)

// ����������
#define  PULSE_SRC_FREQUENCY     1.0E6   // ����ԴƵ��(1M)

// ������������ʱ��ʹ�ÿ����㷨
//#define  CALC_SIN_FAST

// �Ƿ���ÿ���������ڼ�����������˶�ѧ����
//#define CALC_FDKP

// ͨ������
#define UART3_BAUD_RATE 4800

// ���������ַ���ʽ��ʾ������Ϣ������debug������
#define  SHOW_DEBUG_STRING
//----------------------------------------------------------------------------

#endif
