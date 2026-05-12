import ss_function as ss_f
#设置模数p
p=1000000007
#随机选取两个参与方，例如student2和student3，获得d2,d3，从而恢复出d=a+b+c
#读取d2,d3
d_23=[]
for i in range(2,4):
    with open(f'd_{i}.txt', "r") as f:  #打开文本
        d_23.append(int(f.read())) #读取文本
#加法重构获得d
d=ss_f.restructure_polynomial([2,3],d_23,2,p)
#计算平均值
d=d/3
print(f'得票结果平均值为：{d}')
