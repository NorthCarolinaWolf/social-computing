'''
Created on Oct 29, 2015

@author: PranavKulkarni
'''
import os
import operator
import random
import CreateDictionaries
from math import log10
import sys
from sys import argv

mapOfDictionaries = {}
modOfVocab = 0
stopwordsFile = "./lib/Project-Data/stopwords.csv"
miscFile = "./lib/Project-Data/misc.txt"
stopWords = []
split = []
featureSet = set()
dictDir = "./lib/Project-Data/Dictionaries/"
businessDir = "./lib/Project-Data/"
businessData = {}

def init():
    #Load stop words file
    #print "Starting the init"
    global stopWords
    with open(stopwordsFile, 'r') as stopFile:
        for line in stopFile:
            for stopword in line.split(","): #assuming stop words are all comma separated. No enter characters
                stopWords.append(stopword)
    stopFile.close()
    global mapOfDictionaries
    mapOfDictionaries = CreateDictionaries.getDictionaries()
    #BUILD dictionaries/vocabulary here for each category
    #print("Map of dictionaries : ", mapOfDictionaries)
    uniqueWords = set()
    for valueSet in mapOfDictionaries.values():
        for value in valueSet:
            uniqueWords.add(value)
    global modOfVocab        
    modOfVocab = len(uniqueWords)
    #print("Mod of vocab --> ", modOfVocab)
    #build business data
    global businessData
    with open(businessDir + 'SOC-BusinessDataCSV.csv') as fp:
        for line in fp:
            businessSplit = line.split(",")
            #print businessSplit
            if(businessSplit[0] == 'Id' and businessSplit[1] == 'Name of Business'):
                continue
            else:
                if(businessSplit[4] not in businessData.keys()): # if category is new
                    bList = []
                    bList.append(line)
                    businessData[businessSplit[4]] =  bList # it is the business category
                else:
                    businessData[businessSplit[4]].append(line)
    #print "Business data :- "                    
    #for key in businessData.keys():
        #print "$$$$", key, "----->>>>", businessData[key]
               
                           
def readMessage(message):
    #print "Reading message = ", message
    if not message:
        return "Error: Message is empty"
    else:
        message = cleanMessage(message)
        #spaceSeparatedWords = message.rsplit()
        global split
        split = message.rsplit()
        fSet = set() # need a set to store unique words/features of the message
        for word in split:
            if stopWords.count(word.lower())==0:
               fSet.add(word)
        global featureSet       
        featureSet = fSet
        #print("Features: ", featureSet)
        contactData = computeProbabilitiesAndCategorize()
        if type(contactData) == type('sample string'):
            print "None"
            return contactData
        else:
            #print "ContactData before returning = ", contactData
            printContact = contactData[0] + "$" + contactData[1] + "$" + contactData[2]
            print printContact
            #return contactData
    #self.computeProbabilities(self, split)

def cleanMessage(message):
        message = message.replace(","," ")
        message = message.replace(";"," ")
        message = message.replace("."," ")
        message = message.replace("?"," ")
        message = message.replace("!"," ")
        message = message.replace("'s"," ")
        return message.lower()      

def computeProbabilitiesAndCategorize():
    finalProb = {}
    for key in mapOfDictionaries.keys(): # for each category
        catDict = mapOfDictionaries[key]
        p = 1
        for feature in featureSet:
            if(feature in catDict):
                n = 1
                nk = split.count(feature)
                probFeatureGivenCategory = float((nk+1))/(n+modOfVocab)
                #print("Probability of ", feature, " given ", key, " = ", probFeatureGivenCategory)
                p = p*probFeatureGivenCategory
        if(p!=1):
            finalProb[key] = -log10(p)
        else:
            finalProb[key] = 0    
    #print("Final probabilities for each category --- ", finalProb)
    
    category = max(finalProb.iteritems(), key=operator.itemgetter(1))
    
    #Now that category is computed, give the business contact details
    if(category[1] == 0):
        miscF = open(miscFile, 'a')
        s = ""
        for item in featureSet:
        	s = s + item + " "
        miscF.write(s)
        miscF.write("\n")
        miscF.close()
        #print "This is miscellaneous category service. We will get back to you"
        return "This is miscellaneous category service. We will get back to you"
    else:
        contacts = businessData[category[0]]
        contact = random.choice(contacts)
        contactData = contact.split(",")
        #now return only what the web server expects. i.e. company name, contact, and category
        companyName = contactData[1]
        #contactInfo = contactData[] 
        contactInfo = contactData[2] + " " + contactData[3]
        content = contactData[4] #this is category
        returnThis = []
        returnThis.append(companyName)
        returnThis.append(contactInfo)
        returnThis.append(content)
        #print "Final contact to be returned = ", returnThis
        return returnThis

def main(argv):
    init()
    readMessage(argv)

if __name__ == "__main__":
    # str=''
    # for s in sys.argv[1:]:
    #     str+=s+' '
    main(argv[1])   

'''    
init()
readMessage("My car has a leaking battery with a flat tire. The hood is broken")
'''
'''
print "---------------------------------------------------------------"
readMessage("please fix my microwave")
'''


'''
BACKUP constructor of dictionaries

for file in os.listdir(self.dictDir):
                tempSet = set()
                print("Dict File ", file)
                
                with open(self.dictDir + file, 'r') as dictFile:
                    for line in dictFile:
                        for term in line.split(","):
                            tempSet.add(term)
                dictFile.close()
                self.mapOfDictionaries[file] = tempSet #insert the terms in a dictionary
        print("Map of dictionaries : ", self.mapOfDictionaries)'''  
