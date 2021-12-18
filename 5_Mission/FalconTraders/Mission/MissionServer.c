modded class MissionServer
{
	private ref array<Man> players = new array<Man>;
	private int tradersUpdateTick = 5;
	private int tradersCurrentTime;
	private int tradersNTime = 0;
	
	private ref array<ref FalconSafeZone> safeZones = new ref array<ref FalconSafeZone>();
	
	ref TraderMenuBack traderMenuBack;
	ref ATMMenuBack atmMenuBack;
	
	
	void MissionServer()
	{
		safeZones = FalconSafeZoneUtils.getSafeZones();
		
		traderMenuBack = new TraderMenuBack();
		atmMenuBack = new ATMMenuBack();
	}
	
	override void OnInit()
	{
		super.OnInit();
		
		FalconSafeZoneUtils.clearSafeZones(safeZones);
		FalconSafeZoneUtils.initSafezones();
		FalconMiningUtils.initMiningZones();
		FalconATMUtils.initATMs();
	}
	
	override void OnMissionLoaded()
	{
		super.OnMissionLoaded();
		
		// Moved to OnInit() to avoid the same bug as encountered in FalconCouriers

		//FalconSafeZoneUtils.clearSafeZones(safeZones);
		//FalconSafeZoneUtils.initSafezones();
		//FalconMiningUtils.initMiningZones();
		//FalconATMUtils.initATMs();
	}
	
	override void TickScheduler( float timeslice )
	{	
		super.TickScheduler( timeslice );
		
		tradersCurrentTime = GetGame().GetTime() * 0.001;
		
		if(tradersCurrentTime >= tradersNTime + tradersUpdateTick)
		{
			GetGame().GetPlayers(players);
			
			FalconSafeZoneUtils.checkPlayersInSafezone(players, safeZones);
			FalconSafeZoneUtils.clearZombies(safeZones);
			
			tradersNTime = tradersCurrentTime;
		}
	}
}