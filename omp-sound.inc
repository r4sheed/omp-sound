// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_omp_sound
    #undef _inc_omp_sound
#endif

// custom include-guard to ensure we don't duplicate
#if defined _omp_sound_included
	#endinput
#endif
#define _omp_sound_included

#include <open.mp>

#tryinclude <YSI_Data\y_iterate>

#if !defined SOUND_NO_SOUND_DEFINITIONS
	#define SOUND_CEILING_VENT_LAND 			(1002)
	#define SOUND_BONNET_DENT 					(1009)
	#define SOUND_WHEEL_OF_FORTUNE_CLACKER 		(1027)
	#define SOUND_SHUTTER_DOOR_START 			(1035)
	#define SOUND_SHUTTER_DOOR_STOP 			(1036)
	#define SOUND_PARACHUTE_OPEN 				(1039)
	#define SOUND_AMMUNATION_BUY_WEAPON 		(1052)
	#define SOUND_AMMUNATION_BUY_WEAPON_DENIED 	(1053)
	#define SOUND_SHOP_BUY 						(1054)
	#define SOUND_SHOP_BUY_DENIED 				(1055)
	#define SOUND_RACE_321 						(1056)
	#define SOUND_RACE_GO 						(1057)
	#define SOUND_PART_MISSION_COMPLETE 		(1058)
	#define SOUND_GOGO_TRACK_START 				(1062)
	#define SOUND_GOGO_TRACK_STOP 				(1063)
	#define SOUND_DUAL_TRACK_START 				(1068)
	#define SOUND_DUAL_TRACK_STOP 				(1069)
	#define SOUND_BEE_TRACK_START 				(1076)
	#define SOUND_BEE_TRACK_STOP 				(1077)
	#define SOUND_ROULETTE_ADD_CASH 			(1083)
	#define SOUND_ROULETTE_REMOVE_CASH 			(1084)
	#define SOUND_ROULETTE_NO_CASH 				(1085)
	#define SOUND_BIKE_PACKER_CLUNK 			(1095)
	#define SOUND_AWARD_TRACK_START 			(1097)
	#define SOUND_AWARD_TRACK_STOP 				(1098)
	#define SOUND_MESH_GATE_OPEN_START 			(1100)
	#define SOUND_MESH_GATE_OPEN_STOP 			(1101)
	#define SOUND_PUNCH_PED 					(1130)
	#define SOUND_AMMUNATION_GUN_COLLISION 		(1131)
	#define SOUND_CAMERA_SHOT 					(1132)
	#define SOUND_BUY_CAR_MOD 					(1133)
	#define SOUND_BUY_CAR_RESPRAY 				(1134)
	#define SOUND_BASEBALL_BAT_HIT_PED 			(1135)
	#define SOUND_STAMP_PED 					(1136)
	#define SOUND_CHECKPOINT_AMBER 				(1137)
	#define SOUND_CHECKPOINT_GREEN 				(1138)
	#define SOUND_CHECKPOINT_RED 				(1139)
	#define SOUND_CAR_SMASH_CAR 				(1140)
	#define SOUND_CAR_SMASH_GATE 				(1141)
	#define SOUND_OTB_TRACK_START 				(1142)
	#define SOUND_OTB_TRACK_STOP 				(1143)
	#define SOUND_PED_HIT_WATER_SPLASH 			(1144)
	#define SOUND_RESTAURANT_TRAY_COLLISION 	(1145)
	#define SOUND_SWEETS_HORN 					(1147)
	#define SOUND_MAGNET_VEHICLE_COLLISION 		(1148)
	#define SOUND_PROPERTY_PURCHASED 			(1149)
	#define SOUND_PICKUP_STANDARD 				(1150)
	#define SOUND_GARAGE_DOOR_START 			(1153)
	#define SOUND_GARAGE_DOOR_STOP 				(1154)
	#define SOUND_PED_COLLAPSE 					(1163)
	#define SOUND_SHUTTER_DOOR_SLOW_START 		(1165)
	#define SOUND_SHUTTER_DOOR_SLOW_STOP 		(1166)
	#define SOUND_RESTAURANT_CJ_PUKE 			(1169)
	#define SOUND_DRIVING_AWARD_TRACK_START 	(1183)
	#define SOUND_DRIVING_AWARD_TRACK_STOP 		(1184)
	#define SOUND_BIKE_AWARD_TRACK_START 		(1185)
	#define SOUND_BIKE_AWARD_TRACK_STOP 		(1186)
	#define SOUND_PILOT_AWARD_TRACK_START 		(1187)
	#define SOUND_PILOT_AWARD_TRACK_STOP 		(1188)
	#define SOUND_SLAP 							(1190)
#endif

/*
 * <library>omp-sound</library>
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
	#if !defined _INC_y_iterate
		for (new playerid = 0; playerid < MAX_PLAYERS; playerid++) if (IsPlayerConnected(playerid))
	#else
		foreach (new playerid : Player)
	#endif
	{
		if (!IsPlayerInRangeOfPoint(playerid, radius, x, y, z))
			continue;

		if ((GetPlayerVirtualWorld(playerid) == worldid) && (GetPlayerInterior(playerid) == interiorid))
		{
			PlayerPlaySound(playerid, soundid, x, y, z);
		}
	}
}

/*
 * <library>omp-sound</library>
 * <param name="playerid">The ID of the player to play the sound at.</param>
 * <param name="soundid">The sound to play.</param>
 * <param name="radius">The distance within the sound should be played.</param>
*/
stock bool:PlaySoundAtPlayer(playerid, soundid, Float:radius = 30.0)
{
	new
		Float:x,
		Float:y,
		Float:z;
	if (!GetPlayerPos(playerid, x, y, z))
	{
		return false;
	}

	#if !defined _INC_y_iterate
		foreach (new i : StreamedPlayer[playerid])
		{
			if (IsPlayerInRangeOfPoint(i, radius, x, y, z))
			{
				PlayerPlaySound(i, soundid, x, y, z);
			}
		}

		PlayerPlaySound(playerid, soundid, x, y, z);
	#else
		PlaySoundAtPoint(soundid, x, y, z, radius, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
	#endif

	return true;
}