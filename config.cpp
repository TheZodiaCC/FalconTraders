class CfgPatches
{
	class FalconTraders
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"DZ_Data", "JM_CF_Scripts"};
	};

	class Goldbar
	{
		units[]={
			"Goldbar"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Gear_Crafting"
		};
	}

	class Goldcoin
	{
		units[]={
			"Goldcoin"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Gear_Crafting"
		};
	}

	class GoldNugget
	{
		units[]={
			"GoldNugget"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Gear_Crafting"
		};
	}
};

class CfgMods
{
	class FalconTraders
	{
	    dir = FalconTraders
	    picture = "";
	    action = "";
	    hideName = 1;
	    hidePicture = 1;
	    name = FalconTraders
	    credits = "";
	    author = "";
	    authorID = "0";
	    version = "1.0";
	    extra = 0;
	    type = "mod";

	    dependencies[] = { "World", "Mission" };

		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"FalconTraders/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"FalconTraders/5_Mission"};
			};
		};
	};
};

class CfgSlots
{
	class GoldNuggetSlot
	{
		name = "GoldNuggetSlot";
		displayName = "Gold Nugget";
		ghostIcon = "";
		stackMax = 10;
	};
};


class CfgVehicles
{
	class SurvivorMale_Base;
	class FalconTraderTaki: SurvivorMale_Base
	{
		scope = 2;
		emptyHead = "MaleTaikiHead";
		emptyBody = "MaleTaikiTorso";
		emptyLegs = "MaleTaikiLegs";
		emptyFeet = "MaleTaikiFeet";
		emptyGloves = "MaleTaikiHands";
		faceType = "MaleTaikiHead";
		decayedTexture = "\DZ\characters\heads\data\m_Taiki\hhl_m_Taiki_body_shaved_decayed_co.paa";
		class BloodyHands
		{
			mat_normal = "dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved.rvmat";
			mat_blood = "dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bloodyhands.rvmat";
		};
		class Lifespan
		{
			class Beard
			{
				mat[] = {"dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved_co.paa","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved_co.paa","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded_co.paa","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_beard_ca.paa","dz\characters\heads\data\m_taiki\hhl_m_taiki_beard.rvmat"};
			};
		};
		class Wounds
		{
			tex[] = {};
			mat[] = {"dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved_injury.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved_injury2.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved_injury.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved_injury2.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded_injury.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded_injury2.rvmat"};
		};
		voiceType = 2;
	};

	class FalconTraderHassan: SurvivorMale_Base
	{
		scope = 2;
		emptyHead = "MaleHassanHead";
		emptyBody = "MaleHassanTorso";
		emptyLegs = "MaleHassanLegs";
		emptyFeet = "MaleHassanFeet";
		emptyGloves = "MaleHassanHands";
		faceType = "MaleHassanHead";
		decayedTexture = "\DZ\characters\heads\data\m_Hassan\hhl_m_Hassan_body_shaved_decayed_co.paa";
		class BloodyHands
		{
			mat_normal = "dz\characters\heads\data\m_hassan\hhl_m_hassan_body_shaved.rvmat";
			mat_blood = "dz\characters\heads\data\m_hassan\hhl_m_hassan_body_bloodyhands.rvmat";
		};
		class Lifespan
		{
			class Beard
			{
				mat[] = {"dz\characters\heads\data\m_hassan\hhl_m_hassan_body_shaved_co.paa","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_shaved.rvmat","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_unshaved_co.paa","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_unshaved.rvmat","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_bearded_co.paa","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_bearded.rvmat","dz\characters\heads\data\m_hassan\hhl_m_hassan_beard_ca.paa","dz\characters\heads\data\m_hassan\hhl_m_hassan_beard.rvmat"};
			};
		};
		class Wounds
		{
			tex[] = {};
			mat[] = {"dz\characters\heads\data\m_hassan\hhl_m_hassan_body_shaved.rvmat","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_shaved_injury.rvmat","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_shaved_injury2.rvmat","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_unshaved.rvmat","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_unshaved_injury.rvmat","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_unshaved_injury2.rvmat","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_bearded.rvmat","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_bearded_injury.rvmat","dz\characters\heads\data\m_hassan\hhl_m_hassan_body_bearded_injury2.rvmat"};
		};
		voiceType = 1;
	};

	class Inventory_Base;

	class GoldFrame: Inventory_Base
	{
		scope = 2;
		displayName = "Gold Frame";
		descriptionShort = "Gold Frame";
		model="FalconTraders\Items\goldbar\gold_bar.p3d";
		rotationFlags=90;
		itemSize[] = {4,2};
		weight = 400;
		fragility=0.000001;
		attachments[]={"GoldNuggetSlot"};

		class Cargo
		{
			itemsCargoSize[] = {0,0};
		};
		class GUIInventoryAttachmentsProps
		{
			class BaseBuildingAttachments
			{
				name = "Gold Nuggets";
				description = "";
				icon = "";
				attachmentSlots[] = {"GoldNuggetSlot"};
			};
		};
	};

	class FalconATM: Inventory_Base
	{
		scope=1;
		displayName="ATM";
		descriptionShort="";
		model="FalconTraders\Items\goldnode\goldnode.p3d";
		rotationFlags=0;
		weight=5000;
		itemSize[]={15,15};
		fragility=0.00000001;
		canBeDigged = 0;
		heavyItem = 1;
		itemBehaviour = 0;
		placement = "ForceSlopeOnTerrain";
		physLayer = "item_large";
	};

	class Goldbar: Inventory_Base
	{
		scope=2;
		displayName="Gold Bar";
		descriptionShort="A shiny gold bar. Very Heavy.";
		model="FalconTraders\Items\goldbar\gold_bar.p3d";
		rotationFlags=0;
		weight=5000;
		itemSize[]={3,2};
		fragility=0.00000001;
	};

	class Goldcoin: Inventory_Base
	{
		scope=2;
		displayName="Gold Coin";
		descriptionShort="A shiny gold coin. Used as currency.";
		model="FalconTraders\Items\goldcoin\gold_coin.p3d";
		rotationFlags=0;
		canBeSplit = 1;
		varQuantityInit = 100.0;
		varQuantityMin = 0.0;
		varQuantityMax = 100.0;
		weight=100;
		itemSize[]={1,1};
		fragility=0.00000001;
	};

	class GoldNugget: Inventory_Base
	{
		scope=2;
		displayName="Gold Nugget";
		descriptionShort="Golden Nugget. Can be smelted.";
		model="FalconTraders\Items\goldnugget\goldnugget.p3d";
		rotationFlags=0;
		canBeSplit = 1;
		varQuantityInit = 1.0;
		varQuantityMin = 0.0;
		varQuantityMax = 10.0;
		weight=1500;
		itemSize[]={2,2};
		fragility=0.00000001;
		inventorySlot[] = {"GoldNuggetSlot"};
	}

	class GoldRock: Inventory_Base
	{
		scope=1;
		displayName="Gold Node";
		descriptionShort="";
		model="FalconTraders\Items\goldnode\goldnode.p3d";
		rotationFlags=0;
		weight=5000;
		itemSize[]={15,15};
		fragility=0.00000001;
		canBeDigged = 0;
		heavyItem = 1;
		itemBehaviour = 0;
		placement = "ForceSlopeOnTerrain";
		physLayer = "item_large";

		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 999999;
				};
			};
		};
	};
};
