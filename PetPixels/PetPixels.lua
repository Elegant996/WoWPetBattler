----------------------------------------------
-- Constants
----------------------------------------------

local LibPetBreedInfo = LibStub("LibPetBreedInfo-1.0");

local PetPixels, events = CreateFrame("Frame"), {};

local mUpdateInterval, mVersion = 0.04, 56;
local mBorderR1, mBorderG1, mBorderB1 = 16/255, 8/255, 12/255;
local mBorderR2, mBorderG2, mBorderB2 = 12/255, 8/255, 16/255;

local myTeam, enemyTeam, teams, numAbilities, team = 1, 2, 2, 3, {1, 2};

local maxIndex, uiBox = 40, {};
for i=1, maxIndex do uiBox[i] = _G[string.format('uiBox%02d',i)]; end

----------------------------------------------
-- Variables
----------------------------------------------

local inPetBattle, wonLastBattle, teamIsAlive, playerIsGhost, playerIsDead, playerAffectingCombat = false, false, false, nil, nil, nil;
local queueEnabled, queueState, canAccept, initialized, selectPet, selectAbility = false, nil, false, false, false, false;

local teamSize, teamsActivePet, petsSpecies, petsBreed = {0, 0}, {0, 0}, {{}, {}}, {{}, {}};
local petsCurrentHP, petsLevel, petsQuality = {{}, {}}, {{}, {}}, {{}, {}};
local petsAbilitiesVerified, petsAbilities, petsAbilitiesCD = {{}, {}}, {{}, {}}, {{}, {}};
local petsNumAuras, petsAuras, petsAurasDuration = {}, {}, {};
for i=0, teams do petsNumAuras[i], petsAuras[i], petsAurasDuration[i] = {}, {}, {}; end

----------------------------------------------
-- Events
----------------------------------------------

function events:CHAT_MSG_PET_BATTLE_COMBAT_LOG(...)
	--print("CHAT_MSG_PET_BATTLE_COMBAT_LOG");
	if (not initialized or not isPVPBattle()) then
		return;
	end

	local check, _, abilityID, maxHealth, power, speed = string.find(..., "HbattlePetAbil:([%d]+):([%d]+):([%d]+):([%d]+).*");
	if(not check) then return; end

	abilityID, power, speed = tonumber(abilityID), tonumber(power), tonumber(speed);

	if (power == C_PetBattles.GetPower(enemyTeam, teamsActivePet[enemyTeam]) and speed == C_PetBattles.GetSpeed(enemyTeam, teamsActivePet[enemyTeam])) then
		local idTable, _ = C_PetJournal.GetPetAbilityList(C_PetBattles.GetPetSpeciesID(enemyTeam, teamsActivePet[enemyTeam]));

		for i=0, 5 do
			if (idTable[i+1] == abilityID and not petsAbilitiesVerified[enemyTeam][teamsActivePet[enemyTeam]][i%3+1]) then
				petsAbilitiesVerified[enemyTeam][teamsActivePet[enemyTeam]][i%3+1] = true;
				petsAbilities[enemyTeam][teamsActivePet[enemyTeam]][i%3+1] = math.ceil((i+1)/3);
				break;
			end
		end
	end
end

function events:PET_BATTLE_HEALTH_CHANGED(...)
	--print("PET_BATTLE_HEALTH_CHANGED")
	for i=1, teams do
		for j=1, teamSize[i] do
			petsCurrentHP[i][j] = C_PetBattles.GetHealth(i, j);
		end
	end
end

function events:PET_BATTLE_AURA_CHANGED(...)
	--print("PET_BATTLE_AURA_CHANGED");
	for i=0, teams do
		for j=(i==0) and 0 or 1, (i==0) and 0 or teamSize[i] do
			petsNumAuras[i][j], petsAuras[i][j], petsAurasDuration[i][j] = C_PetBattles.GetNumAuras(i, j), {}, {};
			for k=1, petsNumAuras[i][j] do
				petsAuras[i][j][k], _, petsAurasDuration[i][j][k], _ = C_PetBattles.GetAuraInfo(i, j, k);
			end
		end
	end
end

function events:PET_BATTLE_AURA_APPLIED(...)
	--print("PET_BATTLE_AURA_APPLIED");
	for i=0, teams do
		for j=(i==0) and 0 or 1, (i==0) and 0 or teamSize[i] do
			petsNumAuras[i][j], petsAuras[i][j], petsAurasDuration[i][j] = C_PetBattles.GetNumAuras(i, j), {}, {};
			for k=1, petsNumAuras[i][j] do
				petsAuras[i][j][k], petsAurasDuration[i][j][k] = (select(1, C_PetBattles.GetAuraInfo(i, j, k))), (select(3, C_PetBattles.GetAuraInfo(i, j, k)));
			end
		end
	end
end

function events:PET_BATTLE_AURA_CANCELED(...)
	--print("PET_BATTLE_AURA_CANCELED");
	for i=0, teams do
		for j=(i==0) and 0 or 1, (i==0) and 0 or teamSize[i] do
			petsNumAuras[i][j], petsAuras[i][j], petsAurasDuration[i][j] = C_PetBattles.GetNumAuras(i, j), {}, {};
			for k=1, petsNumAuras[i][j] do
				petsAuras[i][j][k], _, petsAurasDuration[i][j][k], _ = C_PetBattles.GetAuraInfo(i, j, k);
			end
		end
	end
end

function events:PET_BATTLE_PET_ROUND_PLAYBACK_COMPLETE(...)
	--print("PET_BATTLE_PET_ROUND_PLAYBACK_COMPLETE");
	if (initialized) then
		for i=1, teams do
			for j=1, teamSize[i] do
				for k=1, numAbilities do
					if (C_PetBattles.GetAbilityState(i, j, k) ~= nil and (select(2, C_PetBattles.GetAbilityState(i, j, k))) >= (select(3, C_PetBattles.GetAbilityState(i, j, k)))) then
						petsAbilitiesCD[i][j][k] = (select(2, C_PetBattles.GetAbilityState(i, j, k)));
					elseif (C_PetBattles.GetAbilityState(i, j, k) ~= nil and (select(2, C_PetBattles.GetAbilityState(i, j, k))) < (select(3, C_PetBattles.GetAbilityState(i, j, k)))) then
						petsAbilitiesCD[i][j][k] = (select(3, C_PetBattles.GetAbilityState(i, j, k)));
					else
						petsAbilitiesCD[i][j][k] = 0;
					end
				end
			end
		end

		selectAbility, selectPet = true, C_PetBattles.ShouldShowPetSelect();
	else		
		for i=1, teams do
			teamSize[i], teamsActivePet[i] = C_PetBattles.GetNumPets(i), C_PetBattles.GetActivePet(i);

			for j=1, teamSize[i] do
				petsSpecies[i][j] = C_PetBattles.GetPetSpeciesID(i, j);
				petsBreed[i][j] = (LibPetBreedInfo:GetBreedByPetBattleSlot(i, j));
				petsLevel[i][j] = C_PetBattles.GetLevel(i, j);
				petsQuality[i][j] = C_PetBattles.GetBreedQuality(i, j);
				petsCurrentHP[i][j] = C_PetBattles.GetHealth(i, j);

				petsAbilitiesVerified[i][j], petsAbilities[i][j], petsAbilitiesCD[i][j] = {}, {}, {};
				for k=1, numAbilities do
					local idTable, _ = C_PetJournal.GetPetAbilityList(petsSpecies[i][j]);

					for l=1, 6 do
						if (idTable[l] == (C_PetBattles.GetAbilityInfo(i, j, k))) then
							petsAbilitiesVerified[i][j][k] = isPVPBattle() and i==2 and j==1 and petsLevel[i][j] < 10 and true
															or isPVPBattle() and i==2 and j==2 and petsLevel[i][j] < 15 and true
															or isPVPBattle() and i==2 and j==3 and petsLevel[i][j] < 20 and true
															or isPVPBattle() and false
															or true;
							petsAbilities[i][j][k] = isPVPBattle() and i==enemyTeam and 1 or math.ceil(l/3);
							break
						end
					end

					if (C_PetBattles.GetAbilityState(i, j, k) ~= nil and (select(2, C_PetBattles.GetAbilityState(i, j, k))) >= (select(3, C_PetBattles.GetAbilityState(i, j, k)))) then
						petsAbilitiesCD[i][j][k] = (select(2, C_PetBattles.GetAbilityState(i, j, k)));
					elseif (C_PetBattles.GetAbilityState(i, j, k) ~= nil and (select(2, C_PetBattles.GetAbilityState(i, j, k))) < (select(3, C_PetBattles.GetAbilityState(i, j, k)))) then
						petsAbilitiesCD[i][j][k] = (select(3, C_PetBattles.GetAbilityState(i, j, k)));
					else
						petsAbilitiesCD[i][j][k] = 0;
					end
				end

				petsNumAuras[i][j], petsAuras[i][j], petsAurasDuration[i][j] = C_PetBattles.GetNumAuras(i, j), {}, {};
				for k=1, petsNumAuras[i][j] do
					petsAuras[i][j][k], _, petsAurasDuration[i][j][k], _ = C_PetBattles.GetAuraInfo(i, j, k);
				end
			end
		end

		petsNumAuras[0][0], petsAuras[0][0], petsAurasDuration[0][0] = C_PetBattles.GetNumAuras(0, 0), {}, {};
		for k=1, petsNumAuras[0][0] do
			petsAuras[0][0][k], _, petsAurasDuration[0][0][k], _ = C_PetBattles.GetAuraInfo(0, 0, k);
		end
		
		initialized, selectAbility = true, true;
	end
end

function events:PET_BATTLE_ACTION_SELECTED(...)
	--print("PET_BATTLE_ACTION_SELECTED");
	selectAbility, selectPet = false, C_PetBattles.ShouldShowPetSelect();
end

function events:PET_BATTLE_PET_CHANGED(...)
	--print("PET_BATTLE_PET_CHANGED")
	for i=1, teams do teamsActivePet[i] = C_PetBattles.GetActivePet(i); end
end

function events:PET_BATTLE_OPENING_START(...)
	--print("PET_BATTLE_OPENING_START");
	inPetBattle = C_PetBattles.IsInBattle();

	teamSize, teamsActivePet, petsSpecies, petsBreed = {0, 0}, {0, 0}, {{}, {}}, {{}, {}};
	petsCurrentHP, petsLevel, petsQuality = {{}, {}}, {{}, {}}, {{}, {}};
	petsAbilitiesVerified, petsAbilities, petsAbilitiesCD = {{}, {}}, {{}, {}}, {{}, {}};
	petsNumAuras, petsAuras, petsAurasDuration = {}, {}, {};
	for i=0, teams do petsNumAuras[i], petsAuras[i], petsAurasDuration[i] = {}, {}, {}; end
end

function events:PET_BATTLE_OPENING_DONE(...)
	--print("PET_BATTLE_OPENING_DONE");
	--Select pet menu is available but we know nothing about the other team so we'll select our first pet.
	selectPet = C_PetBattles.ShouldShowPetSelect()
end

function events:PET_BATTLE_QUEUE_STATUS(...)
	--print("PET_BATTLE_QUEUE_STATUS");
	wonLastBattle = false;
	teamIsAlive = queueEnabled and (C_PetJournal.GetPetStats(C_PetJournal.GetPetLoadOutInfo(1))) > 0 and
			(C_PetJournal.GetPetStats(C_PetJournal.GetPetLoadOutInfo(2))) > 0 and
			(C_PetJournal.GetPetStats(C_PetJournal.GetPetLoadOutInfo(3))) > 0;
	queueEnabled = C_PetJournal.IsFindBattleEnabled();
	queueState = (C_PetBattles.GetPVPMatchmakingInfo());
	canAccept = C_PetBattles.CanAcceptQueuedPVPMatch();
	playerIsGhost = UnitIsGhost("player");
	playerIsDead = UnitIsDead("player");
	playerAffectingCombat = UnitAffectingCombat("player");
	
	--if (queueState == "proposal" and canAccept) then
		--C_PetBattles.AcceptQueuedPVPMatch();
	--end
end

function events:PET_BATTLE_OVER(...)
	--print("PET_BATTLE_OVER");
	--Battle is over but let's update everything one last time to find the victor
	for i=1, teams do
		for j=1, teamSize[i] do
			for k=1, numAbilities do
				if (C_PetBattles.GetAbilityState(i, j, k) ~= nil and (select(2, C_PetBattles.GetAbilityState(i, j, k))) >= (select(3, C_PetBattles.GetAbilityState(i, j, k)))) then
					petsAbilitiesCD[i][j][k] = (select(2, C_PetBattles.GetAbilityState(i, j, k)));
				elseif (C_PetBattles.GetAbilityState(i, j, k) ~= nil and (select(2, C_PetBattles.GetAbilityState(i, j, k))) < (select(3, C_PetBattles.GetAbilityState(i, j, k)))) then
					petsAbilitiesCD[i][j][k] = (select(3, C_PetBattles.GetAbilityState(i, j, k)));
				else
					petsAbilitiesCD[i][j][k] = 0;
				end
			end
		end
	end

	if (petsCurrentHP[1][1] == petsCurrentHP[1][2] == petsCurrentHP[1][3]
		== petsCurrentHP[2][1] == petsCurrentHP[2][2] == petsCurrentHP[2][3] == 0) then
		wonLastBattle = false;
	elseif (petsCurrentHP[1][1] == petsCurrentHP[1][2] == petsCurrentHP[1][3] == 0) then
		wonLastBattle = false;
	elseif (petsCurrentHP[2][1] == petsCurrentHP[2][2] == petsCurrentHP[2][3] == 0) then
		wonLastBattle = true;
	else
		wonLastBattle = true;
	end
end

function events:PET_BATTLE_CLOSE(...)
	--print("PET_BATTLE_CLOSE");
	--Wait a few seconds before queueing again
	inPetBattle, initialized, selectPet, selectAbility = false, false, false, false;

	queueEnabled = C_PetJournal.IsFindBattleEnabled();
	queueState = (C_PetBattles.GetPVPMatchmakingInfo());
	canAccept = C_PetBattles.CanAcceptQueuedPVPMatch();
	teamIsAlive = queueEnabled and (C_PetJournal.GetPetStats(C_PetJournal.GetPetLoadOutInfo(1))) > 0 and
			(C_PetJournal.GetPetStats(C_PetJournal.GetPetLoadOutInfo(2))) > 0 and
			(C_PetJournal.GetPetStats(C_PetJournal.GetPetLoadOutInfo(3))) > 0;
	playerIsGhost = UnitIsGhost("player");
	playerIsDead = UnitIsDead("player");
	playerAffectingCombat = UnitAffectingCombat("player");

	for i=1, teams do
		for j=1, teamSize[i] do
			petsSpecies[i][j] = 0;
			petsBreed[i][j] = 0;
			petsLevel[i][j] = 0;
			petsQuality[i][j] = 0;
			petsCurrentHP[i][j] = 0;

			for k=1, numAbilities do
				petsAbilitiesVerified[i][j][k] = false;
				petsAbilities[i][j][k] = 0;
				petsAbilitiesCD[i][j][k] = 0;
			end

			for k=1, petsNumAuras[i][j] do
				petsAuras[i][j][k], petsAurasDuration[i][j][k] = 0, 0;
			end
			petsNumAuras[i][j] = 0;
		end
	end

	for k=1, petsNumAuras[0][0]==nil and 0 or petsNumAuras[0][0] do
		petsAuras[0][0][k], _, petsAurasDuration[0][0][k], _ = C_PetBattles.GetAuraInfo(0, 0, k);
	end
end

function events:PLAYER_LOGIN(...)
	--print("PLAYER_LOGIN");
	inPetBattle = C_PetBattles.IsInBattle();
	--if (inPetBattle) then
		--C_PetBattles.ForfeitGame();
	--end
	queueEnabled = not (select(5, C_PetJournal.GetPetLoadOutInfo(3)));
	queueState = (C_PetBattles.GetPVPMatchmakingInfo());
	canAccept, teamIsAlive = true, true; --Assumption
	playerIsGhost = UnitIsGhost("player");
	playerIsDead = UnitIsDead("player");
	playerAffectingCombat = UnitAffectingCombat("player");
end

----------------------------------------------
-- Encodes
----------------------------------------------

function encodeInitial(index)
	for i=1, maxIndex do
		uiBox[i]:SetVertexColor(0, 0, 0);
	end
end

function encodeStates()
	local r, g, b = 0, 0, 0;

	if (inPetBattle) then r = r + 128; end
	if (teamIsAlive) then r = r + 64; end
	if (playerIsGhost ~= nil) then r = r + 32; end
	if (playerIsDead ~= nil) then r = r + 16; end
	if (playerAffectingCombat ~= nil) then r = r + 8; end
	if (queueEnabled) then r = r + 4; end
	if (queueState == "proposal") then r = r + 3;
		elseif (queueState == "queued") then r = r + 2;
		elseif (queueState == "suspended") then r = r + 1;
	end

	if (canAccept) then g = g + 128; end
	if (initialized) then g = g + 64; end
	if (selectPet) then g = g + 32; end
	if (selectAbility) then g = g + 16; end
	if (wonLastBattle) then g = g + 8; end
	
	b = mVersion;

	uiBox[1]:SetVertexColor(r/255, g/255, b/255);
end

function encodePetInfo()
	local r, g, b = {{}, {}}, {{}, {}}, {{}, {}};

	for i=1, teams do
		for j=1, 2*teamSize[i], 2 do
			local petsSpecies = deepCopy(petsSpecies[i][((j-1)/2)+1]);
			local petsBreed = deepCopy(petsBreed[i][((j-1)/2)+1]);
			local petsQuality = deepCopy(petsQuality[i][((j-1)/2)+1]);
			local petsLevel = deepCopy(petsLevel[i][((j-1)/2)+1]);
			local petsAbilitiesCD = {deepCopy(petsAbilitiesCD[i][((j-1)/2)+1][1]),
											deepCopy(petsAbilitiesCD[i][((j-1)/2)+1][2]),
											deepCopy(petsAbilitiesCD[i][((j-1)/2)+1][3])};

			r[i][j], r[i][j+1] = 0, 0;
			g[i][j], g[i][j+1] = 0, 0;
			b[i][j], b[i][j+1] = 0, 0;

			if (petsSpecies ~= nil) then
				petsSpecies = bit.lshift(petsSpecies, 5);
				g[i][j] = g[i][j] + bit.band(petsSpecies, 255);
				petsSpecies = bit.rshift(petsSpecies, 8);
				r[i][j] = r[i][j] + bit.band(petsSpecies, 255);
			end

			if (petsBreed ~= nil) then
				g[i][j] = g[i][j] + bit.band(petsBreed, 31);
			end

			if (petsQuality ~= nil) then
				petsQuality = bit.lshift(petsQuality, 5);
				b[i][j] = b[i][j] + bit.band(petsQuality, 255);
			end

			if (petsLevel ~= nil) then
				petsLevel = bit.lshift(petsLevel, 7);
				r[i][j+1] = r[i][j+1] + bit.band(petsLevel, 255);
				petsLevel = bit.rshift(petsLevel, 8);
				b[i][j] = b[i][j] + bit.band(petsLevel, 255);
			end

			--Hardcode Ability 1
			if (petsAbilitiesVerified[i][((j-1)/2)+1][1]) then r[i][j+1] = r[i][j+1] + 64; end
			if (petsAbilities[i][((j-1)/2)+1][1] == 2) then r[i][j+1] = r[i][j+1] + 32; end
			petsAbilitiesCD[1] = bit.lshift(petsAbilitiesCD[1], 1);
			r[i][j+1] = r[i][j+1] + bit.band(petsAbilitiesCD[1], 255);

			--Hardcode Ability 2
			if (petsAbilitiesVerified[i][((j-1)/2)+1][2]) then r[i][j+1] = r[i][j+1] + 1; end
			if (petsAbilities[i][((j-1)/2)+1][2] == 2) then g[i][j+1] = g[i][j+1] + 128; end
			petsAbilitiesCD[2] = bit.lshift(petsAbilitiesCD[2], 7);
			g[i][j+1] = g[i][j+1] + bit.band(petsAbilitiesCD[2], 255);

			--Hardcode Ability 3
			if (petsAbilitiesVerified[i][((j-1)/2)+1][3]) then g[i][j+1] = g[i][j+1] + 4; end
			if (petsAbilities[i][((j-1)/2)+1][3] == 2) then g[i][j+1] = g[i][j+1] + 2; end
			petsAbilitiesCD[3] = bit.lshift(petsAbilitiesCD[3], 5);
			b[i][j+1] = b[i][j+1] + bit.band(petsAbilitiesCD[3], 255);
			petsAbilitiesCD[3] = bit.rshift(petsAbilitiesCD[3], 8);
			g[i][j+1] = g[i][j+1] + bit.band(petsAbilitiesCD[3], 255);

			local index = i==1 and i+j or i==2 and 4*i+j-1;
			if (index == 12) then index = index + 1; end
			uiBox[index]:SetVertexColor(r[i][j]/255, g[i][j]/255, b[i][j]/255); index = index + 1;
			uiBox[index]:SetVertexColor(r[i][j+1]/255, g[i][j+1]/255, b[i][j+1]/255);
		end 
	end
end

function encodeHealth()
	local petsCurrentHP = deepCopy(petsCurrentHP);
	local r, g, b = {}, {}, {};
	local index = 15;

	for i=1, teams do
		for j=i, teamSize[i], 2 do
			r[(i*i+j)/2], g[(i*i+j)/2], b[(i*i+j)/2] = 0, 0, 0;

			petsCurrentHP[i][j] = bit.lshift(petsCurrentHP[i][j], 4);
			g[(i*i+j)/2] = g[(i*i+j)/2] + bit.band(petsCurrentHP[i][j], 255);
			petsCurrentHP[i][j] = bit.rshift(petsCurrentHP[i][j], 8);
			r[(i*i+j)/2] = r[(i*i+j)/2] + bit.band(petsCurrentHP[i][j], 255);
			b[(i*i+j)/2] = b[(i*i+j)/2] + bit.band(petsCurrentHP[j+1>3 and i+1 or i][j+1>3 and 1 or j+1], 255);
			petsCurrentHP[j+1>3 and i+1 or i][j+1>3 and 1 or j+1] = bit.rshift(petsCurrentHP[j+1>3 and i+1 or i][j+1>3 and 1 or j+1], 8);
			g[(i*i+j)/2] = g[(i*i+j)/2] + bit.band(petsCurrentHP[j+1>3 and i+1 or i][j+1>3 and 1 or j+1], 255);

			uiBox[index]:SetVertexColor(r[(i*i+j)/2]/255, g[(i*i+j)/2]/255, b[(i*i+j)/2]/255); index = index + 1;
		end
	end
end

function encodeAuras()
	local index = 18;

	for i=0, teams do
		for j=(i==0) and 0 or 1, (i==0) and 0 or teamSize[i] do
			for k=1, petsNumAuras[i][j] ~= nil and petsNumAuras[i][j] or 0 do
				local r, g, b = 0, 0, 0;
				local team, pet = deepCopy(i), deepCopy(j);
				local auraID = petsAuras[i][j][k]==nil and 0 or deepCopy(petsAuras[i][j][k]);
				local auraDuration = (petsAurasDuration[i][j][k]==-1 or petsAurasDuration[i][j][k]==nil) and 0
										or deepCopy(petsAurasDuration[i][j][k]);
				
				team = bit.lshift(team, 6);
				r = r + bit.band(team, 255);
				pet = bit.lshift(pet, 4);
				r = r + bit.band(pet, 255);
				r = r + bit.band(auraDuration, 255);
				auraID = bit.lshift(auraID, 4);
				b = b + bit.band(auraID, 255);
				auraID = bit.rshift(auraID, 8);
				g = g + bit.band(auraID, 255);

				if (index > maxIndex) then
					uiBox[index] = {r, b, g};
				else
					uiBox[index]:SetVertexColor(r/255, g/255, b/255); index = index + 1;
					if (index == 20 or index == 23 or index == 29 or index == 37) then index = index + 1; end
				end
			end
		end
	end
end

function encodeChecksums()
	uiBox[12]:SetVertexColor(
		(select(3, uiBox[10]:GetVertexColor())),
		(select(1, uiBox[3]:GetVertexColor())),
		(select(2, uiBox[7]:GetVertexColor()))
		)
		
	uiBox[20]:SetVertexColor(
		(select(2, uiBox[17]:GetVertexColor())),
		(select(3, uiBox[13]:GetVertexColor())),
		(select(1, uiBox[15]:GetVertexColor()))
		)
		
	uiBox[23]:SetVertexColor(
		mVersion/255,
		(select(1, uiBox[21]:GetVertexColor())),
		(select(2, uiBox[22]:GetVertexColor()))
		)
		
	uiBox[29]:SetVertexColor(
		(select(2, uiBox[4]:GetVertexColor())),
		mVersion/255,
		(select(1, uiBox[13]:GetVertexColor()))
		)
		
	uiBox[37]:SetVertexColor(
		mVersion/255,
		(select(1, uiBox[1]:GetVertexColor())),
		(select(2, uiBox[10]:GetVertexColor()))
		)
end

----------------------------------------------
-- Miscellaneous
----------------------------------------------

function isPVPBattle()
	return inPetBattle and not C_PetBattles.IsWildBattle() and not C_PetBattles.IsPlayerNPC(enemyTeam)
end

function deepCopy(orig)
    local orig_type = type(orig);
    local copy;
    if orig_type == 'table' then
        copy = {};
        for orig_key, orig_value in next, orig, nil do
            copy[deepCopy(orig_key)] = deepCopy(orig_value);
        end
        setmetatable(copy, deepCopy(getmetatable(orig)));
    else -- number, string, boolean, etc
        copy = orig;
    end
    return copy;
end

----------------------------------------------
-- Update
----------------------------------------------

function UpdateEvent(self, elapsed)

	self.TimeSinceLastUpdate = self.TimeSinceLastUpdate + elapsed;
	if (self.TimeSinceLastUpdate < mUpdateInterval) then return; end

	uiBg1:SetVertexColor(mBorderR1, mBorderG1, mBorderB1);
	uiBg2:SetVertexColor(mBorderR2, mBorderG2, mBorderB2);

	encodeInitial();
	encodeStates();
	encodePetInfo();
	encodeHealth();
	encodeAuras();
	encodeChecksums();
end

----------------------------------------------
-- Register Event
----------------------------------------------

PetPixels:SetScript("OnEvent", function(self, event, ...)
	events[event](self, ...); -- call one of the functions above
end)

PetPixels:RegisterEvent("PLAYER_LOGIN")
--PetPixels:RegisterEvent("PLAYER_ENTERING_WORLD")
--PetPixels:RegisterEvent("PET_BATTLE_ABILITY_CHANGED")
PetPixels:RegisterEvent("PET_BATTLE_ACTION_SELECTED")
PetPixels:RegisterEvent("PET_BATTLE_AURA_APPLIED")
PetPixels:RegisterEvent("PET_BATTLE_AURA_CANCELED")
PetPixels:RegisterEvent("PET_BATTLE_AURA_CHANGED")
--PetPixels:RegisterEvent("PET_BATTLE_CAPTURED")
PetPixels:RegisterEvent("PET_BATTLE_CLOSE")
--PetPixels:RegisterEvent("PET_BATTLE_FINAL_ROUND")
PetPixels:RegisterEvent("PET_BATTLE_HEALTH_CHANGED")
--PetPixels:RegisterEvent("PET_BATTLE_LEVEL_CHANGED")
--PetPixels:RegisterEvent("PET_BATTLE_LOOT_RECEIVED")
--PetPixels:RegisterEvent("PET_BATTLE_MAX_HEALTH_CHANGED")
PetPixels:RegisterEvent("PET_BATTLE_OPENING_DONE")
PetPixels:RegisterEvent("PET_BATTLE_OPENING_START")
PetPixels:RegisterEvent("PET_BATTLE_OVER")
PetPixels:RegisterEvent("PET_BATTLE_PET_CHANGED")
PetPixels:RegisterEvent("PET_BATTLE_PET_ROUND_PLAYBACK_COMPLETE")
--PetPixels:RegisterEvent("PET_BATTLE_PET_ROUND_RESULTS")
--PetPixels:RegisterEvent("PET_BATTLE_PVP_DUEL_REQUESTED")
--PetPixels:RegisterEvent("PET_BATTLE_PVP_DUEL_REQUEST_CANCEL")
--PetPixels:RegisterEvent("PET_BATTLE_QUEUE_PROPOSAL_ACCEPTED")
--PetPixels:RegisterEvent("PET_BATTLE_QUEUE_PROPOSAL_DECLINED")
--PetPixels:RegisterEvent("PET_BATTLE_QUEUE_PROPOSE_MATCH")
PetPixels:RegisterEvent("PET_BATTLE_QUEUE_STATUS")
--PetPixels:RegisterEvent("PET_BATTLE_TURN_STARTED")
--PetPixels:RegisterEvent("PET_BATTLE_XP_CHANGED")
PetPixels:RegisterEvent("CHAT_MSG_PET_BATTLE_COMBAT_LOG")