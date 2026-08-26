#include <math.h>

void compute(const double* input, double* output)
{
	double temp = 0.0;
	// 计算第 0 个SFI多项式
	temp = 0.0;
		temp += input[0];
		temp += input[1];
		temp += input[2];
		temp += input[3];
		temp += input[4];
		temp += input[5];
	output[0] = temp;
	// 计算第 1 个SFI多项式
	temp = 0.0;
		temp += pow(input[0], 2);
		temp += pow(input[1], 2);
		temp += pow(input[2], 2);
		temp += pow(input[3], 2);
		temp += pow(input[4], 2);
		temp += pow(input[5], 2);
	output[1] = temp;
	// 计算第 2 个SFI多项式
	temp = 0.0;
		temp += pow(input[0], 3);
		temp += pow(input[1], 3);
		temp += pow(input[2], 3);
		temp += pow(input[3], 3);
		temp += pow(input[4], 3);
		temp += pow(input[5], 3);
	output[2] = temp;
	// 计算第 3 个SFI多项式
	temp = 0.0;
		temp += pow(input[0], 4);
		temp += pow(input[1], 4);
		temp += pow(input[2], 4);
		temp += pow(input[3], 4);
		temp += pow(input[4], 4);
		temp += pow(input[5], 4);
	output[3] = temp;
	// 计算第 4 个SFI多项式
	temp = 0.0;
		temp += (1.0 / input[0]);
		temp += (1.0 / input[1]);
		temp += (1.0 / input[2]);
		temp += (1.0 / input[3]);
		temp += (1.0 / input[4]);
		temp += (1.0 / input[5]);
	output[4] = temp;
	// 计算第 5 个SFI多项式
	temp = 0.0;
		temp += (1.0 / pow(input[0], 2));
		temp += (1.0 / pow(input[1], 2));
		temp += (1.0 / pow(input[2], 2));
		temp += (1.0 / pow(input[3], 2));
		temp += (1.0 / pow(input[4], 2));
		temp += (1.0 / pow(input[5], 2));
	output[5] = temp;
	// 计算第 6 个SFI多项式
	temp = 0.0;
		temp += (1.0 / pow(input[0], 3));
		temp += (1.0 / pow(input[1], 3));
		temp += (1.0 / pow(input[2], 3));
		temp += (1.0 / pow(input[3], 3));
		temp += (1.0 / pow(input[4], 3));
		temp += (1.0 / pow(input[5], 3));
	output[6] = temp;
	// 计算第 7 个SFI多项式
	temp = 0.0;
		temp += (1.0 / pow(input[0], 4));
		temp += (1.0 / pow(input[1], 4));
		temp += (1.0 / pow(input[2], 4));
		temp += (1.0 / pow(input[3], 4));
		temp += (1.0 / pow(input[4], 4));
		temp += (1.0 / pow(input[5], 4));
	output[7] = temp;
	// 计算第 8 个SFI多项式
	temp = 0.0;
		temp += exp(-1.0 * input[0]);
		temp += exp(-1.0 * input[1]);
		temp += exp(-1.0 * input[2]);
		temp += exp(-1.0 * input[3]);
		temp += exp(-1.0 * input[4]);
		temp += exp(-1.0 * input[5]);
	output[8] = temp;
	// 计算第 9 个SFI多项式
	temp = 0.0;
		temp += exp(-2.0 * input[0]);
		temp += exp(-2.0 * input[1]);
		temp += exp(-2.0 * input[2]);
		temp += exp(-2.0 * input[3]);
		temp += exp(-2.0 * input[4]);
		temp += exp(-2.0 * input[5]);
	output[9] = temp;
	// 计算第 10 个SFI多项式
	temp = 0.0;
		temp += exp(-1.0 * input[0] * input[0]);
		temp += exp(-1.0 * input[1] * input[1]);
		temp += exp(-1.0 * input[2] * input[2]);
		temp += exp(-1.0 * input[3] * input[3]);
		temp += exp(-1.0 * input[4] * input[4]);
		temp += exp(-1.0 * input[5] * input[5]);
	output[10] = temp;
	// 计算第 11 个SFI多项式
	temp = 0.0;
		temp += exp(-2.0 * input[0] * input[0]);
		temp += exp(-2.0 * input[1] * input[1]);
		temp += exp(-2.0 * input[2] * input[2]);
		temp += exp(-2.0 * input[3] * input[3]);
		temp += exp(-2.0 * input[4] * input[4]);
		temp += exp(-2.0 * input[5] * input[5]);
	output[11] = temp;
	// 计算第 12 个SFI多项式
	temp = 0.0;
		temp += cos(1.0 * input[0]);
		temp += cos(1.0 * input[1]);
		temp += cos(1.0 * input[2]);
		temp += cos(1.0 * input[3]);
		temp += cos(1.0 * input[4]);
		temp += cos(1.0 * input[5]);
	output[12] = temp;
	// 计算第 13 个SFI多项式
	temp = 0.0;
		temp += cos(2.0 * input[0]);
		temp += cos(2.0 * input[1]);
		temp += cos(2.0 * input[2]);
		temp += cos(2.0 * input[3]);
		temp += cos(2.0 * input[4]);
		temp += cos(2.0 * input[5]);
	output[13] = temp;
	// 计算第 14 个SFI多项式
	temp = 0.0;
		temp += sin(1.0 * input[0]);
		temp += sin(1.0 * input[1]);
		temp += sin(1.0 * input[2]);
		temp += sin(1.0 * input[3]);
		temp += sin(1.0 * input[4]);
		temp += sin(1.0 * input[5]);
	output[14] = temp;
	// 计算第 15 个SFI多项式
	temp = 0.0;
		temp += sin(2.0 * input[0]);
		temp += sin(2.0 * input[1]);
		temp += sin(2.0 * input[2]);
		temp += sin(2.0 * input[3]);
		temp += sin(2.0 * input[4]);
		temp += sin(2.0 * input[5]);
	output[15] = temp;
	// 计算第 16 个SFI多项式
	temp = 0.0;
		temp += input[0] * input[1];
		temp += input[0] * input[2];
		temp += input[0] * input[3];
		temp += input[0] * input[4];
		temp += input[1] * input[2];
		temp += input[1] * input[3];
		temp += input[1] * input[5];
		temp += input[2] * input[4];
		temp += input[2] * input[5];
		temp += input[3] * input[4];
		temp += input[3] * input[5];
		temp += input[4] * input[5];
	output[16] = temp;
	// 计算第 17 个SFI多项式
	temp = 0.0;
		temp += pow(input[0], 2) * pow(input[1], 2);
		temp += pow(input[0], 2) * pow(input[2], 2);
		temp += pow(input[0], 2) * pow(input[3], 2);
		temp += pow(input[0], 2) * pow(input[4], 2);
		temp += pow(input[1], 2) * pow(input[2], 2);
		temp += pow(input[1], 2) * pow(input[3], 2);
		temp += pow(input[1], 2) * pow(input[5], 2);
		temp += pow(input[2], 2) * pow(input[4], 2);
		temp += pow(input[2], 2) * pow(input[5], 2);
		temp += pow(input[3], 2) * pow(input[4], 2);
		temp += pow(input[3], 2) * pow(input[5], 2);
		temp += pow(input[4], 2) * pow(input[5], 2);
	output[17] = temp;
	// 计算第 18 个SFI多项式
	temp = 0.0;
		temp += (1.0 / input[0]) * (1.0 / input[1]);
		temp += (1.0 / input[0]) * (1.0 / input[2]);
		temp += (1.0 / input[0]) * (1.0 / input[3]);
		temp += (1.0 / input[0]) * (1.0 / input[4]);
		temp += (1.0 / input[1]) * (1.0 / input[2]);
		temp += (1.0 / input[1]) * (1.0 / input[3]);
		temp += (1.0 / input[1]) * (1.0 / input[5]);
		temp += (1.0 / input[2]) * (1.0 / input[4]);
		temp += (1.0 / input[2]) * (1.0 / input[5]);
		temp += (1.0 / input[3]) * (1.0 / input[4]);
		temp += (1.0 / input[3]) * (1.0 / input[5]);
		temp += (1.0 / input[4]) * (1.0 / input[5]);
	output[18] = temp;
	// 计算第 19 个SFI多项式
	temp = 0.0;
		temp += (1.0 / pow(input[0], 2)) * (1.0 / pow(input[1], 2));
		temp += (1.0 / pow(input[0], 2)) * (1.0 / pow(input[2], 2));
		temp += (1.0 / pow(input[0], 2)) * (1.0 / pow(input[3], 2));
		temp += (1.0 / pow(input[0], 2)) * (1.0 / pow(input[4], 2));
		temp += (1.0 / pow(input[1], 2)) * (1.0 / pow(input[2], 2));
		temp += (1.0 / pow(input[1], 2)) * (1.0 / pow(input[3], 2));
		temp += (1.0 / pow(input[1], 2)) * (1.0 / pow(input[5], 2));
		temp += (1.0 / pow(input[2], 2)) * (1.0 / pow(input[4], 2));
		temp += (1.0 / pow(input[2], 2)) * (1.0 / pow(input[5], 2));
		temp += (1.0 / pow(input[3], 2)) * (1.0 / pow(input[4], 2));
		temp += (1.0 / pow(input[3], 2)) * (1.0 / pow(input[5], 2));
		temp += (1.0 / pow(input[4], 2)) * (1.0 / pow(input[5], 2));
	output[19] = temp;
	// 计算第 20 个SFI多项式
	temp = 0.0;
		temp += exp(-1.0 * input[0]) * exp(-1.0 * input[1]);
		temp += exp(-1.0 * input[0]) * exp(-1.0 * input[2]);
		temp += exp(-1.0 * input[0]) * exp(-1.0 * input[3]);
		temp += exp(-1.0 * input[0]) * exp(-1.0 * input[4]);
		temp += exp(-1.0 * input[1]) * exp(-1.0 * input[2]);
		temp += exp(-1.0 * input[1]) * exp(-1.0 * input[3]);
		temp += exp(-1.0 * input[1]) * exp(-1.0 * input[5]);
		temp += exp(-1.0 * input[2]) * exp(-1.0 * input[4]);
		temp += exp(-1.0 * input[2]) * exp(-1.0 * input[5]);
		temp += exp(-1.0 * input[3]) * exp(-1.0 * input[4]);
		temp += exp(-1.0 * input[3]) * exp(-1.0 * input[5]);
		temp += exp(-1.0 * input[4]) * exp(-1.0 * input[5]);
	output[20] = temp;
	// 计算第 21 个SFI多项式
	temp = 0.0;
		temp += exp(-1.0 * input[0] * input[0]) * exp(-1.0 * input[1] * input[1]);
		temp += exp(-1.0 * input[0] * input[0]) * exp(-1.0 * input[2] * input[2]);
		temp += exp(-1.0 * input[0] * input[0]) * exp(-1.0 * input[3] * input[3]);
		temp += exp(-1.0 * input[0] * input[0]) * exp(-1.0 * input[4] * input[4]);
		temp += exp(-1.0 * input[1] * input[1]) * exp(-1.0 * input[2] * input[2]);
		temp += exp(-1.0 * input[1] * input[1]) * exp(-1.0 * input[3] * input[3]);
		temp += exp(-1.0 * input[1] * input[1]) * exp(-1.0 * input[5] * input[5]);
		temp += exp(-1.0 * input[2] * input[2]) * exp(-1.0 * input[4] * input[4]);
		temp += exp(-1.0 * input[2] * input[2]) * exp(-1.0 * input[5] * input[5]);
		temp += exp(-1.0 * input[3] * input[3]) * exp(-1.0 * input[4] * input[4]);
		temp += exp(-1.0 * input[3] * input[3]) * exp(-1.0 * input[5] * input[5]);
		temp += exp(-1.0 * input[4] * input[4]) * exp(-1.0 * input[5] * input[5]);
	output[21] = temp;
	// 计算第 22 个SFI多项式
	temp = 0.0;
		temp += cos(1.0 * input[0]) * cos(1.0 * input[1]);
		temp += cos(1.0 * input[0]) * cos(1.0 * input[2]);
		temp += cos(1.0 * input[0]) * cos(1.0 * input[3]);
		temp += cos(1.0 * input[0]) * cos(1.0 * input[4]);
		temp += cos(1.0 * input[1]) * cos(1.0 * input[2]);
		temp += cos(1.0 * input[1]) * cos(1.0 * input[3]);
		temp += cos(1.0 * input[1]) * cos(1.0 * input[5]);
		temp += cos(1.0 * input[2]) * cos(1.0 * input[4]);
		temp += cos(1.0 * input[2]) * cos(1.0 * input[5]);
		temp += cos(1.0 * input[3]) * cos(1.0 * input[4]);
		temp += cos(1.0 * input[3]) * cos(1.0 * input[5]);
		temp += cos(1.0 * input[4]) * cos(1.0 * input[5]);
	output[22] = temp;
	// 计算第 23 个SFI多项式
	temp = 0.0;
		temp += sin(1.0 * input[0]) * sin(1.0 * input[1]);
		temp += sin(1.0 * input[0]) * sin(1.0 * input[2]);
		temp += sin(1.0 * input[0]) * sin(1.0 * input[3]);
		temp += sin(1.0 * input[0]) * sin(1.0 * input[4]);
		temp += sin(1.0 * input[1]) * sin(1.0 * input[2]);
		temp += sin(1.0 * input[1]) * sin(1.0 * input[3]);
		temp += sin(1.0 * input[1]) * sin(1.0 * input[5]);
		temp += sin(1.0 * input[2]) * sin(1.0 * input[4]);
		temp += sin(1.0 * input[2]) * sin(1.0 * input[5]);
		temp += sin(1.0 * input[3]) * sin(1.0 * input[4]);
		temp += sin(1.0 * input[3]) * sin(1.0 * input[5]);
		temp += sin(1.0 * input[4]) * sin(1.0 * input[5]);
	output[23] = temp;
	// 计算第 24 个SFI多项式
	temp = 0.0;
		temp += input[0] * input[5];
		temp += input[1] * input[4];
		temp += input[2] * input[3];
	output[24] = temp;
	// 计算第 25 个SFI多项式
	temp = 0.0;
		temp += pow(input[0], 2) * pow(input[5], 2);
		temp += pow(input[1], 2) * pow(input[4], 2);
		temp += pow(input[2], 2) * pow(input[3], 2);
	output[25] = temp;
	// 计算第 26 个SFI多项式
	temp = 0.0;
		temp += (1.0 / input[0]) * (1.0 / input[5]);
		temp += (1.0 / input[1]) * (1.0 / input[4]);
		temp += (1.0 / input[2]) * (1.0 / input[3]);
	output[26] = temp;
	// 计算第 27 个SFI多项式
	temp = 0.0;
		temp += (1.0 / pow(input[0], 2)) * (1.0 / pow(input[5], 2));
		temp += (1.0 / pow(input[1], 2)) * (1.0 / pow(input[4], 2));
		temp += (1.0 / pow(input[2], 2)) * (1.0 / pow(input[3], 2));
	output[27] = temp;
	// 计算第 28 个SFI多项式
	temp = 0.0;
		temp += exp(-1.0 * input[0]) * exp(-1.0 * input[5]);
		temp += exp(-1.0 * input[1]) * exp(-1.0 * input[4]);
		temp += exp(-1.0 * input[2]) * exp(-1.0 * input[3]);
	output[28] = temp;
	// 计算第 29 个SFI多项式
	temp = 0.0;
		temp += exp(-1.0 * input[0] * input[0]) * exp(-1.0 * input[5] * input[5]);
		temp += exp(-1.0 * input[1] * input[1]) * exp(-1.0 * input[4] * input[4]);
		temp += exp(-1.0 * input[2] * input[2]) * exp(-1.0 * input[3] * input[3]);
	output[29] = temp;
	// 计算第 30 个SFI多项式
	temp = 0.0;
		temp += cos(1.0 * input[0]) * cos(1.0 * input[5]);
		temp += cos(1.0 * input[1]) * cos(1.0 * input[4]);
		temp += cos(1.0 * input[2]) * cos(1.0 * input[3]);
	output[30] = temp;
	// 计算第 31 个SFI多项式
	temp = 0.0;
		temp += sin(1.0 * input[0]) * sin(1.0 * input[5]);
		temp += sin(1.0 * input[1]) * sin(1.0 * input[4]);
		temp += sin(1.0 * input[2]) * sin(1.0 * input[3]);
	output[31] = temp;
}
