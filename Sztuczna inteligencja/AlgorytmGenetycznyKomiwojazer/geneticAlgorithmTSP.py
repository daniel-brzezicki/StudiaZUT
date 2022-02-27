from json.encoder import INFINITY
import random
import matplotlib.pyplot as plt
import numpy as np
import math



def CreateCities(cities, order):
    for i in range(totalCities):
       city = [random.randint(0,100),random.randint(0,100)]
       cities.append(city)
       order.append(i)


def shuffle(a, num):
    for i in range(num):
        idA=random.randint(0,len(a)-1)
        idB=random.randint(0,len(a)-1)
        swap(a,idA, idB)

    return a

def swap(a,i,j):
    temp=a[i]
    a[i]=a[j]
    a[j]=temp


def calcDistance(points,order):
    sum=0
    for i in range(len(order)-1):
        cityAID = order[i]
        cityA=points[cityAID]
        cityBID = order[i+1]
        cityB=points[cityBID]
        d = math.sqrt(math.pow(cityB[0]-cityA[0],2) + math.pow(cityB[1]-cityA[1],2))
        sum+=d

    return sum


def calcFitness(population,cities,bestEver,recordDistance):
    f=[]
    fit=[]
    be = bestEver
    rd = recordDistance
    bestInPop = INFINITY
    for i in range(len(population)):
        d = calcDistance(cities,population[i])
        if(d<rd):
            rd = d
            be=population[i]
        
        if(d<bestInPop):
            bestInPop=d

        f.append(1/(d+1))
        fit.append(d)
    return f, be, rd,bestInPop,fit


def normalizeFitness(fitness):
    sum=0
    for i in range(len(fitness)):
        sum+=fitness[i]

    for i in range(len(fitness)):
        fitness[i]=fitness[i]/sum

    return fitness


def selection(population, probability):
    id = 0
    r = random.random()

    while(r>0):
        r=r-probability[id]
        id=id+1

    id=id-1
    return population[id]


def randomToTour(population):
    number = random.randrange(4,12)

    tournamentIndexes = []

    for i in range(number):
        id = random.randrange(0,len(population)-1)
        if(id not in tournamentIndexes):
            tournamentIndexes.append(id)
        else:
            i = i-1


    return tournamentIndexes

def tourSelection(population, probability):
    bestID = 0
    
    toTournament = randomToTour(population)
    best=probability[toTournament[0]]

    for i in range(len(toTournament)):
        if(best<probability[toTournament[i]]):
            best=probability[toTournament[i]]
            bestID=toTournament[i]

    return bestID



def newTour(population,probability):
    idA = random.randrange(0,len(population)-1)
    idB = random.randrange(0,len(population)-1)

    if(idA== idB):
        idB=newTour(population,probability)

    if(probability[idA] > probability[idB]):
        return idA
    else:
        return idB
    

def mutate(order,totalCities, mutationRate):
    for i in range(totalCities):
        if(random.random()<mutationRate):
            idA=math.floor(random.randint(0,len(order)-1))
            #idB=math.floor(random.randint(0,len(order)-1))
            idB=(idA+1)%totalCities
            swap(order,idA,idB)

def crossOver(orderA,orderB,type):
    newOrder=[]
    if(type==0):
        end =  random.randint(0,len(orderA)-1)

        for i in range(end):
            newOrder.append(orderA[i])

        for i in range(len(orderB)):
            city = orderB[i]
            if(city not in newOrder):
                newOrder.append(city)
    elif(type==1): #OX
        start = random.randint(0,len(orderA)-2)
        end =  random.randint(start+1,len(orderA)-1)

        notDuplicated=[]
        generated=[]

        point = start
        while(point<end):
            generated.append(orderA[point])
            point=point+1

        for i in range(len(orderB)):
            city = orderB[i]
            if(city not in generated):
                notDuplicated.append(city)

        pointNotDuplicated=0
        while(pointNotDuplicated<start):
            newOrder.append(notDuplicated[pointNotDuplicated])
            pointNotDuplicated=pointNotDuplicated+1

        point = start
        while(point<end):
            newOrder.append(orderA[point])
            point=point+1

        while(pointNotDuplicated<len(notDuplicated)):
            newOrder.append(notDuplicated[pointNotDuplicated])
            pointNotDuplicated=pointNotDuplicated+1
    elif(type==2): #CX
        for i in range(len(orderA)):
            newOrder.append(-1)

        point=0
        currentCity=orderB[point]
        while(orderA[0]!=currentCity):
            newOrder[point]=orderA[point]
            currentCity=orderB[point]
            for i in range(len(orderA)):
                if(orderA[i]==currentCity):
                    point=i

        for i in range(len(orderB)):
            if(newOrder[i]==-1):
                newOrder[i]=orderB[i]
    elif(type==3):
        start = random.randint(0,len(orderA)-2)
        end =  random.randint(start+1,len(orderA)-1)

        for i in range(len(orderA)):
            newOrder.append(-1)

        point=start
        generated = []
        while(point<end):
            generated.append(orderA[point])
            newOrder[point]=orderA[point]
            point=point+1



        point=start
        toFind=orderA[point]
        temp=orderB[point]
        while(point<end):
            flag=True
            for i in range(len(newOrder)):
                if(newOrder[i]==temp):
                    point=point+1
                    flag=False

            if(flag):
                if(orderA[point]!=orderB[point]):

                    a=0
                    for i in range(len(orderB)):
                        if(orderB[i]==toFind):
                            a=i
                            break

                    if(a>start and a<end):
                        toFind = orderA[a]
                    else:
                        newOrder[a]=temp
                        point=point+1
                else:
                    point=point+1


        for i in range(len(orderB)):
            city = orderB[i]
            if(city not in newOrder):
                for a in range(len(newOrder)):
                    if(newOrder[a]==-1):
                        newOrder[a]=city
                        break



    return newOrder



def nextGeneration(population,fitness,totalCities,crossOverType):
    newPopulation=[]
    oldPopulation= population.copy()
    for i in range(len(oldPopulation)):

        
        #orderA =population[newTour(population,fitness)]
        #orderB =population[newTour(population,fitness)]
        orderA = population[tourSelection(oldPopulation,fitness)]
        orderB = population[tourSelection(oldPopulation,fitness)]
        #orderA = selection(oldPopulation,fitness)
        #orderB = selection(oldPopulation,fitness)


        norder = crossOver(orderA,orderB,crossOverType)

        mutate(norder,totalCities,0.1)
        newPopulation.append(norder)

    return newPopulation
        

def ga(population,bestEver,recordDistance,cities,totalCities,gens, crossOverType,avg):
    fitness=[]
    g=[]
    best=[]
    bestSoFar=[]
    for i in range(gens):
        g.append(i)

        fitness, bestEver, recordDistance,bestInPop,fitDist= calcFitness(population,cities.copy(),bestEver, recordDistance)
        fitness = normalizeFitness(fitness)
        population = nextGeneration(population,fitness,totalCities,crossOverType)

        x=[]
        y=[]
        for j in range(len(bestEver)):
            x.append(cities[bestEver[j]][0])
            y.append(cities[bestEver[j]][1])

        sum=0
        leng=0
        for k in range(len(fitDist)):
            sum=sum+fitDist[k]
            leng=leng+len(avg)+1
        averageFitness = sum/leng

        avg.append(averageFitness)

        best.append(bestInPop)

        bestSoFar.append(recordDistance)


        if((i+1)%(gens/4)==0 or i==0):
            plt.scatter(x,y)
            plt.plot(x,y)
            plt.title("gen "+str(i+1))
            plt.show(block=False)
            plt.pause(1)
            plt.close()

    return g, avg, best,bestSoFar,x,y

        
def gaWithPlots(mainPopulation,bestEver,recordDistance,cities,totalCities,gens,type):
    avg=[]
    g,avg,best,bestsofar,x,y = ga(mainPopulation,bestEver,recordDistance,cities,totalCities,gens,type,avg)


    plt.plot(g,avg)
    plt.title('Srednie przystosowanie')
    plt.show()
    plt.plot(g,best)
    plt.title('Najlepszy z populacji')
    plt.show()
    plt.plot(g,bestsofar)
    plt.title('Najlepszy dotychczas')
    plt.show()
        


cities = []
totalCities=50

order =[]

popSize=300
population=[]
fitness=[]

bestEver=[]
recordDistance=INFINITY

statusP=0


CreateCities(cities,order)

for i in range(popSize):
    population.append(order.copy())
    population[i]=shuffle(population[i], 100)


mainPopulation=population.copy()


gens = 1000
gaWithPlots(mainPopulation,bestEver,recordDistance,cities,totalCities,gens,2)


#gaWithPlots(mainPopulation,bestEver,recordDistance,cities,totalCities,gens,2)

#gaWithPlots(mainPopulation,bestEver,recordDistance,cities,totalCities,gens,3)