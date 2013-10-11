'''
Created on Oct 10, 2013

@author: Shane
'''

import urllib.request

#Set URL.     
abilityURL = "http://us.battle.net/api/wow/battlePet/ability/"

for i in range(1, 1201, 1):
    try:
        #If the ability exists
        curAbility = urllib.request.urlopen(abilityURL + str(i)).read().decode("utf-8")
        
        curAbilityText = open('..\\WoWPetBattler\\Ability\\' + str(i) + '.json', 'wt')
        curAbilityText.write("{")
        
        #Get current ability id.
        petAbilityIdStart = curAbility.find("\"id\":")
        petAbilityIdEnd = curAbility.find(",", petAbilityIdStart) + 1
        abilityId = curAbility[petAbilityIdStart:petAbilityIdEnd]
        curAbilityText.write(abilityId)
        
        #Get current ability name.
        abilityNameStart = curAbility.find("\"name\":")
        abilityNameEnd = curAbility.find(",", abilityNameStart) + 1
        abilityName = curAbility[abilityNameStart:abilityNameEnd]
        curAbilityText.write(abilityName)
        
        #Get current ability cooldown.
        roundsStart = curAbility.find("\"rounds\":")
        roundsEnd = curAbility.find(",", roundsStart) + 1
        rounds = curAbility[roundsStart:roundsEnd]
        curAbilityText.write(rounds)
        
        
        #Get current ability rounds.
        cooldownStart = curAbility.find("\"cooldown\":")
        cooldownEnd = curAbility.find(",", cooldownStart) + 1
        cooldown = curAbility[cooldownStart:cooldownEnd]
        curAbilityText.write(cooldown)
        
        #Get current ability type.
        petTypeIdStart = curAbility.find("\"petTypeId\":")
        petTypeIdEnd = curAbility.find(",", petTypeIdStart) + 1
        petTypeId = curAbility[petTypeIdStart:petTypeIdEnd]
        curAbilityText.write(petTypeId)
        
        #Get current ability passive state.
        isPassiveStart = curAbility.find("\"isPassive\":")
        isPassiveEnd = curAbility.find(",", isPassiveStart)
        isPassive = curAbility[isPassiveStart:isPassiveEnd]
        curAbilityText.write(isPassive)
        
        curAbilityText.write("}")
        curAbilityText.close()
        
        #Success
        print("Ability " + str(i) + " recorded.")
    
    except urllib.error.HTTPError:
        #Failure
        pass
    
print("Database update successful!")
