/*
 * special1.cpp
 *	 Special routines.
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

//*********************************************************************
//						doSpecial
//*********************************************************************

int Object::doSpecial(Player* player) {
	BaseRoom* room = player->getRoom();
	Socket* sock = player->getSock();
	char	str[80], str2[160];
	unsigned int i=0;

	switch(special) {
	case SP_MAPSC:
		strcpy(str, name);
		for(i=0; i<strlen(str); i++)
			if(str[i] == ' ')
				str[i] = '_';
		sprintf(str2, "%s/%s.txt", Path::Sign, str);
		if(flagIsSet(O_LOGIN_FILE))
			viewLoginFile(player->getSock(), str2);
		else
			viewFile(player->getSock(), str2);
		break;
		
	case SP_COMBO:
		xtag	*xp;
		char	str[80];
		int		dmg, i;

		str[0] = damage.getSides()+'0';
		str[1] = 0;

		if(damage.getNumber() == 1 || strlen(sock->tempstr[3]) > 70)
			strcpy(sock->tempstr[3], str);
		else
			strcat(sock->tempstr[3], str);

		player->print("Click.\n");
		if(!strcmp(player->name, "Bane"))
			player->print("Combo so far: %s\n", sock->tempstr[3]);

		broadcast(sock, room, "%M presses %P^x.", player, this);

		if(strlen(sock->tempstr[3]) >= strlen(use_output)) {
			if(strcmp(sock->tempstr[3], use_output)) {
				dmg = mrand(20,40 + player->getLevel());
				player->hp.decrease(dmg);
				player->printColor("You were zapped for %s%d^x damage!\n", player->customColorize("*CC:DAMAGE*").c_str(), dmg);
				broadcast(sock, room, "%M was zapped by %P^x!", player, this);
				sock->tempstr[3][0] = 0;

				if(player->hp.getCur() < 1) {
					player->print("You died.\n");
					//((Creature*)player)->die((Creature*)player);
					player->die(ZAPPED);
				}
			} else {
				for(i=1, xp = room->first_ext;
						xp && i < damage.getPlus();
						i++, xp = xp->next_tag)
					;
				if(!xp)
					return(0);
				player->statistics.combo();
				player->print("You opened the %s!\n", xp->ext->name);
				broadcast(player->getSock(), player->getRoom(),
					"%M opened the %s!", player, xp->ext->name);
				xp->ext->clearFlag(X_LOCKED);
				xp->ext->clearFlag(X_CLOSED);
				xp->ext->ltime.ltime = time(0);
			}
		}
		break;
		
	default:
		player->print("Nothing.\n");
		break;
	}

	return(0);
}
