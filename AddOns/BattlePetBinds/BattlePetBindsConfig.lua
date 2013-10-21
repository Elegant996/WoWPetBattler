-- THERE IS NO NEED TO MODIFY THIS FILE NOW.
-- ALL SETTINGS ARE IN-GAME UNDER ESCAPE --> INTERFACE --> ADDONS --> BATTLEPETBINDS

------------------------------
-- Author: Simca@Malfurion  --
------------------------------

-- Thanks to Ro for inspiration (and the title/version/description code) for the overall structure of this Options panel

-- localize addon namespace
local addon, ns = ...

-- current button variable for masterframe config
local currID

ns.BPB_Desc = { -- local text variable to help ease implementation of foreign localizations (at a later stage if ever)
	"Attack #1",
	"Attack #2",
	"Attack #3",
	"accessing the swap pet menu",
	"throwing traps",
	"forfeiting",
	"passing your turn",
	"swapping to Pet #1",
	"swapping to Pet #2",
	"swapping to Pet #3",
}
ns.masterTransfer = false

local Options = CreateFrame("Frame",nil,InterfaceOptionsFramePanelContainer)
Options:Hide()
Options.name = "Battle Pet Binds"

local function createfont(fontName, r, g, b, anchorPoint, relativeTo, relativePoint, cx, cy, xoff, yoff, text)
	local font = Options:CreateFontString(nil, "BACKGROUND", fontName)
	font:SetJustifyH("LEFT")
	font:SetJustifyV("TOP")
	if type(r) == "string" then -- r is text, no positioning
		text = r
	else
		if r then
			font:SetTextColor(r, g, b, 1)
		end
		font:SetSize(cx, cy)
		font:SetPoint(anchorPoint, relativeTo, relativePoint, xoff, yoff)
	end
	font:SetText(text)
	return font
end

local panelWidth = InterfaceOptionsFramePanelContainer:GetWidth() -- ~623
local wideWidth = panelWidth - 40

local title = createfont("GameFontNormalLarge", "Battle Pet Binds")
title:SetPoint("TOPLEFT", 16, -16)
local ver = createfont("GameFontNormalSmall", "version "..GetAddOnMetadata("BattlePetBinds", "Version"))
ver:SetPoint("BOTTOMLEFT", title, "BOTTOMRIGHT", 4, 0)
local desc = createfont("GameFontHighlight", nil, nil, nil, "TOPLEFT", title, "BOTTOMLEFT" ,wideWidth, 40, 0, -8, "An addon that allows users to easily define custom keybinds for all Pet Battle features (including skipping turns, changing pets, and forfeiting) without overwriting non-pet-battle keybinds!")

-- create and hide the master keybind accepting frame
local masterFrame = CreateFrame("Button", "BPBConfigMaster", Options)

-- transfer the key being rebound from one key to another (this occurs when 
local function masterFrame_TransferBurden()
	for i = 1, 10 do
		_G["BPBConfigButton"..i]:SetText("Key for " .. ns.BPB_Desc[i] .. ": " .. ns.BPB_Shorten(BPBindOptions.Bind[i]))
	end
	
	_G["BPBConfigButton"..currID]:SetText("Input a new key for " ..  ns.BPB_Desc[currID] .. "!")
	
	ns.masterTransfer = true
end

-- hide the masterFrame (so that input can be accepted once again)
local function BPB_HideMasterFrame()
	masterFrame:SetFrameStrata("HIGH")
	masterFrame:UnregisterEvent("PLAYER_REGEN_DISABLED")
	masterFrame:UnlockHighlight()
	masterFrame:EnableKeyboard(false)
	masterFrame:EnableMouse(false)
	masterFrame:EnableMouseWheel(false)
	masterFrame:SetHeight(1)
	masterFrame:SetWidth(1)
	masterFrame:SetPoint("TOPLEFT", UIParent, "TOPLEFT")
	
	ns.masterTransfer = false
	
	masterFrame:Hide()
	
	--[[masterFrame:SetScript("OnKeyDown", nil)
	masterFrame:SetScript("OnMouseDown", nil)
	masterFrame:SetScript("OnMouseWheel", nil)]]--
	
	_G["BPBConfigButton"..currID]:SetText("Key for " .. ns.BPB_Desc[currID] .. ": " .. ns.BPB_Shorten(BPBindOptions.Bind[currID]))
	currID = 0
end

-- accept keybinds into the masterFrame when it is enabled
local function masterFrame_OnKeyDown(self, key)
	-- thanks to the authors of AceGUI-3.0 for this line of code and idea
	local testkey = key
	local ignoreKeys = { ["UNKNOWN"] = true, ["LSHIFT"] = true, ["LCTRL"] = true, ["LALT"] = true, ["RSHIFT"] = true, ["RCTRL"] = true, ["RALT"] = true, ["PRINTSCREEN"] = true, }
	
	if (ignoreKeys[testkey]) then return end
	
	if (testkey == "ESCAPE") and (not ns.masterTransfer) then
		BPB_HideMasterFrame()
		return
	elseif (testkey == "ESCAPE") then
		return
	end
	
	if IsShiftKeyDown() then testkey = "SHIFT-"..testkey end
	if IsControlKeyDown() then testkey = "CTRL-"..testkey end
	if IsAltKeyDown() then testkey = "ALT-"..testkey end
	
	local duplicate = false
	for i = 1, 10 do
		if (BPBindOptions.Bind[i] == testkey) then duplicate = i break end
	end
	
	if duplicate then
		BPBindOptions.Bind[currID] = testkey
		currID = duplicate
		masterFrame_TransferBurden()
	else
		BPBindOptions.Bind[currID] = testkey
		BPB_HideMasterFrame()
	end
end

-- accept mousebinds into the masterFrame when it is enabled
local function masterFrame_OnMouseDown(self, button)
	--if IsShiftKeyDown() then button = "SHIFT-"..button end
	--if IsControlKeyDown() then button = "CTRL-"..button end
	--if IsAltKeyDown() then button = "ALT-"..button end
	local testkey = button
	
	if ( testkey == "LeftButton" ) then
		testkey = "BUTTON1"
	elseif ( testkey == "RightButton" ) then
		testkey = "BUTTON2"
	elseif ( testkey == "MiddleButton" ) then
		testkey = "BUTTON3"
	else
		testkey = ns.upper(testkey)
	end
	
	local duplicate = false
	for i = 1, 10 do
		if (BPBindOptions.Bind[i] == testkey) then duplicate = i break end
	end
	
	if duplicate then
		BPBindOptions.Bind[currID] = testkey
		currID = duplicate
		masterFrame_TransferBurden()
	else
		BPBindOptions.Bind[currID] = testkey
		BPB_HideMasterFrame()
	end
end

-- accept mousewheelbinds into the masterFrame when it is enabled
local function masterFrame_OnMouseWheel(self, delta)
	--if IsShiftKeyDown() then delta = "SHIFT-"..delta end
	--if IsControlKeyDown() then delta = "CTRL-"..delta end
	--if IsAltKeyDown() then delta = "ALT-"..delta end
	local testkey = delta
	
	if testkey == 1 then
		testkey = "MOUSEWHEELUP"
	elseif (testkey == -1) then
		testkey = "MOUSEWHEELDOWN"
	end
	
	local duplicate = false
	for i = 1, 10 do
		if (BPBindOptions.Bind[i] == testkey) then duplicate = i break end
	end
	
	if duplicate then
		BPBindOptions.Bind[currID] = testkey
		currID = duplicate
		masterFrame_TransferBurden()
	else
		BPBindOptions.Bind[currID] = testkey
		BPB_HideMasterFrame()
	end
end

masterFrame:SetScript("OnKeyDown", masterFrame_OnKeyDown)
masterFrame:SetScript("OnMouseDown", masterFrame_OnMouseDown)
masterFrame:SetScript("OnMouseWheel", masterFrame_OnMouseWheel)
masterFrame:Hide()

-- effectively this is the "ShowMasterFrame()" function
local function BPBConfigButton_OnClick(self, ...)
	if InCombatLockdown() then return end
	masterFrame:SetFrameStrata("FULLSCREEN_DIALOG")
	masterFrame:RegisterEvent("PLAYER_REGEN_DISABLED")
	masterFrame:LockHighlight()
	--masterFrame:EnableMouse(true)
	--masterFrame:EnableMouseWheel(true)
	masterFrame:EnableKeyboard(true)
	masterFrame:SetHeight(UIParent:GetHeight())
	masterFrame:SetWidth(UIParent:GetWidth())
	masterFrame:SetPoint("CENTER", UIParent, "CENTER")
	masterFrame:SetScript("OnKeyDown", masterFrame_OnKeyDown)
	masterFrame:SetScript("OnMouseDown", masterFrame_OnMouseDown)
	masterFrame:SetScript("OnMouseWheel", masterFrame_OnMouseWheel)
	
	ns.masterTransfer = true
	
	masterFrame:Show()
	
	currID = self:GetID()
	self:SetText("Input a new key for " ..  ns.BPB_Desc[currID] .. "!")
end

-- create the 10 UI buttons
for i = 1, 10 do
	local currentbutton = "BPBConfigButton" .. i
	CreateFrame("Button", currentbutton, Options, "UIPanelButtonTemplate")
	if (i == 1) then
		_G[currentbutton]:SetPoint("TOPLEFT", desc, "BOTTOMLEFT", 20, -40)
	else
		_G[currentbutton]:SetPoint("TOPLEFT", _G["BPBConfigButton" .. (i - 1)], "BOTTOMLEFT", 0, -10)
	end
	_G[currentbutton]:SetID(i)
	_G[currentbutton]:SetNormalFontObject("GameFontNormal")
	_G[currentbutton]:SetScript("OnClick", BPBConfigButton_OnClick)
	_G[currentbutton]:SetWidth(320)
end

-- create checkbox
local checkbox = CreateFrame("CheckButton", "BPBConfigForfeitBox", Options, "UICheckButtonTemplate")
checkbox:SetPoint("BOTTOMLEFT", Options, "BOTTOMLEFT", 64, 64)
checkbox:SetSize(32, 32)
checkbox.text:SetFontObject("GameFontNormal")
checkbox.text:SetText(" Require confirmation (second press) when Forfeit button pushed")

-- OnClick for checkbox
local function BPBConfigForfeitBox_OnClick(self, button, down)
	BPBindOptions.ForfeitCheck = BPBConfigForfeitBox:GetChecked()
end
	
-- hide masterFrame in combat
local function masterFrame_OnEvent(self, event, ...)
	if (event == "PLAYER_REGEN_DISABLED") then
		BPB_HideMasterFrame()
	end
end

-- defaults
function Options.default()
	if masterFrame:IsShown() then BPB_HideMasterFrame() end
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
	
	for i = 1, 10 do
		_G["BPBConfigButton"..i]:SetText("Key for " .. ns.BPB_Desc[i] .. ": " .. ns.BPB_Shorten(BPBindOptions.Bind[i]))
	end
end

-- update hotkeys when okay is pressed if in battle
function Options.okay()
	if not InCombatLockdown() and C_PetBattles.IsInBattle() then
		ns.UpdateHotKeys()
	end
end

-- update hotkeys when cancel is pressed if in battle
function Options.cancel()
	-- could potentially do something to void changes just made in the future, but for now just mimic functionality of okay button
	if not InCombatLockdown() and C_PetBattles.IsInBattle() then
		ns.UpdateHotKeys()
	end
end

-- set script for checkbox
BPBConfigForfeitBox:SetScript("OnClick", BPBConfigForfeitBox_OnClick)

-- add the Options panel to the Blizzard list
InterfaceOptions_AddCategory(Options)