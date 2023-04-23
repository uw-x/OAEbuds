#ifndef UTIL_H
#define UTIL_H

#include "arm_const_structs.h"
#include "arm_math.h"

static uint32_t  m_fft_flag             = 0;                            //!< Flag that selects forward (0) or inverse (1) transform.
static uint32_t  m_ifft_flag             = 1;                            //!< Flag that selects forward (0) or inverse (1) transform.

//#define DEBUG_CHANNEL 1
//#define DEBUG_CHANNEL 1
#define CONTINUE_TRACKING 1

#define CONTINUE_TRACKING_WITH_CHANNEL 1
#define CONTINUE_TRACKING_RANGE 12
#define MAX_TRACKING_RANGE 50
#define TRACK_THRESHOLD 0.4
#define TRACK_THRESHOLD2 0.15

#define RATIO_THRESHOLD 3
#define RATIO_THRESHOLD_UP 8
// define parameters for the DATA TYPE 
#define USE_FIXED_POINT 1
#ifdef USE_FIXED_POINT
  #define MIC_TYPE int16_t
  #define DIVIDE_FACTOR 1.0/10
  #define MULTI_FACTOR 1800
#else
  #define MIC_TYPE float32_t
#endif

// define parameters for RECORDING 
#define CHIRP_LEN 2048
//#define CHIRP_LEN_REAL 1025
#define BW_BEGIN 15500//11000
#define BW_END 29800 //21000 
#define FS 62500
#define DUAL_RANGE 4
// define parameters for the correlation
#define MAX_CORR_LEN 4000 
#define USE_FFT_CORR 1 
#define FFT_CORR_LEN 2048
#define seekback_threshold 0.2
#define seekback_sample 960
#define FIX_COARSE_INDEX 300
#define SELF_BEGIN 73 //20

// define parameters for the channel estimation
// #define COMBINE_TWO_PEAK 1
#define CHANNEL_LEN 2048
#define CHANNEL_RESULT_LEN 600
#define OFFSET 100
#define PEAK_THRESHOLD 0.11
#define PEAK_THRESHOLD2 0.02
#define COARSE_BEGIN_INDEX 300
#define GI 1500
#define CHIRP_NUM 1
#define OUTLIER_THRESHOLD 1.1


#define NOISE_BEGIN 1700
#define NOISE_LEN 300

//#define BEGIN_BIN 407 // ROUND(BW1/(FS/Ns)))
//#define END_BIN 777 // ROUND(BW2/(FS/Ns)))

#ifdef USE_FIXED_POINT
#define my_fft arm_cfft_q15
#define my_max arm_max_q15
const static arm_cfft_instance_q15 *p_struct_2048 = &arm_cfft_sR_q15_len2048;
const static arm_cfft_instance_q15 *p_struct_1024 = &arm_cfft_sR_q15_len1024;

#else
const static arm_cfft_instance *p_struct_2048_f32 = &arm_cfft_sR_f32_len2048;
const static arm_cfft_instance *p_struct_1024_f32 = &arm_cfft_sR_f32_len1024;
#define my_fft arm_cfft_f32
#define my_max arm_max_f32
#define my_cmplx_mag arm_cmplx_mag_f32

#endif
const static float32_t avg_filter[9] = {0.0093 ,   0.0476 ,   0.1224   , 0.2022   , 0.2370 ,0.2022  ,  0.1224  ,  0.0476    ,0.0093};

const static float32_t chirp[2048] = {
0.8134, 0.1304, -1.0311, -0.1608, 0.9559, 0.3103, -0.9417, -0.4062, 0.8865, 0.5118, -0.8312, -0.6034, 0.7655, 0.6860, -0.6926, -0.7585, 0.6140, 0.8213, -0.5313, 
-0.8741, 0.4460, 0.9171, -0.3594, -0.9505, 0.2723, 0.9748, -0.1856, -0.9912, 0.1005, 0.9999, -0.0177, -1.0014, -0.0622, 0.9964, 0.1390, -0.9857, -0.2120, 0.9706, 0.2811, 
-0.9512, -0.3457, 0.9281, 0.4062, -0.9021, -0.4625, 0.8738, 0.5144, -0.8444, -0.5619, 0.8136, 0.6051, -0.7822, -0.6447, 0.7505, 0.6805, -0.7190, -0.7126, 0.6886, 0.7411, 
-0.6589, -0.7664, 0.6304, 0.7891, -0.6033, -0.8089, 0.5779, 0.8262, -0.5547, -0.8410, 0.5334, 0.8535, -0.5142, -0.8645, 0.4972, 0.8736, -0.4827, -0.8809, 0.4709, 0.8864, 
-0.4616, -0.8904, 0.4547, 0.8934, -0.4503, -0.8950, 0.4487, 0.8952, -0.4499, -0.8939, 0.4536, 0.8911, -0.4599, -0.8873, 0.4687, 0.8821, -0.4800, -0.8752, 0.4941, 0.8665, 
-0.5105, -0.8558, 0.5291, 0.8437, -0.5499, -0.8294, 0.5727, 0.8126, -0.5978, -0.7933, 0.6246, 0.7712, -0.6527, -0.7465, 0.6821, 0.7186, -0.7124, -0.6873, 0.7438, 0.6524, 
-0.7754, -0.6136, 0.8069, 0.5711, -0.8377, -0.5244, 0.8675, 0.4735, -0.8962, -0.4183, 0.9226, 0.3586, -0.9463, -0.2947, 0.9665, 0.2266, -0.9825, -0.1545, 0.9943, 0.0786, 
-1.0004, 0.0008, 1.0003, -0.0831, -0.9932, 0.1677, 0.9784, -0.2540, -0.9558, 0.3410, 0.9243, -0.4278, -0.8834, 0.5136, 0.8327, -0.5968, -0.7720, 0.6762, 0.7016, -0.7503, 
-0.6211, 0.8177, 0.5309, -0.8771, -0.4315, 0.9266, 0.3238, -0.9647, -0.2090, 0.9897, 0.0882, -1.0004, 0.0368, 0.9959, -0.1642, -0.9746, 0.2916, 0.9360, -0.4169, -0.8794, 
0.5372, 0.8050, -0.6496, -0.7134, 0.7512, 0.6052, -0.8391, -0.4817, 0.9108, 0.3451, -0.9630, -0.1978, 0.9935, 0.0429, -1.0001, 0.1159, 0.9813, -0.2746, -0.9366, 0.4288, 
0.8653, -0.5737, -0.7682, 0.7048, 0.6469, -0.8170, -0.5038, 0.9058, 0.3427, -0.9672, -0.1678, 0.9976, -0.0156, -0.9947, 0.2013, 0.9568, -0.3827, -0.8836, 0.5528, 0.7762, 
-0.7046, -0.6372, 0.8310, 0.4711, -0.9258, -0.2833, 0.9835, 0.0808, -1.0003, 0.1280, 0.9733, -0.3339, -0.9020, 0.5274, 0.7880, -0.6988, -0.6348, 0.8387, 0.4487, -0.9388, 
-0.2376, 0.9924, 0.0115, -0.9950, 0.2181, 0.9443, -0.4386, -0.8411, 0.6376, 0.6892, -0.8026, -0.4957, 0.9227, 0.2707, -0.9890, -0.0266, 0.9954, -0.2221, -0.9396, 0.4595, 
0.8228, -0.6697, -0.6505, 0.8378, 0.4326, -0.9508, -0.1826, 0.9990, -0.0829, -0.9767, 0.3454, 0.8832, -0.5854, -0.7233, 0.7839, 0.5068, -0.9244, -0.2488, 0.9941, -0.0315, 
-0.9851, 0.3120, 0.8956, -0.5696, -0.7308, 0.7820, 0.5023, -0.9293, -0.2281, 0.9969, -0.0689, -0.9761, 0.3626, 0.8664, -0.6258, -0.6752, 0.8328, 0.4185, -0.9622, -0.1191, 
0.9993, -0.1946, -0.9378, 0.4917, 0.7811, -0.7415, -0.5429, 0.9166, 0.2457, -0.9965, 0.0803, 0.9700, -0.4004, -0.8372, 0.6790, 0.6100, -0.8838, -0.3119, 0.9892, -0.0247, 
-0.9806, 0.3611, 0.8561, -0.6572, -0.6276, 0.8760, 0.3207, -0.9887, 0.0286, 0.9785, -0.3770, -0.8436, 0.6799, 0.5984, -0.8964, -0.2725, 0.9957, -0.0922, -0.9616, 0.4473, 
0.7957, -0.7433, -0.5179, 0.9373, 0.1650, -0.9995, 0.2141, 0.9178, -0.5648, -0.7009, 0.8347, 0.3782, -0.9813, 0.0040, 0.9796, -0.3883, -0.8266, 0.7150, 0.5429, -0.9310, 
-0.1707, 0.9995, -0.2315, -0.9057, 0.5986, 0.6620, -0.8689, -0.3059, 0.9944, -0.1044, -0.9510, 0.4995, 0.7426, -0.8100, -0.4025, 0.9794, -0.0115, -0.9743, 0.4261, 0.7923, 
-0.7654, -0.4632, 0.9650, 0.0455, -0.9847, 0.3835, 0.8170, -0.7416, -0.4905, 0.9581, 0.0662, -0.9874, 0.3739, 0.8200, -0.7417, -0.4860, 0.9611, 0.0507, -0.9838, 0.3977, 
0.8018, -0.7654, -0.4496, 0.9726, -0.0008, -0.9720, 0.4536, 0.7600, -0.8096, -0.3793, 0.9882, -0.0882, -0.9462, 0.5384, 0.6892, -0.8681, -0.2723, 0.9991, -0.2103, -0.8971, 
0.6461, 0.5822, -0.9304, -0.1259, 0.9922, -0.3632, -0.8126, 0.7660, 0.4314, -0.9811, 0.0594, 0.9513, -0.5377, -0.6797, 0.8815, 0.2324, -0.9997, 0.2775, 0.8574, -0.7173, 
-0.4882, 0.9692, -0.0131, -0.9620, 0.5135, 0.6940, -0.8764, -0.2344, 0.9993, -0.2925, -0.8445, 0.7402, 0.4510, -0.9802, 0.0729, 0.9409, -0.5784, -0.6293, 0.9180, 0.1322, 
-0.9895, 0.4065, 0.7676, -0.8263, -0.3142, 0.9988, -0.2366, -0.8679, 0.7175, 0.4691, -0.9786, 0.0775, 0.9350, -0.6022, -0.5960, 0.9383, 0.0653, -0.9751, 0.4889, 0.6964, 
-0.8865, -0.1887, 0.9946, -0.3837, -0.7731, 0.8306, 0.2915, -0.9998, 0.2909, 0.8297, -0.7765, -0.3741, 0.9962, -0.2134, -0.8700, 0.7286, 0.4373, -0.9886, 0.1527, 0.8972, 
-0.6903, -0.4823, 0.9805, -0.1098, -0.9140, 0.6639, 0.5103, -0.9746, 0.0850, 0.9224, -0.6507, -0.5222, 0.9723, -0.0786, -0.9235, 0.6515, 0.5183, -0.9742, 0.0905, 0.9174, 
-0.6660, -0.4984, 0.9799, -0.1208, -0.9033, 0.6938, 0.4620, -0.9879, 0.1691, 0.8795, -0.7332, -0.4081, 0.9958, -0.2350, -0.8436, 0.7819, 0.3354, -1.0000, 0.3174, 0.7923, 
-0.8365, -0.2427, 0.9960, -0.4143, -0.7220, 0.8923, 0.1295, -0.9783, 0.5226, 0.6291, -0.9434, 0.0038, 0.9406, -0.6373, -0.5104, 0.9822, -0.1554, -0.8765, 0.7517, 0.3639, 
-1.0000, 0.3209, 0.7797, -0.8567, -0.1896, 0.9872, -0.4932, -0.6454, 0.9410, -0.0093, -0.9342, 0.6619, 0.4709, -0.9918, 0.2259, 0.8325, -0.8132, -0.2578, 0.9954, -0.4484, 
-0.6764, 0.9301, 0.0127, -0.9388, 0.6597, 0.4650, -0.9941, 0.2511, 0.8124, -0.8386, -0.2046, 0.9871, -0.5131, -0.6127, 0.9603, -0.0898, -0.8944, 0.7462, 0.3451, -1.0004, 
0.3936, 0.7091, -0.9187, -0.0267, 0.9384, -0.6725, -0.4362, 0.9984, -0.3121, -0.7639, 0.8864, 0.0960, -0.9586, 0.6288, 0.4821, -0.9944, 0.2740, 0.7855, -0.8731, -0.1180, 
0.9632, -0.6209, -0.4860, 0.9947, -0.2810, -0.7773, 0.8825, 0.0931, -0.9545, 0.6493, 0.4482, -0.9991, 0.3330, 0.7379, -0.9118, -0.0210, 0.9282, -0.7109, -0.3661, 1.0005, 
-0.4271, -0.6611, 0.9527, -0.0984, -0.8740, 0.7971, 0.2354, -0.9856, 0.5567, 0.5373, -0.9897, 0.2622, 0.7773, -0.8920, -0.0531, 0.9348, -0.7083, -0.3569, 0.9996, -0.4612, 
-0.6211, 0.9712, -0.1777, -0.8244, 0.8579, 0.1152, -0.9530, 0.6749, 0.3921, -1.0009, 0.4419, 0.6318, -0.9698, 0.1804, 0.8184, -0.8675, -0.0883, 0.9416, -0.7064, -0.3444, 
0.9976, -0.5016, -0.5713, 0.9873, -0.2699, -0.7567, 0.9165, -0.0279, -0.8922, 0.7939, 0.2092, -0.9739, 0.6308, 0.4286, -1.0014, 0.4393, 0.6199, -0.9779, 0.2316, 0.7757, 
-0.9088, 0.0193, 0.8916, -0.8013, -0.1874, 0.9658, -0.6637, -0.3799, 0.9991, -0.5045, -0.5515, 0.9940, -0.3323, -0.6977, 0.9544, -0.1548, -0.8156, 0.8852, 0.0213, -0.9041, 
0.7919, 0.1903, -0.9634, 0.6802, 0.3477, -0.9949, 0.5553, 0.4899, -1.0009, 0.4225, 0.6149, -0.9843, 0.2864, 0.7214, -0.9486, 0.1508, 0.8094, -0.8970, 0.0190, 0.8791, 
-0.8328, -0.1067, 0.9316, -0.7594, -0.2242, 0.9681, -0.6797, -0.3322, 0.9905, -0.5965, -0.4300, 1.0006, -0.5122, -0.5173, 1.0004, -0.4286, -0.5943, 0.9919, -0.3474, -0.6613, 
0.9767, -0.2698, -0.7188, 0.9566, -0.1970, -0.7674, 0.9332, -0.1298, -0.8080, 0.9083, -0.0686, -0.8416, 0.8828, -0.0138, -0.8691, 0.8579, 0.0346, -0.8912, 0.8344, 0.0762, 
-0.9085, 0.8131, 0.1110, -0.9217, 0.7949, 0.1390, -0.9315, 0.7803, 0.1603, -0.9386, 0.7694, 0.1752, -0.9431, 0.7625, 0.1836, -0.9451, 0.7598, 0.1852, -0.9448, 0.7616, 
0.1803, -0.9423, 0.7678, 0.1689, -0.9378, 0.7780, 0.1509, -0.9305, 0.7920, 0.1264, -0.9200, 0.8094, 0.0951, -0.9060, 0.8301, 0.0569, -0.8880, 0.8534, 0.0121, -0.8654, 
0.8782, -0.0393, -0.8373, 0.9036, -0.0972, -0.8025, 0.9286, -0.1614, -0.7606, 0.9524, -0.2315, -0.7106, 0.9733, -0.3067, -0.6520, 0.9895, -0.3860, -0.5837, 0.9994, -0.4685, 
-0.5051, 1.0011, -0.5528, -0.4161, 0.9932, -0.6370, -0.3167, 0.9734, -0.7187, -0.2074, 0.9395, -0.7954, -0.0886, 0.8900, -0.8649, 0.0382, 0.8234, -0.9236, 0.1708, 0.7392, 
-0.9681, 0.3065, 0.6361, -0.9949, 0.4424, 0.5143, -1.0007, 0.5744, 0.3750, -0.9829, 0.6977, 0.2204, -0.9385, 0.8070, 0.0535, -0.8652, 0.8968, -0.1218, -0.7624, 0.9621, 
-0.2997, -0.6305, 0.9971, -0.4734, -0.4718, 0.9967, -0.6353, -0.2895, 0.9573, -0.7776, -0.0891, 0.8767, -0.8915, 0.1215, 0.7550, -0.9684, 0.3327, 0.5937, -1.0006, 0.5341, 
0.3977, -0.9826, 0.7136, 0.1748, -0.9114, 0.8588, -0.0638, -0.7858, 0.9575, -0.3052, -0.6090, 0.9999, -0.5340, -0.3888, 0.9789, -0.7334, -0.1372, 0.8905, -0.8866, 0.1304, 
0.7359, -0.9787, 0.3949, 0.5220, -0.9987, 0.6350, 0.2621, -0.9389, 0.8286, -0.0253, -0.7987, 0.9557, -0.3170, -0.5852, 1.0010, -0.5864, -0.3136, 0.9539, -0.8060, -0.0064, 
0.8130, -0.9505, 0.3079, 0.5869, -1.0008, 0.5965, 0.2945, -0.9451, 0.8260, -0.0357, -0.7831, 0.9666, -0.3684, -0.5274, 0.9972, -0.6635, -0.2037, 0.9070, -0.8822, 0.1510, 
0.7005, -0.9919, 0.4928, 0.3986, -0.9727, 0.7744, 0.0376, -0.8194, 0.9531, -0.3347, -0.5470, 0.9976, -0.6647, -0.1896, 0.8950, -0.9001, 0.2022, 0.6528, -0.9990, 0.5685, 
0.3030, -0.9390, 0.8484, -0.1020, -0.7226, 0.9901, -0.4956, -0.3790, 0.9625, -0.8087, 0.0368, 0.7626, -0.9806, 0.4519, 0.4199, -0.9725, 0.7878, -0.0076, -0.7780, 0.9765, 
-0.4396, -0.4275, 0.9733, -0.7890, 0.0145, 0.7704, -0.9798, 0.4596, 0.4024, -0.9650, 0.8118, -0.0575, -0.7387, 0.9892, -0.5107, -0.3433, 0.9443, -0.8527, 0.1364, 0.6792, 
-0.9984, 0.5895, 0.2480, -0.9048, 0.9048, -0.2495, -0.5858, 0.9978, -0.6899, -0.1143, 0.8359, -0.9570, 0.3927, 0.4523, -0.9738, 0.8006, -0.0575, -0.7260, 0.9937, -0.5573, 
-0.2731, 0.9099, -0.9049, 0.2627, 0.5638, -0.9941, 0.7274, 0.0477, -0.7891, 0.9798, -0.4883, -0.3423, 0.9349, -0.8792, 0.2155, 0.5967, -0.9967, 0.7107, 0.0638, -0.7939, 
0.9798, -0.4953, -0.3270, 0.9258, -0.8942, 0.2550, 0.5567, -0.9909, 0.7547, -0.0093, -0.7420, 0.9933, -0.5775, -0.2256, 0.8770, -0.9418, 0.3780, 0.4372, -0.9611, 0.8464, 
-0.1707, -0.6175, 0.9972, -0.7188, -0.0328, 0.7624, -0.9909, 0.5701, 0.2235, -0.8705, 0.9496, -0.4104, -0.3950, 0.9437, -0.8808, 0.2484, 0.5438, -0.9851, 0.7923, -0.0908, 
-0.6685, 0.9992, -0.6914, -0.0574, 0.7690, -0.9913, 0.5842, 0.1927, -0.8472, 0.9663, -0.4762, -0.3133, 0.9053, -0.9292, 0.3714, 0.4183, -0.9463, 0.8846, -0.2728, -0.5078, 
0.9733, -0.8363, 0.1830, 0.5827, -0.9892, 0.7877, -0.1033, -0.6438, 0.9970, -0.7417, 0.0348, 0.6927, -0.9993, 0.7002, 0.0220, -0.7306, 0.9983, -0.6652, -0.0673, 0.7587, 
-0.9956, 0.6377, 0.1004, -0.7782, 0.9930, -0.6185, -0.1218, 0.7896, -0.9911, 0.6086, 0.1316, -0.7939, 0.9905, -0.6078, -0.1294, 0.7908, -0.9917, 0.6164, 0.1159, -0.7804, 
0.9938, -0.6341, -0.0903, 0.7624, -0.9967, 0.6603, 0.0530, -0.7356, 0.9989, -0.6944, -0.0039, 0.6994, -0.9990, 0.7349, -0.0572, -0.6523, 0.9953, -0.7804, 0.1294, 0.5931, 
-0.9848, 0.8288, -0.2128, -0.5206, 0.9655, -0.8772, 0.3059, 0.4333, -0.9342, 0.9228, -0.4067, -0.3308, 0.8875, -0.9613, 0.5133, 0.2126, -0.8230, 0.9885, -0.6214, -0.0794, 
0.7372, -0.9997, 0.7271, -0.0668, -0.6284, 0.9891, -0.8247, 0.2234, 0.4956, -0.9523, 0.9071, -0.3852, -0.3385, 0.8845, -0.9675, 0.5456, 0.1599, -0.7817, 0.9977, -0.6969, 
0.0360, 0.6429, -0.9900, 0.8285, -0.2422, -0.4678, 0.9383, -0.9296, 0.4482, 0.2604, -0.8366, 0.9892, -0.6418, -0.0287, 0.6840, -0.9955, 0.8082, -0.2166, -0.4827, 0.9407, 
-0.9307, 0.4592, 0.2395, -0.8194, 0.9944, -0.6796, 0.0314, 0.6317, -0.9853, 0.8573, -0.3113, -0.3856, 0.8945, -0.9698, 0.5760, 0.0956, -0.7207, 0.9984, -0.7972, 0.2145, 
0.4704, -0.9305, 0.9469, -0.5139, -0.1623, 0.7613, -1.0006, 0.7677, -0.1742, -0.5003, 0.9401, -0.9405, 0.5017, 0.1702, -0.7621, 1.0004, -0.7759, 0.1930, 0.4783, -0.9289, 
0.9528, -0.5407, -0.1184, 0.7231, -0.9979, 0.8191, -0.2696, -0.4016, 0.8911, -0.9785, 0.6259, 0.0069, -0.6361, 0.9808, -0.8878, 0.3997, 0.2652, -0.8119, 0.9995, -0.7459, 
0.1639, 0.4895, -0.9274, 0.9596, -0.5728, -0.0635, 0.6716, -0.9874, 0.8759, -0.3861, -0.2699, 0.8093, -1.0003, 0.7631, -0.2001, -0.4481, 0.9051, -0.9768, 0.6348, -0.0248, 
-0.5953, 0.9644, -0.9274, 0.5020, 0.1329, -0.7119, 0.9942, -0.8623, 0.3733, 0.2696, -0.8008, 1.0018, -0.7901, 0.2548, 0.3842, -0.8657, 0.9943, -0.7178, 0.1506, 0.4769, 
-0.9113, 0.9782, -0.6510, 0.0631, 0.5494, -0.9418, 0.9588, -0.5937, -0.0064, 0.6032, -0.9612, 0.9403, -0.5488, -0.0575, 0.6404, -0.9727, 0.9257, -0.5181, -0.0900, 0.6625, 
-0.9785, 0.9173, -0.5028, -0.1041, 0.6703, -0.9800, 0.9162, -0.5034, -0.0998, 0.6644, -0.9775, 0.9224, -0.5198, -0.0771, 0.6444, -0.9705, 0.9352, -0.5516, -0.0359, 0.6093, 
-0.9573, 0.9528, -0.5976, 0.0239, 0.5578, -0.9354, 0.9725, -0.6557, 0.1019, 0.4880, -0.9013, 0.9904, -0.7231, 0.1975, 0.3980, -0.8511, 1.0014, -0.7957, 0.3089, 0.2863, 
-0.7802, 0.9997, -0.8679, 0.4330, 0.1524, -0.6843, 0.9782, -0.9324, 0.5647, -0.0029, -0.5595, 0.9295, -0.9805, 0.6969, -0.1763, -0.4038, 0.8465, -1.0020, 0.8197, -0.3617, 
-0.2174, 0.7231, -0.9863, 0.9208, -0.5493, -0.0042, 0.5556, -0.9228, 0.9861, -0.7254, 0.2273, 0.3445, -0.8032, 1.0004, -0.8729, 0.4629, 0.0958, -0.6230, 0.9497, -0.9717, 
0.6831, -0.1773, -0.3844, 0.8236, -1.0016, 0.8633, -0.4537, -0.0981, 0.6185, -0.9450, 0.9766, -0.7050, 0.2147, 0.3412, -0.7911, 0.9971, -0.8972, 0.5224, 0.0112, -0.5408, 
0.9054, -0.9956, 0.7844, -0.3373, -0.2106, 0.6947, -0.9707, 0.9564, -0.6579, 0.1645, 0.3770, -0.8067, 0.9980, -0.8963, 0.5321, -0.0130, -0.5093, 0.8828, -1.0001, 0.8282, 
-0.4177, -0.1124, 0.6095, -0.9317, 0.9877, -0.7626, 0.3216, 0.2100, -0.6815, 0.9607, -0.9697, 0.7075, -0.2478, -0.2801, 0.7295, -0.9763, 0.9533, -0.6675, 0.1989, 0.3236, 
-0.7570, 0.9837, -0.9425, 0.6462, -0.1756, -0.3417, 0.7664, -0.9850, 0.9402, -0.6448, 0.1784, 0.3347, -0.7585, 0.9818, -0.9467, 0.6635, -0.2072, -0.3024, 0.7327, -0.9725, 
0.9604, -0.7009, 0.2615, 0.2442, -0.6868, 0.9537, -0.9778, 0.7540, -0.3401, -0.1591, 0.6174, -0.9204, 0.9930, -0.8180, 0.4400, 0.0463, -0.5205, 0.8658, -0.9979, 0.8854, 
-0.5570, 0.0933, 0.3923, -0.7821, 0.9826, -0.9463, 0.6830, -0.2566, -0.2302, 0.6616, -0.9354, 0.9875, -0.8068, 0.4367, 0.0353, -0.4981, 0.8442, -0.9937, 0.9127, -0.6210, 
0.1869, 0.2894, -0.6988, 0.9479, -0.9811, 0.7917, -0.4234, -0.0396, 0.4929, -0.8352, 0.9901, -0.9243, 0.6533, -0.2382, -0.2289, 0.6447, -0.9184, 0.9909, -0.8471, 0.5194, 
-0.0798, -0.3763, 0.7507, -0.9631, 0.9690, -0.7683, 0.4044, 0.0446, -0.4833, 0.8195, -0.9829, 0.9401, -0.7013, 0.3169, 0.1327, -0.5538, 0.8600, -0.9892, 0.9153, -0.6546, 
0.2614, 0.1843, -0.5920, 0.8793, -0.9896, 0.9015, -0.6334, 0.2399, 0.2004, -0.6005, 0.8813, -0.9883, 0.9019, -0.6394, 0.2529, 0.1816, -0.5803, 0.8667, -0.9857, 0.9160, 
-0.6719, 0.3002, 0.1276, -0.5302, 0.8325, -0.9779, 0.9399, -0.7272, 0.3797, 0.0377, -0.4469, 0.7731, -0.9574, 0.9660, -0.7987, 0.4872, -0.0879, -0.3264, 0.6809, -0.9132, 
0.9820, -0.8758, 0.6150, -0.2462, -0.1655, 0.5470, -0.8320, 0.9720, -0.9426, 0.7503, -0.4294, 0.0351, 0.3643, -0.7004, 0.9171, -0.9780, 0.8732, -0.6224, 0.2677, 0.1313, 
-0.5071, 0.7980, -0.9569, 0.9574, -0.8009, 0.5142, -0.1439, -0.2487, 0.6000, -0.8541, 0.9705, -0.9309, 0.7437, -0.4385, 0.0644, 0.3186, -0.6507, 0.8806, -0.9721, 0.9125, 
-0.7120, 0.4017, -0.0307, -0.3439, 0.6656, -0.8852, 0.9699, -0.9087, 0.7107, -0.4066, 0.0430, 0.3263, -0.6466, 0.8703, -0.9658, 0.9198, -0.7393, 0.4524, -0.1006, -0.2651, 
0.5915, -0.8323, 0.9545, -0.9403, 0.7932, -0.5350, 0.2020, 0.1582, -0.4952, 0.7631, -0.9246, 0.9580, -0.8607, 0.6457, -0.3433, -0.0045, 0.3509, -0.6494, 0.8598, -0.9551, 
0.9235, -0.7691, 0.5145, -0.1928, -0.1535, 0.4785, -0.7405, 0.9066, -0.9551, 0.8812, -0.6954, 0.4211, -0.0947, -0.2426, 0.5489, -0.7855, 0.9233, -0.9469, 0.8530, -0.6544, 
0.3766, -0.0533, -0.2755, 0.5696, -0.7947, 0.9238, -0.9415, 0.8481, -0.6540, 0.3832, -0.0687, -0.2532, 0.5449, -0.7720, 0.9096, -0.9423, 0.8664, -0.6928, 0.4407, -0.1394, 
-0.1763, 0.4713, -0.7133, 0.8747, -0.9392, 0.9002, -0.7621, 0.5419, -0.2634, -0.0431, 0.3436, -0.6062, 0.8038, -0.9148, 0.9289, -0.8453, 0.6727, -0.4312, 0.1454, 0.1547, 
-0.4376, 0.6746, -0.8426, 0.9238, -0.9115, 0.8078, -0.6229, 0.3771, -0.0946, -0.1966, 0.4672, -0.6910, 0.8473, -0.9203, 0.9044, -0.8019, 0.6225, -0.3850, 0.1118, 0.1713, 
-0.4370, 0.6608, -0.8230, 0.9080, -0.9092, 0.8274, -0.6698, 0.4526, -0.1952, -0.0790, 0.3449, -0.5791, 0.7616, -0.8759, 0.9131, -0.8706, 0.7522, -0.5699, 0.3390, -0.0799, 
-0.1849, 0.4330, -0.6439, 0.7997, -0.8884, 0.9032, -0.8427, 0.7140, -0.5271, 0.2979, -0.0458, -0.2092, 0.4465, -0.6470, 0.7957, -0.8811, 0.8966, -0.8427, 0.7233, -0.5484, 
0.3325, -0.0917, -0.1550, 0.3888, -0.5927, 0.7513, -0.8530, 0.8918, -0.8644, 0.7739, -0.6276, 0.4361, -0.2143, -0.0219, 0.2557, -0.4703, 0.6507, -0.7851, 0.8639, -0.8826, 
0.8405, -0.7406, 0.5911, -0.4020, 0.1866, 0.0402, -0.2634, 0.4683, -0.6412, 0.7715, -0.8510, 0.8746, -0.8424, 0.7561, -0.6220, 0.4494, -0.2490, 0.0342, 0.1818, -0.3856, 
0.5648, -0.7084, 0.8087, -0.8595, 0.8585, -0.8064, 0.7064, -0.5657, 0.3923, -0.1968, -0.0090, 0.2133, -0.4045, 0.5717, -0.7058, 0.7998, -0.8483, 0.8501, -0.8047, 0.7155, 
-0.5880, 0.4290, -0.2481, 0.0547, 0.1406, -0.3275, 0.4962, -0.6384, 0.7468, -0.8162, 0.8437, -0.8280, 0.7711, -0.6756, 0.5470, -0.3922, 0.2188, -0.0358, -0.1480, 0.3237, 
-0.4831, 0.6185, -0.7242, 0.7954, -0.8291, 0.8245, -0.7818, 0.7040, -0.5946, 0.4592, -0.3040, 0.1361, 0.0367, -0.2071, 0.3674, -0.5110, 0.6319, -0.7254, 0.7876, -0.8165, 
0.8113, -0.7725, 0.7025, -0.6041, 0.4820, -0.3412, 0.1877, -0.0277, -0.1325, 0.2865, -0.4287, 0.5534, -0.6563, 0.7339, -0.7834, 0.8035, -0.7937, 0.7550, -0.6889, 0.5985, 
-0.4871, 0.3592, -0.2194, 0.0726, 0.0755, -0.2203, 0.3565, -0.4797, 0.5862, -0.6723, 0.7356, -0.7744, 0.7877, -0.7754, 0.7385, -0.6782, 0.5971, -0.4977, 0.3836, -0.2586, 
0.1263, 0.0087, -0.1426, 0.2715, -0.3912, 0.4989, -0.5914, 0.6662, -0.7216, 0.7562, -0.7694, 0.7613, -0.7321, 0.6833, -0.6165, 0.5334, -0.4371, 0.3298, -0.2146, 0.0950, 
0.0265, -0.1462, 0.2614, -0.3695, 0.4673, -0.5532, 0.6251, -0.6813, 0.7212, -0.7437, 0.7486, -0.7365, 0.7074, -0.6627, 0.6035, -0.5312, 0.4481, -0.3557, 0.2563, -0.1525, 
0.0460, 0.0604, -0.1646, 0.2650, -0.3588, 0.4449, -0.5215, 0.5870, -0.6409, 0.6818, -0.7094, 0.7237, -0.7240, 0.7113, -0.6857, 0.6478, -0.5990, 0.5387, -0.4684, 0.3885, 
-0.2992, 0.2011, -0.0929, -0.0266, 0.1631, -0.3363, 0.0000, 0.0000, 0.0000, 
};




/*
const static float32_t chirp[1024] = {
1.0000, -0.5362, -0.4242, 0.9916, -0.6427, -0.2988, 0.9646, -0.7432, -0.1603, 0.9164, -0.8335, -0.0109, 0.8448, -0.9089, 0.1465, 0.7485, -0.9646, 0.3076, 0.6270, 
-0.9954, 0.4671, 0.4809, -0.9966, 0.6187, 0.3127, -0.9642, 0.7551, 0.1264, -0.8950, 0.8686, -0.0723, -0.7875, 0.9511, -0.2756, -0.6421, 0.9948, -0.4740, -0.4619, 0.9931, 
-0.6565, -0.2525, 0.9411, -0.8112, -0.0226, 0.8364, -0.9261, 0.2160, 0.6799, -0.9900, 0.4491, 0.4768, -0.9938, 0.6606, 0.2364, -0.9313, 0.8333, -0.0275, -0.8012, 0.9510, 
-0.2968, -0.6075, 0.9994, -0.5505, -0.3604, 0.9686, -0.7658, -0.0767, 0.8547, -0.9205, 0.2210, 0.6615, -0.9953, 0.5057, 0.4012, -0.9768, 0.7481, 0.0951, -0.8598, 0.9200, 
-0.2281, -0.6494, 0.9974, -0.5340, -0.3627, 0.9648, -0.7859, -0.0277, 0.8185, -0.9498, 0.3178, 0.5688, -0.9993, 0.6306, 0.2411, -0.9202, 0.8669, -0.1253, -0.7151, 0.9891, 
-0.4817, -0.4052, 0.9726, -0.7753, -0.0300, 0.8113, -0.9579, 0.3569, 0.5217, -0.9941, 0.6945, 0.1431, -0.8694, 0.9239, -0.2662, -0.5959, 0.9997, -0.6367, -0.2134, 0.8999, 
-0.8995, 0.2143, 0.6333, -0.9999, 0.6090, 0.2420, -0.9098, 0.8918, -0.2032, -0.6374, 0.9999, -0.6143, -0.2297, 0.9019, -0.9027, 0.2332, 0.6087, -0.9996, 0.6520, 0.1760, 
-0.8740, 0.9294, -0.3034, -0.5443, 0.9937, -0.7181, -0.0800, 0.8194, -0.9640, 0.4106, 0.4391, -0.9715, 0.8041, -0.0589, -0.7280, 0.9930, -0.5482, -0.2875, 0.9178, -0.8953, 
0.2377, 0.5878, -0.9972, 0.7027, 0.0863, -0.8142, 0.9702, -0.4468, -0.3886, 0.9523, -0.8524, 0.1601, 0.6428, -0.9999, 0.6657, 0.1275, -0.8323, 0.9646, -0.4350, -0.3920, 
0.9505, -0.8602, 0.1844, 0.6162, -0.9983, 0.7043, 0.0653, -0.7903, 0.9828, -0.5149, -0.2979, 0.9107, -0.9148, 0.3090, 0.5019, -0.9789, 0.8067, -0.1009, -0.6709, 1.0000, 
-0.6712, -0.0980, 0.8024, -0.9815, 0.5199, 0.2799, -0.8972, 0.9318, -0.3630, -0.4399, 0.9585, -0.8596, 0.2085, 0.5758, -0.9910, 0.7729, -0.0622, -0.6874, 1.0000, -0.6786, 
-0.0717, 0.7761, -0.9911, 0.5828, 0.1908, -0.8443, 0.9697, -0.4901, -0.2941, 0.8950, -0.9405, 0.4041, 0.3814, -0.9312, 0.9079, -0.3274, -0.4532, 0.9561, -0.8753, 0.2617, 
0.5104, -0.9724, 0.8456, -0.2083, -0.5540, 0.9825, -0.8209, 0.1678, 0.5850, -0.9883, 0.8029, -0.1407, -0.6044, 0.9912, -0.7925, 0.1270, 0.6126, -0.9921, 0.7904, -0.1270, 
-0.6099, 0.9912, -0.7967, 0.1407, 0.5961, -0.9883, 0.8110, -0.1678, -0.5710, 0.9825, -0.8325, 0.2083, 0.5338, -0.9724, 0.8600, -0.2617, -0.4835, 0.9561, -0.8914, 0.3274, 
0.4192, -0.9312, 0.9244, -0.4041, -0.3397, 0.8950, -0.9558, 0.4901, 0.2445, -0.8443, 0.9816, -0.5828, -0.1332, 0.7761, -0.9974, 0.6786, 0.0064, -0.6874, 0.9981, -0.7729, 
0.1340, 0.5758, -0.9780, 0.8596, -0.2851, -0.4399, 0.9318, -0.9318, 0.4416, 0.2799, -0.8542, 0.9815, -0.5968, -0.0980, 0.7413, -1.0000, 0.7416, -0.1009, -0.5910, 0.9789, 
-0.8649, 0.3090, 0.4039, -0.9107, 0.9546, -0.5149, -0.1845, 0.7903, -0.9979, 0.7043, -0.0583, -0.6162, 0.9829, -0.8602, 0.3108, 0.3920, -0.9004, 0.9646, -0.5543, -0.1275, 
0.7462, -0.9999, 0.7661, -0.1601, -0.5230, 0.9523, -0.9214, 0.4468, 0.2421, -0.8142, 0.9963, -0.7027, 0.0750, 0.5878, -0.9713, 0.8953, -0.3971, -0.2875, 0.8364, -0.9930, 
0.6856, -0.0589, -0.5946, 0.9715, -0.8984, 0.4106, 0.2658, -0.8194, 0.9968, -0.7181, 0.1121, 0.5443, -0.9529, 0.9294, -0.4860, -0.1760, 0.7582, -0.9996, 0.7934, -0.2332, 
-0.4303, 0.9019, -0.9733, 0.6143, 0.0153, -0.6374, 0.9791, -0.8918, 0.4150, 0.2420, -0.7932, 0.9999, -0.7739, 0.2143, 0.4369, -0.8999, 0.9770, -0.6367, 0.0255, 0.5959, 
-0.9639, 0.9239, -0.4941, -0.1431, 0.7195, -0.9941, 0.8531, -0.3569, -0.2871, 0.8113, -0.9996, 0.7753, -0.2324, -0.4052, 0.8763, -0.9891, 0.6990, -0.1253, -0.4985, 0.9202, 
-0.9705, 0.6306, -0.0382, -0.5688, 0.9482, -0.9498, 0.5746, 0.0277, -0.6184, 0.9648, -0.9319, 0.5340, 0.0722, -0.6494, 0.9736, -0.9200, 0.5107, 0.0951, -0.6636, 0.9768, 
-0.9160, 0.5057, 0.0966, -0.6615, 0.9753, -0.9205, 0.5191, 0.0767, -0.6431, 0.9686, -0.9328, 0.5505, 0.0354, -0.6075, 0.9549, -0.9510, 0.5984, -0.0275, -0.5528, 0.9313, 
-0.9717, 0.6606, -0.1116, -0.4768, 0.8935, -0.9900, 0.7333, -0.2160, -0.3773, 0.8364, -0.9997, 0.8112, -0.3382, -0.2525, 0.7544, -0.9931, 0.8869, -0.4740, -0.1020, 0.6421, 
-0.9613, 0.9511, -0.6163, 0.0723, 0.4955, -0.8950, 0.9920, -0.7551, 0.2652, 0.3127, -0.7857, 0.9966, -0.8768, 0.4671, 0.0961, -0.6270, 0.9515, -0.9646, 0.6631, -0.1465, 
-0.4169, 0.8448, -0.9999, 0.8335, -0.4002, -0.1603, 0.6691, -0.9646, 0.9543, -0.6427, 0.1292, 0.4242, -0.8441, 1.0000, -0.8446, 0.4273, 0.1215, -0.6321, 0.9477, -0.9723, 
0.6997, -0.2143, -0.3356, 0.7830, -0.9934, 0.9044, -0.5440, 0.0214, 0.5070, -0.8838, 0.9979, -0.8169, 0.3953, 0.1419, -0.6367, 0.9449, -0.9775, 0.7263, -0.2652, -0.2717, 
0.7297, -0.9778, 0.9461, -0.6448, 0.1607, 0.3681, -0.7923, 0.9929, -0.9146, 0.5806, -0.0852, -0.4331, 0.8307, -0.9983, 0.8908, -0.5389, 0.0402, 0.4688, -0.8496, 0.9996, 
-0.8793, 0.5225, -0.0260, -0.4768, 0.8516, -0.9995, 0.8823, -0.5323, 0.0426, 0.4575, -0.8372, 0.9980, -0.8993, 0.5677, -0.0901, -0.4099, 0.8041, -0.9921, 0.9270, -0.6266, 
0.1680, 0.3323, -0.7482, 0.9760, -0.9596, 0.7043, -0.2747, -0.2222, 0.6636, -0.9412, 0.9880, -0.7936, 0.4065, 0.0785, -0.5437, 0.8774, -1.0000, 0.8833, -0.5563, 0.0978, 
0.3832, -0.7730, 0.9805, -0.9580, 0.7119, -0.3006, -0.1797, 0.6177, -0.9128, 0.9980, -0.8549, 0.5173, -0.0627, -0.4052, 0.7811, -0.9808, 0.9607, -0.7263, 0.3308, 0.1373, 
-0.5743, 0.8842, -0.9999, 0.8971, -0.5992, 0.1719, 0.2918, -0.6918, 0.9429, -0.9920, 0.8298, -0.4918, 0.0505, 0.4007, -0.7671, 0.9724, -0.9748, 0.7749, -0.4150, -0.0297, 
0.4676, -0.8090, 0.9850, -0.9608, 0.7422, -0.3745, -0.0678, 0.4957, -0.8241, 0.9883, -0.9568, 0.7368, -0.3726, -0.0638, 0.4870, -0.8149, 0.9847, -0.9646, 0.7594, -0.4095, 
-0.0177, 0.4408, -0.7799, 0.9715, -0.9807, 0.8067, -0.4830, 0.0704, 0.3544, -0.7133, 0.9409, -0.9964, 0.8708, -0.5878, 0.1994, 0.2241, -0.6067, 0.8805, -0.9976, 0.9381, 
-0.7136, 0.3645, 0.0477, -0.4507, 0.7749, -0.9648, 0.9886, -0.8431, 0.5543, -0.1719, -0.2387, 0.6084, -0.8754, 0.9957, -0.9501, 0.7473, -0.4217, 0.0275, 0.3705, -0.7073, 
0.9287, -0.9997, 0.9097, -0.6743, 0.3317, 0.0628, -0.4466, 0.7593, -0.9523, 0.9962, -0.8851, 0.6372, -0.2916, -0.0980, 0.4719, -0.7732, 0.9567, -0.9955, 0.8847, -0.6418, 
0.3038, 0.0785, -0.4484, 0.7516, -0.9442, 0.9988, -0.9085, 0.6872, -0.3676, -0.0039, 0.3741, -0.6904, 0.9086, -0.9985, 0.9486, -0.7666, 0.4787, -0.1253, -0.2445, 0.5800, 
-0.8358, 0.9778, -0.9875, 0.8646, -0.6263, 0.3053, 0.0555, -0.4082, 0.7065, -0.9118, 0.9981, -0.9551, 0.7892, -0.5225, 0.1897, 0.1664, -0.5006, 0.7711, -0.9445, 0.9998, 
-0.9310, 0.7475, -0.4726, 0.1407, 0.2077, -0.5300, 0.7878, -0.9505, 0.9995, -0.9298, 0.7504, -0.4833, 0.1603, 0.1806, -0.4998, 0.7606, -0.9335, 0.9996, -0.9521, 0.7972, 
-0.5531, 0.2477, 0.0844, -0.4064, 0.6828, -0.8838, 0.9879, -0.9847, 0.8753, -0.6723, 0.3980, -0.0821, -0.2416, 0.5391, -0.7795, 0.9383, -0.9995, 0.9578, -0.8181, 0.5955, 
-0.3132, 0.0000, 0.3123, -0.5927, 0.8136, -0.9537, 1.0000, -0.9485, 0.8052, -0.5846, 0.3085, -0.0037, -0.3007, 0.5758, -0.7962, 0.9416, -0.9993, 0.9646, -0.8414, 0.6418, 
-0.3844, 0.0931, 0.2057, -0.4854, 0.7212, -0.8928, 0.9855, -0.9921, 0.9126, -0.7546, 0.5325, -0.2655, -0.0231, 0.3090, -0.5682, 0.7794, -0.9254, 0.9949, -0.9828, 0.8909, 
-0.7272, 0.5057, -0.2444, -0.0356, 0.3119, -0.5629, 0.7693, -0.9155, 0.9908, -0.9900, 0.9140, -0.7691, 0.5669, -0.3230, 0.0559, 0.2145, -0.4684, 0.6874, -0.8560, 0.9625, 
-1.0000, 0.9664, -0.8647, 0.7027, -0.4924, 0.2487, 0.0114, -0.2698, 0.5091, -0.7133, 0.8691, -0.9667, 1.0000, -0.9676, 0.8722, -0.7207, 0.5233, -0.2931, 0.0451, 0.2049, 
-0.4413, 0.6494, -0.8168, 0.9334, -0.9928, 0.9920, -0.9315, 0.8157, -0.6520, 0.4505, -0.2233, -0.0160, 0.2535, -0.4757, 0.6702, -0.8261, 0.9353, -0.9921, 0.9940, -0.9415, 
0.8379, -0.6895, 0.5048, -0.2938, 0.0681, 0.1603, -0.3796, 0.5784, -0.7469, 0.8768, -0.9619, 0.9986, -0.9855, 0.9239, -0.8173, 0.6714, -0.4937, 0.2931, -0.0794, -0.1373, 
0.3466, -0.5391, 0.7061, -0.8402, 0.9358, -0.9890, 0.9980, -0.9629, 0.8858, -0.7705, 0.6225, -0.4485, 0.2562, -0.0540, -0.1497, 0.3463, -0.5280, 0.6874, -0.8185, 0.9163, 
-0.9774, 0.9999, -0.9834, 0.9290, -0.8393, 0.7181, -0.5705, 0.4023, -0.2200, 0.0304, 0.1594, -0.3427, 0.5129, -0.6643, 0.7917, -0.8911, 0.9595, -0.9949, 0.9966, -0.9650, 
0.9016, -0.8090, 0.6906, -0.5505, 0.3935, -0.2248, 0.0500, 0.1256, -0.2964, 0.4575, -0.6040, 0.7318, -0.8375, 0.9181, -0.9719, 0.9977, -0.9950, 0.9646, -0.9075, 0.8258, 
-0.7222, 0.5996, -0.4618, 0.3125, -0.1559, -0.0039, 0.1628, -0.3167, 0.4619, -0.5949, 0.7127, -0.8126, 0.8926, -0.9511, 0.9870, -1.0000, 0.9900, -0.9578, 0.9044, -0.8313, 
0.7406, -0.6344, 0.5153, -0.3861, 0.2496, -0.1088, -0.0334, 0.1741, -0.3105, 0.4399, -0.5601, 0.6688, -0.7643, 0.8448, -0.9094, 0.9570, -0.9871, 0.9996, -0.9945, 0.9723, 
-0.9337, 0.8796, -0.8113, 0.7301, -0.6378, 
};


*/

#define FFT_FLAG 0
#define IFFT_FLAG 1
static uint32_t  m_do_bit_reverse = 1;                            //!< Flag that enables (1) or disables (0) bit reversal of output.

void init_chirp_fft();

void real_to_complex(const MIC_TYPE * real_input, MIC_TYPE* complex_output, uint16_t size_input);
void complex_to_real(const MIC_TYPE * complex_input, MIC_TYPE* real_output, uint16_t size_real);

void reset_tracking();


float32_t Complex_power(float32_t real, float32_t imag);
void estimate_H( const float32_t* X, MIC_TYPE * Y, uint16_t fft_begin, uint16_t fft_end);

void channel_estimation_freq(const MIC_TYPE * rx, float32_t* channel_result, uint16_t sig_len, uint16_t left_right);


void detection_phase_left(MIC_TYPE* recv_signal, uint16_t sig_len);
void detection_phase_right(MIC_TYPE* recv_signal, uint16_t sig_len);
uint16_t detection_phase_combine(uint16_t I_am_master, uint16_t use_dual);

#endif