class FalconSafeZoneHelpers
{	
	void FalconSafeZoneHelpers()
	{
		GetRPCManager().AddRPC( "Falcon", "turnOnSZMarkC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "Falcon", "turnOffSZMarkC", this, SingeplayerExecutionType.Server );
	}
	
	private void turnOnSZMarkC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Client ) {
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			
			if (data.param1 == player.GetIdentity().GetId()) 
			{
				player.setIsInSafeZone(true);
			}
        }
    }
	
	void turnOnMarks(string playerID) {
		GetRPCManager().SendRPC( "Falcon", "turnOnSZMarkC", new Param1<string>(playerID) );
	}
	
	private void turnOffSZMarkC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Client ) {
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			
			if (data.param1 == player.GetIdentity().GetId()) 
			{
				player.setIsInSafeZone(false);
			}
        }
    }
	
	void turnOffMarks(string playerID) {
		GetRPCManager().SendRPC( "Falcon", "turnOffSZMarkC", new Param1<string>(playerID) );
	}
}