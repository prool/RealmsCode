import mud
import re

CAP = 1

def ucfirst(str):
	return str[0].upper() + str[1:]

def auxReplace(str, viewer, argType, type, **args):
	if argType in args:
		if args[argType].getExit():
			str = str.replace("*" + type + "*", ucfirst(args[argType].getName()))
			str = str.replace("*LOW-" + type + "*", args[argType].getName())
		else:
			str = str.replace("*" + type + "*", args[argType].getCrtStr(viewer, CAP))
			str = str.replace("*LOW-" + type + "*", args[argType].getCrtStr(viewer))
	return str

def doReplace(fmt, viewer, **args):
	toReturn = viewer.customColorize(fmt)
	toReturn = auxReplace(toReturn, viewer, 'actor', 'ACTOR', **args)
	toReturn = auxReplace(toReturn, viewer, 'target', 'TARGET', **args)
	toReturn = auxReplace(toReturn, viewer, 'applier', 'APPLIER', **args)
	toReturn = toReturn.replace("*A-HISHER*", args['actor'].hisHer())
	toReturn = toReturn.replace("*A-UPHISHER*", args['actor'].hisHer())
	return toReturn

def broadcastRoom(room, fmt, **args):
	actor = None
	ignore = None
	ignore2 = None
	
	if 'actor' in args:
		actor = args['actor']

	if 'ignore' in args:
		ignore = args['ignore']

	if 'ignore2' in args:
		ignore2 = args['ignore2']

	if 'target' in args:
		target = args['target']
		
	for ply in room.players:
		if ply.equals(ignore) or ply.equals(ignore2) or ply.isUnconscious():
			continue
          
		toSend = doReplace(fmt, ply, **args)
		ply.send(toSend + "\n")

def indefinite_article(noun_phrase):
    # algorithm adapted from CPAN package Lingua-EN-Inflect-1.891 by Damian Conway
    m = re.search('\w+', noun_phrase)
    if m:
        word = m.group(0)
    else:
        return 'an'

    wordi = word.lower()
    for anword in ('euler', 'heir', 'honest', 'hono'):
        if wordi.startswith(anword):
            return 'an'

    if wordi.startswith('hour') and not wordi.startswith('houri'):
        return 'an'

    if len(word) == 1:
        if wordi in 'aedhilmnorsx':
            return 'an'
        else:
            return 'a'

    if re.match(r'(?!FJO|[HLMNS]Y.|RY[EO]|SQU|'
                  r'(F[LR]?|[HL]|MN?|N|RH?|S[CHKLMNPTVW]?|X(YL)?)[AEIOU])'
                  r'[FHLMNRSX][A-Z]', word):
        return 'an'

    for regex in (r'^e[uw]', r'^onc?e\b',
                    r'^uni([^nmd]|mo)','^u[bcfhjkqrst][aeiou]'):
        if re.match(regex, wordi):
            return 'a'

    # original regex was /^U[NK][AIEO]?/ but that matches UK, UN, etc.
    if re.match('^U[NK][AIEO]', word):
        return 'a'
    elif word == word.upper():
        if wordi[0] in 'aedhilmnorsx':
            return 'an'
        else:
            return 'a'

    if wordi[0] in 'aeio':
        return 'an'

    if re.match(r'^y(b[lor]|cl[ea]|fere|gg|p[ios]|rou|tt)', wordi):
        return 'an'
    else:
        return 'a'

def doPurchaseCast(actor, args, target):       
    spell = True
    effect = actor.getEffect()
    if mud.gConfig.effectExists(effect):
        spell = False

    casterId = args.split(",")[0]
    caster = actor
    if casterId != "":
        caster = target.getParent().findCreature(target, casterId)
        if spell == False:
            target.send(caster.getCrtStr(target, CAP) + " casts " + indefinite_article(effect) + " " + effect + " spell on you.\n")
            broadcastRoom(target.getRoom(), "*ACTOR* casts " + indefinite_article(effect) + " " + effect + " spell on *TARGET*.", actor = caster, target = target, ignore = target)

    if spell == False:
        target.addEffect(effect, actor.getEffectDuration(), actor.getEffectStrength(), actor, True, target, False)
    elif spell:
        action = "cast " + effect + " " + target.getName()
        mud.doCast(caster, target, effect)
    else:
        return True

    return False
