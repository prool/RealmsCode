/*
 * structs.h
 *   Main data structure and type definitions
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
#ifndef MSTRUCT_H
#define MSTRUCT_H

#include <list>

#include "anchor.hpp"
#include "delayedAction.hpp"
#include "dice.hpp"
#include "global.hpp"
#include "money.hpp"
#include "realm.hpp"


class Object;
class Creature;
class Player;
class Monster;
class Exit;
class BaseRoom;
class UniqueRoom;
class Faction;
class Socket;
class MapMarker;
class EffectInfo;
class AlchemyEffect;
class MudObject;

// A common class that has a name and description to avoid two separate classes with name/desc (skill & command) being inherited by SkillCommand
class Nameable {
public:
    Nameable() {};
    virtual ~Nameable() {};

    bstring name;
    bstring description;

    bstring getName() const;
    bstring getDescription() const;

};

enum AlcoholState {
    ALCOHOL_SOBER = 0,
    ALCOHOL_TIPSY = 1,
    ALCOHOL_DRUNK = 2,
    ALCOHOL_INEBRIATED = 3
};

enum Sex {
    SEX_NONE = 0,
    SEX_FEMALE = 1,
    SEX_MALE = 2
};


enum EffectParentType {
    EFFECT_NO_PARENT,
    EFFECT_CREATURE,
    EFFECT_ROOM,
    EFFECT_EXIT
};



class MudFlag {
public:
    MudFlag();

    int id;
    bstring name;
    bstring desc;
};


// UniqueRoom effectList tags
typedef struct rom_tag {
public:
    rom_tag() { next_tag = 0; rom = 0; };
    struct rom_tag  *next_tag;
    UniqueRoom* rom;
} rtag;


// TODO: Rework first_charm and remove this
// Enemy effectList tags
typedef struct enm_tag {
public:
    enm_tag() { next_tag = 0; enemy[0] = 0; damage = 0; owner[0] = 0; };
    struct enm_tag  *next_tag;
    char            enemy[80];
    int             damage;
    char            owner[80];
} etag;


typedef struct vstat {
public:
    vstat() { num[0] = num[1] = num[2] = num[3] = num[4] = 0;
            hp = mp = pp = 0; level = race = 0; cls = cls2 = CreatureClass::NONE; };
    int     num[5];
    int     hp;
    int     mp;
    int     pp;
    int     rp;
    char    level;
    CreatureClass    cls;
    CreatureClass    cls2;
    char    race;
} vstat;


// Talk effectList tags
typedef struct tlk_tag {
public:
    tlk_tag() { next_tag = 0; key = 0; response = 0; type = 0; action = 0; target = 0; on_cmd = 0; if_cmd = 0;
            test_for = 0; do_act = 0; success = 0; if_goto_cmd = 0; not_goto_cmd = 0; goto_cmd = 0; arg1 = arg2 = 0; };
    struct tlk_tag *next_tag;
    char    *key;
    char    *response;
    char    type;
    char    *action;
    char    *target;
    char    on_cmd;     // action functions
    char    if_cmd;     // if # command succesful
    char    test_for;   // test for condition in Room
    char    do_act;     // do action
    char    success;    // command was succesful
    char    if_goto_cmd;    // used to jump to new cmd point
    char    not_goto_cmd;   // jump to cmd if not success
    char    goto_cmd;   // unconditional goto cmd
    int arg1;
    int arg2;
} ttag;


typedef struct tic {
public:
    tic() {amountCur = amountMax = amountTmp = 0; interval = intervalMax = intervalTmp = 0; };
    char    amountCur;
    char    amountMax;
    char    amountTmp;

    long    interval;
    long    intervalMax;
    long    intervalTmp;
} tic;


typedef struct spellTimer {
public:
    spellTimer() { interval = ltime = misc = misc2 = castLevel = 0; };
    long        interval;
    long        ltime;
    short       misc;
    short       misc2;
    char        castLevel;
} spellTimer;


// Daily-use operation struct
typedef struct daily {
public:
    daily() { max = cur = ltime = 0; };
    short       max;
    short       cur;
    long        ltime;
} daily;



typedef struct lockout {
public:
    lockout() { address[0] = password[0] = userid[0] = 0; };
    char        address[80];
    char        password[20];
    char        userid[9];
} lockout;


typedef struct osp_t {
    int     splno;
    Realm   realm;
    int     mp;
    Dice    damage;
    char    bonus_type;
    bool    drain;
} osp_t;


typedef struct osong_t {
    int     songno;
    Dice    damage;
} osong_t;


typedef struct saves {
public:
    saves() { chance = gained = misc = 0; };
    short   chance; // Percent chance to save.
    short   gained;
    short   misc;
} saves;



// These are special defines to reuse creature structure while still
// making the code readable.


typedef struct tagPlayer {
    Player* ply;
    Socket* sock;
//  iobuf   *io;
//  extra   *extr;
} plystruct;


typedef struct {
    short   hpstart;
    short   mpstart;
    short   hp;
    short   mp;
    short   ndice;
    short   sdice;
    short   pdice;
} class_stats_struct;


typedef struct {
    short    poison;    // Poison, disease, noxious clouds, etc...
    short    death;     // Deadly traps, massive damage, energy drain attacks, massive tramples, disintegrate spells, fatally wounds from touch, etc..
    short    breath;    // Exploding monsters, firey dragon breath, exploding traps...
    short    mental;    // Charm spells, hold-person spells, confusion spells, teleport traps, mp drain traps...
    short    spells;    // Offensive spell damage, stun spells, dispel-magic traps/spells, other adverse spell effects..
} saves_struct;


typedef struct {
    short   hp;
    short   mp;
    short   armor;
    short   thaco;
    short   ndice;
    short   sdice;
    short   pdice;
    short   str;
    short   dex;
    short   con;
    short   intel;
    short   pie;
    long    realms;
} creatureStats;


// ******************
//   MudMethod
// ******************
// Base class for Command, Spell, Song, etc
class MudMethod : public virtual Nameable {
public:
    virtual ~MudMethod() {};
    int priority;

    bool exactMatch(bstring toMatch); 
    bool partialMatch(bstring toMatch);
};

// ******************
//   MysticMethod
// ******************
// Base class for songs & spells
class MysticMethod: public MudMethod {
public:
    virtual ~MysticMethod() {};
           
    bool exactMatch(bstring toMatch); 
    bool partialMatch(bstring toMatch);

    virtual void save(xmlNodePtr rootNode) const = 0;
    const bstring& getScript() const;

public:
    bstring script;
    
protected:
    std::list<bstring> nameParts;
    void parseName();
};

// ******************
//   Spell
// ******************

class Spell: public MysticMethod {
public:
    Spell(xmlNodePtr rootNode);
    ~Spell() {};

    void save(xmlNodePtr rootNode) const;
};

#include "songs.hpp"

// Base class for Ply/Crt commands
class Command: public virtual MudMethod {
public:
    ~Command() {};
    bool    (*auth)(const Creature *);

    virtual int execute(Creature* player, cmd* cmnd) = 0;
};

// these are supplemental to the cmd class
class CrtCommand: public Command {
public:
    CrtCommand(bstring pCmdStr, int pPriority, int (*pFn)(Creature* player, cmd* cmnd), bool (*pAuth)(const Creature *), bstring pDesc): fn(pFn)
    {
        name = pCmdStr;
        priority = pPriority;
        auth = pAuth;
        description = pDesc;
    };
    ~CrtCommand() {};
    int (*fn)(Creature* player, cmd* cmnd);
    int execute(Creature* player, cmd* cmnd);
};

class PlyCommand: public Command {
public:
    PlyCommand(bstring pCmdStr, int pPriority, int (*pFn)(Player* player, cmd* cmnd), bool (*pAuth)(const Creature *), bstring pDesc): fn(pFn)
    {
        name = pCmdStr;
        priority = pPriority;
        auth = pAuth;
        description = pDesc;
    };
    ~PlyCommand() {};
    int (*fn)(Player* player, cmd* cmnd);
    int execute(Creature* player, cmd* cmnd);
};

typedef int (*PFNCOMPARE)(const void *, const void *);

#endif
