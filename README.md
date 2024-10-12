# FitMe

FitMe 是一个自用的dll，用于将离散数据使用指定算法拟合后，在同一张图上绘制散点和拟合曲线，并将图片保存为svg格式。

## 依赖

FitMe 依赖 GNU plot 进行图片绘制。

对于 Windows 用户，你需要:
1. 下载最近的稳定版 GNU plot
2. 将其解压后放到安全的位置（如`C:\Program Files`目录下)
3. 将其二进制文件所在目录添加到 `PATH` 中

## 使用

1. 将 dll 文件放置到主程序同级目录下（或放到 `PATH` 包含的目录中）
2. 将 lib 文件作为链接输入添加到你的项目中
3. 将 .h 文件作为头文件添加到你的项目中

## 接口

### Plot
函数签名:
```c++
void
Plot
(const std::vector<double>& x, const std::vector<double>& y, const std::string& methodString, int degree, const std::string& filename);
```
参数说明:

| 参数 | 类型 | 解释 | 备注|
| --- | --- | --- | ---|
|`x`| `std::vector<double>` | x值 | 要与 `y` 长度一致 |
|`y`| `std::vector<double>` | y值 | 要与 `x` 长度一致 |
|`methodString`| `std::string`| 拟合算法名称 | `"POLY"`, `"CUBIC_SPLINE"`, 注意需要大写。默认使用 `"POLY"` |
|`degree` | `int` | 使用多项式拟合时，多项式的最高次数 |仅在`methodString`使用`"POLY"`拟合算法时生效，默认为 `5`|
|`filename` | `std::string` |需要保存的图片名称| 默认为 `tmp.svg` |

### PlotS
函数签名:
```c++
void 
PlotS
(const std::string & dataString, const std::string & methodString, int degree, const std::string & filename);
```
参数说明:

| 参数 | 类型 | 解释 | 备注|
| --- | --- | --- | ---|
|`dataString`| `std::string` | 数据，但是以字符串形式给出 | 字符串格式要符合约定:`品种_类型_均值1,均值2_标准差1,标准差2`,每个品种使用`;`分隔，否则会解析错误 |
|`methodString`| `std::string`| 拟合算法名称 | `"POLY"`, `"CUBIC_SPLINE"`, 注意需要大写。默认使用 `"POLY"` |
|`degree` | `int` | 使用多项式拟合时，多项式的最高次数 |仅在`methodString`使用`"POLY"`拟合算法时生效，默认为 `5`|
|`filename` | `std::string` |需要保存的图片名称| 默认为 `tmp.svg` |


## 拟合算法

| methodString | 算法名称 | 额外参数 |
| --- | --- | --- |
| POLY | 多项式拟合 | `int degree`|
| CUBIC_SPLINE | 三次样条插值 | |
