class FalconATMAccount
{
	private int balance;
	
	
	int getBalance() 
	{
		return balance;
	}
	
	void init()
	{
		balance = 0;
	}
	
	void depositMoney(int money)
	{
		balance += money;
	}
	
	void withdrawMoney(int money)
	{
		if (balance - money >= 0)
		{
			balance -= money;
		}
	}
}