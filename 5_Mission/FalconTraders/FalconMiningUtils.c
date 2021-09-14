class FalconMiningUtils
{	
	const static string safeZonesDataPath = "$profile:/FValues/FTGoldZones.json";
	
	static ref array<ref MiningZone> getMiningZones() 
	{
		ref array<ref MiningZone> miningZones = new ref array<ref MiningZone>();
		
		JsonFileLoader<ref array<ref MiningZone>>.JsonLoadFile(safeZonesDataPath, miningZones);
		
		return miningZones;
	}
	
	static void initMiningZones()
	{
		array<vector> positions = new array<vector>();
		array<ref MiningZone> miningZones = new array<ref MiningZone>();
		vector zonePos;
		int zoneRadius;
		int rocks;
		
		float x;
		float y;
		float z;

		miningZones = getMiningZones();
		
		for (int i = 0; i < miningZones.Count(); i++)
		{
			zonePos = miningZones[i].getZonePos().ToVector();
			zoneRadius = miningZones[i].getZoneRadius();
			
			rocks = Math.RandomInt(GoldMiningConsts.MIN_GOLD_ROCKS_PER_ZONE, GoldMiningConsts.MAX_GOLD_ROCKS_PER_ZONE);
			
			for (int j = 0; j < rocks; j++)
			{
				x = Math.RandomInt(zonePos[0] - zoneRadius, zonePos[0] + zoneRadius);
				z = Math.RandomInt(zonePos[2] - zoneRadius, zonePos[2] + zoneRadius);
				
				y = GetGame().SurfaceY(x, z);
				
				positions.Insert(Vector(x, y, z));
				
				//Print("Position: " + Vector(x, y, z).ToString());
			}
			
			//Print("Positions Count " + positions.Count().ToString());
		}
		
		for (int k = 0; k < positions.Count(); k++)
		{
			GetGame().CreateObject("GoldRock", positions[k], false, false, false);
		}
	}
}