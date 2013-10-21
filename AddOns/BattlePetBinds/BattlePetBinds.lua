-- THERE IS NO NEED TO MODIFY THIS FILE NOW.
-- ALL SETTINGS ARE IN-GAME UNDER ESCAPE --> INTERFACE --> ADDONS --> BATTLEPETBINDS

------------------------------
-- Author: Simca@Malfurion  --
------------------------------

-- localize addon namespace
local addon, ns = ...

-- localize functions
local SOBC = _G.SetOverrideBindingClick
ns.find = string.find
ns.len = string.len
ns.lower = string.lower
ns.sub = string.sub
ns.tostr = tostring
ns.upper = string.upper

-- use boolean variable to account for Blizzard event misfire bug
local BPB_BindState = false

-- create event handling frame
local BattlePetBinds = CreateFrame("FRAME", "BattlePetBinds")

-- register events
BattlePetBinds:RegisterEvent("ADDON_LOADED")
BattlePetBinds:RegisterEvent("PET_BATTLE_OPENING_START")
BattlePetBinds:RegisterEvent("PET_BATTLE_OPENING_DONE")
BattlePetBinds:RegisterEvent("PET_BATTLE_OVER")
BattlePetBinds:RegisterEvent("PET_BATTLE_CLOSE")

-- shorten binding names for display purposes
function ns.BPB_Shorten(binding)
	
	local text = binding
	local modifiers = ""
	
	-- go here for modifiers
	if ns.len(text) > 3 then
		-- shorten CTRL, ALT, SHIFT, BUTTON, and NUMPAD into single letters
		if ns.find(text, "ALT-") then text = ns.sub(text, ns.find(text, "ALT-") + 4) modifiers = modifiers .. "A" end
		if ns.find(text, "CTRL-") then text = ns.sub(text, ns.find(text, "CTRL-") + 5) modifiers = modifiers .. "C" end
		if ns.find(text, "SHIFT-") then text = ns.sub(text, ns.find(text, "SHIFT-") + 6) modifiers = modifiers .. "S" end
		if ns.find(text, "NUMPAD") then text = ns.sub(text, ns.find(text, "NUMPAD") + 6) modifiers = "N" end
		if ns.find(text, "BUTTON") then text = ns.sub(text, ns.find(text, "BUTTON") + 6) modifiers = "M" end
	end
	
	-- go here for obscure keys only (since modifiers are dealt with)
	if ns.len(text) > 2 then
		-- handle PAGEUP and PAGEDOWN
		if ns.find(text, "PAGEUP") then text = "Up" modifiers = modifiers .. "P" end
		if ns.find(text, "PAGEDOWN") then text = "Dwn" modifiers = modifiers .. "P" end
		
		-- handle MOUSEWHEELUP and MOUSEWHEELDOWN
		if ns.find(text, "MOUSEWHEELUP") then text = "Up" modifiers = "M" end
		if ns.find(text, "MOUSEWHEELDOWN") then text = "Dwn" modifiers = "M" end
		
		-- handle obscure NUMPAD operators
		if ns.find(text, "PLUS") then text = "+" end
		if ns.find(text, "MINUS") then text = "-" end
		if ns.find(text, "MULTIPLY") then text = "*" end
		if ns.find(text, "DIVIDE") then text = "/" end
		if ns.find(text, "DECIMAL") then text = "." end
		
		-- exceptions list for things that look better as 4 letters
		local exceptionsList = { ["HOME"] = true, ["BACKSPACE"] = true, ["CAPSLOCK"] = true, }
		
		-- chop off anything left in strings greater than 3 chars and lowercase everything after the first char if not an exception
		if (ns.len(text) > 2) and (not exceptionsList[text]) then
			text = ns.upper(ns.sub(text, 1, 1)) .. ns.lower(ns.sub(text, 2, 3))
		elseif (ns.len(text) > 3) then
			text = ns.upper(ns.sub(text, 1, 1)) .. ns.lower(ns.sub(text, 2, 4))
		end
	end
	
	text = modifiers .. text
	
	return text
end

-- set up buttons to be clicked on by our new bindings (replaces Bindings.xml)
local function BPB_CreateHotKeys()
	
	-- create buttons to be clicked and define them as macros
	for i = 1, 10 do
		local button = "BPB_HotKey"..i
		CreateFrame("Button", button, nil, "SecureActionButtonTemplate")
		_G[button]:SetAttribute("type", "macro")
	end
	
	CreateFrame("Button", "BPB_NothingButton", nil, "SecureActionButtonTemplate")
	CreateFrame("Button", "BPB_LongForfeit", nil, "SecureActionButtonTemplate")
	_G["BPB_LongForfeit"]:SetAttribute("type", "macro")
	
	-- add macro code (to store code for later) into the buttons
	_G["BPB_HotKey1"]:SetAttribute("macrotext", "/run StaticPopup_Hide(\34PET_BATTLE_FORFEIT\34,nil) StaticPopup_Hide(\34PET_BATTLE_FORFEIT_NO_PENALTY\34,nil) C_PetBattles.UseAbility(1)")
	_G["BPB_HotKey2"]:SetAttribute("macrotext", "/run StaticPopup_Hide(\34PET_BATTLE_FORFEIT\34,nil) StaticPopup_Hide(\34PET_BATTLE_FORFEIT_NO_PENALTY\34,nil) C_PetBattles.UseAbility(2)")
	_G["BPB_HotKey3"]:SetAttribute("macrotext", "/run StaticPopup_Hide(\34PET_BATTLE_FORFEIT\34,nil) StaticPopup_Hide(\34PET_BATTLE_FORFEIT_NO_PENALTY\34,nil) C_PetBattles.UseAbility(3)")
	_G["BPB_HotKey4"]:SetAttribute("macrotext", "/run StaticPopup_Hide(\34PET_BATTLE_FORFEIT\34,nil) StaticPopup_Hide(\34PET_BATTLE_FORFEIT_NO_PENALTY\34,nil) local selectionFrame = PetBattleFrame.BottomFrame.PetSelectionFrame local battleState = C_PetBattles.GetBattleState() local selectedActionType = C_PetBattles.GetSelectedAction() local mustSwap = ( ( not selectedActionType ) or ( selectedActionType == BATTLE_PET_ACTION_NONE ) ) and ( battleState == LE_PET_BATTLE_STATE_WAITING_PRE_BATTLE ) or ( battleState == LE_PET_BATTLE_STATE_WAITING_FOR_FRONT_PETS ) if ( selectionFrame:IsShown() and ( not mustSwap ) ) then PetBattlePetSelectionFrame_Hide(selectionFrame) else PetBattlePetSelectionFrame_Show(selectionFrame) end")
	_G["BPB_HotKey5"]:SetAttribute("macrotext", "/run do local usable = C_PetBattles.IsTrapAvailable() if (usable) then StaticPopup_Hide(\34PET_BATTLE_FORFEIT\34,nil) StaticPopup_Hide(\34PET_BATTLE_FORFEIT_NO_PENALTY\34,nil) C_PetBattles.UseTrap() end end")
	_G["BPB_HotKey6"]:SetAttribute("macrotext", "/run StaticPopup_Hide(\34PET_BATTLE_FORFEIT\34,nil) StaticPopup_Hide(\34PET_BATTLE_FORFEIT_NO_PENALTY\34,nil) C_PetBattles.ForfeitGame()")
	_G["BPB_HotKey7"]:SetAttribute("macrotext", "/run StaticPopup_Hide(\34PET_BATTLE_FORFEIT\34,nil) StaticPopup_Hide(\34PET_BATTLE_FORFEIT_NO_PENALTY\34,nil) C_PetBattles.SkipTurn()")
	_G["BPB_HotKey8"]:SetAttribute("macrotext", "/run if (C_PetBattles.CanActivePetSwapOut() and C_PetBattles.CanPetSwapIn(1)) then C_PetBattles.ChangePet(1) PetBattlePetSelectionFrame_Hide(PetBattleFrame.BottomFrame.PetSelectionFrame) end")
	_G["BPB_HotKey9"]:SetAttribute("macrotext", "/run if (C_PetBattles.CanActivePetSwapOut() and C_PetBattles.CanPetSwapIn(2)) then C_PetBattles.ChangePet(2) PetBattlePetSelectionFrame_Hide(PetBattleFrame.BottomFrame.PetSelectionFrame) end")
	_G["BPB_HotKey10"]:SetAttribute("macrotext", "/run if (C_PetBattles.CanActivePetSwapOut() and C_PetBattles.CanPetSwapIn(3)) then C_PetBattles.ChangePet(3) PetBattlePetSelectionFrame_Hide(PetBattleFrame.BottomFrame.PetSelectionFrame) end")
	_G["BPB_LongForfeit"]:SetAttribute("macrotext", "/run if (StaticPopup1:IsVisible()) then StaticPopup1Button1:Click() else local forfeitPenalty = C_PetBattles.GetForfeitPenalty() if (forfeitPenalty == 0) then StaticPopup_Show(\34PET_BATTLE_FORFEIT_NO_PENALTY\34, nil, nil, nil) else StaticPopup_Show(\34PET_BATTLE_FORFEIT\34, forfeitPenalty, nil, nil) end end")
end

-- set up text indicators for forfeit, pass turn, and pet swapping HotKeys
local function BPB_CreateHotKeyTexts()
	
	-- create the fontstrings
	for i = 6, 10 do
		BattlePetBinds:CreateFontString("BPB_HotKeyText"..i, "OVERLAY", "NumberFontNormalSmallGray")
	end
	
	-- set the true parent frame for each fontstring
	_G["BPB_HotKeyText6"]:SetParent(PetBattleFrame.BottomFrame.ForfeitButton)
	_G["BPB_HotKeyText7"]:SetParent(PetBattleFrame.BottomFrame.TurnTimer.SkipButton)
	_G["BPB_HotKeyText8"]:SetParent(PetBattleFrame.BottomFrame.PetSelectionFrame.Pet1)
	_G["BPB_HotKeyText9"]:SetParent(PetBattleFrame.BottomFrame.PetSelectionFrame.Pet2)
	_G["BPB_HotKeyText10"]:SetParent(PetBattleFrame.BottomFrame.PetSelectionFrame.Pet3)
	
	-- set the anchor point for each fontstring
	_G["BPB_HotKeyText6"]:SetPoint("TOPRIGHT", PetBattleFrame.BottomFrame.ForfeitButton, "TOPRIGHT", -1, -3)
	_G["BPB_HotKeyText7"]:SetPoint("TOPRIGHT", PetBattleFrame.BottomFrame.TurnTimer.SkipButton, "TOPRIGHT", -1, -6)
	_G["BPB_HotKeyText8"]:SetPoint("BOTTOMRIGHT", PetBattleFrame.BottomFrame.PetSelectionFrame.Pet1, "BOTTOMRIGHT", -6, 9)
	_G["BPB_HotKeyText9"]:SetPoint("BOTTOMRIGHT", PetBattleFrame.BottomFrame.PetSelectionFrame.Pet2, "BOTTOMRIGHT", -6, 9)
	_G["BPB_HotKeyText10"]:SetPoint("BOTTOMRIGHT", PetBattleFrame.BottomFrame.PetSelectionFrame.Pet3, "BOTTOMRIGHT", -6, 9)
	
	-- set the properties of the new fontstrings (justification, height, width, text and isvisible)
	for i = 6, 10 do
		local fstr = "BPB_HotKeyText"..i
		_G[fstr]:SetJustifyH("RIGHT")
		_G[fstr]:SetHeight(10)
		_G[fstr]:SetWidth(46)
		_G[fstr]:SetText(ns.BPB_Shorten(BPBindOptions.Bind[i]))
		_G[fstr]:Show()
	end
end

-- update the hotkey texts with the binds in case they've changed and also increase widths slightly
function ns.UpdateHotKeys()
	
	for i = 1, 3 do
		PetBattleFrame.BottomFrame.abilityButtons[i].HotKey:SetText(ns.BPB_Shorten(BPBindOptions.Bind[i]))
		PetBattleFrame.BottomFrame.abilityButtons[i].HotKey:SetWidth(46)
	end
	
	PetBattleFrame.BottomFrame.SwitchPetButton.HotKey:SetText(ns.BPB_Shorten(BPBindOptions.Bind[4]))
	PetBattleFrame.BottomFrame.SwitchPetButton.HotKey:SetWidth(46)
	PetBattleFrame.BottomFrame.CatchButton.HotKey:SetText(ns.BPB_Shorten(BPBindOptions.Bind[5]))
	PetBattleFrame.BottomFrame.CatchButton.HotKey:SetWidth(46)
	
	for i = 6, 10 do
		local fstr = "BPB_HotKeyText"..i
		_G[fstr]:SetText(ns.BPB_Shorten(BPBindOptions.Bind[i]))
	end
end

-- event handler function
local function BattlePetBinds_OnEvent(self, event, ...)

	-- if this addon loads then
	if (event == "ADDON_LOADED") and (... == "BattlePetBinds") then
		
		-- create SavedVariables table using default values if not already found
		if (not BPBindOptions) then BPBindOptions = {} end
		if (not BPBindOptions.ForfeitCheck) then BPBindOptions.ForfeitCheck = false end
		if (not BPBindOptions.Bind) then
			BPBindOptions.Bind = {
				"1", -- Attack #1
				"2", -- Attack #2
				"3", -- Attack #3
				"4", -- accessing the Swap Pet Menu
				"5", -- throwing traps
				"F", -- forfeiting
				"T", -- passing your turn
				"F1", -- swapping to Pet #1
				"F2", -- swapping to Pet #2
				"F3", -- swapping to Pet #3
			}
		end
		
		for i = 1, 10 do
			_G["BPBConfigButton"..i]:SetText("Key for " .. ns.BPB_Desc[i] .. ": " .. ns.BPB_Shorten(BPBindOptions.Bind[i]))
		end
		
		-- set checkbox to status of ForfeitCheck
		BPBConfigForfeitBox:SetChecked(BPBindOptions.ForfeitCheck)
		
		-- create and bind hotkeys if we're not in combat and we're in a pet battle
		if not InCombatLockdown() and C_PetBattles.IsInBattle() then
			
			-- create hotkey frames and hotkey text frames (because we know they don't exist at addon load)
			BPB_CreateHotKeys()
			BPB_CreateHotKeyTexts()
			
			-- remove old blizzard bindings
			for i = 1, 5 do
				SOBC(BattlePetBinds, true, ns.tostr(i), "BPB_NothingButton")
			end
			
			-- set up our override binding clicks
			for i = 1, 10 do
				local button = "BPB_HotKey"..i
				SOBC(BattlePetBinds, true, BPBindOptions.Bind[i], button)
			end
			
			-- set up "confirm forfeit" bind if the user wants it
			if (BPBindOptions.ForfeitCheck) then
				SOBC(BattlePetBinds, true, BPBindOptions.Bind[6], "BPB_LongForfeit")
			end
			
			-- tell the boolean we have set our bindings
			BPB_BindState = true
			
			-- register combat enter/exit events
			BattlePetBinds:RegisterEvent("PLAYER_REGEN_ENABLED")
			BattlePetBinds:RegisterEvent("PLAYER_REGEN_DISABLED")
		end
	
	-- if we start a pet battle and are not in combat then (checking both opening events to account for Blizzard event misfire bug)
	elseif ((event == "PET_BATTLE_OPENING_START") or (event == "PET_BATTLE_OPENING_DONE")) and not InCombatLockdown() then
		
		-- create hotkey frames if they don't exist
		if not BPB_HotKey1 then
			BPB_CreateHotKeys()
		end
		
		-- create hotkey text frames if they don't exist
		if not BPB_HotKeyText1 then
			BPB_CreateHotKeyTexts()
		end
		
		ns.UpdateHotKeys()
		
		-- remove old blizzard bindings
		for i = 1, 5 do
			SOBC(BattlePetBinds, true, ns.tostr(i), "BPB_NothingButton")
		end
		
		-- set up our override binding clicks
		for i = 1, 10 do
			local button = "BPB_HotKey"..i
			SOBC(BattlePetBinds, true, BPBindOptions.Bind[i], button)
		end
		
		-- set up "confirm forfeit" bind if the user wants it
		if (BPBindOptions.ForfeitCheck) then
			SOBC(BattlePetBinds, true, BPBindOptions.Bind[6], "BPB_LongForfeit")
		end
		
		-- tell the boolean we have set our bindings
		BPB_BindState = true
		
		-- register combat enter/exit events
		BattlePetBinds:RegisterEvent("PLAYER_REGEN_ENABLED")
		BattlePetBinds:RegisterEvent("PLAYER_REGEN_DISABLED")
		
	-- if the pet battle ends then (checking both closing events to account for Blizzard event misfire bug) OR is interrupted by combat
	elseif BPB_BindState and ((event == "PET_BATTLE_OVER") or (event == "PET_BATTLE_CLOSE") or (event == "PLAYER_REGEN_ENABLED") or (event == "PLAYER_REGEN_DISABLED")) then
		-- remove our bindings
		ClearOverrideBindings(BattlePetBinds)
		
		-- tell the boolean that we have removed our bindings
		BPB_BindState = false
		
		-- unregister combat enter/exit events
		BattlePetBinds:UnregisterEvent("PLAYER_REGEN_ENABLED")
		BattlePetBinds:UnregisterEvent("PLAYER_REGEN_DISABLED")
	end
end

-- create slash commands
SLASH_BATTLEPETBINDS1 = "/battlepetbinds"
SLASH_BATTLEPETBINDS2 = "/bpbinds"
SLASH_BATTLEPETBINDS3 = "/petbinds"
SlashCmdList["BATTLEPETBINDS"] = function(msg)
	InterfaceOptionsFrame:Show()
	InterfaceOptionsFrameTab2:Click()
	
	local i = 1
	local currAddon = "InterfaceOptionsFrameAddOnsButton" .. i
	while _G[currAddon] do
		if (_G[currAddon]:GetText() == "Battle Pet Binds") then _G[currAddon]:Click() break end
		i = i + 1
		currAddon = "InterfaceOptionsFrameAddOnsButton" .. i
	end
end

-- set our event handler function
BattlePetBinds:SetScript("OnEvent", BattlePetBinds_OnEvent)