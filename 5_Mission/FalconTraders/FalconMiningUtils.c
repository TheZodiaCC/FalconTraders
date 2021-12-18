class FalconMiningUtils
{	
	const static string goldMiningZonesData = TradersConsts.GOLD_MINING_ZONES_DATA_PATH;
	
	static ref array<ref MiningZone> getMiningZones(string dataPath) 
	{
		ref array<ref MiningZone> miningZones = new ref array<ref MiningZone>();
		
		JsonFileLoader<ref array<ref MiningZone>>.JsonLoadFile(dataPath, miningZones);
		
		return miningZones;
	}
	
	static void initMiningZones()
	{
		spawnRocks(getMiningZones(goldMiningZonesData));
	}
	
	static void spawnRocks(array<ref MiningZone> miningZones)
	{
		array<vector> positions = new array<vector>();
		vector zonePos;
		int zoneRadius;
		int rocks;
		
		float x;
		float y;
		float z;
		
		Object rock;
		
		for (int i = 0; i < miningZones.Count(); i++)
		{
			zonePos = miningZones[i].getZonePos().ToVector();
			zoneRadius = miningZones[i].getZoneRadius();
			
			rocks = Math.RandomInt(MiningConsts.MIN_GOLD_ROCKS_PER_ZONE, MiningConsts.MAX_GOLD_ROCKS_PER_ZONE);
			
			for (int j = 0; j < rocks; j++)
			{
				x = Math.RandomInt(zonePos[0] - zoneRadius, zonePos[0] + zoneRadius);
				z = Math.RandomInt(zonePos[2] - zoneRadius, zonePos[2] + zoneRadius);
				
				y = GetGame().SurfaceY(x, z);
				
				positions.Insert(Vector(x, y, z));
			}
		}
		
		for (int k = 0; k < positions.Count(); k++)
		{
			rock = GetGame().CreateObject(MiningConsts.GOLD_ROCK_ITEM, positions[k], false, false, false);
			
			rock.PlaceOnSurface();
		}
	}
}