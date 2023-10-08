import numpy as np

#tablice
a=np.array([1,2,3,4,5,6,7]) 
b=np.array([[1,2,3,4,5], [6,7,8,9,10]])

np.transpose(b)

ar=np.arange(100)
print(ar)

ar=np.linspace(0,2,num=10)
print(ar)

ar=np.arange(0,101,5)
print(ar)

#liczby losowe

ar=np.random.randn(20)
ar=np.around(ar,2)
print(ar)

ar=np.random.randint(1,1001,size=100)
print(ar)

ar=np.zeros((3,2))
print(ar)

ar=np.ones((3,2))
print(ar)

ar=np.random.randint(1000,size=(5,5),dtype='int32')
print(ar)

a = np.linspace(0.0, 10.0, num=10)
b = a.astype(int)
a = np.around(a,0)
a = a.astype(int)
print('a = ',a)
print('b = ',b)

#Selekcja danych
ar=np.array([[1,2,3,4,5], [6,7,8,9,10]],dtype=np.int32)

print(np.ndim(ar))

print(np.size(ar))

print(ar[0,2],',',ar[0,4])

print(ar[0,1],',',ar[0,3])

print(ar[0,:])

print(ar[:,0])

ar=np.random.randint(101,size=(20,7))
print(ar)
print(ar[:,(0,1,2,3)])

#operacje matematyczne i logiczne

a=np.random.randint(0,11,size=(3,3))
b=np.random.randint(0,11,size=(3,3))

print(a+b)

print(a*b)

print(a/b)

print(a**b)

print(a>=4)

print(a<=1)

print(np.trace(b))

#dane statystyczne

print(b.sum(), b.min(), b.max(), np.std(b))

print(b.mean(axis=1))
print(b.mean(axis=0))

#rzutowanie wymiarów

ar=np.random.randint(0,101,size=50)

ar1=ar.reshape(10,5)
ar2=ar.resize(10,5)

print(ar.ravel())   

a=np.random.randint(0,11,size=5)
b=np.random.randint(0,11,size=4)

#print(a+b)   

b_new=b[:,np.newaxis]

print(a+b_new)

#sortowanie danych

a=np.random.randn(5,5)

print(-np.sort(a,axis=0))

print(np.sort(a,axis=1))

b=np.array([(1,'MZ','mazowieckie'),(2,'ZP','zachodniopomorskie'),(3,'ML','malopolskie')])
print(b)
#nie do konca wiem jak rozwaizac to zadanie

#PODSUMOWANIE
#zadanie 1
ar=np.random.randint(0,101,size=(10,5))
print('Suma glownej przekatnej: ', ar.trace())
print('Glowna przekątna: ', np.diag(ar))

#zadanie 2
a = np.random.randn(14)
b = np.random.randn(14)
print(a*b)

#zadanie 3
a = np.random.randint(1, 101, size=15).reshape(3,5)
b = np.random.randint(1, 101, size=15).reshape(3,5)
print(a+b)

#zadanie 4
a = np.random.randint(0,11,(5,4))
b = np.random.randint(0,11,(4,5))
ans = a+b.swapaxes(0,1)
print(ans)

#zadanie 5
print(a[:,(2,3)]*b.swapaxes(0, 1)[:,(2,3)])

#zadanie 6
a=np.random.normal(size=10)
print('a: mean =',a.mean(),'std =',a.std(),'var =',a.var())
b=np.random.uniform(size=10)
print('b: mean =',b.mean(),'std =',b.std(),'var =',b.var())

#zadanie 7
a=np.random.randint(0,51,size=(2,2))
b=np.random.randint(0,51,size=(2,2))
print('a*b =',a*b,'\na.dot(b) =',a.dot(b))
#dot to procedura mnożenia mecierzy, a samo a*b oferuje nam wymnożenie danych elementów macierzy przez siebie

#zadanie 8
x = np.array([[0, 1, 2, 3, 4],
              [5, 6, 7, 8, 9],
              [10, 11, 12, 13, 14],
              [15, 16, 17, 18, 19]], dtype=np.int32)
print(x.strides)

#x - nasz tablica z ktorej wybieramy dane
#(2,3) 2 - ilosc wierszy, ktore zostana wyswietlone w nowej tablicy i analogicznie 3 liczba kolumn 
y=np.lib.stride_tricks.as_strided(x,(2,3))
print(y)

#zadanie 9
a = np.random.randint(0, 21, size=10)
b = np.random.randint(0, 21, size=10)
print(np.vstack((a,b)))
#vstack tworzy macierz, rozmiar musi się pokrywać
print(np.hstack((a,b)))
#hstack łączy tablice w jedną

#zadanie 10 
#nie umiem go rozwiązać