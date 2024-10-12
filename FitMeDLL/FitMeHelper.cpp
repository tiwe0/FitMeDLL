#include "FitMeHelper.h"

MatrixXd
BuildVandermondeMatrix
(const VectorXd& x, int degree)
{
    int n = static_cast<int>(x.size());
    MatrixXd A(n, degree + 1);

    // 填充 Vandermonde 矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= degree; ++j) {
            A(i, j) = pow(x(i), j);  // x(i) 的 j 次方
        }
    }
    return A;
}

FitMethod
toMethodEnum
(const std::string& method)
{
    if (method == "POLY") return FitMethod::POLY;
    if (method == "CUBIC_SPLINE") return FitMethod::CUBIC_SPLINE;
    if (method == "STUPID") return FitMethod::STUPID;
    return FitMethod::POLY;
}

std::function<double(double)>
CubicSplineFit
(const VectorXd& x, const VectorXd& y)
{
    Eigen::RowVectorXd x_knots = x.transpose();
    Eigen::RowVectorXd y_values = y.transpose();

    // 使用 Eigen 的 SplineFitting 进行三次样条拟合
    Spline<double, 1> spline = SplineFitting<Spline<double, 1>>::Interpolate(y_values, 3, x_knots);

    // 构建包装函数并返回
    return [spline](double x) {
        return spline(x)(0);
    };
}

std::function<double(double)>
PolyFit
(const VectorXd& x, const VectorXd& y, int degree)
{
    // 构建 Vandermonde 矩阵
    MatrixXd A = BuildVandermondeMatrix(x, degree);

    // 通过最小二乘法求解多项式系数
    VectorXd coeffs = A.colPivHouseholderQr().solve(y);

    // 构建多项式函数并返回
    return [coeffs](double x) {
        double y = 0.0;
        int degree = coeffs.size() - 1;  // 多项式的阶数

        // 根据多项式公式计算y值
        for (int i = 0; i <= degree; ++i) {
            y += coeffs[i] * std::pow(x, i);
        }

        return y;
    };
}

std::function<double(double)>
StupidFit
(const VectorXd& x, const VectorXd& y)
{
    return [](double x) {
        return x;
    };
}

std::function<double(double)>
Fit
(const std::vector<double>& x, const std::vector<double>& y, const std::string& methodString, int degree)
{
    VectorXd vx = VectorXd::Map(x.data(), x.size());
    VectorXd vy = VectorXd::Map(y.data(), y.size());

    FitMethod method = toMethodEnum(methodString);

    switch (method)
    {
    case FitMethod::POLY:
        return PolyFit(vx, vy, degree);
    case FitMethod::CUBIC_SPLINE:
        return CubicSplineFit(vx, vy);
    case FitMethod::STUPID:
        return StupidFit(vx, vy);
    default:
        return PolyFit(vx, vy, degree);
    }
}

// 分割字符串的辅助函数
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// 解析输入字符串并返回 DataRecord 的列表
std::vector<DataRecord> parseDataRecords(const std::string& input) {
    std::vector<DataRecord> records;

    // 以分号分割不同的记录
    std::vector<std::string> entries = split(input, ';');

    for (const auto& entry : entries) {
        if (entry.empty()) continue;

        // 以逗号分割 Breed_Variety_Mean1,Mean2_SD1,SD2
        std::vector<std::string> ThreeParts = split(entry, ',');
        if (ThreeParts.size() != 3) {
            std::cerr << "Invalid input format: " << entry << std::endl;
            continue;
        }

        DataRecord record;

        std::vector<std::string> BreedVarietyMean1 = split(ThreeParts[0], '_');
        std::vector<std::string> Mean2_SD1 = split(ThreeParts[1], '_');

        record.Breed = BreedVarietyMean1[0];
        record.Variety = std::stoi(BreedVarietyMean1[1]);
        record.Mean_1 = std::stod(BreedVarietyMean1[2]);
        record.Mean_2 = std::stod(Mean2_SD1[0]);
        record.SD_1 = std::stod(Mean2_SD1[1]);
        record.SD_2 = std::stod(ThreeParts[2]);

        records.push_back(record);
    }

    return records;
}

// 将数据记录解析为 std::vector
std::vector<double> 
dataRecordGetMeanVector
(const std::vector<DataRecord>& dataRecordVector)
{
    std::vector<double> dv;
    for (auto record : dataRecordVector) {
        dv.push_back(record.Mean_1);
        dv.push_back(record.Mean_2);
    }
    return dv;
}

// 将数据记录解析为 std::vector
std::vector<double>
dataRecordGetSDVector
(const std::vector<DataRecord>& dataRecordVector)
{
    std::vector<double> dv;
    for (auto record : dataRecordVector) {
        dv.push_back(record.SD_1);
        dv.push_back(record.SD_2);
    }
    return dv;
}