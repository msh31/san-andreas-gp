#if defined _vehicle_included
    #endinput
#endif
#define _vehicle_included

enum VehicleData {
    vDBID,
    vSAMPID,
    vModelID,
    vColor1,
    vColor2,
    vPaintjob,
    Float:vPos_x, Float:vPos_y, Float:vPos_z, Float:vPos_a,
    Float:vHealth
}

new CurrentVehicle[MAX_PLAYERS][VehicleData];

// this function should only be called once
// explains the hard coded position
stock GivePlayerStarterVehicle(playerid) {
    new insertQuery[256];

    CurrentVehicle[playerid][vModelID] = 560;
    CurrentVehicle[playerid][vColor1] = random(256);
    CurrentVehicle[playerid][vColor2] = random(256);
    CurrentVehicle[playerid][vPaintjob] = -1;
    CurrentVehicle[playerid][vPos_x] = 2495.33;
    CurrentVehicle[playerid][vPos_y] = 1644.80;
    CurrentVehicle[playerid][vPos_z] = 10.80;
    CurrentVehicle[playerid][vPos_a] = 0.0;
    CurrentVehicle[playerid][vHealth] = 1000.0;

    mysql_format(Database_GetHandle(), insertQuery, sizeof(insertQuery),
        "INSERT INTO `player_vehicles` (`player_id`, `model_id`, `color1`, `color2`, `paintjob`, \
        `pos_x`, `pos_y`, `pos_z`, `pos_a`, `health`) \
        VALUES (%d, %d, %d, %d, %d, %f, %f, %f, %f, %f)",
        Player[playerid][pDBID],
        CurrentVehicle[playerid][vModelID],
        CurrentVehicle[playerid][vColor1],
        CurrentVehicle[playerid][vColor2],
        CurrentVehicle[playerid][vPaintjob],
        CurrentVehicle[playerid][vPos_x],
        CurrentVehicle[playerid][vPos_y],
        CurrentVehicle[playerid][vPos_z],
        CurrentVehicle[playerid][vPos_a],
        CurrentVehicle[playerid][vHealth]
    );

    mysql_tquery(Database_GetHandle(), insertQuery, "OnVehicleCreated", "d", playerid);
}

forward OnVehicleCreated(playerid);
public OnVehicleCreated(playerid) {
    new vehicleDBID = cache_insert_id();
    CurrentVehicle[playerid][vDBID] = vehicleDBID;

    new updateQuery[128];
    mysql_format(Database_GetHandle(), updateQuery, sizeof(updateQuery),
        "UPDATE `players` SET `last_vehicle_id`=%d WHERE `id`=%d",
        vehicleDBID,
        Player[playerid][pDBID]
    );
    mysql_tquery(Database_GetHandle(), updateQuery, "", "");
}

stock LoadPlayerVehicle(playerid, vehicleDBID) {
    new query[256];
    mysql_format(Database_GetHandle(), query, sizeof(query),
        "SELECT * FROM `player_vehicles` WHERE `id` = %d",
        vehicleDBID
    );

    mysql_tquery(Database_GetHandle(), query, "OnPlayerVehicleLoaded", "d", playerid);
}

forward OnPlayerVehicleLoaded(playerid);
public OnPlayerVehicleLoaded(playerid) {
    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    if(cache_num_rows() == 0) {
         return 0;
    }

    cache_get_value_name_int(0, "id", CurrentVehicle[playerid][vDBID]);
    cache_get_value_name_int(0, "model_id", CurrentVehicle[playerid][vModelID]);
    cache_get_value_name_int(0, "color1", CurrentVehicle[playerid][vColor1]);
    cache_get_value_name_int(0, "color2", CurrentVehicle[playerid][vColor2]);
    cache_get_value_name_int(0, "paintjob", CurrentVehicle[playerid][vPaintjob]);
    cache_get_value_name_float(0, "pos_x", CurrentVehicle[playerid][vPos_x]);
    cache_get_value_name_float(0, "pos_y", CurrentVehicle[playerid][vPos_y]);
    cache_get_value_name_float(0, "pos_z", CurrentVehicle[playerid][vPos_z]);
    cache_get_value_name_float(0, "pos_a", CurrentVehicle[playerid][vPos_a]);
    cache_get_value_name_float(0, "health", CurrentVehicle[playerid][vHealth]);

    return 1;
}
