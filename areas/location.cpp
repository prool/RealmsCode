/*
 * location.cpp
 *   Location file
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
#include "rooms.hpp"
#include "server.hpp"
#include "xml.hpp"


//*********************************************************************
//                      Location
//*********************************************************************

Location::Location() { }

void Location::save(xmlNodePtr rootNode, bstring name) const {
    xmlNodePtr curNode = xml::newStringChild(rootNode, name);
    room.save(curNode, "Room", false);
    if(mapmarker.getArea()) {
        xmlNodePtr childNode = xml::newStringChild(curNode, "MapMarker");
        mapmarker.save(childNode);
    }
}

void Location::load(xmlNodePtr curNode) {
    xmlNodePtr childNode = curNode->children;

    while(childNode) {
        if(NODE_NAME(childNode, "Room")) room.load(childNode);
        else if(NODE_NAME(childNode, "MapMarker")) mapmarker.load(childNode);
        childNode = childNode->next;
    }
}

bstring Location::str() const {
    if(room.id)
        return(room.str());
    return(mapmarker.str());
}

bool Location::operator==(const Location& l) const {
    return( (   (room.id == 0 && l.room.id == 0) || // if rooms are empty, don't care about area
                (room == l.room)                    // same room
            ) &&
            mapmarker == l.mapmarker
    );
}
bool Location::operator!=(const Location& l) const {
    return(!(*this == l));
}

BaseRoom* Location::loadRoom(Player* player) const {
    UniqueRoom* uRoom=0;
    if(room.id && ::loadRoom(room, &uRoom))
        return(uRoom);

    Area* area = gServer->getArea(mapmarker.getArea());
    if(area) {
        AreaRoom* aRoom = area->loadRoom(player, &mapmarker, false);
        return(aRoom);
    }

    return(0);
}

short Location::getId() const {
    if(room.id)
        return(room.id);
    return(mapmarker.getArea());
}

