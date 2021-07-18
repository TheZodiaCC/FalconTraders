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
			
			player.setIsInSafeZone(true);
        }
    }
	
	void turnOnMarks() {
		GetRPCManager().SendRPC( "Falcon", "turnOnSZMarkC", new Param1<string>("") );
	}
	
	private void turnOffSZMarkC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Client ) {
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			
			player.setIsInSafeZone(false);
        }
    }
	
	void turnOffMarks() {
		GetRPCManager().SendRPC( "Falcon", "turnOffSZMarkC", new Param1<string>("") );
	}
}