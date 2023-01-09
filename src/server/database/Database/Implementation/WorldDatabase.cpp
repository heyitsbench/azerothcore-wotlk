/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "WorldDatabase.h"
#include "MySQLPreparedStatement.h"

void WorldDatabaseConnection::DoPrepareStatements()
{
    if (!m_reconnecting)
        m_stmts.resize(MAX_WORLDDATABASE_STATEMENTS);

    PrepareStatement(WORLD_SEL_QUEST_POOLS, "SELECT Entry, PoolEntry FROM pool_quest", CONNECTION_SYNCH);
    PrepareStatement(WORLD_DEL_CRELINKED_RESPAWN, "DELETE FROM linked_respawn WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_REP_CREATURE_LINKED_RESPAWN, "REPLACE INTO linked_respawn (GUID, LinkedGUID) VALUES (?, ?)", CONNECTION_ASYNC);
    PrepareStatement(WORLD_SEL_CREATURE_TEXT, "SELECT CreatureID, GroupID, ID, Text, Type, Language, Probability, Emote, Duration, Sound, BroadcastTextID, TextRange FROM creature_text", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_SMART_SCRIPTS, "SELECT EntryOrGUID, SourceType, ID, Link, EventType, EventPhaseMask, EventChance, EventFlags, EventParam1, EventParam2, EventParam3, EventParam4, EventParam5, ActionType, ActionParam1, ActionParam2, ActionParam3, ActionParam4, ActionParam5, ActionParam6, TargetType, TargetParam1, TargetParam2, TargetParam3, TargetParam4, TargetX, TargetY, TargetZ, TargetO FROM smart_scripts ORDER BY EntryOrGUID, SourceType, ID, Link", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_SMARTAI_WP, "SELECT Entry, PointID, PositionX, PositionY, PositionZ, Orientation, Delay FROM waypoints ORDER BY Entry, PointID", CONNECTION_SYNCH);
    PrepareStatement(WORLD_DEL_GAMEOBJECT, "DELETE FROM gameobject WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_DEL_EVENT_GAMEOBJECT, "DELETE FROM game_event_gameobject WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_INS_GRAVEYARD_ZONE, "INSERT INTO graveyard_zone (ID, GhostZone, Faction) VALUES (?, ?, ?)", CONNECTION_ASYNC);
    PrepareStatement(WORLD_DEL_GRAVEYARD_ZONE, "DELETE FROM graveyard_zone WHERE ID = ? AND GhostZone = ? AND Faction = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_INS_GAME_TELE, "INSERT INTO game_tele (ID, PositionX, PositionY, PositionZ, Orientation, Map, Name) VALUES (?, ?, ?, ?, ?, ?, ?)", CONNECTION_ASYNC);
    PrepareStatement(WORLD_DEL_GAME_TELE, "DELETE FROM game_tele WHERE Name = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_INS_NPC_VENDOR, "INSERT INTO npc_vendor (Entry, Item, MaxCount, IncrTime, ExtendedCost) VALUES(?, ?, ?, ?, ?)", CONNECTION_ASYNC);
    PrepareStatement(WORLD_DEL_NPC_VENDOR, "DELETE FROM npc_vendor WHERE Entry = ? AND Item = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_SEL_NPC_VENDOR_REF, "SELECT Item, MaxCount, IncrTime, ExtendedCost FROM npc_vendor WHERE Entry = ? ORDER BY Slot ASC", CONNECTION_SYNCH);
    PrepareStatement(WORLD_UPD_CREATURE_MOVEMENT_TYPE, "UPDATE creature SET MovementType = ? WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_CREATURE_FACTION, "UPDATE creature_template SET Faction = ? WHERE Entry = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_CREATURE_NPCFLAG, "UPDATE creature_template SET NPCFlag = ? WHERE Entry = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_CREATURE_POSITION, "UPDATE creature SET PositionX = ?, PositionY = ?, PositionZ = ?, Orientation = ? WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_CREATURE_WANDER_DISTANCE, "UPDATE creature SET WanderDistance = ?, MovementType = ? WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_CREATURE_SPAWN_TIME_SECS, "UPDATE creature SET SpawnTimeSecs = ? WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_INS_CREATURE_FORMATION, "INSERT INTO creature_formations (LeaderGUID, MemberGUID, Distance, Angle, GroupAI) VALUES (?, ?, ?, ?, ?)", CONNECTION_ASYNC);
    PrepareStatement(WORLD_INS_WAYPOINT_DATA, "INSERT INTO waypoint_data (ID, Point, PositionX, PositionY, PositionZ) VALUES (?, ?, ?, ?, ?)", CONNECTION_ASYNC);
    PrepareStatement(WORLD_DEL_WAYPOINT_DATA, "DELETE FROM waypoint_data WHERE ID = ? AND Point = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_WAYPOINT_DATA_POINT, "UPDATE waypoint_data SET Point = Point - 1 WHERE ID = ? AND Point > ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_WAYPOINT_DATA_POSITION, "UPDATE waypoint_data SET PositionX = ?, PositionY = ?, PositionZ = ? where ID = ? AND Point = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_WAYPOINT_DATA_WPGUID, "UPDATE waypoint_data SET WaypointGUID = ? WHERE ID = ? and Point = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_SEL_WAYPOINT_DATA_MAX_ID, "SELECT MAX(ID) FROM waypoint_data", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_WAYPOINT_DATA_MAX_POINT, "SELECT MAX(Point) FROM waypoint_data WHERE ID = ?", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_WAYPOINT_DATA_BY_ID, "SELECT Point, PositionX, PositionY, PositionZ, Orientation, MoveType, Delay, Action, ActionChance FROM waypoint_data WHERE ID = ? ORDER BY Point", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_WAYPOINT_DATA_POS_BY_ID, "SELECT Point, PositionX, PositionY, PositionZ FROM waypoint_data WHERE ID = ?", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_WAYPOINT_DATA_POS_FIRST_BY_ID, "SELECT PositionX, PositionY, PositionZ FROM waypoint_data WHERE Point = 1 AND ID = ?", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_WAYPOINT_DATA_POS_LAST_BY_ID, "SELECT PositionX, PositionY, PositionZ, Orientation FROM waypoint_data WHERE ID = ? ORDER BY Point DESC LIMIT 1", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_WAYPOINT_DATA_BY_WPGUID, "SELECT ID, Point FROM waypoint_data WHERE WaypointGUID = ?", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_WAYPOINT_DATA_ALL_BY_WPGUID, "SELECT ID, Point, Delay, MoveType, Action, ActionChance FROM waypoint_data WHERE WaypointGUID = ?", CONNECTION_SYNCH);
    PrepareStatement(WORLD_UPD_WAYPOINT_DATA_ALL_WPGUID, "UPDATE waypoint_data SET WaypointGUID = 0", CONNECTION_ASYNC);
    PrepareStatement(WORLD_SEL_WAYPOINT_DATA_BY_POS, "SELECT ID, Point FROM waypoint_data WHERE (abs(PositionX - ?) <= ?) and (abs(PositionY - ?) <= ?) and (abs(PositionZ - ?) <= ?)", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_WAYPOINT_DATA_WPGUID_BY_ID, "SELECT WaypointGUID FROM waypoint_data WHERE ID = ? and WaypointGUID <> 0", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_WAYPOINT_DATA_ACTION, "SELECT DISTINCT Action FROM waypoint_data", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_WAYPOINT_SCRIPTS_MAX_ID, "SELECT MAX(GUID) FROM waypoint_scripts", CONNECTION_SYNCH);
    PrepareStatement(WORLD_INS_CREATURE_ADDON, "INSERT INTO creature_addon(GUID, PathID) VALUES (?, ?)", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_CREATURE_ADDON_PATH, "UPDATE creature_addon SET PathID = ? WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_DEL_CREATURE_ADDON, "DELETE FROM creature_addon WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_SEL_CREATURE_ADDON_BY_GUID, "SELECT GUID FROM creature_addon WHERE GUID = ?", CONNECTION_SYNCH);
    PrepareStatement(WORLD_INS_WAYPOINT_SCRIPT, "INSERT INTO waypoint_scripts (GUID) VALUES (?)", CONNECTION_ASYNC);
    PrepareStatement(WORLD_DEL_WAYPOINT_SCRIPT, "DELETE FROM waypoint_scripts WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_WAYPOINT_SCRIPT_ID, "UPDATE waypoint_scripts SET ID = ? WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_WAYPOINT_SCRIPT_X, "UPDATE waypoint_scripts SET X = ? WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_WAYPOINT_SCRIPT_Y, "UPDATE waypoint_scripts SET Y = ? WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_WAYPOINT_SCRIPT_Z, "UPDATE waypoint_scripts SET Z = ? WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_WAYPOINT_SCRIPT_O, "UPDATE waypoint_scripts SET O = ? WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_SEL_WAYPOINT_SCRIPT_ID_BY_GUID, "SELECT ID FROM waypoint_scripts WHERE GUID = ?", CONNECTION_SYNCH);
    PrepareStatement(WORLD_DEL_CREATURE, "DELETE FROM creature WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_SEL_COMMANDS, "SELECT Name, Security, Help FROM command", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_CREATURE_TEMPLATE, "SELECT Entry, DifficultyEntry1, DifficultyEntry2, DifficultyEntry3, KillCredit1, KillCredit2, ModelID1, ModelID2, ModelID3, ModelID4, Name, Subname, IconName, GossipMenuID, MinLevel, MaxLevel, Expansion, Faction, NPCFlag, SpeedWalk, SpeedRun, SpeedSwim, SpeedFlight, DetectionRange, Scale, `Rank`, DamageSchool, DamageModifier, BaseAttackTime, RangeAttackTime, BaseVariance, RangeVariance, UnitClass, UnitFlags1, UnitFlags2, DynamicFlags, Family, TrainerType, TrainerSpell, TrainerClass, TrainerRace, Type, TypeFlags, LootID, PickpocketLoot, SkinLoot, PetSpellDataID, VehicleID, MinGold, MaxGold, AIName, MovementType, ctm.Ground, ctm.Swim, ctm.Flight, ctm.Rooted, ctm.Chase, ctm.Random, ctm.InteractionPauseTimer, HoverHeight, HealthModifier, ManaModifier, ArmorModifier, ExperienceModifier, RacialLeader, MovementID, RegenHealth, MechanicImmuneMask, SpellSchoolImmuneMask, FlagsExtra, ScriptName FROM creature_template ct LEFT JOIN creature_template_movement ctm ON ct.Entry = ctm.CreatureID WHERE Entry = ?", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_WAYPOINT_SCRIPT_BY_ID, "SELECT GUID, Delay, Command, Data1, Data2, Data3, X, Y, Z, O FROM waypoint_scripts WHERE ID = ?", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_ITEM_TEMPLATE_BY_NAME, "SELECT Entry FROM item_template WHERE Name = ?", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_CREATURE_BY_ID, "SELECT GUID FROM creature WHERE ID1 = ? OR ID2 = ? OR ID3 = ?", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_GAMEOBJECT_NEAREST, "SELECT GUID, ID, PositionX, PositionY, PositionZ, Map, (POW(PositionX - ?, 2) + POW(PositionY - ?, 2) + POW(PositionZ - ?, 2)) AS order_ FROM gameobject WHERE Map = ? AND (POW(PositionX - ?, 2) + POW(PositionY - ?, 2) + POW(PositionZ - ?, 2)) <= ? AND (PhaseMask & ?) <> 0 ORDER BY order_", CONNECTION_SYNCH);
    PrepareStatement(WORLD_SEL_CREATURE_NEAREST, "SELECT GUID, ID1, ID2, ID3, PositionX, PositionY, PositionZ, Map, (POW(PositionX - ?, 2) + POW(PositionY - ?, 2) + POW(PositionZ - ?, 2)) AS order_ FROM creature WHERE Map = ? AND (POW(PositionX - ?, 2) + POW(PositionY - ?, 2) + POW(PositionZ - ?, 2)) <= ? AND (PhaseMask & ?) <> 0 ORDER BY order_", CONNECTION_SYNCH);
    PrepareStatement(WORLD_INS_CREATURE, "INSERT INTO creature (GUID, ID1, ID2, ID3, Map, SpawnMask, PhaseMask, EquipmentID, PositionX, PositionY, PositionZ, Orientation, SpawnTimeSecs, WanderDistance, CurrentWaypoint, CurrentHealth, CurrentMana, MovementType, NPCFlag, UnitFlags, DynamicFlags) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", CONNECTION_ASYNC);
    PrepareStatement(WORLD_DEL_GAME_EVENT_CREATURE, "DELETE FROM game_event_creature WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_DEL_GAME_EVENT_MODEL_EQUIP, "DELETE FROM game_event_model_equip WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_INS_GAMEOBJECT, "INSERT INTO gameobject (GUID, ID, Map, SpawnMask, PhaseMask, PositionX, PositionY, PositionZ, Orientation, Rotation1, Rotation2, Rotation3, Rotation4, SpawnTimeSecs, AnimProgress, State) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", CONNECTION_ASYNC);
    PrepareStatement(WORLD_INS_DISABLES, "INSERT INTO disables (Entry, SourceType, Flags, Comment) VALUES (?, ?, ?, ?)", CONNECTION_ASYNC);
    PrepareStatement(WORLD_SEL_DISABLES, "SELECT Entry FROM disables WHERE Entry = ? AND SourceType = ?", CONNECTION_SYNCH);
    PrepareStatement(WORLD_DEL_DISABLES, "DELETE FROM disables WHERE Entry = ? AND SourceType = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_CREATURE_ZONE_AREA_DATA, "UPDATE creature SET ZoneID = ?, AreaID = ? WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_UPD_GAMEOBJECT_ZONE_AREA_DATA, "UPDATE gameobject SET ZoneID = ?, AreaID = ? WHERE GUID = ?", CONNECTION_ASYNC);
    PrepareStatement(WORLD_INS_GAMEOBJECT_ADDON, "INSERT INTO gameobject_addon (GUID, InvisibilityType, InvisibilityValue) VALUES (?, 0, 0)", CONNECTION_ASYNC);
    // 0: uint8
    PrepareStatement(WORLD_SEL_REQ_XP, "SELECT Experience FROM player_xp_for_level WHERE Level = ?", CONNECTION_SYNCH);
}

WorldDatabaseConnection::WorldDatabaseConnection(MySQLConnectionInfo& connInfo) : MySQLConnection(connInfo)
{
}

WorldDatabaseConnection::WorldDatabaseConnection(ProducerConsumerQueue<SQLOperation*>* q, MySQLConnectionInfo& connInfo) : MySQLConnection(q, connInfo)
{
}

WorldDatabaseConnection::~WorldDatabaseConnection()
{
}
