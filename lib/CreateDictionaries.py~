'''
Created on Oct 30, 2015

@author: PranavKulkarni
'''
import threading
import os
  
lock = threading.Lock()
numberOfThreads = 2
dictDir =  "./Project Data/Dictionaries/"
setOfDictFiles = {}
mapOfDictionaries = {}

for file in os.listdir(dictDir):
    setOfDictFiles[file] = 'unprocessed' 
   
def createDictionaries():
    for key, value in setOfDictFiles.iteritems():
        if(value == 'unprocessed'):
            with lock:
                setOfDictFiles[key] = 'processed'
            tempSet = set()
            with open(dictDir + key, 'r') as dictFile:
                    for line in dictFile:
                        for term in line.split(","):
                            tempSet.add(term)
            dictFile.close()
            mapOfDictionaries[key.replace('.txt','')] = tempSet
    
threads = []
for i in range (numberOfThreads):
    t = threading.Thread(target = createDictionaries, name="thread-" + str(i), args = ())
    threads.append(t)
    t.start()
    t.join()

def getDictionaries():
    return mapOfDictionaries
      
