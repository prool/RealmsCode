/*
 * objectAttr.cpp
 *   Object attribute functions
 *   ____            _
 *  |  _ \ ___  __ _| |_ __ ___  ___
 *  | |_) / _ \/ _` | | '_ ` _ \/ __|
 *  |  _ <  __/ (_| | | | | | | \__ \
 *  |_| \_\___|\__,_|_|_| |_| |_|___/
 *
 * Permission to use, modify and distribute is granted via the
 *  Creative Commons - Attribution - Non Commercial - Share Alike 3.0 License
 *    http://creativecommons.org/licenses/by-nc-sa/3.0/
 *
 * 	Copyright (C) 2007-2012 Jason Mitchell, Randi Mitchell
 * 	   Contributions by Tim Callahan, Jonathan Hseu
 *  Based on Mordor (C) Brooke Paul, Brett J. Vickers, John P. Freeman
 *
 */
#include "mud.h"
#include "effects.h"


//*********************************************************************
//						track
//*********************************************************************

void Object::track(Player* player) { lastMod = player->name; }

//*********************************************************************
//						setDelay
//*********************************************************************

void Object::setDelay(int newDelay) { delay = newDelay; }

//*********************************************************************
//						setExtra
//*********************************************************************

void Object::setExtra(int x) { extra = x; }

//*********************************************************************
//						setWeight
//*********************************************************************

void Object::setWeight(short w) { weight = w; }

//*********************************************************************
//						setBulk
//*********************************************************************

void Object::setBulk(short b) { bulk = MAX(0, b); }

//*********************************************************************
//						setMaxbulk
//*********************************************************************

void Object::setMaxbulk(short b) { maxbulk = b; }

//*********************************************************************
//						setSize
//*********************************************************************

void Object::setSize(Size s) { size = s; }

//*********************************************************************
//						setType
//*********************************************************************

void Object::setType(short t) { type = t; }

//*********************************************************************
//						setWearflag
//*********************************************************************

void Object::setWearflag(short w) { wearflag = w; }

//*********************************************************************
//						setArmor
//*********************************************************************

void Object::setArmor(short a) { armor = MAX(0, MIN(a, 1000)); }

//*********************************************************************
//						setQuality
//*********************************************************************

void Object::setQuality(short q) { quality = q; }

//*********************************************************************
//						setAdjustment
//*********************************************************************

void Object::setAdjustment(short a) { adjustment = MAX(-127, MIN(a, 127)); }

//*********************************************************************
//						setNumAttacks
//*********************************************************************

void Object::setNumAttacks(short n) { numAttacks = n; }

//*********************************************************************
//						setShotsmax
//*********************************************************************

void Object::setShotsmax(short s) { shotsmax = s; }

//*********************************************************************
//						setShotscur
//*********************************************************************

void Object::setShotscur(short s) { shotscur = s; }

//*********************************************************************
//						decShotscur
//*********************************************************************

void Object::decShotscur(short s) { shotscur -= s; }

//*********************************************************************
//						incShotscur
//*********************************************************************

void Object::incShotscur(short s) { shotscur += s; }

//*********************************************************************
//						setMagicpower
//*********************************************************************

void Object::setMagicpower(short m) { magicpower = m; }

//*********************************************************************
//						setLevel
//*********************************************************************

void Object::setLevel(short l) { level = l; }

//*********************************************************************
//						setRequiredSkill
//*********************************************************************

void Object::setRequiredSkill(int s) { requiredSkill = s; }

//*********************************************************************
//						setMinStrength
//*********************************************************************

void Object::setMinStrength(short s) { minStrength = s; }

//*********************************************************************
//						setClan
//*********************************************************************

void Object::setClan(short c) { clan = c; }

//*********************************************************************
//						setSpecial
//*********************************************************************

void Object::setSpecial(short s) { special = s; }

//*********************************************************************
//						setQuestnum
//*********************************************************************

void Object::setQuestnum(short q) { questnum = q; }

//*********************************************************************
//						setEffect
//*********************************************************************

void Object::setEffect(bstring e) { effect = e; }

//*********************************************************************
//						setEffectDuration
//*********************************************************************

void Object::setEffectDuration(long d) { effectDuration = MAX(-1, MIN(d, EFFECT_MAX_DURATION)); }

//*********************************************************************
//						setEffectStrength
//*********************************************************************

void Object::setEffectStrength(short s) { effectStrength = MAX(0, MIN(s, EFFECT_MAX_STRENGTH)); }

//*********************************************************************
//						setCoinCost
//*********************************************************************

void Object::setCoinCost(unsigned long c) { coinCost = c; }

//*********************************************************************
//						setShopValue
//*********************************************************************

void Object::setShopValue(unsigned long v) { shopValue = MIN(200000000, v); }

//*********************************************************************
//						setLotteryCycle
//*********************************************************************

void Object::setLotteryCycle(int c) { lotteryCycle = c; }

//*********************************************************************
//						setLotteryNumbers
//*********************************************************************

void Object::setLotteryNumbers(short i, short n) { lotteryNumbers[i] = n; }

//*********************************************************************
//						setRecipe
//*********************************************************************

void Object::setRecipe(int r) { recipe = r; }

//*********************************************************************
//						setMaterial
//*********************************************************************

void Object::setMaterial(Material m) { material = m; }

//*********************************************************************
//						setQuestOwner
//*********************************************************************

void Object::setQuestOwner(const Player* player) { questOwner = player->name; }

//*********************************************************************
//						setUniqueId
//*********************************************************************

void Object::setUniqueId(int id) { uniqueId = id; }

//*********************************************************************
//						clearEffect
//*********************************************************************

void Object::clearEffect() {
	setEffect("");
	setEffectDuration(0);
	setEffectStrength(0);
}

//*********************************************************************
//						flagIsSet
//*********************************************************************

bool Object::flagIsSet(int flag) const {
	return(flags[flag/8] & 1<<(flag%8));
}

//*********************************************************************
//						setFlag
//*********************************************************************

void Object::setFlag(int flag) {
	flags[flag/8] |= 1<<(flag%8);
}

//*********************************************************************
//						clearFlag
//*********************************************************************

void Object::clearFlag(int flag) {
	flags[flag/8] &= ~(1<<(flag%8));
}

//*********************************************************************
//						toggleFlag
//*********************************************************************

bool Object::toggleFlag(int flag) {
	if(flagIsSet(flag))
		clearFlag(flag);
	else
		setFlag(flag);
	return(flagIsSet(flag));
}

//*********************************************************************
//						getVersion
//*********************************************************************

bstring Object::getVersion() const {
	return(version);
}

//*********************************************************************
//						setMade
//*********************************************************************

void Object::setMade() {
	made = time(0);
}

//*********************************************************************
//						isHeavyArmor
//*********************************************************************

bool Object::isHeavyArmor() const {
//	return(type == ARMOR && (subType == "chain" || subType == "plate"));
	return(type == ARMOR && subType == "plate");
}

//*********************************************************************
//						isMediumArmor
//*********************************************************************

bool Object::isMediumArmor() const {
	return(type == ARMOR && subType == "chain");
}

//*********************************************************************
//						isLightArmor
//*********************************************************************

bool Object::isLightArmor() const {
	return(type == ARMOR && (subType == "cloth" || subType == "leather"));
}

//*********************************************************************
//						isBroken
//*********************************************************************

bool Object::isBroken() const {
	return(shotscur == 0 && shotsmax >= 0 && (type == ARMOR || type == KEY || type == WEAPON));
}
