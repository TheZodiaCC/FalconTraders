modded class MissionBase {
    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (!menu) {
            switch (id) {
				case 2138142: {
					menu = new TraderMenu;
					break;
				}
				case 1214649: {
					menu = new ATMMenu;
					break;
				}
            }
            if (menu) {
                menu.SetID(id);
            }
        }
        return menu;
    }
}