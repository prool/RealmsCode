/*
 * creatureStreams.cpp
 *   Handles streaming to creatures
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
 *  Copyright (C) 2007-2012 Jason Mitchell, Randi Mitchell
 *     Contributions by Tim Callahan, Jonathan Hseu
 *  Based on Mordor (C) Brooke Paul, Brett J. Vickers, John P. Freeman
 *
 */

#include "mud.h"

Streamable& Streamable::operator << ( Streamable& (*op)(Streamable&)) {
    // call the function passed as parameter with this stream as the argument
    return (*op)(*this);
}

Streamable& operator<<(Streamable& out, setf flags) {
    return flags(out);
}

Streamable& setf::operator()(Streamable& out) const {
    out.setManipFlags(value);
    return(out);
}

Streamable& operator<<(Streamable& out, setn num) {
    return num(out);
}

Streamable& setn::operator()(Streamable& out) const {
    out.setManipNum(value);
    return(out);
}


void Streamable::initStreamable() {
    manipFlags = 0;
    manipNum = 0;
    streamColor = false;
}


Streamable& Streamable::operator<< ( MudObject& mo) {
	Player* player = dynamic_cast<Player*>(this);
    if(player && player->getSock()) {
        const Creature* creature = mo.getCreature();
        const Object* object = mo.getObject();

        int mFlags = player->displayFlags() | player->getManipFlags();
        int mNum = player->getManipNum();
        if(creature) {
            doPrint(creature->getCrtStr(player, mFlags, mNum));
        } else if(object) {
            doPrint(object->getObjStr(player, mFlags, mNum));
        }

    }
    return(*this);
}

Streamable& Streamable::operator<< ( MudObject* mo) {
    return(*this << *mo);
}

Streamable& Streamable::operator<< (const bstring& str) {
    const Player* player = dynamic_cast<Player*>(this);
    if(player && player->getSock()) {
        doPrint(str);
    }
    return(*this);
}
void Streamable::setColorOn() {
    streamColor = true;
}
void Streamable::setColorOff() {
    streamColor = false;
}

void Streamable::setManipFlags(int flags) {
    manipFlags |= flags;
    std::cout << "setManipFlags" << std::endl;
}

// Returns the manipFlags and resets them
int Streamable::getManipFlags() {
    int toReturn = manipFlags;
    manipFlags = 0;

    return (toReturn);
}

void Streamable::setManipNum(int num) {
    manipNum = num;

}

// Returns the manipNum and resets them
int Streamable::getManipNum() {
    int toReturn = manipNum;
    manipNum = 0;
    return(toReturn);
}

void Streamable::doPrint(const bstring& toPrint) {
    const Player* player = dynamic_cast<Player*>(this);
    if(player) {
        Socket* sock = player->getSock();
        if(sock) {
            if(streamColor)
                sock->bprintColor(toPrint);
            else
                sock->bprintNoColor(toPrint);
        }
    }
}