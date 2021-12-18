class TradersMessagesUtils
{
	static void messageClient(string message, PlayerBase player)
	{
		GetRPCManager().SendRPC("FalconTraders", "FTmessagePlayerC", new Param1<string>(message), true,  player.GetIdentity());
	}
}