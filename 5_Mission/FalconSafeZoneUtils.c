class FalconSafeZoneUtils
{
	static vector safeZonePos = Vector(9997, 10, 1663);
	static int safeZoneRadius = 20;
	//static ref array<FalconSafeZone> safeZones = new array<FalconSafeZone>();
	
	static ref FalconSafeZoneHelpers SafeZoneHelpers = new FalconSafeZoneHelpers();
	
	
	static ref array<ref FalconSafeZone> getSafeZones() {
		string safeZonesDataPath = "$profile:/FValues/FSafeZones.json";;
		
		ref array<ref FalconSafeZone> safeZones = new ref array<ref FalconSafeZone>();
		
		JsonFileLoader<ref array<ref FalconSafeZone>>.JsonLoadFile(safeZonesDataPath, safeZones);
		
		return safeZones;
	}
	
	static void checkPlayersInSafezone(array<Man> players) {
		float playerSafeZoneDistance;
		
		PlayerBase playerInSafeZone;
		string playerID;
		
		array<ref FalconSafeZone> safeZones = FalconSafeZoneUtils.getSafeZones();
		
		foreach (Man player : players)
		{
			foreach (FalconSafeZone safeZone : safeZones)
			{
				Print(safeZone.getSafeZoneName());
				
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
}