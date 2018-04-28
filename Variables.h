#pragma once
#include <set>
#include <map>
#include <unordered_map>


struct skinInfo
{
	int seed = -1;
	int paintkit;
	std::string tagName;
};


//Color Feature for Color Changer
struct ColorP
{
public:
	const char* Name;
	float* Ccolor;

	ColorP(const char* name, float* color)
	{
		this->Name = name;
		this->Ccolor = color;
	}
};

struct Variables
{
	Variables()
	{

	}

	struct Ragebot_s
	{
		bool	MainSwitch;
		bool 	Enabled;
		bool 	AutoFire;
		float 	FOV;
		bool 	Silent;
		bool	AutoPistol;
		int		KeyPress;
		bool	AimStep;

		//AA Builder 
		//THESE NOW BECOME WHAT I WILL SET DEPENDING ON THE MVOEMENT TYPE EXACMPLE: IF WERE WALKING { JITTER = WALK_JITTER; } //LESS CODE!
		bool	BuilderAAs;
		bool	Jitter;
		bool	FJitter;
		bool	LBYBreaker;
		float	BuilderReal;
		float	BuilderFake;
		float	BuilderPitch;
		float	JitterRange;
		float	FJitterRange;


		//walking builder aa's
		bool	walk_BuilderAAs;
		bool	walk_Jitter;
		bool	walk_FJitter;
		bool	walk_LBYBreaker;
		float	walk_BuilderReal;
		float	walk_BuilderFake;
		float	walk_BuilderPitch;
		float	walk_JitterRange;
		float	walk_FJitterRange;

		//running builder aa's
		bool	run_BuilderAAs;
		bool	run_Jitter;
		bool	run_FJitter;
		bool	run_LBYBreaker;
		float	run_BuilderReal;
		float	run_BuilderFake;
		float	run_BuilderPitch;
		float	run_JitterRange;
		float	run_FJitterRange;


		//crouching builder aa's
		bool	crouch_BuilderAAs;
		bool	crouch_Jitter;
		bool	crouch_FJitter;
		bool	crouch_LBYBreaker;
		float	crouch_BuilderReal;
		float	crouch_BuilderFake;
		float	crouch_BuilderPitch;
		float	crouch_JitterRange;
		float	crouch_FJitterRange;


		//fakewalk builder aa's
		bool	fwalk_BuilderAAs;
		bool	fwalk_Jitter;
		bool	fwalk_FJitter;
		bool	fwalk_LBYBreaker;
		float	fwalk_BuilderReal;
		float	fwalk_BuilderFake;
		float	fwalk_BuilderPitch;
		float	fwalk_JitterRange;
		float	fwalk_FJitterRange;


		//standing builder aa's
		bool	stand_BuilderAAs;
		bool	stand_Jitter;
		bool	stand_FJitter;
		bool	stand_LBYBreaker;
		float	stand_BuilderReal;
		float	stand_BuilderFake;
		float	stand_BuilderPitch;
		float	stand_JitterRange;
		float	stand_FJitterRange;


		int flip_aa;

		bool ayywarecrasher = false;

		bool	EnabledAntiAim;
		int		SubAATabs;
		bool	PreAAs;
		int		Pitch;
		int		YawTrue;
		int		YawFake;
		int		YawTrueMove;
		float	PitchAdder;
		float	YawTrueAdder;
		float	YawFakeAdder;
		float	YawFakeMove;
		bool	AtTarget;
		bool	Edge;
		bool	KnifeAA;
		bool	FakeLag;
		int		FakeLagAmt;
		int		FakeLagMode;

		// Pitch  PitchAdder  YawTrue  YawFakeAdder  YawFake  YawFakeAdder

		//walking prebuilt aa
		bool	walk_PreAAs;
		int		walk_Pitch;
		float	walk_PitchAdder;
		int		walk_YawTrue;
		float	walk_YawTrueAdder;
		int		walk_YawFake;
		float	walk_YawFakeAdder;


		//running prebuilt aa
		bool	run_PreAAs;
		int		run_Pitch;
		float	run_PitchAdder;
		int		run_YawTrue;
		float	run_YawTrueAdder;
		int		run_YawFake;
		float	run_YawFakeAdder;


		//crouching prebuilt aa
		bool	crouch_PreAAs;
		int		crouch_Pitch;
		float	crouch_PitchAdder;
		int		crouch_YawTrue;
		float	crouch_YawTrueAdder;
		int		crouch_YawFake;
		float	crouch_YawFakeAdder;


		//fakewalk prebuilt aa fwalk
		bool	fwalk_PreAAs;
		int		fwalk_Pitch;
		float	fwalk_PitchAdder;
		int		fwalk_YawTrue;
		float	fwalk_YawTrueAdder;
		int		fwalk_YawFake;
		float	fwalk_YawFakeAdder;


		//standing prebuilt aa's 
		bool	stand_PreAAs;
		int		stand_Pitch;
		float	stand_PitchAdder;
		int		stand_YawTrue;
		float	stand_YawTrueAdder;
		int		stand_YawFake;
		float	stand_YawFakeAdder;


		bool stand_allowflip;
		bool fwalk_allowflip;
		bool crouch_allowflip;
		bool walk_allowflip;
		bool run_allowflip;

		int flipkey;

		int error_type;  //aa warning variable

		bool	FriendlyFire;
		int		Hitbox;
		int		Hitscan;
		float	Pointscale;
		bool	Multipoint;
		float	Multipoints;

		bool	AntiRecoil;
		bool	AutoWall;
		int 	AutoStop;
		bool	AutoCrouch;
		bool	AutoScope;
		float	MinimumDamageSniper;
		float	MinimumDamageRifle;
		float	MinimumDamagePistol;
		float	MinimumDamageHeavy;
		float	MinimumDamageSmg;
		float	MinimumDamageRevolver;
		bool	Hitchance;
		float	HitchanceSniper;
		float	HitchancePistol;
		float	HitchanceRifle;
		float	HitchanceHeavy;
		float	HitchanceSmgs;
		float	HitchanceRevolver;
		int		Resolver;
		bool	FakeLagFix;
		bool	PosAdjust;
		bool	playerlist;
		int		BAIMkey;
		float	bruteAfterX;


		bool	AA_onRun;
		bool	AA_onWalk;
		bool	AA_onCrouch;
		bool	AA_onFakeWalk;
		bool	AA_onStand;

		bool fakewalk;
		int fakewalkkey;

		bool BAIMIfLethal;

	} Ragebot;

	

	struct
	{
		bool Enable;

		bool AutoPistol;

		int MainKey = 1;
		float MainSmooth = 1;
		float Mainfov;
		float main_random_smooth;
		float main_recoil_min;
		float main_recoil_max;
		float main_randomized_angle;



		int PistolKey = 6;
		float Pistolfov;
		float PistolSmooth = 1;;
		float pistol_random_smooth;
		float pistol_recoil_min;
		float pistol_recoil_max;
		float pistol_randomized_angle;



		int SniperKey = 6;
		float Sniperfov;
		float SniperSmooth = 1;
		float sniper_random_smooth;
		float sniper_recoil_min;
		float sniper_recoil_max;
		float sniper_randomized_angle;


		int smg_Key = 6;
		float smg_fov;
		float smg_Smooth = 1;
		float smg_random_smooth;
		float smg_recoil_min;
		float smg_recoil_max;
		float smg_randomized_angle;

		int heavy_wp_Key = 6;
		float heavy_wp_fov;
		float heavy_wp_Smooth;
		float heavy_wp_random_smooth;
		float heavy_wp_recoil_min;
		float heavy_wp_recoil_max;
		float heavy_wp_randomized_angle;

		struct
		{
			bool Headwpmain;
			bool Neckwpmain;
			bool Chestwpmain;
			bool Stomachwpmain;
			bool multiboneswpmain;
		}FilterMainWeapons;

		struct
		{
			bool Headwppis;
			bool Neckwppis;
			bool Chestwppis;
			bool Stomachwppis;
			bool multiboneswppis;
		}FilterPistolWeapons;


		struct
		{
			bool HeadwpSnip;
			bool NeckwpSnip;
			bool ChestwpSnip;
			bool StomachwpSnip;
			bool multiboneswpSnip;

		}FilterSniperWeapons;


		struct
		{
			bool Headwpsmg;
			bool Neckwpsmg;
			bool Chestwpsmg;
			bool Stomachwpsmg;
			bool multiboneswpsmg;

		}FiltersmgWeapons;


		struct
		{
			bool Headwphv;
			bool Neckwphv;
			bool Chestwphv;
			bool Stomachwphv;
			bool multibonewphv;

		}FilterheavyWeapons;


		struct
		{
			bool Enabled;
			float Delay;
			int Key = 6;
			float hitchance;
			struct
			{
				bool Head;
				bool Arms;
				bool Chest;
				bool Stomach;
				bool Legs;
			} Filter;

		} Triggerbot;


	}LegitBot;

	struct
	{
		bool backtrackenable;
		int BacktrackType;
		int  backtrackticks = 1;


	}Backtrack;





	struct
	{
		bool Enabled;
		bool StreamProof;


		bool TeamESP;
		bool Box;
		int BoxType;
		bool fill;
		float esp_fill_amount;
		float spread_crosshair_amount = 110;
		int healthtype;
		bool health;
		bool armor;
		int Armor2;

		bool Money;
		bool Name;
		bool skeletonenbl;
		int skeletonopts;
		int Weapon;
		bool AimLine;
		bool angleLines;
		bool angleLinesName;
		bool barrel;
		int barrelL;
		bool DrawAwall;
		bool LBYIndicator;
		bool RageDraw;
		bool C4World;
		bool resolveMode;
		int DroppedGunsType;
		bool DroppedGuns;
		bool noscopeborder;

		bool AmmoBox;


         //Info Enemy
		bool BombCarrier;
		bool Flashed;
		bool Distance;
		bool Scoped;
		bool IsHasDefuser;
		bool IsDefusing;

		//GRENADE
		int Grenades;
		bool GrenadePrediction;
		bool GrenadeBox;




		//CHAMS
		bool Chams;
		int matierial;
		bool Teamchams;
		int champlayeralpha = 100;
		bool chamsHp;
		bool XQZ;
		int Hands;
		int HandsAlpha = 100;
		int chamswphands;
		int chamswphandsalpha = 100;
		bool FakeAngleChams;
		bool LocalChams;

		//CROSSHAIR
		bool RecoilCrosshair;
		int RecoilCrosshair2;
		bool SpreadCrosshair;
		bool SniperCrosshair;
		int SniperCrosshairType;
		bool AWallCrosshair;

	

		//REMOVERS
		bool NoVisualRecoil;
		bool NoFlash;
		int Smoke;
		bool NoPostProcess;


		//VIEWMODEL CHANGERS
		bool viewmodelChanger_enabled;
		bool FOVChanger_enabled;
		float FOVChanger;
		float viewmodelChanger = 68;

		//WORLD
		bool nightMode;
		bool snowmode;
		bool lsdmode;
		bool chromemode;
		float wallalpha = 1.f;
		float propalpha = 1.f;
		float modelalpha = 1.f;
		bool minecraftmode;
		bool ambientlight;
		int SkyboxChanger;
		bool OffscreenIndicator;
		int OffscreenIndicatorSize = 7;
		bool Hostage;
		bool HostageBox;
		bool Chicken;
		bool ChickenBox;

		bool WeaponBox;

		//ThirdPerson
		int TPKey;
		bool transparency;
		bool Enabletp;
		bool GrenadeCheck;
		int ThirdpersonMode;

		//GLOW
		bool GlowEnable;
		bool GlowPlayerEnable;
		bool GlowEnemy;
		bool GlowTeam;
		float EnemyAlpha = 255;
		float TeamAlpha = 255;
		bool GlowWeaponsEnable;
		bool GlowC4Enable;
		float C4GlowAlpha = 255;
		float WeaponsGlowAlpha = 255;

		//OTHERS
	    bool DamageIndicator;
		bool bulletshow;
		float flTracersDuration;
		float flTracersWidth;

		bool Hitbox;
		float HitboxDuration;
		

		bool AAIndicator;

	} Visuals;
	struct
	{
		bool antiuntrusted = true;
		bool syncclantag;
		bool namePrometheus;
		bool Bhop;
		int spammer;
		bool spammeron;
		int AutoStrafe;
		bool SpecList;
		bool ServerRankRevealAll;
		bool Watermark = true;
		bool AutoAccept;
		bool Hitmarker;
		int Hitsound = 0;
		bool afkbot;
		bool inventoryalwayson;
		bool eventlogs;
		bool eventlogs2;
		bool radaringame;
		bool radarwindow;
		int radrsize = 200;
		float radralpha = 1.f;
		float radrzoom = 2.f;
	} Misc;
	struct
	{
		bool Enabled;
		int knifemodel;
		int glove;
		int gloveskin;

		struct
		{
			bool ChangerEnabled = false;
			int ChangerSkin = 0;
		} W[519]; // CHANGE HERE
		bool SkinFilter;
		std::unordered_map<std::string, std::set<std::string>> weaponSkins;
		std::unordered_map<std::string, skinInfo> skinMap;
		std::unordered_map<std::string, std::string> skinNames;
		std::vector<std::string> weaponNames;
	} Skinchanger;

	struct
	{
		bool Opened = false;
		int 	Key;
		int		ConfigFile = 0;
		int		Theme = 0;
		int currentWeapon;
	} Menu;

	struct
	{//need more
		float TeamESP[3] = { 0, 1.f, 0 };
		float EnemyESP[3] = { 1.f, 0, 0 };
		float EnemyChamsVis[3] = { 1.f, 0, 0 };
		float EnemyChamsNVis[3] = { 1.f, 0, 0 };
		float TeamChamsVis[3] = { 0, 1.f, 0 };
		float TeamChamsNVis[3] = { 0, 1.f, 0 };
		float PlayerChamsVis[3] = { 1.f, 1.f, 1.f };
		float PlayerChamsNVis[3] = { 0, 1.f, 1.f };
		float hitmarker_color[3] = { 1.f, 1.f, 1.f };
		float backtrackdots_color[3] = { 1.f, 1.f, 1.f };
		float dlight_color[3] = { 1.f, 1.f, 1.f };
		float color_skeleton[3] = { 1.f, 1.f, 1.f };
		float color_grenadeprediction[3] = { 1.f, 1.f, 1.f };
		float color_grenadeprediction_circle[3] = { 1.f, 1.f, 1.f };
		float GrenadeCollision[3] = { 1.f,0.f,0.f };
		float color_recoil[3] = { 1.f, 1.f, 1.f };
		float color_spread[3] = { 1.f, 1.f, 1.f };
		float color_sniper[3] = { 1.f, 1.f, 1.f };
		float EnemyGlow[3] = { 1.f, 1.f, 1.f };
		float TeamGlow[3] = { 1.f, 1.f, 1.f };
		float OtherGlow[3] = { 1.f, 1.f, 1.f };
		float HandsColor[3] = { 1.f, 1.f, 1.f };
		float AimLineColor[3] = { 1.f, 1.f, 1.f };
		float BulletTraceColor[3] = { 1.f, 1.f, 1.f };
		float fill_color_enemy[3] = { 1.f, 1.f, 0.0f};
		float fill_color_team[3] = { 0.f, 0.2f, 1.f};
		float glow_weapon[3] = { 1.f, 1.f, 1.f };
		float glow_c4[3] = { 1.f, 1.f, 1.f };
    	float damageindicator[3] = { 1.f,1.f,1.f };
		float WeaponColor[3] = { 1.f, 1.f, 1.f };
		float droppedguns [3] = { 1.f,1.f,1.f };
		float ScopeLine[3] = { 0.f,0.f,0.f };
		float flTracers[3] = { 1.f, 0.f, 0.f };
		float ambientlightcolor[3];
		float Offscreen[3] = { 1.f, 0.f, 0.f };
		float hitbox[3] = { 1.f, 0.f, 0.f };
		float FakeAngleChams[3] = { 1.f, 1.f, 1.f };
	}Colors;
};

extern Variables g_Options;