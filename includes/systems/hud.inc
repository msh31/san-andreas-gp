#if defined _hud_included
    #endinput
#endif
#define _hud_included

new PlayerText:welcomeText[MAX_PLAYERS]; //refactoring wip
new PlayerText:hudMoney[MAX_PLAYERS];
//new PlayerText:hudLevel[MAX_PLAYERS];
//new PlayerText:hudRep[MAX_PLAYERS];

stock CreatePlayerHUD(playerid) {
// Money
    hudMoney[playerid] = CreatePlayerTextDraw(playerid, 550.0, 100.0, "$0");
    PlayerTextDrawFont(playerid, hudMoney[playerid], 1);
    PlayerTextDrawLetterSize(playerid, hudMoney[playerid], 0.4, 1.6);
    PlayerTextDrawColor(playerid, hudMoney[playerid], 0x00FF00FF);
    PlayerTextDrawSetOutline(playerid, hudMoney[playerid], 1);
    PlayerTextDrawSetProportional(playerid, hudMoney[playerid], 1);
    PlayerTextDrawAlignment(playerid, hudMoney[playerid], 3); // right side
    PlayerTextDrawShow(playerid, hudMoney[playerid]);
    UpdatePlayerMoney(playerid);
}

stock UpdatePlayerMoney(playerid) {
    new string[32];
    format(string, sizeof(string), "$%d", Player[playerid][pMoney]);

    PlayerTextDrawSetString(playerid, hudMoney[playerid], string);
}

stock UpdatePlayerLevel(playerid) {
    // TODO
}

stock DestroyPlayerHUD(playerid) {
    PlayerTextDrawDestroy(playerid, welcomeText[playerid]);
}

forward HideText(playerid);
public HideText(playerid) {
    PlayerTextDrawHide(playerid, welcomeText[playerid]);
    return 1;
}
