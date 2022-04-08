import pandas as pd 
import matplotlib.pyplot as plt
import numpy as np
import os
plt.rcParams['font.sans-serif']=['SimHei'] #用来正常显示中文标签
plt.rcParams['axes.unicode_minus']=False #用来正常显示负号

DATA_PATH="./"
filename="analysis.csv"
file_path=os.path.join(DATA_PATH,filename)
#导入数据
def load_data(filepath):   
    return pd.read_csv(file_path)

data=load_data(file_path)
judgeTimes=data['judgeTimes']
avarageTimes=str(judgeTimes.mean())
avTstring='总计执行填充1000次，平均填入数字的次数:'+avarageTimes+'\n直方图的组距为1000'
print(avTstring)
bins = np.linspace(0,160000,161)

#调用画直方图的函数，把数据分成100个区间
plt.hist(judgeTimes,bins)
#设置出横坐标
plt.xlabel("回溯法填充一个数独的数字填入次数")
#设置纵坐标的标题
plt.ylabel("频率")
#设置图注
plt.text(40000,200,avTstring)
#设置整个图片的标题
plt.title("数字填入次数分布直方图")
#画图
plt.show()