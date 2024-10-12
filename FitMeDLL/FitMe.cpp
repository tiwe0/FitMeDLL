#include "FitMe.h"
#include "FitMeHelper.h"

void
Plot
(const std::vector<double>& x, const std::vector<double>& y, const std::string& methodString, int degree, const std::string& filename)
{
    std::function<double(double)> func = Fit(x, y, methodString, degree);

    auto x_min_it = std::min_element(x.begin(), x.end());
    auto x_max_it = std::max_element(x.begin(), x.end());

    double x_min = static_cast<double>(*x_min_it);
    double x_max = static_cast<double>(*x_max_it);

    using namespace matplot;

    fplot(func, std::array<double, 2>{x_min, x_max});

    hold(on);
    scatter(x, y);
    hold(off);

    // 添加标题和标签
    title("Fitting Plot");
    xlabel("Mean");
    ylabel("SD");

    save(filename);
}

void
PlotS
(const std::string& dataString, const std::string& methodString, int degree, const std::string& filename)
{
    std::vector<DataRecord> dataRecord = parseDataRecords(dataString);
    std::vector<double> means = dataRecordGetMeanVector(dataRecord);
    std::vector<double> sds = dataRecordGetSDVector(dataRecord);
    Plot(means, sds, methodString, degree, filename);
}
