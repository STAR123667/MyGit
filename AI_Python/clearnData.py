import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

##########  数据加载  ########  

df = pd.read_csv('COATING_MACHINE_TABLE.csv')

# 查看数据的基本信息和前几行
print("数据集形状（行，列）:", df.shape)
print("\n数据前5行：")
print(df.head())
print("\n数据基本信息：")
print(df.info())
print("\n数据统计描述：")
print(df.describe())

##########  处理缺失值  ##########

# 1. 检查缺失值
print("各列缺失值数量：")
print(df.isnull().sum())

# 2. 处理缺失值 - 方法一：删除
# 删除任何包含缺失值的行（适用于缺失值很少的情况）
# df_dropped = df.dropna()
# print(f"\n删除缺失值后，数据形状: {df_dropped.shape}")

# 3. 处理缺失值 - 方法二：填充
# 更常用的方法是根据列的特性进行填充
df_filled = df.copy()

# 对于数值型列（如'年龄'），用中位数填充（比均值更抗异常值影响）
# if '年龄' in df_filled.columns:
#     df_filled['年龄'].fillna(df_filled['年龄'].median(), inplace=True)

# 对于分类列（如'城市'），用众数（最频繁出现的值）填充
if '地址' in df_filled.columns:
    df_filled['地址'].fillna(df_filled['地址'].mode()[0], inplace=True)

# 对于可能随时间变化的列（如'上次消费金额'），有时用0填充更有业务意义
# if '上次消费金额' in df_filled.columns:
#     df_filled['上次消费金额'].fillna(0, inplace=True)

print("\n填充缺失值后，各列缺失值数量：")
print(df_filled.isnull().sum())


##########  识别与处理异常值  ##########

# 我们以'年收入'为例，假设它应该是一个合理的正值
if '值' in df_filled.columns:
    # 方法一：使用四分位距（IQR）法识别
    Q1 = df_filled['值'].quantile(0.25)
    Q3 = df_filled['值'].quantile(0.75)
    IQR = Q3 - Q1
    lower_bound = Q1 - 1.5 * IQR
    upper_bound = Q3 + 1.5 * IQR

    # 找出异常值
    outliers = df_filled[(df_filled['值'] < lower_bound) | (df_filled['值'] > upper_bound)]
    print(f"\n使用IQR法发现的'值'异常值数量: {len(outliers)}")

    # 处理异常值：这里选择用上下边界值进行截断（Winsorization）
    df_filled['值'] = np.where(df_filled['值'] > upper_bound, upper_bound,
                                   np.where(df_filled['值'] < lower_bound, lower_bound, df_filled['值']))

print("已对'值'的异常值进行截断处理。")


##########  处理重复值  ##########

# 检查并删除完全重复的行
duplicate_rows = df_filled.duplicated()
print(f"\n发现完全重复的行数: {duplicate_rows.sum()}")

# 删除这些重复行，只保留第一次出现的记录
df_cleaned = df_filled.drop_duplicates()
print(f"删除重复值后，数据形状: {df_cleaned.shape}")



##########  处理不一致性，确保数据格式和值的统一  ######### 

# 1. 标准化文本格式：例如，将'城市'列统一为首字母大写
if '单位' in df_cleaned.columns:
    df_cleaned['单位'] = df_cleaned['单位'].str.title()

# 2. 映射统一值：例如，将性别信息统一为'男'和'女'
# if '性别' in df_cleaned.columns:
#     gender_mapping = {'male': '男', 'female': '女', 'M': '男', 'F': '女'}
#     df_cleaned['性别'] = df_cleaned['性别'].replace(gender_mapping)
    # 也可以使用 .map() 函数，但 .replace() 更灵活，未指定的值保持不变

# 3. 转换数据类型：确保数值列是数字类型
if '单位' in df_cleaned.columns:
    df_cleaned['单位'] = pd.to_numeric(df_cleaned['单位'], errors='coerce') # errors='coerce'将错误转换为NaN
    # 转换后，可以再次用中位数填充因转换产生的新NaN
    df_cleaned['单位'].fillna(df_cleaned['单位'].median(), inplace=True)

print("\n数据清洗完成！查看清洗后的数据前5行：")
print(df_cleaned.head())
