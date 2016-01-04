# -*- coding: utf-8 -*-
import numpy as np
import scipy.sparse
import random
import math
import time

class CF:
    data_address = ''
    datasets = []
    np_training_datasets = np.zeros(1)
    sim_matrix = np.zeros(1)
    topN = 10
    
    def __init__(self,data_address = 'movie',n=6):
        self.data_address = data_address
        self.topN = n
        
    
    def loadData(self,TimeIntervalID = ''):
        self.np_training_datasets_old = self.np_training_datasets
        Users = []
        Movies = []
        U2S = []
        input_file = open(self.data_address+TimeIntervalID,'r')
        for line in input_file:
            tmp = line.split()
            Users.append(int(tmp[0]))
            Movies.append(int(tmp[1]))
            reT = int(tmp[2])
           #U2S.append((reT if reT < 1.6 else 1.6))
            U2S.append(reT)
        self.np_training_datasets = scipy.sparse.csr_matrix((U2S,(Users,Movies))).todense()    
        input_file.close()
    
    def transpose(self):
        self.np_training_datasets = np.transpose(self.np_training_datasets)
        
    def split_testData(self,density = 0.8):
        testDataset = []
        [x,y] = self.np_training_datasets.shape
        for i in range(x):
            for j in range(y):
                if self.np_training_datasets[i,j] != 0 :
                    if random.random() > density:
                        testDataset.append((i,j,self.np_training_datasets[i,j]))
                        self.np_training_datasets[i,j] = .0
        self.testDataset = testDataset
        
# Returns a distance-based similarity score for person1 and person2
    def sim_distance(self,person1,person2):
  # Get the list of shared_items
        I = np.logical_and(self.np_training_datasets[person1,:],self.np_training_datasets[person2,:]).astype(int)
        if not I.any():
            return .0
        sum_of_squares = np.sum(np.multiply(np.power(self.np_training_datasets[person1,:]-self.np_training_datasets[person2,:],2),I))       
        return 1/(1+math.sqrt(sum_of_squares/np.sum(I)))

    def get_simMatrix(self,similarity=sim_distance):
        x,y = self.np_training_datasets.shape
        self.sim_matrix = np.zeros((x,x))
        for i in range(x-1):
            for j in range(i+1,x):
                self.sim_matrix[i,j] = similarity(self,i,j)
                self.sim_matrix[j,i] = self.sim_matrix[i,j]
    
    def get_topMatchesMatrix(self):
        x = self.np_training_datasets.shape[0]
        self.topMatchesMatrix = np.zeros((x,self.topN),dtype = np.int)
        for person in range(x):
            person2all_scores = self.sim_matrix[person,:].copy()
            person_topScores_indexes = []
            for i in range(self.topN):
                index = np.argmax(person2all_scores)
                person_topScores_indexes.append(index)
                person2all_scores[index] = .0
            self.topMatchesMatrix[person,:] = np.array(person_topScores_indexes,dtype = int)

    def recommendation(self):
        x,y = self.np_training_datasets.shape
        self.recommendationMatrix = np.matrix(np.zeros((x,y)))
        for person in range(x):
            I = np.matrix(np.logical_not(self.np_training_datasets[person,:]).astype(int))
            s = np.matrix(np.zeros_like(I))
            for match in self.topMatchesMatrix[person,:]:
                I_match = np.logical_and(self.np_training_datasets[match,:],self.np_training_datasets[match,:]).astype(int)
                sim = self.sim_matrix[person,match]
                s = np.add(s,np.multiply(sim,I_match))
                self.recommendationMatrix[person,:] += np.multiply(np.multiply(self.np_training_datasets[match,:],I),sim)
            old_err_state = np.seterr(divide='raise')
            ignored_states = np.seterr(**old_err_state)            
            self.recommendationMatrix[person,:] = np.divide(self.recommendationMatrix[person,:],s)

    def errMetrics(self,method = 'RMSE'):
        err = .0
        n = len(self.testDataset)
        print n
        for (i,j,q) in self.testDataset:
            eui = self.recommendationMatrix[i,j]
            if not np.isnan(eui):
                if method == 'RMSE':
                    err += pow(q - eui,2)
                elif method == 'MAE':
                    err += abs(q - eui)
            else:
                n -= 1
        if method == 'RMSE':
            print n
            return math.sqrt(err/n)
            
        elif method == 'MAE':
            return err/n
                   
## Returns the Pearson correlation coefficient for p1 and p2
#def sim_pearson(prefs,p1,p2):
#  # Get the list of mutually rated items
#  si={}
#  for item in prefs[p1]: 
#    if item in prefs[p2]: si[item]=1
#
#  # if they are no ratings in common, return 0
#  if len(si)==0: return 0
#
#  # Sum calculations
#  n=len(si)
#  
#  # Sums of all the preferences
#  sum1=sum([prefs[p1][it] for it in si])
#  sum2=sum([prefs[p2][it] for it in si])
#  
#  # Sums of the squares
#  sum1Sq=sum([pow(prefs[p1][it],2) for it in si])
#  sum2Sq=sum([pow(prefs[p2][it],2) for it in si])	
#  
#  # Sum of the products
#  pSum=sum([prefs[p1][it]*prefs[p2][it] for it in si])
#  
#  # Calculate r (Pearson score)
#  num=pSum-(sum1*sum2/n)
#  den=sqrt((sum1Sq-pow(sum1,2)/n)*(sum2Sq-pow(sum2,2)/n))
#  if den==0: return 0
#
#  r=num/den
#
#  return r
#
## Returns the best matches for person from the prefs dictionary. 
## Number of results and similarity function are optional params.
#
#
## Gets recommendations for a person by using a weighted average
## of every other user's rankings
#def getRecommendations(prefs,person,similarity=sim_pearson):
#  totals={}
#  simSums={}
#  for other in prefs:
#    # don't compare me to myself
#    if other==person: continue
#    sim=similarity(prefs,person,other)
#
#    # ignore scores of zero or lower
#    if sim<=0: continue
#    for item in prefs[other]:
#	    
#      # only score movies I haven't seen yet
#      if item not in prefs[person] or prefs[person][item]==0:
#        # Similarity * Score
#        totals.setdefault(item,0)
#        totals[item]+=prefs[other][item]*sim
#        # Sum of similarities
#        simSums.setdefault(item,0)
#        simSums[item]+=sim
#
#  # Create the normalized list
#  rankings=[(total/simSums[item],item) for item,total in totals.items()]
#
#  # Return the sorted list
#  rankings.sort()
#  rankings.reverse()
#  return rankings
#
#def transformPrefs(prefs):
#  result={}
#  for person in prefs:
#    for item in prefs[person]:
#      result.setdefault(item,{})
#      
#      # Flip item and person
#      result[item][person]=prefs[person][item]
#  return result
#
#
#def calculateSimilarItems(prefs,n=10):
#  # Create a dictionary of items showing which other items they
#  # are most similar to.
#  result={}
#  # Invert the preference matrix to be item-centric
#  itemPrefs=transformPrefs(prefs)
#  c=0
#  for item in itemPrefs:
#    # Status updates for large datasets
#    c+=1
#    if c%100==0: print "%d / %d" % (c,len(itemPrefs))
#    # Find the most similar items to this one
#    scores=topMatches(itemPrefs,item,n=n,similarity=sim_distance)
#    result[item]=scores
#  return result
#
#def getRecommendedItems(prefs,itemMatch,user):
#  userRatings=prefs[user]
#  scores={}
#  totalSim={}
#  # Loop over items rated by this user
#  for (item,rating) in userRatings.items( ):
#
#    # Loop over items similar to this one
#    for (similarity,item2) in itemMatch[item]:
#
#      # Ignore if this user has already rated this item
#      if item2 in userRatings: continue
#      # Weighted sum of rating times similarity
#      scores.setdefault(item2,0)
#      scores[item2]+=similarity*rating
#      # Sum of all the similarities
#      totalSim.setdefault(item2,0)
#      totalSim[item2]+=similarity
#
#  # Divide each total score by total weighting to get an average
#  rankings=[(score/totalSim[item],item) for item,score in scores.items( )]
#
#  # Return the rankings from highest to lowest
#  rankings.sort( )
#  rankings.reverse( )
#  return rankings

if __name__ == "__main__":
    myCF = CF()
    myCF.loadData(TimeIntervalID = '')
#    myCF.transpose()
    myCF.split_testData(density=0.1)
    start = time.clock()
    myCF.get_simMatrix()
    myCF.get_topMatchesMatrix()
    myCF.recommendation()
    end = time.clock()
    print end - start
    print myCF.errMetrics()
    f = open('prediction', 'w+')
    x,y = myCF.recommendationMatrix.shape
    for i in range(x):
        for j in range(y):
            if not np.isnan(myCF.recommendationMatrix[i,j]):
                f.write(str(i)+' '+str(j)+' '+str(myCF.recommendationMatrix[i,j])+'\n')
    f.close()
