// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_samp_sound
    #undef _inc_samp_sound
#endif

// custom include-guard to ensure we don't duplicate
#if defined _samp_sound_included
	#endinput
#endif
#define _samp_sound_included

#include <a_samp>

#include <YSI_Data\y_iterate>

/*
 * <library>samp-sound</library>
 * <param name="soundid">The sound to play.</param>
 * <param name="x">X coordinate for the sound to play at.</param>
 * <param name="y">Y coordinate for the sound to play at.</param>
 * <param name="z">Z coordinate for the sound to play at.</param>
 * <param name="radius"></param>
 * <param name="worldid">Virtual world for the sound to play at.</param>
 * <param name="interiorid">Interior for the sound to play at.</param>
*/
stock PlaySoundAtPoint(soundid, Float:x, Float:y, Float:z, Float:radius = 30.0, worldid = 0, interiorid = 0)
{
	foreach(new playerid : Player)
	{
		if(!IsPlayerInRangeOfPoint(playerid, radius, x, y, z))
			continue;

		if((GetPlayerVirtualWorld(playerid) == worldid) && (GetPlayerInterior(playerid) == interiorid))
		{
			PlayerPlaySound(playerid, soundid, x, y, z);
		}
	}
}

/*
 * <library>samp-sound</library>
 * <param name="playerid">The ID of the player to play the sound at.</param>
 * <param name="soundid">The sound to play.</param>
 * <param name="radius">The distance within the sound should be played.</param>
*/
stock PlaySoundAtPlayer(playerid, soundid, Float:radius = 30.0)
{
	new
		Float:x,
		Float:y,
		Float:z;
	GetPlayerPos(playerid, x, y, z);

	PlaySoundAtPoint(soundid, x, y, z, radius, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
}