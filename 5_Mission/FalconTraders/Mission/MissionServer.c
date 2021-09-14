modded class MissionServer
{
	private ref array<Man> players = new array<Man>;
	private int updateTick = 5;
	private int currentTime;
	private int nTime = 0;
	
	private ref array<ref FalconSafeZone> safeZones = new ref array<ref FalconSafeZone>();
	
	ref TraderMenuBack traderMenuBack;
	
	
	void MissionServer()
	{
		safeZones = FalconSafeZoneUtils.getSafeZones();
		
		traderMenuBack = new TraderMenuBack();
	}
	
	override void OnInit()
	{
		super.OnInit();
	}
	
	override void OnMissionLoaded()
	{
		super.OnMissionLoaded();
		
		FalconSafeZoneUtils.clearSafeZones(safeZones);
		FalconSafeZoneUtils.initSafezones();
		FalconMiningUtils.initMiningZones();
	}
	
	override void TickScheduler( float timeslice )
	{	
		super.TickScheduler( timeslice );
		
		currentTime = GetGame().GetTime() * 0.001;
		
		if(currentTime >= nTime + updateTick)
		{
			GetGame().GetPlayers(players);
			
			FalconSafeZoneUtils.checkPlayersInSafezone(players, safeZones);
			FalconSafeZoneUtils.clearZombies(safeZones);
			
			nTime = currentTime;
		}
	}
}