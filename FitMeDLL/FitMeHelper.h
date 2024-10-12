#pragma once

#include <cmath>
#include <algorithm>
#include <functional>
#include <array>

#include <Eigen/Dense>
#include <unsupported/Eigen/Splines>
#include <matplot/matplot.h>

using namespace Eigen;

enum FitMethod {
    POLY, CUBIC_SPLINE, STUPID
};

struct DataRecord {
    std::string Breed;
    // 0 表示标准，1 表示申请
    int Variety;
    double Mean_1;
    double Mean_2;
    double SD_1;
    double SD_2;
};


FitMethod toMethodEnum(const std::string& method);
MatrixXd BuildVandermondeMatrix(const VectorXd& x, int degree);

std::function<double(double)> CubicSplineFit(const VectorXd& x, const VectorXd& y);
std::function<double(double)> PolyFit(const VectorXd& x, const VectorXd& y, int degree);
std::function<double(double)> StupidFit(const VectorXd& x, const VectorXd& y);

std::function<double(double)> Fit(const std::vector<double>& x, const std::vector<double>& y, const std::string& methodString, int degree);

// 数据解析
std::vector<DataRecord> parseDataRecords(const std::string& dataString);
std::vector<double>dataRecordGetMeanVector(const std::vector<DataRecord>& dataRecordVector);
std::vector<double>dataRecordGetSDVector(const std::vector<DataRecord>& dataRecordVector);
