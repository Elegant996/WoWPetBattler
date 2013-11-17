'''
Created on Oct 6, 2013

@author: Shane
'''

from sys import exit
import urllib.request

#Open library.
try:
    baseStatsLib = open('..\\AddOns\\PetPixels\\Libs\\LibPetBreedInfo-1.0\\LibPetBreedInfo-1.0.lua', 'r').read()
except IOError:
    #Failure
    print("Please move LibPetBreedInfo-1.0 folder into the script's folder.")
    exit(0)

#Find our base stats section and set URL.     
baseStatsSection = baseStatsLib.find("lib.breedData.speciesToBaseStatProfile")
speciesURL = "http://us.battle.net/api/wow/battlePet/species/"

for i in range(1, 1501, 1):
    try:
        #If the species exists
        curSpecies = urllib.request.urlopen(speciesURL + str(i)).read().decode("utf-8")
        
        curSpeciesText = open('..\\WoWPetBattler\\Species\\' + str(i) + '.json', 'wt')
        curSpeciesText.write("{")
        
        #Get current species id.
        petSpeciesIdStart = curSpecies.find("\"speciesId\":")
        petSpeciesIdEnd = curSpecies.find(",", petSpeciesIdStart) + 1
        speciesId = curSpecies[petSpeciesIdStart:petSpeciesIdEnd]
        curSpeciesText.write(speciesId)
        
        #Get current pet type.
        petTypeIdStart = curSpecies.find("\"petTypeId\":")
        petTypeIdEnd = curSpecies.find(",", petTypeIdStart) + 1
        petTypeId = curSpecies[petTypeIdStart:petTypeIdEnd]
        curSpeciesText.write(petTypeId)
        
        #Get current pet name.
        petNameStart = curSpecies.find("\"name\":")
        petNameEnd = curSpecies.find(",", petNameStart) + 1
        petName = curSpecies[petNameStart:petNameEnd]
        curSpeciesText.write(petName)
        
        #Get current pet base health.
        petBaseHealthIndex = baseStatsLib.find(str(i), baseStatsSection)
        petBaseHealthStart = baseStatsLib.find("{", petBaseHealthIndex) + 1
        petBaseHealthEnd = baseStatsLib.find(",", petBaseHealthStart)
        curSpeciesText.write("\"baseHealth\":" + baseStatsLib[petBaseHealthStart:petBaseHealthEnd] + ",")
        
        #Get current pet base power.
        petBasePowerStart = petBaseHealthEnd + 2
        petBasePowerEnd = baseStatsLib.find(",", petBasePowerStart)
        curSpeciesText.write("\"basePower\":" + baseStatsLib[petBasePowerStart:petBasePowerEnd] + ",")
        
        #Get current pet base speed.
        petBaseSpeedStart = petBasePowerEnd + 2
        petBaseSpeedEnd = baseStatsLib.find("}", petBaseSpeedStart)
        curSpeciesText.write("\"baseSpeed\":" + baseStatsLib[petBaseSpeedStart:petBaseSpeedEnd] + ",")
        
        #Get current pet abilities.
        curSpeciesText.write("\"abilities\":[")
        petAbilitySection = curSpecies.find("\"abilities\":")
        for j in range(0, 6, 1):
            petAbilityIndex = curSpecies.find("\"order\":" + str(j), petAbilitySection)
            petAbilityIdStart = curSpecies.find("\"id\":", petAbilityIndex)
            petAbilityIdEnd = curSpecies.find(",", petAbilityIdStart);
            petAbilityId = curSpecies[petAbilityIdStart:petAbilityIdEnd]
            curSpeciesText.write("{" + petAbilityId + "}")
            if j != 5:
                curSpeciesText.write(",")
        
        curSpeciesText.write("]")
        curSpeciesText.write("}")
        curSpeciesText.close()
        
        #Success
        print("Species " + str(i) + " recorded.")
    
    except urllib.error.HTTPError:
        #Failure
        pass
    
print("Database update successful!")
