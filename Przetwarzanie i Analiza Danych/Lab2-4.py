import pandas as pd
import numpy as np
import scipy.stats
import matplotlib.pyplot as plt

#Manipulowanie danymi
a= pd.DataFrame(np.random.normal(size=(5,3)),index=pd.date_range(start='3/1/2020',end='3/5/2020'),columns=['a','b','c'])
print(a)

d=pd.DataFrame(np.random.randint(1,100,(20,3)), columns=['a','b','c'])
print(d)

print(d.head(3))
print(d.tail(3))
print(d.index.tolist())
print(d.columns)
print(d.values)
print(d.sample(axis=1))

print(d.describe())
if d.describe().count().a > 0.0 and d.describe().count().b > 0.0 and d.describe().count().c > 0.0:
 print(d.describe().count())
if d.describe().mean().a > 0.0 and d.describe().mean().b > 0.0 and d.describe().mean().c > 0.0:
 print(d.describe().mean())
if d.describe().std().a > 0.0 and d.describe().std().b > 0.0 and d.describe().std().c > 0.0:
 print(d.describe().std())
if d.describe().min().a > 0.0 and d.describe().min().b > 0.0 and d.describe().min().c > 0.0:
 print(d.describe().min())

p = d.describe()
p.loc[p["a"] >= 0]

for x in range(7):
    if p["a"][x]>0.0:
      print(p["a"][x])

print("Srednia a: ",np.average(p["a"]))
print("Srednia b: ",np.average(p["b"]))
print("Srednia c: ",np.average(p["c"]))

a = pd.DataFrame([['a', 1], ['b', 2]], columns=['litera', 'liczba'])
b = pd.DataFrame([['c', 3], ['d', 4]], columns=['litera', 'liczba'])

p = pd.concat([a,b])
print(np.transpose(p))

d = pd.DataFrame({"x": [1, 2, 3, 4, 5], "y": ['a', 'b', 'a', 'b', 'b']}, index=np.arange(5))
d.index.name='id'
print(d.sort_index(ascending=True))
print(d.sort_values(by='y',ascending=False))

dict = {"Day": ['Mon', 'Tue', 'Mon', 'Tue', 'Mon'], "Fruit": ['Apple','Apple', 'Banana', 'Banana', 'Apple'], "Pound": [10, 15, 50, 40, 5], 'Profit':[20, 30, 25, 20, 10]}
d = pd.DataFrame(dict)
print(d)
print(d.groupby('Day').sum())
print(d.groupby(['Day','Fruit']).sum())

d=pd.DataFrame(np.random.randn(20, 3),index=np.arange(20), columns=['A','B','C'])
d.index.name='id'
print(d)
d['B']=1
print(d)
d.iloc[1,2]=10
print(d)
d[d<0]=-d
print(d)

d.iloc[[0, 3], 1] = np.nan
print(d)
d.fillna(0, inplace=True)
print(d)
d.iloc[[0, 3], 1] = np.nan
d=d.replace(np.nan,value=-9999)
print(d)
d.iloc[[0, 3], 1] = np.nan
print(pd.isnull(d))

#Zadanie 1
print("\n Zadanie 1 \n")
df = pd.DataFrame({'x':[1,2,3,4,5], 'y':['a','b','a','b','b']})
print(df.groupby('y').mean())

#Zadanie 2
print("\n Zadanie 2 \n")
#print(df.value_counts())
print(df['x'].value_counts())
print(df['y'].value_counts())

#Zadanie 3
print("\n Zadanie 3 \n")
df = np.loadtxt('autos.csv',dtype=str,delimiter=",") 
print(df)
#loadtxt nie dzieli poszczegolnych wierszy na kolumny, wymaga dodatkowej implementacji separacji

print("\n read \n")
df=pd.read_csv('autos.csv')
print(df.head())
#read_csv zachowuje cale dane 

#Zadanie 4
print("\n Zadanie 4 \n")
print(df.groupby('make').mean()[['city-mpg','highway-mpg']])

#Zadanie 5
print("\n Zadanie 5 \n")
print(df.groupby('make')['fuel-type'].value_counts())


#Zadanie 6
print("\n Zadanie 6 \n")

print(df[['length','city-mpg']].head())

k1=np.polyfit(df['length'],df['city-mpg'],1)
print(k1)

k2=np.polyfit(df['length'],df['city-mpg'],2)
print(k2)

print(np.polyval(k1, 168.8))

print(np.polyval(k2, 168.8))

#Zadanie 7
print("\n Zadanie 7 \n")
print(scipy.stats.pearsonr(df['length'],df['city-mpg']))

#Zadanie 8
print("\n Zadanie 8 \n")
plt.grid()
plt.scatter(df['length'],df['city-mpg'])
plt.plot(range(140,210,1), np.polyval(k2,range(140,210,1)),'g')
plt.show()

#Zadanie 9
print("\n Zadanie 9 \n")
g = scipy.stats.kde.gaussian_kde(df['length'])
x = np.linspace(140,210,100)
y = g(x)

ax1=plt.subplot(2,1,1)
ax2=plt.subplot(2,1,2)

ax1.grid()
ax1.scatter(df['length'],df['city-mpg'],label='probe')

ax2.grid()
ax2.plot(x,y,'blue',label='funkcja gestosci')

plt.xlabel('length')

ax1.legend()
ax2.legend()

plt.show()

#Zadanie 10
print("\n Zadanie 10 \n")
g = scipy.stats.kde.gaussian_kde(df['width'])
x = np.linspace(60,72,100)
y = g(x)

plt.ylabel('width')

ax1=plt.subplot(1,2,1)
ax2=plt.subplot(1,2,2)

ax1.scatter(df['length'],df['width'],label='probe')
ax2.plot(x,y,'blue',label='width')

ax1.grid()
ax2.grid()

ax1.legend()
ax2.legend()

plt.show()

#Zadanie 11
print("\n Zadanie 11 \n")
x,y=np.mgrid[60:72,140:210]
p=np.vstack([x.ravel(),y.ravel()])
g = scipy.stats.kde.gaussian_kde(np.vstack([df['width'],df['length']]))
z=np.reshape(g(p),x.shape)

plt.contour(x,y,z,linewidths=2,cmap='RdGy')
plt.scatter(df['width'],df['length'],label='probe')
plt.grid()
plt.legend()
plt.xlabel('width')
plt.ylabel('length')

plt.savefig('zadanie11.png')
plt.savefig('zadanie11.pdf')

plt.show()