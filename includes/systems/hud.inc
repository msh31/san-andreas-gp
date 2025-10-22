#if defined _hud_included
    #endinput
#endif
#define _hud_included

new PlayerText:welcomeText[MAX_PLAYERS]; //refactoring wip
new PlayerText:hudLevel[MAX_PLAYERS];
new PlayerText:hudMoney[MAX_PLAYERS];

stock CreatePlayerHUD(playerid) {
// Money
    hudMoney[playerid] = CreatePlayerTextDraw(playerid, 600.0, 150.0, "$0");
    PlayerTextDrawFont(playerid, hudMoney[playerid], 1);
    PlayerTextDrawLetterSize(playerid, hudMoney[playerid], 0.4, 1.6);
    PlayerTextDrawColor(playerid, hudMoney[playerid], 0x00FF00FF);
    PlayerTextDrawSetOutline(playerid, hudMoney[playerid], 1);
    PlayerTextDrawSetProportional(playerid, hudMoney[playerid], 1);
    PlayerTextDrawAlignment(playerid, hudMoney[playerid], 3); // right side
    PlayerTextDrawShow(playerid, hudMoney[playerid]);
    UpdatePlayerMoney(playerid);

// Level
    hudLevel[playerid] = CreatePlayerTextDraw(playerid, 585.0, 165.0, "Level: 0");
    PlayerTextDrawFont(playerid, hudLevel[playerid], 1);
    PlayerTextDrawLetterSize(playerid, hudLevel[playerid], 0.4, 1.6);
    PlayerTextDrawColor(playerid, hudLevel[playerid], 0x0099FFFF);
    PlayerTextDrawSetOutline(playerid, hudLevel[playerid], 1);
    PlayerTextDrawSetProportional(playerid, hudLevel[playerid], 1);
    PlayerTextDrawAlignment(playerid, hudLevel[playerid], 3); // right side
    PlayerTextDrawShow(playerid, hudLevel[playerid]);
    UpdatePlayerLevel(playerid);
}

stock UpdatePlayerMoney(playerid) {
    new string[32];
    format(string, sizeof(string), "$%d", Player[playerid][pMoney]);

    PlayerTextDrawSetString(playerid, hudMoney[playerid], string);
}

stock UpdatePlayerLevel(playerid) {
    new string[32];
    format(string, sizeof(string), "Level: %d", Player[playerid][pLevel]);

    PlayerTextDrawSetString(playerid, hudLevel[playerid], string);
}

stock DestroyPlayerHUD(playerid) {
    PlayerTextDrawDestroy(playerid, welcomeText[playerid]);
    PlayerTextDrawDestroy(playerid, hudMoney[playerid]);
    PlayerTextDrawDestroy(playerid, hudLevel[playerid]);
}

forward HideText(playerid);
public HideText(playerid) {
    PlayerTextDrawHide(playerid, welcomeText[playerid]);
    return 1;
}
