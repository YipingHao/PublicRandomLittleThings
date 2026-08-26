#include"analyzer.h"
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cmath>

using namespace analyzer;
static char* CopyMalloc(const char* s);
namespace analyzer
{
xyz::xyz() : E(0.0), count(0), Force(false)
{
}
xyz::~xyz()
{
	// 新版 StringConst 自动析构，无需手动 delete
}
xyz::xyz(const xyz& other)
	: E(other.E), count(other.count), name(other.name), XYZ(other.XYZ), Force(other.Force)
{
}
xyz& xyz::operator=(const xyz& other)
{
	if (this != &other) {
		E = other.E;
		count = other.count;
		name = other.name;
		XYZ = other.XYZ;
		Force = other.Force;
	}
	return *this;
}
void xyz::clear(void)
{
	E = 0.0;
	count = 0;
	Force = false;
	name.clear();
	XYZ.clear();
}
void xyz::Print(double* mat) const
{
	size_t i;
	size_t dim;
	dim = (Force ? 6 : 3);
	for (i = 0; i < count; i++)
	{
		mat[i * 3 + 0] = XYZ[i * dim + 0];
		mat[i * 3 + 1] = XYZ[i * dim + 1];
		mat[i * 3 + 2] = XYZ[i * dim + 2];
	}
	mat[count * 3] = E;
}
void xyz::PrintBondlength(double* mat) const
{
	size_t i, j, site;
	size_t dim;
	double x_1, y_1, z_1, x_2, y_2, z_2;
	double r, temp;
	dim = (Force ? 6 : 3);
	site = 0;
	for (i = 0; i < count; i++)
	{
		x_1 = XYZ[i * dim + 0];
		y_1 = XYZ[i * dim + 1];
		z_1 = XYZ[i * dim + 2];
		for (j = i + 1; j < count; j++)
		{
			x_2 = XYZ[j * dim + 0];
			y_2 = XYZ[j * dim + 1];
			z_2 = XYZ[j * dim + 2];
			r = 0.0;
			temp = x_2 - x_1;
			r += temp * temp;
			temp = y_2 - y_1;
			r += temp * temp;
			temp = z_2 - z_1;
			r += temp * temp;
			r = sqrt(r);
			mat[site] = r;
			site += 1;
		}
	}
	mat[site] = E;
}
void xyz::PrintAngle(double* mat) const
{
	PrintAngleCosines(mat);
	const size_t angleCount = (count >= 3) ? (count * (count - 1) * (count - 2) / 2) : 0;
	for (size_t i = 0; i < angleCount; ++i)
	{
		mat[i] = acos(mat[i]);
	}
}

void xyz::PrintAngleCosines(double* mat) const
{
	// 键角 (c, a, b): c 是中心原子，a 和 b 是两翼，a < b。
	const size_t dim = (Force ? 6 : 3);
	size_t site = 0;

	for (size_t c = 0; c < count; ++c)
	{
		const double xc = XYZ[c * dim + 0];
		const double yc = XYZ[c * dim + 1];
		const double zc = XYZ[c * dim + 2];

		for (size_t a = 0; a < count; ++a)
		{
			if (a == c) continue;

			const double vax = XYZ[a * dim + 0] - xc;
			const double vay = XYZ[a * dim + 1] - yc;
			const double vaz = XYZ[a * dim + 2] - zc;
			const double len_a = sqrt(vax * vax + vay * vay + vaz * vaz);

			for (size_t b = a + 1; b < count; ++b)
			{
				if (b == c) continue;

				const double vbx = XYZ[b * dim + 0] - xc;
				const double vby = XYZ[b * dim + 1] - yc;
				const double vbz = XYZ[b * dim + 2] - zc;
				const double len_b = sqrt(vbx * vbx + vby * vby + vbz * vbz);

				double cosAngle = 1.0; // 与旧退化行为 angle=0 保持一致。
				if (len_a > 0.0 && len_b > 0.0)
				{
					cosAngle = (vax * vbx + vay * vby + vaz * vbz) / (len_a * len_b);
					if (cosAngle > 1.0) cosAngle = 1.0;
					if (cosAngle < -1.0) cosAngle = -1.0;
				}

				mat[site++] = cosAngle;
			}
		}
	}
	mat[site] = E;
}

void xyz::PrintDihedralCosines(double* mat) const
{
	// 无向二面角 key=(B,C,A,D)：中心边 B<C，端点 A<D。
	// 对固定中心边，n_X=(r_X-r_B)x(r_C-r_B)，cos(phi)=n_A.n_D/(|n_A||n_D|)。
	const size_t dim = (Force ? 6 : 3);
	size_t site = 0;
	vector<double> nx;
	vector<double> ny;
	vector<double> nz;
	vector<double> normalLength;
	nx.recount(count);
	ny.recount(count);
	nz.recount(count);
	normalLength.recount(count);

	if (count >= 4)
	{
		for (size_t B = 0; B < count; ++B)
		{
			const double bx = XYZ[B * dim + 0];
			const double by = XYZ[B * dim + 1];
			const double bz = XYZ[B * dim + 2];
			for (size_t C = B + 1; C < count; ++C)
			{
				const double cbx = XYZ[C * dim + 0] - bx;
				const double cby = XYZ[C * dim + 1] - by;
				const double cbz = XYZ[C * dim + 2] - bz;

				for (size_t X = 0; X < count; ++X)
				{
					if (X == B || X == C)
					{
						nx[X] = ny[X] = nz[X] = normalLength[X] = 0.0;
						continue;
					}
					const double xbx = XYZ[X * dim + 0] - bx;
					const double xby = XYZ[X * dim + 1] - by;
					const double xbz = XYZ[X * dim + 2] - bz;
					nx[X] = xby * cbz - xbz * cby;
					ny[X] = xbz * cbx - xbx * cbz;
					nz[X] = xbx * cby - xby * cbx;
					normalLength[X] = sqrt(nx[X] * nx[X] + ny[X] * ny[X] + nz[X] * nz[X]);
				}

				for (size_t A = 0; A < count; ++A)
				{
					if (A == B || A == C) continue;
					for (size_t D = A + 1; D < count; ++D)
					{
						if (D == B || D == C) continue;
						double cosDihedral = 1.0;
						if (normalLength[A] > 0.0 && normalLength[D] > 0.0)
						{
							cosDihedral = (nx[A] * nx[D] + ny[A] * ny[D] + nz[A] * nz[D]) /
								(normalLength[A] * normalLength[D]);
							if (cosDihedral > 1.0) cosDihedral = 1.0;
							if (cosDihedral < -1.0) cosDihedral = -1.0;
						}
						mat[site++] = cosDihedral;
					}
				}
			}
		}
	}
	mat[site] = E;
}
void xyz::demo(FILE* fp) const
{
	size_t i, j;
	size_t dim;
	dim = (Force ? 6 : 3);
	fprintf(fp, "%zu\n", count);
	fprintf(fp, "%+25.16E\n", E);
	for (i = 0; i < name.count(); i++)
	{
		fprintf(fp, "%s", name[i].ptr());
		for (j = 0; j < dim; j++)
		{
			fprintf(fp, "    %+25.16E", XYZ[i * dim + j]);
		}
		fprintf(fp, "\n");
	}
}
bool xyz::operator==(const xyz& right) const
{
	return compare(right);
}
bool xyz::operator!=(const xyz& right) const
{
	return !compare(right);
}
bool xyz::compare(const xyz& right) const
{
	if (count != right.count) return false;
	if (Force != right.Force) return false;
	if (name.count() != right.name.count()) return false;
	if (XYZ.count() != right.XYZ.count()) return false;
	for (size_t i = 0; i < name.count(); i++)
	{
		if (!(name[i] == right.name[i])) return false;
	}
	return true;
}
int xyz::build(double Energy, const vector<const char*>& Name, const vector<double>& xyzSource)
{
		E = Energy;
		if (3 * Name.count() == xyzSource.count()) Force = false;
		else if (6 * Name.count() == xyzSource.count()) Force = true;
		else return 1;
		// 旧接口兼容：将 vector<char*> 转为 vector<StringConst>
		name.recount(Name.count());
		for (size_t i = 0; i < Name.count(); ++i) {
			name[i] = Name[i];
		}
		XYZ = xyzSource;
		count = name.count();
		return 0;
}
int xyz::build(double Energy, const vector<StringConst>& Name, const vector<double>& xyzSource)
{
    E = Energy;
    if (3 * Name.count() == xyzSource.count()) Force = false;
    else if (6 * Name.count() == xyzSource.count()) Force = true;
    else return 1;
    name = Name;
    XYZ = xyzSource;
    count = name.count();
    return 0;
}
int xyz::build(const xyz& source)
{
		E = source.E;
		count = source.count;
		XYZ = source.XYZ;
		name = source.name;
		Force = source.Force;
		return 0;
}
// 显式移动函数，配合新版模板 move_assign 调用
void xyz::move(xyz& src) {
	if (&src == this) return;
	E = src.E;
	count = src.count;
	XYZ = std::move(src.XYZ);
	name = std::move(src.name);
	Force = src.Force;
	// src 置空
	src.count = 0;
	src.E = 0;
	src.Force = false;
}

void xyz::permutation(const vector<size_t>& group)
{
		vector<StringConst> tempN;
		vector<double> tempXYZ;
		tempN.recount(name.count());
		tempXYZ.recount(XYZ.count());
		if (group.count() != name.count()) return;
		permutation(group, tempN, tempXYZ);
}
void xyz::permutation(const vector<size_t>& group, vector<StringConst>& tempN, vector<double>& tempXYZ)
{
		size_t i, dim, Src, j;
		dim = (Force ? 6 : 3);
		for (i = 0; i < name.count(); i++) tempN[i] = name[i];
		for (i = 0; i < XYZ.count(); i++) tempXYZ[i] = XYZ[i];
		for (i = 0; i < group.count(); i++) 
		{
			Src = group[i];
			name[i] = tempN[Src];
			for (j = 0; j < dim; j++)
				XYZ[i * dim + j] = tempXYZ[Src * dim + j];
		}
}
size_t xyz::AtomCount(void)const
{
	return count;
}
const char* xyz::AtomName(size_t index) const
{
	return (index < name.count()) ? name[index].ptr() : NULL;
}
}

namespace analyzer
{
xyzFile::xyzFile()
{
	atom = 0;
}
xyzFile::~xyzFile()
{
	clear();
}
xyzFile::xyzFile(const xyzFile& other)
    : atom(other.atom), content(other.content)
{
}
xyzFile& xyzFile::operator=(const xyzFile& other)
{
    if (this != &other) {
        atom = other.atom;
        content = other.content;
    }
    return *this;
}
void xyzFile::clear(void)
{
    content.clear();
    atom = 0;
}
void xyzFile::move(xyzFile& src)
{
    if (&src == this) return;
    clear();
    content.move(src.content);
    atom = src.atom;
    src.atom = 0;
}
int xyzFile::append(const xyz& element)
{
	if (content.count() != 0) {
		if (content[0] != element) return 1;
	}
	content.append(element);
	atom = element.count;
	return 0;
}
size_t xyzFile::check(void)const
{
	size_t i;
	for (i = 1; i < content.count(); i++)
	{
		if (content[i] != content[0]) return i;
	}
	return 0;
}
size_t xyzFile::count(void) const
{
	return content.count();
}
double* xyzFile::Print(void) const
{
	double* mat;
	size_t i, dim;
	dim = (atom * 3 + 1);
	mat = (double*)malloc(sizeof(double) * dim * content.count());
	for (i = 0; i < content.count(); i++)
		content[i].Print(mat + i * dim);
	return mat;
}
void xyzFile::PrintR(vector<double>& output) const
{
	size_t i, dim;
	dim = atom * (atom - 1);
	dim = dim / 2 + 1;
	output.recount(dim * content.count());
	for (i = 0; i < content.count(); i++)
		content[i].PrintBondlength(output.ptr(i * dim));
}
void xyzFile::PrintAngles(vector<double>& output) const
{
	// 计算键角数量：每个原子作为中心，两翼原子对数为 C(N-1, 2) = (N-1)*(N-2)/2
	// 总键角数 = N * (N-1) * (N-2) / 2
	size_t i, dim;
	if (atom < 3)
	{
		// 少于3个原子时没有键角
		dim = 1; // 只有能量
	}
	else
	{
		dim = atom * (atom - 1) * (atom - 2) / 2 + 1; // 键角数 + 能量
	}
	output.recount(dim * content.count());
	for (i = 0; i < content.count(); i++)
		content[i].PrintAngle(output.ptr(i * dim));
}

void xyzFile::PrintAngleCosines(vector<double>& output) const
{
	size_t dim = 1;
	if (atom >= 3)
	{
		dim = atom * (atom - 1) * (atom - 2) / 2 + 1;
	}
	output.recount(dim * content.count());
	for (size_t i = 0; i < content.count(); ++i)
	{
		content[i].PrintAngleCosines(output.ptr(i * dim));
	}
}

void xyzFile::PrintDihedralCosines(vector<double>& output) const
{
	size_t dim = 1;
	if (atom >= 4)
	{
		dim = atom * (atom - 1) * (atom - 2) * (atom - 3) / 4 + 1;
	}
	output.recount(dim * content.count());
	for (size_t i = 0; i < content.count(); ++i)
	{
		content[i].PrintDihedralCosines(output.ptr(i * dim));
	}
}

void xyzFile::PrintRAndAngleCosines(vector<double>& bondOutput, vector<double>& angleCosineOutput) const
{
	PrintRAndGeometricCosines(bondOutput, &angleCosineOutput, NULL);
}

void xyzFile::PrintRAndGeometricCosines(vector<double>& bondOutput, vector<double>* angleCosineOutput,
	vector<double>* dihedralCosineOutput) const
{
	size_t bondDim = atom * (atom - 1) / 2 + 1;
	size_t angleDim = 1;
	if (atom >= 3)
	{
		angleDim = atom * (atom - 1) * (atom - 2) / 2 + 1;
	}
	size_t dihedralDim = 1;
	if (atom >= 4)
	{
		dihedralDim = atom * (atom - 1) * (atom - 2) * (atom - 3) / 4 + 1;
	}

	bondOutput.recount(bondDim * content.count());
	if (angleCosineOutput != NULL)
	{
		angleCosineOutput->recount(angleDim * content.count());
	}
	if (dihedralCosineOutput != NULL)
	{
		dihedralCosineOutput->recount(dihedralDim * content.count());
	}

	const size_t pairCount = (atom >= 2) ? (atom * (atom - 1) / 2) : 0;
	vector<double> dx;
	vector<double> dy;
	vector<double> dz;
	vector<double> length;
	vector<size_t> pairIndex;
	dx.recount(pairCount);
	dy.recount(pairCount);
	dz.recount(pairCount);
	length.recount(pairCount);
	pairIndex.recount(atom * atom);
	pairIndex.value((size_t)(-1));

	for (size_t frame = 0; frame < content.count(); ++frame)
	{
		const xyz& one = content[frame];
		const size_t dim = one.Force ? 6 : 3;
		double* bondRow = bondOutput.ptr(frame * bondDim);
		double* angleCosineRow = (angleCosineOutput != NULL) ? angleCosineOutput->ptr(frame * angleDim) : NULL;
		double* dihedralCosineRow = (dihedralCosineOutput != NULL) ? dihedralCosineOutput->ptr(frame * dihedralDim) : NULL;

		size_t site = 0;
		for (size_t i = 0; i < atom; ++i)
		{
			const double xi = one.XYZ[i * dim + 0];
			const double yi = one.XYZ[i * dim + 1];
			const double zi = one.XYZ[i * dim + 2];
			for (size_t j = i + 1; j < atom; ++j)
			{
				const double xj = one.XYZ[j * dim + 0];
				const double yj = one.XYZ[j * dim + 1];
				const double zj = one.XYZ[j * dim + 2];
				const double vx = xj - xi;
				const double vy = yj - yi;
				const double vz = zj - zi;
				const double len = sqrt(vx * vx + vy * vy + vz * vz);

				dx[site] = vx;
				dy[site] = vy;
				dz[site] = vz;
				length[site] = len;
				pairIndex[i * atom + j] = site;
				pairIndex[j * atom + i] = site;
				bondRow[site] = len;
				++site;
			}
		}
		bondRow[site] = one.E;

		site = 0;
		if (angleCosineRow != NULL && atom >= 3)
		{
			for (size_t c = 0; c < atom; ++c)
			{
				for (size_t a = 0; a < atom; ++a)
				{
					if (a == c)
					{
						continue;
					}
					for (size_t b = a + 1; b < atom; ++b)
					{
						if (b == c)
						{
							continue;
						}

						const size_t ca = pairIndex[c * atom + a];
						const size_t cb = pairIndex[c * atom + b];
						double vax = dx[ca];
						double vay = dy[ca];
						double vaz = dz[ca];
						double vbx = dx[cb];
						double vby = dy[cb];
						double vbz = dz[cb];

						if (c > a)
						{
							vax = -vax;
							vay = -vay;
							vaz = -vaz;
						}
						if (c > b)
						{
							vbx = -vbx;
							vby = -vby;
							vbz = -vbz;
						}

						double cosAngle = 1.0; // 与旧退化行为 angle=0 保持一致。
						if (length[ca] > 0.0 && length[cb] > 0.0)
						{
							cosAngle = (vax * vbx + vay * vby + vaz * vbz) / (length[ca] * length[cb]);
							if (cosAngle > 1.0) cosAngle = 1.0;
							if (cosAngle < -1.0) cosAngle = -1.0;
						}
						angleCosineRow[site] = cosAngle;
						++site;
					}
				}
			}
		}
		if (angleCosineRow != NULL)
		{
			angleCosineRow[site] = one.E;
		}
		if (dihedralCosineRow != NULL)
		{
			one.PrintDihedralCosines(dihedralCosineRow);
		}
	}
}
void xyzFile::demo(FILE* fp) const
{
	demo(fp, 0, content.count());
}
void xyzFile::demo(FILE* fp, size_t lower, size_t upper) const
{
	size_t i;
	for (i = lower; i < upper && i < content.count(); i++)
	{
		content[i].demo(fp);
	}
}
void xyzFile::tail(FILE* fp, size_t N) const
{
	size_t lower;
	size_t i;
	lower = (N < content.count() ? content.count() - N : 0);
	fprintf(fp, "count: %zu\n", content.count());
	for (i = lower; i < N + lower && i < content.count(); i++)
	{
		content[i].demo(fp);
	}
}
int xyzFile::permutation(const vector<size_t>& group)
{
	vector<StringConst> tempN;
	vector<double> tempXYZ;
	size_t i;

	if (content.count() == 0) return 0;
	if (group.count() != content[0].name.count())return 1;
	tempN.recount(content[0].name.count());
	tempXYZ.recount(content[0].XYZ.count());
	for (i = 0; i < content.count(); i++)
	{
		content[i].permutation(group, tempN, tempXYZ);
	}
	return 0;
}
double xyzFile::EnergyUpper(void) const
{
	double upper;
	size_t i;
	if (content.count() != 0) upper = content[0].E;
	else upper = 0.0;
	for (i = 1; i < content.count(); i++)
	{
		upper = (upper > content[i].E ? upper : content[i].E);
	}
	return upper;
}
double xyzFile::EnerguLower(void) const
{
	double lower;
	size_t i;
	if (content.count() != 0) lower = content[0].E;
	else lower = 0.0;
	for (i = 1; i < content.count(); i++)
	{
		lower = (lower < content[i].E ? lower : content[i].E);
	}
	return lower;
}
void xyzFile::OutputErange(vector<double>&output) const
{
	size_t i;
	double lower;
	output.recount(content.count());
	lower = EnerguLower();
	for (i = 0; i < content.count(); i++)
	{
		output[i] = content[i].E - lower;
	}
}
}

static char* CopyMalloc(const char* s)
{
	if (s == NULL) return NULL;
	size_t len = 0;
	while (s[len] != '\0') ++len;
	char* out = (char*)malloc(len + 1);
	if (out == NULL) return NULL;
	for (size_t i = 0; i <= len; ++i) out[i] = s[i];
	return out;
}

#include "sheet.h"
#include "automata.h"

namespace analyzer
{
typedef hyperlex::Morpheme tokenstream;
typedef hyperlex::GrammarTree AST;
typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor> GTNode;
typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor>::PostIterator GTiterator;

/*
## xyz 文件格式说明

参考 sample.xyz 文件格式：
1. 每个分子块以原子数量开始
2. 第二行是能量值
3. 接下来的行是每个原子的信息，包括：原子标签、x坐标、y坐标、z坐标、力的三个分量（如果有）

示例：
```
9
-97208.40600498248
C       0.0072  -0.5687 0.0     1.4517297437249999      6.01923561735   5.2067503058e-07
C       -1.2854 0.2499  0.0     17.9533587683   -5.1623821924   3.49002255005e-07
O       1.1304  0.3147  0.0     -4.0883694515   22.5901955842   3.30876819905e-06
H       0.0392  -1.1972 0.89    -1.141572648295 -9.7469181345   7.64734244805
H       0.0392  -1.1972 -0.89   -1.141572648295 -9.7469181345   -7.64734244805
H       -1.3175 0.8784  0.89    -2.48205465155  4.933531279     4.3699824457
H       -1.3175 0.8784  -0.89   -2.48205465155  4.933531279     -4.3699824457
H       -2.1422 -0.4239 0.0     -5.5147904611   -3.0206752465   -8.9092739811e-09
H       1.9857  -0.1365 0.0     -2.4392777023   -10.83820307755 -6.07213606025e-08
```

*/
int xyzFile::build(FILE*fp)
{
	// 解析思路：先做词法分析，把 token 按行号分组。
	// 每个“非空行”对应一行数据，按状态机解析：
	//   ExpectCount  -> 原子数（单个整数）
	//   ExpectEnergy -> 能量（单个实数/整数）
	//   ExpectAtom   -> 原子信息（元素名 + 3 或 6 个数）
	// 读满 expectedAtoms 行后完成一帧并回到 ExpectCount。
	tokenstream TS;
	int error = TS.Build<sheet::FIL>(fp);
	if (error != 0)
	{
		return error * 11;
	}

	clear();

	struct LineToken
	{
		bool isId;
		const char* id;
		double num;
		LineToken() : isId(false), id(NULL), num(0.0) {}
	};

	enum Stage
	{
		ExpectCount = 0,
		ExpectEnergy = 1,
		ExpectAtom = 2
	};

	Stage stage = ExpectCount;
	size_t expectedAtoms = 0;
	size_t atomsRead = 0;
	size_t atomDim = 0;
	vector<const char*> name;
	vector<double> XYZ;
	double energy = 0.0;

	vector<LineToken> lineTokens;
	bool haveLine = false;
	size_t currentLine = 0;

	for (size_t i = 0; i < TS.GetCount(); i++)
	{
		const tokenstream::result& res = TS[i];
		const int accept = res.accept;
		if (!haveLine) {
			currentLine = res.line;
			haveLine = true;
		}

		if (res.line != currentLine)
		{
			// 处理上一行的 token
			// 如果 lineTokens 不为空，表示当前行已结束，开始处理累积的 token
			if (!lineTokens.empty())
			{
				if (stage == ExpectCount)
				{
					if (lineTokens.count() != 1 || lineTokens[0].isId) return -101;
					expectedAtoms = (size_t)lineTokens[0].num;
					if (expectedAtoms == 0) return -101;
					name.clear();
					XYZ.clear();
					atomsRead = 0;
					atomDim = 0;
					stage = ExpectEnergy;
				}
				else if (stage == ExpectEnergy)
				{
					// 能量行允许多列，取第一列作为能量，其余忽略
					if (lineTokens.count() < 1 || lineTokens[0].isId) return -102;
					energy = lineTokens[0].num;
					stage = ExpectAtom;
				}
				else
				{
					if (lineTokens.count() < 4 || lineTokens[0].isId == false) return -103;
					const char* atomName = lineTokens[0].id;
					size_t numCount = 0;
					// 统计原子行的数值个数
					// 原子行的第一个 token 是元素名，后面的 token 是数值
					for (size_t k = 1; k < lineTokens.count(); k++)
					{
						if (lineTokens[k].isId) return -104;
						numCount++;
					}
					if (numCount != 3 && numCount != 6) return -105;
					if (atomDim == 0) atomDim = numCount;
					else if (atomDim != numCount) return -106;

					name.append(atomName);
					for (size_t k = 1; k < lineTokens.count(); k++)
					{
						XYZ.append(lineTokens[k].num);
					}
					atomsRead++;
					if (atomsRead == expectedAtoms)
					{
						// 一帧读取完成：将 name/XYZ 打包成 xyz
						// build() 会检查坐标长度是否满足 3N 或 6N
						xyz ele;
						error = ele.build(energy, name, XYZ);
						if (error != 0) return error;
						size_t eleCount = ele.AtomCount();
						content.appendMove(ele);
						atom = eleCount;
						stage = ExpectCount;
						name.clear();
						XYZ.clear();
						atomsRead = 0;
						atomDim = 0;
					}
				}
			}

			lineTokens.clear();
			currentLine = res.line;
		}

		if (accept == sheet::FIL::regular::_identifier_ ||
			accept == sheet::FIL::regular::_real_ ||
			accept == sheet::FIL::regular::_integer_)
		{
			// 只收集 identifier/real/integer，其它 token 作为格式噪声忽略
			// 依赖词法分析器提供的行号进行分组
			LineToken t;
			if (accept == sheet::FIL::regular::_identifier_)
			{
				t.isId = true;
				t.id = TS.GetWord(i);
			}
			else
			{
				t.isId = false;
				t.num = (accept == sheet::FIL::regular::_real_) ? TS.GetReal(i) : (double)TS.GetInt(i);
			}
			lineTokens.append(t);
		}
	}

	if (!lineTokens.empty())
	{
		// 文件末尾可能没有触发行切换，这里补一次处理
		if (stage == ExpectCount)
		{
			if (lineTokens.count() != 1 || lineTokens[0].isId) return -101;
			expectedAtoms = (size_t)lineTokens[0].num;
			if (expectedAtoms == 0) return -101;
			stage = ExpectEnergy;
		}
		else if (stage == ExpectEnergy)
		{
			// 能量行允许多列，取第一列作为能量，其余忽略
			if (lineTokens.count() < 1 || lineTokens[0].isId) return -102;
			energy = lineTokens[0].num;
			stage = ExpectAtom;
		}
		else
		{
			if (lineTokens.count() < 4 || lineTokens[0].isId == false) return -103;
			const char* atomName = lineTokens[0].id;
			size_t numCount = 0;
			for (size_t k = 1; k < lineTokens.count(); k++)
			{
				if (lineTokens[k].isId) return -104;
				numCount++;
			}
			if (numCount != 3 && numCount != 6) return -105;
			if (atomDim == 0) atomDim = numCount;
			else if (atomDim != numCount) return -106;

			name.append(atomName);
			for (size_t k = 1; k < lineTokens.count(); k++)
			{
				XYZ.append(lineTokens[k].num);
			}
			atomsRead++;
			if (atomsRead == expectedAtoms)
			{
				xyz ele;
				error = ele.build(energy, name, XYZ);
				if (error != 0) return error;
				size_t eleCount = ele.AtomCount();
				content.appendMove(ele);
				atom = eleCount;
				stage = ExpectCount;
			}
		}
	}

	// 若未回到 ExpectCount，说明最后一帧不完整
	if (stage != ExpectCount) return -107;
	return 0;
}
}
