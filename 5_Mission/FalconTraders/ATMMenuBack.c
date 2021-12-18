class ATMMenuBack
{
	void ATMMenuBack()
	{
		GetRPCManager().AddRPC( "FalconTraders", "getMaxMoneyBalanceS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "getYourAccountBalanceS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "depositS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "withdrawS", this, SingeplayerExecutionType.Server );
	}
	
	private void getMaxMoneyBalanceS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) 
		{
			FalconATMConfig config = FalconATMUtils.getATMsConfig();
		
			GetRPCManager().SendRPC( "FalconTraders", "getMaxMoneyBalanceC", new Param1<int>(config.getMaxAccountBalance()), true, sender );
       	}
    }
	
	void getMaxMoneyBalance() 
	{		
		GetRPCManager().SendRPC( "FalconTraders", "getMaxMoneyBalanceS", new Param1<string>("") );
	}
	
	private void getYourAccountBalanceS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) 
		{
			FalconATMAccount accountData = FalconATMUtils.getAccountData(sender.GetId());
		
			GetRPCManager().SendRPC( "FalconTraders", "getYourAccountBalanceC", new Param1<int>(accountData.getBalance()), true, sender );
       	 }
    }
	
	void getYourAccountBalance() 
	{		
		GetRPCManager().SendRPC( "FalconTraders", "getYourAccountBalanceS", new Param1<string>("") );
	}
	
	private void withdrawS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<int> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) 
		{
			FalconATMAccount accountData = FalconATMUtils.getAccountData(sender.GetId());
			
			int accountBalance = accountData.getBalance();
			int money = data.param1;
			
			if (accountBalance - money >= 0)
			{
				FalconATMUtils.addMoney(FalconATMUtils.getPlayerByIdentity(sender), money);
				FalconATMUtils.withdrawMoney(sender.GetId(), money);
			}
       	}
    }
	
	void withdraw(int moneyAmmount) 
	{		
		GetRPCManager().SendRPC( "FalconTraders", "withdrawS", new Param1<int>(moneyAmmount) );
	}
	
	private void depositS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<int> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) 
		{
			FalconATMAccount accountData = FalconATMUtils.getAccountData(sender.GetId());
			FalconATMConfig config = FalconATMUtils.getATMsConfig();
			
			int accountBalance = accountData.getBalance();
			int money = data.param1;
			
			if (accountBalance + money <= config.getMaxAccountBalance())
			{
				FalconATMUtils.takeMoney(FalconATMUtils.getPlayerByIdentity(sender), money);
				FalconATMUtils.depositMoney(sender.GetId(), money);
			}
       	}
    }
	
	void deposit(int moneyAmmount) 
	{		
		GetRPCManager().SendRPC( "FalconTraders", "depositS", new Param1<int>(moneyAmmount) );
	}
}