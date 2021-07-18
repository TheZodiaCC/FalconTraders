class CfgPatches
{
	class FalconTraders
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"DZ_Data", "JM_CF_Scripts"};
	};
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
	    author = "zNitche";
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