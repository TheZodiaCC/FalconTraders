class FalconSafeZoneUtils
{	
	static ref FalconSafeZoneHelpers SafeZoneHelpers = new FalconSafeZoneHelpers();
	
	
	static ref array<ref FalconSafeZone> getSafeZones() {
		string safeZonesDataPath = "$profile:/FValues/FSafeZones.json";;
		
		ref array<ref FalconSafeZone> safeZones = new ref array<ref FalconSafeZone>();
		
		JsonFileLoader<ref array<ref FalconSafeZone>>.JsonLoadFile(safeZonesDataPath, safeZones);
		
		return safeZones;
	}
	
	static void checkPlayersInSafezone(array<Man> players, array<ref FalconSafeZone> safeZones) {
		float playerSafeZoneDistance;
		
		PlayerBase playerInSafeZone;
		string playerID;
		
		
		foreach (Man player : players)
		{
			foreach (FalconSafeZone safeZone : safeZones)
			{
				playerSafeZoneDistance = vector.Distance(safeZone.getSafeZonePos().ToVector(), player.GetPosition());
			
				if (playerSafeZoneDistance <= safeZone.getSafeZoneRadius()) 
				{
					playerInSafeZone = PlayerBase.Cast(player);
					playerID = playerInSafeZone.GetIdentity().GetId();
					
					playerInSafeZone.setIsInSafeZone(true);
					playerInSafeZone.setHasGM(true);
					
					SafeZoneHelpers.turnOnMarks(playerID);
				}
				else
				{
					playerInSafeZone = PlayerBase.Cast(player);
					playerID = playerInSafeZone.GetIdentity().GetId();
					
					playerInSafeZone.setIsInSafeZone(false);
					playerInSafeZone.setHasGM(false);
					
					SafeZoneHelpers.turnOffMarks(playerID);
				}
			}
		}
	}
	
	static void initSafezones() {
		
	}
}