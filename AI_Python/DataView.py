# 导入必要的库
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# 设置图表风格，让图表更好看
sns.set_style("whitegrid")
# -------------------------- 设置中文字体 start --------------------------
plt.rcParams['font.sans-serif'] = [
    # Windows 优先
    'SimHei', 'Microsoft YaHei',
    # macOS 优先
    'PingFang SC', 'Heiti TC',
    # Linux 优先
    'WenQuanYi Micro Hei', 'DejaVu Sans'
]
# 修复负号显示为方块的问题
plt.rcParams['axes.unicode_minus'] = False
# -------------------------- 设置中文字体 end --------------------------

# 加载数据
# 这里我们直接从 seaborn 的内置数据集加载
df = sns.load_dataset('titanic')

# 查看数据的前几行和基本信息
print("数据形状（行数，列数）:", df.shape)
print("\n数据前5行：")
print(df.head())
print("\n数据基本信息（类型、非空值数量等）：")
print(df.info())

# 绘制年龄的直方图
# plt.figure(figsize=(10, 6))
# plt.hist(df['age'].dropna(), bins=30,  edgecolor='black', alpha=0.7)
# plt.title('乘客年龄分布直方图')
# plt.xlabel('年龄')
# plt.ylabel('频数')
# plt.show()

# 绘制票价的箱线图
# plt.figure(figsize=(8, 5))
# plt.boxplot(df['fare'].dropna())
# plt.title('票价箱线图')
# plt.ylabel('票价')
# plt.show()

# 绘制乘客性别的柱状图
# survival_counts = df['sex'].value_counts()
# plt.figure(figsize=(8, 5))
# plt.bar(survival_counts.index, survival_counts.values, color=['lightblue', 'lightcoral'])
# plt.title('乘客性别分布')
# plt.xlabel('性别')
# plt.ylabel('人数')
# plt.show()

# 绘制年龄与票价的散点图
# plt.figure(figsize=(10, 6))
# plt.scatter(df['age'], df['fare'], alpha=0.5) # alpha 设置透明度，便于观察点密度
# plt.title('年龄 vs 票价 散点图')
# plt.xlabel('年龄')
# plt.ylabel('票价')
# plt.show()

# 使用 seaborn 绘制分组箱线图 (pclass: 舱位等级，1/2/3等舱)
# plt.figure(figsize=(10, 6))
# sns.boxplot(x='pclass', y='fare', data=df)
# plt.title('不同舱位的票价分布')
# plt.show()

# 绘制不同性别下年龄分布的小提琴图
# plt.figure(figsize=(10, 6))
# sns.violinplot(x='sex', y='age', data=df, inner='quartile') # inner 参数显示四分位线
# plt.title('不同性别的年龄分布（小提琴图）')
# plt.show()

# 创建性别与生存情况的交叉表
# cross_tab = pd.crosstab(df['sex'], df['survived'], normalize='index') # normalize='index' 按行计算比例
# print(cross_tab)

# 绘制堆叠柱状图
# cross_tab.plot(kind='bar', stacked=True, figsize=(10, 6), color=['tomato', 'lightgreen'])
# plt.title('不同性别的生存比例')
# plt.xlabel('性别')
# plt.ylabel('比例')
# plt.legend(['未幸存', '幸存'])
# plt.show()

# 在年龄-票价散点图中，用颜色区分是否幸存
# plt.figure(figsize=(12, 8))
# sns.scatterplot(x='age', y='fare', hue='survived', style='survived', data=df, alpha=0.7)
# plt.title('年龄 vs 票价（按生存情况着色）')
# plt.show()

# 选择数值型列
numeric_df = df.select_dtypes(include=['float64', 'int64'])

# 计算相关系数矩阵
corr_matrix = numeric_df.corr()

# 绘制热力图
plt.figure(figsize=(12, 8))
sns.heatmap(corr_matrix, annot=True, cmap='coolwarm', center=0, square=True)
plt.title('数值特征相关矩阵热力图')
plt.show()




