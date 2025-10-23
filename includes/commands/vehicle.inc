#if defined _vehiclecommands_included
    #endinput
#endif
#define _vehiclecommands_included

// puts the player back in their last vehicle
// dev command maily
CMD:getin(playerid, params[]) {
    if(!IsPlayerLoggedIn(playerid)) {
        return SendClientMessage(playerid, COLOR_ERROR, "You must be logged in!");
    }

    new vehicleid = CurrentVehicle[playerid][vSAMPID];
    if(vehicleid == 0) {
        return SendClientMessage(playerid, COLOR_ERROR, "You don't have a vehicle!");
    }

    PutPlayerInVehicle(playerid, vehicleid, 0);
    return 1;
}
