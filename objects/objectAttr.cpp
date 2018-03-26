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
 *  GNU Affero General Public License v3 or later
 *
 *  Copyright (C) 2007-2018 Jason Mitchell, Randi Mitchell
 *     Contributions by Tim Callahan, Jonathan Hseu
 *  Based on Mordor (C) Brooke Paul, Brett J. Vickers, John P. Freeman
 *
 */

#include "creatures.hpp"
#include "mud.hpp"



//*********************************************************************
//                      track
//*********************************************************************

void Object::track(Player* player) { lastMod = player->getName(); }

//*********************************************************************
//                      setDelay
//*********************************************************************

void Object::setDelay(int newDelay) { delay = newDelay; }

//*********************************************************************
//                      setExtra
//*********************************************************************

void Object::setExtra(int x) { extra = x; }

//*********************************************************************
//                      setWeight
//*********************************************************************

void Object::setWeight(short w) { weight = w; }

//*********************************************************************
//                      setBulk
//*********************************************************************

void Object::setBulk(short b) { bulk = MAX<short>(0, b); }

//*********************************************************************
//                      setMaxbulk
//*********************************************************************

void Object::setMaxbulk(short b) { maxbulk = b; }

//*********************************************************************
//                      setSize
//*********************************************************************

void Object::setSize(Size s) { size = s; }

//*********************************************************************
//                      setType
//*********************************************************************

void Object::setType(ObjectType t) { type = t; }

//*********************************************************************
//                      setWearflag
//*********************************************************************

void Object::setWearflag(short w) { wearflag = w; }

//*********************************************************************
//                      setArmor
//*********************************************************************

void Object::setArmor(short a) { armor = MAX<short>(0, MIN<short>(a, 1000)); }

//*********************************************************************
//                      setQuality
//*********************************************************************

void Object::setQuality(short q) { quality = q; }

//*********************************************************************
//                      setAdjustment
//*********************************************************************

void Object::setAdjustment(short a) {
    removeFromSet();
    adjustment = MAX<short>(-127, MIN<short>(a, 127));
    addToSet();
}

//*********************************************************************
//                      setNumAttacks
//*********************************************************************

void Object::setNumAttacks(short n) { numAttacks = n; }

//*********************************************************************
//                      setShotsmax
//*********************************************************************

void Object::setShotsMax(short s) { shotsMax = s; }

//*********************************************************************
//                      setShotscur
//*********************************************************************

void Object::setShotsCur(short s) { shotsCur = s; }

//*********************************************************************
//                      decShotscur
//*********************************************************************

void Object::decShotsCur(short s) { shotsCur -= s; }

//*********************************************************************
//                      incShotscur
//*********************************************************************

void Object::incShotsCur(short s) { shotsCur += s; }

//*********************************************************************
//                      setChargesMax
//*********************************************************************

void Object::setChargesMax(short s) { chargesMax = s; }

//*********************************************************************
//                      setChargesCur
//*********************************************************************

void Object::setChargesCur(short s) { chargesCur = s; }

//*********************************************************************
//                      decChargesCur
//*********************************************************************

void Object::decChargesCur(short s) { chargesCur -= s; }

//*********************************************************************
//                      incChargesCur
//*********************************************************************

void Object::incChargesCur(short s) { chargesCur += s; }


//*********************************************************************
//                      setMagicpower
//*********************************************************************

void Object::setMagicpower(short m) { magicpower = m; }

//*********************************************************************
//                      setLevel
//*********************************************************************

void Object::setLevel(short l) { level = l; }

//*********************************************************************
//                      setRequiredSkill
//*********************************************************************

void Object::setRequiredSkill(int s) { requiredSkill = s; }

//*********************************************************************
//                      setMinStrength
//*********************************************************************

void Object::setMinStrength(short s) { minStrength = s; }

//*********************************************************************
//                      setClan
//*********************************************************************

void Object::setClan(short c) { clan = c; }

//*********************************************************************
//                      setSpecial
//*********************************************************************

void Object::setSpecial(short s) { special = s; }

//*********************************************************************
//                      setQuestnum
//*********************************************************************

void Object::setQuestnum(short q) { questnum = q; }

//*********************************************************************
//                      setEffect
//*********************************************************************

void Object::setEffect(bstring e) { effect = e; }

//*********************************************************************
//                      setEffectDuration
//*********************************************************************

void Object::setEffectDuration(long d) { effectDuration = MAX<long>(-1, MIN<long>(d, EFFECT_MAX_DURATION)); }

//*********************************************************************
//                      setEffectStrength
//*********************************************************************

void Object::setEffectStrength(short s) { effectStrength = MAX<long>(0, MIN<long>(s, EFFECT_MAX_STRENGTH)); }

//*********************************************************************
//                      setCoinCost
//*********************************************************************

void Object::setCoinCost(unsigned long c) { coinCost = c; }

//*********************************************************************
//                      setShopValue
//*********************************************************************

void Object::setShopValue(unsigned long v) {
    removeFromSet();
    shopValue = MIN<unsigned long>(200000000, v);
    addToSet();
}

//*********************************************************************
//                      setLotteryCycle
//*********************************************************************

void Object::setLotteryCycle(int c) { lotteryCycle = c; }

//*********************************************************************
//                      setLotteryNumbers
//*********************************************************************

void Object::setLotteryNumbers(short i, short n) { lotteryNumbers[i] = n; }

//*********************************************************************
//                      setRecipe
//*********************************************************************

void Object::setRecipe(int r) { recipe = r; }

//*********************************************************************
//                      setMaterial
//*********************************************************************

void Object::setMaterial(Material m) { material = m; }

//*********************************************************************
//                      setQuestOwner
//*********************************************************************

void Object::setQuestOwner(const Player* player) { questOwner = player->getName(); }

//*********************************************************************
//                      clearEffect
//*********************************************************************

void Object::clearEffect() {
    setEffect("");
    setEffectDuration(0);
    setEffectStrength(0);
}

//*********************************************************************
//                      flagIsSet
//*********************************************************************

bool Object::flagIsSet(int flag) const {
    return(flags[flag/8] & 1<<(flag%8));
}

//*********************************************************************
//                      setFlag
//*********************************************************************

void Object::setFlag(int flag) {
    flags[flag/8] |= 1<<(flag%8);
}

//*********************************************************************
//                      clearFlag
//*********************************************************************

void Object::clearFlag(int flag) {
    flags[flag/8] &= ~(1<<(flag%8));
}

//*********************************************************************
//                      toggleFlag
//*********************************************************************

bool Object::toggleFlag(int flag) {
    if(flagIsSet(flag))
        clearFlag(flag);
    else
        setFlag(flag);
    return(flagIsSet(flag));
}

//*********************************************************************
//                      getVersion
//*********************************************************************

bstring Object::getVersion() const {
    return(version);
}

//*********************************************************************
//                      setMade
//*********************************************************************

void Object::setMade() {
    made = time(0);
}

//*********************************************************************
//                      isHeavyArmor
//*********************************************************************

bool Object::isHeavyArmor() const {
//  return(type == ObjectType::ARMOR && (subType == "chain" || subType == "plate"));
    return(type == ObjectType::ARMOR && subType == "plate");
}

//*********************************************************************
//                      isMediumArmor
//*********************************************************************

bool Object::isMediumArmor() const {
    return(type == ObjectType::ARMOR && subType == "chain");
}

//*********************************************************************
//                      isLightArmor
//*********************************************************************

bool Object::isLightArmor() const {
    return(type == ObjectType::ARMOR && (subType == "cloth" || subType == "leather"));
}

//*********************************************************************
//                      isBroken
//*********************************************************************

bool Object::isBroken() const {
    return(shotsCur == 0 && shotsMax >= 0 && (type == ObjectType::ARMOR || type == ObjectType::KEY || type == ObjectType::WEAPON));
}
