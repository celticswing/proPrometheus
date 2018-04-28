#include "Configuration.hpp"
#include "Variables.h"
#include <winerror.h>
#pragma warning( disable : 4091)
#include <ShlObj.h>
#include <string>
#include <sstream>
#include "XorStr.hpp"


const char* GetWeaponName(int iWeaponID)
{
	switch (iWeaponID)
	{
	default:
		return "none";
	case WEAPON_DEAGLE:
		return "deagle";
	case WEAPON_DUALS:
		return "duals";
	case WEAPON_FIVE7:
		return "five7";
	case WEAPON_GLOCK:
		return "glock";
	case WEAPON_AK47:
		return "ak47";
	case WEAPON_AUG:
		return "aug";
	case WEAPON_AWP:
		return "awp";
	case WEAPON_FAMAS:
		return "famas";
	case WEAPON_G3SG1:
		return "g3sg1";
	case WEAPON_GALIL:
		return "galil";
	case WEAPON_M249:
		return "m249";
	case WEAPON_M4A1:
		return "m4a4";
	case WEAPON_MAC10:
		return "mac10";
	case WEAPON_P90:
		return "p90";
	case WEAPON_UMP45:
		return "ump45";
	case WEAPON_XM1014:
		return "xm1014";
	case WEAPON_BIZON:
		return "bizon";
	case WEAPON_MAG7:
		return "mag7";
	case WEAPON_NEGEV:
		return "negev";
	case WEAPON_SAWEDOFF:
		return "sawedoff";
	case WEAPON_TEC9:
		return "tec9";
	case WEAPON_TASER:
		return "taser";
	case WEAPON_USPS:
		return "usp-s";
	case WEAPON_MP7:
		return "mp7";
	case WEAPON_MP9:
		return "mp9";
	case WEAPON_NOVA:
		return "nova";
	case WEAPON_P250:
		return "p250";
	case WEAPON_SCAR20:
		return "scar20";
	case WEAPON_SG553:
		return "sg556";
	case WEAPON_SCOUT:
		return "ssg08";
	case WEAPON_M4A1S:
		return "m4a1-s";
	case WEAPON_P2000:
		return "p2000";
	case WEAPON_CZ75:
		return "cz75";
	case WEAPON_REVOLVER:
		return "revolver";
	case WEAPON_KNIFE_BAYONET:
		return "bayonet";
	case WEAPON_KNIFE_BUTTERFLY:
		return "butterfly";
	case WEAPON_KNIFE_FALCHION:
		return "falshion";
	case WEAPON_KNIFE_FLIP:
		return "flip";
	case WEAPON_KNIFE_GUT:
		return "gut";
	case WEAPON_KNIFE_KARAMBIT:
		return "karambit";
	case WEAPON_KNIFE_M9BAYONET:
		return "m9";
	case WEAPON_KNIFE_HUNTSMAN:
		return "huntsman";
	case WEAPON_KNIFE_BOWIE:
		return "bowie";
	case WEAPON_KNIFE_DAGGER:
		return "daggers";
	}
}


void CConfig::Setup()
{
	//RAGEBOT
	SetupValue(g_Options.Ragebot.MainSwitch, false, ("Ragebot"), ("RageToggle"));
	SetupValue(g_Options.Ragebot.Enabled, false, ("Ragebot"), ("Enabled"));
	SetupValue(g_Options.Ragebot.AutoFire, false, ("Ragebot"), ("AutoFire"));
	SetupValue(g_Options.Ragebot.FOV, 0.f, ("Ragebot"), ("FOV"));
	SetupValue(g_Options.Ragebot.Silent, false, ("Ragebot"), ("Silent"));
	SetupValue(g_Options.Ragebot.AutoPistol, false, ("Ragebot"), ("AutoPistol"));
	SetupValue(g_Options.Ragebot.KeyPress, 0, ("Ragebot"), ("Key"));


	SetupValue(g_Options.Ragebot.EnabledAntiAim, false, ("Ragebot"), ("AntiaimEnabled"));
	SetupValue(g_Options.Ragebot.PreAAs, false, ("Ragebot"), ("Pre-set-AAs"));
	SetupValue(g_Options.Ragebot.Pitch, 0, ("Ragebot"), ("AntiaimPitch"));
	SetupValue(g_Options.Ragebot.YawTrue, 0, ("Ragebot"), ("AntiaimYaw-true"));
	SetupValue(g_Options.Ragebot.YawFake, 0, ("Ragebot"), ("AntiaimYaw-fake"));
	SetupValue(g_Options.Ragebot.AtTarget, false, ("Ragebot"), ("attargets"));
	SetupValue(g_Options.Ragebot.Edge, false, ("Ragebot"), ("edge"));
	SetupValue(g_Options.Ragebot.KnifeAA, false, ("Ragebot"), ("KnifeAA"));
	SetupValue(g_Options.Ragebot.BuilderAAs, false, ("Ragebot"), ("Builder-AAs"));
	SetupValue(g_Options.Ragebot.BuilderPitch, 0, ("Ragebot"), ("Builder-Pitch"));
	SetupValue(g_Options.Ragebot.BuilderReal, 0, ("Ragebot"), ("Builder-Yaw"));
	SetupValue(g_Options.Ragebot.BuilderFake, 0, ("Ragebot"), ("Builder-Fake"));
	SetupValue(g_Options.Ragebot.Jitter, false, ("Ragebot"), ("Builder-Jitter"));
	SetupValue(g_Options.Ragebot.JitterRange, 0, ("Ragebot"), ("Builder-Jitter-Range"));
	SetupValue(g_Options.Ragebot.FJitter, false, ("Ragebot"), ("Builder-fJitter"));
	SetupValue(g_Options.Ragebot.FJitterRange, 0, ("Ragebot"), ("Builder-fJitter-Range"));
	SetupValue(g_Options.Ragebot.LBYBreaker, false, ("Ragebot"), ("Builder-LBY-Breaker"));
	SetupValue(g_Options.Ragebot.FakeLag, false, ("Ragebot"), ("Fakelag"));
	SetupValue(g_Options.Ragebot.FakeLagAmt, 0, ("Ragebot"), ("Fakelag Amount"));
	SetupValue(g_Options.Ragebot.fakewalk, false, ("Ragebot"), ("Fakewalk"));
	SetupValue(g_Options.Ragebot.fakewalkkey, 0, ("Ragebot"), ("Fakewalk Key"));

	SetupValue(g_Options.Ragebot.FriendlyFire, false, ("Ragebot"), ("FriendlyFire"));
	SetupValue(g_Options.Ragebot.Hitbox, 0, ("Ragebot"), ("Hitbox"));
	SetupValue(g_Options.Ragebot.Hitscan, 0, ("Ragebot"), ("Hitscan"));

	SetupValue(g_Options.Ragebot.AntiRecoil, false, ("Ragebot"), ("AntiRecoil"));
	SetupValue(g_Options.Ragebot.AutoStop, 0, ("Ragebot"), ("AutoStop"));
	SetupValue(g_Options.Ragebot.AutoCrouch, false, ("Ragebot"), ("AutoCrouch"));
	SetupValue(g_Options.Ragebot.AutoScope, false, ("Ragebot"), ("AutoScope"));
	SetupValue(g_Options.Ragebot.MinimumDamageSniper, 0.f, ("Ragebot"), ("AutoWallDamageSniper"));
	SetupValue(g_Options.Ragebot.MinimumDamagePistol, 0.f, ("Ragebot"), ("AutoWallDamagePistol"));
	SetupValue(g_Options.Ragebot.MinimumDamageRifle, 0.f, ("Ragebot"), ("AutoWallDamageRifle"));
	SetupValue(g_Options.Ragebot.MinimumDamageHeavy, 0.f, ("Ragebot"), ("AutoWallDamageHeavy"));
	SetupValue(g_Options.Ragebot.MinimumDamageSmg, 0.f, ("Ragebot"), ("AutoWallDamageSmgs"));
	SetupValue(g_Options.Ragebot.MinimumDamageRevolver, 0.f, ("Ragebot"), ("AutoWallDamageRevolver"));
	SetupValue(g_Options.Ragebot.Hitchance, false, ("Ragebot"), ("HitChance"));
	SetupValue(g_Options.Ragebot.HitchanceSniper, 0.f, ("Ragebot"), ("HitChanceSniper"));
	SetupValue(g_Options.Ragebot.HitchancePistol, 0.f, ("Ragebot"), ("HitChancePistol"));
	SetupValue(g_Options.Ragebot.HitchanceHeavy, 0.f, ("Ragebot"), ("HitChanceHeavy"));
	SetupValue(g_Options.Ragebot.HitchanceSmgs, 0.f, ("Ragebot"), ("HitChanceSmgs"));
	SetupValue(g_Options.Ragebot.HitchanceRifle, 0.f, ("Ragebot"), ("HitChanceRifle"));
	SetupValue(g_Options.Ragebot.HitchanceRevolver, 0.f, ("Ragebot"), ("HitChanceRevolver"));
	SetupValue(g_Options.Ragebot.Resolver, false, ("Ragebot"), ("Resolver"));
	SetupValue(g_Options.Ragebot.bruteAfterX, 0, ("Ragebot"), ("Bruteforce"));
	SetupValue(g_Options.Ragebot.FakeLagFix, false, ("Ragebot"), ("Fakelag Fix"));
	SetupValue(g_Options.Ragebot.PosAdjust, false, ("Ragebot"), ("Position Adjustment"));
	SetupValue(g_Options.Ragebot.BAIMkey, 0, ("Ragebot"), ("BAIMKey"));
	SetupValue(g_Options.Ragebot.BAIMIfLethal, false, ("Ragebot"), ("BAIMIfLethal"));


	//new aa stuff going here
	SetupValue(g_Options.Ragebot.AA_onCrouch, false, ("RageBot"), ("AACrouch"));
	SetupValue(g_Options.Ragebot.AA_onFakeWalk, false, ("RageBot"), ("AAFakeWalk"));
	SetupValue(g_Options.Ragebot.AA_onRun, false, ("RageBot"), ("AARun"));
	SetupValue(g_Options.Ragebot.AA_onWalk, false, ("RageBot"), ("AAWalk"));
	SetupValue(g_Options.Ragebot.AA_onStand, false, ("RageBot"), ("AAStand"));


	//walkiing builder aa's
	SetupValue(g_Options.Ragebot.walk_BuilderAAs, false, ("RageBot"), ("walk_BuilderAAs"));
	SetupValue(g_Options.Ragebot.walk_Jitter, false, ("RageBot"), ("walk_Jitter"));
	SetupValue(g_Options.Ragebot.walk_FJitter, false, ("RageBot"), ("walk_FJitter"));
	SetupValue(g_Options.Ragebot.walk_LBYBreaker, false, ("RageBot"), ("walk_LBYBreaker"));
	SetupValue(g_Options.Ragebot.walk_BuilderReal, 0, ("RageBot"), ("walk_BuilderReal"));
	SetupValue(g_Options.Ragebot.walk_BuilderFake, 0, ("RageBot"), ("walk_BuilderFake"));
	SetupValue(g_Options.Ragebot.walk_BuilderPitch, 0, ("RageBot"), ("walk_BuilderPitch"));
	SetupValue(g_Options.Ragebot.walk_JitterRange, 0, ("RageBot"), ("walk_JitterRange"));
	SetupValue(g_Options.Ragebot.walk_FJitterRange, 0, ("RageBot"), ("walk_FJitterRange"));

	//ruinning builder aa's
	SetupValue(g_Options.Ragebot.run_BuilderAAs, false, ("RageBot"), ("run_BuilderAAs"));
	SetupValue(g_Options.Ragebot.run_Jitter, false, ("RageBot"), ("run_Jitter"));
	SetupValue(g_Options.Ragebot.run_FJitter, false, ("RageBot"), ("run_FJitter"));
	SetupValue(g_Options.Ragebot.run_LBYBreaker, false, ("RageBot"), ("run_LBYBreaker"));
	SetupValue(g_Options.Ragebot.run_BuilderReal, 0, ("RageBot"), ("run_BuilderReal"));
	SetupValue(g_Options.Ragebot.run_BuilderFake, 0, ("RageBot"), ("run_BuilderFake"));
	SetupValue(g_Options.Ragebot.run_BuilderPitch, 0, ("RageBot"), ("run_BuilderPitch"));
	SetupValue(g_Options.Ragebot.run_JitterRange, 0, ("RageBot"), ("run_JitterRange"));
	SetupValue(g_Options.Ragebot.run_FJitterRange, 0, ("RageBot"), ("run_FJitterRange"));

	//crouching builder aa's
	SetupValue(g_Options.Ragebot.crouch_BuilderAAs, false, ("RageBot"), ("crouch_BuilderAAs"));
	SetupValue(g_Options.Ragebot.crouch_Jitter, false, ("RageBot"), ("crouch_Jitter"));
	SetupValue(g_Options.Ragebot.crouch_FJitter, false, ("RageBot"), ("crouch_FJitter"));
	SetupValue(g_Options.Ragebot.crouch_LBYBreaker, false, ("RageBot"), ("crouch_LBYBreaker"));
	SetupValue(g_Options.Ragebot.crouch_BuilderReal, 0, ("RageBot"), ("crouch_BuilderReal"));
	SetupValue(g_Options.Ragebot.crouch_BuilderFake, 0, ("RageBot"), ("crouch_BuilderFake"));
	SetupValue(g_Options.Ragebot.crouch_BuilderPitch, 0, ("RageBot"), ("crouch_BuilderPitch"));
	SetupValue(g_Options.Ragebot.crouch_JitterRange, 0, ("RageBot"), ("crouch_JitterRange"));
	SetupValue(g_Options.Ragebot.crouch_FJitterRange, 0, ("RageBot"), ("crouch_FJitterRange"));

	//fakewalk builder aa's
	SetupValue(g_Options.Ragebot.fwalk_BuilderAAs, false, ("RageBot"), ("fwalk_BuilderAAs"));
	SetupValue(g_Options.Ragebot.fwalk_Jitter, false, ("RageBot"), ("fwalk_Jitter"));
	SetupValue(g_Options.Ragebot.fwalk_FJitter, false, ("RageBot"), ("fwalk_FJitter"));
	SetupValue(g_Options.Ragebot.fwalk_LBYBreaker, false, ("RageBot"), ("fwalk_LBYBreaker"));
	SetupValue(g_Options.Ragebot.fwalk_BuilderReal, 0, ("RageBot"), ("fwalk_BuilderReal"));
	SetupValue(g_Options.Ragebot.fwalk_BuilderFake, 0, ("RageBot"), ("fwalk_BuilderFake"));
	SetupValue(g_Options.Ragebot.fwalk_BuilderPitch, 0, ("RageBot"), ("fwalk_BuilderPitch"));
	SetupValue(g_Options.Ragebot.fwalk_JitterRange, 0, ("RageBot"), ("fwalk_JitterRange"));
	SetupValue(g_Options.Ragebot.fwalk_FJitterRange, 0, ("RageBot"), ("fwalk_FJitterRange"));

	//standing builder aa's
	SetupValue(g_Options.Ragebot.stand_BuilderAAs, false, ("RageBot"), ("stand_BuilderAAs"));
	SetupValue(g_Options.Ragebot.stand_Jitter, false, ("RageBot"), ("stand_Jitter"));
	SetupValue(g_Options.Ragebot.stand_FJitter, false, ("RageBot"), ("stand_FJitter"));
	SetupValue(g_Options.Ragebot.stand_LBYBreaker, false, ("RageBot"), ("stand_LBYBreaker"));
	SetupValue(g_Options.Ragebot.stand_BuilderReal, 0, ("RageBot"), ("stand_BuilderReal"));
	SetupValue(g_Options.Ragebot.stand_BuilderFake, 0, ("RageBot"), ("stand_BuilderFake"));
	SetupValue(g_Options.Ragebot.stand_BuilderPitch, 0, ("RageBot"), ("stand_BuilderPitch"));
	SetupValue(g_Options.Ragebot.stand_JitterRange, 0, ("RageBot"), ("stand_JitterRange"));
	SetupValue(g_Options.Ragebot.stand_FJitterRange, 0, ("RageBot"), ("stand_FJitterRange"));


	//BEGINNING OF PREBUILT AA'S

	//walking prebuild aa's  walk
	SetupValue(g_Options.Ragebot.walk_PreAAs, false, ("RageBot"), ("walk_PreAAs"));
	SetupValue(g_Options.Ragebot.walk_Pitch, false, ("RageBot"), ("walk_Pitch"));
	SetupValue(g_Options.Ragebot.walk_PitchAdder, 0, ("RageBot"), ("walk_PitchAdder"));
	SetupValue(g_Options.Ragebot.walk_YawTrue, false, ("RageBot"), ("walk_YawTrue"));
	SetupValue(g_Options.Ragebot.walk_YawTrueAdder, 0, ("RageBot"), ("walk_YawTrueAdder"));
	SetupValue(g_Options.Ragebot.walk_YawFake, false, ("RageBot"), ("walk_YawFake"));
	SetupValue(g_Options.Ragebot.walk_YawFakeAdder, 0, ("RageBot"), ("walk_YawFakeAdder"));

	//running prebuild aa's
	SetupValue(g_Options.Ragebot.run_PreAAs, false, ("RageBot"), ("run_PreAAs"));
	SetupValue(g_Options.Ragebot.run_Pitch, false, ("RageBot"), ("run_Pitch"));
	SetupValue(g_Options.Ragebot.run_PitchAdder, 0, ("RageBot"), ("run_PitchAdder"));
	SetupValue(g_Options.Ragebot.run_YawTrue, false, ("RageBot"), ("run_YawTrue"));
	SetupValue(g_Options.Ragebot.run_YawTrueAdder, 0, ("RageBot"), ("run_YawTrueAdder"));
	SetupValue(g_Options.Ragebot.run_YawFake, false, ("RageBot"), ("run_YawFake"));
	SetupValue(g_Options.Ragebot.run_YawFakeAdder, 0, ("RageBot"), ("run_YawFakeAdder"));

	//crouching prebuild aa's crouch
	SetupValue(g_Options.Ragebot.crouch_PreAAs, false, ("RageBot"), ("_PreAAs"));
	SetupValue(g_Options.Ragebot.crouch_Pitch, false, ("RageBot"), ("_Pitch"));
	SetupValue(g_Options.Ragebot.crouch_PitchAdder, 0, ("RageBot"), ("_PitchAdder"));
	SetupValue(g_Options.Ragebot.crouch_YawTrue, false, ("RageBot"), ("_YawTrue"));
	SetupValue(g_Options.Ragebot.crouch_YawTrueAdder, 0, ("RageBot"), ("_YawTrueAdder"));
	SetupValue(g_Options.Ragebot.crouch_YawFake, false, ("RageBot"), ("_YawFake"));
	SetupValue(g_Options.Ragebot.crouch_YawFakeAdder, 0, ("RageBot"), ("_YawFakeAdder"));

	//fakewalking prebuild aa's fwalk
	SetupValue(g_Options.Ragebot.fwalk_PreAAs, false, ("RageBot"), ("fwalk_PreAAs"));
	SetupValue(g_Options.Ragebot.fwalk_Pitch, false, ("RageBot"), ("fwalk_Pitch"));
	SetupValue(g_Options.Ragebot.fwalk_PitchAdder, 0, ("RageBot"), ("fwalk_PitchAdder"));
	SetupValue(g_Options.Ragebot.fwalk_YawTrue, false, ("RageBot"), ("fwalk_YawTrue"));
	SetupValue(g_Options.Ragebot.fwalk_YawTrueAdder, 0, ("RageBot"), ("fwalk_YawTrueAdder"));
	SetupValue(g_Options.Ragebot.fwalk_YawFake, false, ("RageBot"), ("fwalk_YawFake"));
	SetupValue(g_Options.Ragebot.fwalk_YawFakeAdder, 0, ("RageBot"), ("fwalk_YawFakeAdder"));

	//standing prebuild aa's  stand
	SetupValue(g_Options.Ragebot.stand_PreAAs, false, ("RageBot"), ("stand_PreAAs"));
	SetupValue(g_Options.Ragebot.stand_Pitch, false, ("RageBot"), ("stand_Pitch"));
	SetupValue(g_Options.Ragebot.stand_PitchAdder, 0, ("RageBot"), ("stand_PitchAdder"));
	SetupValue(g_Options.Ragebot.stand_YawTrue, false, ("RageBot"), ("stand_YawTrue"));
	SetupValue(g_Options.Ragebot.stand_YawTrueAdder, 0, ("RageBot"), ("stand_YawTrueAdder"));
	SetupValue(g_Options.Ragebot.stand_YawFake, false, ("RageBot"), ("stand_YawFake"));
	SetupValue(g_Options.Ragebot.stand_YawFakeAdder, 0, ("RageBot"), ("stand_YawFakeAdder"));

	SetupValue(g_Options.Ragebot.walk_allowflip, false, ("RageBot"), ("walk_allowflip"));
	SetupValue(g_Options.Ragebot.run_allowflip, false, ("RageBot"), ("run_allowflip"));
	SetupValue(g_Options.Ragebot.crouch_allowflip, false, ("RageBot"), ("crouch_allowflip"));
	SetupValue(g_Options.Ragebot.fwalk_allowflip, false, ("RageBot"), ("fwalk_allowflip"));
	SetupValue(g_Options.Ragebot.stand_allowflip, false, ("RageBot"), ("stand_allowflip"));



	//LEGITBOT
	SetupValue(g_Options.LegitBot.Enable, false, ("Legitbot"), ("Enabled"));

	//BACKTRACK
	SetupValue(g_Options.Backtrack.backtrackenable, false, ("Legitbot"), ("Backtrack"));
	SetupValue(g_Options.Backtrack.BacktrackType, 0, ("Legitbot"), ("BacktrackType"));
	SetupValue(g_Options.Backtrack.backtrackticks, 0, ("Legitbot"), ("BacktrackTicks"));


	SetupValue(g_Options.LegitBot.MainKey, 1, ("Legitbot"), ("Key-Rifles"));
	SetupValue(g_Options.LegitBot.Mainfov, 0.f, ("Legitbot"), ("FOV-Rifles"));
	SetupValue(g_Options.LegitBot.MainSmooth, 1.f, ("Legitbot"), ("Smooth-Rifles"));
	SetupValue(g_Options.LegitBot.main_recoil_min, 0, ("Legitbot"), ("RCS-min-Rifles"));
	SetupValue(g_Options.LegitBot.main_recoil_max, 0, ("Legitbot"), ("RCS-max-Rifles"));

	SetupValue(g_Options.LegitBot.PistolKey, 6, ("Legitbot"), ("Key-Pistol"));
	SetupValue(g_Options.LegitBot.Pistolfov, 0.f, ("Legitbot"), ("FOV-Pistol"));
	SetupValue(g_Options.LegitBot.PistolSmooth, 1.f, ("Legitbot"), ("Smooth-Pistol"));
	SetupValue(g_Options.LegitBot.pistol_recoil_min, 0, ("Legitbot"), ("RCS-min-pistol"));
	SetupValue(g_Options.LegitBot.pistol_recoil_max, 0, ("Legitbot"), ("RCS-max-pistol"));

	SetupValue(g_Options.LegitBot.SniperKey, 6, ("Legitbot"), ("Key-Sniper"));
	SetupValue(g_Options.LegitBot.Sniperfov, 0.f, ("Legitbot"), ("FOV-Sniper"));
	SetupValue(g_Options.LegitBot.SniperSmooth, 0.f, ("Legitbot"), ("Smooth-Sniper"));
	SetupValue(g_Options.LegitBot.sniper_recoil_min, 0, ("Legitbot"), ("RCS-min-sniper"));
	SetupValue(g_Options.LegitBot.sniper_recoil_max, 0, ("Legitbot"), ("RCS-max-sniper"));

	//WEAPONS SETTS 
	SetupValue(g_Options.LegitBot.FilterMainWeapons.Headwpmain, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterMainWeapons.Neckwpmain, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterMainWeapons.Chestwpmain, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterMainWeapons.Stomachwpmain, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterMainWeapons.multiboneswpmain, false, ("Legitbot"), ("WeponsSettings"));

	//PISTOLS
	SetupValue(g_Options.LegitBot.FilterPistolWeapons.Headwppis, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterPistolWeapons.Neckwppis, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterPistolWeapons.Chestwppis, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterPistolWeapons.Stomachwppis, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterPistolWeapons.multiboneswppis, false, ("Legitbot"), ("WeponsSettings"));

	//SNIPER
	SetupValue(g_Options.LegitBot.FilterSniperWeapons.HeadwpSnip, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterSniperWeapons.NeckwpSnip, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterSniperWeapons.ChestwpSnip, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterSniperWeapons.StomachwpSnip, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterSniperWeapons.multiboneswpSnip, false, ("Legitbot"), ("WeponsSettings"));

	//SMGWEAPONS
	SetupValue(g_Options.LegitBot.FiltersmgWeapons.Headwpsmg, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FiltersmgWeapons.Neckwpsmg, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FiltersmgWeapons.Chestwpsmg, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FiltersmgWeapons.Stomachwpsmg, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FiltersmgWeapons.multiboneswpsmg, false, ("Legitbot"), ("WeponsSettings"));

	//HEABYWEAPONS
	SetupValue(g_Options.LegitBot.FilterheavyWeapons.Headwphv, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterheavyWeapons.Neckwphv, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterheavyWeapons.Chestwphv, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterheavyWeapons.Stomachwphv, false, ("Legitbot"), ("WeponsSettings"));
	SetupValue(g_Options.LegitBot.FilterheavyWeapons.multibonewphv, false, ("Legitbot"), ("WeponsSettings"));



	//TRIGGERBOT
	SetupValue(g_Options.LegitBot.Triggerbot.Enabled, false, ("Triggerbot"), ("Enabled"));
	SetupValue(g_Options.LegitBot.Triggerbot.Key, 6, ("Triggerbot"), ("Key"));
	SetupValue(g_Options.LegitBot.Triggerbot.Delay, 0.f, ("Triggerbot"), ("Delay"));
	SetupValue(g_Options.LegitBot.Triggerbot.hitchance, 0.f, ("Triggerbot"), ("Hitchance"));

	SetupValue(g_Options.LegitBot.Triggerbot.Filter.Head, false, ("Triggerbot"), ("FilterHead"));
	SetupValue(g_Options.LegitBot.Triggerbot.Filter.Chest, false, ("Triggerbot"), ("FilterChest"));
	SetupValue(g_Options.LegitBot.Triggerbot.Filter.Stomach, false, ("Triggerbot"), ("FilterStomach"));
	SetupValue(g_Options.LegitBot.Triggerbot.Filter.Arms, false, ("Triggerbot"), ("FilterArms"));
	SetupValue(g_Options.LegitBot.Triggerbot.Filter.Legs, false, ("Triggerbot"), ("FilterLegs"));

	//VISUALS
	SetupValue(g_Options.Visuals.Enabled, false, ("Visuals"), ("Enabled"));
	SetupValue(g_Options.Visuals.TeamESP, false, ("Visuals"), ("TeamESP"));
	SetupValue(g_Options.Visuals.Box, false, ("Visuals"), ("BoxEnabled"));
	SetupValue(g_Options.Visuals.BoxType, 0, ("Visuals"), ("BoxType"));
	SetupValue(g_Options.Visuals.fill, false, ("Visuals"), ("Box-Fill"));
	SetupValue(g_Options.Visuals.esp_fill_amount, 0.f, ("Visuals"), ("Fill-Amount"));
	SetupValue(g_Options.Visuals.health, false, ("Visuals"), ("Health"));
	SetupValue(g_Options.Visuals.healthtype, 0, ("Visuals"), ("HealthType"));
	SetupValue(g_Options.Visuals.armor, false, ("Visuals"), ("Armor"));
	SetupValue(g_Options.Visuals.Armor2, 0, ("Visuals"), ("ArmorType"));
	SetupValue(g_Options.Visuals.Money, false, ("Visuals"), ("Money"));
	SetupValue(g_Options.Visuals.Name, false, ("Visuals"), ("Name"));
	SetupValue(g_Options.Visuals.skeletonenbl, false, ("Visuals"), ("SkeletonEnabled"));
	SetupValue(g_Options.Visuals.skeletonopts, 0, ("Visuals"), ("SkeletonType"));
	SetupValue(g_Options.Visuals.Weapon, 0, ("Visuals"), ("Weapon"));
	SetupValue(g_Options.Visuals.AimLine, false, ("Visuals"), ("AimLine"));
	SetupValue(g_Options.Visuals.angleLines, false, ("Visuals"), ("AngleLines"));
	SetupValue(g_Options.Visuals.angleLinesName, false, ("Visuals"), ("AngleLinesName"));
	SetupValue(g_Options.Visuals.barrel, false, ("Visuals"), ("Barrel"));
	SetupValue(g_Options.Visuals.barrelL, 0, ("Visuals"), ("Barrel-Amount"));
	SetupValue(g_Options.Visuals.bulletshow, false, ("Visuals"), ("BulletImpacts"));
	SetupValue(g_Options.Visuals.flTracersDuration, 0.f, ("Visuals"), ("BulletImpact-Duration"));
	SetupValue(g_Options.Visuals.flTracersWidth, 0.f, ("Visuals"), ("BulletImpact-Width"));
	SetupValue(g_Options.Visuals.Hitbox, false, ("Visuals"), ("Hitbox"));
	SetupValue(g_Options.Visuals.HitboxDuration, 0.f, ("Visuals"), ("HitboxDuration"));
	SetupValue(g_Options.Visuals.viewmodelChanger, 0.f, ("Visuals"), ("Viewmodel-Amount"));
	SetupValue(g_Options.Visuals.C4World, false, ("Visuals"), ("Bomb"));
	SetupValue(g_Options.Visuals.DroppedGuns, false, ("Visuals"), ("DroppedGuns"));
	SetupValue(g_Options.Visuals.DroppedGunsType, 0, ("Visuals"), ("DroppedGunsType"));
	SetupValue(g_Options.Visuals.noscopeborder, false, ("Visuals"), ("Noscopeborder"));
	SetupValue(g_Options.Visuals.BombCarrier, false, ("Visuals"), ("BombCarrier"));
	SetupValue(g_Options.Visuals.AAIndicator, false, ("Visuals"), ("AA Indicator"));
	SetupValue(g_Options.Visuals.Hostage, false, ("Visuals"), ("Hostage"));
	SetupValue(g_Options.Visuals.Flashed, false, ("Visuals"), ("Flashed"));
	SetupValue(g_Options.Visuals.Distance, false, ("Visuals"), ("Distance"));
	SetupValue(g_Options.Visuals.Scoped, false, ("Visuals"), ("Scoped"));
	//	SetupValue(g_Options.Visuals.Reloading, false, ("Visuals"), ("Reloading"));
	SetupValue(g_Options.Visuals.Hostage, false, ("Visuals"), ("Hostage"));
	SetupValue(g_Options.Visuals.IsHasDefuser, false, ("Visuals"), ("HasDefuser"));
	SetupValue(g_Options.Visuals.IsDefusing, false, ("Visuals"), ("IsDefusing"));
	SetupValue(g_Options.Visuals.Grenades, 0, ("Visuals"), ("Grenades"));
	SetupValue(g_Options.Visuals.GrenadePrediction, false, ("Visuals"), ("GrenadePrediction"));
	SetupValue(g_Options.Visuals.GrenadeBox, false, ("Visuals"), ("GrenadeBox"));
	SetupValue(g_Options.Visuals.Chams, false, ("Visuals"), ("Chams-Enabled"));
	SetupValue(g_Options.Visuals.FakeAngleChams, false, ("Visuals"), ("FakeAngleChams"));
	SetupValue(g_Options.Visuals.matierial, 0, ("Visuals"), ("MaterialChams"));
	SetupValue(g_Options.Visuals.Teamchams, false, ("Visuals"), ("Teamchams"));
	SetupValue(g_Options.Visuals.champlayeralpha, 0, ("Visuals"), ("Chams-Alpha"));
	SetupValue(g_Options.Visuals.chamsHp, false, ("Visuals"), ("ChamsHp"));
	SetupValue(g_Options.Visuals.XQZ, false, ("Visuals"), ("XQZ"));
	SetupValue(g_Options.Visuals.Hands, 0, ("Visuals"), ("Hands"));
	SetupValue(g_Options.Visuals.HandsAlpha, 0, ("Visuals"), ("HandsAlpha"));
	SetupValue(g_Options.Visuals.chamswphands, 0, ("Visuals"), ("HeldWeaponCham"));
	SetupValue(g_Options.Visuals.chamswphandsalpha, 0, ("Visuals"), ("HeldWeaponChamAlpha"));
	SetupValue(g_Options.Visuals.SniperCrosshair, false, ("Visuals"), ("SniperCrosshair"));
	SetupValue(g_Options.Visuals.SniperCrosshairType, 0, ("Visuals"), ("SniperCrosshairType"));
	SetupValue(g_Options.Visuals.RecoilCrosshair, false, ("Visuals"), ("RecoilCrosshair"));
	SetupValue(g_Options.Visuals.RecoilCrosshair2, 0, ("Visuals"), ("RecoilCrosshair2"));
	SetupValue(g_Options.Visuals.AWallCrosshair, false, ("Visuals"), ("A-WallIndicator"));
	SetupValue(g_Options.Visuals.SpreadCrosshair, false, ("Visuals"), ("SpreadCrosshair"));
	SetupValue(g_Options.Visuals.spread_crosshair_amount, 110.f, ("Visuals"), ("Spread-Amount"));
	SetupValue(g_Options.Visuals.NoVisualRecoil, false, ("Visuals"), ("NoVisualRecoil"));
	SetupValue(g_Options.Visuals.NoFlash, false, ("Visuals"), ("NoFlash"));
	SetupValue(g_Options.Visuals.Smoke, 0, ("Visuals"), ("Smoke"));
	SetupValue(g_Options.Visuals.viewmodelChanger_enabled, false, ("Visuals"), ("ViewmodelEnabled"));
	SetupValue(g_Options.Visuals.FOVChanger_enabled, false, ("Visuals"), ("FovEnabled"));
	SetupValue(g_Options.Visuals.FOVChanger, 0.f, ("Visuals"), ("FOV-Amount"));
	SetupValue(g_Options.Visuals.viewmodelChanger, 0.f, ("Visuals"), ("Viewmodel-Amount"));



	SetupValue(g_Options.Visuals.nightMode, false, ("Visuals"), ("NightMode"));
	SetupValue(g_Options.Visuals.NoPostProcess, false, ("Visuals"), ("Postprocess"));
	SetupValue(g_Options.Visuals.snowmode, false, ("Visuals"), ("mat_drawgray"));
	SetupValue(g_Options.Visuals.lsdmode, false, ("Visuals"), ("mat_showmiplevels"));
	SetupValue(g_Options.Visuals.chromemode, false, ("Visuals"), ("ChromeMode"));
	SetupValue(g_Options.Visuals.wallalpha, 0.f, ("Visuals"), ("wallalpha"));
	SetupValue(g_Options.Visuals.propalpha, 0.f, ("Visuals"), ("propalpha"));
	SetupValue(g_Options.Visuals.modelalpha, 0.f, ("Visuals"), ("modelalpha"));
	SetupValue(g_Options.Visuals.minecraftmode, false, ("Visuals"), ("MinecraftMode"));
	SetupValue(g_Options.Visuals.TPKey, 0, ("Visuals"), ("TP-KEY"));
//	SetupValue(g_Options.Visuals.ThirdpersonMode, 0, ("Visuals"), ("TP-Mode"));
	SetupValue(g_Options.Visuals.Enabletp, false, ("Visuals"), ("TP-Enable"));
	SetupValue(g_Options.Visuals.transparency, false, ("Visuals"), ("TP-Transparency"));

	SetupValue(g_Options.Visuals.GlowPlayerEnable, false, ("Visuals"), ("Glow-Player"));
	SetupValue(g_Options.Visuals.GlowWeaponsEnable, false, ("Visuals"), ("Glow-Weapon"));
	SetupValue(g_Options.Visuals.WeaponsGlowAlpha, 0.f, ("Visuals"), ("GlowWeaponAlpha"));
	SetupValue(g_Options.Visuals.GlowC4Enable, false, ("Visuals"), ("Glow-C4"));
	SetupValue(g_Options.Visuals.C4GlowAlpha, 0.f, ("Visuals"), ("GlowC4-Alpha"));
	SetupValue(g_Options.Visuals.DamageIndicator, false, ("Visuals"), ("DamageIndicator"));

	SetupValue(g_Options.Visuals.LBYIndicator, false, ("Visuals"), ("LBYIndicator"));

	SetupValue(g_Options.Misc.syncclantag, false, ("Misc"), ("Sync-Clantag"));
	SetupValue(g_Options.Misc.namePrometheus, false, ("Misc"), ("namePrometheus"));
	SetupValue(g_Options.Misc.Bhop, false, ("Misc"), ("Bhop"));
	SetupValue(g_Options.Misc.AutoStrafe, 0, ("Misc"), ("Autostrafe"));
	SetupValue(g_Options.Misc.spammer, 0, ("Visuals"), ("Spammer"));
	SetupValue(g_Options.Misc.spammeron, false, ("Misc"), ("SpammerEnabled"));
	SetupValue(g_Options.Misc.SpecList, false, ("Misc"), ("SpecList"));
	SetupValue(g_Options.Misc.ServerRankRevealAll, false, ("Misc"), ("RankRevealAll"));
	SetupValue(g_Options.Misc.Watermark, false, ("Misc"), ("WaterMark"));
	SetupValue(g_Options.Misc.AutoAccept, false, ("Misc"), ("AutoAccept"));
	SetupValue(g_Options.Misc.Hitmarker, false, ("Misc"), ("Hitmarker"));
	SetupValue(g_Options.Misc.Hitsound, 0, ("Misc"), ("HitSound"));
	SetupValue(g_Options.Misc.eventlogs, false, ("Misc"), ("Log"));
	SetupValue(g_Options.Misc.eventlogs2, false, ("Misc"), ("Log2"));
	SetupValue(g_Options.Misc.afkbot, false, ("Misc"), ("AFK-BOT"));

	SetupValue(g_Options.Misc.inventoryalwayson, false, ("Misc"), ("EnableInventory"));

	SetupValue(g_Options.Misc.radaringame, false, ("Misc"), ("Radar-Minimap"));
	SetupValue(g_Options.Misc.radarwindow, false, ("Misc"), ("Radar-Window"));

	SetupValue(g_Options.Misc.radrzoom, false, ("Misc"), ("Radar-Zoom"));
	SetupValue(g_Options.Misc.radralpha, false, ("Misc"), ("Radar-Alpha"));
	SetupValue(g_Options.Misc.radrsize, false, ("Misc"), ("Radar-Zoom"));

	SetupValue(g_Options.Skinchanger.Enabled, false, ("skins"), ("enable"));
	SetupValue(g_Options.Skinchanger.gloveskin, 0, ("skins"), ("gloveskin"));
	SetupValue(g_Options.Skinchanger.glove, 0, ("skins"), ("glove"));
	SetupValue(g_Options.Skinchanger.knifemodel, 0, ("skins"), ("modelknife"));

	for (int id = 0; id < 65; id++) { // Weapons
		SetupValue(g_Options.Skinchanger.W[id].ChangerSkin, 0, GetWeaponName(id), ("Skin"));
	}

	for (int id = 500; id <= 516; id++) { // knifes

		if ((id < 505 && id >= 501) || (id > 512 && id < 514))
			continue;

		SetupValue(g_Options.Skinchanger.W[id].ChangerSkin, 0, GetWeaponName(id), ("Skin"));

	}


	//COLORS

	SetupValue(g_Options.Colors.TeamESP[0], 0.0f, "Colors", "TeamESP1");
	SetupValue(g_Options.Colors.TeamESP[1], 0.0f, "Colors", "TeamESP2");
	SetupValue(g_Options.Colors.TeamESP[2], 0.0f, "Colors", "TeamESP3");

	SetupValue(g_Options.Colors.EnemyESP[0], 0.0f, "Colors", "EnemyESP1");
	SetupValue(g_Options.Colors.EnemyESP[1], 0.0f, "Colors", "EnemyESP2");
	SetupValue(g_Options.Colors.EnemyESP[2], 0.0f, "Colors", "EnemyESP3");

	SetupValue(g_Options.Colors.EnemyChamsVis[0], 0.0f, "Colors", "EnemyChamsVis1");
	SetupValue(g_Options.Colors.EnemyChamsVis[1], 0.0f, "Colors", "EnemyChamsVis2");
	SetupValue(g_Options.Colors.EnemyChamsVis[2], 0.0f, "Colors", "EnemyChamsVis3");

	SetupValue(g_Options.Colors.EnemyChamsNVis[0], 0.0f, "Colors", "EnemyChamsNVis1");
	SetupValue(g_Options.Colors.EnemyChamsNVis[1], 0.0f, "Colors", "EnemyChamsNVis2");
	SetupValue(g_Options.Colors.EnemyChamsNVis[2], 0.0f, "Colors", "EnemyChamsNVis3");

	SetupValue(g_Options.Colors.TeamChamsVis[0], 0.0f, "Colors", "TeamChamsVis1");
	SetupValue(g_Options.Colors.TeamChamsVis[1], 0.0f, "Colors", "TeamChamsVis2");
	SetupValue(g_Options.Colors.TeamChamsVis[2], 0.0f, "Colors", "TeamChamsVis3");

	SetupValue(g_Options.Colors.TeamChamsNVis[0], 0.0f, "Colors", "TeamChamsNVi1");
	SetupValue(g_Options.Colors.TeamChamsNVis[1], 0.0f, "Colors", "TeamChamsNVi2");
	SetupValue(g_Options.Colors.TeamChamsNVis[2], 0.0f, "Colors", "TeamChamsNVi3");

	SetupValue(g_Options.Colors.hitmarker_color[0], 0.0f, "Colors", "hitmarker_color1");
	SetupValue(g_Options.Colors.hitmarker_color[1], 0.0f, "Colors", "hitmarker_color2");
	SetupValue(g_Options.Colors.hitmarker_color[2], 0.0f, "Colors", "hitmarker_color3");

	SetupValue(g_Options.Colors.backtrackdots_color[0], 0.0f, "Colors", "backtrackdots_color1");
	SetupValue(g_Options.Colors.backtrackdots_color[1], 0.0f, "Colors", "backtrackdots_color2");
	SetupValue(g_Options.Colors.backtrackdots_color[2], 0.0f, "Colors", "backtrackdots_color3");

	SetupValue(g_Options.Colors.hitbox[0], 0.0f, "Colors", "hitbox1");
	SetupValue(g_Options.Colors.hitbox[1], 0.0f, "Colors", "hitbox2");
	SetupValue(g_Options.Colors.hitbox[2], 0.0f, "Colors", "hitbox3");

	SetupValue(g_Options.Colors.dlight_color[0], 0.0f, "Colors", "dlight_color1");
	SetupValue(g_Options.Colors.dlight_color[1], 0.0f, "Colors", "dlight_color2");
	SetupValue(g_Options.Colors.dlight_color[2], 0.0f, "Colors", "dlight_color3");

	SetupValue(g_Options.Colors.color_skeleton[0], 0.0f, "Colors", "color_skeleton1");
	SetupValue(g_Options.Colors.color_skeleton[1], 0.0f, "Colors", "color_skeleton2");
	SetupValue(g_Options.Colors.color_skeleton[2], 0.0f, "Colors", "color_skeleton3");

	SetupValue(g_Options.Colors.color_grenadeprediction[0], 0.0f, "Colors", "color_grenadeprediction1");
	SetupValue(g_Options.Colors.color_grenadeprediction[1], 0.0f, "Colors", "color_grenadeprediction2");
	SetupValue(g_Options.Colors.color_grenadeprediction[2], 0.0f, "Colors", "color_grenadeprediction3");

	SetupValue(g_Options.Colors.color_grenadeprediction_circle[0], 0.0f, "Colors", "color_grenadeprediction_circle1");
	SetupValue(g_Options.Colors.color_grenadeprediction_circle[1], 0.0f, "Colors", "color_grenadeprediction_circle2");
	SetupValue(g_Options.Colors.color_grenadeprediction_circle[2], 0.0f, "Colors", "color_grenadeprediction_circle3");

	SetupValue(g_Options.Colors.GrenadeCollision[0], 0.0f, "Colors", "color_grenadeprediction_box1");
	SetupValue(g_Options.Colors.GrenadeCollision[1], 0.0f, "Colors", "color_grenadeprediction_box2");
	SetupValue(g_Options.Colors.GrenadeCollision[2], 0.0f, "Colors", "color_grenadeprediction_box3");

	SetupValue(g_Options.Colors.color_recoil[0], 0.0f, "Colors", "color_recoil1");
	SetupValue(g_Options.Colors.color_recoil[1], 0.0f, "Colors", "color_recoil2");
	SetupValue(g_Options.Colors.color_recoil[2], 0.0f, "Colors", "color_recoil3");

	SetupValue(g_Options.Colors.color_spread[0], 0.0f, "Colors", "color_spread1");
	SetupValue(g_Options.Colors.color_spread[1], 0.0f, "Colors", "color_spread2");
	SetupValue(g_Options.Colors.color_spread[2], 0.0f, "Colors", "color_spread3");

	SetupValue(g_Options.Colors.color_sniper[0], 0.0f, "Colors", "color_sniper1");
	SetupValue(g_Options.Colors.color_sniper[1], 0.0f, "Colors", "color_sniper2");
	SetupValue(g_Options.Colors.color_sniper[2], 0.0f, "Colors", "color_sniper3");

	SetupValue(g_Options.Colors.EnemyGlow[0], 0.0f, "Colors", "EnemyGlow1");
	SetupValue(g_Options.Colors.EnemyGlow[1], 0.0f, "Colors", "EnemyGlow2");
	SetupValue(g_Options.Colors.EnemyGlow[2], 0.0f, "Colors", "EnemyGlow3");

	SetupValue(g_Options.Colors.FakeAngleChams[0], 0.0f, "Colors", "FakeAngleChams1");
	SetupValue(g_Options.Colors.FakeAngleChams[1], 0.0f, "Colors", "FakeAngleChams2");
	SetupValue(g_Options.Colors.FakeAngleChams[2], 0.0f, "Colors", "FakeAngleChams3");

	SetupValue(g_Options.Colors.TeamGlow[0], 0.0f, "Colors", "TeamGlow1");
	SetupValue(g_Options.Colors.TeamGlow[1], 0.0f, "Colors", "TeamGlow2");
	SetupValue(g_Options.Colors.TeamGlow[2], 0.0f, "Colors", "TeamGlow3");

	SetupValue(g_Options.Colors.HandsColor[0], 0.0f, "Colors", "HandsColor1");
	SetupValue(g_Options.Colors.HandsColor[1], 0.0f, "Colors", "HandsColor2");
	SetupValue(g_Options.Colors.HandsColor[2], 0.0f, "Colors", "HandsColor3");

	SetupValue(g_Options.Colors.WeaponColor[0], 0.0f, "Colors", "WeaponColor1");
	SetupValue(g_Options.Colors.WeaponColor[1], 0.0f, "Colors", "WeaponColor2");
	SetupValue(g_Options.Colors.WeaponColor[2], 0.0f, "Colors", "WeaponColor3");

	SetupValue(g_Options.Colors.AimLineColor[0], 0.0f, "Colors", "AimLineColor1");
	SetupValue(g_Options.Colors.AimLineColor[1], 0.0f, "Colors", "AimLineColor2");
	SetupValue(g_Options.Colors.AimLineColor[2], 0.0f, "Colors", "AimLineColor3");

	SetupValue(g_Options.Colors.ScopeLine[0], 0.0f, "Colors", "ScopeLineColor1");
	SetupValue(g_Options.Colors.ScopeLine[1], 0.0f, "Colors", "ScopeLineColor2");
	SetupValue(g_Options.Colors.ScopeLine[2], 0.0f, "Colors", "ScopeLineColor3");

	SetupValue(g_Options.Colors.BulletTraceColor[0], 0.0f, "Colors", "BulletTraceColor1");
	SetupValue(g_Options.Colors.BulletTraceColor[1], 0.0f, "Colors", "BulletTraceColor2");
	SetupValue(g_Options.Colors.BulletTraceColor[2], 0.0f, "Colors", "BulletTraceColor3");

	SetupValue(g_Options.Colors.fill_color_enemy[0], 0.0f, "Colors", "fill_color_enemy1");
	SetupValue(g_Options.Colors.fill_color_enemy[1], 0.0f, "Colors", "fill_color_enemy2");
	SetupValue(g_Options.Colors.fill_color_enemy[2], 0.0f, "Colors", "fill_color_enemy3");

	SetupValue(g_Options.Colors.fill_color_team[0], 0.0f, "Colors", "fill_color_team1");
	SetupValue(g_Options.Colors.fill_color_team[1], 0.0f, "Colors", "fill_color_team2");
	SetupValue(g_Options.Colors.fill_color_team[2], 0.0f, "Colors", "fill_color_team3");

	SetupValue(g_Options.Colors.glow_weapon[0], 0.0f, "Colors", "glow_weapon1");
	SetupValue(g_Options.Colors.glow_weapon[1], 0.0f, "Colors", "glow_weapon2");
	SetupValue(g_Options.Colors.glow_weapon[2], 0.0f, "Colors", "glow_weapon3");

	SetupValue(g_Options.Colors.glow_c4[0], 0.0f, "Colors", "glow_c41");
	SetupValue(g_Options.Colors.glow_c4[1], 0.0f, "Colors", "glow_c42");
	SetupValue(g_Options.Colors.glow_c4[2], 0.0f, "Colors", "glow_c43");

	SetupValue(g_Options.Colors.damageindicator[0], 0.0f, "Colors", "damageindicator1");
	SetupValue(g_Options.Colors.damageindicator[1], 0.0f, "Colors", "damageindicator2");
	SetupValue(g_Options.Colors.damageindicator[2], 0.0f, "Colors", "damageindicator3");

	SetupValue(g_Options.Colors.droppedguns[0], 0.0f, "Colors", "droppedguns1");
	SetupValue(g_Options.Colors.droppedguns[1], 0.0f, "Colors", "droppedguns2");
	SetupValue(g_Options.Colors.droppedguns[2], 0.0f, "Colors", "droppedguns3");

	SetupValue(g_Options.Colors.flTracers[0], 0.0f, "Colors", "flTracers_1");
	SetupValue(g_Options.Colors.flTracers[1], 0.0f, "Colors", "flTracers_2");
	SetupValue(g_Options.Colors.flTracers[2], 0.0f, "Colors", "flTracers_3");

	SetupValue(g_Options.Colors.ambientlightcolor[0], 0.0f, "Colors", "ambientlightcolor_1");
	SetupValue(g_Options.Colors.ambientlightcolor[1], 0.0f, "Colors", "ambientlightcolor_2");
	SetupValue(g_Options.Colors.ambientlightcolor[2], 0.0f, "Colors", "ambientlightcolor_3");
}

void CConfig::SetupValue(int &value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue<int>(category, name, &value));
}

void CConfig::SetupValue(float &value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue<float>(category, name, &value));
}

void CConfig::SetupValue(bool &value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue<bool>(category, name, &value));
}



void CConfig::Save(char* name)
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;
	if (strlen(name) > 0)
	{
		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
		{
			folder = std::string(path) + ("\\Prometheus\\");
			file = std::string(path) + ("\\Prometheus\\") + std::string(name) + XorStr(".Prometheus");
		}
	}
	else
	{
		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
		{
			folder = std::string(path) + ("\\Prometheus\\");
			file = std::string(path) + ("\\Prometheus\\config.Prometheus");
		}
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::Load(char* name)
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;
	if (strlen(name) > 0)
	{
		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
		{
			folder = std::string(path) + ("\\Prometheus\\");
			file = std::string(path) + ("\\Prometheus\\") + std::string(name) + XorStr(".Prometheus");
		}
	}
	else
	{
		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
		{
			folder = std::string(path) + ("\\Prometheus\\");
			file = std::string(path) + ("\\Prometheus\\config.Prometheus");
		}
	}

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = (float)atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

CConfig* Config = new CConfig();
Variables g_Options;
